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

VBO g_VBO1;
VAO g_VAO1;
EBO g_EBO;

ShaderProgram shaderProgram1;

int texWidth, texHeight, nrChanels;

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

    shaderProgram1.loadSource("resources/fragment.frag", ShaderProgram::FRAGMENT);
    shaderProgram1.loadSource("resources/vertex.vert", ShaderProgram::VERTEX);
    shaderProgram1.createShaderProgram();

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
    float vertices[] = {
        // positions          // colors           // texture coords
        0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // top right
        0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // bottom right
        -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // bottom left
        -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // top left 
    };

    uint indices[] = {
        0, 1, 3, // first triangle
        1, 2, 3  // second triangle
    };

    u_char* data = stbi_load("resources/img/container.jpg", &texWidth, &texHeight, &nrChanels, 0);;
    if (data == nullptr) throw std::runtime_error("Can not load the texture img");
    
    GLuint texture_id;
    glGenTextures(1, &texture_id);

    g_VAO1.createVAO();
    g_VBO1.genBuffer();
    g_EBO.genBuffer();
    g_VAO1.bind(); // To save the configurations
    glBindTexture(GL_TEXTURE_2D, texture_id);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, texWidth, texHeight, 0, GL_RGB,GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);
    g_VBO1.bindBuffer();
    g_EBO.bindBuffer();
    g_EBO.bufferData(sizeof(indices), indices, GL_STATIC_DRAW);
    g_VBO1.bufferData(sizeof(vertices), vertices, GL_STATIC_DRAW);
    g_VAO1.linkVBO(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    g_VAO1.linkVBO(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    g_VAO1.linkVBO(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    g_VAO1.unBind();
    g_VBO1.unBind();
    g_EBO.unBind();

    // g_EBO.unBind();
    stbi_image_free(data);
}

void CleanUp() {
    // g_EBO.deleteBuffer();
    g_VAO1.deleteVAO();
    g_VBO1.deleteBuffer();
    g_EBO.deleteBuffer();
}

void PreDraw() {
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
}

void Draw(VAO& vao_obj, int size) {
    vao_obj.bind();
    // glDrawArrays(GL_TRIANGLES, 0, size);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
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

    // float n = SDL_GetTicks() / 1000.0f;
    // n = (std::sin(n) / 2);
    PreDraw();
    shaderProgram1.useProgram();
    // glUniform1f(glGetUniformLocation(shaderProgram1.sp_id, "offset"), n);
    Draw(g_VAO1, 3);

    window.SwapWindow();
    return true;
}

// TODO:
/***
 * Abstract texture class
 * add uniforms features to shaderProgram class
 * SI
*/