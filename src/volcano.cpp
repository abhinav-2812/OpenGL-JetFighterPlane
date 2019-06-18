#include "volcano.h"
#include "main.h"

#define GLM_ENABLE_EXPERIMENTAL

Volcano::Volcano(float x, float y, float z, color_t color) {
    this->position = glm::vec3(x, y, z);
    speed = 1;
    // this->r = glm::mat4(1.0f);
    // Our vertices. Three consecutive floats give a 3D vertex; Three
    // consecutive vertices give a triangle. A cube has 6 faces with 2 triangles
    // each, so this makes 6*2=12 triangles, and 12*3 vertices
    static GLfloat vertex_buffer_data[120000];
    static GLfloat color_buffer_data[120000];
    int j = 0;
    for (int i = 0; i < 36; i++) {
        vertex_buffer_data[j + 0] =
            5.0 * cos(10.0 * M_PI * (double)(i) / 180.0);
        vertex_buffer_data[j + 2] =
            5.0 * sin(10.0 * M_PI * (double)(i) / 180.0);
        vertex_buffer_data[j + 1] = 0.1;
        vertex_buffer_data[j + 3] =
            5.0 * cos(10.0 * M_PI * (double)(i + 1) / 180.0);
        vertex_buffer_data[j + 5] =
            5.0 * sin(10.0 * M_PI * (double)(i + 1) / 180.0);
        vertex_buffer_data[j + 4] = 0.1;
        vertex_buffer_data[j + 6] =
            2.0 * cos(10.0 * M_PI * (double)(i) / 180.0);
        vertex_buffer_data[j + 8] =
            2.0 * sin(10.0 * M_PI * (double)(i) / 180.0);
        vertex_buffer_data[j + 7] = 10.0;
        j += 9;
    }
    j = 324;
    for (int i = 0; i < 36; i++) {
        vertex_buffer_data[j + 0] =
            2.0 * cos(10.0 * M_PI * (double)(i + 1) / 180.0);
        vertex_buffer_data[j + 2] =
            2.0 * sin(10.0 * M_PI * (double)(i + 1) / 180.0);
        vertex_buffer_data[j + 1] = 10.0;
        vertex_buffer_data[j + 3] =
            2.0 * cos(10.0 * M_PI * (double)(i) / 180.0);
        vertex_buffer_data[j + 5] =
            2.0 * sin(10.0 * M_PI * (double)(i) / 180.0);
        vertex_buffer_data[j + 4] = 10.0;
        vertex_buffer_data[j + 6] =
            5.0 * cos(10.0 * M_PI * (double)(i + 1) / 180.0);
        vertex_buffer_data[j + 8] =
            5.0 * sin(10.0 * M_PI * (double)(i + 1) / 180.0);
        vertex_buffer_data[j + 7] = 0.1;
        j += 9;
    }
    for (int i = 0; i < 648; i += 3) {
        color_buffer_data[i] = 139.0 / 256.0;
        color_buffer_data[i + 1] = 69.0 / 256.0;
        color_buffer_data[i + 2] = 19.0 / 256.0;
    }
    // lava
    for (int i = 0; i < 36; i++) {
        vertex_buffer_data[j + 0] =
            0.5 * cos(10.0 * M_PI * (double)(i + 1) / 180.0);
        vertex_buffer_data[j + 2] =
            0.5 * sin(10.0 * M_PI * (double)(i + 1) / 180.0);
        vertex_buffer_data[j + 1] = 10.5;
        vertex_buffer_data[j + 3] =
            0.5 * cos(10.0 * M_PI * (double)(i) / 180.0);
        vertex_buffer_data[j + 5] =
            0.5 * sin(10.0 * M_PI * (double)(i) / 180.0);
        vertex_buffer_data[j + 4] = 10.5;
        vertex_buffer_data[j + 6] =
            2.0 * cos(10.0 * M_PI * (double)(i + 1) / 180.0);
        vertex_buffer_data[j + 8] =
            2.0 * sin(10.0 * M_PI * (double)(i + 1) / 180.0);
        vertex_buffer_data[j + 7] = 10.0;
        j += 9;
    }
    for (int i = 0; i < 36; i++) {
        vertex_buffer_data[j + 0] =
            2.0 * cos(10.0 * M_PI * (double)(i) / 180.0);
        vertex_buffer_data[j + 2] =
            2.0 * sin(10.0 * M_PI * (double)(i) / 180.0);
        vertex_buffer_data[j + 1] = 10.0;
        vertex_buffer_data[j + 3] =
            2.0 * cos(10.0 * M_PI * (double)(i + 1) / 180.0);
        vertex_buffer_data[j + 5] =
            2.0 * sin(10.0 * M_PI * (double)(i + 1) / 180.0);
        vertex_buffer_data[j + 4] = 10.0;
        vertex_buffer_data[j + 6] =
            0.5 * cos(10.0 * M_PI * (double)(i) / 180.0);
        vertex_buffer_data[j + 8] =
            0.5 * sin(10.0 * M_PI * (double)(i) / 180.0);
        vertex_buffer_data[j + 7] = 10.5;
        j += 9;
    }
    for (int i = 648; i < 1296; i += 3) {
        color_buffer_data[i] = 255.0 / 256.0;
        color_buffer_data[i + 1] = 0.0 / 256.0;
        color_buffer_data[i + 2] = 0.0 / 256.0;
    }

    // for (int i = 0; i < 36; i++) {
    //     vertex_buffer_data[j++] = 0.0;
    //     vertex_buffer_data[j++] = 0.0;
    //     vertex_buffer_data[j++] = 0.0;
    //     vertex_buffer_data[j++] = 10.0 * cos(10.0 * M_PI * (double)(i) /
    //     180.0); vertex_buffer_data[j++] = 0.0; vertex_buffer_data[j++] = 10.0
    //     * cos(10.0 * M_PI * (double)(i) / 180.0); vertex_buffer_data[j++] =
    //         10.0 * cos(10.0 * M_PI * (double)(i + 1) / 180.0);
    //     vertex_buffer_data[j++] = 0.0;
    //     vertex_buffer_data[j++] =
    //         10.0 * cos(10.0 * M_PI * (double)(i + 1) / 180.0);
    // }
    vertex_buffer_data[j++] = -10.0;
    vertex_buffer_data[j++] = 0.0;
    vertex_buffer_data[j++] = 10.0;
    vertex_buffer_data[j++] = 10.0;
    vertex_buffer_data[j++] = 0.0;
    vertex_buffer_data[j++] = 10.0;
    vertex_buffer_data[j++] = 10.0;
    vertex_buffer_data[j++] = 0.0;
    vertex_buffer_data[j++] = -10.0;
    vertex_buffer_data[j++] = 10.0;
    vertex_buffer_data[j++] = 0.0;
    vertex_buffer_data[j++] = -10.0;
    vertex_buffer_data[j++] = -10.0;
    vertex_buffer_data[j++] = 0.0;
    vertex_buffer_data[j++] = -10.0;
    vertex_buffer_data[j++] = -10.0;
    vertex_buffer_data[j++] = 0.0;
    vertex_buffer_data[j++] = 10.0;

    for (int i = 1296; i < 1296 + 18; i += 3) {
        color_buffer_data[i] = 139.0 / 256.0;
        color_buffer_data[i + 1] = 69.0 / 256.0;
        color_buffer_data[i + 2] = 19.0 / 256.0;
    }

    this->object = create3DObject(GL_TRIANGLES, 1000, vertex_buffer_data,
                                  color_buffer_data, GL_FILL);
}

void Volcano::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate(this->position);  // glTranslatef
    // glm::mat4 rotate_x = glm::rotate((float)(this->rotation.x * M_PI /
    // 180.0f),
    //                                  glm::vec3(0, 1, 0));
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
}

void Volcano::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Volcano::tick() {
    // this->rotation += speed;
    // this->position.x -= speed;
    // this->position.y -= speed;
}
