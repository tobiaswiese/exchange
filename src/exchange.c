#define _GNU_SOURCE
#include <fcntl.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>

#ifndef SMALL
#include <getopt.h>
#include <unistd.h>
#endif

#ifndef DEFAULT_PROGRAM_NAME
# define DEFAULT_PROGRAM_NAME "exchange"
#endif

#ifndef VERSION
# define VERSION ""
#endif

#ifndef SMALL
static char *program_name = DEFAULT_PROGRAM_NAME;
static struct option const long_options[] = {
	{ "help", no_argument, NULL, 'h' },
	{ "version", no_argument, NULL, 'v' },
	{ NULL, 0, NULL, 0 },
};

void usage(FILE *fd) {
	fprintf(fd, "\
Usage: %s [OPTION]... <PATH 1> <PATH 2>\n\
Exchange PATH 1 and PATH 2.\n",
		program_name);
	fprintf(fd, "\n");
	fprintf(fd, "\
Available Options:\n\
  -h, --help            display this help and exit\n\
  -v, --version         output version information and exit\n");
}

void version() {
	printf("%s %s\n", program_name, VERSION);
	printf("Build on %s %s.\n", __DATE__, __TIME__);
}
#endif // !SMALL

int main(int argc, char *argv[]) {
	char *path1, *path2;
#ifndef SMALL
	if (argc > 0)
		program_name = argv[0];

	int c;
	while ((c = getopt_long(argc, argv, "hvt", long_options, NULL))
			!= -1)
	{
		switch (c) {
			case 't':
				break;
			case 'h':  // help
				usage(stdout);
				return EXIT_SUCCESS;
			case 'v':  // version
				version();
				return EXIT_SUCCESS;
			default:
				usage(stderr);
				return EXIT_FAILURE;
		}
	}

	if (argc - optind != 2) {
		fprintf(stderr, "%s: invalid number of arguments. Expected 2.\n", program_name);
		usage(stderr);
		return EXIT_FAILURE;
	}

#else
	// We currently don't accept any options
	// when compiling with SMALL
	// Define optind manually, because we don't use optparse.
	const int optind = 1;
#endif // !SMALL

	if (argc - optind != 2) {
#ifndef SMALL
		fprintf(stderr, "%s: invalid number of arguments. Expected 2.\n", program_name);
		usage(stderr);
#endif
		return EXIT_FAILURE;
	}
	path1 = argv[optind];
	path2 = argv[optind + 1];

	// Do the magic
	if (renameat2(AT_FDCWD, path1, AT_FDCWD, path2, RENAME_EXCHANGE) != 0) {
		int errsv = errno;
#ifndef SMALL
		perror(program_name);
#endif
		return -errsv;
	}
	return EXIT_SUCCESS;
}
