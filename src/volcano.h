#include "main.h"

#ifndef VOLCANO_H
#define VOLCANO_H

class Volcano {
   public:
    Volcano() {}
    Volcano(float x, float y, float z, color_t color);
    glm::vec3 position;
    glm::vec3 rotation;
    // glm::mat4 r;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick();
    double speed;
    // int view;

   private:
    VAO *object;
};

#endif  // SEA_H
