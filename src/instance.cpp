#include "instance.hpp"

namespace selaura {
	std::shared_ptr<selaura::instance> inst;

	std::shared_ptr<selaura::instance> instance::get() {
		return selaura::inst;
	}

	bool instance::start() {
		if (auto self = shared_from_this(); self) {
			selaura::inst = self;
		}
		else {
			throw std::runtime_error("selaura::instance must be managed by an std::shared_ptr");
		}

		return true;
	}

	void instance::init() {
		auto startTime = std::chrono::high_resolution_clock::now();

		this->get_data_folder();
		auto log_file = this->data_folder / "logs.txt";

		auto logger = spdlog::basic_logger_mt("selaura", log_file.string(), true);
		logger->set_pattern("[%Y-%m-%d %H:%M:%S] [%^%l%$] %v");
		logger->set_level(spdlog::level::debug);
		logger->flush_on(spdlog::level::debug);

		spdlog::set_default_logger(logger);

		get<hook_manager>().init();
		get<input_manager>().init();
		get<script_manager>().init();
		get<screen_manager>().init();

		get<event_manager>().subscribe<key_event>([&](key_event& ev) {
			get<screen_manager>().for_each([&](screen& scr) {
				if (scr.is_enabled()) ev.cancel();

				if (!scr.is_enabled() && scr.get_hotkey() == ev.key && ev.action == selaura::key_action::key_up) scr.set_enabled(true);
				if (scr.is_enabled() && ev.key == selaura::key::Escape && ev.action == selaura::key_action::key_up) scr.set_enabled(false);
			});
		});

#ifdef SELAURA_WINDOWS
		winrt::Windows::ApplicationModel::Core::CoreApplication::MainView().CoreWindow().Dispatcher().RunAsync(winrt::Windows::UI::Core::CoreDispatcherPriority::Normal, []() {
			winrt::Windows::UI::ViewManagement::ApplicationView::GetForCurrentView().Title(winrt::to_hstring(std::format("Selaura Client {}{}", CLIENT_VERSION, DEVELOPER_MODE)));
		});
#endif

		auto endTime = std::chrono::high_resolution_clock::now();
		std::chrono::duration<float> duration = endTime - startTime;

		spdlog::info("Successfully injected [{:.2f}s]", duration.count());

	}

	void instance::shutdown() {
		auto startTime = std::chrono::high_resolution_clock::now();
		spdlog::info("Attempting to uninject");

		//this->hook_manager->for_each([&](auto& hook) {
			//hook.disable();
		//});

#ifdef SELAURA_WINDOWS
		winrt::Windows::ApplicationModel::Core::CoreApplication::MainView().CoreWindow().Dispatcher().RunAsync(winrt::Windows::UI::Core::CoreDispatcherPriority::Normal, []() {
			winrt::Windows::UI::ViewManagement::ApplicationView::GetForCurrentView().Title(winrt::to_hstring(""));
		});
#endif

		auto endTime = std::chrono::high_resolution_clock::now();
		std::chrono::duration<float> duration = endTime - startTime;

		spdlog::info("Successfully uninjected [{:.2f}s]", duration.count());
	}

	const std::filesystem::path& instance::get_data_folder() {
#ifdef SELAURA_WINDOWS
		char* localAppData = nullptr;
		size_t size = 0;
		_dupenv_s(&localAppData, &size, "APPDATA");
		if (localAppData) {
			this->data_folder = std::filesystem::path(localAppData + std::string("\\..\\Local\\Packages\\Microsoft.MinecraftUWP_8wekyb3d8bbwe\\RoamingState\\Selaura"));
		}
#elif defined(SELAURA_LINUX)
		this->data_folder = "/data/data/com.mojang.minecraftpe/Selaura";
#elif defined(SELAURA_ANDROID)
		this->data_folder = "/data/data/com.selauraclient.launcher/Selaura";
#endif
		std::filesystem::create_directories(this->data_folder);

		return this->data_folder;
	}
};