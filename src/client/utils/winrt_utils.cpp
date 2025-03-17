#include "winrt_utils.hpp"

void winrt_utils::reset_title() {
	set_title("");
}

winrt_utils::game_version winrt_utils::get_package_version() {
	const winrt::Windows::ApplicationModel::Package package = winrt::Windows::ApplicationModel::Package::Current();
	auto [major, minor, build, revision] = package.Id().Version();

	return { major, minor, build, revision };
}

std::string winrt_utils::get_package_version_string() {
	const auto version = get_package_version();
	return std::to_string(version.major) + "." + std::to_string(version.minor) + "." + std::to_string(version.build) + "." + std::to_string(version.revision);
}

std::string winrt_utils::get_formatted_package_version_string() {
	const auto version = get_package_version();

	int build = version.build / 100;
	return std::to_string(version.major) + "." + std::to_string(version.minor) + "." + std::to_string(build);
}

HWND winrt_utils::get_window_handle(winrt::Windows::UI::Core::CoreWindow const& window) {
	HWND hwnd = nullptr;
	winrt::com_ptr<ICoreWindowInterop> interop;
	winrt::check_hresult(winrt::get_unknown(window)->QueryInterface(interop.put()));
	winrt::check_hresult(interop->get_WindowHandle(&hwnd));

	return hwnd;
}