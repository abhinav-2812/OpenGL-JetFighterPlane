#include "score.h"
#include "main.h"

#define GLM_ENABLE_EXPERIMENTAL
Score::Score(float x, float y, color_t color) {
    this->position = glm::vec3(x, y, 0);
    this->rotation = 0;
    // Our vertices. Three consecutive floats give a 3D vertex; Three
    // consecutive vertices give a triangle. A cube has 6 faces with 2 triangles
    // each, so this makes 6*2=12 triangles, and 12*3 vertices
    static const GLfloat vertex_buffer_data0[] = {
        -0.2f, 0.55f, 0.0f, -0.2f, 0.45f, 0.0f, 0.2f,  0.55f, 0.0f,
        0.2f,  0.55f, 0.0f, 0.2f,  0.45f, 0.0f, -0.2f, 0.45f, 0.0f};
    this->object[0] = create3DObject(GL_TRIANGLES, 2 * 3, vertex_buffer_data0,
                                     color, GL_FILL);
    static const GLfloat vertex_buffer_data1[] = {
        -0.2f, 0.45f, 0.0f, -0.1f, 0.45f, 0.0f, -0.1f, 0.05f, 0.0f,
        -0.1f, 0.05f, 0.0f, -0.2f, 0.05f, 0.0f, -0.2f, 0.45f, 0.0f};
    this->object[1] = create3DObject(GL_TRIANGLES, 2 * 3, vertex_buffer_data1,
                                     color, GL_FILL);
    static const GLfloat vertex_buffer_data2[] = {
        0.2f, 0.45f, 0.0f, 0.1f, 0.45f, 0.0f, 0.1f, 0.05f, 0.0f,
        0.1f, 0.05f, 0.0f, 0.2f, 0.05f, 0.0f, 0.2f, 0.45f, 0.0f};
    this->object[2] = create3DObject(GL_TRIANGLES, 2 * 3, vertex_buffer_data2,
                                     color, GL_FILL);
    static const GLfloat vertex_buffer_data3[] = {
        -0.2f, 0.05f,  0.0f, -0.2f, -0.05f, 0.0f, 0.2f,  -0.05f, 0.0f,
        0.2f,  -0.05f, 0.0f, 0.2f,  0.05f,  0.0f, -0.2f, 0.05f,  0.0f};
    this->object[3] = create3DObject(GL_TRIANGLES, 2 * 3, vertex_buffer_data3,
                                     color, GL_FILL);
    static const GLfloat vertex_buffer_data4[] = {
        -0.2f, -0.05f, 0.0f, -0.1f, -0.05f, 0.0f, -0.1f, -0.45f, 0.0f,
        -0.1f, -0.45f, 0.0f, -0.2f, -0.45f, 0.0f, -0.2f, -0.05f, 0.0f};
    this->object[4] = create3DObject(GL_TRIANGLES, 2 * 3, vertex_buffer_data4,
                                     color, GL_FILL);
    static const GLfloat vertex_buffer_data5[] = {
        0.2f, -0.05f, 0.0f, 0.1f, -0.05f, 0.0f, 0.1f, -0.45f, 0.0f,
        0.1f, -0.45f, 0.0f, 0.2f, -0.45f, 0.0f, 0.2f, -0.05f, 0.0f};
    this->object[5] = create3DObject(GL_TRIANGLES, 2 * 3, vertex_buffer_data5,
                                     color, GL_FILL);
    static const GLfloat vertex_buffer_data6[] = {
        -0.2f, -0.45f, 0.0f, -0.2f, -0.55f, 0.0f, 0.2f,  -0.55f, 0.0f,
        0.2f,  -0.55f, 0.0f, 0.2f,  -0.45f, 0.0f, -0.2f, -0.45f, 0.0f};
    this->object[6] = create3DObject(GL_TRIANGLES, 2 * 3, vertex_buffer_data6,
                                     color, GL_FILL);
    this->s[0] = "1110111";
    this->s[1] = "0010010";
    this->s[2] = "1011101";
    this->s[3] = "1011011";
    this->s[4] = "0111010";
    this->s[5] = "1101011";
    this->s[6] = "1101111";
    this->s[7] = "1010010";
    this->s[8] = "1111111";
    this->s[9] = "1111011";
}

void Score::draw(glm::mat4 VP, int d) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 scale = glm::scale(glm::vec3(7.0, 5.0, 0));
    glm::mat4 translate = glm::translate(this->position);  // glTranslatef
    glm::mat4 rotate = glm::rotate((float)(this->rotation * M_PI / 180.0f),
                                   glm::vec3(1, 0, 0));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to
    // rotate rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * scale);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    for (int i = 0; i < 7; i++) {
        if (this->s[d][i] == '1') draw3DObject(this->object[i]);
    }
}

void Score::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Score::tick() {
    // this->rotation += speed;
    // this->position.x += speed;
    // this->position.y += speed;
}