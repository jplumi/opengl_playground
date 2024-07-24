#pragma once

#include "Renderer.hpp"

namespace test {

class Test
{
public:
    Test() {}
    virtual ~Test() {}

    virtual void Update(float deltaTime) {}
    virtual void Render(const Renderer& renderer) {}
    virtual void ImGuiRender() {}
};

}
