#pragma once
#include <iostream>

#include "Walnut/Application.h"
#include <imgui_internal.h>

namespace SpriteDocks {
	class EditorLayer : public Walnut::Layer {
	public:
		ImVec4 color = ImVec4(0.0f, 0.0f, 0.0f, 1.0f);
		int brushSize = 1;
		float brushOpacity = 1;
		Walnut::Application* app;

		EditorLayer(Walnut::Application* spriteDocksApp);

		virtual void OnUIRender() override;

	private:
		void RenderMenuBar();

		void RenderColorPickerWindow();
		void RenderLayerContainerWindow();
		void RenderToolBarWindow();
		void RenderToolInfoWindow();
		void RenderPaintLayer();

		void LoadDefaultDockingConfiguration();
		bool ImGuiIniFileFound();
	};

};

