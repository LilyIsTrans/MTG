#pragma once

#include <cstdint>
#include <vector>


constexpr long double factorial(const uint64_t n)
{
	if (!(n > 0 && n < 4000))
	{
		return 1.0;
	}
	long double acc = 1;
	for (uint64_t i = 1; i <= n; ++i)
		acc *= i;
	return acc;
}

constexpr long double combinations(const uint64_t n, const uint64_t r) {
	return factorial(n) / (factorial(n - r) * factorial(r));
}

constexpr long double hypergeometric_probability(const uint64_t matches_drawn, const uint64_t total_cards, const uint64_t cards_drawn, const uint64_t total_matches)
{

	uint64_t total_non_matches = total_cards - total_matches; // (N-k)
	uint64_t non_matches_drawn = cards_drawn - matches_drawn; // (n-x)

	long double numerator = 1;
	long double denominator = 1;
	numerator = combinations(total_matches, matches_drawn) * combinations(total_non_matches, non_matches_drawn);
	denominator = combinations(total_cards, cards_drawn);
	return numerator / denominator;

}


constexpr long double n_or_more_matches(const uint64_t minimum_matches_drawn, const uint64_t total_cards, const uint64_t cards_drawn, const uint64_t total_matches) {
	long double acc = 0;
	for (uint64_t matches = minimum_matches_drawn; matches <= total_matches && matches <= cards_drawn; ++matches)
		acc += hypergeometric_probability(matches, total_cards, cards_drawn, total_matches);
	return acc;
}

