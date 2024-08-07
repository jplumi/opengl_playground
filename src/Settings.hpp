#pragma once

struct WindowSettings
{
    float height = 1080.0f;
    float width = 1920.0f;
    const char* title = "Game";
};

inline const WindowSettings g_WindowSettings;

