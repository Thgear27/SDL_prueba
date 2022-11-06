#include <SDL2/SDL.h>
#include <glad/glad.h>
#include <iostream>

const char* vertexShaderSource = "#version 330 core\n"
                                 "layout (location = 0) in vec3 aPos;\n"
                                 "void main()\n"
                                 "{\n"
                                 " gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
                                 "}\0";

int main() {
    SDL_Window* window;

    SDL_Init(SDL_INIT_VIDEO); // Inicializamos el subsistema de SDL

    // Seteamos los atributos de la OpenGL window antes de crear una ventana
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

    // Creamos una ventana con ayuda de SDL
    window = SDL_CreateWindow(
        "Una ventana :v",        // window title
        SDL_WINDOWPOS_UNDEFINED, // initial x position
        SDL_WINDOWPOS_UNDEFINED, // initial y position
        800,                     // width, in pixels
        600,                     // height, in pixels
        SDL_WINDOW_OPENGL        // flags - see below
    );

    // Vemos si la ventana ha sido creada correctamente
    if (window == NULL) {
        printf("Could not create window: %s\n", SDL_GetError());
        return 1;
    }

    SDL_GLContext context;
    context = SDL_GL_CreateContext(window);

    // Se cargan los punteros a las funciones de openGL
    if (!gladLoadGLLoader(SDL_GL_GetProcAddress)) {
        std::cout << "Failed to initialize GLAD\n";
        return -1;
    }

    float vertices[] = { -0.5f, -0.5f, 0.0f, 0.5f, -0.5f, 0.0f, 0.5f, 0.5f, 0.0f };

    uint vertexShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr);
    glCompileShader(vertexShader);
    std::cout << vertexShaderSource;

    int success;
    char infoLog[512];
    GLsizei sizei;
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(vertexShader, 512, &sizei, infoLog);
        std::cout << infoLog << '\n';
        return -1;
    }
    glCompileShader(vertexShader);


    uint VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // A partir de aquí ya se puede hacer uso de openGL
    // -----------------------------------------------------
    bool running = true;
    while (running) {
        glViewport(0, 0, 800, 600);
        // openGL stuff

        // -------------------------------------
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

        // Input management
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) running = false;
            if (event.type == SDL_KEYDOWN) {
                if (event.key.keysym.sym == SDLK_ESCAPE) {
                    running = false;
                }
                std::cout << "Se ha presionado algo\n";
            }
        }
        // Swap buffers
        SDL_GL_SwapWindow(window);
    }
    // -----------------------------------------------------

    // Cierra y destruye la ventana
    SDL_DestroyWindow(window);

    // Cosas de SDL, desinicializa los subsistemas apropiadamente para evitar memory leaks
    SDL_Quit();
    return 0;
}
