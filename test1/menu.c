#include "main.h"
#include <curses.h>
#include <menu.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// #define ARRAY_SIZE(a) (sizeof(a) / sizeof(a[0]))
// #define CTRLD 4

int mainU()
{
  ITEM **my_items;
  int c;
  MENU *my_menu;
  int i;
  ITEM *cur_item;

  /* Initialize curses */
  initscr();
  cbreak();
  noecho();
  keypad(stdscr, TRUE);

  /* Initialize items */
  // file_count = ARRAY_SIZE(file_names);
  my_items = (ITEM **)calloc(file_count + 1, sizeof(ITEM *));
  for (i = 0; i < file_count; ++i)
    my_items[i] = new_item(file_infos.name, file_infos.name);
  my_items[file_count] = (ITEM *)NULL;

  my_menu = new_menu((ITEM **)my_items);

  /* Make the menu multi valued */
  menu_opts_off(my_menu, O_ONEVALUE);

  mvprintw(LINES - 3, 0, "Use <SPACE> to select or unselect an item.");
  mvprintw(LINES - 2, 0, "<ENTER> to see presently selected items(F1 to Exit; CTRL+c also works :) )");
  post_menu(my_menu);
  refresh();

  while ((c = getch()) != KEY_F(1))
  {
    switch (c)
    {
    case KEY_DOWN:
      menu_driver(my_menu, REQ_DOWN_ITEM);
      break;
    case KEY_UP:
      menu_driver(my_menu, REQ_UP_ITEM);
      break;
    case ' ':
      menu_driver(my_menu, REQ_TOGGLE_ITEM);
      break;
    case 10: /* Enter */
    {
      char temp[200];
      ITEM **items;

      items = menu_items(my_menu);
      temp[0] = '\0';
      for (i = 0; i < item_count(my_menu); ++i)
        if (item_value(items[i]) == TRUE)
        {
          strcat(temp, item_name(items[i]));
          strcat(temp, " ");
        }
      move(20, 0);
      clrtoeol();
      mvprintw(20, 0, temp);
      refresh();
    }
    break;
    }
  }

  free_item(my_items[0]);
  free_item(my_items[1]);
  free_menu(my_menu);
  endwin();
  return 0;
}
