#include <stdio.h>
#include <sys/stat.h>
#include <sys/stat.h>

void show_stat_info(char*, struct stat *);

int main(int ac, char* av[])
{
	struct stat info;

	if (ac > 1)
		if ( stat(av[1], &info) != -1 )
		{
			show_stat_info( av[1], &info );
			return 0;
		}
		else
			perror(av[1]);

	return 1;
}

void show_stat_info(char* fname, struct stat* buf)
{
	printf("mode\t: %o\n", buf->st_mode);
	printf("links\t: %d\n", buf->st_nlink);
	printf("user\t: %d\n", buf->st_uid);
	printf("group\t: %d\n", buf->st_gid);
	printf("size\t: %d\n", buf->st_size);
	printf("modtime\t: %d\n", buf->st_mtime);
	printf("name\t: %s\n", fname);
}
