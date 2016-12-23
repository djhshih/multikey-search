#include <Rcpp.h>

#include <vector>
//#include <algorithm>
// Ideally, we would use <algorithm>, but the vector iterator must be typed, 
// and the types of the sorted vectors contained in x and y are not known
// at compile time...
// The auto feature of C++11 may circumvent this issue.
using namespace std;

#include "algorithm/vector.hpp"

// Rcpp::List is a heterogeneous container. As far as I know, there is no equivalent type in C++.

//' Determine the indices into the reference list for each multi-value element of the query list.
//' Each element in query and reference lists can be multi-valued. The reference list must be sorted.
//' @param x  query list of sorted vectors, in which the i-th element of each vector constitute the i-th multi-value element
//' @param y  sorted reference list of vectors
//' @return indices of y for each multi-value element in x
// [[Rcpp::export]]
Rcpp::IntegerVector match_sorted_lists(Rcpp::List x, Rcpp::List y) {

	// number of components in the key
	size_t k = x.size();
	
	if (k == 0) {
		Rcpp::stop("List x cannot be empty.");
	}
	
	if (y.size() != k) {
		Rcpp::stop("List x and List y must have the same number of keys.");
	}

	// number of multi-value elements in x
	size_t nx = x[0].size();
	for (size_t i = 1; i < k; ++i) {
		if (nx != x[i].size()) {
			Rcpp::stop("Each vector in List x must be same size.");
		}
	}
	
	// number of multi-value elements in y
	size_t ny = y[0].size();
	for (size_t i = 1; i < k; ++i) {
		if (ny != y[i].size()) {
			Rcpp::stop("Each vector in List y must be the same size.");
		}
	}
	
	Rcpp::IntegerVector idx(nx);
	
	// iterate through the multi-value elements of x
	for (size_t j = 0; j < nx; ++j) {
		// each component of the multi-value key stricts the feasible range [lower, upper) of ys containing elements that possibly match x
		// if the search completes successfully after the last component, lower points to a possible match
		size_t lower = lower_bound(y[0], x[0][j]);
		size_t upper = upper_bound(y[0], x[0][j]);
		bool match = TRUE;
		if (y[i][lower] != x[i][j]) {
			// component of key does not match
			match = FALSE;	
		} else {
			for (size_t i = 1; i < k; ++i) {
				lower = lower_bound(y[i], x[i][j], lower, upper)
				upper = upper_bound(y[i], x[i][j], lower, upper)
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

	return idx;
}
