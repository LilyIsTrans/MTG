#include "filing.h"

#include <filesystem>
#include <string>
#include <format>
#include "Deck.h"
#include <fstream>
#include "uuid_utils.h"


[[nodiscard]] int load_deck_from_file(Deck& deck, const std::filesystem::path& filename)
{
	if (std::filesystem::status(filename).type() != std::filesystem::file_type::regular)
	{
		return -1;
	}
	std::ifstream file(filename);
	while (file.good())
	{
		std::stringbuf buffer;
		Card card;
		file.ignore(std::numeric_limits<std::streamsize>::max(), '"');
		file.get(buffer, '"');
		card.name = buffer.str();
		buffer = std::stringbuf();
		file.ignore(std::numeric_limits<std::streamsize>::max(), ':');
		file.get(buffer, '\n');
		card.count = std::stoi(buffer.str());
		buffer = std::stringbuf();
		file.ignore(std::numeric_limits<std::streamsize>::max(), ':');
		file.get(buffer, '\n');
		card.desired_minimum = std::stoi(buffer.str());
		buffer = std::stringbuf();
		deck[gen_uuid()] = card;
		file.ignore(std::numeric_limits<std::streamsize>::max(), '{');
	}
	return 0;
}


[[nodiscard]] int save_deck_to_file(Deck& deck, const std::filesystem::path& filename, bool overwrite)
{
	switch (std::filesystem::status(filename).type())
	{
	case std::filesystem::file_type::regular:
		{
		if (std::filesystem::file_size(filename) == 0)
		{
			break;
		}
		else
		{
			return 1;
		}
		};
	case std::filesystem::file_type::not_found: break;
	default: return -1;
	}

	const std::format_string<const std::string&, const int&, const int&> json_template = "{{\n\tname: \"{}\"\n\tcount: {}\n\tdesired_minimum: {}\n}}\n";


	std::ofstream file(filename);

	
	for (const auto& [id, card] : deck)
	{
		file << std::format(json_template, card.name, card.count, card.desired_minimum);
	}



	return 0;
}
