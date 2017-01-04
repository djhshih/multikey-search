source("util.R");
source("order.R");
source("order_copy.R");

n <- 5;
m <- 4;
z <- matrix(sample(1:n, replace=TRUE, n*m), n, m);

idx3 <- order_cols(z);
truth3 <- order(z[1, ], z[2, ], z[3, ], z[4, ], z[5, ]);
stopifnot(test_equal(idx3, truth3));
stopifnot(test_equal(order_cols_r(z), truth3));
stopifnot(test_equal(convert_idx(order_cols_copy_(z), m), truth3));
stopifnot(test_equal(convert_idx(order_cols_copy_boost_(z), m), truth3));

z[, idx3];


idx4 <- order_rows(z);
truth4 <- order(z[, 1], z[, 2], z[, 3], z[, 4])
stopifnot(test_equal(idx4, truth4));
stopifnot(test_equal(order_rows_r(z), truth4));

z[idx4, ];
