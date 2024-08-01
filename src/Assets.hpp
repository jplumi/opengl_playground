#pragma once

#include <map>
#include <string>
#include "Shader.hpp"
#include "Texture.hpp"

class Assets
{
public:
    static void Init();

    static Shader* LoadShader(const std::string& name, const char* vertexPath, const char* fragmentPath);
    static Shader* LoadShader(const std::string& name);

    static Texture* LoadTexture(const std::string& path);

    static void Clear();
private:
    static std::map<std::string, Shader*> m_shaders;
    static std::map<std::string, Texture*> m_textures;
    static std::string m_ResourcesPath;
};
