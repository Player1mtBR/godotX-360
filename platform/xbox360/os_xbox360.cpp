#include "os_xbox360.h"

#include "main/main.h"

#include <input/input.h>
#include <ppc/timebase.h>
#include <usb/usbmain.h>

#include <stdio.h>

OS_Xbox360::OS_Xbox360() {
	main_loop = nullptr;
	timebase_start = mftb();
}

void OS_Xbox360::initialize_core() {
	timebase_start = mftb();
}

Error OS_Xbox360::initialize(const VideoMode &p_desired, int, int) {
	current_videomode = p_desired;
	return ERR_UNAVAILABLE;
}

void OS_Xbox360::finalize() {
	delete_main_loop();
}

void OS_Xbox360::finalize_core() {
}

void OS_Xbox360::set_main_loop(MainLoop *p_main_loop) {
	main_loop = p_main_loop;
}

void OS_Xbox360::delete_main_loop() {
	if (main_loop) {
		memdelete(main_loop);
		main_loop = nullptr;
	}
}

bool OS_Xbox360::_check_internal_feature_support(const String &) {
	return false;
}

String OS_Xbox360::get_name() const {
	return "Xbox 360";
}

void OS_Xbox360::alert(const String &p_alert, const String &p_title) {
	printf("%s: %s\n", p_title.utf8().get_data(), p_alert.utf8().get_data());
}

String OS_Xbox360::get_stdin_string() {
	return String();
}

Point2 OS_Xbox360::get_mouse_position() const {
	return Point2();
}

int OS_Xbox360::get_mouse_button_state() const {
	return 0;
}

void OS_Xbox360::set_window_title(const String &) {
}

void OS_Xbox360::set_video_mode(const VideoMode &p_video_mode, int) {
	current_videomode = p_video_mode;
}

OS::VideoMode OS_Xbox360::get_video_mode(int) const {
	return current_videomode;
}

void OS_Xbox360::get_fullscreen_mode_list(List<VideoMode> *, int) const {
}

int OS_Xbox360::get_current_video_driver() const {
	return -1;
}

int OS_Xbox360::get_video_driver_count() const {
	return 0;
}

const char *OS_Xbox360::get_video_driver_name(int) const {
	return "";
}

Error OS_Xbox360::get_entropy(uint8_t *, int) {
	return ERR_UNAVAILABLE;
}

Size2 OS_Xbox360::get_window_size() const {
	return Size2(current_videomode.width, current_videomode.height);
}

bool OS_Xbox360::can_draw() const {
	return false;
}

Error OS_Xbox360::execute(const String &, const List<String> &, bool, ProcessID *, String *, int *, bool, Mutex *, bool) {
	return ERR_UNAVAILABLE;
}

Error OS_Xbox360::kill(const ProcessID &) {
	return ERR_UNAVAILABLE;
}

bool OS_Xbox360::is_process_running(const ProcessID &) const {
	return false;
}

bool OS_Xbox360::has_environment(const String &) const {
	return false;
}

String OS_Xbox360::get_environment(const String &) const {
	return String();
}

bool OS_Xbox360::set_environment(const String &, const String &) const {
	return false;
}

MainLoop *OS_Xbox360::get_main_loop() const {
	return main_loop;
}

OS::Date OS_Xbox360::get_date(bool) const {
	Date date = {};
	date.month = MONTH_JANUARY;
	date.weekday = DAY_SUNDAY;
	return date;
}

OS::Time OS_Xbox360::get_time(bool) const {
	Time time = {};
	return time;
}

OS::TimeZoneInfo OS_Xbox360::get_time_zone_info() const {
	TimeZoneInfo info = {};
	return info;
}

void OS_Xbox360::delay_usec(uint32_t p_usec) const {
	const uint64_t target_ticks = (static_cast<uint64_t>(p_usec) * PPC_TIMEBASE_FREQ + 999999) / 1000000;
	const uint64_t start = mftb();
	while (mftb() - start < target_ticks) {
		asm volatile("or 31,31,31");
	}
}

uint64_t OS_Xbox360::get_ticks_usec() const {
	const uint64_t elapsed_ticks = mftb() - timebase_start;
	return (elapsed_ticks / PPC_TIMEBASE_FREQ) * 1000000 +
			(elapsed_ticks % PPC_TIMEBASE_FREQ) * 1000000 / PPC_TIMEBASE_FREQ;
}

void OS_Xbox360::run() {
	if (!main_loop) {
		return;
	}

	main_loop->init();
	while (true) {
		usb_do_poll();
		controller_data_s controller = {};
		get_controller_data(&controller, 0);
		if (Main::iteration()) {
			break;
		}
	}
	main_loop->finish();
}