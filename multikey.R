library(Rcpp);

sourceCpp("multikey.cpp");

x <- data.frame(
	chrom = c(4, 3, 2),
	pos = c(1000, 2000, 1000)
);

y <- data.frame(
	chrom = c(1, 2, 3, 4),
	pos = c(1000, 1000, 2000, 2000)
);

truth <- c(NA, 3, 2);

as_integer_matrix <- function(x) {
	if (!is.matrix(x)) {
		x <- as.matrix(x);
	}
	if (length(x) > 1 && class(x[1]) != "integer") {
		x <- matrix(as.integer(x), nrow=nrow(x));
	}
	x
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

	y.order <- order(y[, 1], y[, 2]);
	y.sorted <- y[y.order, ];

	idx <- match_rows(x, y.sorted);

	# convert 0-based to 1-based
	idx <- idx + 1

	# recode missing matches
	idx[idx > nrow(y)] <- NA;

	idx
}

idx <- match_coords(x, y);


test_equal <- function(x, y) {
	all(is.na(x) == is.na(y)) && all(x == y, na.rm=TRUE)
}

stopifnot(test_equal(idx, truth));

cbind(x, y[idx, ])

