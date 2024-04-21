#pragma once

#include <cmath>
#include <SDL2/SDL.h>
#include "complex_functions.hpp"

SDL_Color makeColor(const Uint8& r, const Uint8& g, const Uint8& b);
SDL_Color makeColor(const Uint8& r, const Uint8& g, const Uint8& b, const Uint8& a);

#define BLACK makeColor(0, 0, 0)
#define DARK_GREY makeColor(20, 20, 20)
#define GREY makeColor(125, 125, 125)
#define WHITE makeColor(255, 255, 255)
#define RED makeColor(255, 0, 0)
#define YELLOW makeColor(255, 255, 0)
#define GREEN makeColor(0, 255, 0)
#define CYAN makeColor(0, 255, 255)
#define BLUE makeColor(0, 0, 255)
#define PURPLE makeColor(255, 0, 255)
#define ORANGE makeColor(255, 165, 0)

SDL_Color operator* (const SDL_Color& c, const float& lambda);
SDL_Color operator* (const float& lambda, const SDL_Color& c);
void operator*= (SDL_Color& c, const float& lambda);
SDL_Color operator/ (const SDL_Color& c, const float& lambda);
void operator/= (SDL_Color& c, const float& lambda);
SDL_Color operator+ (const SDL_Color& a, const SDL_Color& b);
void operator+= (SDL_Color& a, const SDL_Color& b);
SDL_Color operator- (const SDL_Color& a, const SDL_Color& b);
void operator-= (SDL_Color& a, const SDL_Color& b);

SDL_Color colorInterpolation(const SDL_Color& a, const SDL_Color& b, const float& t);

SDL_Color hsl(const float& h, float s, float l);

SDL_Color randColor();
SDL_Color randHueColor(const float& saturation, const float& light);