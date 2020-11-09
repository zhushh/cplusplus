#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>

int LockFile(int fd)
{
  struct flock flk;
  flk.l_type = F_WRLCK;
  flk.l_start = 0;
  flk.l_whence = SEEK_SET;
  flk.l_len = 0;

  // 非阻塞式加锁
  return fcntl(fd, F_SETLK, &flk);
}

int AlreadyRunning(void)
{
  int fd;
  char buf[32];

  // 打开日志文件
  FILE *fp = fopen("/tmp/daemon_single_upgrade.log", "a");
  if (fp == NULL)
  {
    perror("fopen");
    return -1;
  }

  // 锁文件
  fd = open("/var/run/daemon_signle_upgrade.pid", O_RDWR | O_CREAT, 0644);
  if (fd < 0)
  {
    fprintf(fp, "can't open /var/run/daemon_signle_upgrade.pid: %s\n", strerror(errno));
    fclose(fp);
    exit(1);
  }

  if (LockFile(fd) < 0)
  {
    // 已锁住
    if (errno == EACCES || errno == EAGAIN)
    {
      fprintf(fp, "daemon_signle_upgrade already running: %s\n", strerror(errno));
      close(fd);
      fclose(fp);
      return 1;
    }

    fprintf(fp, "can't lock /var/run/daemon_signle_upgrade.pid: %s\n", strerror(errno));
    fclose(fp);
    exit(1);
  }

  ftruncate(fd, 0); // 截断成0
  sprintf(buf, "%d", getpid());
  write(fd, buf, strlen(buf) + 1);
  return 0;
}

int main()
{
  if (daemon(0, 0) < 0)
  {
    perror("daemon");
    return -1;
  }

  if (AlreadyRunning())
  {
    return -1;
  }

  while (true)
  {
    sleep(10);

    // do someting here
  }

  return 0;
}