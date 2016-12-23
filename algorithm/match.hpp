#ifndef _match_cpp_
#define _match_cpp_

#include "key_vector.hpp"

namespace alg {

/**
 * Find index to slices in y that match each slice of x.
 * y must be sorted
 */
template <typename T>
void match_keys(
	const key_vector<T>& x,
	const key_vector<T>& y,
	vector<size_t>& idx
) {

	// number of dimensions in key
	size_t d = x.ndim();
	
	if (y.ndim() != d) {
		throw invalid_argument("x and y must have the same key dimension.");
	}

	size_t nx = x.nkeys();
	size_t ny = y.nkeys();

	idx.resize(nx);
	
	// iterate through the multi-value elements of x
	for (size_t i = 0; i < nx; ++i) {
		// each component of the multi-value key stricts the feasible range [lower, upper) of ys containing elements that possibly match x
		// if the search completes successfully after the last component, lower points to a possible match
		T t = x[0][i];
		size_t lower = lower_bound(y[0], t);
		size_t upper = upper_bound(y[0], t);
		bool match = TRUE;
		if (y[0][lower] != t) {
			// component of key does not match
			match = FALSE;	
		} else {
			for (size_t j = 1; j < d; ++j) {
				t = x[j][i];
				lower = lower_bound(y[j], t, lower, upper);
				upper = upper_bound(y[j], t, lower, upper);
				if (y[j][lower] != t) {
					// component of key does not match
					match = FALSE;
					break;
				}
			}
		}
	
		if (match) {
			idx[i] = lower;
		} else {
			// indicates no match in y for the i-th multi-value element of x
			idx[i] = ny;
		}
	}
}


} // namespace alg

#endif
