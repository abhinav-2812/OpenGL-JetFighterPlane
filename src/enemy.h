#include "main.h"

#ifndef ENEMY_H
#define ENEMY_H

class Enemy {
   public:
    Enemy() {}
    Enemy(float x, float y, float z, color_t color);
    glm::vec3 position;
    glm::vec3 rotation;
    glm::mat4 r;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick();
    double speed;
    // int view;
    int alive = true;
    int health = 50;

    VAO *object[2];
};

#endif  // PLANE_H
