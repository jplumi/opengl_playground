#pragma once

namespace test {

class Test
{
public:
    Test() {}
    virtual ~Test() {};

    virtual void Update(float deltaTime) {}
    virtual void Render() {}
    virtual void ImGuiRender() {}
};

}
