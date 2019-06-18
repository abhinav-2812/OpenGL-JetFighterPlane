#include "main.h"
#define GLM_ENABLE_EXPERIMENTAL
#ifndef SCORE_H
#define SCORE_H

class Score {
   public:
    Score() {}
    Score(float x, float y, color_t color);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP, int d);
    void set_position(float x, float y);
    void tick();
    std::string s[10];
    VAO *object[7];
};

#endif  // BALL_H