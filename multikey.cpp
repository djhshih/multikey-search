#include <Rcpp.h>

#include <cstdint>
#include <stdexcept>
#include <vector>
#include <algorithm>  // sort
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

	mkey_vector<int32_t> vx(d);
	mkey_vector<int32_t> vy(d);
	vector<size_t> idx(nx);

	for (size_t j = 0; j < d; ++j) {
		vx.add_slice( slice<int32_t>(x.column(j).begin(), x.column(j).end()) );
		vy.add_slice( slice<int32_t>(y.column(j).begin(), y.column(j).end()) );
	}

	match_mkeys(vx, vy, idx);

	return Rcpp::wrap(idx);
}

// [[Rcpp::export]]
Rcpp::IntegerVector order_cols_(Rcpp::IntegerMatrix x) {

	size_t m = x.ncol();

	vector< slice<int32_t> > x2;
	vector<size_t> idx(m);
	slice_less<int32_t> less;

	for (size_t j = 0; j < m; ++j) {
		x2.push_back( slice<int32_t>(x.column(j).begin(), x.column(j).end(), j));
	}

	std::sort(x2.begin(), x2.end(), less);

	for (size_t j = 0; j < m; ++j) {
		idx[j] = x2[j].index();
	}

	return Rcpp::wrap(idx);
}

