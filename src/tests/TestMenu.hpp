#pragma once

#include "Test.hpp"
#include <functional>
#include <utility>
#include <vector>

namespace test {

class TestMenu : public Test
{
public:
    TestMenu(Test*& currentTestPointer);

    void ImGuiRender() override;

    template<typename T>
    void RegisterTest(const std::string& name)
    {
        m_Tests.push_back(std::make_pair(name, []() { return new T; }));
    }

private:
    Test*& m_CurrentTest;
    std::vector<std::pair<std::string, std::function<Test*()>>> m_Tests;
};

}
