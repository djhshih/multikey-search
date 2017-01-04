source("util.R");
source("multikey.R");
source("multikey_container.R");

x <- data.frame(
	chrom = c(4, 3, 2),
	pos = c(1000, 2000, 1000)
);

y <- data.frame(
	chrom = c(1, 2, 3, 4),
	pos = c(1000, 1000, 2000, 2000)
);

truth <- c(NA, 3, 2);

y2 <- y[c(4, 1, 2, 3), ]

truth2 <- c(NA, 4, 3);


idx <- match_coords(x, y);
stopifnot(test_equal(idx, truth));

cbind(x, y[idx, ])

idx2 <- match_coords(x, y2);
stopifnot(test_equal(idx2, truth2));

cbind(x, y2[idx2, ])


idx <- match_coords_hash(x, y);
stopifnot(test_equal(idx, truth));

idx2 <- match_coords_hash(x, y2);
stopifnot(test_equal(idx2, truth2));


idx <- match_coords_tree(x, y);
stopifnot(test_equal(idx, truth));

idx2 <- match_coords_tree(x, y2);
stopifnot(test_equal(idx2, truth2));


idx <- match_coords_svector(x, y);
stopifnot(test_equal(idx, truth));

idx2 <- match_coords_svector(x, y2);
stopifnot(test_equal(idx2, truth2));

