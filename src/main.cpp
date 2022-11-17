#include <SDL2/SDL.h>
#include <glad/glad.h>
#include <iostream>
#include <stdexcept>
#include "Window.hpp"
#include "ShaderProgram.hpp"
#include "BufferObjects/VAO.hpp"
#include "BufferObjects/VBO.hpp"
#include "BufferObjects/EBO.hpp"

VBO g_VBO;
VAO g_VAO;
EBO g_EBO;

constexpr int width  = 800;
constexpr int height = 640;

void LoadGLFunctions();
void PrintRenderInformation();
void CreateVertexSpecification();
void CleanUp();
void PreDraw();
void Draw(VAO& vao_obj);
bool IsGameRunning(Window& window, ShaderProgram& shader_program);
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

    ShaderProgram sptest;
    sptest.loadSource("resources/fragment.shader", ShaderProgram::FRAGMENT);
    sptest.loadSource("resources/vertex.shader", ShaderProgram::VERTEX);
    sptest.createShaderProgram();

    CreateVertexSpecification();

    while (IsGameRunning(myWindow, sptest));

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
    float vertices[] = {
        // x     y     z
        0.5f,  0.5f,  0.0f, //
        0.5f,  -0.5f, 0.0f, //
        -0.5f, -0.5f, 0.0f, //
        -0.5f, 0.5f,  0.0f  //
    };

    uint indices[] = {
        0, 1, 3, // first triangle
        1, 2, 3  // second triangle
    };

    g_VAO.createVAO();
    g_VBO.genBuffer();
    g_EBO.genBuffer();

    g_VAO.bind(); // To save the configurations

    g_VBO.bindBuffer();
    g_EBO.bindBuffer();

    g_VBO.bufferData(sizeof(vertices), vertices, GL_STATIC_DRAW);
    g_EBO.bufferData(sizeof(indices), indices, GL_STATIC_DRAW);

    g_VAO.linkVBO(0);

    g_VAO.unBind();
    g_VBO.unBind();
    g_EBO.unBind();
}

void CleanUp() {
    g_EBO.deleteBuffer();
    g_VAO.deleteVAO();
    g_VBO.deleteBuffer();
}

void PreDraw() {
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
}

void Draw(VAO& vao_obj) {
    vao_obj.bind();
    // glDrawArrays(GL_TRIANGLES, 0, 3);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    vao_obj.unBind();
}

bool IsGameRunning(Window& window, ShaderProgram& shader_program) {
    shader_program.useProgram();
    PreDraw();
    Draw(g_VAO);

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

    window.SwapWindow();
    return true;
}