#include <stdio.h>
#include <stdbool.h>

#include <console/console.h>
#include <input/input.h>
#include <usb/usbmain.h>
#include <xenon_soc/xenon_power.h>
#include <xenos/xenos.h>

int main() {
	xenos_init(VIDEO_MODE_AUTO);
	console_init();

	xenon_make_it_faster(XENON_SPEED_FULL);

	usb_init();
	usb_do_poll();

	console_clrscr();

	printf("Godot Xbox 360 platform test\n");
	printf("============================\n\n");
	printf("libxenon initialized successfully.\n");
	printf("Godot Xenon ELF is running.\n\n");
	printf("HELL YEAH!");
	printf("Press Y to exit.\n");

	struct controller_data_s pad;

	while (true) {
		usb_do_poll();

		if (get_controller_data(&pad, 0)) {
			if (pad.y) {
				return 0;
			}
		}
	}

	return 0;
}
