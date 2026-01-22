#include <filemgr.h>

int window_style = DEFAULT;

#include <raylib.h>
#define RAYGUI_IMPLEMENTATION
#include <raygui.h>

int main(int argc, char* const argv[]) {
    SetConfigFlags(FLAG_WINDOW_UNDECORATED);
    InitWindow(800, 450, "FileMgr");
    SetTargetFPS(60);

    Vector2 cursor = { 0 };
    Vector2 window_pos = { 500, 200 };
    Vector2 pan_offset = cursor;
    bool drag_window = false;
    
    SetWindowPosition(window_pos.x, window_pos.y);

    bool exitWindow = false;

    // Initialise all base components
    filemgr_init_all();

    while(!exitWindow) {
        cursor = GetMousePosition();

        if(IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && !drag_window) {
            if(CheckCollisionPointRec(cursor, filemgr_titlebar_bounds)) {
                window_pos = GetWindowPosition();
                drag_window = true;
                pan_offset = cursor;
            }
        }

        if(drag_window) {
            window_pos.x += (cursor.x - pan_offset.x);
            window_pos.y += (cursor.y - pan_offset.y);

            SetWindowPosition((int)window_pos.x, (int)window_pos.y);

            if(IsMouseButtonReleased(MOUSE_LEFT_BUTTON)) drag_window = false;
        }

        ClearBackground(GetColor(GuiGetStyle(window_style, BACKGROUND_COLOR)));

        BeginDrawing();

        // Draw all of the basic window features
        filemgr_draw_base();

        EndDrawing();
    }

    CloseWindow();

    return 0;
}