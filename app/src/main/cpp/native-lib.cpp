#include <GLES3/gl3.h>
#include <SDL.h>

const GLchar* vertexSource =
        R"shader(#version 300 es
precision mediump float;

layout (location = 0) in vec2 position;
layout (location = 1) in vec3 color;
out vec2 _position;
out vec3 _color;

void main()
{
    gl_Position = vec4(position, 0.0, 1.0);
    _position = position;
    _color = color;
}
)shader";

const GLchar* fragmentSource =
        R"shader(#version 300 es
precision mediump float;

out vec4 color;
in vec3 _color;

void main()
{
    color = vec4(_color, 1.0);
}
)shader";

GLfloat vertices[] = {
//         x,     y,    r,    g,    b,
        0.0f,  0.5f, 1.0f, 0.0f, 0.0f,
        0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
        -0.5f, -0.5f, 0.0f, 0.0f, 1.0f
};

int main(int argc, char** argv)
{
    SDL_Log("1: %s\n", SDL_GetError());
    SDL_Log("%d -- sz \n", strlen(SDL_GetError()));
    SDL_Init(SDL_INIT_VIDEO);

    auto window = SDL_CreateWindow("test", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                             640, 480, SDL_WINDOW_OPENGL | SDL_WINDOW_FULLSCREEN);

    SDL_DisplayMode displayMode;
    SDL_GetWindowDisplayMode(window, &displayMode);

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_ES);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
//    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

    auto context = SDL_GL_CreateContext(window);
    SDL_GL_MakeCurrent(window, context);

    SDL_GL_SetSwapInterval(0);

    glViewport(0, 0, displayMode.w, displayMode.h);

    GLuint vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    GLuint vbo;
    glGenBuffers(1, &vbo);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexSource, NULL);
    glCompileShader(vertexShader);

    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
    glCompileShader(fragmentShader);

    GLuint shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    glUseProgram(shaderProgram);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(2 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);

    glClearColor(0.2f, 0.2f, 0.2f, 1.0f);

    while(true)
    {
        SDL_Event e;
        while(SDL_PollEvent(&e))
        {
            switch (e.type) {
                case SDL_APP_WILLENTERBACKGROUND: SDL_Log("SDL_APP_WILLENTERBACKGROUND\n"); break;
                case SDL_APP_DIDENTERBACKGROUND : SDL_Log("SDL_APP_DIDENTERBACKGROUND \n"); break;
                case SDL_APP_WILLENTERFOREGROUND: SDL_Log("SDL_APP_WILLENTERFOREGROUND\n"); break;
                case SDL_APP_DIDENTERFOREGROUND : SDL_Log("SDL_APP_DIDENTERFOREGROUND \n"); break;
            }
        }

        glClear(GL_COLOR_BUFFER_BIT);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        SDL_GL_SwapWindow(window);
    }

    return 0;
}