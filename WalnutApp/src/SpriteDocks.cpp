#include "Walnut/Application.h"
#include "Walnut/Entrypoint.h"

#include "EditorLayer.h"

Walnut::Application* Walnut::CreateApplication(int argc, char** argv)
{
	Walnut::ApplicationSpecification spec;
	spec.Name = "SpriteDocks";

	Walnut::Application* app = new Walnut::Application(spec);

	std::shared_ptr<SpriteDocks::EditorLayer> editorLayer = std::make_shared<SpriteDocks::EditorLayer>(app);
	app->PushLayer(editorLayer);

	return app;
}
