#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <fcntl.h>

static void sighandler(int i) {
  if (i == SIGINT) {
    int fd = open("exit.txt", O_APPEND | O_RDWR);
    write(fd, "Program exited due to SIGINT\n", 30);
    close(fd);
    printf("Program exited\nMore info in \"exit.txt\"\n");
    exit(0);
  }

  else if (i == SIGUSR1) {
    printf("Program did not exit due to SIGUSR1 but here's the parent PID to make you feel better about it: %d\n", getppid());
  }
}

int main() {
  while(1) {
    printf("Hey nice to meet you I'm %d\n", getpid());
    sleep(1);
    signal(SIGINT, sighandler);
    signal(SIGUSR1, sighandler);
  }
}
