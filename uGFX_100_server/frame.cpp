#include <iostream>

#include "frame.hpp"
#include "opengl_includes.hpp"
#include "glm_includes.hpp"
#include "camera.hpp"



using namespace std;


//#include "esUtil.h"
typedef struct
{
    // Handle to a program object
    GLuint programObject;
} UserData;

///
// Create a shader object, load the shader source, and
// compile the shader.
//

GLuint LoadShader(const GLchar *shaderSrc, GLenum type)
{
    GLuint shader;
    GLint compiled;

    // Create the shader object
    shader = glCreateShader(type);

    if(shader == 0)
        return 0;

    // Load the shader source
    glShaderSource(shader, 1, &shaderSrc, NULL);

    // Compile the shader
    glCompileShader(shader);

    // Check the compile status
    glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);

    if(!compiled)
    {
        GLint infoLen = 0;
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLen);

        if(infoLen > 1)
        {
            char* infoLog = new char[infoLen]();
            glGetShaderInfoLog(shader, infoLen, NULL, infoLog);
            cerr << "Error compiling shader:" << infoLog << endl;
            delete [] infoLog;
        }
        glDeleteShader(shader);
        return 0;
    }
    return shader;
}

UserData data;

///
// Initialize the shader and program object
//
bool Init()
{
    UserData *userData = &data;
    GLchar vShaderStr[] =
            "#version 100                   \n"
            "attribute vec4 vPosition;      \n"
            "                               \n"
            "uniform mat4 M;                \n"
            "uniform mat4 V;                \n"
            "uniform mat4 P;                \n"
            "                               \n"
            "void main()                    \n"
            "{                              \n"
            "   gl_Position = P*V*M*vPosition; \n"
            "}                              \n";

    GLchar fShaderStr[] =
            "precision mediump float;                   \n"
            "void main()                                \n"
            "{                                          \n"
            "  gl_FragColor = vec4(1.0, 0.0, 0.0, 1.0); \n"
            "}                                          \n";

    GLuint vertexShader;
    GLuint fragmentShader;
    GLuint programObject;
    GLint linked;

    // Load the vertex/fragment shaders
    vertexShader = LoadShader(vShaderStr, GL_VERTEX_SHADER);
    fragmentShader = LoadShader(fShaderStr, GL_FRAGMENT_SHADER);

    // Create the program object
    programObject = glCreateProgram();
    if(programObject == 0)
        return 0;

    glAttachShader(programObject, vertexShader);
    glAttachShader(programObject, fragmentShader);

    // Bind vPosition to attribute 0
    glBindAttribLocation(programObject, 0, "vPosition");

    // Link the program
    glLinkProgram(programObject);

    // Check the link status
    glGetProgramiv(programObject, GL_LINK_STATUS, &linked);
    if(!linked)
    {
        GLint infoLen = 0;
        glGetProgramiv(programObject, GL_INFO_LOG_LENGTH, &infoLen);
        if(infoLen > 1)
        {
            char* infoLog = new char[infoLen]();
            glGetProgramInfoLog(programObject, infoLen, NULL, infoLog);
            cerr << "Error linking program: " << infoLog << endl;
            delete[] infoLog;
        }
        glDeleteProgram(programObject);
        return false;
    }

    // Store the program object
    userData->programObject = programObject;
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    return true;
}

///
// Draw a triangle using the shader pair created in Init()
//
void Draw(int width, int height)
{

    UserData *userData = &data;
    GLfloat vVertices[] = {0.0f,  0.5f, 0.0f,
                           -0.5f, -0.5f, 0.0f,
                           0.5f, -0.5f,  0.0f};


    glm::mat4 P = glm::mat4(1);
    glm::mat4 V = glm::mat4(1);
    glm::mat4 M = glm::mat4(1);
    static float angle = 0.0f;
    angle += 0.07f;
    M = glm::rotate(M,angle, glm::vec3(0,0,1));

    // Set the viewport
    glViewport(0, 0, width, height);

    // Clear the color buffer
    glClear(GL_COLOR_BUFFER_BIT);

    // Use the program object
    glUseProgram(userData->programObject);
    {
        glUniformMatrix4fv( glGetUniformLocation(userData->programObject, "P"), 1, GL_FALSE, glm::value_ptr(P));
        glUniformMatrix4fv( glGetUniformLocation(userData->programObject, "V"), 1, GL_FALSE, glm::value_ptr(V));
        glUniformMatrix4fv( glGetUniformLocation(userData->programObject, "M"), 1, GL_FALSE, glm::value_ptr(M));

        // Load the vertex data
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, vVertices);
        glEnableVertexAttribArray(0);
        glDrawArrays(GL_TRIANGLES, 0, 3);
    }
}

void frame_init()
{
    Init();
}

void frame_render(int width, int height)
{
    Draw(width, height);
}
