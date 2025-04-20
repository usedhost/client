#pragma once

#include <thread>
#include <span>
#include <cstddef>
#include <unordered_map>
#include <typeindex>
#include <memory>
#include <stdexcept>
#include <string_view>
#include <optional>
#include <new>
#include <string>
#include <mutex>

#ifdef _WIN32
#include <winrt/base.h>
#include <winrt/Windows.UI.ViewManagement.h>
#include <winrt/Windows.ApplicationModel.Core.h>
#include <winrt/Windows.UI.Core.h>
#endif

#define FMT_HEADER_ONLY
#include <fmt/format.h>

#include "event/event_handler.hpp"
#include "memory/memory_handler.hpp"
#include <safetyhook.hpp>

class selaura {
public:
	explicit selaura();
	static selaura& get();
	
	event_handler::dispatcher& get_dispatcher();
private:
	event_handler::dispatcher dispatcher;
};

extern char selauraBuffer[sizeof(selaura)];