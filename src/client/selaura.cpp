#include "selaura.hpp"

selaura& selaura::get() {
	static selaura inst;
	return inst;
};


/*
std::shared_ptr<selaura> selaura::get() {
	static auto inst = std::make_shared<selaura>();
	return inst;
}
void selaura::init(HMODULE hModule) {
	if (this->m_initialized.load()) return;
	logger::clear();
	logger::info("Initializing Selaura Client");
	this->hModule = hModule;

	winrt_utils::run_async([this]() {
		auto window = winrt::Windows::UI::Core::CoreWindow::GetForCurrentThread();
		if (window)
		{
			selaura_handlers::input::initialize(window);
		}
	});

	selaura_hooks::initialize();

	std::string buildType;
	#ifdef _DEBUG
		buildType = "Debug";
	#else
		buildType = "Release";
	#endif
	winrt_utils::set_title("Selaura Client ({}) - {}", buildType, winrt_utils::get_formatted_package_version_string());

	selaura_handlers::event::subscribe([](selaura_event_types::PointerPressed& event) {
		logger::debug("{}", event.button);
	});

	this->m_initialized.store(true);
	logger::info("Selaura Client initialized");
}

void selaura::shutdown() {
	if (!this->m_initialized.load()) return;
	logger::info("Shutting down Selaura Client");
	
	winrt_utils::run_async([]() {
		selaura_handlers::input::shutdown();
	});
	selaura_hooks::shutdown();
	winrt_utils::reset_title();

	this->m_initialized.store(false);
	logger::info("Selaura Client shutdown");
}

void selaura::eject() {
	this->shutdown();

	Sleep(200);
	CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)FreeLibraryAndExitThread, this->hModule, 0, nullptr);
}*/