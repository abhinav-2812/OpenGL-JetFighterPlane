#include "compass.h"
#include "main.h"

#define GLM_ENABLE_EXPERIMENTAL
Compass::Compass(float x, float y, color_t color) {
    this->position = glm::vec3(x, y, 0);
    this->rotation = 0;
    // Our vertices. Three consecutive floats give a 3D vertex; Three
    // consecutive vertices give a triangle. A cube has 6 faces with 2 triangles
    // each, so this makes 6*2=12 triangles, and 12*3 vertices
    static const GLfloat vertex_buffer_data[1000] = {
        -1.0, 1.0,  0.0, 1.0, 1.0,  0.0, 0.0, 10.0,  0.0,
        -1.0, -1.0, 0.0, 1.0, -1.0, 0.0, 0.0, -10.0, 0.0};

    static GLfloat color_buffer_data[18];
    for (int i = 0; i < 9; i += 3) {
        color_buffer_data[i] = 128.0 / 256.0;
        color_buffer_data[i + 1] = 128.0 / 256.0;
        color_buffer_data[i + 2] = 128.0 / 256.0;
    }
    for (int i = 9; i < 2 * 9; i += 3) {
        color_buffer_data[i] = 255.0 / 256.0;
        color_buffer_data[i + 1] = 0.0 / 256.0;
        color_buffer_data[i + 2] = 0.0 / 256.0;
    }

    this->object = create3DObject(GL_TRIANGLES, 2 * 3, vertex_buffer_data,
                                  color_buffer_data, GL_FILL);
}

void Compass::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate(this->position);  // glTranslatef
    // glm::mat4 rotate = glm::rotate((float)(this->rotation * M_PI / 18
    // - 2.0f),
    //                                glm::vec3(1, 0, 0));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to
    // rotate rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= ((translate) * this->r);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Compass::tick(double x, double y, double z) {
    //
    this->r =
        glm::rotate((float)((atan2(z, x) - M_PI / 2.0)), glm::vec3(0, 0, 1));
}
