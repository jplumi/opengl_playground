#include "Assets.hpp"

#include "OpenGLDebug.hpp"
#include "Texture.hpp"
#include <fstream>
#include <iostream>
#include <sstream>
#include <filesystem>

#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>

std::map<std::string, Shader*> Assets::m_shaders;
std::map<std::string, Texture*> Assets::m_textures;

std::string Assets::m_ResourcesPath;

void Assets::Init()
{
    std::string rootPath = std::__fs::filesystem::current_path() / "assets/"; // "/" appends a path
    m_ResourcesPath = rootPath;
}

Shader* Assets::LoadShader(const std::string& name, const char* vertexPath, const char* fragmentPath)
{
    if(m_shaders.count(name) != 0)
        return m_shaders[name];

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
    
    m_shaders[name] = new Shader();
    m_shaders[name]->Compile(vShaderCode, fShaderCode);
    return m_shaders[name];
}

Shader* Assets::LoadShader(const std::string& name)
{
    return m_shaders[name];
}

Texture* Assets::LoadTexture(const std::string& path)
{
    if(m_textures.count(path) != 0)
        return m_textures[path];

    stbi_set_flip_vertically_on_load(1);
    int width, height, bpp;
    std::string fullpath = m_ResourcesPath + path;
    unsigned char* imgData = stbi_load(fullpath.c_str(), &width, &height, &bpp, 4);

    unsigned int texId;
    GLCall(glGenTextures(1, &texId));
    GLCall(glBindTexture(GL_TEXTURE_2D, texId));

    GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST));
    GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST));
    GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
    GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));

    GLCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, imgData));
    GLCall(glBindTexture(GL_TEXTURE_2D, 0));

    if(imgData)
        stbi_image_free(imgData);

    m_textures[path] = new Texture();
    m_textures[path]->SetData(texId, width, height, bpp);

    return m_textures[path];
}

void Assets::Clear()
{
    for(auto shader : m_shaders)
        delete shader.second;
    m_shaders.clear();
    for(auto tex : m_textures)
        delete tex.second;
    m_textures.clear();
}

