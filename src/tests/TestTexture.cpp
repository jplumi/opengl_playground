#include "TestTexture.hpp"

#include "Application.hpp"
#include "Assets.hpp"
#include "Renderer2D.hpp"
#include <cstring>
#include <glad/glad.h>
#include "imgui/imgui.h"

namespace test {

TestTexture::TestTexture()
    : m_Translation(glm::vec3(0.0f)) 
{
    Application::camera.position = glm::vec3(0);
    
    m_Texture = Assets::LoadTexture("images/player.png");

    m_Shader = Assets::LoadShader("textureShader", "vert_Texture2D.glsl", "frag_Texture2D.glsl");
}

TestTexture::~TestTexture()
{
}

void TestTexture::Render(Renderer2D& renderer)
{
    Application::renderer->Draw(*m_Texture, *m_Shader, m_Translation);
}

void TestTexture::ImGuiRender()
{
    ImGui::SliderFloat2("Position", &m_Translation.x, -500.0f, 500.0f);
}
}


