#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>

#include "color_functions.hpp"
#include "complex_functions.hpp"

class SDL {
public:
    SDL(int DIMX, int DIMY);

    ~SDL();

    SDL_Window* window;
    SDL_Renderer* renderer;
    TTF_Font* font;

    // The width of the window.
    const int DX;
    // The height ot the window.
    const int DY;
    // The position of the center of the window.
    const SDL_Point CENTER;
    // The size of the font.
    const int FONTSIZE;

    // False if the window is open.
    bool stop;
    // Handles every events.
    SDL_Event event{};
    // Checks the state of all keyboard keys.
    const Uint8* keyboard{};

    /**
     * \brief Checks if either the 'ESCAPE' key or the window's 'X' is pressed.
     * If it is, changes the value of SDL::stop.
     */
    void quitWindow();

    /**
     * \brief Updates the changes since the last iteration and clears previous ones off the window.
     * @param backgroundColor The color the window will be cleared with.
     */
    void clearAndUpdate(SDL_Color backgroundColor) const;

    /**
     * \brief Updates the state of SDL::keyboard
     */
    void getKeyboardState();

    /**
     * \brief Updates the drawing color
     * @param color The color it will be changed to.
     */
    void setColor(SDL_Color color) const;

    /**
     * \brief Draws a pixel.
     * @param point The position of the pixel.
     * @param color The color it will be drawn with.
     */
    void drawPoint(SDL_Point point, SDL_Color color) const;

    /**
     * \brief Draws a circle.
     * @param center The position of the circle's center.
     * @param radius The radius of the circle.
     * @param color The color it will be drawn with.
     */
    void drawCircle(SDL_Point center, int radius, SDL_Color color) const;

    /**
     * \brief Draws a circle with a thickness to its outline.
     * @param center The position of the circle's center.
     * @param radius The radius of the circle.
     * @param thickness The thickness of the outline.
     * @param color The color it will be drawn with.
     */
    void drawThickCircle(SDL_Point center, int radius, int thickness, SDL_Color color) const;

    /**
     * \brief Draws a filled circle.
     * @param center The position of the circle's center.
     * @param radius The radius of the circle.
     * @param color The color it will be drawn with.
     */
    void fillCircle(SDL_Point center, int radius, SDL_Color color) const;

    /**
     * \brief Draws the top half of a circle.
     * @param center The position of the circle's center.
     * @param radius The radius of the circle.
     * @param color The color it will be drawn with.
     */
    void drawUpperArc(SDL_Point center, int radius, SDL_Color color) const;

    /**
     * \brief Draws the bottom half of a circle.
     * @param center The position of the circle's center.
     * @param radius The radius of the circle.
     * @param color The color it will be drawn with.
     */
    void drawLowerArc(SDL_Point center, int radius, SDL_Color color) const;

    /**
     * \brief Draws a circle with a different color for the outline and the filling.
     * @param center The position of the circle's center.
     * @param radius The radius of the circle.
     * @param filling The color of the filling.
     * @param outline The color of the outline.
     */
    void outlinedCircle(SDL_Point center, int radius, SDL_Color filling, SDL_Color outline) const;

    /**
     * \brief Draws a line between two points.
     * @param start The position of the first point.
     * @param end The positoin of the second point.
     * @param color The color it will be drawn with.
     */
    void drawLine(SDL_Point start, SDL_Point end, SDL_Color color) const;

    /**
     * \brief Draws a line with a thickness to it between two points.
     * @param start The position of the first point.
     * @param end The positoin of the second point.
     * @param thickness The thickness of the line.
     * @param color The color it will be drawn with.
     */
    void drawThickLine(SDL_Point start, SDL_Point end, int thickness, SDL_Color color) const;

    /**
     * \brief Draws all the lines from the consecutive vertices of an array.
     * @param vertices Array containing all of the polygon's vertices, in order.
     * @param nVertex The number of vertices.
     * @param color The color it will be drawn with.
     */
    void drawLines(SDL_Point* vertices, int nVertex, SDL_Color color) const;

    /**
     * \brief Draws a polygon with an array of its vertices.
     * @param vertices Array containing all of the polygon's vertices, in order.
     * @param nVertex The number of vertices.
     * @param color The color it will be drawn with.
     */
    void drawPolygon(SDL_Point* vertices, int nVertex, SDL_Color color) const;

    /**
     * \brief Draws a regular polygon.
     * @param center The position of the polygon's center.
     * @param nVertex The number of vertices.
     * @param radius The radius of the polygon.
     * @param color The color it will be drawn with.
     */
    void drawRegularPolygon(SDL_Point center, int nVertex, int radius, SDL_Color color) const;

    /**
     * \brief Draws a regular polygon.
     * @param center The position of the polygon's center.
     * @param nVertex The number of vertices.
     * @param radius The radius of the polygon.
     * @param thickness The thickness of the line.
     * @param color The color it will be drawn with.
     */
    void drawRegularThickPolygon(SDL_Point center, int nVertex, int radius, int thickness, SDL_Color color) const;

    /**
     * \brief Draws a regular polygon.
     * @param center The position of the polygon's center.
     * @param nVertex The number of vertices.
     * @param radius The radius of the polygon.
     * @param thickness The thickness of the line.
     * @param color The color it will be drawn with.
     */
    void drawRegularThickPolygon(SDL_Point center, int nVertex, int radius, int thickness, float thetaDeg, SDL_Color color) const;

    /**
     * \brief Draws a filled regular polygon.
     * @param center The position of the polygon's center.
     * @param nVertex The number of vertices.
     * @param radius The radius of the polygon.
     * @param color The color it will be drawn with.
     */
    void fillRegularPolygon(SDL_Point center, int nVertex, int radius, SDL_Color color) const;

    /**
     * \brief Draws a filled regular polygon and rotates it.
     * @param center The position of the polygon's center.
     * @param nVertex The number of vertices.
     * @param radius The radius of the polygon.
     * @param rotationAngle The angle of the rotation.
     * @param color The color it will be drawn with.
     */
    void fillRegularPolygon(SDL_Point center, int nVertex, int radius, float thetaDeg, SDL_Color color) const;

    /**
     * \brief Draws a filled triangle.
     * @param A The first point.
     * @param B The second point.
     * @param C The last point.
     * @param color The color it will be drawn with.
     */
    void fillTriangle(SDL_Point A, SDL_Point B, SDL_Point C, SDL_Color color) const;

    /**
     * \brief Draws text. (char*)
     * @param text The text that will be drawn.
     * @param pos The position the text will start writing at.
     * @param color The color it will be drawn with.
     */
    void drawText(const char* text, SDL_Point pos, SDL_Color color) const;

    /**
     * \brief Draws text. (std::string)
     * @param text The text that will be drawn.
     * @param pos The position the text will start writing at.
     * @param color The color it will be drawn with.
     */
    void drawText(const std::string& text, SDL_Point pos, SDL_Color color) const;

    /**
     * \brief Draws text at the center of a reference rectangle. (char*)
     * @param text The text that will be drawn.
     * @param reference The rectangle used as reference.
     * @param color The color it will be drawn with.
     */
    void drawTextCentered(const char* text, SDL_Rect reference, SDL_Color color) const;

    /**
      * \brief Draws text at the center of a reference rectangle. (std::string)
      * @param text The text that will be drawn.
      * @param reference The rectangle used as reference.
      * @param color The color it will be drawn with.
      */
    void drawTextCentered(const std::string& text, SDL_Rect reference, SDL_Color color) const;
};