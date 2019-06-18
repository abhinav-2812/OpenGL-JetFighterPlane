#include "main.h"
#define GLM_ENABLE_EXPERIMENTAL
#ifndef Heart_H
#define Heart_H

class Heart {
   public:
    Heart() {}
    Heart(float x, float y);
    glm::vec3 position;
    float rotation;
    double speed;
    double direction;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick();
    bool done = false;
    VAO *object;
};

#endif  // BALL_H