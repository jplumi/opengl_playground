#pragma once

#include "Test.hpp"

namespace test {

class TestClearColor : public Test
{
public:
    TestClearColor();
    ~TestClearColor();

    void Update(float deltaTime) override;
    void Render(const Renderer& renderer) override;
    void ImGuiRender() override;
private:
    float m_ClearColor[4];
};

}
