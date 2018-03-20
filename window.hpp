#pragma once

#ifndef WINDOW_HPP
#define WINDOW_HPP

#include <SDL2pp/Window.hh>

#include <memory>

namespace SDL2pp {
    class SDL;
    class Window;
    class Renderer;
    class Texture;
}

class Window
{
public:
    Window(int width = 800, int height = 600);

    int width() const { return width_; }
    int height() const { return height_; }

    SDL2pp::Renderer& renderer() const { return *renderer_; }
    SDL2pp::Texture& texture() const { return *texture_; }

    void upate() const;

private:
    int width_;
    int height_;

    std::unique_ptr<SDL2pp::SDL> sdl_;
    std::unique_ptr<SDL2pp::Window> window_;
    std::unique_ptr<SDL2pp::Renderer> renderer_;
    std::unique_ptr<SDL2pp::Texture> texture_;
};

#endif // WINDOW_HPP
