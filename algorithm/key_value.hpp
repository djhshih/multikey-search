#ifndef _vector_hpp_
#define _vector_hpp_

namespace alg {

	template <typename key_t, typename value_t>
	struct key_value {
		key_t key;
		value_t value;
		key_value(const key_t& k, const value_t& v)
			: key(k), value(v) {}
	};

	// compare using only the key
	template <typename key_t, typename value_t>
	bool operator<(const key_value<key_t, value_t>& a, const key_value<key_t, value_t>& b) {
		return a.key < b.key;
	}

}

#endif
