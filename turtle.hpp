#pragma once

#ifndef TURTLE_HPP
#define TURTLE_HPP

#include "vector2d.hpp"
#include "window.hpp"

#include <SDL2pp/Color.hh>
#include <SDL2pp/Point.hh>
#include <SDL2pp/Renderer.hh>
#include <SDL2pp/Texture.hh>

#include <functional>
#include <unordered_map>
#include <stack>
#include <string>


class Turtle
{
public:

    using CommandTable = std::unordered_map<std::string::value_type, std::function<void(void)>>;

    struct State {
        Vector2d<double> position = { 0, 0 };
        double angle = 0;
        SDL2pp::Color color =  {0, 0, 255 };
    };

    State state;

    Turtle(const Window &window) : window_(window) {}

    void forward(double length);
    void push_state();
    void pop_state();

    void execute(const std::string& word, double length, double angle);
    void execute(const std::string& word, const CommandTable& table);

private:

    const Window& window_;
    //SDL2pp::Renderer& renderer_;
    //SDL2pp::Texture& texture_;

    std::stack<State> stack_;

    SDL2pp::Point transform(Vector2d<double> v);
};

#endif // TURTLE_HPP
