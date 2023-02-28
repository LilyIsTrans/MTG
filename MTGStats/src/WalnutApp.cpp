#include "Walnut/Application.h"
#include <Walnut/EntryPoint.h>

#include "Walnut/Image.h"

#include "imgui_stdlib.h"


#include <fstream>
#include <ranges>

#include "uuid_utils.h"
#include "Deck.h"
#include "stats.h"
#include "filing.h"

class application : public Walnut::Layer
{
public:

	// CALLED EACH FRAME
	void OnUIRender() override
	{
		render_main_deck();

		render_desired_hand_config();
		
		render_load_file_dialogue();
	}

	void render_load_file_dialogue()
	{
		static int last_load_failed;
		static int last_save_failed;
		static bool force_overwrite;
		ImGui::Begin("Load");
		if (last_load_failed)
			ImGui::TextColored(ImVec4(1, 0, 0, 1), "File not found!");
		if (last_save_failed == -1)
			ImGui::TextColored(ImVec4(1, 0, 0, 1), "Error occurred while saving!");
		if (last_save_failed == 1)
		{
			ImGui::TextColored(ImVec4(1, 0, 0, 1), "File already exists. Are you sure you want to overwrite?");
			ImGui::Checkbox("Confirm Overwrite", &force_overwrite);
		}
		else
		{
			force_overwrite = false;
		}
			
			
		ImGui::InputText("File", &m_buf);
		if (ImGui::Button("Load"))
		{
			const std::filesystem::path filename(m_buf);
			last_load_failed = load_deck_from_file(m_deck, filename);
		}
		if (ImGui::Button("Save"))
		{
			const std::filesystem::path filename(m_buf);
			last_save_failed = save_deck_to_file(m_deck, filename, force_overwrite);
		}

		ImGui::End();
	}

	void render_desired_hand_config()
	{
		ImGui::Begin("Desired Hand");
		ImGui::DragInt("Hand Size", &m_handSize);
		if (m_handSize < m_deck.desired_min_hand_size())
			ImGui::TextColored(ImVec4(1, 0, 0, 1), "Warning! Hand size makes no sense!");
		ImGui::Text("Cards desired in hand: %d", m_deck.desired_min_hand_size());
		long double prob = 1;
		uint64_t cards_accounted_for = 0;
		for (const auto& card : m_deck.cards | std::views::values)
		{
			prob *= n_or_more_matches(static_cast<uint64_t>(card.desired_minimum),
			                          m_deck.card_count() - cards_accounted_for,
			                          static_cast<uint64_t>(m_handSize) - cards_accounted_for,
			                          static_cast<uint64_t>(card.count));
			cards_accounted_for += static_cast<uint64_t>(card.desired_minimum);
		}
		ImGui::Text("%Lf%%", prob * 100);
		ImGui::End();

	}

	void render_main_deck() {
		static std::string new_card_name;
		static int new_card_count;
		ImGui::Begin("Deck");
		ImGui::Text("New card: ");
		ImGui::InputText("Name", &new_card_name);
		ImGui::DragInt("Count", &new_card_count);
		if (ImGui::Button("Add to deck"))
		{
			std::string new_name;
			new_name.append(new_card_name);
			card new_card = card(new_name);
			new_card.count = new_card_count;
			m_deck[gen_uuid()] = new_card;
			new_card_name.clear();
		}

		std::vector<uuids::uuid> to_delete;

		for (auto& [id, card] : m_deck.cards)
		{
			ImGui::PushID(int_from_id(id));
			ImGui::Separator();
			ImGui::Text(card.name.c_str());
			ImGui::DragInt("Count", &card.count);
			ImGui::DragInt("Desired minimum in initial hand", &card.desired_minimum);
			if (ImGui::Button("Remove"))
				to_delete.push_back(id);
			ImGui::PopID();
		}

		for (auto& id : to_delete)
		{
			m_deck.cards.erase(id);
		}
		to_delete.clear();


		ImGui::End();
	}

private:
	deck m_deck;
	int m_handSize = 7;
	std::string m_buf;
};

// ENTRY POINT
Walnut::Application* Walnut::CreateApplication(int argc, char** argv)
{
	Walnut::ApplicationSpecification spec;
	spec.Name = "MTG_Deck_Probability_Analyzer";

	auto app = new Walnut::Application(spec);
	app->PushLayer<application>();
	app->SetMenubarCallback([app]()
	{
		if (ImGui::BeginMenu("File"))
		{
			if (ImGui::MenuItem("Exit"))
			{
				app->Close();
			}
			ImGui::EndMenu();
		}
	});
	return app;
}