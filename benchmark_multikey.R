library(microbenchmark);

source("util.R");
source("multikey.R");
source("multikey_container.R");

ny <- 1e5;
nx <- 1e3;

chroms <- 1:24;
pos <- 1:1e6;

y <- data.frame(
	chrom = sample(chroms, ny, replace=TRUE),
	pos = sample(pos, ny, replace=TRUE)
);

x <- y[sample(1:nrow(y), nx), ]; 

idx.mkey <- match_coords(x, y);
idx.hash <- match_coords_hash(x, y);
idx.tree <- match_coords_tree(x, y);
#idx.svector <- match_coords_svector(x, y);

stopifnot(idx.mkey == idx.hash);
stopifnot(idx.mkey == idx.tree);
#stopifnot(idx.mkey == idx.svector);

results <- microbenchmark(
	match_coords(x, y),
	match_coords_hash(x, y),
	match_coords_tree(x, y)
	#match_coords_svector(x, y)
);

print(results)

# Unit: milliseconds
#                        expr         min         lq       mean     median         uq        max neval
#          match_coords(x, y)    8.692748   10.64148   13.83016   11.97486   14.18956   59.62452   100
#     match_coords_hash(x, y)   28.510132   30.72065   38.09534   37.17696   42.62232   70.11460   100
#     match_coords_tree(x, y)   56.197424   60.30497   68.96369   65.83952   74.94407   95.02558   100
#  match_coords_svector(x, y) 2729.448785 2789.34322 2947.56992 2930.02049 3019.74339 3697.78952   100

