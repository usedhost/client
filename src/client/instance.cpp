#include "instance.hpp"

void* fovOriginal;
float fov(void* a1, float a2, void* a3, void* a4) {
	return 30.f;
}

namespace selaura {
	void instance::start() {
		auto startTime = std::chrono::high_resolution_clock::now();

		this->io = std::make_unique<selaura::io>();
		selaura::init_hooking();

		auto sig = this->resolver->signature("? ? ? ? ? ? ? 48 89 ? ? 57 48 81 EC ? ? ? ? 0F 29 ? ? 0F 29 ? ? 44 0F ? ? ? 44 0F ? ? ? 48 8B ? ? ? ? ? 48 33 ? 48 89 ? ? ? 41 0F");
		auto hook = selaura::hook((void*)sig.value(), (void*)fov, (void**)&fovOriginal);
		hook.enable();

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
