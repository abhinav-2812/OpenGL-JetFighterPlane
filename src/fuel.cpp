#include "fuel.h"
#include "main.h"

#define GLM_ENABLE_EXPERIMENTAL

Fuel::Fuel(float x, float y, float z, color_t color) {
    this->position = glm::vec3(x, y, z);
    speed = 0.1;
    // this->r = glm::mat4(1.0f);
    // Our vertices. Three consecutive floats give a 3D vertex; Three
    // consecutive vertices give a triangle. A cube has 6 faces with 2 triangles
    // each, so this makes 6*2=12 triangles, and 12*3 vertices
    float x1 = 1.0;
    float x2 = -1.0;
    float z1 = x1;
    float z2 = x2;
    float y1 = 2.0;
    float y2 = -2.0;
    static GLfloat vertex_buffer_data[] = {
        x2, y1, z2, x1, y1, z2, x1, y1, z1, x1, y1, z1, x2, y1, z1, x2, y1, z2,
        x2, y2, z2, x1, y2, z2, x1, y2, z1, x1, y2, z1, x2, y2, z1, x2, y2, z2,
        x2, y1, z1, x2, y1, z2, x2, y2, z2, x2, y2, z2, x2, y2, z1, x2, y1, z1,
        x1, y1, z1, x1, y1, z2, x1, y2, z2, x1, y2, z2, x1, y2, z1, x1, y1, z1,
        x2, y1, z1, x1, y1, z1, x1, y2, z1, x1, y2, z1, x2, y2, z1, x2, y1, z1,
        x2, y1, z2, x1, y1, z2, x1, y2, z2, x1, y2, z2, x2, y2, z2, x2, y1, z2};

    this->object =
        create3DObject(GL_TRIANGLES, 36, vertex_buffer_data, color, GL_FILL);
}

void Fuel::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate(this->position);  // glTranslatef
    // glm::mat4 rotate_x = glm::rotate((float)(this->rotation.x * M_PI /
    // 180.0f),
    //                                  glm::vec3(1, 0, 0));
    glm::mat4 rotate_y = glm::rotate((float)(this->rotation.y * M_PI / 180.0f),
                                     glm::vec3(0, 1, 0));
    // glm::mat4 rotate_z = glm::rotate((float)(this->rotation.z * M_PI /
    // 180.0f),
    //                                  glm::vec3(0, 0, 1));

    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to
    // rotate rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    // this->r *= rotate_y * rotate_x * rotate_z;
    Matrices.model *= (translate * rotate_y);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Fuel::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Fuel::tick() {
    this->rotation += speed;
    // this->position.x -= speed;
    // this->position.y -= speed;
}
