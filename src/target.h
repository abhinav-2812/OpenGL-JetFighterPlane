#include "main.h"

#ifndef TARGET_H
#define TARGET_H

class Target {
   public:
    Target() {}
    Target(float x, float y, float z, color_t color);
    glm::vec3 position;
    glm::vec3 rotation;
    glm::mat4 r;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick();
    double speed;
    int view;
    int alive = true;

    VAO *object[3];
};

#endif  // PLANE_H
