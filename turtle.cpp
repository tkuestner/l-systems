#include "turtle.hpp"


void Turtle::forward(double length)
{
    auto& renderer = window_.renderer();
    renderer.SetTarget(window_.texture());
    renderer.SetDrawColor(state.color);

    Vector2d<double> target {
        state.position.x + length * std::cos(state.angle / 180.0 * M_PI),
        state.position.y + length * std::sin(state.angle / 180.0 * M_PI)
    };

    renderer.DrawLine(transform(state.position), transform(target));
    state.position = target;
}


void Turtle::push_state()
{
    stack_.push(state);
}


void Turtle::pop_state()
{
    state = stack_.top();
    stack_.pop();
}


void Turtle::execute(const std::string& word, double length, double angle)
{
    CommandTable default_table = {
        { 'F', [&](){ forward(length); }},
        { '+', [&](){ state.angle += angle; }},
        { '-', [&](){ state.angle -= angle; }},
        { '[', [&](){ push_state(); }},
        { ']', [&](){ pop_state(); }},
    };

    execute(word, default_table);
}


void Turtle::execute(const std::string &word, const CommandTable& table)
{
    for (auto& c : word) {
        auto search = table.find(c);
        if (search != table.end()) search->second();
    }
}


// Coordinate transformation from real x/y to pixels with origin in center of window
SDL2pp::Point Turtle::transform(Vector2d<double> v)
{
    const int width = window_.width();
    const int height = window_.height();

    return SDL2pp::Point(
        static_cast<int>( v.x +  width / 2.0 + 0.5),
        static_cast<int>(-v.y + height / 2.0 + 0.5)
    );
}
