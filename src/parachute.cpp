#include "parachute.h"
#include "main.h"

#define GLM_ENABLE_EXPERIMENTAL

Parachute::Parachute(float x, float y, float z, color_t color) {
    this->position = glm::vec3(x, y, z);
    this->rotation.x = 0;
    this->rotation.y = 0;
    this->rotation.z = 0;
    speed = 1;
    this->r = glm::mat4(1.0f);
    // Our vertices. Three consecutive floats give a 3D vertex; Three
    // consecutive vertices give a triangle. A cube has 6 faces with 2 triangles
    // each, so this makes 6*2=12 triangles, and 12*3 vertices
    float x1 = 0.5;
    float x2 = -0.5;
    float z1 = x1;
    float z2 = x2;
    float y1 = 0.5;
    float y2 = -0.5;
    static GLfloat vertex_buffer_data0[1000] = {
        x2, y1, z2, x1, y1, z2, x1, y1, z1, x1, y1, z1, x2, y1, z1, x2, y1, z2,
        x2, y2, z2, x1, y2, z2, x1, y2, z1, x1, y2, z1, x2, y2, z1, x2, y2, z2,
        x2, y1, z1, x2, y1, z2, x2, y2, z2, x2, y2, z2, x2, y2, z1, x2, y1, z1,
        x1, y1, z1, x1, y1, z2, x1, y2, z2, x1, y2, z2, x1, y2, z1, x1, y1, z1,
        x2, y1, z1, x1, y1, z1, x1, y2, z1, x1, y2, z1, x2, y2, z1, x2, y1, z1,
        x2, y1, z2, x1, y1, z2, x1, y2, z2, x1, y2, z2, x2, y2, z2, x2, y1, z2};
    int j = 108;
    static GLfloat color_buffer_data0[120000];
    for (int i = 0; i < 36; i++) {
        vertex_buffer_data0[j + 0] =
            1.3 * cos(10.0 * M_PI * (double)(i) / 180.0);
        vertex_buffer_data0[j + 2] =
            1.3 * sin(10.0 * M_PI * (double)(i) / 180.0);
        vertex_buffer_data0[j + 1] = 2.1;
        vertex_buffer_data0[j + 3] =
            1.3 * cos(10.0 * M_PI * (double)(i + 1) / 180.0);
        vertex_buffer_data0[j + 5] =
            1.3 * sin(10.0 * M_PI * (double)(i + 1) / 180.0);
        vertex_buffer_data0[j + 4] = 2.1;
        vertex_buffer_data0[j + 6] =
            1.0 * cos(10.0 * M_PI * (double)(i) / 180.0);
        vertex_buffer_data0[j + 8] =
            1.0 * sin(10.0 * M_PI * (double)(i) / 180.0);
        vertex_buffer_data0[j + 7] = 7.0;
        j += 9;
    }
    for (int i = 0; i < 36; i++) {
        vertex_buffer_data0[j + 0] =
            1.0 * cos(10.0 * M_PI * (double)(i + 1) / 180.0);
        vertex_buffer_data0[j + 2] =
            1.0 * sin(10.0 * M_PI * (double)(i + 1) / 180.0);
        vertex_buffer_data0[j + 1] = 7.0;
        vertex_buffer_data0[j + 3] =
            1.0 * cos(10.0 * M_PI * (double)(i) / 180.0);
        vertex_buffer_data0[j + 5] =
            1.0 * sin(10.0 * M_PI * (double)(i) / 180.0);
        vertex_buffer_data0[j + 4] = 7.0;
        vertex_buffer_data0[j + 6] =
            1.3 * cos(10.0 * M_PI * (double)(i + 1) / 180.0);
        vertex_buffer_data0[j + 8] =
            1.3 * sin(10.0 * M_PI * (double)(i + 1) / 180.0);
        vertex_buffer_data0[j + 7] = 2.1;
        j += 9;
    }
    for (int i = 0; i < 756; i += 3) {
        color_buffer_data0[i] = 52.0 / 256.0;
        color_buffer_data0[i + 1] = 73.0 / 256.0;
        color_buffer_data0[i + 2] = 94.0 / 256.0;
    }

    this->object = create3DObject(GL_TRIANGLES, 1000, vertex_buffer_data0,
                                  color_buffer_data0, GL_FILL);
    // this->object[1] =
    //     create3DObject(GL_TRIANGLES, 1000, vertex_buffer_data1, color,
    //     GL_FILL);
}

void Parachute::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate(this->position);  // glTranslatef
    // glm::mat4 rotate_x = glm::rotate((float)(this->rotation.x * M_PI /
    // 180.0f),
    //                                  glm::vec3(1, 0, 0));
    // glm::mat4 rotate_y = glm::rotate((float)(this->rotation.y * M_PI /
    // 180.0f),
    //                                  glm::vec3(0, 1, 0));
    // glm::mat4 rotate_z = glm::rotate((float)(this->rotation.z * M_PI /
    // 180.0f),
    //                                  glm::vec3(0, 0, 1));

    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to
    // rotate rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    // this->r *= rotate_y * rotate_x * rotate_z;
    Matrices.model *= (translate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
    // draw3DObject(this->object[1]);
    // this->rotation.x = 0;
    // this->rotation.y = 0;
    // this->rotation.z = 0;
}

void Parachute::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Parachute::tick() {
    this->position.y -= 0.05;
    this->position.z += 0.05;
    // this->rotation += speed;
    // this->position.x -= speed;
    // this->position.y -= speed;
}
