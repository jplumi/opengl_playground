#pragma once

#include "IndexBuffer.hpp"
#include "Shader.hpp"
#include "Texture.hpp"
#include "VertexArray.hpp"
#include "tests/Test.hpp"

namespace test {

struct Vertex
{
    glm::vec2 position;
    glm::vec2 texCoords;
    glm::vec3 color;
};

class TestBatching : public Test
{
public:
    TestBatching();
    ~TestBatching();

    void Render() override;
    void ImGuiRender() override;
private:
    Shader* m_Shader;
    Texture* m_Texture;
    VertexArray* m_VAO;
    VertexBuffer* m_VBO;
    IndexBuffer* m_EBO;

    glm::vec2 m_Position1;
    glm::vec2 m_Position2;
};

}
