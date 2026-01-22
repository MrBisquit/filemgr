#ifndef FILEMGR_TITLEBAR_H
#define FILEMGR_TITLEBAR_H

#include "ray.h"
#include "globals.h"

//#include <raylib.h>
//#include <raygui.h>

/*
    The titlebar will contain tabs, a settings button, and the minimise, maximise/restore,
    and close buttons.
*/

// Defines
extern Rectangle filemgr_titlebar_bounds;

// Functions
void filemgr_titlebar_init(void);
void filemgr_titlebar_resize(void);
void filemgr_titlebar_draw(void);

#endif