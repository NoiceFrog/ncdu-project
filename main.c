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

struct file_info
{
  char name[256];
  int size_bytes;
};

int main()
{

  dir = opendir("."); // open current directory

  if (dir ==
      NULL)
  { // if the dir variable returns null it means there is a problem
    printf("Error opening directory.\n");
    return 1; // exit the program with exit code 1
  }

  while ((ent = readdir(dir)) != NULL)
  {
    file_count++;
    struct file_info file_infos;
    strncpy(file_infos.name, ent->d_name, sizeof(file_infos.name));
    file_infos.size_bytes = ent->d_ino;
  }

  mainU();

  if (closedir(dir) == -1)
  { // if the program fails closing the directory it
    // means there is a problem
    printf("Error closing directory.\n");
    return 1; // exit the program with exit code 1
  }
  return 0;
}
