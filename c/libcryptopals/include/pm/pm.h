#ifndef PM_H_
#define PM_H_

#include <stddef.h>
#include <stdint.h>

#if defined (__cplusplus)
extern "C" {
#endif

#define PM_SUCCESS                   (0)
#define PM_FAILURE                   (-1)
#define PM_SKIPPED                   (-2)

#define PM_DIM(x)                    (sizeof(x) / sizeof(x[0]))
#define PM_MIN(x, y)                 ((x) <= (y) ? (x) : (y))
#define PM_MAX(x, y)                 ((x) >= (y) ? (x) : (y))
#define PM_STATIC_STRLEN(x)          (sizeof(x) - 1)

#define PM_CACHE_LINE_SIZE           64U
#define PM_CACHE_LINE_MASK           (PM_CACHE_LINE_SIZE-1)

#define PM_ALIGNED(x)                __attribute__((__aligned__((x))))

#define PM_CACHE_ALIGNED             PM_ALIGNED(PM_CACHE_LINE_SIZE)

/**
 * add a byte-value offset from a pointer
 */
#define PM_PTR_ADD(ptr, x) ((void*)((uintptr_t)(ptr) + (uintptr_t)(x)))

/**
 * subtract a byte-value offset from a pointer
 */
#define PM_PTR_SUB(ptr, x) ((void*)((uintptr_t)ptr - (uintptr_t)(x)))

/**
 * get the difference between two pointer values, i.e. how far apart
 * in bytes are the locations they point two. It is assumed that
 * ptr1 is greater than ptr2.
 */
#define PM_PTR_DIFF(ptr1, ptr2) ((uintptr_t)(ptr1) - (uintptr_t)(ptr2))

/*********** Macros/static functions for doing alignment ********/

#define PM_ROUND_UP(number, factor) \
        ((number + factor - 1) - ((number + factor - 1) % factor))

#define PM_ROUND_DOWN(number, factor) ()

/**
 * Macro to align a pointer to a given power-of-two. The resultant
 * pointer will be a pointer of the same type as the first parameter, and
 * point to an address no higher than the first parameter. Second parameter
 * must be a power-of-two value.
 */
#define PM_PTR_ALIGN_FLOOR(ptr, align) \
    ((__typeof__(ptr))PM_ALIGN_FLOOR((uintptr_t)ptr, align))

/**
 * Macro to align a value to a given power-of-two. The resultant value
 * will be of the same type as the first parameter, and will be no
 * bigger than the first parameter. Second parameter must be a
 * power-of-two value.
 */
#define PM_ALIGN_FLOOR(val, align) \
    (__typeof__(val))((val) & (~((__typeof__(val))((align) - 1))))

/**
 * Macro to align a pointer to a given power-of-two. The resultant
 * pointer will be a pointer of the same type as the first parameter, and
 * point to an address no lower than the first parameter. Second parameter
 * must be a power-of-two value.
 */
#define PM_PTR_ALIGN_CEIL(ptr, align) \
    PM_PTR_ALIGN_FLOOR((__typeof__(ptr))PM_PTR_ADD(ptr, (align) - 1), align)

/**
 * Macro to align a value to a given power-of-two. The resultant value
 * will be of the same type as the first parameter, and will be no lower
 * than the first parameter. Second parameter must be a power-of-two
 * value.
 */
#define PM_ALIGN_CEIL(val, align) \
    PM_ALIGN_FLOOR(((val) + ((__typeof__(val)) (align) - 1)), align)

/**
 * Macro to align a pointer to a given power-of-two. The resultant
 * pointer will be a pointer of the same type as the first parameter, and
 * point to an address no lower than the first parameter. Second parameter
 * must be a power-of-two value.
 * This function is the same as PM_PTR_ALIGN_CEIL
 */
#define PM_PTR_ALIGN(ptr, align) PM_PTR_ALIGN_CEIL(ptr, align)

/**
 * Macro to align a value to a given power-of-two. The resultant
 * value will be of the same type as the first parameter, and
 * will be no lower than the first parameter. Second parameter
 * must be a power-of-two value.
 * This function is the same as PM_ALIGN_CEIL
 */
#define PM_ALIGN(val, align)           PM_ALIGN_CEIL(val, align)

#define POWEROF2(x)                    ((((x)-1) & (x)) == 0)

#ifndef likely
#define likely(x)                      __builtin_expect((x),1)
#endif

#ifndef unlikely
#define unlikely(x)                    __builtin_expect((x),0)
#endif

#ifdef __SSE2__
#include <emmintrin.h>
/**
 * PAUSE instruction for tight loops
 */
static inline void
mpac_pause(void)
{
    _mm_pause();
}
#else
static inline void
mpac_pause(void) {}
#endif

struct mpac_version_s
{
    uint16_t major;
    uint8_t minor;
    uint8_t patch;
};

extern size_t mpac_alignpow2(
    size_t x);

extern int mpac_is_power_of_2(
    size_t n);

extern char *mpac_strncpy(
    char *dest, size_t szDest, char const *source);

#if defined (__cplusplus)
}
#endif

#endif
