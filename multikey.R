library(Rcpp);

sourceCpp("multikey.cpp");

x <- data.frame(
	chrom = c(4, 3, 2),
	pos = c(100, 200, 100)
);

y <- data.frame(
	chrom = c(1, 2, 3, 4),
	pos = c(100, 100, 200, 200)
);


#' @param x  data.frame
#' @param y  data.frame
match_coords <- function(x, y) {

	if (is.data.frame(x)) {
		x <- as.list(x);
	}

	if (is.data.frame(y)) {
		y <- as.list(y);
	}

	k <- length(x);

	if (length(y) != k) {
		stop("lists x and y must have the same size");
	}

	y <- y[order(y[[1]], y[[2]])];

	idx <- match_sorted_coords(x, y, k);

	# convert 0-based to 1-based
	idx <- idx + 1

	# recode missing matches
	idx[idx > length(y[[1]])] <- NA;

	idx
}

idx <- match_coords(x, y);

cbind(x, y[idx, ])

