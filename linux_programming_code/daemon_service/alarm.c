#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <ctype.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>


#define OUTPUT_FILE "./tmp/tmp_logfile.log"


int main()
{
    int fd;
    char buf[100];

    system("mkdir -p tmp");
    fd = open(OUTPUT_FILE, O_CREAT|O_RDWR, 0664);
    if (fd < 0)
    {
        printf("open error\n");
        exit(-1);
    }

	for (;;)
	{
		time_t t;
		time(&t);

        memset(buf, 0, sizeof(buf));
		sprintf(buf, "current time: %ld\n", (long)t);
        write(fd, buf, sizeof(buf));

		sleep(3);
	}

	return 0;
}
