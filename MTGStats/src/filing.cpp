#include "filing.h"

#include <filesystem>
#include <string>
#include <format>
#include "Deck.h"
#include <fstream>
#include <ranges>
#include <vector>
#include "uuid_utils.h"


[[nodiscard]] int load_deck_from_file(Deck& deck, const std::filesystem::path& filename)
{
	std::vector<std::string> objects;
	try
	{
		std::ifstream file(filename);
		
		while (!file.eof())
		{
			std::stringbuf buf;
			file.ignore(std::numeric_limits<std::streamsize>::max(), '{');
			file.get(buf, '}');
			if (file.good())
				objects.emplace_back(buf.view());
			
		}
	}
	catch (...)
	{
		return -1;
	}
	for (std::string& ob: objects)
	{
		const std::string nums = "0123456789";
		const size_t begin_count = ob.find_first_of(nums, ob.find("count:"));
		const size_t end_count = ob.find_first_not_of(nums, begin_count);
		const size_t begin_desired_min = ob.find_first_of(nums, ob.find("desired_minimum:"));
		const size_t end_desired_min = ob.find_first_not_of(nums, begin_desired_min);
		const size_t begin_name = ob.find('"', ob.find("name:")) + 1;
		const size_t end_name = ob.find('"', begin_name);
		deck.cards.try_emplace(gen_uuid(),
				std::string(ob.substr(begin_name, end_name - begin_name)),
				std::stoi(ob.substr(begin_count, end_count - begin_count)),
				std::stoi(ob.substr(begin_desired_min, end_desired_min - begin_desired_min))
			);
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

	
	for (const auto& card : deck | std::views::values)
	{
		file << std::format(json_template, card.name, card.count, card.desired_minimum);
	}



	return 0;
}
