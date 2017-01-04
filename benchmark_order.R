library(microbenchmark);

source("order.R");
source("order_copy.R");

ny <- 1e4;

# integers

chroms <- 1:24;
pos <- 1:1e6;

y <- matrix(
	c(
		chrom = sample(chroms, ny, replace=TRUE),
		pos = sample(pos, ny, replace=TRUE)
	),
	ncol = 2
);

yt <- t(y);

microbenchmark(
	order_slices_int_(yt),
	order_rows(y),
	order_cols(yt),
	order_cols_copy_(yt),
	order_cols_copy_boost_(yt),
	order_rows_r(y),
	order(y[,1], y[,2])
);

# C++ std::sort is not a stable sort
# ties in y coudl lead to differences in the indices
mean( order_rows(y) == order(y[,1], y[,2]) )
# but the sorted rows are the same
stopifnot(y[order_rows(y), ] == y[order(y[,1], y[,2]), ])


# floating points

yf <- matrix(rnorm(ny*2), ncol=2);
yft <- t(yf);

microbenchmark(
	order_slices_double_(yft),
	order_rows(yf),
	order_cols(yft),
	order_cols_copy_(yft),
	order_cols_copy_boost_(yft),
	order_rows_r(yf),
	order(yf[,1], yf[,2])
);

stopifnot(yf[order_rows(yf), ] == yf[order(yf[,1], yf[,2]), ])

