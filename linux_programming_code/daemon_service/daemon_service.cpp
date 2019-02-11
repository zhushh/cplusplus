#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include <ctype.h>
#include <unistd.h>
#include <fcntl.h>
#include <syslog.h>
#include <sys/stat.h>

#include <string>
using std::string;


#define TMP_OUT_FILE "./tmp/daemon_tmp_file"

#define NAME "test_proc"
#define NAME_FIND "test_proc"
#define RUN_NAME "/Users/irick/zhushh/code/cplusplus/test_proc &"



string int2str(int n)
{
    char t[100];
    sprintf(t, "%d", n);
    return string(t);
}

int get_current_time()
{
    time_t t;
    time(&t);
    return (int)t;
}

int daemon_service(int nochdir, int noclose)
{
    pid_t pid;

    pid = fork();
    if (pid < 0)
    {
        perror("fork");
        return -1;
    }

    // close parent
    if (pid != 0)
    {
        exit(0);
    }

    // create new session
    pid = setsid();
    if (pid < -1)
    {
        perror("setsid");
        return -1;
    }

    if (!nochdir)
    {
        chdir("/");
    }

    // close standard input/output and redirect to /dev/null
    if (!noclose)
    {
        int fd;
        fd = open("/dev/null", O_RDWR, 0);
        if (fd != -1)
        {
            dup2(fd, STDIN_FILENO);
            dup2(fd, STDOUT_FILENO);
            dup2(fd, STDERR_FILENO);
            if (fd > 2)
            {
                close(fd);
            }
        }
    }
    umask(0027);

    return 0;
}

int match(char *src, char *dst, int len)
{
    int i = 0;
    int j = 0;
    int size_dst = 0;

    size_dst = strlen(dst);
    if (size_dst > len)
    {
        return 0;
    }

    for (i = 0; i < len; i++)
    {
        for (j = 0; j < size_dst; j++)
        {
            if (src[i+j] != dst[j])
            {
                break;
            }
        }
        if (j == size_dst)
        {
            return 1;
        }
    }

    return 0;
}

int main(int argc, char **argv)
{
    int fd = 0;
    char buf[1024];
    int cnt = 0;

    daemon_service(0, 0);

    while (true)
    {
        // open log
        openlog(argv[0], LOG_CONS | LOG_PID, LOG_USER);

        system("touch "TMP_OUT_FILE);
        system("ps -ef | grep -v grep | grep "NAME_FIND" >> "TMP_OUT_FILE);

        fd = open(TMP_OUT_FILE, O_CREAT|O_RDONLY, 0777);
        memset(buf, 0, sizeof(buf));
        read(fd, buf, sizeof(buf));

        if (match(buf, NAME, sizeof(buf)))
        {
            syslog(LOG_INFO, "Found proc: "NAME_FIND);
        }
        else
        {
            syslog(LOG_INFO, "Do not found proc: "NAME_FIND);
            system(RUN_NAME);
        }


        cnt++;
        syslog(LOG_INFO, "sshuang monitor run %d times.", cnt);
        sleep(5);
        system("rm "TMP_OUT_FILE);

        sleep(25);
    }

    closelog();

    // printf("%s\n", int2str(get_current_time()).c_str());

    return 0;
}




























