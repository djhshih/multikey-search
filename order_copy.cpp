// Make the boost headers available
// [[Rcpp::depends(BH)]]

#include <Rcpp.h>
using namespace Rcpp;

#include <cstdint>
#include <algorithm>  // sort
using namespace std;

#include "algorithm/key_value.hpp"
using namespace alg;

#include <boost/container/vector.hpp>

// [[Rcpp::export]]
Rcpp::IntegerVector order_cols_copy_(Rcpp::IntegerMatrix x) {
	size_t m = x.ncol();

	typedef vector<int32_t> column_t ;
	typedef key_value<column_t, size_t> key_value_t;

	boost::container::vector<key_value_t> x2;
	vector<size_t> idx(m);

	x2.reserve(m);
	for (size_t j = 0; j < m; ++j) {
		// in-place copy construction of a column
		x2.push_back(
			key_value_t(
				column_t(x.column(j).begin(), x.column(j).end()),
				j
			)
		);
	}

	std::sort(x2.begin(), x2.end());

	for (size_t j = 0; j < m; ++j) {
		idx[j] = x2[j].value;
	}

	return Rcpp::wrap(idx);
}


// [[Rcpp::export]]
Rcpp::IntegerVector order_cols_copy_boost_(Rcpp::IntegerMatrix x) {
	size_t m = x.ncol();

	typedef boost::container::vector<int32_t> column_t ;
	typedef key_value<column_t, size_t> key_value_t;

	boost::container::vector<key_value_t> x2;
	vector<size_t> idx(m);

	x2.reserve(m);
	for (size_t j = 0; j < m; ++j) {
		// in-place copy construction of a column
		x2.emplace_back(
			column_t(x.column(j).begin(), x.column(j).end()),
			j
		);
	}

	std::sort(x2.begin(), x2.end());

	for (size_t j = 0; j < m; ++j) {
		idx[j] = x2[j].value;
	}

	return Rcpp::wrap(idx);
}
