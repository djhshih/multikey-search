library(Rcpp);

sourceCpp("multikey.cpp");

test_equal <- function(x, y) {
	all(is.na(x) == is.na(y)) && all(x == y, na.rm=TRUE)
}

#' Convert to integer matrix
#'
#' @param x  data.frame or matrix
#' @return integer matrix
#' @export
as_integer_matrix <- function(x) {
	if (!is.matrix(x)) {
		x <- as.matrix(x);
	}
	if (length(x) > 1 && class(x[1]) != "integer") {
		x <- matrix(as.integer(x), nrow=nrow(x));
	}
	x
}

# Convert from C++ index to R index
# @param idx  0-based index
# @param n    max index value (e.g. vector size)
convert_idx <- function(idx, n) {
	# convert 0-based to 1-based
	idx <- idx + 1

	# recode missing matches
	idx[idx > n] <- NA;

	idx
}

#' Return the column index of the column-sorted matrix
#'
#' @param x integer matrix
#' @return integer vector
order_cols <- function(x) {
	idx <- order_cols_(x);
	convert_idx(idx, ncol(x))
}

#' Return the row index of the row-sorted matrix
#'
#' @param x integer matrix
#' @return integer vector
order_rows <- function(x) {
	idx <- order_cols_(t(x));
	convert_idx(idx, nrow(x))
}

#' Match coordinates.
#'
#' @param x  integer matrix
#' @param y  integer matrix
#' @return row index into y for each row of x
#' @export
match_coords <- function(x, y) {
	x <- as_integer_matrix(x);
	y <- as_integer_matrix(y);

	# number of coordinate dimensions
	d <- ncol(x);

	if (ncol(y) != d) {
		stop("x and y must have the same coordinate dimensions");
	}

	y.order <- order_rows(y);

	# find row index of row-sorted y for each row of x
	idx <- match_rows(x, y[y.order, ]);

	idx <- convert_idx(idx, nrow(y));

	# return row index for the unsorted y
	y.order[idx]
}


sourceCpp("container.cpp");

match_coords_hash <- function(x, y) {
	idx <- match_coords_hash_(x$chrom, x$pos, y$chrom, y$pos);
	convert_idx(idx, nrow(y))
}

match_coords_tree <- function(x, y) {
	idx <- match_coords_tree_(x$chrom, x$pos, y$chrom, y$pos);
	convert_idx(idx, nrow(y))
}

match_coords_svector <- function(x, y) {
	idx <- match_coords_svector_(x$chrom, x$pos, y$chrom, y$pos);
	convert_idx(idx, nrow(y))
}

