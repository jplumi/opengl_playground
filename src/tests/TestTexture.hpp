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

    void Render(Renderer2D& renderer) override;
    void ImGuiRender() override;
private:
    glm::vec3 m_Translation;
    Shader* m_Shader;
    Texture* m_Texture;
};

}
