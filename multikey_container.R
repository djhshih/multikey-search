library(Rcpp);

sourceCpp("multikey_container.cpp");

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

