/*!
 *  Copyright (c) 2017 by Contributors
 * \file half2.h
 * \brief definition of vector float16, half2 type.
 *
 * \author Antti-Pekka Hynninen
 */
#ifndef MSHADOW_HALF2_H_
#define MSHADOW_HALF2_H_

#if (defined(__CUDACC__) && __CUDA_ARCH__ >= 530 && MSHADOW_USE_CUDA && CUDA_VERSION >= 7050)
  #define MSHADOW_CUDA_HALF2 1
  #include <cuda_fp16.h>
  #define MSHADOW_HALF2_INLINE MSHADOW_FORCE_INLINE __device__
#else
  #define MSHADOW_CUDA_HALF2 0
  #define MSHADOW_HALF2_INLINE MSHADOW_FORCE_INLINE
#endif

/*! \brief namespace for mshadow */
namespace mshadow {
/* \brief name space for host/device portable half-precision floats */
namespace half {

#define MSHADOW_HALF2_ASSIGNOP(AOP, OP)                                   \
  template<typename T>                                                    \
  MSHADOW_XINLINE half2_t operator AOP (const T& a) {                     \
    return *this = half2_t(*this OP a);  /* NOLINT(*)*/                   \
  }                                                                       \

class half2_t {
 public:
#if MSHADOW_CUDA_HALF2
  half2 half2_;
#else
  half_t half_t2[2];
#endif

  MSHADOW_HALF2_INLINE half2_t() {}

#if MSHADOW_CUDA_HALF2
  MSHADOW_HALF2_INLINE explicit half2_t(half2 a) : half2_(a) {}
#else
  MSHADOW_HALF2_INLINE explicit half2_t(half_t a, half_t b) {
    half_t2[0] = a;
    half_t2[1] = b;
  }
#endif

  MSHADOW_HALF2_INLINE explicit half2_t(int a) {
#if MSHADOW_CUDA_HALF2
    half2_ = __half2half2(__int2half_rz(a));
#else
    half_t2[0] = (half_t)a;
    half_t2[1] = (half_t)a;
#endif
  }

  MSHADOW_HALF2_INLINE half2_t operator+() {
    return *this;
  }

  MSHADOW_HALF2_INLINE half2_t operator-() {
#if MSHADOW_CUDA_HALF2
    return half2_t(__hneg2(half2_));
#else
    return half2_t(-half_t2[0], -half_t2[1]);
#endif
  }

  MSHADOW_HALF2_INLINE half2_t operator=(const half2_t& a) {
#if MSHADOW_CUDA_HALF2
    half2_ = a.half2_;
#else
    half_t2[0] = a.half_t2[0];
    half_t2[1] = a.half_t2[1];
#endif
    return a;
  }

  MSHADOW_HALF2_ASSIGNOP(+=, +)
  MSHADOW_HALF2_ASSIGNOP(-=, -)
  MSHADOW_HALF2_ASSIGNOP(*=, *)
  MSHADOW_HALF2_ASSIGNOP(/=, /)
};

/*! \brief overloaded + operator for half2_t */
MSHADOW_HALF2_INLINE half2_t operator+(half2_t a, half2_t b) {
#if MSHADOW_CUDA_HALF2
  return half2_t(__hadd2(a.half2_, b.half2_));
#else
  return half2_t(a.half_t2[0] + b.half_t2[0], a.half_t2[1] + b.half_t2[1]);
#endif
}
/*! \brief overloaded - operator for half2_t */
MSHADOW_HALF2_INLINE half2_t operator-(half2_t a, half2_t b) {
#if MSHADOW_CUDA_HALF2
  return half2_t(__hsub2(a.half2_, b.half2_));
#else
  return half2_t(a.half_t2[0] - b.half_t2[0], a.half_t2[1] - b.half_t2[1]);
#endif
}
/*! \brief overloaded * operator for half2_t */
MSHADOW_HALF2_INLINE half2_t operator*(half2_t a, half2_t b) {
#if MSHADOW_CUDA_HALF2
  return half2_t(__hmul2(a.half2_, b.half2_));
#else
  return half2_t(a.half_t2[0] * b.half_t2[0], a.half_t2[1] * b.half_t2[1]);
#endif
}
/*! \brief overloaded / operator for half2_t */
MSHADOW_HALF2_INLINE half2_t operator/(half2_t a, half2_t b) {
#if MSHADOW_CUDA_HALF2
  return half2_t(h2div(a.half2_, b.half2_));
#else
  return half2_t(a.half_t2[0] / b.half_t2[0], a.half_t2[1] / b.half_t2[1]);
#endif
}
/*! \brief overloaded == operator for half2_t */
MSHADOW_HALF2_INLINE bool operator==(half2_t a, half2_t b) {
#if MSHADOW_CUDA_HALF2
  return __hbeq2(a.half2_, b.half2_);
#else
  return (a.half_t2[0] == b.half_t2[0] && a.half_t2[1] == b.half_t2[1]);
#endif
}

}  // namespace half
}  // namespace mshadow
#endif  // MSHADOW_HALF2_H_

