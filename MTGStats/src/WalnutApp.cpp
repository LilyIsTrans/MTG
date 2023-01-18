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

		deck.RenderGui();
	}




private:
	Deck<60> deck;
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