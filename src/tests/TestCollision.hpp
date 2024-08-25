#pragma once

#include "Shader.hpp"
#include "Texture.hpp"
#include "tests/Test.hpp"

namespace test {
    
class TestCollision : public Test
{
public:
    TestCollision();
    ~TestCollision();

    void Update(float deltaTime) override;
    void Render(Renderer2D& renderer) override;
    void ImGuiRender() override;
private:
    Texture* m_Texture;
    Shader* m_Shader;
};

}

