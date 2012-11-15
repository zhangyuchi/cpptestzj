#ifndef __febird_fast_hash_common__
#define __febird_fast_hash_common__

#include "node_layout.hpp"
#include <algorithm>

// HSM_ : Hash String Map
#define HSM_SANITY assert

#if defined(__GNUC__) || defined(__INTEL_COMPILER) || defined(__clang__)
	#define HSM_unlikely(expr) __builtin_expect(expr, 0)
#else
	#define HSM_unlikely(expr) expr
#endif

template<class Uint>
inline Uint BitsRotateLeft(Uint x, int c) {
	assert(c >= 0);
	assert(c < (int)sizeof(Uint)*8);
	BOOST_STATIC_ASSERT(Uint(~Uint(0)) > 0); // is unsigned
	return x << c | x >> (sizeof(Uint)*8 - c);
}
template<class Uint>
inline Uint BitsRotateRight(Uint x, int c) {
	assert(c >= 0);
	assert(c < (int)sizeof(Uint)*8);
	BOOST_STATIC_ASSERT(Uint(~Uint(0)) > 0); // is unsigned
	return x >> c | x << (sizeof(Uint)*8 - c);
}
inline static size_t
__hsm_stl_next_prime(size_t __n)
{
	static const size_t primes[] =
	{
		5,11,19,37,   53ul,         97ul,         193ul,       389ul,
		769ul,        1543ul,       3079ul,       6151ul,      12289ul,
		24593ul,      49157ul,      98317ul,      196613ul,    393241ul,
		786433ul,     1572869ul,    3145739ul,    6291469ul,   12582917ul,
		25165843ul,   50331653ul,   100663319ul,  201326611ul, 402653189ul,
		805306457ul,  1610612741ul, 3221225473ul, 4294967291ul
	};
	const size_t* __first = primes;
	const size_t* __last = primes + sizeof(primes)/sizeof(primes[0]);
	const size_t* pos = std::lower_bound(__first, __last, __n);
	return pos == __last ? __last[-1] : *pos;
}

inline size_t __hsm_align_pow2(size_t x) {
	assert(x > 0);
	size_t p = 0, y = x;
	while (y)
		y >>= 1, ++p;
	if ((size_t(1) << (p-1)) == x)
		return x;
	else
		return size_t(1) << p;
}

template<class UInt>
struct dummy_bucket{
	typedef UInt link_t;
	static const UInt tail = ~UInt(0);
	static const UInt delmark = tail-1;
	static UInt b[1];
};
template<class UInt> UInt dummy_bucket<UInt>::b[1] = {~UInt(0)};

template<class Key, class Hash, class Equal>
struct hash_and_equal : private Hash, private Equal {
	size_t hash(const Key& x) const { return Hash::operator()(x); }
	bool  equal(const Key& x, const Key& y) const {
	   	return Equal::operator()(x, y);
   	}
	hash_and_equal() {}
	hash_and_equal(const Hash& h, const Equal& eq) : Hash(h), Equal(eq) {}
};

#endif // __febird_fast_hash_common__  

