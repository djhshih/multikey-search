library(Rcpp);

sourceCpp("multikey.cpp");

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

	# get row index of row-sorted y matrix
	y.order <- order(y[, 1], y[, 2]);

	# find row index of row-sorted y for each row of x
	idx <- match_slices_(x, y[y.order, ]);

	idx <- convert_idx(idx, nrow(y));

	# return row index for the unsorted y
	y.order[idx]
}

