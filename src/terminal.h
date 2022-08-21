#ifndef TERMINAL_H
#define TERMINAL_H
#include "editor.h"

void set_raw(void);
void refresh_screen(Editor&);
void cleanup_term();
void window_size(unsigned int&, unsigned int&);
#endif
