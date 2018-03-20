#include "window.hpp"

#include <SDL2/SDL.h>

#include <SDL2pp/Renderer.hh>
#include <SDL2pp/SDL.hh>
#include <SDL2pp/Texture.hh>
#include <SDL2pp/Window.hh>


Window::Window(int width, int height) : width_(width), height_(height)
{
    sdl_ = std::make_unique<SDL2pp::SDL>(SDL_INIT_VIDEO);
    window_ = std::make_unique<SDL2pp::Window>("L-systems",
                                              SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                                              width, height,
                                              0); // flags

    renderer_ = std::make_unique<SDL2pp::Renderer>(*window_,
                                                   -1, // first renderer to support requested flags
                                                   SDL_RENDERER_ACCELERATED);

    texture_ = std::make_unique<SDL2pp::Texture>(*renderer_,
                                                 SDL_PIXELFORMAT_RGBA32,
                                                 SDL_TEXTUREACCESS_TARGET,
                                                 width_, height_);

    SDL2pp::Color background { 30, 30, 40};

    // Clear black texture
    renderer_->SetTarget(*texture_);
    renderer_->SetDrawColor(background);
    renderer_->Clear();

    // Clear black screen
    renderer_->SetTarget();
    renderer_->SetDrawColor(background);
    renderer_->Clear();
    renderer_->Present();
}


void Window::upate() const
{
    renderer_->SetTarget();
    renderer_->Copy(*texture_);
    renderer_->Present();
}
