#include "Assets.hpp"

#include <fstream>
#include <iostream>
#include <sstream>
#include <filesystem>

std::map<std::string, Shader> Assets::m_shaders;
std::string Assets::m_ResourcesPath;

void Assets::Init()
{
    std::string rootPath = std::__fs::filesystem::current_path() / "resources/"; // "/" appends a path
    m_ResourcesPath = rootPath;
}

Shader Assets::LoadShader(const std::string name, const char* vertexPath, const char* fragmentPath)
{
    Init();
    std::string vertexCode;
    std::string fragmentCode;
    std::ifstream vShaderFile;
    std::ifstream fShaderFile;
    
    vShaderFile.exceptions (std::ifstream::failbit | std::ifstream::badbit);
    fShaderFile.exceptions (std::ifstream::failbit | std::ifstream::badbit);
    try 
    {
        vShaderFile.open(m_ResourcesPath + vertexPath);
        fShaderFile.open(m_ResourcesPath + fragmentPath);
        std::stringstream vShaderStream, fShaderStream;

        vShaderStream << vShaderFile.rdbuf();
        fShaderStream << fShaderFile.rdbuf();		
        
        vShaderFile.close();
        fShaderFile.close();
        
        vertexCode   = vShaderStream.str();
        fragmentCode = fShaderStream.str();		
    }
    catch(std::ifstream::failure e)
    {
        std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
    }
    const char* vShaderCode = vertexCode.c_str();
    const char* fShaderCode = fragmentCode.c_str();
    
    Shader shader;
    shader.Compile(vShaderCode, fShaderCode);

    m_shaders[name] = shader;

    return shader;
}

Shader Assets::GetShader(const std::string name)
{
    return m_shaders[name];
}

void Assets::Clear()
{
    for(auto i : m_shaders)
        glDeleteProgram(i.second.ID);
}

