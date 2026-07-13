#pragma once

struct ControlsState {
    bool press_left_mouse = false;
    bool press_right_mouse = false;
    bool press_middle_mouse = false;

    bool click_left_mouse = false;

    bool move_forwards = false;
    bool move_backwards = false;
    bool move_left = false;
    bool move_right = false;

    bool run = false;
    bool fly = false;
    bool open_inventory = false;
    bool drop = false;
    bool open_chat = false;
    bool jump = false;
    bool crouch = false;

    bool press_escape = false;
    bool press_exit = false;

    float move_mouse_du = 0.0F;
    float move_mouse_dv = 0.0F;  

    bool toggle_flying = false;

    bool title_to_simulation = false;
    bool simulation_to_title = false;
};
