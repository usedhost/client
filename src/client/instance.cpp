#include "instance.hpp"

namespace selaura {
	void instance::start() {
		auto startTime = std::chrono::high_resolution_clock::now();

		this->io = std::make_unique<selaura::io>();
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

		this->io->info("Successfully injected [{:.2f}s]", duration.count());

		/*
		this->subscribe<test, &instance::func>();

		test ev( 1 );
		selaura::dispatcher<test>::dispatch(ev);
		*/
	}
};
