#include "main.h"

#ifndef MISSILE_H
#define MISSILE_H

class Missile {
   public:
    Missile() {}
    Missile(float x, float y, float z, color_t color);
    glm::vec3 position;
    glm::vec3 rotation;
    glm::mat4 r;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick();
    double speed;
    int view;
    bool fired = false;

   private:
    VAO *object;
};

#endif  // PLANE_H
