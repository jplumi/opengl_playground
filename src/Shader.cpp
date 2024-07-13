#include "Shader.hpp"

#include <iostream>

Shader::~Shader()
{
    glDeleteProgram(m_ID);
}

void Shader::Compile(const char* vSource, const char* fSource)
{
    unsigned int vertex, fragment;
    int success;
    char infoLog[512];
    
    // vertex Shader
    vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex, 1, &vSource, NULL);
    glCompileShader(vertex);
    glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
    if(!success)
    {
        glGetShaderInfoLog(vertex, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    };

    // fragment Shader
    fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, &fSource, NULL);
    glCompileShader(fragment);
    glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
    if(!success)
    {
        glGetShaderInfoLog(fragment, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    };
    
    m_ID = glCreateProgram();
    glAttachShader(m_ID, vertex);
    glAttachShader(m_ID, fragment);
    glLinkProgram(m_ID);
    
    glGetProgramiv(m_ID, GL_LINK_STATUS, &success);
    if(!success)
    {
        glGetProgramInfoLog(m_ID, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }
    
    glDeleteShader(vertex);
    glDeleteShader(fragment);
}

void Shader::Bind() const
{
    glUseProgram(m_ID);
}

void Shader::Unbind() const
{
    glUseProgram(0);
}

void Shader::SetBool(const std::string &name, bool value)
{         
    glUniform1i(GetUniformLocation(name), (int)value); 
}
void Shader::SetInt(const std::string &name, int value) 
{ 
    glUniform1i(GetUniformLocation(name), value); 
}
void Shader::SetFloat(const std::string &name, float value) 
{ 
    glUniform1f(GetUniformLocation(name), value); 
} 
void Shader::SetMat4(const std::string &name, glm::mat4 value) 
{ 
    glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, glm::value_ptr(value)); 
}
void Shader::SetMat3(const std::string &name, glm::mat3 value) 
{ 
    glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, glm::value_ptr(value)); 
}
void Shader::SetVec4(const std::string &name, float v1, float v2, float v3, float v4) 
{ 
    glUniform4f(GetUniformLocation(name), v1, v2, v3, v4);
}
void Shader::SetVec3(const std::string &name, float v1, float v2, float v3) 
{
    glUniform3f(GetUniformLocation(name), v1, v2, v3);
}

int Shader::GetUniformLocation(const std::string& name)
{
    if(m_uniformLocationCache.find(name) != m_uniformLocationCache.end())
        return m_uniformLocationCache[name];

    int location = glGetUniformLocation(m_ID, name.c_str());
    m_uniformLocationCache[name] = location;

    return location;
}

