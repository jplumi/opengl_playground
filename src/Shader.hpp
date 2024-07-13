#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <string>
#include <unordered_map>

class Shader
{
public:
    ~Shader();

    void Compile(const char* vSource, const char* fSource);
    void Bind() const;
    void Unbind() const;

    void SetBool(const std::string &name, bool value);
    void SetInt(const std::string &name, int value);
    void SetFloat(const std::string &name, float value);
    void SetMat4(const std::string &name, glm::mat4 value);
    void SetMat3(const std::string &name, glm::mat3 value);
    void SetVec3(const std::string &name, float v1, float v2, float v3);
    void SetVec4(const std::string &name, float v1, float v2, float v3, float v4);
private:
    unsigned int m_ID;

    std::unordered_map<std::string, int> m_uniformLocationCache;

    int GetUniformLocation(const std::string& name);
};
