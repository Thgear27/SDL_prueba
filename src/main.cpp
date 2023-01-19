#include "OpenGL/Buffers/VertexArray.hpp"
#include "OpenGL/GLerror.hpp"
#include "OpenGL/ShaderProgram.hpp"
#include "OpenGL/Texture2D.hpp"
#include "OpenGL/stb_image.hpp"
#include "Window.hpp"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_timer.h>
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include <stdexcept>

ShaderProgram shaderProgram1;
Texture2D texture2d1;
Texture2D texture2d2;

const Uint8* keyState;

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
    } catch (std::exception const& e) {
        std::cout << "[ERROR]: " << e.what() << '\n';
    }

    SDL_Quit();
}

// Functions definitions
void game() {
    Window myWindow { width, height, "OpenGL window" };
    myWindow.createWindow();
    myWindow.createGLContext();

    LoadGLFunctions();
    PrintRenderInformation();

    keyState = SDL_GetKeyboardState(nullptr);

    shaderProgram1.loadSource("resources/fragment.frag", ShaderProgram::FRAGMENT);
    shaderProgram1.loadSource("resources/vertex.vert", ShaderProgram::VERTEX);
    shaderProgram1.createShaderProgram();

    VertexBuffer vbo;
    ElementBuffer ebo;
    VertexArray vao;

    CreateVertexSpecification(vao, vbo, ebo);

    GLCall(glEnable(GL_DEPTH_TEST));
    while (IsGameRunning(myWindow, vao))
        ;

    CleanUp();
}

void CreateVertexSpecification(VertexArray& vao, VertexBuffer& vbo, ElementBuffer& ebo) {
    float vertices[] = {
        -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, //
        0.5f,  -0.5f, -0.5f, 1.0f, 0.0f, //
        0.5f,  0.5f,  -0.5f, 1.0f, 1.0f, //
        0.5f,  0.5f,  -0.5f, 1.0f, 1.0f, //
        -0.5f, 0.5f,  -0.5f, 0.0f, 1.0f, //
        -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, //

        -0.5f, -0.5f, 0.5f,  0.0f, 0.0f, //
        0.5f,  -0.5f, 0.5f,  1.0f, 0.0f, //
        0.5f,  0.5f,  0.5f,  1.0f, 1.0f, //
        0.5f,  0.5f,  0.5f,  1.0f, 1.0f, //
        -0.5f, 0.5f,  0.5f,  0.0f, 1.0f, //
        -0.5f, -0.5f, 0.5f,  0.0f, 0.0f, //

        -0.5f, 0.5f,  0.5f,  1.0f, 0.0f, //
        -0.5f, 0.5f,  -0.5f, 1.0f, 1.0f, //
        -0.5f, -0.5f, -0.5f, 0.0f, 1.0f, //
        -0.5f, -0.5f, -0.5f, 0.0f, 1.0f, //
        -0.5f, -0.5f, 0.5f,  0.0f, 0.0f, //
        -0.5f, 0.5f,  0.5f,  1.0f, 0.0f, //

        0.5f,  0.5f,  0.5f,  1.0f, 0.0f, //
        0.5f,  0.5f,  -0.5f, 1.0f, 1.0f, //
        0.5f,  -0.5f, -0.5f, 0.0f, 1.0f, //
        0.5f,  -0.5f, -0.5f, 0.0f, 1.0f, //
        0.5f,  -0.5f, 0.5f,  0.0f, 0.0f, //
        0.5f,  0.5f,  0.5f,  1.0f, 0.0f, //

        -0.5f, -0.5f, -0.5f, 0.0f, 1.0f, //
        0.5f,  -0.5f, -0.5f, 1.0f, 1.0f, //
        0.5f,  -0.5f, 0.5f,  1.0f, 0.0f, //
        0.5f,  -0.5f, 0.5f,  1.0f, 0.0f, //
        -0.5f, -0.5f, 0.5f,  0.0f, 0.0f, //
        -0.5f, -0.5f, -0.5f, 0.0f, 1.0f, //

        -0.5f, 0.5f,  -0.5f, 0.0f, 1.0f, //
        0.5f,  0.5f,  -0.5f, 1.0f, 1.0f, //
        0.5f,  0.5f,  0.5f,  1.0f, 0.0f, //
        0.5f,  0.5f,  0.5f,  1.0f, 0.0f, //
        -0.5f, 0.5f,  0.5f,  0.0f, 0.0f, //
        -0.5f, 0.5f,  -0.5f, 0.0f, 1.0f  //
    };

    uint indices[] = {
        0, 1, 3, // first triangle
        1, 2, 3  // second triangle
    };

    stbi_set_flip_vertically_on_load(true);

    texture2d1.loadImageData("resources/img/container.jpg", 0, GL_RGB, GL_RGB);
    texture2d2.loadImageData("resources/img/awesomeface.png", 0, GL_RGBA, GL_RGBA);

    texture2d1.setTextureUnit(0);
    texture2d2.setTextureUnit(1);

    vbo.loadData(sizeof(vertices), vertices, GL_STATIC_DRAW);
    vbo.push_VertexAttribLayout(GL_FLOAT, GL_FALSE, 3);
    vbo.push_VertexAttribLayout(GL_FLOAT, GL_FALSE, 2);
    ebo.loadData(sizeof(indices), indices, GL_STATIC_DRAW);
    vao.addVertexBuffer(&vbo);
    vao.addElementBuffer(&ebo);
    vao.linkBuffers();
    GLCall(glViewport(0, 0, width, height));
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

void CleanUp() {}

void PreDraw() {
    GLCall(glClearColor(0.2f, 0.3f, 0.3f, 1.0f));
    GLCall(glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT));
}

void Draw(VertexArray& vao_obj, int size) {
    vao_obj.bind();
    GLCall(glDrawArrays(GL_TRIANGLES, 0, size));
    // glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    vao_obj.unBind();
}

bool IsGameRunning(Window& window, VertexArray& vao) {
    static float f_z = -1.0f;
    static float f_x = -1.0f;

    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) return false;
        if (event.type == SDL_KEYDOWN) {
            if (event.key.keysym.sym == SDLK_ESCAPE) {
                return false;
            }
            if (event.key.keysym.sym == SDLK_r) {
                GLCall(glPolygonMode(GL_FRONT_AND_BACK, GL_LINE));
            }
            if (event.key.keysym.sym == SDLK_e) {
                GLCall(glPolygonMode(GL_FRONT_AND_BACK, GL_FILL));
            }
        }
    }

    if (keyState[SDL_SCANCODE_UP] == 1) f_z += 0.1f;
    if (keyState[SDL_SCANCODE_DOWN] == 1) f_z -= 0.1f;
    if (keyState[SDL_SCANCODE_LEFT] == 1) f_x -= 0.1f;
    if (keyState[SDL_SCANCODE_RIGHT] == 1) f_x += 0.1f;

    float n = SDL_GetTicks() / 1000.0f;

    glm::mat4 view = glm::mat4 { 1.0f };
    view           = glm::translate(view, glm::vec3 { f_x, 0.0f, f_z });

    glm::mat projection = glm::mat4 { 1.0f };
    projection          = glm::perspective(glm::radians(70.0f), 800.0f / 600.0f, 0.3f, 100.0f);

    glm::vec3 cubePositions[] = { glm::vec3(0.0f, 0.0f, 0.0f),    glm::vec3(2.0f, 5.0f, -15.0f),
                                  glm::vec3(-1.5f, -2.2f, -2.5f), glm::vec3(-3.8f, -2.0f, -12.3f),
                                  glm::vec3(2.4f, -0.4f, -3.5f),  glm::vec3(-1.7f, 3.0f, -7.5f),
                                  glm::vec3(1.3f, -2.0f, -2.5f),  glm::vec3(1.5f, 2.0f, -2.5f),
                                  glm::vec3(1.5f, 0.2f, -1.5f),   glm::vec3(-1.3f, 1.0f, -1.5f) };

    shaderProgram1.useProgram();
    shaderProgram1.setInt("texture1", 0);
    shaderProgram1.setInt("texture1", 1);
    shaderProgram1.setFloat("si", 1);
    shaderProgram1.setMat4("view", view);
    shaderProgram1.setMat4("projection", projection);

    PreDraw();
    for (int i = 0; i < 10; i++) {
        glm::mat4 model = glm::mat4 { 1.0f };
        model           = glm::translate(model, cubePositions[i]);
        model           = glm::rotate(model, n * ((i + 1) / 8.0f), glm::vec3 { 1.0f, 0.3f, 0.5f });
        // float angle     = i * 20.0f;

        shaderProgram1.setMat4("model", model);

        Draw(vao, 36);
    }

    window.SwapWindow();
    return true;
}

// TODO:
/***
 * add uniforms features to shaderProgram class
 */
