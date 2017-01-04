// Make the boost headers available
// [[Rcpp::depends(BH)]]

#include <Rcpp.h>
using namespace Rcpp;

#include <cstdint>
using namespace std;

#include <boost/unordered_map.hpp>  // hash table
#include <boost/container/map.hpp>  // red-black tree
#include <boost/container/flat_map.hpp>  // sorted vector

struct coord {
	uint8_t chrom;
	uint32_t pos;
	
	coord(uint8_t c, uint32_t p)
		: chrom(c), pos(p) {}
};

// required by boost::unordered_map
bool operator==(const coord& p, const coord& q) {
	return p.chrom == q.chrom && p.pos == q.pos;
}

// required by boost::map and boost::flat_map
bool operator<(const coord& p, const coord& q) {
	if (p.chrom < q.chrom) return true;
	if (p.chrom > q.chrom) return false;
	// otherwise chroms are equal: proceed to compare pos

	if (p.pos < q.pos) return true;
	if (p.pos > p.pos) return false;
	// otherwise both are equal

	return false;
}

size_t hash_value(const coord &p) {
	size_t seed = 0;
	boost::hash_combine(seed, p.chrom);
	boost::hash_combine(seed, p.pos);
	return seed;
}

struct snv : public coord {
	char alt;

	snv(uint8_t c, uint32_t p, char a)
		: coord(c, p), alt(a) {}
};

bool operator==(const snv& p, const snv& q) {
	return p.chrom == q.chrom && p.pos == q.pos && p.alt == q.alt;
}

size_t hash_value(const snv &p) {
	size_t seed = 0;
	boost::hash_combine(seed, p.chrom);
	boost::hash_combine(seed, p.pos);
	boost::hash_combine(seed, p.alt);
	return seed;
}

template <class map>
IntegerVector match_coords_(
	IntegerVector chrom_x,
	IntegerVector pos_x,
	IntegerVector chrom_y,
	IntegerVector pos_y
) {
	size_t nx = chrom_x.size();
	size_t ny = chrom_y.size();

	vector<size_t> idx(nx);

	// create reference map from y
	
	map ref;
	for (size_t i = 0; i < ny; ++i) {
		ref.emplace(coord(chrom_y[i], pos_y[i]), i);
	}

	// query each element of x

	for (size_t i = 0; i < nx; ++i) {
		typename map::iterator it = ref.find(coord(chrom_x[i], pos_x[i]));
		if (it != ref.end()) {
			idx[i] = it->second;
		} else {
			// element is not found
			idx[i] = ny;
		}
	}

	return wrap(idx);
}

// [[Rcpp::export]]
IntegerVector match_coords_hash_(
	IntegerVector chrom_x,
	IntegerVector pos_x,
	IntegerVector chrom_y,
	IntegerVector pos_y
) {
	typedef boost::unordered_map<coord, size_t> map;
	return match_coords_<map>(chrom_x, pos_x, chrom_y, pos_y);
}

// [[Rcpp::export]]
IntegerVector match_coords_tree_(
	IntegerVector chrom_x,
	IntegerVector pos_x,
	IntegerVector chrom_y,
	IntegerVector pos_y
) {
	typedef boost::container::map<coord, size_t> map;
	return match_coords_<map>(chrom_x, pos_x, chrom_y, pos_y);
}

// [[Rcpp::export]]
IntegerVector match_coords_svector_(
	IntegerVector chrom_x,
	IntegerVector pos_x,
	IntegerVector chrom_y,
	IntegerVector pos_y
) {
	typedef boost::container::flat_map<coord, size_t> map;
	return match_coords_<map>(chrom_x, pos_x, chrom_y, pos_y);
}

