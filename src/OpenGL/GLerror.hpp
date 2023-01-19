#ifndef __GLERROR_H__
#define __GLERROR_H__

#include <glad/glad.h>
#include <iostream>

inline void GLClearAllError() {
    while(glGetError() != GL_NO_ERROR) {
    }
}

inline void GLCheckErrorStatus(const char* func, int line, const char* file) {
    while (GLenum error = glGetError()) {
        std::cerr << "\nOpenGL ERROR: \n";
        std::cerr << "  On file: "<< file << "\n  At line: " << line << "\n  In function: " << func << '\n';
        std::cerr << "  Error Code: " << error << '\n';
        throw std::runtime_error("An OpenGL error has ocurred");
    }
}

#ifdef DEBUG
#define GLCall(x) GLClearAllError();\
                  x;                \
                  GLCheckErrorStatus(#x, __LINE__, __FILE__);
#else
#define GLCall(x) x;
#endif
 
 #endif // __GLERROR_H__