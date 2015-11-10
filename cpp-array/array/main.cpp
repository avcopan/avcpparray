/*
 * Copyright (©) 2014 Alejandro M. Aragón
 * Written by Alejandro M. Aragón <alejandro.aragon@fulbrightmail.org>
 * All Rights Reserved
 *
 * cpp-array is free  software: you can redistribute it and/or  modify it under
 * the terms  of the  GNU Lesser  General Public  License as  published by  the
 * Free Software Foundation, either version 3 of the License, or (at your
 *option)
 * any later version.
 *
 * cpp-array is  distributed in the  hope that it  will be useful, but  WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 * FOR A  PARTICULAR PURPOSE. See  the GNU  Lesser General  Public License  for
 * more details.
 *
 * You should  have received  a copy  of the GNU  Lesser General  Public License
 * along with cpp-array. If not, see <http://www.gnu.org/licenses/>.
 *
 */

#include <iostream>
#include <iomanip>

#include "array.hpp"

using std::cout;
using std::endl;

using namespace array;

void separator() { cout << std::setw(40) << std::setfill('_') << " " << endl; }

int main(int argc, char **argv) {

  typedef array::vector_type<double> vector_type;
  typedef array::matrix_type<double> matrix_type;
//  typedef array::tensor_type<double> tensor_type;

//  // create 10x10 identity matrix
//  matrix_type A(10, [=](int i, int j) { return i == j ? 1 : 0; });
//  cout << "A: " << A << endl;
  
  

  vector_type b = {1,2,3,4};
  vector_type a = b;

  
  
  
  double s = (transpose(a)*b) / (transpose(b) * b);
//    double s = (5.) / (transpose(b) * b);
//  double s = (transpose(a)*b) / (5.);

  
  cout<<s<<endl;


  return 0;
}
