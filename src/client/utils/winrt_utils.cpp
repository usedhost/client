#include "winrt_utils.hpp"

void winrt_utils::reset_title() {
	set_title("");
}

winrt_utils::game_version winrt_utils::get_package_version() {
	const winrt::Windows::ApplicationModel::Package package = winrt::Windows::ApplicationModel::Package::Current();
	auto [major, minor, build, revision] = package.Id().Version();

	return { major, minor, build, revision };
}

std::string winrt_utils::get_package_version_string() {
	const auto version = get_package_version();
	return std::to_string(version.major) + "." + std::to_string(version.minor) + "." + std::to_string(version.build) + "." + std::to_string(version.revision);
}

std::string winrt_utils::get_formatted_package_version_string() {
	const auto version = get_package_version();

	int build = version.build / 100;
	return std::to_string(version.major) + "." + std::to_string(version.minor) + "." + std::to_string(build);
}