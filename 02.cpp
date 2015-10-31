#include <iostream>   // std::cout, std::endl
#include <functional> // std::multiplies
#include <numeric>    // std::accumulate
#include <boost/shared_ptr.hpp> // boost::shared_ptr

// adding move semantics

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


    // do we need these?
    Array(Array&& other) {
      boost::shared_ptr<T[]>::swap(this->_data, other._data); other._data.reset();
      std::swap(this->_shape , other._shape );
      std::swap(this->_stride, other._stride); 
    }

    Array& operator=(Array&& other) {
      std::swap(this->_data  , other._data  ); other._data.reset();
      std::swap(this->_shape , other._shape );
      std::swap(this->_stride, other._stride); 
    }
};

int main() {
  Array<3,double> A(5,5,5);

  Array<3,double> B(5,5,5);

  for(int i=0; i<3; ++i)
    std::cout << A._stride[i] << std::endl;

  A = std::move(B);

  for(int i=0; i<3; ++i)
    std::cout << A._stride[i] << std::endl;

  std::cout << A._nelem << std::endl;
}
