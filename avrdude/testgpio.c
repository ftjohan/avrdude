#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <linux/types.h>

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include <sys/stat.h>

void printstat(char *fn) {

  struct stat fileStat;
  stat(fn,&fileStat);
  
  fprintf(stderr, "Stat (");
  fprintf(stderr, (S_ISDIR(fileStat.st_mode)) ? "d" : "-");
  fprintf(stderr, (fileStat.st_mode & S_IRUSR) ? "r" : "-");
  fprintf(stderr, (fileStat.st_mode & S_IWUSR) ? "w" : "-");
  fprintf(stderr, (fileStat.st_mode & S_IXUSR) ? "x" : "-");
  fprintf(stderr, (fileStat.st_mode & S_IRGRP) ? "r" : "-");
  fprintf(stderr, (fileStat.st_mode & S_IWGRP) ? "w" : "-");
  fprintf(stderr, (fileStat.st_mode & S_IXGRP) ? "x" : "-");
  fprintf(stderr, (fileStat.st_mode & S_IROTH) ? "r" : "-");
  fprintf(stderr, (fileStat.st_mode & S_IWOTH) ? "w" : "-");
  fprintf(stderr, (fileStat.st_mode & S_IXOTH) ? "x" : "-");
  fprintf(stderr, ")   %s\n", fn);
}

void testwrite(char *fn, char *val) {

  FILE* f = fopen(fn, "w");

  if (f  == NULL) {
    fprintf(stderr, "Open file failed    %s\n", fn);
  } else {
    fprintf(stderr, "Opened file ok      %s\n", fn);	  

    if (fprintf(f, "%s", val) < 0) {
      fprintf(stderr, "Writing failed      %s %s\n", fn, val);
    } else {
      fprintf(stderr, "Writing ok          %s %s\n", fn, val);  
    }	
	fclose(f);
  }
  fprintf(stderr, "\n");  
}

void testfile(char *fn, char *val) {
  printstat(fn);
  testwrite(fn,val);	
}

int main(int argc, char * argv []){

  mode_t mask = umask(0);
  umask(mask);
  fprintf(stderr, "Umask: %d\n\n",mask);
  
  testfile("/sys/class/gpio/export", "30");
  testfile("/sys/class/gpio/gpio30/direction", "out");
  testfile("/sys/class/gpio/gpio30/value", "0");
  sleep(1);
  testfile("/sys/class/gpio/gpio30/value", "1");
  testfile("/sys/class/gpio/gpio30/direction", "in");
  /* testfile("/sys/class/gpio/unexport", "30"); */
}
