#include "Walnut/Application.h"
#include "Walnut/EntryPoint.h"

#include "Walnut/Image.h"

#include <iostream>
#include "MTG_UUID.h"
#include "Deck.h"

class ExampleLayer : public Walnut::Layer
{
public:
	// CALLED EACH FRAME
	virtual void OnUIRender() override
	{
		ImGui::Begin("Hello");
		if (ImGui::Button("Button"))
			std::cout << MTG_UUID().id << std::endl;
		ImGui::End();

		RenderMainDeck();
		
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
			ImGui::PopID();
		}
		ImGui::End();
	}




private:
	Deck deck;
	Deck desired_hand;
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