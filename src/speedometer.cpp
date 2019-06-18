#include "speedometer.h"
#include "main.h"
#include "math.h"

#define GLM_ENABLE_EXPERIMENTAL
Speedometer::Speedometer(float x, float y, color_t color) {
    this->position = glm::vec3(x, y, 0);
    this->rotation = 90.0;
    // Our vertices. Three consecutive floats give a 3D vertex; Three
    // consecutive vertices give a triangle. A cube has 6 faces with 2 triangles
    // each, so this makes 6*2=12 triangles, and 12*3 vertices
    static GLfloat vertex_buffer_data[10000];

    int j = 0;
    for (int i = 1; i < 90; i += 2, j += 9) {
        vertex_buffer_data[j] = 1.0 * cos(2.0 * (double)(i)*M_PI / 180.0);
        vertex_buffer_data[j + 1] = 1.0 * sin(2.0 * (double)(i)*M_PI / 180.0);
        vertex_buffer_data[j + 2] = 0.0f;
        vertex_buffer_data[j + 3] = 2.0 * cos(2.0 * (double)(i)*M_PI / 180.0);
        vertex_buffer_data[j + 4] = 2.0 * sin(2.0 * (double)(i)*M_PI / 180.0);
        vertex_buffer_data[j + 5] = 0.0f;
        vertex_buffer_data[j + 6] =
            2.0 * cos(2.0 * (double)(i + 1) * M_PI / 180.0);
        vertex_buffer_data[j + 7] =
            2.0 * sin(2.0 * (double)(i + 1) * M_PI / 180.0);
        vertex_buffer_data[j + 8] = 0.0f;
    }
    for (int i = 0; i < 90; i += 2, j += 9) {
        vertex_buffer_data[j] = 2.0 * cos(2.0 * (double)(i)*M_PI / 180.0);
        vertex_buffer_data[j + 1] = 2.0 * sin(2.0 * (double)(i)*M_PI / 180.0);
        vertex_buffer_data[j + 2] = 0.0f;
        vertex_buffer_data[j + 3] =
            1.0 * cos(2.0 * (double)(i + 1) * M_PI / 180.0);
        vertex_buffer_data[j + 4] =
            1.0 * sin(2.0 * (double)(i + 1) * M_PI / 180.0);
        vertex_buffer_data[j + 5] = 0.0f;
        vertex_buffer_data[j + 6] = 1.0 * cos(2.0 * (double)(i)*M_PI / 180.0);
        vertex_buffer_data[j + 7] = 1.0 * sin(2.0 * (double)(i)*M_PI / 180.0);
        vertex_buffer_data[j + 8] = 0.0f;
    }
    int t1 = j / 3;
    static GLfloat color_buffer_data[10000];
    for (int i = 0; i < j; i += 3) {
        color_buffer_data[i] = 52.0 / 256.0;
        color_buffer_data[i + 1] = 73.0 / 256.0;
        color_buffer_data[i + 2] = 94.0 / 256.0;
    }
    static GLfloat vertex_buffer_data1[10000];
    static GLfloat color_buffer_data1[10000];
    j = 0;
    vertex_buffer_data1[j++] = -0.1;
    vertex_buffer_data1[j++] = 0.0;
    vertex_buffer_data1[j++] = 0.0;
    vertex_buffer_data1[j++] = 0.1;
    vertex_buffer_data1[j++] = 0.0;
    vertex_buffer_data1[j++] = 0.0;
    vertex_buffer_data1[j++] = 0.0;
    vertex_buffer_data1[j++] = 0.8;
    vertex_buffer_data1[j++] = 0.0;

    for (int i = 0; i < j; i += 3) {
        color_buffer_data1[i] = 255.0 / 256.0;
        color_buffer_data1[i + 1] = 0.0 / 256.0;
        color_buffer_data1[i + 2] = 0.0 / 256.0;
    }

    this->object[0] = create3DObject(GL_TRIANGLES, t1 * 3, vertex_buffer_data,
                                     color_buffer_data, GL_FILL);
    this->object[1] = create3DObject(GL_TRIANGLES, 3, vertex_buffer_data1,
                                     color_buffer_data1, GL_FILL);
}

void Speedometer::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 scale = glm::scale(glm::vec3(5.0, 7.0, 0.0));
    glm::mat4 translate = glm::translate(this->position);  // glTranslatef

    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to
    // rotate rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * scale);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object[0]);
    glm::mat4 rotate =
        glm::rotate((float)(this->rotation * M_PI / 180.0), glm::vec3(0, 0, 1));
    Matrices.model = (translate * scale * rotate);
    glm::mat4 MVP1 = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP1[0][0]);
    draw3DObject(this->object[1]);
}

void Speedometer::tick(double speed) {
    //
    this->rotation = 90 - 90 * speed / 2.5;
}
