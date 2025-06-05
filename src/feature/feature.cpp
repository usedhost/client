#include "feature.hpp"

namespace selaura {
	feature::~feature() noexcept {
		this->enabled = false;
	}

	void feature::set_enabled(bool enabled) {
		this->enabled = enabled;
	}

	bool feature::is_enabled() const {
		return this->enabled;
	}

	void feature::toggle() {
		this->enabled = !this->enabled;
	}

	void feature::set_hotkey(int hotkey) {
		this->hotkey = hotkey;
	}

	int feature::get_hotkey() const {
		return this->hotkey;
	}

	void feature::on_enable() {}
	void feature::on_disable() {}

	void feature::set_feature_size(const glm::vec2& size) {
		this->size = size;
	}
	void feature::set_feature_position(const glm::vec2& pos) {
		this->pos = pos;
	}
	const glm::vec2& feature::get_feature_size() {
		return this->size;
	}
	const glm::vec2& feature::get_feature_pos() {
		return this->pos;
	}
};