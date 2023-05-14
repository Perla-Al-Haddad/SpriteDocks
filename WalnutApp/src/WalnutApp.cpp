#include <iostream>

#include "Walnut/Application.h"
#include "Walnut/EntryPoint.h"

#include "Walnut/Image.h"
#include <imgui_internal.h>

class ColorLayer : public Walnut::Layer
{
public:
	ImVec4 color = ImVec4(0.0f, 0.0f, 0.0f, 1.0f);

	virtual void OnUIRender() override
	{
		ImGui::Begin("Colors");

		ImGui::ColorPicker4("Color Picker", (float*)&color);

		ImGui::End();
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


class LayerStackManager : public Walnut::Layer {
public:
	ImVec2 viewPortOffset;

	LayerStackManager(ImVec2 viewPortOffset) {
		this->viewPortOffset = viewPortOffset;
	}

	virtual void OnUIRender() override {

		static ImGuiDockNodeFlags dockspaceFlags = ImGuiDockNodeFlags_PassthruCentralNode;

		ImGuiViewport* viewport = ImGui::GetMainViewport();

		ImGuiIO& io = ImGui::GetIO();
		if (!(io.ConfigFlags & ImGuiConfigFlags_DockingEnable)) { return; }
		ImGuiID dockspaceId = ImGui::GetID("VulkanAppDockspace");

		static auto first_time = true;
		if (!first_time) { return; }
		first_time = false;

		ImGui::DockBuilderRemoveNode(dockspaceId); // clear any previous layout
		ImGui::DockBuilderAddNode(dockspaceId, dockspaceFlags | ImGuiDockNodeFlags_DockSpace);
		ImGui::DockBuilderSetNodeSize(dockspaceId, viewport->Size);

		auto mainLeft = ImGui::DockBuilderSplitNode(dockspaceId, ImGuiDir_Left, 0.325f, nullptr, &dockspaceId);

		auto mainLeftLeft = ImGui::DockBuilderSplitNode(mainLeft, ImGuiDir_Left, 0.2f, nullptr, &mainLeft);
		auto mainLeftRight = ImGui::DockBuilderSplitNode(mainLeft, ImGuiDir_Right, 0.2f, nullptr, &mainLeft);

		auto mainLeftRightUp = ImGui::DockBuilderSplitNode(mainLeftRight, ImGuiDir_Up, 0.5f, nullptr, &mainLeftRight);
		auto mainLeftRightDown = ImGui::DockBuilderSplitNode(mainLeftRight, ImGuiDir_Down, 0.5f, nullptr, &mainLeftRight);

		auto mainUp = ImGui::DockBuilderSplitNode(dockspaceId, ImGuiDir_Up, 0.08f, nullptr, &dockspaceId);

		ImGui::DockBuilderDockWindow("Tools", mainLeftLeft);
		ImGui::DockBuilderDockWindow("Colors", mainLeftRightUp);
		ImGui::DockBuilderDockWindow("Layers", mainLeftRightDown);
		ImGui::DockBuilderDockWindow("Tool Info", mainUp);
		ImGui::DockBuilderDockWindow("Paint", dockspaceId);

		ImGui::DockBuilderFinish(dockspaceId);
	}
};

class MenubarHandler {
public:
	static void RenderMenuBar(Walnut::Application* app) {
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
	}
};


Walnut::Application* Walnut::CreateApplication(int argc, char** argv)
{
	Walnut::ApplicationSpecification spec;
	spec.Name = "SpriteDocks";

	Walnut::Application* app = new Walnut::Application(spec);

	ImVec2 menuBarSize;
	app->SetMenubarCallback([app, &menuBarSize]()
		{
			MenubarHandler::RenderMenuBar(app);
			menuBarSize = ImGui::GetWindowSize();
		});

	size_t file_data_size = 0;
	char* file_data = (char*)ImFileLoadToMemory(ImGui::GetCurrentContext()->IO.IniFilename, "rb", &file_data_size);
	file_data = false;
	if (!file_data) {
		std::shared_ptr<LayerStackManager> layerStackManager = std::make_shared<LayerStackManager>(menuBarSize);
		app->PushLayer(layerStackManager);
	}

	app->PushLayer<ColorLayer>();
	app->PushLayer<PaintLayer>();
	app->PushLayer<LayerContainerLayer>();
	app->PushLayer<ToolBarLayer>();
	app->PushLayer<ToolInfoLayer>();

	return app;
}
