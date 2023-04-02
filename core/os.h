#ifndef IRON_OS
#define IRON_OS
#include"core_structure.h"
#include"gpu_structure.h"
#include "iron_gl.h"
#include<GLFW/glfw3.h>

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

struct Cursor
{
    vec2 last_pos;
    vec2 pos;
    vec2 velocity;
    vec2 offset;
    bool click;
};

struct Window
{
    int width;
    int height;
    float ratio;
};



class OS
{
public:
    static OS* instance;
    Cursor cursor;
    static vec2 cursor_pos;
    static double delta_time;
    static vec2 cursor_relative;
    static double time;
    //int key, int scancode, int action, int mods
    void (*key_callback) (int, int,int,int);
    vec2i window_size;
    vec2i renderbuff_size;
    float window_aspect;
    Rframebuff default_frame;


private:
    static double last_time;
    static vec2 last_cursor_pos;
    GLFWwindow * glfw_window;
    static const char* glsl_version;

    void glfw_window_init();

    static void cursor_position_callback(GLFWwindow* window, double xpos, double ypos);
    static void glfw_key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);

    static void error_callback(int error, const char* description);

    
    
public:
    
    
    OS(int width = 800, int height = 600);
    ~OS();

    void set_key_callback(void (*call_back)(int,int,int,int));

    bool is_window_open();

    static double getTime();

    static bool get_key(int key);

    static vec2 get_cursor_pos();

    static void frame_begin();

    static void frame_end();

    static bool get_mouse_button(int button);



    static bool should_close(){
        return glfwWindowShouldClose(instance->glfw_window);

    }

};




#endif