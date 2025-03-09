#include "selaura.hpp"

std::shared_ptr<selaura> selaura::get() {
	static auto inst = std::make_shared<selaura>();
	return inst;
}

void selaura::init(HMODULE hModule) {
	if (this->m_initialized.load()) return;
	logger::clear();
	logger::info("Initializing Selaura Client");
	this->hModule = hModule;

	std::string buildType;
	#ifdef _DEBUG
		buildType = "Debug";
	#else
		buildType = "Release";
	#endif
	winrt_utils::set_title("Selaura Client ({}) - {}", buildType, winrt_utils::get_formatted_package_version_string());
	
	winrt_utils::run_async([this]() {
		auto window = winrt::Windows::UI::Core::CoreWindow::GetForCurrentThread();
		if (window)
		{
			selaura_handlers::input::initialize(window);
		}
	});

	/*
			if (args.VirtualKey() == winrt::Windows::System::VirtualKey::Shift && args.KeyStatus().ScanCode == 42)
	{
		// left shift
	}

	if (args.VirtualKey() == winrt::Windows::System::VirtualKey::Shift && args.KeyStatus().ScanCode == 54)
	{
		// right shift
		std::terminate();
	}
	*/

	while (true) {
		logger::debug("Mouse X: {}, Mouse Y: {}", selaura_handlers::input::get_mouse_x(), selaura_handlers::input::get_mouse_y());
		if (selaura_handlers::input::is_key_down("RightShift")) {
			std::terminate();
		}
	}

	this->m_initialized.store(true);
	logger::info("Selaura Client initialized");
}

void selaura::shutdown() {
	if (!this->m_initialized.load()) return;
	logger::info("Shutting down Selaura Client");

	winrt_utils::reset_title();

	this->m_initialized.store(false);
	logger::info("Selaura Client shutdown");
}

void selaura::eject() {
	this->shutdown();

	Sleep(200);
	CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)FreeLibraryAndExitThread, this->hModule, 0, nullptr);
}