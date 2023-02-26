#pragma once

#include "uuid.h"
#include <random>
#include <array>

static bool statics_initialized = false;

static std::random_device rd;
static std::array<int, std::mt19937::state_size> seed_data = std::array<int, std::mt19937::state_size> {};
static std::seed_seq seq(std::begin(seed_data), std::end(seed_data));
static std::mt19937 generator = std::mt19937(seq);
static uuids::uuid_random_generator gen(generator);



inline uuids::uuid gen_uuid() {
	if (!statics_initialized) {
		statics_initialized = true;
		std::generate(std::begin(seed_data), std::end(seed_data), std::ref(rd));
	}
	return gen();
}