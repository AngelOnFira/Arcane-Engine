#include "DebugPane.h"

namespace arcane { namespace ui {

	bool DebugPane::s_WireframeMode = false;

	DebugPane::DebugPane(glm::vec2 &panePosition) : Pane(std::string("Debug Controls"), panePosition)
	{
	}

	void DebugPane::setupPaneObjects() {
#if DEBUG_ENABLED
		ImGui::Text("Hit \"P\" to show/hide the cursor");
		ImGui::Checkbox("Wireframe Mode", &s_WireframeMode);
#endif
	}

} }