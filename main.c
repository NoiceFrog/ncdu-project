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

struct directory_entry {
  char file_name[500];
  uint32_t file_size_bytes;
  struct directory_entry *next_entry;
};

int main() {

  dir = opendir("."); // open current directory

  if (dir ==
      NULL) { // if the dir variable returns null it means there is a problem
    printf("Error opening directory.\n");
    return 1; // exit the program with exit code 1
  }

  printf("DT_REG %d\n", DT_REG);

  struct directory_entry my_directory_listing;
  struct directory_entry *entry = &my_directory_listing;

  while ((ent = readdir(dir)) != NULL) {
    file_count++;
    if (ent->d_type == DT_REG) {
      printf("File: %s\n", ent->d_name);
      strncpy(entry->file_name, ent->d_name, sizeof(entry->file_name));
      uint32_t file_size = 0; // TODO figure out how to get file size in bytes
      entry->file_size_bytes = file_size;
      entry->next_entry = malloc(sizeof(struct directory_entry));
      entry = entry->next_entry;
      if (entry == NULL) {
        printf("PANIC!\n");
        exit(23);
      }
      entry->next_entry = NULL;

    } else if (ent->d_type == DT_DIR) {
      printf("Dir: %s\n", ent->d_name);
    }
  }

  printf("\nFiles in directory:\n");
  entry = &my_directory_listing;
  while(entry) {
    printf("%s\n", entry->file_name);
    entry = entry->next_entry;
  }

  mainU();

  if (closedir(dir) == -1) { // if the program fails closing the directory it
                             // means there is a problem
    printf("Error closing directory.\n");
    return 1; // exit the program with exit code 1
  }
  return 0;
}
