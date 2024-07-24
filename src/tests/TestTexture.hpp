#pragma once

#include "Shader.hpp"
#include "Texture.hpp"
#include "tests/Test.hpp"

namespace test {

class TestTexture : public Test
{
public:
    TestTexture();
    ~TestTexture();

    void Update(float deltaTime) override;
    void Render(const Renderer& renderer) override;
    void ImGuiRender() override;
private:
    glm::vec3 m_Translation;
    Shader m_Shader;
    Texture m_Texture;
    VertexArray* m_VAO;
    VertexBuffer* m_VBO;
    IndexBuffer* m_EBO;

    // std::unique_ptr<Shader> m_Shader;
    // std::unique_ptr<VertexArray> m_VAO;
    // std::unique_ptr<VertexBuffer> m_VBO;
    // std::unique_ptr<IndexBuffer> m_EBO;
};

}
