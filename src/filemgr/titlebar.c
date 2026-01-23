#include <filemgr/titlebar.h>

Rectangle filemgr_titlebar_bounds;
Rectangle filemgr_titlebar_close_btn_bounds;
Rectangle filemgr_titlebar_max_btn_bounds;
Rectangle filemgr_titlebar_min_btn_bounds;

void filemgr_titlebar_init() {
    filemgr_titlebar_bounds = (Rectangle) { 0, 0, 0, 30 };
    filemgr_titlebar_close_btn_bounds = (Rectangle) { 0, 0, 0, 0 };
    filemgr_titlebar_max_btn_bounds = (Rectangle) { 0, 0, 0, 0 };
    filemgr_titlebar_min_btn_bounds = (Rectangle) { 0, 0, 0, 0 };

    filemgr_titlebar_resize();
}

void filemgr_titlebar_resize() {
    int w = IsWindowMaximized() ? GetScreenWidth() : GetRenderWidth();

    filemgr_titlebar_bounds.width = w;

    filemgr_titlebar_close_btn_bounds.width = 40;
    filemgr_titlebar_close_btn_bounds.height = filemgr_titlebar_bounds.height - 1;
    filemgr_titlebar_close_btn_bounds.x = w - filemgr_titlebar_close_btn_bounds.width;

    filemgr_titlebar_max_btn_bounds.width = 40;
    filemgr_titlebar_max_btn_bounds.height = filemgr_titlebar_bounds.height - 1;
    filemgr_titlebar_max_btn_bounds.x = w - (filemgr_titlebar_max_btn_bounds.width * 2);

    filemgr_titlebar_min_btn_bounds.width = 40;
    filemgr_titlebar_min_btn_bounds.height = filemgr_titlebar_bounds.height - 1;
    filemgr_titlebar_min_btn_bounds.x = w - (filemgr_titlebar_min_btn_bounds.width * 3);
}

void filemgr_titlebar_draw() {
    Color c = GetColor(GuiGetStyle(window_style, BACKGROUND_COLOR));
    c.r -= 10;
    c.g -= 10;
    c.b -= 10;

    Color c_b;

    if(IsWindowFocused())
        c_b = GetColor(GuiGetStyle(window_style, BORDER_COLOR_NORMAL));
    else
        c_b = GetColor(GuiGetStyle(window_style, BORDER_COLOR_DISABLED));

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
        c_b
    );

    int max_icon = IsWindowMaximized() ? 221 : 222;
    int min_icon = 220;

    Vector2 cursor = GetMousePosition();
    bool focused = IsWindowFocused();

    // Draw the buttons on the right
    Color close_color;
    Color max_color;
    Color min_color;
    Color icons_color = GetColor(GuiGetStyle(window_style, TEXT_COLOR_NORMAL));

    if(!focused) {
        icons_color = GetColor(GuiGetStyle(window_style, TEXT_COLOR_DISABLED));
    }

    const char* close_text = GuiIconText(ICON_CROSS, "");
    const char* max_text = GuiIconText(max_icon, "");
    const char* min_text = GuiIconText(min_icon, "");

    if(CheckCollisionPointRec(cursor, filemgr_titlebar_close_btn_bounds) && focused) {
        if(IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
            close_color = GetColor(GuiGetStyle(window_style, BASE_COLOR_PRESSED));
        } else {
            close_color = GetColor(GuiGetStyle(window_style, BASE_COLOR_FOCUSED));
        }

        if(IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) {
            should_exit = true;
        }
    } else {
        //close_color = GetColor(GuiGetStyle(window_style, BASE_COLOR_NORMAL));
        close_color = c;
    }

    if(CheckCollisionPointRec(cursor, filemgr_titlebar_max_btn_bounds) && focused) {
        if(IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
            max_color = GetColor(GuiGetStyle(window_style, BASE_COLOR_PRESSED));
        } else {
            max_color = GetColor(GuiGetStyle(window_style, BASE_COLOR_FOCUSED));
        }

        if(IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) {
            if(IsWindowMaximized())
                RestoreWindow();
            else
                MaximizeWindow();

            filemgr_resize_all();
        }
    } else {
        //max_color = GetColor(GuiGetStyle(window_style, BASE_COLOR_NORMAL));
        max_color = c;
    }

    if(CheckCollisionPointRec(cursor, filemgr_titlebar_min_btn_bounds) && focused) {
        if(IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
            min_color = GetColor(GuiGetStyle(window_style, BASE_COLOR_PRESSED));
        } else {
            min_color = GetColor(GuiGetStyle(window_style, BASE_COLOR_FOCUSED));
        }

        if(IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) {
            MinimizeWindow();
        }
    } else {
        //min_color = GetColor(GuiGetStyle(window_style, BASE_COLOR_NORMAL));
        min_color = c;
    }

    DrawRectangleRec(filemgr_titlebar_close_btn_bounds, close_color);
    GuiDrawIcon(
        ICON_CROSS,
        filemgr_titlebar_close_btn_bounds.x + (filemgr_titlebar_close_btn_bounds.width / 2) - (16 / 2),
        filemgr_titlebar_close_btn_bounds.y + (filemgr_titlebar_close_btn_bounds.height / 2) - (16 / 2),
        1,
        icons_color
    );

    /*DrawText(
        close_text,
        filemgr_titlebar_close_btn_bounds.x + (filemgr_titlebar_close_btn_bounds.width / 2) - (10 / 2),
        filemgr_titlebar_close_btn_bounds.y + (filemgr_titlebar_close_btn_bounds.height / 2) - (10 / 2),
        10,
        GetColor(GuiGetStyle(window_style, TEXT_COLOR_NORMAL))
    );*/

    DrawRectangleRec(filemgr_titlebar_max_btn_bounds, max_color);
    GuiDrawIcon(
        max_icon,
        filemgr_titlebar_max_btn_bounds.x + (filemgr_titlebar_max_btn_bounds.width / 2) - (16 / 2),
        filemgr_titlebar_max_btn_bounds.y + (filemgr_titlebar_max_btn_bounds.height / 2) - (16 / 2),
        1,
        icons_color
    );

    /*DrawText(
        max_text,
        filemgr_titlebar_max_btn_bounds.x + (filemgr_titlebar_max_btn_bounds.width / 2) - (10 / 2),
        filemgr_titlebar_max_btn_bounds.y + (filemgr_titlebar_max_btn_bounds.height / 2) - (10 / 2),
        10,
        GetColor(GuiGetStyle(window_style, TEXT_COLOR_NORMAL))
    );*/

    DrawRectangleRec(filemgr_titlebar_min_btn_bounds, min_color);
    GuiDrawIcon(
        min_icon,
        filemgr_titlebar_min_btn_bounds.x + (filemgr_titlebar_min_btn_bounds.width / 2) - (16 / 2),
        filemgr_titlebar_min_btn_bounds.y + (filemgr_titlebar_min_btn_bounds.height / 2) - (16 / 2),
        1,
        icons_color
    );

    /*DrawText(
        min_text,
        filemgr_titlebar_min_btn_bounds.x + (filemgr_titlebar_min_btn_bounds.width / 2) - (10 / 2),
        filemgr_titlebar_min_btn_bounds.y + (filemgr_titlebar_min_btn_bounds.height / 2) - (10 / 2),
        10,
        GetColor(GuiGetStyle(window_style, TEXT_COLOR_NORMAL))
    );*/

    //int close = GuiButton(filemgr_titlebar_close_btn_bounds, GuiIconText(ICON_CROSS, ""));
    //int max = GuiButton(filemgr_titlebar_max_btn_bounds, GuiIconText(max_icon, ""));
    //int min = GuiButton(filemgr_titlebar_min_btn_bounds, GuiIconText(min_icon, ""));
}

bool filemgr_titlebar_hit(Vector2 cursor) {
    if(CheckCollisionPointRec(cursor, filemgr_titlebar_close_btn_bounds) ||
        CheckCollisionPointRec(cursor, filemgr_titlebar_max_btn_bounds) ||
        CheckCollisionPointRec(cursor, filemgr_titlebar_min_btn_bounds))
        return true;
    else
        return false;
}