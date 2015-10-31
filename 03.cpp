#include <functional> // std::multiplies
#include <numeric>    // std::accumulate
#include <boost/shared_ptr.hpp> // boost::shared_ptr
#include <iostream>   // std::cout, std::endl
#include <iomanip>    // std::setw

// added variadic element access using constexpr -- still not sure if this is the best way to do it or not

template<int k, typename T>
class Array {

  public:

    int _shape [k] = {};// shape (initialize array to 0)

    int _stride[k] = {};// stride

    int _nelem;

    boost::shared_ptr<T[]> _data;

    template<typename... Args>
    Array(const Args&... args) : _shape{args...} {
      /* check args */ static_assert(sizeof...(args) == k, "Requested shape does not match rank.");
      for(int i=0; i<k; ++i) _stride[i] = std::accumulate(_shape + 1, _shape + (k-i), 1, std::multiplies<int>());
      _nelem = std::accumulate(_shape, _shape + k, 1, std::multiplies<int>());
      _data  = boost::shared_ptr<T[]>(new T[_nelem]);
    }

    template<typename... Args>
    T  operator()(const Args&... args) const {
      /* check args */ static_assert(sizeof...(args) == k, "Number of indices does not match rank.");
      return this->_data[index<0>(args...)];
    }

    template<typename... Args>
    T& operator()(const Args&... args)       {
      /* check args */ static_assert(sizeof...(args) == k, "Number of indices does not match rank.");
      return this->_data[index<0>(args...)];
    }

    // converting multi-index to global index: this function should transform into
    //    arg1 * _stride[0] + arg2 * _stride[1] + ... + argk * _stride[k-1]
    // at compile time
    template<int ax, typename... Args>
    constexpr T index(int first, const Args&... rest) {return first * _stride[ax] + index<ax+1>(rest...);}
    template<int ax>
    constexpr T index() {return 0;}
};

int main() {
  Array<3,double> A(5,5,5);

  for(int i=0; i<3; ++i)
    std::cout << A._stride[i] << std::endl;

  for(int i=0; i<5; ++i)
    for(int j=0; j<5; ++j)
      for(int k=0; k<5; ++k)
        A(i,j,k) = 1/(5*5*i + 5*j + k + 1.);

  for(int i=0; i<5; ++i)
    for(int j=0; j<5; ++j)
      for(int k=0; k<5; ++k)
        std::cout << std::setw(10) << std::fixed << std::setprecision(5) << A(i,j,k) << (k==4 ? '\n' : ' ');

  A(0,0);

  std::cout << A._nelem << std::endl;
}
