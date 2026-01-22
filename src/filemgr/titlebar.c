#include <filemgr/titlebar.h>

Rectangle filemgr_titlebar_bounds;

void filemgr_titlebar_init() {
    filemgr_titlebar_bounds = (Rectangle) { 0, 0, 0, 20 };
    filemgr_titlebar_resize();
}

void filemgr_titlebar_resize() {
    filemgr_titlebar_bounds.width = GetRenderWidth();
}

void filemgr_titlebar_draw() {
    Color c = GetColor(GuiGetStyle(window_style, BACKGROUND_COLOR));
    c.r -= 10;
    c.g -= 10;
    c.b -= 10;

    DrawRectangle(
        filemgr_titlebar_bounds.x,
        filemgr_titlebar_bounds.y,
        filemgr_titlebar_bounds.width,
        filemgr_titlebar_bounds.height,
        c
    );

    DrawLine(
        filemgr_titlebar_bounds.x,
        filemgr_titlebar_bounds.y + filemgr_titlebar_bounds.height - 1,
        filemgr_titlebar_bounds.x + filemgr_titlebar_bounds.width,
        filemgr_titlebar_bounds.y + filemgr_titlebar_bounds.height - 1,
        GetColor(GuiGetStyle(window_style, BORDER_COLOR_NORMAL))
    );
}