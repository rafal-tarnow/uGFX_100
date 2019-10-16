#include <iostream>

#include "opengl_includes.hpp"
#include "frame.hpp"

using namespace std;

void errorCallback(int e, const char *d);
void printOpenGlVersion();

int main()
{
    GLFWwindow *win;
    constexpr int WINDOW_WIDTH = 480;
    constexpr int WINDOW_HEIGHT =  480;

    glfwSetErrorCallback(errorCallback);
    if (!glfwInit())
    {
        cerr << "[GFLW] failed to init!\n" << endl;
        exit(EXIT_FAILURE);
    }

    // OPEN GL ES
    glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_ES_API);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);

    win = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, __FILE__, NULL, NULL);
    //glfwSetWindowPos(win, 1920*(0.5) - WINDOW_WIDTH/2, 1080*(0.95) - WINDOW_HEIGHT/2);
    glfwMakeContextCurrent(win);
    glfwSwapInterval(1);

    printOpenGlVersion();

    frame_init();

    while (!glfwWindowShouldClose(win))
    {
        glfwPollEvents();

        frame_render(WINDOW_WIDTH, WINDOW_HEIGHT);

        glfwSwapBuffers(win);
    }

    glfwTerminate();
    cout << "EXIT_SUCCESS!" << endl;
    return EXIT_SUCCESS;
}

void printOpenGlVersion()
{
    cout << "GL_VENDOR  : " << glGetString(GL_VENDOR) << endl;
    cout << "GL_RENDERER : " << glGetString(GL_RENDERER) << endl;
    cout << "GL_VERSION  : " << glGetString(GL_VERSION) << endl;
    cout << "GL_SHADING_LANGUAGE_VERSION  : " << glGetString(GL_SHADING_LANGUAGE_VERSION) << endl;
    cout << "GL_EXTENSIONS  : " << glGetString(GL_EXTENSIONS) << endl;
}

void errorCallback(int e, const char *d)
{
    cerr << "Error " << e << d << endl;
    exit(EXIT_FAILURE);
}
