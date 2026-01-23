#include <filemgr.h>

#include <raylib.h>
#define RAYGUI_IMPLEMENTATION
#include <raygui.h>

int should_exit = false;
int window_style = DEFAULT;
//char** normal_icons = NULL;
//char** custom_icons = NULL;

int main(int argc, char* const argv[]) {
    SetConfigFlags(FLAG_WINDOW_UNDECORATED);
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(800, 450, "FileMgr");
    SetTargetFPS(60);

    Vector2 cursor = { 0 };
    Vector2 window_pos = { 500, 200 };
    Vector2 pan_offset = cursor;
    bool drag_window = false;
    
    SetWindowPosition(window_pos.x, window_pos.y);

    bool exit_window = false;

    //normal_icons = GuiLoadIcons(NULL, false);
    char** custom_icons = GuiLoadIcons("iconset.rgi", false);

    // Initialise all base components
    filemgr_init_all();

    while(!exit_window && !should_exit) {
        cursor = GetMousePosition();

        if(IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && !drag_window) {
            if(IsWindowMaximized()) {
                RestoreWindow();
                filemgr_resize_all();

                window_pos.x = (cursor.x - pan_offset.x);
                window_pos.y = (cursor.y - pan_offset.y);

                SetWindowPosition((int)window_pos.x, (int)window_pos.y);

                pan_offset = cursor;
                drag_window = true;
            }

            if(CheckCollisionPointRec(cursor, filemgr_titlebar_bounds) && !filemgr_titlebar_hit(cursor)) {
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