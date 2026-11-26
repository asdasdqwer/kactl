/**
 * Author: Simon Lindholm
 * Date: 2015-03-15
 * License: CC0
 * Source: own work
 * Description: Self-explanatory methods for string hashing.
 * HashInterval can be used for querying hashes, hashString computes
 * the hash of the entire string. 
 * Status: stress-tested
 */
#pragma once

typedef uint64_t ull;
const ull M = (1ULL << 61) - 1;
struct H {
	ull x; H(ull v = 0) : x((v & M) + (v >> 61)) { if (x >= M) x -= M; }
	H operator+(H o) { return x + o.x; }
	H operator-(H o) { return x + M - o.x; }
	H operator*(H o) { auto m = (__uint128_t)x * o.x;
		return (ull)(m & M) + (ull)(m >> 61); }
	ull get() const { return x; }
	bool operator==(H o) const { return x == o.x; }
	bool operator<(H o) const { return x < o.x; }
};

static const H C = mt19937_64(chrono::...)(); // C < M always true
static const H R = mt19937_64(chrono::... + 1)();
// R only for GridHasher, R != C necessary

struct HashInterval {
	vector<H> ha, pw;
	HashInterval(string& str) : ha(sz(str)+1), pw(ha) {
		pw[0] = 1;
		rep(i,0,sz(str))
			ha[i+1] = ha[i] * C + str[i],
			pw[i+1] = pw[i] * C;
	}
	H hashInterval(int a, int b) { // hash [a, b)
		return ha[b] - ha[a] * pw[b - a];
	}
};


H hashString(string& s){H h{}; for(char c:s) h=h*C+c;return h;}
