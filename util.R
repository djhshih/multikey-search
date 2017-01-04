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
