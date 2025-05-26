#pragma once

namespace bedrock {
	class LevelSeed64 {
		using ValueType = uint64_t;
	public:
		LevelSeed64();
		LevelSeed64(ValueType value) : value(value) {};

		ValueType value{ 0 };
	};
};