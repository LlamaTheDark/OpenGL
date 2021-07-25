#include "Renderer.h"

#include <iostream>

void GLClearError() {
    while (glGetError() != GL_NO_ERROR); // GL_NO_ERROR is guaranteed to be 0
}

bool GLLogCall(const char* function, const char* filename, int linenum) {
    while (GLenum error = glGetError()) {
        std::cout << "[OpenGL Error] (" << error << "): "
            << function << ": in file "
            << filename << ": on line "
            << linenum << std::endl;
        return false;
    }
    return true;
}