#pragma once

#include <SDL2/SDL.h>
#include <iostream>
#include <cmath>
#include <cstdlib>
#include <random>

#define PI 3.14159265

SDL_FPoint makeComplex(const float& x, const float& y);
SDL_Point makePoint(const int& x, const int& y);
SDL_FPoint makeComplexExp(const float& r, const float& theta);

SDL_FPoint operator+ (const SDL_FPoint& a, const SDL_FPoint& b);
void operator+= (SDL_FPoint& a, const SDL_FPoint& b);

SDL_FPoint operator- (const SDL_FPoint& a, const SDL_FPoint& b);
SDL_FPoint operator- (const SDL_FPoint& z);
void operator-= (SDL_FPoint& a, const SDL_FPoint& b);
SDL_Point operator- (const SDL_Point& a, const SDL_Point& b);
SDL_Point operator- (const SDL_Point& z);
void operator-= (SDL_Point& a, const SDL_Point& b);

SDL_FPoint operator* (const float& lambda, const SDL_FPoint& z);
SDL_FPoint operator* (const SDL_FPoint& z, const float& lambda);
void operator*= (SDL_FPoint& z, const float& lambda);
SDL_Point operator* (const int& lambda, const SDL_Point& z);
SDL_Point operator* (const SDL_Point& z, const int& lambda);
void operator*= (SDL_Point& z, const int& lambda);

SDL_FPoint operator* (const SDL_FPoint& a, const SDL_FPoint& b);
void operator*= (SDL_FPoint& a, const SDL_FPoint& b);

SDL_FPoint operator/ (const SDL_FPoint& z, const float& lambda);
void operator/= (SDL_FPoint& z, const float& lambda);

SDL_FPoint operator/ (const float& lambda, const SDL_FPoint& z);
SDL_FPoint operator/ (const SDL_FPoint& a, const SDL_FPoint& b);
void operator/= (SDL_FPoint& a, const SDL_FPoint& b);

bool operator== (const SDL_FPoint& a, const SDL_FPoint& b);
bool operator!= (const SDL_FPoint& a, const SDL_FPoint& b);

SDL_FPoint conjugue(const SDL_FPoint& z);

float rad(const float& deg);
float deg(const float& rad);

SDL_FPoint scaleComplex(const SDL_FPoint& z, const SDL_FPoint& z0, const float& lambda);
SDL_FPoint rotateComplex(const SDL_FPoint& z, const SDL_FPoint& z0, const float& theta_deg);

float module(const SDL_FPoint& z);
float module(const SDL_Point& z);

int randInt(const int& start, const int& end);
float randFloat(const float& start, const float& end);
SDL_FPoint randComplex(const float& start, const float& end);
SDL_FPoint randComplex(const float& startX, const float& endX, const float& startY, const float& endY);

SDL_FPoint PointToFPoint(SDL_Point point);
SDL_Point FPointToPoint(SDL_FPoint point);