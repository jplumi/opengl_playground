#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <string>

class Shader
{
public:
    unsigned int ID;

    ~Shader();

    void Compile(const char* vSource, const char* fSource);

    void Use() const;
    void SetBool(const std::string &name, bool value) const;
    void SetInt(const std::string &name, int value) const;
    void SetFloat(const std::string &name, float value) const;
    void SetMat4(const std::string &name, glm::mat4 value) const;
    void SetMat3(const std::string &name, glm::mat3 value) const;
    void SetVec3(const std::string &name, float r, float g, float b) const;
    void SetVec4(const std::string &name, float r, float g, float b, float a) const;
};
