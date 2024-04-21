#include "color_functions.hpp"

#include <cmath>

SDL_Color makeColor(const Uint8& r, const Uint8& g, const Uint8& b)
{
    SDL_Color c;

    c.r = r;
    c.g = g;
    c.b = b;
    c.a = 255;

    return c;
}

SDL_Color makeColor(const Uint8& r, const Uint8& g, const Uint8& b, const Uint8& a)
{
    SDL_Color c;

    c.r = r;
    c.g = g;
    c.b = b;
    c.a = a;

    return c;
}

SDL_Color operator* (const SDL_Color& c, const float& lambda)
{
    return makeColor((Uint8)((float)c.r * lambda), (Uint8)((float)c.g * lambda), (Uint8)((float)c.b * lambda));
}

SDL_Color operator* (const float& lambda, const SDL_Color& c)
{
    return c * lambda;
}

void operator*= (SDL_Color& c, const float& lambda)
{
    c = c * lambda;
}

SDL_Color operator/ (const SDL_Color& c, const float& lambda)
{
    return c * (1.f / lambda);
}

void operator/= (SDL_Color& c, const float& lambda)
{
    c = c / lambda;
}

SDL_Color operator+ (const SDL_Color& a, const SDL_Color& b)
{
    return makeColor(a.r + b.r, a.g + b.g, a.b + b.b);
}

void operator+= (SDL_Color& a, const SDL_Color& b)
{
    a = a + b;
}

SDL_Color operator- (const SDL_Color& a, const SDL_Color& b)
{
    return makeColor(a.r - b.r, a.g - b.g, a.b - b.b);
}

void operator-= (SDL_Color& a, const SDL_Color& b)
{
    a = a - b;
}

SDL_Color colorInterpolation(const SDL_Color& a, const SDL_Color& b, const float& t)
{
    return a * (1.f - t) + b * t;
}

SDL_Color hsl(const float& h, float s, float l)
{
    s /= 100; l /= 100;

    float r1, g1, b1;
    float c = s * (1 - std::fabs(2 * l - 1));
    float m = l - c / 2;
    float x = c * (1 - std::fabs(fmodf(h / 60, 2) - 1));

    switch ((int)h / 60)
    {
    case 0:
        r1 = c;
        g1 = x;
        b1 = 0;
        break;
    case 1:
        r1 = x;
        g1 = c;
        b1 = 0;
        break;
    case 2:
        r1 = 0;
        g1 = c;
        b1 = x;
        break;
    case 3:
        r1 = 0;
        g1 = x;
        b1 = c;
        break;
    case 4:
        r1 = x;
        g1 = 0;
        b1 = c;
        break;
    case 5:
        r1 = c;
        g1 = 0;
        b1 = x;
        break;
    default:
        r1 = 0;
        g1 = 0;
        b1 = 0;
        break;
    }

    return makeColor((Uint8)(255.f * (m + r1)), (Uint8)(255.f * (m + g1)), (Uint8)(255.f * (m + b1)));
}

SDL_Color randColor()
{
    return makeColor((Uint8)randInt(0, 255), (Uint8)randInt(0, 255), (Uint8)randInt(0, 255));
}

SDL_Color randHueColor(const float& saturation, const float& light)
{
    return hsl(randFloat(0, 360), saturation, light);
}