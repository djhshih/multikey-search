library(Rcpp);

source("order.R");

sourceCpp("multikey.cpp");

#' Match coordinates.
#'
#' Recommended columns: chr_index, pos
#'
#' @param x  integer matrix
#' @param y  integer matrix
#' @return row index into y for each row of x
#' @export
match_coords <- function(x, y) {
	match_rows(as_integer_matrix(x), as_integer_matrix(y))
}

#' Match single nucleotide variants (SNVs).
#'
#' Recommended fields: chr_index, pos, [ref], alt
#'
#' @param x  SNV data.frame
#' @param y  SNV data.frame
#' @return row index into y for each row of x
#' @export
match_snvs <- function(x, y, alleles=c("A", "C", "G", "T")) {
	stopifnot(is.data.frame(x));
	stopifnot(is.data.frame(y));

	d <- ncol(x);

	if (ncol(y) != d) {
		stop("x and y must have the same number of columns");
	}

	# convert character columns to factors, then to integers
	for (j in 1:d) {
		v <- x[,j];
		x[,j] <- if (is.character(v) || is.factor(v))
			as.integer(factor(v, alleles)) else as.integer(v);

		# do the same for y
		w <- y[,j];
		y[,j] <- if (is.character(w) || is.factor(w))
			as.integer(factor(w, alleles)) else as.integer(w);
	}

	match_rows(as.matrix(x), as.matrix(y))
}

#' Match rows.
#'
#' @param x  matrix
#' @param y  matrix
#' @return row index into y for each row of x
#' @export
match_rows <- function(x, y) {
	# number of key dimensions
	d <- ncol(x);

	if (ncol(y) != d) {
		stop("x and y must have the same number of columns");
	}

	if (is.integer(x) && is.integer(y)) {
		# get row index of row-sorted y matrix
		y.order <- order_rows_r(y);
		# find row index of row-sorted y for each row of x
		idx <- match_slices_int_(x, y[y.order, ]);
	} else {
		# get row index of row-sorted y matrix
		y.order <- order_rows(y);
		# find row index of row-sorted y for each row of x
		idx <- match_slices_double_(x, y[y.order, ]);
	}

	idx <- convert_idx(idx, nrow(y));

	# return row index for the unsorted y
	y.order[idx]
}

