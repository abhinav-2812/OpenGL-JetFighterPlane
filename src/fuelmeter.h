#include "main.h"
#define GLM_ENABLE_EXPERIMENTAL
#ifndef FUELMETER_H
#define FUELMETER_H

class Fuelmeter {
   public:
    Fuelmeter() {}
    Fuelmeter(float x, float y, color_t color);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP, int d);
    void set_position(float x, float y);
    void tick();
    float flag = 3000.0;

   private:
    VAO *object[11];
};

#endif  // BALL_H