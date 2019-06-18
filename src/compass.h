#include "main.h"
#define GLM_ENABLE_EXPERIMENTAL
#ifndef COMPASS_H
#define COMPASS_H

class Compass {
   public:
    Compass() {}
    Compass(float x, float y, color_t color);
    glm::vec3 position;
    glm::mat4 r;
    float rotation;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick(double x, double y, double z);

   private:
    VAO *object;
};

#endif  // BALL_H