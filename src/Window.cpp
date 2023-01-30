#include <Window.hpp>
#include <iostream>

Window::Window(int width, int height, const std::string& window_name)
    : m_initial_width(width)
    , m_initial_height(height)
    , m_window_name(window_name)
{}

Window::~Window() {
    if (m_window_ptr != nullptr) {
        SDL_DestroyWindow(m_window_ptr);
    }
}
    
void Window::createWindow() {
    auto subsytem_init = SDL_WasInit(SDL_INIT_EVERYTHING);
    if (!(subsytem_init & SDL_INIT_VIDEO))
        throw std::runtime_error("SDL Video subsystem is not initialized, cannot construct a window");

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

    m_window_ptr = SDL_CreateWindow(
        m_window_name.c_str(),
        SDL_WINDOWPOS_CENTERED, // Posición en x de la ventana
        SDL_WINDOWPOS_CENTERED, // Posición en y de la ventana
        m_initial_width,
        m_initial_height,
        SDL_WINDOW_OPENGL       // Flags
    );
}

void Window::createGLContext() {
    m_glContext = SDL_GL_CreateContext(m_window_ptr);
}

void Window::SwapWindow() {
    SDL_GL_SwapWindow(m_window_ptr);
}

SDL_GLContext Window::getSDL_GLContext() {
    return m_glContext;
}

void Window::setWindowGrab(SDL_bool grabbed) {
    SDL_SetWindowGrab(m_window_ptr, grabbed); 
}