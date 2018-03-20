#include "rulesystem.hpp"
#include "turtle.hpp"
#include "vector2d.hpp"
#include "window.hpp"

#include <SDL2/SDL.h>

#include <SDL2pp/SDL.hh>
#include <SDL2pp/Exception.hh>

#include <cmath>
#include <functional>
#include <iostream>
#include <unordered_map>
#include <vector>


// Simple example
void simple(Turtle& turtle)
{
    std::string axiom { "F-F-F-F" };
    RuleSystem system {{{ 'F', "F-F+F+FF-F-F+F" }}};
    std::string word = system.iterate(axiom, 3);

    const int length = 5;
    const int angle = 90;

    turtle.state.position = { -200, 150 };
    turtle.state.angle = 0;
    turtle.state.color = { 250, 175, 65 };
    turtle.execute(word, length, angle);
}


void koch_snowflake(Turtle& turtle)
{
    std::string axiom { "F++F++F" };
    RuleSystem system {{{ 'F', "F-F++F-F" }}};
    std::string word = system.iterate(axiom, 4);

    const double length = 6;
    const double angle = 60;

    turtle.state.position = { -250, -150 };
    turtle.state.angle = 0;
    turtle.state.color = { 30, 210, 150 };
    turtle.execute(word, length, angle);
}


void sierpinski_arrowhead(Turtle& turtle)
{
    std::string axiom { "A" };
    RuleSystem system {{
      { 'A', "B-A-B" },
      { 'B', "A+B+A" }
    }};
    std::string word = system.iterate(axiom, 6);

    const double length = 9;
    const double angle = 60;

    Turtle::CommandTable table = {
        { 'A', [&](){ turtle.forward(length); }},
        { 'B', [&](){ turtle.forward(length); }},
        { '+', [&](){ turtle.state.angle += angle; }},
        { '-', [&](){ turtle.state.angle -= angle; }},
    };

    turtle.state.position = { -300, -250 };
    turtle.state.angle = 0;
    turtle.state.color = { 240, 40, 45 };
    turtle.execute(word, table);
}


void fern(Turtle& turtle)
{
    std::string axiom { "F" };
    RuleSystem system {{{ 'F', "F[-F]F[+F]F" }}};
    std::string word = system.iterate(axiom, 4);

    turtle.state.position = { 0, -290 };
    turtle.state.angle = 90;
    turtle.state.color = { 20, 165, 45 };
    turtle.execute(word, 7, 20);
}


void buch_of_ferns(Turtle& turtle)
{
    std::string axiom { "F" };
    RuleSystem system {{{ 'F', "F[-F]F[+F]F" }}};
    std::vector<std::string> words;
    for (int i=0; i<6; ++i) {
        words.push_back(system.iterate(axiom, i));
    }

    const double angle = 20;
    const Vector2d<double> start_position { 0, -200 };

    for (size_t i=0; i<words.size(); ++i) {
        double length = 400 * std::pow(1.0 / 3.0, i);
        SDL2pp::Color color(5 + (double)i / (double)words.size() * 250,
                            5 + (double)i / (double)words.size() * 125,
                            250 - (double)i / (double)words.size() * 250);

        turtle.state.position = start_position;
        turtle.state.angle = 150 - 20 * i;
        turtle.state.color = color;
        turtle.execute(words[i], length, angle);
    }
}


int main(int argc, char* argv[])
{
    std::vector<std::function<void(Turtle&)>> examples = {
        simple, koch_snowflake, sierpinski_arrowhead, fern, buch_of_ferns
    };

    size_t example_nr = 0;
    if (argc > 1) {
        try {
            example_nr = std::stol(argv[1]);
        }
        catch (const std::invalid_argument) {}
        catch (const std::out_of_range) {}
    }
    if (example_nr < 0) example_nr = 0;
    if (example_nr >= examples.size()) example_nr = examples.size() - 1;

    try {
        Window window {};
        Turtle turtle {window};

        examples[example_nr](turtle);

        window.upate();
        
        // Main loop
        SDL_Event event;
        bool running = true;
        while (running && SDL_WaitEvent(&event)) {
            switch (event.type) {
            case SDL_KEYDOWN:
                switch (event.key.keysym.sym) {
                case SDLK_ESCAPE:
                    running = false;
                    break;
                }
                break;
            case SDL_WINDOWEVENT:
                window.upate();
                break;
            case SDL_QUIT:
                running = false;
                break;
            }
        }
        
    } catch (SDL2pp::Exception& e) {
      std::cerr << "Error in: " << e.GetSDLFunction() << std::endl;
      std::cerr << "  Reason: " << e.GetSDLError() << std::endl;
    } catch (std::exception& e) {
      std::cerr << e.what() << std::endl;
    }
}
