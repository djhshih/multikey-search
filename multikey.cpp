#include <Rcpp.h>

#include <stdexcept>
#include <vector>
//#include <algorithm>
// Ideally, we would use <algorithm>, but the vector iterator must be typed, 
// and the types of the sorted vectors contained in x and y are not known
// at compile time...
// The auto feature of C++11 may circumvent this issue.
using namespace std;

#include "algorithm/vector.hpp"

template <typename T>
void _match_sorted_lists(
	const vector< vector<T> >& x,
	const vector< vector<T> >& y,
	vector<size_t>& idx
) {

	// number of components in the key
	size_t k = x.size();
	
	if (k == 0) {
		throw invalid_argument("List x cannot be empty.");
	}
	
	if (y.size() != k) {
		throw invalid_argument("List x and List y must have the same number of keys.");
	}

	// number of multi-value elements in x
	size_t nx = x[0].size();
	for (size_t i = 1; i < k; ++i) {
		if (nx != x[i].size()) {
			throw invalid_argument("Each vector in List x must be same size.");
		}
	}
	
	// number of multi-value elements in y
	size_t ny = y[0].size();
	for (size_t i = 1; i < k; ++i) {
		if (ny != y[i].size()) {
			throw invalid_argument("Each vector in List y must be the same size.");
		}
	}

	idx.resize(nx);
	
	// iterate through the multi-value elements of x
	for (size_t j = 0; j < nx; ++j) {
		// each component of the multi-value key stricts the feasible range [lower, upper) of ys containing elements that possibly match x
		// if the search completes successfully after the last component, lower points to a possible match
		size_t lower = vec::lower_bound(y[0], x[0][j]);
		size_t upper = vec::upper_bound(y[0], x[0][j]);
		bool match = TRUE;
		if (y[0][lower] != x[0][j]) {
			// component of key does not match
			match = FALSE;	
		} else {
			for (size_t i = 1; i < k; ++i) {
				lower = vec::lower_bound(y[i], x[i][j], lower, upper);
				upper = vec::upper_bound(y[i], x[i][j], lower, upper);
				if (y[i][lower] != x[i][j]) {
					// component of key does not match
					match = FALSE;
					break;
				}
			}
		}
	
		if (match) {
			idx[j] = lower;
		} else {
			// indicates no match in y for the j-th multi-value element of x
			idx[j] = ny;
		}
	}
}


//' Determine the indices into the reference list for each multi-value element of the query list.
//' Each element in query and reference lists can be multi-valued. The reference list must be sorted.
//' @param x  query list of sorted vectors, in which the i-th element of each vector constitute the i-th multi-value element
//' @param y  sorted reference list of vectors
//' @return indices of y for each multi-value element in x
// [[Rcpp::export]]
Rcpp::IntegerVector match_sorted_coords(Rcpp::List x, Rcpp::List y, size_t k) {

	vector< vector<long> > vx(k);
	vector< vector<long> > vy(k);
	vector<size_t> idx;
	
	for (size_t i = 0; i < k; ++i) {
		vx[i] = Rcpp::as< vector<long> >(x[i]);
		vy[i] = Rcpp::as< vector<long> >(y[i]);
	}

	_match_sorted_lists(vx, vy, idx);

	return Rcpp::wrap(idx);
}

