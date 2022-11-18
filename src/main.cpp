#include <SDL2/SDL.h>
#include <SDL2/SDL_timer.h>
#include <glad/glad.h>
#include <iostream>
#include <stdexcept>
#include "Window.hpp"
#include "ShaderProgram.hpp"
#include "BufferObjects/VAO.hpp"
#include "BufferObjects/VBO.hpp"
#include "BufferObjects/EBO.hpp"

VBO g_VBO1;
VAO g_VAO1;

VBO g_VBO2;
VAO g_VAO2;

ShaderProgram shaderProgram1;
ShaderProgram shaderProgram2;

EBO g_EBO;

constexpr int width  = 800;
constexpr int height = 640;

void LoadGLFunctions();
void PrintRenderInformation();
void CreateVertexSpecification();
void CleanUp();
void PreDraw();
void Draw(VAO& vao_obj, int size);
bool IsGameRunning(Window& window);
void game();

int main() {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        std::cout << "Cannot intialize SDL\n";
        return -1;
    }

    try {
        game();
    } catch(std::exception const& e) {
        std::cout << "[ERROR]: " << e.what() << '\n';
    }
    SDL_Quit();
}

// Functions definitions
void game() {
    Window myWindow{ width, height, "OpenGL window" }; 
    myWindow.createWindow();
    myWindow.createGLContext();

    LoadGLFunctions();

    PrintRenderInformation();

    shaderProgram1.loadSource("resources/fragment.shader", ShaderProgram::FRAGMENT);
    shaderProgram1.loadSource("resources/vertex.shader", ShaderProgram::VERTEX);
    shaderProgram1.createShaderProgram();

    shaderProgram2.loadSource("resources/fragment2.shader", ShaderProgram::FRAGMENT);
    shaderProgram2.loadSource("resources/vertex.shader", ShaderProgram::VERTEX);
    shaderProgram2.createShaderProgram();

    CreateVertexSpecification();

    while (IsGameRunning(myWindow));

    CleanUp();
}

void LoadGLFunctions() {
    if (!gladLoadGLLoader(SDL_GL_GetProcAddress)) {
        throw std::runtime_error("Failed to initialize GLAD");
    }
}

void PrintRenderInformation() {
    std::cout << "VENDOR:  " << glGetString(GL_VENDOR) << '\n';
    std::cout << "RENDERER:" << glGetString(GL_RENDERER) << '\n';
    std::cout << "VERSION: " << glGetString(GL_VERSION) << '\n';
    std::cout << "SHADING LENGUAGE VERSION:" << glGetString(GL_SHADING_LANGUAGE_VERSION) << '\n';
}

void CreateVertexSpecification() {
    // ESTO ESTÁ EN LA CPU
    float vertices1[] = {
        // x     y     z
        0.5f,  0.5f,  0.0f, // 0
        0.5f,  -0.5f, 0.0f, // 1
        -0.5f, 0.5f,  0.0f, // 3
    };

    float vertices2[] = {
        // x     y     z
        0.5f,  -0.5f, 0.0f, // 1
        -0.5f, -0.5f, 0.0f, // 2
        -0.5f, 0.5f,  0.0f  // 3
    };

    // uint indices[] = {
    //     0, 1, 3, // first triangle
    //     1, 2, 3  // second triangle
    // };

    g_VAO1.createVAO();
    g_VBO1.genBuffer();
    g_VAO1.bind(); // To save the configurations
    g_VBO1.bindBuffer();
    g_VBO1.bufferData(sizeof(vertices1), vertices1, GL_STATIC_DRAW);
    g_VAO1.linkVBO(0);
    g_VAO1.unBind();
    g_VBO1.unBind();

    g_VAO2.createVAO();
    g_VAO2.bind();
    g_VBO2.genBuffer();
    g_VBO2.bindBuffer();
    g_VBO2.bufferData(sizeof(vertices2), vertices2, GL_STATIC_DRAW);
    g_VAO2.linkVBO(0);
    g_VAO2.unBind();
    g_VBO2.unBind();

    // g_EBO.unBind();
}

void CleanUp() {
    // g_EBO.deleteBuffer();
    g_VAO1.deleteVAO();
    g_VBO1.deleteBuffer();
    g_VAO2.deleteVAO();
    g_VBO2.deleteBuffer();
}

void PreDraw() {
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
}

void Draw(VAO& vao_obj, int size) {
    vao_obj.bind();
    glDrawArrays(GL_TRIANGLES, 0, size);
    // glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    vao_obj.unBind();
}

bool IsGameRunning(Window& window) {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) return false;
        if (event.type == SDL_KEYDOWN) {
            if (event.key.keysym.sym == SDLK_ESCAPE) {
                return false;
            }
            if (event.key.keysym.sym == SDLK_r) {
                glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
            }
            if (event.key.keysym.sym == SDLK_e) {
                glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
            }
        }
    }

    int vertexColorLocation = glGetUniformLocation(shaderProgram1.sp_id, "ourColor");
    float n = SDL_GetTicks() / 1000.0f;
    n = (std::sin(n) / 2) + 0.5f;
    PreDraw();
    shaderProgram1.useProgram();
    glUniform4f(vertexColorLocation, n, n, n, 1.0f);
    Draw(g_VAO1, 3);
    shaderProgram2.useProgram();
    Draw(g_VAO2, 3);


    window.SwapWindow();
    return true;
}