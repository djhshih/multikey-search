#include <Rcpp.h>

#include <cstdint>
#include <stdexcept>
#include <vector>
//#include <algorithm>
// Ideally, we would use <algorithm>, but the vector iterator must be typed, 
// and the types of the sorted vectors contained in x and y are not known
// at compile time...
// The auto feature of C++11 may circumvent this issue.
using namespace std;

#include "algorithm/match.hpp"
using namespace alg;

//' Determine the row index into row-sorted y for each row of x.
//' 
//' The rows of y must be sorted by considering each row as a mutli-value key,
//' with the most significant key in the first column.
//'
//' @param x  query integer matrix
//' @param y  reference row-sorted integer matrix
//' @return row index into y for each row fo x
// [[Rcpp::export]]
Rcpp::IntegerVector match_rows(Rcpp::IntegerMatrix x, Rcpp::IntegerMatrix y) {

	size_t nx = x.nrow();
	size_t d = x.ncol();

	key_vector<int32_t> vx(d);
	key_vector<int32_t> vy(d);
	vector<size_t> idx(nx);

	for (size_t j = 0; j < d; ++j) {
		vx.add_slice( slice<int32_t>(x.column(j).begin(), x.column(j).end()) );
		vy.add_slice( slice<int32_t>(y.column(j).begin(), y.column(j).end()) );
	}

	match_keys(vx, vy, idx);

	return Rcpp::wrap(idx);
}

