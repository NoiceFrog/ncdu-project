#include <curses.h>
#include <dirent.h>
#include <menu.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#define ARRAY_SIZE(b) (sizeof(b) / sizeof(b[0]))

DIR *dir;
struct dirent *ent;
struct stat st;

void init() {
  initscr();
  cbreak();
  noecho();
  keypad(stdscr, TRUE);
};

int main() {
  ITEM **items;
  int ch;
  MENU *f_menu;
  int n_file, e;
  ITEM *cur_item;

  init();

  dir = opendir(".");

  if (dir == NULL) {
    printf("An Error ocurred while opening the current directory! exiting...");
    exit(21);
  }

  int i = 0;

  while ((ent = readdir(dir)) != NULL) {
    // printf("%s\n", ent->d_name);
    i++;
  }
  char *f_names[i];

  closedir(dir);

  dir = opendir(".");
  int j = 0;
  int a;

  while ((ent = readdir(dir)) != NULL) {
    // for (a = 0; ent->d_name[a]; a++)
    //{
    //  smt
    //};
    a = strlen(ent->d_name) + 1;
    f_names[j] = (char *)malloc(++a * sizeof(char));
    // f_names[j] = (char *)ent->d_name;
    strcpy(f_names[j], ent->d_name);
    j++;
  }

  // for (int k = 0; k < i; k++)
  // {
  //     printf("%s\n", f_names[k]);
  // }

  n_file = sizeof(f_names) / sizeof(f_names[0]);
  items = (ITEM **)calloc(n_file + 1, sizeof(ITEM *));

  for (e = 0; e < n_file; ++e) {
    items[e] = new_item(f_names[e], f_names[e]);
  }
  items[n_file] = (ITEM *)NULL;

  f_menu = new_menu((ITEM **)items);
  mvprintw(LINES - 2, 0, "F1 to Exit");
  post_menu(f_menu);
  refresh();

  while ((ch = getch()) != KEY_F(1)) {
    switch (ch) {
    case KEY_DOWN:
      menu_driver(f_menu, REQ_DOWN_ITEM);
      break;
    case KEY_UP:
      menu_driver(f_menu, REQ_UP_ITEM);
      break;
    }
  }

  for (int q = 0; q < i; q++) {
    free_item(items[q]);
  }
  free_menu(f_menu);
  endwin();
  closedir(dir);
  return 0;
}
