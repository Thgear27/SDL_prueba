#ifndef WINDOW_HPP
#define WINDOW_HPP

#include <SDL2/SDL.h>
#include <string> 

class Window {
private:
    SDL_Window* m_window_ptr;
    SDL_GLContext m_glContext;

    const int m_initial_width;   // used in the SDL_CreateWindow function
    const int m_initial_height; // used in the SDL_CreateWindow function
    std::string m_window_name;

public:
    Window(int width, int height, const std::string& window_name);

    ~Window(); 
    void createWindow() ;

    // Creates the context and makes it current
    void createGLContext(); 

    void SwapWindow();

    SDL_GLContext getSDL_GLContext();

    void setWindowGrab(SDL_bool grabbed);
};

#endif // WINDOW_HPP