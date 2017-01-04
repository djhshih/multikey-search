library(Rcpp);

source("util.R");

sourceCpp("order.cpp");

#' Return the column index of the column-sorted matrix
#'
#' @param x matrix
#' @return integer vector
order_cols <- function(x) {
	if (is.integer(x)) {
		order_cols_r(x)
	} else {
		convert_idx(order_slices_double_(x), ncol(x))
	}
}

#' Return the row index of the row-sorted matrix
#'
#' @param x matrix
#' @return integer vector
order_rows <- function(x) {
	if (is.integer(x)) {
		order_rows_r(x)
	} else {
		convert_idx(order_slices_double_(t(x)), nrow(x))
	}
}

#' Return the column index of the column-sorted matrix
#' Wrapper for C++ function, used for benchmarking
order_cols_cpp <- function(x) {
	if (is.integer(x)) {
		idx <- order_slices_int_(x);
	} else {
		idx <- order_slices_double_(x);
	}
	convert_idx(idx, ncol(x))
}

#' Return the row index of the row-sorted matrix
#' Wrapper for C++ function, used for benchmarking
order_rows_cpp <- function(x) {
	if (is.integer(x)) {
		idx <- order_slices_int_(t(x));
	} else {
		idx <- order_slices_double_(t(x));
	}
	convert_idx(idx, nrow(x))
}

#' Return the row index of the row-sorted matrix
#' This will actually work with any matrix, but performance is best
#' with R's native order (using radix sort) for integers
order_rows_r <- function(x) {
	# sort rows: use columns as keys
	m <- ncol(x);
	# construct R expression
	expr <- parse(text = 
		sprintf("order(%s)", paste(paste0("x[,", 1:m, "]"), collapse=", ")));
	eval(expr)
}

#' Return the column index of the col-sorted matrix
#' This will actually work with any matrix, but performance is best
#' with R's native order (using radix sort) for integers
order_cols_r <- function(x) {
	# sort columns: use rows as keys
	n <- nrow(x);
	# construct R expression
	expr <- parse(text = 
		sprintf("order(%s)", paste(paste0("x[", 1:n, ",]"), collapse=", ")));
	eval(expr)
}

