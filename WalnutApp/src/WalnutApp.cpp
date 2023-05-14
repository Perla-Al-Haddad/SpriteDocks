#include <iostream>

#include "Walnut/Application.h"
#include "Walnut/EntryPoint.h"

#include "Walnut/Image.h"

class ColorLayer : public Walnut::Layer
{
public:
	ImVec4 color = ImVec4(0.0f, 0.0f, 0.0f, 1.0f);

	virtual void OnUIRender() override
	{
		ImGui::Begin("Colors");

		ImGui::ColorPicker4("Color Picker", (float*)&color);

		ImGui::End();

		//ImGui::ShowDemoWindow();
	}
};

class LayerContainerLayer : public Walnut::Layer {
public:
	virtual void OnUIRender() override {
		ImGui::Begin("Layers");



		ImGui::End();
	}
};

class ToolBarLayer : public Walnut::Layer {
	virtual void OnUIRender() override {
		ImGui::Begin("Tools");

		ImGui::Button("Pen");
		ImGui::Button("Eraser");
		ImGui::Button("Mouse");
		ImGui::Button("Select");
		ImGui::Button("Bucket");

		ImGui::End();
	}
};

class ToolInfoLayer : public Walnut::Layer {
	int brushSize = 1;
	float brushOpacity = 1;

	virtual void OnUIRender() override {
		ImGui::Begin("Tool Info", false);

		ImGui::PushItemWidth(ImGui::GetWindowWidth() * 0.2f);

		ImGui::SliderFloat("Brush Opacity", &brushOpacity, 0.0f, 1.0f);
		ImGui::SameLine();
		ImGui::SliderInt("Brush Size", &brushSize, 1, 100);

		ImGui::End();
	}
};

class PaintLayer : public Walnut::Layer {
	virtual void OnUIRender() override {
		ImGui::Begin("Paint");
		ImGui::End();
	}
};

Walnut::Application* Walnut::CreateApplication(int argc, char** argv)
{
	Walnut::ApplicationSpecification spec;
	spec.Name = "SpriteDocks";

	Walnut::Application* app = new Walnut::Application(spec);
	app->PushLayer<ColorLayer>();
	app->PushLayer<LayerContainerLayer>();
	app->PushLayer<ToolBarLayer>();
	app->PushLayer<ToolInfoLayer>();
	app->PushLayer<PaintLayer>();

	app->SetMenubarCallback([app]()
		{
			if (ImGui::BeginMenu("File"))
			{
				if (ImGui::MenuItem("Open File..."))
				{
					std::cout << "Open" << std::endl;
				}
				if (ImGui::MenuItem("Save"))
				{
					std::cout << "Save" << std::endl;
				}
				if (ImGui::MenuItem("Save As"))
				{
					std::cout << "Save As" << std::endl;
				}
				if (ImGui::MenuItem("Exit"))
				{
					app->Close();
				}
				ImGui::EndMenu();
			}
			if (ImGui::BeginMenu("Edit")) {
				if (ImGui::MenuItem("Copy"))
				{
					std::cout << "Copy" << std::endl;
				}
				if (ImGui::MenuItem("Paste"))
				{
					std::cout << "Paste" << std::endl;
				}
				if (ImGui::MenuItem("Cut"))
				{
					std::cout << "Cut" << std::endl;
				}
				ImGui::EndMenu();
			}
		});
	return app;
}
