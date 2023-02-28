#include "Walnut/Application.h"
#include "Walnut/EntryPoint.h"

#include "Walnut/Image.h"

#include "imgui_stdlib.h"


#include <fstream>
#include <ranges>

#include "uuid_utils.h"
#include "Deck.h"
#include "stats.h"
#include "filing.h"

class ExampleLayer : public Walnut::Layer
{
public:

	// CALLED EACH FRAME
	virtual void OnUIRender() override
	{
		RenderMainDeck();

		RenderDesiredHandConfig();
		
		RenderLoadFileDialogue();
	}

	void RenderLoadFileDialogue()
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
			
			
		ImGui::InputText("File", &buf);
		if (ImGui::Button("Load"))
		{
			const std::filesystem::path filename(buf);
			last_load_failed = load_deck_from_file(deck, filename);
		}
		if (ImGui::Button("Save"))
		{
			const std::filesystem::path filename(buf);
			last_save_failed = save_deck_to_file(deck, filename, force_overwrite);
		}

		ImGui::End();
	}

	void RenderDesiredHandConfig()
	{
		ImGui::Begin("Desired Hand");
		ImGui::DragInt("Hand Size", &hand_size);
		if (hand_size < deck.desired_min_hand_size())
			ImGui::TextColored(ImVec4(1, 0, 0, 1), "Warning! Hand size makes no sense!");
		ImGui::Text("Cards desired in hand: %d", deck.desired_min_hand_size());
		long double prob = 1;
		uint64_t cards_accounted_for = 0;
		for (const auto& card : deck.cards | std::views::values)
		{
			prob *= n_or_more_matches((uint64_t)card.desired_minimum, deck.card_count() - cards_accounted_for, (uint64_t)hand_size - cards_accounted_for, (uint64_t)card.count);
			cards_accounted_for += (uint64_t)card.desired_minimum;
		}
		ImGui::Text("%f%%", prob * 100);
		ImGui::End();

	}

	void RenderMainDeck() {
		static std::string newCardName;
		static int newCardCount;
		ImGui::Begin("Deck");
		ImGui::Text("New card: ");
		ImGui::InputText("Name", &newCardName);
		ImGui::DragInt("Count", &newCardCount);
		if (ImGui::Button("Add to deck"))
		{
			std::string newName = "";
			newName.append(newCardName);
			Card newCard = Card(newName);
			newCard.count = newCardCount;
			deck[gen_uuid()] = newCard;
			newCardName.clear();
		}

		std::vector<uuids::uuid> to_delete;

		for (auto& [id, card] : deck.cards)
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
			deck.cards.erase(id);
		}
		to_delete.clear();


		ImGui::End();
	}

private:
	Deck deck;
	int hand_size = 7;
	std::string buf;
};

// ENTRY POINT
Walnut::Application* Walnut::CreateApplication(int argc, char** argv)
{
	Walnut::ApplicationSpecification spec;
	spec.Name = "MTG_Deck_Probability_Analyzer";

	Walnut::Application* app = new Walnut::Application(spec);
	app->PushLayer<ExampleLayer>();
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