#include "TestCollision.hpp"
#include "Assets.hpp"

namespace test {

TestCollision::TestCollision()
{
    // m_Texture = Assets::LoadTexture("images/wall.jpg");
    // m_Shader = Assets::LoadShader("texture", "vert_Texture2D.glsl", "vert_Texture2D.glsl");

}

TestCollision::~TestCollision()
{

}

void TestCollision::Update(float deltaTime)
{

}

void TestCollision::Render(Renderer2D& renderer)
{
    // renderer.Draw(*m_Texture, *m_Shader, glm::vec2(0), glm::vec2(1));
}

void TestCollision::ImGuiRender()
{

}

}

