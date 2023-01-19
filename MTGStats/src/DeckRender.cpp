#include "Deck.h"
#include <string>


int from_uuid(uuids::uuid id)
{
	int acc = 0;
	for (size_t i = 0; i < sizeof(int); ++i)
	{
		acc |= ((int)(id.as_bytes()[i]) << i * 8);
	}
	return acc;
}


void Deck::RenderGui()
{
	ImGui::Begin("Deck");
	ImGui::Text("New card: ");
	ImGui::InputText("Name", newCardName, sizeof(newCardName));
	ImGui::DragInt("Count", &newCardCount);
	if (ImGui::Button("Add to deck"))
	{
		std::string newName = "";
		newName.append(newCardName);
		Card newCard = Card(newName);
		newCard.count = newCardCount;
		(*this)[newCard.id.id] = newCard;
		std::fill(newCardName, newCardName + sizeof(newCardName), 0);
	}

	for (auto& [id, card] : cards)
	{
		ImGui::PushID(from_uuid(id));
		ImGui::Separator();
		ImGui::Text(card.name.c_str());
		ImGui::DragInt("Count", &card.count);
		ImGui::PopID();
	}
	ImGui::End();
}