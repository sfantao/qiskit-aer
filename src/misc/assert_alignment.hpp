/**
 * This code is part of Qiskit.
 *
 * (C) Copyright AMD 2023.
 *
 * This code is licensed under the Apache License, Version 2.0. You may
 * obtain a copy of this license in the LICENSE.txt file in the root directory
 * of this source tree or at http://www.apache.org/licenses/LICENSE-2.0.
 *
 * Any modifications or derivative works of this code must retain this
 * copyright notice, and modified files need to carry a notice indicating
 * that they have been altered from the originals.
 */
#ifndef __ASSERT_ALIGNMENT_H__
#define __ASSERT_ALIGNMENT_H__

#include <memory>

//
// Utility function to control alignment of pointers at runtime so that we
// assert that the assumptions being made are not being broken, e.g.
// std::complex pointers alignment is strict enough for thrust::complex.
//
template <typename T1, typename T2>
T1 *assert_alignment(T2 *ptr) {
  size_t space = alignof(T1);
  // Leverage std::align functionality by getting rid of the const qualifiers.
  void *in_ptr = const_cast<void *>(reinterpret_cast<const void *>(ptr));
  void *ret_ptr = std::align(space, space, in_ptr, space);

  if (!ret_ptr || space < alignof(T1)) {
    std::stringstream str;
    throw std::runtime_error("Runtime alignement assertion failed.");
  }
  return reinterpret_cast<T1 *>(ptr);
}

#endif //__ASSERT_ALIGNMENT_H__
