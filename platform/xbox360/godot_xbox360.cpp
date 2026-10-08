#include <stdio.h>

#include <console/console.h>
#include <usb/usbmain.h>
#include <xenon_soc/xenon_power.h>
#include <xenos/xenos.h>

#include "main/main.h"
#include "os_xbox360.h"

int main(int argc, char *argv[]) {
	xenos_init(VIDEO_MODE_AUTO);
	console_init();

	xenon_make_it_faster(XENON_SPEED_FULL);

	usb_init();
	usb_do_poll();

	console_clrscr();
	printf("Xbox 360: libxenon initialized\n");

	OS_Xbox360 os;
	printf("Xbox 360: OS constructed\n");

	const char *exec_path = argc > 0 && argv[0] ? argv[0] : "godot_xbox360";
	const int argument_count = argc > 0 ? argc - 1 : 0;
	char **arguments = argc > 0 ? &argv[1] : nullptr;

	printf("Xbox 360: Main::setup\n");
	Error error = Main::setup(exec_path, argument_count, arguments);
	if (error != OK) {
		if (error == ERR_HELP) {
			return 0;
		}
		return 255;
	}

	printf("Xbox 360: Main::start\n");
	if (Main::start()) {
		printf("Xbox 360: entering OS::run\n");
		os.run();
	}

	Main::cleanup();
	return os.get_exit_code();
}
