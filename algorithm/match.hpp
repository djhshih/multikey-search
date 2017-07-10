#ifndef _match_cpp_
#define _match_cpp_

#include "mkey_vector.hpp"

namespace alg {

/**
 * Find index to multikeys in y that match each multikey of x.
 *
 * @param x    query multikey vector
 * @param y    sorted reference multikey vector
 * @param idx  output vector of index values
 */
template <typename T>
void match_mkeys(
	const mkey_vector<T>& x,
	const mkey_vector<T>& y,
	vector<size_t>& idx
) {

	// number of dimensions of the multikey
	size_t d = x.ndim();
	
	if (y.ndim() != d) {
		throw invalid_argument("x and y must have the same key dimension.");
	}

	size_t nx = x.nkeys();
	size_t ny = y.nkeys();

	idx.resize(nx);
	
	// iterate through the multikeys of x
	for (size_t i = 0; i < nx; ++i) {
		// each component of the multikey stricts the feasible range [lower,
		// upper) of ys containing elements that possibly match x if the search
		// completes successfully after the last component, lower points to a
		// possible match
		T t = x[0][i];
		size_t lower = lower_bound(y[0], t);
		bool match = TRUE;
		if (lower == ny || y[0][lower] != t) {
			// component of multikey does not match
			match = FALSE;	
		} else {
			size_t upper = upper_bound(y[0], t);
			for (size_t j = 1; j < d; ++j) {
				t = x[j][i];
				lower = lower_bound(y[j], t, lower, upper);
				if (lower == upper || y[j][lower] != t) {
					// component of multikey does not match
					match = FALSE;
					break;
				}
				upper = upper_bound(y[j], t, lower, upper);
			}
		}
	
		if (match) {
			idx[i] = lower;
		} else {
			// indicates no match in y for the i-th multikey of x
			idx[i] = ny;
		}
	}
}


} // namespace alg

#endif
