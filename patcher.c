#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/fcntl.h>
#include <sys/stat.h>

void *readallfile(const char *p, unsigned *sz) {
	struct stat s;
	int fd = open(p, O_RDONLY);
	if (fd == -1)
		return 0;
	stat(p, &s);
	void *b = malloc(s.st_size);
	*sz = read(fd, b, s.st_size);
	close(fd);
	return b;
}

int main(int argc, char *argv[argc])
{
	if (argc != 4) {
		fprintf(stderr, "Usage: ./patcher [dol] [code] [load addr]...\n");
		return 1;
	}

	unsigned MEM2 = __builtin_bswap32(strtol(argv[3], 0, 16));
	unsigned s;
	unsigned char *dol = readallfile(argv[1], &s);

	unsigned ps;
	unsigned char *pc = readallfile(argv[2], &ps);

	unsigned *offsets = (void*)(dol + 0x00);
	unsigned *address = (void*)(dol + 0x48);
	unsigned *lengths = (void*)(dol + 0x90);

	unsigned *entry = (void*)(dol + 0xe0);
	*entry = MEM2; // change entrypoint

	unsigned i = 0;
	while (offsets[i]) {
		++i;
	}
	if (i >= 18) {
		fprintf(stderr, "No more free sections...\n");
		return 1;
	}
	offsets[i] = __builtin_bswap32(s);
	address[i] = MEM2;
	lengths[i] = __builtin_bswap32(ps);
	write(1, dol, s);
	write(1, pc, ps);
	free(dol);
	free(pc);
	close(1);
	return 0;
}
