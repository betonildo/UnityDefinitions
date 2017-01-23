#ifndef USING_SSE
#define USING_SSE

#ifdef USE_SSE

//#if _WIN32 || _WIN64
#include <xmmintrin.h>
#include <emmintrin.h>

#define SHUFFLE_PARAM(x, y, z, w) ((x) | ((y) << 2) | ((z) << 4) | ((w) << 6))
#define _mm_replicate_x_ps(v) _mm_shuffle_ps((v), (v), SHUFFLE_PARAM(0, 0, 0, 0))
#define _mm_replicate_y_ps(v) _mm_shuffle_ps((v), (v), SHUFFLE_PARAM(1, 1, 1, 1))
#define _mm_replicate_z_ps(v) _mm_shuffle_ps((v), (v), SHUFFLE_PARAM(2, 2, 2, 2))
#define _mm_replicate_w_ps(v) _mm_shuffle_ps((v), (v), SHUFFLE_PARAM(3, 3, 3, 3))
#define _mm_madd_ps(a, b, c) _mm_add_ps(_mm_mul_ps((a), (b)), (c))

static inline __m128i muly(const __m128i& a, const __m128i& b) {

#ifdef __SSE4_1__  // modern CPU - use SSE 4.1
    return _mm_mullo_epi32(a, b);
#else               // old CPU - use SSE 2
    __m128i tmp1 = _mm_mul_epu32(a,b); /* mul 2,0*/
    __m128i tmp2 = _mm_mul_epu32( _mm_srli_si128(a,4), _mm_srli_si128(b,4)); /* mul 3,1 */
    return _mm_unpacklo_epi32(_mm_shuffle_epi32(tmp1, _MM_SHUFFLE (0,0,2,0)), _mm_shuffle_epi32(tmp2, _MM_SHUFFLE (0,0,2,0))); /* shuffle results to [63..0] and pack */
#endif

}

static inline __m128 mulVectorMatrixFinal(const __m128& v, const __m128 Mrow[4]) {
    __m128 result;
    result = _mm_mul_ps (_mm_replicate_x_ps(v), Mrow[0]);
    result = _mm_madd_ps(_mm_replicate_y_ps(v), Mrow[1], result);
    result = _mm_madd_ps(_mm_replicate_z_ps(v), Mrow[2], result);
    result = _mm_madd_ps(_mm_replicate_w_ps(v), Mrow[3], result);
    return result;
}

static inline __m128 addWithIntrinsics(const __m128& a, const __m128& b) {
    return _mm_add_ps(a, b);
}

static inline __m128 mulVectorMatrixAttempt2(const __m128& v, const __m128& Mrow0, const __m128& Mrow1, const __m128& Mrow2, const __m128& Mrow3)
{
    const __m128 xxxx = _mm_replicate_x_ps(v);
    const __m128 yyyy = _mm_replicate_y_ps(v);
    const __m128 zzzz = _mm_replicate_z_ps(v);
    const __m128 wwww = _mm_replicate_w_ps(v);
    const __m128 xMrow0 = _mm_mul_ps(xxxx, Mrow0);
    const __m128 yMrow1 = _mm_mul_ps(yyyy, Mrow1);
    const __m128 zMrow2 = _mm_mul_ps(zzzz, Mrow2);
    const __m128 wMrow3 = _mm_mul_ps(wwww, Mrow3);
    __m128 result = _mm_add_ps(xMrow0, yMrow1);
    result = _mm_add_ps(result, zMrow2);
    result = _mm_add_ps(result, wMrow3);
    return result;
}


//#endif /*_WIN32 || _WIN64*/


// #if __GNUC__

// #include <xmmintrin.h>

// #endif /*__GNUC__*/

#endif /*USE_SSE*/
#endif /*USING_SSE*/