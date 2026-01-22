#ifndef FILEMGR_FUNCS_H
#define FILEMGR_FUNCS_H

#include "../filemgr.h"

void filemgr_init_all() {
    filemgr_titlebar_init();
}

void filemgr_resize_all() {
    filemgr_titlebar_resize();
}

void filemgr_draw_base() {
    filemgr_titlebar_draw();
}

#endif