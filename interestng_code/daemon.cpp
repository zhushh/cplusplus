#include <unistd.h>
#include <signal.h>
#include <syslog.h>
#include <sys/stat.h>
#include <sys/types.h>

#include <cstdio>
#include <cstring>
#include <cstdlib>

#include <iostream>

using std::cin;
using std::cout;
using std::endl;

int DaemonInit(void)
{
  pid_t pid;

  if ((pid = fork()) < 0)
  {
    return -1;
  }
  else if (pid != 0)
  {
    exit(0);
  }

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
    syslog(LOG_INFO, "program terminated.");
    closelog();
    exit(0);
  }
}

int main(int argc, char **argv)
{
  cout << "Start..." << endl;

  if (DaemonInit() == -1)
  {
    cout << "Can't fork" << endl;
    exit(0);
  }

  // cat /var/log/message | tail | grep DaemonTest
  openlog("DaemonTest", LOG_PID, LOG_USER);
  syslog(LOG_INFO, "program start.");
  signal(SIGTERM, SigTerm);

  while (true)
  {
    sleep(1);
  }

  return 0;
}