#include "Shader.hpp"

#include <iostream>
#include "OpenGLDebug.hpp"

unsigned int Shader::m_LastBoundProgram = 0;

Shader::~Shader()
{
    GLCall(glDeleteProgram(m_ID));
}

void Shader::Compile(const char* vSource, const char* fSource)
{
    unsigned int vertex, fragment;
    int success;
    char infoLog[512];
    
    // vertex Shader
    GLCall(vertex = glCreateShader(GL_VERTEX_SHADER));
    GLCall(glShaderSource(vertex, 1, &vSource, NULL));
    GLCall(glCompileShader(vertex));
    GLCall(glGetShaderiv(vertex, GL_COMPILE_STATUS, &success));
    if(!success)
    {
        GLCall(glGetShaderInfoLog(vertex, 512, NULL, infoLog));
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    };

    // fragment Shader
    GLCall(fragment = glCreateShader(GL_FRAGMENT_SHADER));
    GLCall(glShaderSource(fragment, 1, &fSource, NULL));
    GLCall(glCompileShader(fragment));
    GLCall(glGetShaderiv(fragment, GL_COMPILE_STATUS, &success));
    if(!success)
    {
        GLCall(glGetShaderInfoLog(fragment, 512, NULL, infoLog));
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    };
    
    GLCall(m_ID = glCreateProgram());
    GLCall(glAttachShader(m_ID, vertex));
    GLCall(glAttachShader(m_ID, fragment));
    GLCall(glLinkProgram(m_ID));
    
    GLCall(glGetProgramiv(m_ID, GL_LINK_STATUS, &success));
    if(!success)
    {
        GLCall(glGetProgramInfoLog(m_ID, 512, NULL, infoLog));
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }
    
    GLCall(glDeleteShader(vertex));
    GLCall(glDeleteShader(fragment));
}

void Shader::Bind() const
{
    if(m_LastBoundProgram != m_ID)
    {
        GLCall(glUseProgram(m_ID));
        m_LastBoundProgram = m_ID;
    }
}

void Shader::Unbind() const
{
    GLCall(glUseProgram(0));
}

void Shader::SetBool(const std::string &name, bool value)
{         
    GLCall(glUniform1i(GetUniformLocation(name), (int)value)); 
}
void Shader::SetInt(const std::string &name, int value) 
{ 
    GLCall(glUniform1i(GetUniformLocation(name), value)); 
}
void Shader::SetFloat(const std::string &name, float value) 
{ 
    GLCall(glUniform1f(GetUniformLocation(name), value)); 
} 
void Shader::SetMat4(const std::string &name, glm::mat4 value) 
{ 
    GLCall(glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, glm::value_ptr(value))); 
}
void Shader::SetMat3(const std::string &name, glm::mat3 value) 
{ 
    GLCall(glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, glm::value_ptr(value))); 
}
void Shader::SetVec4(const std::string &name, float v1, float v2, float v3, float v4) 
{ 
    GLCall(glUniform4f(GetUniformLocation(name), v1, v2, v3, v4));
}
void Shader::SetVec3(const std::string &name, float v1, float v2, float v3) 
{
    GLCall(glUniform3f(GetUniformLocation(name), v1, v2, v3));
}

int Shader::GetUniformLocation(const std::string& name) const
{
    if(m_uniformLocationCache.find(name) != m_uniformLocationCache.end())
        return m_uniformLocationCache[name];

    int location;
    GLCall(location = glGetUniformLocation(m_ID, name.c_str()));
    m_uniformLocationCache[name] = location;

    return location;
}

