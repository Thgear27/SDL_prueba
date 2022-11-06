#include <SDL2/SDL.h>
#include <glad/glad.h>
#include <iostream>

SDL_Window* window;
SDL_GLContext glContext;

GLuint vertexBufferObjet;

GLuint shaderProgram;

constexpr int width  = 800;
constexpr int height = 640;

void Init() {
    SDL_Init(SDL_INIT_VIDEO);

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

    int major = 0;
    int minor = 0;
    SDL_GL_GetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, &major);
    SDL_GL_GetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, &minor);

    std::cout << "Major requested: " << major << '\n';
    std::cout << "Minor requested: " << minor << '\n';

    window = SDL_CreateWindow(
        "Nombre de la ventana",
        SDL_WINDOWPOS_CENTERED, // Posición en x de la ventana
        SDL_WINDOWPOS_CENTERED, // Posición en y de la ventana
        width,                  // Ancho de la ventana
        height,                 // Alto de la ventana
        SDL_WINDOW_OPENGL       // Le decimos que vamos a utilizar OpenGL
    );

    if (!window) { // True si el puntero es nullo
        std::cerr << "No se puede abrir la ventana\n";
        std::terminate();
    }

    glContext = SDL_GL_CreateContext(window);
    if (!gladLoadGLLoader(SDL_GL_GetProcAddress)) {
        std::cout << "Failed to initialize GLAD\n";
        std::terminate();
    }
}

void PrintRenderInformation() {
    std::cout << "VENDOR:" << glGetString(GL_VENDOR) << '\n';
    std::cout << "RENDERER:" << glGetString(GL_RENDERER) << '\n';
    std::cout << "VERSION:" << glGetString(GL_VERSION) << '\n';
    std::cout << "SHADING LENGUAGE VERSION:" << glGetString(GL_SHADING_LANGUAGE_VERSION) << '\n';
}

void CreateVertexBuffer() {
    float vertices[] = {
        -0.5f, -0.5f, 0.0f, //
        0.5f,  -0.5f, 0.0f, //
        0.0f,  0.5f,  0.0f  //
    };

    glGenBuffers(1, &vertexBufferObjet);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObjet);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
}

void SetUpGraphicsPipeline() {
    const char* vertexShaderSource = "#version 330 core\n"
                                     "layout (location = 0) in vec3 aPos;\n"
                                     "void main() {\n"
                                     " gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
                                     "}\0";
    GLuint vertexShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr);
    glCompileShader(vertexShader);

    // Para verificar que se haya compilado bien
    int success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(vertexShader, 512, nullptr, infoLog);
        std::cerr << "ERROR: Vertex shader compilation failed\n" << infoLog << '\n';
    } else {
        std::cout << "SUCCESS: Vertex Shader Compilation Successful\n";
    }

    const char* fragmentShaderSource = "#version 330 core\n"
                                       "out vec4 FragColor;\n"
                                       "void main() { FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f); }";
    GLuint fragmentShader;
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, nullptr);
    glCompileShader(fragmentShader);

    // Para verificar que se haya compilado bien
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(vertexShader, 512, nullptr, infoLog);
        std::cerr << "ERROR: Fragment shader compilation failed\n" << infoLog << '\n';
    } else {
        std::cout << "SUCCESS: Fragment Shader Compilation Successful\n";
    }

    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    // Para verificar que se haya linkado bien
    if (!success) {
        glGetProgramInfoLog(shaderProgram, 512, nullptr, infoLog);
        std::cerr << "ERROR: Failed to link shader program\n";
    } else {
        std::cout << "SUCCESS: Shader program linked\n";
    }

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

void CleanUp() {
    SDL_DestroyWindow(window);
    SDL_Quit();
}

bool IsGameRunning() {
    glViewport(0, 0, width, height);

    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) return false;
        if (event.type == SDL_KEYDOWN) {
            if (event.key.keysym.sym == SDLK_ESCAPE) {
                return false;
            }
            std::cout << "Se ha presionado algo\n";
        }
    }

    SDL_GL_SwapWindow(window);
    return true;
}

int main() {
    Init();

    PrintRenderInformation();

    CreateVertexBuffer();

    SetUpGraphicsPipeline();

    while (IsGameRunning())
        ;

    CleanUp();
    return 0;
}