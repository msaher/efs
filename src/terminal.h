#ifndef TERMINAL_H
#define TERMINAL_H
#include "editor.h"

void set_raw(void);
void refresh_screen(Editor&);
void clear_screen();
#endif
