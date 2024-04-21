#include "complex_functions.hpp"

SDL_FPoint makeComplex(const float& x, const float& y) {
    SDL_FPoint z;

    z.x = x;
    z.y = y;

    return z;
}

SDL_Point makePoint(const int& x, const int& y) {
    SDL_Point z;

    z.x = x;
    z.y = y;

    return z;
}


SDL_FPoint makeComplexExp(const float& r, const float& theta) {
    return makeComplex(r * cosf(theta), r * sinf(theta));
}

SDL_FPoint operator+(const SDL_FPoint& a, const SDL_FPoint& b) {
    return makeComplex(a.x + b.x, a.y + b.y);
}

void operator+=(SDL_FPoint& a, const SDL_FPoint& b) {
    a = a + b;
}

SDL_FPoint operator-(const SDL_FPoint& a, const SDL_FPoint& b) {
    return makeComplex(a.x - b.x, a.y - b.y);
}

SDL_FPoint operator-(const SDL_FPoint& z) {
    return makeComplex(-z.x, -z.y);
}

void operator-=(SDL_FPoint& a, const SDL_FPoint& b) {
    a = a - b;
}

SDL_Point operator-(const SDL_Point& a, const SDL_Point& b) {
    return makePoint(a.x - b.x, a.y - b.y);
}

SDL_Point operator-(const SDL_Point& z) {
    return makePoint(-z.x, -z.y);
}

void operator-=(SDL_Point& a, const SDL_Point& b) {
    a = a - b;
}

SDL_FPoint operator*(const float& lambda, const SDL_FPoint& z) {
    return makeComplex(lambda * z.x, lambda * z.y);
}

SDL_FPoint operator*(const SDL_FPoint& z, const float& lambda) {
    return lambda * z;
}

void operator*=(SDL_FPoint& z, const float& lambda) {
    z = lambda * z;
}

SDL_FPoint operator*(const SDL_FPoint& a, const SDL_FPoint& b) {
    return makeComplex(a.x * b.x - a.y * b.y, a.x * b.y + a.y * b.x);
}

void operator*=(SDL_FPoint& a, const SDL_FPoint& b) {
    a = a * b;
}

SDL_Point operator*(const int& lambda, const SDL_Point& z) {
    return makePoint(lambda * z.x, lambda * z.y);
}

SDL_Point operator*(const SDL_Point& z, const int& lambda) {
    return lambda * z;
}

void operator*=(SDL_Point& z, const int& lambda) {
    z = lambda * z;
}

SDL_FPoint operator/(const SDL_FPoint& z, const float& lambda) {
    return z * (1.f / lambda);
}

void operator/=(SDL_FPoint& z, const float& lambda) {
    z = z / lambda;
}

SDL_FPoint operator/(const float& lambda, const SDL_FPoint& z) {
    return makeComplex((lambda * z.x) / (powf(z.x, 2) + powf(z.y, 2)), (-lambda * z.y) / (powf(z.x, 2) + powf(z.y, 2)));
}

SDL_FPoint operator/(const SDL_FPoint& a, const SDL_FPoint& b) {
    return makeComplex((a.x * b.x + a.y * b.y) / (powf(b.x, 2) + powf(b.y, 2)),
                       (-a.x * b.y + a.y * b.x) / (powf(b.x, 2) + powf(b.y, 2)));
}

void operator/=(SDL_FPoint& a, const SDL_FPoint& b) {
    a = a / b;
}

bool operator==(const SDL_FPoint& a, const SDL_FPoint& b) {
    return (a.x == b.x) && (a.y == b.y);
}

bool operator!=(const SDL_FPoint& a, const SDL_FPoint& b) {
    return !(a == b);
}

SDL_FPoint conjugue(const SDL_FPoint& z) {
    return makeComplex(z.x, -z.y);
}

float rad(const float& deg) {
    return deg * (float) PI / 180.f;
}

float deg(const float& rad) {
    return 180.f * rad / (float) PI;
}

SDL_FPoint scaleComplex(const SDL_FPoint& z, const SDL_FPoint& z0, const float& lambda) {
    return lambda * (z - z0) + z0;
}

SDL_FPoint rotateComplex(const SDL_FPoint& z, const SDL_FPoint& z0, const float& theta_deg) {
    SDL_FPoint t = makeComplexExp(1, rad(theta_deg));
    return t * (z - z0) + z0;
}

float module(const SDL_FPoint& z) {
    return sqrtf(z.x * z.x + z.y * z.y);
}

float module(const SDL_Point& z) {
    return sqrtf((float) (z.x * z.x + z.y * z.y));
}

int randInt(const int& start, const int& end) {
    std::random_device rd;
    std::uniform_int_distribution<> dis(start, end);
    return dis(rd);
}

float randFloat(const float& start, const float& end) {
    std::random_device rd;
    std::uniform_real_distribution<float> dis(start, end);
    return dis(rd);
}

SDL_FPoint randComplex(const float& start, const float& end) {
    return makeComplex(randFloat(start, end), randFloat(start, end));
}

SDL_FPoint randComplex(const float& startX, const float& endX, const float& startY, const float& endY) {
    return makeComplex(randFloat(startX, endX), randFloat(startY, endY));
}

SDL_FPoint PointToFPoint(SDL_Point point) {
    return {(float) point.x, (float) point.y};
}

SDL_Point FPointToPoint(SDL_FPoint point) {
    return {(int) point.x, (int) point.y};
}