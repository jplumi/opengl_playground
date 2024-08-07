#include "OpenGLDebug.hpp"

#include <glad/glad.h>
#include <iostream>

void GLClearError()
{
    while(glGetError() != GL_NO_ERROR);
}

bool GLLogCall(const char* function, const char* file, int line)
{
    if(GLenum error = glGetError())
    {
        std::cout << "[OpenGL Error]: (" << error << "): " << function << " at " << file << ":" << line << '\n';
        return false;
    }
    return true;
}

