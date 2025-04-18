#include "selaura.hpp"

std::unique_ptr<selaura> selaura::instance;
std::once_flag selaura::init_flag;

SafetyHookInline FOVHook;

float hk_fov(void* a1, float a2, void* a3, void* a4) {
	return 30.f;
}

selaura::selaura() {

#ifdef _WIN32
	const winrt::Windows::ApplicationModel::Package package = winrt::Windows::ApplicationModel::Package::Current();
	auto [major, minor, build, revision] = package.Id().Version();
	std::string versionString = std::string(std::to_string(major) + "." + std::to_string(minor) + "." + std::to_string(build).substr(0, std::to_string(build).size() - 2));

	winrt::Windows::ApplicationModel::Core::CoreApplication::MainView().CoreWindow().Dispatcher().RunAsync(winrt::Windows::UI::Core::CoreDispatcherPriority::Normal, [&]() {
		std::string status = "Release";
#ifdef DEBUG
		status = "Debug";
#endif

		winrt::Windows::UI::ViewManagement::ApplicationView::GetForCurrentView().Title(winrt::to_hstring("Selaura Client (Windows/" + status + ") - " + versionString));
	});
#endif
	auto sig = memory_handler::find_pattern("? ? ? ? ? ? ? 48 89 ? ? 57 48 81 EC ? ? ? ? 0F 29 ? ? 0F 29 ? ? 44 0F ? ? ? 44 0F ? ? ? 48 8B ? ? ? ? ? 48 33 ? 48 89 ? ? ? 41 0F");

	FOVHook = safetyhook::create_inline(sig.value(), hk_fov);
}

void selaura::init() {
	std::call_once(init_flag, [&] {
		instance = std::make_unique<selaura>();
		});
}

selaura& selaura::get() {
	if (!instance)
		throw std::runtime_error("selaura not initialized");
	return *instance;
}