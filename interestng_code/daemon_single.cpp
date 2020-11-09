#include <unistd.h>
#include <sys/file.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <signal.h>

#include <cstdio>
#include <cstring>
#include <cstdlib>

#include <iostream>
using std::cin;
using std::cout;
using std::endl;

int lock_fd; // 文件锁
const char kDaemonLockFile[] = "daemon_single_test.lock";

int DaemonInit(void)
{
  pid_t pid;
  if ((pid = fork()) < 0)
  {
    return -1;
  }
  else if (pid != 0)
  {
    exit(0); // parent exit
  }

  cout << "Daemon start" << endl;

  setsid(); // become session leader
  umask(0); // clear file mode createtion mask
  close(0); // close stdin
  close(1); // close stdout
  close(2); // close stderr
  return 0;
}

void SigTerm(int signo)
{
  if (signo == SIGTERM)
  {
    //解锁
    int ret = flock(lock_fd, LOCK_UN);
    if (ret < 0)
    {
      perror("flock unlock err");
    }

    close(lock_fd);
    exit(0);
  }
}

int main(int argc, char **argv)
{
  cout << "program start." << endl;

  lock_fd = open(kDaemonLockFile, O_CREAT | O_RDONLY, 0664);
  if (lock_fd < 0)
  {
    cout << "Open file:" << kDaemonLockFile << " fail." << endl;
    exit(1);
  }

  // 加锁，LOCK_NB 参数表示非阻塞模式，如果文件被其他进程加所，会返回错误
  int ret = flock(lock_fd, LOCK_EX | LOCK_NB);
  if (ret < 0)
  {
    cout << "Lock file:" << kDaemonLockFile << " fail." << endl;
    exit(ret);
  }

  if ((ret = DaemonInit()) < 0)
  {
    exit(ret);
  }

  signal(SIGTERM, SigTerm);

  while (true)
  {
    sleep(1);
  }

  return 0;
}