#include <Rcpp.h>
using namespace Rcpp;

#include <cstdint>
#include <vector>
#include <algorithm>  // sort
using namespace std;

#include "algorithm/slice.hpp"
using namespace alg;

template<class Matrix, typename T> 
Rcpp::IntegerVector order_slices_(Matrix x) {
	size_t m = x.ncol();

	vector< slice<T> > x2;
	vector<size_t> idx(m);

	x2.reserve(m);
	for (size_t j = 0; j < m; ++j) {
		// slice only copies the iterators
		x2.push_back( slice<T>(x.column(j).begin(), x.column(j).end(), j));
	}

	std::sort(x2.begin(), x2.end());

	for (size_t j = 0; j < m; ++j) {
		idx[j] = x2[j].index();
	}

	return Rcpp::wrap(idx);
}

// [[Rcpp::export]]
Rcpp::IntegerVector order_slices_int_(Rcpp::IntegerMatrix x) {
	return order_slices_<Rcpp::IntegerMatrix, int32_t>(x);
}

// [[Rcpp::export]]
Rcpp::IntegerVector order_slices_double_(Rcpp::NumericMatrix x) {
	return order_slices_<Rcpp::NumericMatrix, double>(x);
}

