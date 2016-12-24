#ifndef _key_vector_hpp_
#define _key_vector_hpp_

#include "slice.hpp"

namespace alg {

/**
 * Vector of multikeys
 *
 * A mkey_vector instance is populated by successive calls to add_slice(x)
 * where x is a slice of values for the next dimension of the multikey.
 * Therefore, all multikeys must be available at construction.
 *
 * Each dimension of the multikey must have the same type.
 * (There is no dynamic heterogeneous container in C++03 STL.)
 *
 * The values of associated with each multikey is implied by their positions
 * in the vector.
 */
template <typename T>
class mkey_vector {

	private:

		// The i-th multikey is represented by tuple (_rep[0][i], ..., _rep[d-1][i])
		// where d is the dimension of the multikey
		vector< slice<T> > _rep;

		// number of dimensions of the multikey
		const size_t _d;

		// number of multikeys
		size_t _n;

	public:

		mkey_vector(size_t key_size)
			: _d(key_size) {
			if (key_size == 0) {
				throw invalid_argument("Key dimension must be positive.");
			}
			_rep.reserve(_d);
		}

		// populate the next key dimension
		void add_slice(const slice<T>& x) {
			if (_rep.size() == _d) {
				throw runtime_error("Keys are already fully populated.");
			}

			if (_rep.size() == 0) {
				_n = x.size();
			} else if (x.size() != _n) {
				throw invalid_argument("Number of elements for a new slice must match the previous slice.");
			}

			_rep.push_back(x);
		}

		// number of dimensions of the multikey
		size_t ndim() const {
			return _d;
		}

		const slice<T>& operator[](size_t i) const {
			return _rep[i];
		}

		// number of multikeys
		size_t nkeys() const {
			return _n;
		}
};


} // namespace alg

#endif

