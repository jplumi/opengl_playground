#pragma once

#include "tests/Test.hpp"

namespace test {

class TestTexture : public Test
{
public:
    TestTexture();
    ~TestTexture();

    void Update(float deltaTime) override;
    void Render() override;
    void ImGuiRender() override;
};

}
