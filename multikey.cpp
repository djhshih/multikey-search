#include <Rcpp.h>
using namespace Rcpp;

#include <vector>
using namespace std;

template <typename T>
size_t binary_search(const vector<T>& ys, const T& x) {
    size_t l = 0;
    size_t r = ys.size();
    
    while (l < r) {
        size_t m = l + (r - l) / 2;
        if (ys[m] == x) {
            return m;
        } else if (ys[m] < x) {
            // search right half
            l = m + 1;
        } else {
            // search left half
            r = m;
        }
    }
    
    // element not found
    return ys.size();
}

// return the first index of sorted vector ys that matches x, or if none exists, where x should be inserted
template <typename T>
size_t lower_bound(const vector<T>& ys, const T& x) {
    size_t l = 0;
    size_t r = ys.size();
    
    while (l < r) {
        size_t m = l + (r - l) / 2;
        if (ys[m] < x) {
            // search right half
            l = m + 1;
        } else {
            // search left half
            r = m;
        }
    }
    
    return l;
}

// return one past the last index of sorted vector ys that matches x, or if none exists, where x should be inserted
template <class T>
size_t upper_bound(const vector<T>& ys, const T& x) {
    size_t l = 0;
    size_t r = ys.size();
    
    while (l < r) {
        size_t m = l + (r - l) / 2;
        if (x < ys[m]) {
            // search left half
            r = m;
        } else {
            // search right half
            l = m + 1;
        }
    }

    return l;
}

//' Determine the indices into the reference list for each multi-value element of the query list.
//' Each element in query and reference lists can be multi-valued. The reference list must be sorted.
//' @param x  query list of sorted vectors, in which the i-th element of each vector constitute the i-th multi-value element
//' @param y  sorted reference list of vectors
//' @return indices of y for each multi-value element in x
// [[Rcpp::export]]
IntegerVector match_sorted_lists(List x, List y) {

    // number of keys
    size_t k = x.size();
    
    if (k == 0) {
        stop("List x cannot be empty.");
    }
    
    if (y.size() != k) {
        stop("List x and List y must have the same number of keys.");
    }

    // number of multi-value elements in x
    size_t nx = x[0].size();
    for (size_t i = 1; i < k; ++i) {
        if (nx != x[i].size()) {
            stop("Each vector in List x must be same size");
        }
    }
    
    // number of multi-value elements in y
    size_t ny = y[0].size();
    for (size_t i = 1; i < k; ++i) {
        if (ny != y[i].size()) {
            stop("Each vector in List y must be the same size");
        }
    }
    
    // iterate through the multi-value elements of x
    for (size_t j = 0; j < nx; ++j) {
        size_t i = 0;
        size_t ylb = lower_bound(y[i], x[i][j]);
        size_t yub = upper_bound(y[i], x[i][j]);
        // TODO
    }


    return idx;
}
