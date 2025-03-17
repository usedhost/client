#pragma once

namespace selaura_handlers {
	struct input_key;
}

namespace selaura_event_types {
	struct Render {};
	struct Resize {};

    struct KeyDown {
		selaura_handlers::input_key* key;
    };

	struct KeyUp {
		selaura_handlers::input_key* key;
	};

	struct CharReceived {
		uint32_t character;
	};

	struct PointerMoved {
		float x;
		float y;
	};

	struct PointerExited {};

	struct PointerPressed {
		float x;
		float y;
		int button;
	};

	struct PointerReleased {
		float x;
		float y;
		int button;
	};

	struct PointerWheelChanged {
		float delta;
	};
}