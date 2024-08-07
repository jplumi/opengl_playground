#include "TestClearColor.hpp"

#include "glad/glad.h"
#include "imgui/imgui.h"

namespace test {

TestClearColor::TestClearColor() 
    : m_ClearColor {1.0f, 1.0f, 0.5f, 1.0f} {}

TestClearColor::~TestClearColor() {}

void TestClearColor::Update(float deltaTime)
{

}

void TestClearColor::Render()
{
    glClearColor(m_ClearColor[0], m_ClearColor[1], m_ClearColor[2], m_ClearColor[3]);
    glClear(GL_COLOR_BUFFER_BIT);
}

void TestClearColor::ImGuiRender()
{
    ImGui::ColorEdit4("Color clear", m_ClearColor);
}

}
