#pragma once
#include "Deck.h"
#include <string>
#include <filesystem>

/**
 * \brief Handles loading a deck from a file
 *
 * Modifies deck in place, adding all of the cards described in the given text file to the deck (does not remove cards which were already present)
 * Uses a custom file format where each entry is
 * \param deck The deck to be modified
 * \param filename A full or relative path to the text file containing the information on the deck
 * \return 0 if success, -1 otherwise
 */
[[nodiscard]] int load_deck_from_file(deck& deck, const std::filesystem::path& filename);

/**
 * \brief Handles saving a deck to a file
 * \param deck The deck to be saved. Will not be modified
 * \param filename The path to save the data to
 * \param overwrite Whether to overwrite the file if it exists and is not empty.
 * In conjunction with the 1 return value, can be used to ask user for confirmation before overwriting file.
 * \return 0 if success, 1 if file exists, is not empty, and overwrite was false, -1 otherwise
 */
[[nodiscard]] int save_deck_to_file(deck& deck, const std::filesystem::path& filename, bool overwrite);