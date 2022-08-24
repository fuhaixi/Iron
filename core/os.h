#include"core_structure.h"
#include<GLFW/glfw3.h>
#include <driver/gl.h>

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
    Window window;
    vec2 cursor_pos;


private:
    GLFWwindow * glfw_window;

    void glfw_window_init(){
        glfwInit();

        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
        glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_ES_API);
        glfw_window = glfwCreateWindow(480, 480, "My Title", NULL, NULL);
        if (!glfw_window)
        {
            fprintf(stderr, "ERROR: glfw_window or OpenGL context creation failed");
        }
        glfwMakeContextCurrent(glfw_window);
        gladLoadGLLoader((GLADloadproc) glfwGetProcAddress);
        

        printf("%s\n", glGetString(GL_VERSION));
    }

    static void cursor_position_callback(GLFWwindow* window, double xpos, double ypos){
        instance->cursor.pos = vec2(xpos, ypos);
        instance->cursor.offset = instance->cursor.pos - instance->cursor.last_pos;
        instance->cursor.last_pos = instance->cursor.pos;
    }

    static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode){
        // printf("k:%d, scancode:%d", key, scancode);
    }

    static void error_callback(int error, const char* description)
    {
        fprintf(stderr, "Error: %s\n", description);
    }

    
    
public:
    
    
    OS(/* args */){
        if(instance != NULL) free(instance);

        instance = this;
        glfwSetErrorCallback(error_callback);
        glfw_window_init();
        glfwSetKeyCallback(glfw_window, key_callback);
        glfwSetCursorPosCallback(glfw_window, cursor_position_callback);
    }

    ~OS(){
        glfwDestroyWindow(glfw_window);
        glfwTerminate();
    }

    static double getTime(){
        return glfwGetTime();
    }

    static void swap_buffers(){
        glfwSwapBuffers(instance->glfw_window);
    }

    static void get_frame_buffer(){
        glfwGetFramebufferSize(instance->glfw_window, &instance->window.width, &instance->window.height);

    }

    static void poll_event(){
        glfwPollEvents();

    }

    static bool get_key(int key){
        return glfwGetKey(instance->glfw_window, key);
    }

    static vec2 get_cursor_pos(){;

        double x,y;
        glfwGetCursorPos(instance->glfw_window,&x,&y);
        return vec2(x,y);

    }

    static bool get_mouse_button(int button){
        int ret = glfwGetMouseButton(instance->glfw_window, button);
        
        return ret;
    }

};


OS * OS::instance = NULL;