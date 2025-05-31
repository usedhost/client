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
		io = std::make_unique<selaura::io>();

		io->init();

		selaura::detail::register_memory();
		selaura::init_hooking();
		this->hook_manager->for_each([&](auto& hook) {
			hook.enable();
		});

#ifdef SELAURA_WINDOWS
		winrt::Windows::ApplicationModel::Core::CoreApplication::MainView().CoreWindow().Dispatcher().RunAsync(winrt::Windows::UI::Core::CoreDispatcherPriority::Normal, []() {
			winrt::Windows::UI::ViewManagement::ApplicationView::GetForCurrentView().Title(winrt::to_hstring(std::format("Selaura Client {}{}", CLIENT_VERSION, DEVELOPER_MODE)));
		});
#endif

		auto endTime = std::chrono::high_resolution_clock::now();
		std::chrono::duration<float> duration = endTime - startTime;

		io->info("Successfully injected [{:.2f}s]", duration.count());
// refresh
		/*
		this->subscribe<test, &instance::func>();

		test ev( 1 );
		selaura::dispatcher<test>::dispatch(ev);
		*/
	}

	void instance::shutdown() {
		auto startTime = std::chrono::high_resolution_clock::now();
		io->info("Attempting to uninject");

		this->hook_manager->for_each([&](auto& hook) {
			hook.disable();
		});

#ifdef SELAURA_WINDOWS
		winrt::Windows::ApplicationModel::Core::CoreApplication::MainView().CoreWindow().Dispatcher().RunAsync(winrt::Windows::UI::Core::CoreDispatcherPriority::Normal, []() {
			winrt::Windows::UI::ViewManagement::ApplicationView::GetForCurrentView().Title(winrt::to_hstring(""));
		});
#endif
		selaura::shutdown_hooking();

		auto endTime = std::chrono::high_resolution_clock::now();
		std::chrono::duration<float> duration = endTime - startTime;

		io->info("Successfully uninjected [{:.2f}s]", duration.count());
	}
};
