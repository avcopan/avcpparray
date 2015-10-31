#include <iostream>   // std::cout, std::endl
#include <functional> // std::multiplies
#include <numeric>    // std::accumulate
#include <boost/shared_ptr.hpp> // boost::shared_ptr

template<int k, typename T>
class Array {

  public:

    int _shape [k] = {};// shape (initialize array to 0)

    int _stride[k] = {};// stride

    int _nelem;

    boost::shared_ptr<T[]> _data;

    template<typename... Args>
    Array(const Args&... args) : _shape{args...} {static_assert(sizeof...(args) == k, "Requested shape does not match rank.");
      for(int i=0; i<k; ++i) _stride[i] = std::accumulate(_shape + 1, _shape + (k-i), 1, std::multiplies<int>());
      _nelem = std::accumulate(_shape, _shape + k, 1, std::multiplies<int>());
      _data  = boost::shared_ptr<T[]>(new T[_nelem]);
    }

};

int main() {
  Array<5,double> A(1,2,3,4,5);

  for(int i=0; i<5; ++i)
    std::cout << A._stride[i] << std::endl;

  for(int i=0; i<120; ++i)
    std::cout << A._data[i] << std::endl;

  std::cout << A._nelem << std::endl;
}
