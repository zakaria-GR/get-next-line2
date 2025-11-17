#include "get_next_line.h"

int main()
{
	int fd = open("test.txt", O_RDONLY);

	char* ptr;
	while ((ptr = get_next_line(fd)) != NULL)
	{	
		printf("%s", ptr);
		free(ptr);
	}
	close(fd);
}