#include "SDL.hpp"

SDL::SDL(int DIMX, int DIMY) : DX(DIMX), DY(DIMY), CENTER{DIMX / 2, DIMY / 2}, FONTSIZE(25) {
    stop = false;

    window = nullptr;
    renderer = nullptr;
    font = nullptr;

    if(SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cout << "SDL was not initialized, SDL Error: " << SDL_GetError() << std::endl;
        stop = true;
    }

    if(IMG_Init(IMG_INIT_PNG) < 0) {
        std::cout << "SDL_Image was not initialized, SDL Error: " << SDL_GetError() << std::endl;
        stop = true;
    }

    if(Mix_Init(MIX_INIT_MP3 | MIX_INIT_OGG | MIX_INIT_FLAC | MIX_INIT_MOD) < 0) {
        std::cout << "SDL_Mixer was not initialized, SDL Error: " << SDL_GetError() << std::endl;
        stop = true;
    }

    if(TTF_Init() < 0) {
        std::cout << "SDL_ttf was not initialized, SDL Error: " << SDL_GetError() << std::endl;
        stop = true;
    }

    window = SDL_CreateWindow("SDL Tutos", 0x2FFF0000u, 0x2FFF0000u, DX, DY, SDL_WINDOW_SHOWN);
    if(window == nullptr) {
        std::cout << "Window not created, SDL Error: " << SDL_GetError() << std::endl;
        stop = true;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if(renderer == nullptr) {
        std::cout << "Renderer not created, SDL Error: " << SDL_GetError() << std::endl;
        stop = true;
    }

    if(Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096) < 0) {
        std::cout << "Audio not opened, SDL Error: " << SDL_GetError() << std::endl;
        stop = true;
    }
    Mix_AllocateChannels(16);

    font = TTF_OpenFont("data/courbd.ttf", FONTSIZE);
    if(font == nullptr) {
        std::cout << "Font not created, SDL Error: " << SDL_GetError() << std::endl;
        stop = true;
    }

//    SDL_ShowCursor(SDL_DISABLE);
}

SDL::~SDL() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    Mix_CloseAudio();
    TTF_CloseFont(font);

    SDL_Quit();
    IMG_Quit();
    Mix_Quit();
    TTF_Quit();
}

void SDL::quitWindow() {
    while(SDL_PollEvent(&event)) {
        if(event.type == SDL_QUIT || keyboard[SDL_SCANCODE_ESCAPE]) {
            stop = true;
        }
    }
}

void SDL::clearAndUpdate(SDL_Color backgroundColor) const {
    SDL_RenderPresent(renderer);
    setColor(backgroundColor);
    SDL_RenderClear(renderer);
}

void SDL::getKeyboardState() {
    keyboard = SDL_GetKeyboardState(nullptr);
}

void SDL::setColor(SDL_Color color) const {
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
}

void SDL::drawPoint(SDL_Point point, SDL_Color color) const {
    setColor(color);
    SDL_RenderDrawPoint(renderer, (int) point.x, (int) point.y);
}

void SDL::drawCircle(SDL_Point center, int radius, SDL_Color color) const {
    int x = 0, y = radius;
    SDL_Point points[8];

    setColor(color);

    while(x <= y) {
        points[0] = {x, y};
        points[1] = {-x, y};
        points[2] = {x, -y};
        points[3] = {-x, -y};
        points[4] = {y, x};
        points[5] = {-y, x};
        points[6] = {y, -x};
        points[7] = {-y, -x};

        for(SDL_Point& point: points) {
            point.x += center.x;
            point.y += center.y;
        }

        SDL_RenderDrawPoints(renderer, points, 8);

        ++x;
        y = (int) sqrt(radius * radius - x * x);
    }
}

void SDL::drawThickCircle(SDL_Point center, int radius, int thickness, SDL_Color color) const {
    int x = 0, y = radius;
    SDL_Point points[8];

    setColor(color);

    while(x <= y) {
        points[0] = {x, y};
        points[1] = {-x, y};
        points[2] = {x, -y};
        points[3] = {-x, -y};
        points[4] = {y, x};
        points[5] = {-y, x};
        points[6] = {y, -x};
        points[7] = {-y, -x};

        for(SDL_Point& point: points) {
            point.x += center.x;
            point.y += center.y;
        }

        for(SDL_Point point: points) {
            fillCircle(point, thickness, color);
        }

        ++x;
        y = (int) sqrt(radius * radius - x * x);
    }
}

void SDL::fillCircle(SDL_Point center, int radius, SDL_Color color) const {
    int x = 0, y = radius, a, b, c, d;

    setColor(color);

    while(x <= radius) {
        a = center.x + x;
        b = center.y + y;
        c = center.x - x;
        d = center.y - y;

        SDL_RenderDrawLine(renderer, a, b, a, d);
        SDL_RenderDrawLine(renderer, c, b, c, d);

        ++x;
        y = (int) sqrt(radius * radius - x * x);
    }
}

void SDL::drawUpperArc(SDL_Point center, int radius, SDL_Color color) const {
    int x = 0, y = radius;
    SDL_Point points[4];

    setColor(color);

    while(x <= y) {
        points[0] = {y, -x};
        points[1] = {-y, -x};
        points[2] = {x, -y};
        points[3] = {-x, -y};

        for(SDL_Point& point: points) {
            point.x += center.x;
            point.y += center.y;
        }

        SDL_RenderDrawPoints(renderer, points, 4);

        ++x;
        y = (int) sqrt(radius * radius - x * x);
    }
}

void SDL::drawLowerArc(SDL_Point center, int radius, SDL_Color color) const {
    int x = 0, y = radius;
    SDL_Point points[4];

    setColor(color);

    while(x <= y) {
        points[0] = {y, x};
        points[1] = {-y, x};
        points[2] = {x, y};
        points[3] = {-x, y};

        for(SDL_Point& point: points) {
            point.x += center.x;
            point.y += center.y;
        }

        SDL_RenderDrawPoints(renderer, points, 4);

        ++x;
        y = (int) sqrt(radius * radius - x * x);
    }
}

void SDL::outlinedCircle(SDL_Point center, int radius, SDL_Color filling, SDL_Color outline) const {
    fillCircle(center, radius, filling);
    drawCircle(center, radius, outline);
}

void SDL::drawLine(SDL_Point start, SDL_Point end, SDL_Color color) const {
    setColor(color);
    SDL_RenderDrawLine(renderer, start.x, start.y, end.x, end.y);
}

void SDL::drawLines(SDL_Point* vertices, int nVertex, SDL_Color color) const {
    setColor(color);
    SDL_RenderDrawLines(renderer, vertices, nVertex);
}

void SDL::drawPolygon(SDL_Point* vertices, int nVertex, SDL_Color color) const {
    setColor(color);
    SDL_RenderDrawLines(renderer, vertices, nVertex);
    SDL_RenderDrawLine(renderer, vertices[nVertex - 1].x, vertices[nVertex - 1].y, vertices[0].x, vertices[0].y);
}

void SDL::drawRegularPolygon(SDL_Point center, int nVertex, int radius, SDL_Color color) const {
    float rotationAngle = 360.f / (float) nVertex;
    SDL_FPoint fCenter = makeComplex((float) center.x, (float) (center.y));

    SDL_FPoint vertices[nVertex];
    vertices[0] = fCenter;
    vertices[0].y -= (float) radius;

    for(int i = 1 ; i < nVertex ; ++i) {
        vertices[i] = rotateComplex(vertices[i - 1], fCenter, rotationAngle);
    }

    setColor(color);
    SDL_RenderDrawLinesF(renderer, vertices, nVertex);
    SDL_RenderDrawLineF(renderer, vertices[nVertex - 1].x, vertices[nVertex - 1].y, vertices[0].x, vertices[0].y);
}

void SDL::drawRegularThickPolygon(SDL_Point center, int nVertex, int radius, int thickness, SDL_Color color) const {
    float rotationAngle = 360.f / (float) nVertex;
    SDL_FPoint fCenter = makeComplex((float) center.x, (float) (center.y));

    SDL_FPoint vertices[nVertex];
    vertices[0] = fCenter;
    vertices[0].y -= (float) radius;

    for(int i = 1 ; i < nVertex ; ++i) {
        vertices[i] = rotateComplex(vertices[i - 1], fCenter, rotationAngle);
        drawThickLine(FPointToPoint(vertices[i-1]), FPointToPoint(vertices[i]), thickness, color);
    }
    drawThickLine(FPointToPoint(vertices[nVertex-1]), FPointToPoint(vertices[0]), thickness, color);
}

void SDL::drawRegularThickPolygon(SDL_Point center, int nVertex, int radius, int thickness, float thetaDeg, SDL_Color color) const {
    float rotationAngle = 360.f / (float) nVertex;
    SDL_FPoint fCenter = makeComplex((float) center.x, (float) (center.y));

    SDL_FPoint vertices[nVertex];
    vertices[0] = rotateComplex({fCenter.x, fCenter.y-(float)radius}, fCenter, thetaDeg);

    for(int i = 1 ; i < nVertex ; ++i) {
        vertices[i] = rotateComplex(vertices[i - 1], fCenter, rotationAngle);
        drawThickLine(FPointToPoint(vertices[i-1]), FPointToPoint(vertices[i]), thickness, color);
    }
    drawThickLine(FPointToPoint(vertices[nVertex-1]), FPointToPoint(vertices[0]), thickness, color);
}

void SDL::fillRegularPolygon(SDL_Point center, int nVertex, int radius, SDL_Color color) const {
    float rotationAngle = 360.f / (float) nVertex;
    SDL_FPoint fCenter = makeComplex((float) center.x, (float) (center.y));

    SDL_FPoint vertices[nVertex];
    vertices[0] = fCenter;
    vertices[0].y -= (float) radius;

    for(int i = 1 ; i <= nVertex ; ++i) {
        vertices[i] = rotateComplex(vertices[i - 1], fCenter, rotationAngle);
        fillTriangle(center, FPointToPoint(vertices[i % nVertex]), FPointToPoint(vertices[i - 1]), color);
    }
}

void SDL::fillRegularPolygon(SDL_Point center, int nVertex, int radius, float thetaDeg, SDL_Color color) const {
    float rotationAngle = 360.f / (float) nVertex;
    SDL_FPoint fCenter = makeComplex((float) center.x, (float) (center.y));

    SDL_FPoint vertices[nVertex];
    vertices[0] = rotateComplex({fCenter.x, fCenter.y-(float)radius}, fCenter, thetaDeg);

    for(int i = 1 ; i <= nVertex ; ++i) {
        vertices[i] = rotateComplex(vertices[i - 1], fCenter, rotationAngle);
        fillTriangle(center, FPointToPoint(vertices[i % nVertex]), FPointToPoint(vertices[i - 1]), color);
    }
}

void SDL::fillTriangle(SDL_Point A, SDL_Point B, SDL_Point C, SDL_Color color) const {
    setColor(color);

    if(A.y < B.y) {
        std::swap(A, B);
    }
    if(A.y < C.y) {
        std::swap(A, C);
    }
    if(B.y < C.y) {
        std::swap(B, C);
    }

    // The interpolation coefficient between A and C where the height is the same as B
    const float t = (float) (B.y - A.y) / (float) (C.y - A.y);
    // The point at the same height as B on segment AC
    SDL_FPoint H{(1 - t) * (float) A.x + t * (float) C.x, (float) B.y};

    int ABx = B.x - A.x, AHx = (int) H.x - A.x;
    int ABy = B.y - A.y, AHy = (int) H.y - A.y;

    if(ABy && AHy) {
        // Line equations ax+b=y
        float aAB = (ABx) ? (float) ABy / (float) ABx : (float) ABy;
        float aAH = (AHx) ? (float) AHy / (float) AHx : (float) AHy;

        float bAB = (float) A.y - aAB * (float) A.x, bAH = (float) A.y - aAH * (float) A.x;

        for(int y = B.y ; y < A.y ; ++y) {
            SDL_RenderDrawLine(renderer, (int) (((float) y - bAB) / aAB), y, (int) (((float) y - bAH) / aAH), y);
        }
    }

    int CBx = (B - C).x, CHx = (int) H.x - C.x;
    int CBy = (B - C).y, CHy = (int) H.y - C.y;

    if(CBy && CHy) {
        // Line equations ax+b=y
        float aCB = (CBx) ? (float) CBy / (float) CBx : (float) CBy;
        float aCH = (CHx) ? (float) CHy / (float) CHx : (float) CHy;

        float bCB = (float) C.y - aCB * (float) C.x, bCH = (float) C.y - aCH * (float) C.x;

        for(int y = B.y ; y > C.y ; --y) {
            SDL_RenderDrawLine(renderer, (int) (((float) y - bCB) / aCB), y, (int) (((float) y - bCH) / aCH), y);
        }
    }
}

void SDL::drawText(const char* text, SDL_Point pos, SDL_Color color) const {
    SDL_Surface* surface = TTF_RenderText_Solid(font, text, color);
    if(!surface) {
        std::cout << "Text not rendered, SDL Error: " << SDL_GetError() << std::endl;
        return;
    }

    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    if(!texture) {
        std::cout << "Texture not created, SDL Error: " << SDL_GetError() << std::endl;
        SDL_FreeSurface(surface);
        return;
    }

    SDL_Rect rect = {pos.x, pos.y, surface->w, surface->h};
    SDL_RenderCopy(renderer, texture, nullptr, &rect);

    SDL_DestroyTexture(texture);
    SDL_FreeSurface(surface);
}

void SDL::drawText(const std::string& text, SDL_Point pos, SDL_Color color) const {
    drawText(text.c_str(), pos, color);
}

void SDL::drawTextCentered(const char* text, SDL_Rect reference, SDL_Color color) const {
    SDL_Surface* surface = TTF_RenderText_Solid(font, text, color);
    if(!surface) {
        std::cout << "Text not rendered, SDL Error: " << SDL_GetError() << std::endl;
        return;
    }

    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    if(!texture) {
        std::cout << "Texture not created, SDL Error: " << SDL_GetError() << std::endl;
        SDL_FreeSurface(surface);
        return;
    }

    SDL_Rect rect = {reference.x, reference.y, surface->w, surface->h};
    rect.x += (reference.w - surface->w) / 2;
    rect.y += (reference.h - surface->h) / 2;

    SDL_RenderCopy(renderer, texture, nullptr, &rect);

    SDL_DestroyTexture(texture);
    SDL_FreeSurface(surface);
}

void SDL::drawTextCentered(const std::string& text, SDL_Rect reference, SDL_Color color) const {
    drawTextCentered(text.c_str(), reference, color);
}

void SDL::drawThickLine(SDL_Point start, SDL_Point end, int thickness, SDL_Color color) const {
    int dx = end.x - start.x, dy = end.y - start.y;
    int steps = (abs(dx) > abs(dy)) ? abs(dx) : abs(dy);

    float ix = (float) dx / (float) steps;
    float iy = (float) dy / (float) steps;

    auto x = (float) start.x, y = (float) start.y;
    for(int i = 0 ; i <= steps ; ++i) {
        fillCircle({(int) x, (int) y}, thickness, color);
        x += ix;
        y += iy;
    }
}