#include <Rcpp.h>
using namespace Rcpp;

#include <cstdint>
#include <vector>
using namespace std;

#include "algorithm/match.hpp"
#include "algorithm/key_value.hpp"
using namespace alg;

//' Determine the row index into row-sorted y for each row of x.
//' 
//' The rows of y must be sorted by considering each row as a mutli-value key,
//' with the most significant key in the first column.
//'
//' @param x  query integer matrix
//' @param y  reference row-sorted integer matrix
//' @return row index into y for each row fo x
template<class Matrix, typename T>
Rcpp::IntegerVector match_slices_(Matrix x, Matrix y) {
	size_t nx = x.nrow();
	size_t d = x.ncol();

	mkey_vector<T> vx(d);
	mkey_vector<T> vy(d);
	vector<size_t> idx(nx);

	vx.reserve(d);
	vy.reserve(d);
	for (size_t j = 0; j < d; ++j) {
		vx.add_slice( slice<T>(x.column(j).begin(), x.column(j).end()) );
		vy.add_slice( slice<T>(y.column(j).begin(), y.column(j).end()) );
	}

	match_mkeys(vx, vy, idx);

	return Rcpp::wrap(idx);
}

// [[Rcpp::export]]
Rcpp::IntegerVector match_slices_int_(Rcpp::IntegerMatrix x, Rcpp::IntegerMatrix y) {
	return match_slices_<Rcpp::IntegerMatrix, int32_t>(x, y);
}

// [[Rcpp::export]]
Rcpp::IntegerVector match_slices_double_(Rcpp::NumericMatrix x, Rcpp::NumericMatrix y) {
	return match_slices_<Rcpp::NumericMatrix, double>(x, y);
}

