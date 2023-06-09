#pragma once

#include "EditorLayer.h"

namespace SpriteDocks {

	EditorLayer::EditorLayer(Walnut::Application* spriteDocksApp) {
		app = spriteDocksApp;
	}

	void EditorLayer::OnUIRender() {
		if (!ImGuiIniFileFound()) {
			LoadDefaultDockingConfiguration();
		}

		RenderColorPickerWindow();
		RenderLayerContainerWindow();
		RenderToolBarWindow();
		RenderToolInfoWindow();
		RenderPaintLayer();
	}

	void EditorLayer::RenderMenuBar() {
		if (ImGui::BeginMenuBar())
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
			ImGui::EndMenuBar();
		}
	}

	void EditorLayer::RenderColorPickerWindow() {
		ImGui::Begin("Colors");
		ImGui::ColorPicker4("Color Picker", (float*)&color);
		ImGui::End();
	}

	void EditorLayer::RenderLayerContainerWindow() {
		ImGui::Begin("Layers");

		ImGui::End();
	}

	void EditorLayer::RenderToolBarWindow() {
		ImGui::Begin("Tools");

		ImGui::Button("Pen");
		ImGui::Button("Eraser");
		ImGui::Button("Mouse");
		ImGui::Button("Select");
		ImGui::Button("Bucket");

		ImGui::End();
	}

	void EditorLayer::RenderToolInfoWindow() {
		ImGui::Begin("Tool Info", false);

		ImGui::PushItemWidth(ImGui::GetWindowWidth() * 0.2f);

		ImGui::SliderFloat("Brush Opacity", &brushOpacity, 0.0f, 1.0f);
		ImGui::SameLine();
		ImGui::SliderInt("Brush Size", &brushSize, 1, 100);

		ImGui::End();
	}

	void EditorLayer::RenderPaintLayer() {
		ImGui::Begin("Paint");
		ImGui::End();
	}

	void EditorLayer::LoadDefaultDockingConfiguration() {
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

	bool EditorLayer::ImGuiIniFileFound() {
		size_t fileDataSize = 0;
		const char* iniFilename = ImGui::GetCurrentContext()->IO.IniFilename;
		char* fileData = (char*)ImFileLoadToMemory(iniFilename, "rb", &fileDataSize);
		return fileData;
	}

}
