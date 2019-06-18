#include "missile.h"
#include "main.h"

#define GLM_ENABLE_EXPERIMENTAL

Missile::Missile(float x, float y, float z, color_t color) {
    this->position = glm::vec3(x, y, z);
    this->rotation.x = 0;
    this->rotation.y = 0;
    this->rotation.z = 0;
    speed = 1;
    this->r = glm::mat4(1.0f);
    // Our vertices. Three consecutive floats give a 3D vertex; Three
    // consecutive vertices give a triangle. A cube has 6 faces with 2 triangles
    // each, so this makes 6*2=12 triangles, and 12*3 vertices
    static GLfloat vertex_buffer_data[120000];
    int j = 0;
    for (int i = 0; i < 36; i++) {
        vertex_buffer_data[j + 0] =
            0.3 * cos(10.0 * M_PI * (double)(i) / 180.0);
        vertex_buffer_data[j + 1] =
            0.3 * sin(10.0 * M_PI * (double)(i) / 180.0);
        vertex_buffer_data[j + 2] = 0.0;
        vertex_buffer_data[j + 3] =
            0.3 * cos(10.0 * M_PI * (double)(i + 1) / 180.0);
        vertex_buffer_data[j + 4] =
            0.3 * sin(10.0 * M_PI * (double)(i + 1) / 180.0);
        vertex_buffer_data[j + 5] = 0.0;
        vertex_buffer_data[j + 6] =
            0.3 * cos(10.0 * M_PI * (double)(i) / 180.0);
        vertex_buffer_data[j + 7] =
            0.3 * sin(10.0 * M_PI * (double)(i) / 180.0);
        vertex_buffer_data[j + 8] = -2.0;
        j += 9;
    }
    j = 324;
    for (int i = 0; i < 36; i++) {
        vertex_buffer_data[j + 0] =
            0.3 * cos(10.0 * M_PI * (double)(i + 1) / 180.0);
        vertex_buffer_data[j + 1] =
            0.3 * sin(10.0 * M_PI * (double)(i + 1) / 180.0);
        vertex_buffer_data[j + 2] = -2.0;
        vertex_buffer_data[j + 3] =
            0.3 * cos(10.0 * M_PI * (double)(i) / 180.0);
        vertex_buffer_data[j + 4] =
            0.3 * sin(10.0 * M_PI * (double)(i) / 180.0);
        vertex_buffer_data[j + 5] = -2.0;
        vertex_buffer_data[j + 6] =
            0.3 * cos(10.0 * M_PI * (double)(i + 1) / 180.0);
        vertex_buffer_data[j + 7] =
            0.3 * sin(10.0 * M_PI * (double)(i + 1) / 180.0);
        vertex_buffer_data[j + 8] = 0.0;
        j += 9;
    }
    for (int i = 0; i < 36; i++) {
        vertex_buffer_data[j + 0] =
            0.3 * cos(10.0 * M_PI * (double)(i + 1) / 180.0);
        vertex_buffer_data[j + 1] =
            0.3 * sin(10.0 * M_PI * (double)(i + 1) / 180.0);
        vertex_buffer_data[j + 2] = -2.0;
        vertex_buffer_data[j + 3] =
            0.3 * cos(10.0 * M_PI * (double)(i) / 180.0);
        vertex_buffer_data[j + 4] =
            0.3 * sin(10.0 * M_PI * (double)(i) / 180.0);
        vertex_buffer_data[j + 5] = -2.0;
        vertex_buffer_data[j + 6] = 0.0;
        vertex_buffer_data[j + 7] = 0.0;
        vertex_buffer_data[j + 8] = -2.3;
        j += 9;
    }

    this->object =
        create3DObject(GL_TRIANGLES, 1000, vertex_buffer_data, color, GL_FILL);
}

void Missile::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate(this->position);  // glTranslatef
    glm::mat4 scale = glm::scale(glm::vec3(0.5, 0.5, 0.5));
    glm::mat4 rotate_x = glm::rotate((float)(this->rotation.x * M_PI / 180.0f),
                                     glm::vec3(1, 0, 0));
    glm::mat4 rotate_y = glm::rotate((float)(this->rotation.y * M_PI / 180.0f),
                                     glm::vec3(0, 1, 0));
    glm::mat4 rotate_z = glm::rotate((float)(this->rotation.z * M_PI / 180.0f),
                                     glm::vec3(0, 0, 1));

    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to
    // rotate rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    this->r *= rotate_y * rotate_x * rotate_z;
    Matrices.model *= (translate * scale * this->r);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
    this->rotation.x = 0;
    this->rotation.y = 0;
    this->rotation.z = 0;
}

void Missile::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Missile::tick() {
    // this->rotation += speed;
    // this->position.x -= speed;
    // this->position.y -= speed;
}
