#include "heart.h"
#include "main.h"
#include "math.h"

#define PI 3.14159265

#define GLM_ENABLE_EXPERIMENTAL
Heart::Heart(float x, float y) {
    this->position = glm::vec3(x, y, 0);
    this->rotation = 0;
    this->speed = 0.5;
    this->direction = -1.0;
    // Our vertices. Three consecutive floats give a 3D vertex; Three
    // consecutive vertices give a triangle. A cube has 6 faces with 2 triangles
    // each, so this makes 6*2=12 triangles, and 12*3 vertices
    int n = 60;
    double ang = 360.0 / (double)(n);
    static GLfloat vertex_buffer_data[100000];
    vertex_buffer_data[0] = 0.0f;
    vertex_buffer_data[1] = 0.0f;
    vertex_buffer_data[2] = 0.0f;
    vertex_buffer_data[3] = 0.1f;
    vertex_buffer_data[4] = 0.0f;
    vertex_buffer_data[5] = 0.0f;
    vertex_buffer_data[6] = 0.1f * cos(ang * PI / 180.0);
    vertex_buffer_data[7] = 0.1f * sin(ang * PI / 180.0);
    vertex_buffer_data[8] = 0.0f;
    for (int i = 9; i < 9 * n; i += 9) {
        double prevx = vertex_buffer_data[i - 3];
        double prevy = vertex_buffer_data[i - 2];
        vertex_buffer_data[i] = prevx;
        vertex_buffer_data[i + 1] = prevy;
        vertex_buffer_data[i + 2] = 0.0f;
        vertex_buffer_data[i + 3] = 0.0f;
        vertex_buffer_data[i + 4] = 0.0f;
        vertex_buffer_data[i + 5] = 0.0f;
        vertex_buffer_data[i + 6] =
            prevx * cos(ang * PI / 180.0) - prevy * sin(ang * PI / 180.0);
        vertex_buffer_data[i + 7] =
            prevx * sin(ang * PI / 180.0) + prevy * cos(ang * PI / 180.0);
        vertex_buffer_data[i + 8] = 0.0f;
    }

    vertex_buffer_data[9 * n] = 0.0f;
    vertex_buffer_data[1 + 9 * n] = 0.0f;
    vertex_buffer_data[2 + 9 * n] = 0.0f;
    vertex_buffer_data[3 + 9 * n] = 0.1;
    vertex_buffer_data[4 + 9 * n] = 0.0f;
    vertex_buffer_data[5 + 9 * n] = 0.0f;
    vertex_buffer_data[6 + 9 * n] = 0.1f * cos(ang * PI / 180.0);
    vertex_buffer_data[7 + 9 * n] = 0.1f * sin(ang * PI / 180.0);
    vertex_buffer_data[8 + 9 * n] = 0.0f;
    for (int i = 9 + 9 * n; i < 2 * 9 * n; i += 9) {
        double prevx = vertex_buffer_data[i - 3];
        double prevy = vertex_buffer_data[i - 2];
        vertex_buffer_data[i] = prevx;
        vertex_buffer_data[i + 1] = prevy;
        vertex_buffer_data[i + 2] = 0.0f;
        vertex_buffer_data[i + 3] = 0.0f;
        vertex_buffer_data[i + 4] = 0.0f;
        vertex_buffer_data[i + 5] = 0.0f;
        vertex_buffer_data[i + 6] =
            prevx * cos(ang * PI / 180.0) - prevy * sin(ang * PI / 180.0);
        vertex_buffer_data[i + 7] =
            prevx * sin(ang * PI / 180.0) + prevy * cos(ang * PI / 180.0);
        vertex_buffer_data[i + 8] = 0.0f;
    }
    for (int i = 9 * n; i < 2 * 9 * n; i += 9) {
        vertex_buffer_data[i] += 0.1;
        vertex_buffer_data[i + 3] += 0.1;
        vertex_buffer_data[i + 6] += 0.1;
    }
    int j = 2 * 9 * n;
    vertex_buffer_data[j++] = -0.1;
    vertex_buffer_data[j++] = 0.0;
    vertex_buffer_data[j++] = 0.0;
    vertex_buffer_data[j++] = 0.2;
    vertex_buffer_data[j++] = 0.0;
    vertex_buffer_data[j++] = 0.0;
    vertex_buffer_data[j++] = 0.05;
    vertex_buffer_data[j++] = -0.3;
    vertex_buffer_data[j++] = 0.0;

    static GLfloat color_buffer_data[100000];

    for (int i = 0; i < 2 * 9 * n + 9; i += 3) {
        color_buffer_data[i] = 255.0 / 256.0;
        color_buffer_data[i + 1] = 0.0 / 256.0;
        color_buffer_data[i + 2] = 0.0 / 256.0;
    }

    this->object = create3DObject(GL_TRIANGLES, 1500, vertex_buffer_data,
                                  color_buffer_data, GL_FILL);
}

void Heart::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 scale = glm::scale(glm::vec3(7.0, 12.0, 0.0));
    glm::mat4 translate = glm::translate(this->position);  // glTranslatef
    // glm::mat4 rotate = glm::rotate((float)(this->rotation * M_PI / 18
    // - 2.0f),
    //                                glm::vec3(1, 1, 0));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to
    // rotate rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * scale);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Heart::tick() {}