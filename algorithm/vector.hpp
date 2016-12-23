/**
 * Algorithms for vectors
 */

#include <vector>
 
namespace vec {

    using namespace std;
    
    template <typename T>
    size_t binary_search(const vector<T>& ys, const T& x, size_t l, size_t r) {
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

    // Returns an index of sorted vector ys that matches x, or if none exists, ys.size().
    template <typename T>
    size_t binary_search(const vector<T>& ys, const T& x) {
        return binary_search(ys, x, 0, ys.size());
    }

    template <typename T>
    size_t lower_bound(const vector<T>& ys, const T& x, size_t l, size_t r) {
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

    // Returns the first index of sorted vector ys that matches x, or if none exists, where x should be inserted.
    template <typename T>
    size_t lower_bound(const vector<T>& ys, const T& x) {
        return lower_bound(ys, x, 0, ys.size());
    }

    template <class T>
    size_t upper_bound(const vector<T>& ys, const T& x, size_t l, size_t r) {
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

    // Returns one past the last index of sorted vector ys that matches x, or if none exists, where x should be inserted.
    template <class T>
    size_t upper_bound(const vector<T>& ys, const T& x) {
        return upper_bound(ys, x, 0, ys.size());
    }

    template <class T>
    void equal_range(const vector<T>& ys, const T& x, size_t& lower, size_t& upper, size_t l, size_t r) {
        lower = lower_bound(ys, x, l, r);
        upper = upper_bound(ys, x, l, r);
		}

    // Returns the bounds of the range [lower, upper) of sorted vector ys with values equivalent to x.
    template <class T>
    void equal_range(const vector<T>& ys, const T& x, size_t& lower, size_t& upper) {
        return equal_range(ys, x, lower, upper, 0, ys.size());
    }
    
}
