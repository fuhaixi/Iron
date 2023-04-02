#include "os.h"

const char* OS::glsl_version = "#version 330";
OS * OS::instance = NULL;
double OS::time = 0;
double OS::delta_time = 0;
double OS::last_time = -0.02;
vec2 OS::cursor_pos = vec2();
vec2 OS::cursor_relative = vec2();
vec2 OS::last_cursor_pos = vec2();


void OS::glfw_window_init(){
    glfwInit();

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    glfw_window = glfwCreateWindow(window_size.x, window_size.y, "My Title", NULL, NULL);
    if (!glfw_window)
    {
        fprintf(stderr, "ERROR: glfw_window or OpenGL context creation failed");
    }
    glfwMakeContextCurrent(glfw_window);
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return;
    }

    glfwSwapInterval(1); // Enable vsync
    //init imgui
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(glfw_window, true);
    ImGui_ImplOpenGL3_Init(glsl_version);


    printf("%s\n", glGetString(GL_VERSION));
}

void OS::cursor_position_callback(GLFWwindow* window, double xpos, double ypos){
    instance->cursor.pos = vec2(xpos, ypos);
    instance->cursor.offset = instance->cursor.pos - instance->cursor.last_pos;
    instance->cursor.last_pos = instance->cursor.pos;

    ImGui_ImplGlfw_CursorPosCallback(window, xpos, ypos);
}

void OS::glfw_key_callback(GLFWwindow* window, int key, int scancode, int action, int mods){
    instance->key_callback(key, scancode, action, mods);
    
    ImGui_ImplGlfw_KeyCallback(window, key, scancode, action, mods);
}

void OS::error_callback(int error, const char* description)
{
    fprintf(stderr, "Error: %s\n", description);
    
}

    


OS::OS(int width, int height ){
    if(instance != NULL) free(instance);

    window_size.x = width;
    window_size.y = height;

    default_frame.gid = 0;
    default_frame.size = window_size;
    
    window_aspect = window_size.aspect();
    instance = this;
    glfwSetErrorCallback(error_callback);
    glfw_window_init();
    glfwSetKeyCallback(glfw_window, glfw_key_callback);

    glfwSetCursorPosCallback(glfw_window, cursor_position_callback);
}

void OS::set_key_callback(void (*call_back)(int,int,int,int)){
    key_callback = call_back;
    glfwSetKeyCallback(glfw_window, glfw_key_callback);

}

bool OS::is_window_open(){
    return !glfwWindowShouldClose(glfw_window);
}

OS::~OS(){
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    glfwDestroyWindow(glfw_window);
    glfwTerminate();
}

double OS::getTime(){
    return glfwGetTime();
}

bool OS::get_key(int key){
    
    return glfwGetKey(instance->glfw_window, key);
}

vec2 OS::get_cursor_pos(){;

    double x,y;
    glfwGetCursorPos(instance->glfw_window,&x,&y);
    return vec2(x,y);

}

void OS::frame_begin(){
    glfwPollEvents();

    //start imgui
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();


    time = glfwGetTime();
    delta_time = time - last_time;

    cursor_pos = get_cursor_pos();
    cursor_relative = cursor_pos - last_cursor_pos;
}

void OS::frame_end(){
    last_time = time;
    last_cursor_pos = cursor_pos;

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    glfwGetFramebufferSize(instance->glfw_window, &instance->window_size.x, &instance->window_size.y);
    instance->default_frame.size = instance->window_size;
    instance->window_aspect = instance->window_size.aspect();
    glfwSwapBuffers(instance->glfw_window);


}



bool OS::get_mouse_button(int button){
    int ret = glfwGetMouseButton(instance->glfw_window, button);
    
    return ret;
}

