#pragma once

#include "Renderer2D.hpp"

namespace test {

class Test
{
public:
    Test() {}
    virtual ~Test() {}

    virtual void Update(float deltaTime) {}
    virtual void Render(Renderer2D& renderer) {}
    virtual void ImGuiRender() {}
};

}
