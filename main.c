#include "menu.h"
#include <curses.h>
#include <dirent.h>
#include <menu.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>

DIR *dir;
struct dirent *ent;
int file_count = 0;

int main() {

  dir = opendir("."); // open current directory

  if (dir ==
      NULL) { // if the dir variable returns null it means there is a problem
    printf("Error opening directory.\n");
    return 1; // exit the program with exit code 1
  }

  printf("DT_REG %d\n", DT_REG);

  while ((ent = readdir(dir)) != NULL) {
    file_count++;
    if (ent->d_type == DT_REG) {
      printf("File: %s\n", ent->d_name);
    } else if (ent->d_type == DT_DIR) {
      printf("Dir: %s\n", ent->d_name);
    }
  }

  mainU();

  if (closedir(dir) == -1) { // if the program fails closing the directory it
                             // means there is a problem
    printf("Error closing directory.\n");
    return 1; // exit the program with exit code 1
  }
  return 0;
}
