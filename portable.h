#if __GNUC__ >= 3
# define __noinline __attribute__ ((noinline))
# define __pure __attribute__ ((pure))
# define __const __attribute__ ((const))
# define __noreturn __attribute__ ((noreturn))
# define __malloc __attribute__ ((malloc))
# define __must_check __attribute__ ((warn_unused_result))
# define __deprecated __attribute__ ((deprecated))
# define __used __attribute__ ((used))
# define __unused __attribute__ ((unused))
# define __packed __attribute__ ((packed))
# define __align(x) __attribute__ ((aligned (x)))
# define __align_max __attribute__ ((aligned))
# define likely(x) __builtin_expect (!!(x), 1)
# define unlikely(x) __builtin_expect (!!(x), 0)
#else
# define __noinline  /* no noinline */
# define __pure  /* no pure */
# define __const  /* no const */
# define __noreturn  /* no noreturn */
# define __malloc  /* no malloc */
# define __must_check  /* no warn_unused_result */
# define __deprecated  /* no deprecated */
# define __used  /* no used */
# define __unused  /* no unused */
# define __packed  /* no packed */
# define __align(x)  /* no aligned */
# define __align_max  /* no align_max */
# define likely(x) (x)
# define unlikely(x) (x)
#endif

