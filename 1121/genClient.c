#define LEN 256

const int port = 23123;
const char* host = "swedupc";

void main(int ac, char* av[])
{
	int fd;

	fd = connect_to_server(host, port);
	if ( fd == -1 )
		exit(1);
	talk_with_server(fd);
	close(fd);
}

void talk_with_server(int fd)
{
	char buf[LEN];
	int n;

	n = read(fd, buf, LEN);
	write(1, buf, n);
}
