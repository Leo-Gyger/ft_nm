#include <stdlib.h>
#include <stdio.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>
size_t	get_flags(int fd)
{
	struct stat st;

	fstat(fd, &st);
	return (st.st_size);
}

int	main(int ac, char *av[])
{
	int	*buf;
	int	fd;
	size_t	size;

	fd = open("test.o", O_RDWR);
	size = get_flags(fd);

	buf = mmap(0, size, PROT_READ|PROT_EXEC, MAP_SHARED, fd, 0);
	printf("%d\n", buf[18]);
	for (int i = 0; i <= size/sizeof *buf; ++i)
		printf("data in case[%d]: %x\n", i, buf[i]);
	munmap(buf, size);
	close(fd);
	return (1);
}
