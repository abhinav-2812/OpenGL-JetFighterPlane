#include "main.h"

#ifndef PLANE_H
#define PLANE_H

class Plane {
   public:
    Plane() {}
    Plane(float x, float y, float z, color_t color);
    glm::vec3 position;
    glm::vec3 rotation;
    glm::mat4 r;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick();
    double speed;
    int view = 4;
    double fuel = 100;
    int score = 0;
    int health = 50;
    double distance = 0;

   private:
    VAO *object;
};

#endif  // PLANE_H
