#pragma once
#include "../imgui.h"
#include <Windows.h>
#include <Windows.UI.Core.h>

#include "../../../src/client/utils/winrt_utils.hpp"
#include "../../../src/client/handlers/event.hpp"
#include "../../../src/client/handlers/input.hpp"

IMGUI_API bool ImGui_ImplSelaura_Init();
IMGUI_API void ImGui_ImplSelaura_Shutdown();
IMGUI_API void ImGui_ImplSelaura_NewFrame();