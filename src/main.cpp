#include <SDL2/SDL.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_image.h>
#include <glad/glad.h>
#include <iostream>
#include <stdexcept>
#include "stb_image.hpp"
#include "Window.hpp"
#include "ShaderProgram.hpp"
#include "BufferObjects/VAO.hpp"
#include "BufferObjects/VBO.hpp"
#include "BufferObjects/EBO.hpp"
#include "Buffers/VertexArray.hpp"

ShaderProgram shaderProgram1;

int texWidth, texHeight, nrChanels;

constexpr int width  = 800;
constexpr int height = 640;

void LoadGLFunctions();
void PrintRenderInformation();
void CreateVertexSpecification(VertexArray& vao, VertexBuffer& vbo, ElementBuffer& ebo);
void CleanUp();
void PreDraw();
void Draw(VertexArray& vao_obj, int size);
bool IsGameRunning(Window& window, VertexArray& vao);
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

    shaderProgram1.loadSource("resources/fragment.frag", ShaderProgram::FRAGMENT);
    shaderProgram1.loadSource("resources/vertex.vert", ShaderProgram::VERTEX);
    shaderProgram1.createShaderProgram();

    VertexBuffer vbo;
    ElementBuffer ebo;
    VertexArray vao{ vbo, ebo };

    CreateVertexSpecification(vao, vbo, ebo);

    while (IsGameRunning(myWindow, vao));

    CleanUp();
}

void CreateVertexSpecification(VertexArray& vao, VertexBuffer& vbo, ElementBuffer& ebo) {
    float vertices[] = {
        // positions          // colors           // texture coords
         0.5f,  0.5f, 0.0f,  1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // top right
         0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // bottom right
        -0.5f, -0.5f, 0.0f,  0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // bottom left
        -0.5f,  0.5f, 0.0f,  1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // top left 
    };

    uint indices[] = {
        0, 1, 3, // first triangle
        1, 2, 3  // second triangle
    };

    vbo.loadData(sizeof(vertices), vertices, GL_STATIC_DRAW);
    vbo.setVertexAttribCount(3);
    vbo.push_VertexAttribLayout(GL_FLOAT, GL_FALSE, 3);
    vbo.push_VertexAttribLayout(GL_FLOAT, GL_FALSE, 3);
    vbo.push_VertexAttribLayout(GL_FLOAT, GL_FALSE, 2);
    ebo.loadData(sizeof(indices), indices, GL_STATIC_DRAW);
    vao.linkBuffers();
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

void CleanUp() {
}

void PreDraw() {
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
}

void Draw(VertexArray& vao_obj, int size) {
    vao_obj.bind();
    // glDrawArrays(GL_TRIANGLES, 0, size);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    vao_obj.unBind();
}

bool IsGameRunning(Window& window, VertexArray& vao) {
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

    // float n = SDL_GetTicks() / 1000.0f;
    // n = (std::sin(n) / 2);
    PreDraw();
    shaderProgram1.useProgram();
    // glUniform1f(glGetUniformLocation(shaderProgram1.sp_id, "offset"), n);
    Draw(vao, 3);

    window.SwapWindow();
    return true;
}

// TODO:
/***
 * Abstract texture class
 * add uniforms features to shaderProgram class
 * SI
*/