#pragma once

#include "Camera2D.hpp"
#include "IndexBuffer.hpp"
#include "Shader.hpp"
#include "Texture.hpp"
#include "VertexArray.hpp"

class Renderer2D
{
public:
    Renderer2D(Camera2D& camera);
    ~Renderer2D();

    void Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader);
    void Draw(const Texture& texture, const Shader& shader, glm::vec2 position,
              glm::vec2 scale = glm::vec2(1.0f),
              glm::vec3 color = glm::vec3(1.0f));
    void Clear();

private:
    Camera2D& m_Camera;
    VertexArray* m_QuadVAO;
    VertexBuffer* m_QuadVBO;
    IndexBuffer* m_QuadEBO;
};

