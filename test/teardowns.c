#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/syscall.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#include "liburing.h"

static void loop(void)
{
	int i;

	for (i = 0; i < 1000; i++) {
		struct io_uring ring;
		int fd;

		memset(&ring, 0, sizeof(ring));
		fd = io_uring_queue_init(0xa4, &ring, 0);
		if (fd >= 0)
			close(fd);
	}
	exit(0);
}

int main(void)
{
	int i;

	for (i = 0; i < 12; i++) {
		if (!fork()) {
			loop();
			break;
		}
	}

	sleep(20);
	return 0;
}
