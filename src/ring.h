#include "main.h"

#ifndef RING_H
#define RING_H

class Ring {
   public:
    Ring() {}
    Ring(float x, float y, float z, color_t color);
    glm::vec3 position;
    glm::vec3 rotation;
    // glm::mat4 r;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick();
    double speed;
    int alive = true;
    // int view;

   private:
    VAO *object;
};

#endif  // SEA_H
