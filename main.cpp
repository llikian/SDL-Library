#include "src/mainLib.hpp"

class Particle {
public:
    SDL_FPoint position;
    SDL_FPoint speed;
    SDL_FPoint force;
    float mass;
    int radius;
    static float DT;
    static float friction;

    Particle(SDL_FPoint position, float mass, int radius) : position{position}, force{0, 9.81}, mass{mass}, radius{radius} {
        speed = {randFloat(-50, 50), randFloat(-50, 50)};
    }

    Particle() : position{}, speed{}, force{}, mass{}, radius{} { }

    void update(const SDL &sdl) {
        force = {0, 9.81};

        position += DT*speed;
        speed += DT*force/mass;

        if(position.x < (float)radius) {
            ++position.x;
            speed.x *= -friction;
        } else if(position.x > (float)(sdl.DX - radius)) {
            --position.x;
            speed.x *= -friction;
        }

        if(position.y < (float)radius) {
            ++position.y;
            speed.y *= -friction;
        } else if(position.y > (float)(sdl.DY - radius)) {
            --position.y;
            speed.y *= -friction;
        }
    }

    void draw(const SDL& sdl, SDL_Color color) const{
        sdl.fillCircle(FPointToPoint(position), radius, color);
    }
};

class World {
public:
    SDL sdl;
    Particle* particles;
    int num;

    World(int num) : sdl{1200, 700}, num{num} {
        particles = new Particle[num];
        for(int i = 0 ; i < num ; ++i) {
            particles[i] = Particle(PointToFPoint(sdl.CENTER), 1, 5);
        }
    }

    ~World() {
        delete[] particles;
    }

    void update() const{
        for(int i = 0 ; i < num ; ++i) {
            particles[i].update(sdl);
        }
    }

    void draw() const{
        for(int i = 0 ; i < num ; ++i) {
            particles[i].draw(sdl, {(Uint8)(255.f*particles[i].position.x/(float)sdl.DX), 0, (Uint8)(255.f*particles[i].position.y/(float)sdl.DY)});
        }
    }
};

float Particle::DT = 1.f/60.f;
float Particle::friction = .9f;

int main([[maybe_unused]]int argc, [[maybe_unused]]char* argv[]) {
    World world{20};
    Uint32 ticks{};

    // Main Loop
    while(!world.sdl.stop) {
        world.sdl.getKeyboardState();
        Particle::DT = 5.f*(float)(SDL_GetTicks() - ticks)/1000.f;
        ticks = SDL_GetTicks();

        // Main Functions
        world.draw();
        world.update();

        world.sdl.clearAndUpdate(BG_COLOR);
        world.sdl.quitWindow();
    }

	return 0;
}