#include "main.h"

#ifndef PARACHUTE_H
#define PARACHUTE_H

class Parachute {
   public:
    Parachute() {}
    Parachute(float x, float y, float z, color_t color);
    glm::vec3 position;
    glm::vec3 rotation;
    glm::mat4 r;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick();
    double speed;
    // int view;
    int alive = true;

    VAO *object;
};

#endif  // PLANE_H
