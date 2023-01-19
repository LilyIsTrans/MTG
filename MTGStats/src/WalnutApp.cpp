#include "Walnut/Application.h"
#include "Walnut/EntryPoint.h"

#include "Walnut/Image.h"

#include <iostream>
#include <fstream>
#include "MTG_UUID.h"
#include "Deck.h"

#include "stats.h"

class ExampleLayer : public Walnut::Layer
{
public:
	// CALLED EACH FRAME
	virtual void OnUIRender() override
	{
		RenderMainDeck();

		RenderDesiredHandConfig();
		

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
		for (auto [id, card] : deck.cards)
		{
			prob *= n_or_more_matches((uint64_t)card.desired_minimum, deck.card_count() - cards_accounted_for, (uint64_t)hand_size - cards_accounted_for, (uint64_t)card.count);
			cards_accounted_for += (uint64_t)card.desired_minimum;
		}
		ImGui::Text("%f%%", prob * 100);
		ImGui::End();

	}

	void RenderMainDeck() {
		ImGui::Begin("Deck");
		ImGui::Text("New card: ");
		ImGui::InputText("Name", deck.newCardName, sizeof(deck.newCardName));
		ImGui::DragInt("Count", &deck.newCardCount);
		if (ImGui::Button("Add to deck"))
		{
			std::string newName = "";
			newName.append(deck.newCardName);
			Card newCard = Card(newName);
			newCard.count = deck.newCardCount;
			deck[newCard.id.id] = newCard;
			std::fill(deck.newCardName, deck.newCardName + sizeof(deck.newCardName), 0);
		}

		for (auto& [id, card] : deck.cards)
		{
			ImGui::PushID(int_from_id(id));
			ImGui::Separator();
			ImGui::Text(card.name.c_str());
			ImGui::DragInt("Count", &card.count);
			ImGui::DragInt("Desired minimum in initial hand", &card.desired_minimum);
			ImGui::PopID();
		}
		ImGui::End();
	}

private:
	Deck deck;
	int hand_size = 7;
};

// ENTRY POINT
Walnut::Application* Walnut::CreateApplication(int argc, char** argv)
{
	Walnut::ApplicationSpecification spec;
	spec.Name = "Walnut Example";

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