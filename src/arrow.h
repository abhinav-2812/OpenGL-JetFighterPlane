#include "main.h"

#ifndef ARROW_H
#define ARROW_H

class Arrow {
   public:
    Arrow() {}
    Arrow(float x, float y, float z, color_t color);
    glm::vec3 position;
    glm::vec3 rotation;
    glm::mat4 r;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick();
    double speed;
    int view;
    int alive = true;

    VAO *object;
};

#endif  // PLANE_H
