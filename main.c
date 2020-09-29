/**
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include <libusb.h>

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

int main(int argc, char *argv[])
{
	unsigned char cmd[1] = { 0x14 };
	libusb_device_handle *h;
	libusb_context *c = NULL;
	int r;

	/* we need to be able to send control transfer messages
	 * maybe we could find a better way but for now this will
	 * do
	 */
	if (geteuid() != 0) {
		fprintf(stderr, "You need to run as root or use sudo");
		return 1;
	}

	r = libusb_init(&c);
	if (r) {
		fprintf(stderr, "Unable to initialize libusb: %s\n", libusb_strerror(r));
		return 1;
	}

	h = libusb_open_device_with_vid_pid(c, 0x045e, 0x028e);
	if (h == NULL) {
		fprintf(stderr, "Unable to open usb device\n");
		goto cleanup;
	}

	/*
	 * see https://gist.github.com/dnmodder/de2df973323b7c6acf45f40dc66e8db3
	 */
	r = libusb_control_transfer(h, 0xc1, 0x01, 0x0100, 0x00, cmd, sizeof(cmd), 0);
	if (r < 0) {
		fprintf(stderr, "Control transfer failed: %s\n", libusb_strerror(r));
		goto cleanup;
	}

cleanup:
	if (h)
		libusb_close(h);

	libusb_exit(c);
	return 0;
}
