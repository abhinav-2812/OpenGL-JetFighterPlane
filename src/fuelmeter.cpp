#include "fuelmeter.h"
#include "main.h"

#define GLM_ENABLE_EXPERIMENTAL
Fuelmeter::Fuelmeter(float x, float y, color_t color) {
    this->position = glm::vec3(x, y, 0);
    this->rotation = 0;
    // Our vertices. Three consecutive floats give a 3D vertex; Three
    // consecutive vertices give a triangle. A cube has 6 faces with 2 triangles
    // each, so this makes 6*2=12 triangles, and 12*3 vertices
    static const GLfloat vertex_buffer_data[300] = {
        -0.8, -1.2, 0.0, 0.8,  -1.2, 0.0, 0.8,  -1.0, 0.0, 0.8,  -1.0, 0.0,
        -0.8, -1.0, 0.0, -0.8, -1.2, 0.0, -0.8, 1.2,  0.0, 0.8,  1.2,  0.0,
        0.8,  1.0,  0.0, 0.8,  1.0,  0.0, -0.8, 1.0,  0.0, -0.8, 1.2,  0.0,
        -0.8, 1.2,  0.0, -0.6, 1.2,  0.0, -0.6, -1.2, 0.0, -0.6, -1.2, 0.0,
        -0.8, -1.2, 0.0, -0.8, 1.2,  0.0, 0.8,  1.2,  0.0, 0.6,  1.2,  0.0,
        0.6,  -1.2, 0.0, 0.6,  -1.2, 0.0, 0.8,  -1.2, 0.0, 0.8,  1.2,  0.0,
    };
    // 72
    static const GLfloat vertex_buffer_data1[300] = {
        -0.6, -1.0, 0.0, 0.6,  -1.0, 0.0, 0.6,  -0.8, 0.0,
        0.6,  -0.8, 0.0, -0.6, -0.8, 0.0, -0.6, -1.0, 0.0,
    };
    static const GLfloat vertex_buffer_data2[300] = {
        -0.6, -0.8, 0.0, 0.6,  -0.8, 0.0, 0.6,  -0.6, 0.0,
        0.6,  -0.6, 0.0, -0.6, -0.6, 0.0, -0.6, -0.8, 0.0,
    };
    static const GLfloat vertex_buffer_data3[300] = {
        -0.6, -0.6, 0.0, 0.6,  -0.6, 0.0, 0.6,  -0.4, 0.0,
        0.6,  -0.4, 0.0, -0.6, -0.4, 0.0, -0.6, -0.6, 0.0,
    };
    static const GLfloat vertex_buffer_data4[300] = {
        -0.6, -0.4, 0.0, 0.6,  -0.4, 0.0, 0.6,  -0.2, 0.0,
        0.6,  -0.2, 0.0, -0.6, -0.2, 0.0, -0.6, -0.4, 0.0,
    };
    static const GLfloat vertex_buffer_data5[300] = {
        -0.6, -0.2, 0.0, 0.6,  -0.2, 0.0, 0.6,  -0.0, 0.0,
        0.6,  -0.0, 0.0, -0.6, -0.0, 0.0, -0.6, -0.2, 0.0,
    };
    static const GLfloat vertex_buffer_data6[300] = {
        -0.6, 0.0, 0.0, 0.6,  0.0, 0.0, 0.6,  0.2, 0.0,
        0.6,  0.2, 0.0, -0.6, 0.2, 0.0, -0.6, 0.0, 0.0,
    };
    static const GLfloat vertex_buffer_data7[300] = {
        -0.6, 0.2, 0.0, 0.6,  0.2, 0.0, 0.6,  0.4, 0.0,
        0.6,  0.4, 0.0, -0.6, 0.4, 0.0, -0.6, 0.2, 0.0,
    };
    static const GLfloat vertex_buffer_data8[300] = {
        -0.6, 0.4, 0.0, 0.6,  0.4, 0.0, 0.6,  0.6, 0.0,
        0.6,  0.6, 0.0, -0.6, 0.6, 0.0, -0.6, 0.4, 0.0,
    };
    static const GLfloat vertex_buffer_data9[300] = {
        -0.6, 0.6, 0.0, 0.6,  0.6, 0.0, 0.6,  0.8, 0.0,
        0.6,  0.8, 0.0, -0.6, 0.8, 0.0, -0.6, 0.6, 0.0,
    };
    static const GLfloat vertex_buffer_data10[300] = {
        -0.6, 0.8, 0.0, 0.6,  0.8, 0.0, 0.6,  1.0, 0.0,
        0.6,  1.0, 0.0, -0.6, 1.0, 0.0, -0.6, 0.8, 0.0,
    };

    static GLfloat color_buffer_data0[300];
    for (int i = 0; i < 72; i += 3) {
        color_buffer_data0[i] = 128.0 / 256.0;
        color_buffer_data0[i + 1] = 128.0 / 256.0;
        color_buffer_data0[i + 2] = 128.0 / 256.0;
    }
    this->object[0] = create3DObject(GL_TRIANGLES, 72, vertex_buffer_data,
                                     color_buffer_data0, GL_FILL);

    static GLfloat color_buffer_data1[300];

    for (int i = 0; i < 18; i += 3) {
        color_buffer_data1[i] = 124.0 / 256.0;
        color_buffer_data1[i + 1] = 252.0 / 256.0;
        color_buffer_data1[i + 2] = 0.0 / 256.0;
    }

    this->object[1] = create3DObject(GL_TRIANGLES, 6, vertex_buffer_data1,
                                     color_buffer_data1, GL_FILL);
    this->object[2] = create3DObject(GL_TRIANGLES, 6, vertex_buffer_data2,
                                     color_buffer_data1, GL_FILL);
    this->object[3] = create3DObject(GL_TRIANGLES, 6, vertex_buffer_data3,
                                     color_buffer_data1, GL_FILL);
    this->object[4] = create3DObject(GL_TRIANGLES, 6, vertex_buffer_data4,
                                     color_buffer_data1, GL_FILL);
    this->object[5] = create3DObject(GL_TRIANGLES, 6, vertex_buffer_data5,
                                     color_buffer_data1, GL_FILL);
    this->object[6] = create3DObject(GL_TRIANGLES, 6, vertex_buffer_data6,
                                     color_buffer_data1, GL_FILL);
    this->object[7] = create3DObject(GL_TRIANGLES, 6, vertex_buffer_data7,
                                     color_buffer_data1, GL_FILL);
    this->object[8] = create3DObject(GL_TRIANGLES, 6, vertex_buffer_data8,
                                     color_buffer_data1, GL_FILL);
    this->object[9] = create3DObject(GL_TRIANGLES, 6, vertex_buffer_data9,
                                     color_buffer_data1, GL_FILL);
    this->object[10] = create3DObject(GL_TRIANGLES, 6, vertex_buffer_data10,
                                      color_buffer_data1, GL_FILL);
}

void Fuelmeter::draw(glm::mat4 VP, int d) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 scale = glm::scale(glm::vec3(5.0, 7.0, 0.0));
    glm::mat4 translate = glm::translate(this->position);  // glTranslatef
    // glm::mat4 rotate = glm::rotate((float)(this->rotation * M_PI / 18-2.0f),
    //    glm::vec3(1, 0, 0));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to
    // rotate rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * scale);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    for (int i = 0; i <= d; i++) {
        draw3DObject(this->object[i]);
    }
}