#pragma once

#include "uuid.h"
#include <random>
#include <array>

// Basically just a Schwarz Counter, but boolean.
static bool statics_initialized = false;

// The global state for the RNG part of UUID generation. This is basically copied straight from the docs of the uuid library https://github.com/mariusbancila/stduuid#:~:text=Creating%20a%20new%20UUID%20with%20a%20default%20random%20generator
static std::random_device rd;
static std::array<int, std::mt19937::state_size> seed_data = std::array<int, std::mt19937::state_size> {};
static std::seed_seq seq(std::begin(seed_data), std::end(seed_data));
static std::mt19937 generator = std::mt19937(seq);
static uuids::uuid_random_generator gen(generator);


/**
 * \brief Generates a new UUID, initializing the global UUID generator state automatically if needed.
 * \return A new, unique UUID
 */
inline uuids::uuid gen_uuid() {
	if (!statics_initialized) {
		statics_initialized = true;
		std::ranges::generate(seed_data, std::ref(rd));
	}
	return gen();
}