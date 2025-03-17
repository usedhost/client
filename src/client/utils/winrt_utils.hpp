#pragma once

#include <Windows.h>
#include <winrt/base.h>
#include <winrt/Windows.UI.ViewManagement.h>
#include <winrt/Windows.ApplicationModel.Core.h>
#include <winrt/Windows.UI.Core.h>
#include <CoreWindow.h>

#include <format>
#include <string>
#include <utility>

namespace winrt_utils {
	struct game_version {
		int major;
		int minor;
		int build;
		int revision;
	};

	template<typename... Args>
	void set_title(const std::string& fmt, Args&&... args) {
		const std::string title = std::vformat(fmt, std::make_format_args(args...));
		winrt::Windows::ApplicationModel::Core::CoreApplication::MainView().CoreWindow().Dispatcher().RunAsync(
			winrt::Windows::UI::Core::CoreDispatcherPriority::Normal,
			[title]() {
				winrt::Windows::UI::ViewManagement::ApplicationView::GetForCurrentView().Title(winrt::to_hstring(title));
			}
		);
	}

	template <typename Callable>
	void run_async(Callable&& func, winrt::Windows::UI::Core::CoreDispatcherPriority priority = winrt::Windows::UI::Core::CoreDispatcherPriority::Normal)
	{
		winrt::Windows::ApplicationModel::Core::CoreApplication::MainView().CoreWindow().Dispatcher().RunAsync(priority, std::forward<Callable>(func));
	}

	void reset_title();
	game_version get_package_version();
	std::string get_package_version_string();
	std::string get_formatted_package_version_string();
	HWND get_window_handle(winrt::Windows::UI::Core::CoreWindow const&);

};