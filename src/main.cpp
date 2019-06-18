#include "main.h"
#include "arrow.h"
#include "compass.h"
#include "enemy.h"
#include "fuel.h"
#include "fuelmeter.h"
#include "heart.h"
#include "missile.h"
#include "parachute.h"
#include "plane.h"
#include "ring.h"
#include "score.h"
#include "sea.h"
#include "speedometer.h"
#include "target.h"
#include "timer.h"
#include "volcano.h"

using namespace std;

#define GLM_ENABLE_EXPERIMENTAL

GLMatrices Matrices;
GLMatrices Matrices1;
GLuint programID;
GLFWwindow *window;

/**************************
 * Customizable functions *
 **************************/

Plane plane;
bounding_box_t b_plane;
Sea sea;
Ring rings[30];
bounding_box_t b_rings[30];

Volcano volcanoes[30];
bounding_box_t b_volcano[30];

vector<Missile> missiles;
bounding_box_t b_missiles[30];
vector<Missile> bombs;
bounding_box_t b_bombs[30];
vector<Missile> emissiles;
bounding_box_t b_emissiles[30];
double emt = 0.0;
int midx;
int emidx;
double prevmissile = 0.0, prevplanemissile = 0.0, prevbomb = 0.0;
int eidx;
int bidx;
Enemy enemies[30];
bounding_box_t b_enemies[30];
Parachute parachutes[30];
bounding_box_t b_parachute[30];
Fuel fuel[10];
bounding_box_t b_fuel[30];
Arrow arrow;
Target targets;
Score scores[4];
Compass compass;
Fuelmeter fuelmeter;
Speedometer speedometer;
Heart hearts[5];
double cx, cy;
bool loop;
bool barrel;
int curr_fuel = 10;
int shootm, shootb;

float screen_zoom = 0.6, screen_center_x = 0, screen_center_y = 0;
float camera_rotation_angle = 0;

Timer t60(1.0 / 60);

/* Render the scene with openGL */
/* Edit this function according to your assignment */
void draw() {
    // clear the color and depth in the frame buffer
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // use the loaded shader program
    // Don't change unless you know what you are doing
    glUseProgram(programID);

    // Eye - Location of camera. Don't change unless you are sure!!
    double eyex, targetx, upx;
    double eyey, targety, upy;
    double eyez, targetz, upz;
    // plane
    if (plane.view == 1) {
        eyex = plane.position.x + 0.0 * plane.r[1][0] - 10.0 * plane.r[2][0];
        eyey = plane.position.y + 0.0 * plane.r[1][1] - 10.0 * plane.r[2][1];
        eyez = plane.position.z + 0.0 * plane.r[1][2] - 10.0 * plane.r[2][2];
        targetx = plane.position.x + 0.0 * plane.r[1][0] - 20.0 * plane.r[2][0];
        targety = plane.position.y + 0.0 * plane.r[1][1] - 20.0 * plane.r[2][1];
        targetz = plane.position.z + 0.0 * plane.r[1][2] - 20.0 * plane.r[2][2];
        upx = plane.r[1][0];
        upy = plane.r[1][1];
        upz = plane.r[1][2];
    }
    // top
    else if (plane.view == 2) {
        eyex = plane.position.x;
        eyey = plane.position.y + 40.0;
        eyez = plane.position.z;

        targetx = plane.position.x;
        targety = plane.position.y;
        targetz = plane.position.z;

        upx = 0;
        upy = 0;
        upz = -1;
    }
    // tower
    else if (plane.view == 3) {
        eyex = plane.position.x + 20.0;
        eyey = plane.position.y + 20.0;
        eyez = plane.position.z + 10.0;
        targetx = plane.position.x;
        targety = plane.position.y;
        targetz = plane.position.z;
        upx = 0;
        upy = 1;
        upz = 0;

    }
    // follow
    else if (plane.view == 4) {
        eyex = plane.position.x + 12.0 * plane.r[1][0] + 40.0 * plane.r[2][0];
        eyey = plane.position.y + 12.0 * plane.r[1][1] + 40.0 * plane.r[2][1];
        eyez = plane.position.z + 12.0 * plane.r[1][2] + 40.0 * plane.r[2][2];
        targetx = plane.position.x;
        targety = plane.position.y;
        targetz = plane.position.z;
        upx = plane.r[1][0];
        upy = plane.r[1][1];
        upz = plane.r[1][2];
    }
    //
    else if (plane.view == 5) {
        glfwGetCursorPos(window, &cx, &cy);
        float x = (cx - 400) / 20.0;
        // if (x > 20.0) x = 20.0;
        // if (x < -20.0) x = -20.0;

        float y = (cy - 400) / 20.0;
        // if (y > 20.0) y = 20.0;
        // if (y < -20.0) y = -20.0;
        float z = sqrt(200.0 - x * x - y * y);
        eyex = plane.position.x + x / screen_zoom;
        eyey = plane.position.y + y / screen_zoom;
        eyez = plane.position.z + z / screen_zoom;
        targetx = plane.position.x;
        targety = plane.position.y;
        targetz = plane.position.z;
        upx = 0;
        upy = 1;
        upz = 0;
    }
    // Target - Where is the camera looking at.  Don't change unless you are
    // sure!!
    glm::vec3 eye(eyex, eyey, eyez);
    glm::vec3 target(targetx, targety, targetz);
    // Up - Up vector defines tilt of camera.  Don't change unless you are
    // sure!!
    glm::vec3 up(upx, upy, upz);

    // Compute Camera matrix (view)
    Matrices.view = glm::lookAt(eye, target, up);  // Rotating Camera for 3D
    Matrices1.view = glm::lookAt(glm::vec3(0, 0, 1), glm::vec3(0, 0, 0),
                                 glm::vec3(0, 1, 0));  // Rotating Camera for 3D
    // Don't change unless you are sure!!
    // Matrices.view = glm::lookAt(glm::vec3(0, 0, 3), glm::vec3(0, 0, 0),
    // glm::vec3(0, 1, 0)); // Fixed camera for 2D (ortho) in XY plane

    // Compute ViewProject matrix as view/camera might not be changed for this
    // frame (basic scenario) Don't change unless you are sure!!
    glm::mat4 VP = Matrices.projection * Matrices.view;
    glm::mat4 VP1 = Matrices1.projection * Matrices1.view;

    // Send our transformation to the currently bound shader, in the "MVP"
    // uniform For each model you render, since the MVP will be different (at
    // least the M part) Don't change unless you are sure!!
    glm::mat4 MVP;  // MVP = Projection * View * Model

    // Scene render
    plane.draw(VP);
    sea.draw(VP);
    for (int i = 0; i < 30; i++) {
        if (bombs[i].fired) bombs[i].draw(VP);
    }
    for (int i = 0; i < 30; i++) {
        if (rings[i].alive) rings[i].draw(VP);
    }
    for (int i = 0; i < 30; i++) {
        volcanoes[i].draw(VP);
    }
    for (int i = 0; i < 30; i++) {
        if (missiles[i].fired) missiles[i].draw(VP);
    }
    for (int i = 0; i < 30; i++) {
        if (emissiles[i].fired) emissiles[i].draw(VP);
    }
    for (int i = 0; i < 30; i++) {
        if (enemies[i].alive) enemies[i].draw(VP);
    }
    for (int i = 0; i < 30; i++) {
        if (parachutes[i].alive) parachutes[i].draw(VP);
    }
    for (int i = 0; i < 10; i++) {
        if (!fuel[i].taken) fuel[i].draw(VP);
    }
    arrow.draw(VP);
    targets.draw(VP);
    int temp = plane.score;
    int arr[4];
    for (int i = 1; i <= 4; i++) {
        int d = temp % 10;
        temp /= 10;
        arr[4 - i] = d;
    }
    for (int i = 0; i < 4; i++) {
        scores[i].draw(VP1, arr[i]);
    }
    compass.draw(VP1);
    fuelmeter.draw(VP1, curr_fuel);
    speedometer.draw(VP1);
    for (int i = 0; i < plane.health / 10.0; i++) {
        hearts[i].draw(VP1);
    }
}

void tick_input(GLFWwindow *window) {
    int left = glfwGetKey(window, GLFW_KEY_LEFT);
    int right = glfwGetKey(window, GLFW_KEY_RIGHT);
    int up = glfwGetKey(window, GLFW_KEY_UP);
    int down = glfwGetKey(window, GLFW_KEY_DOWN);
    int minus = glfwGetKey(window, GLFW_KEY_MINUS);
    int plus = glfwGetKey(window, GLFW_KEY_EQUAL);
    int w = glfwGetKey(window, GLFW_KEY_W);
    int s = glfwGetKey(window, GLFW_KEY_S);
    int one = glfwGetKey(window, GLFW_KEY_1);
    int two = glfwGetKey(window, GLFW_KEY_2);
    int three = glfwGetKey(window, GLFW_KEY_3);
    int four = glfwGetKey(window, GLFW_KEY_4);
    int five = glfwGetKey(window, GLFW_KEY_5);
    int l = glfwGetKey(window, GLFW_KEY_L);
    int b = glfwGetKey(window, GLFW_KEY_B);
    int f = glfwGetKey(window, GLFW_KEY_F);
    int c = glfwGetKey(window, GLFW_KEY_C);
    int zero = glfwGetKey(window, GLFW_KEY_0);
    int space = glfwGetKey(window, GLFW_KEY_SPACE);

    if (f && !loop && !barrel) {
        plane.position.y += 1.0;
    }
    if (c && !loop && !barrel) {
        plane.position.y -= 1.0;
    }

    // plane.position.x -= 1.0 * plane.r[2][0];
    // plane.position.y -= 1.0 * plane.r[2][1];
    // plane.position.z -= 1.0 * plane.r[2][2];
    if (left && !loop && !barrel) {
        plane.rotation.y += 1.0;
    }
    if (right && !loop && !barrel) {
        plane.rotation.y -= 1.0;
    }
    if (up && !loop && !barrel) {
        plane.rotation.x += 1.0;
    }
    if (down && !loop && !barrel) {
        plane.rotation.x -= 1.0;
    }
    if (plus && !loop && !barrel) {
        plane.rotation.z -= 1.0;
    }
    if (minus && !loop && !barrel) {
        plane.rotation.z += 1.0;
    }
    if (l) {
        if (loop)
            loop = false;
        else
            loop = true;
    }
    if (b) {
        if (barrel)
            barrel = false;
        else
            barrel = true;
    }
    if (loop) {
        plane.rotation.x += 1.0;
        plane.position.x -= 2.0 * plane.r[2][0];
        plane.position.y -= 2.0 * plane.r[2][1];
        plane.position.z -= 2.0 * plane.r[2][2];
    }
    if (barrel) {
        plane.rotation.z += 1.0;
        plane.distance += 2.0;
        plane.position.x -= 2.0 * plane.r[2][0];
        plane.position.y -= 2.0 * plane.r[2][1];
        plane.position.z -= 2.0 * plane.r[2][2];
    }
    glfwGetCursorPos(window, &cx, &cy);
    float x = (cx - 400) / 20.0;
    // if (x > 20.0) x = 20.0;
    // if (x < -20.0) x = -20.0;

    float y = (cy - 400) / 20.0;
    // if (y > 20.0) y = 20.0;
    // if (y < -20.0) y = -20.0;
    targets.position.x = plane.position.x + x * plane.r[0][0] -
                         y * plane.r[1][0] -
                         2.0 * plane.r[2][0] * plane.r[2][0];
    targets.position.y = plane.position.y + x * plane.r[0][1] -
                         y * plane.r[1][1] -
                         2.0 * plane.r[2][1] * plane.r[2][1];
    targets.position.z = plane.position.z + x * plane.r[0][2] -
                         y * plane.r[1][2] -
                         2.0 * plane.r[2][2] * plane.r[2][2];
    if (w && !loop && !barrel) {
        plane.distance += 2.0;
        plane.speed = min(5.0, plane.speed + 0.1);
        plane.position.x -= 2.0 * plane.r[2][0];
        plane.position.y -= 2.0 * plane.r[2][1];
        plane.position.z -= 2.0 * plane.r[2][2];
    }
    plane.speed = max(0.0, plane.speed - 0.01);
    if (s && !loop && !barrel) {
        plane.distance += 2.0;
        plane.speed = min(5.0, plane.speed + 0.1);
        plane.position.x += 2.0 * plane.r[2][0];
        plane.position.y += 2.0 * plane.r[2][1];
        plane.position.z += 2.0 * plane.r[2][2];
    }
    plane.speed = max(0.0, plane.speed - 0.01);
    if (one && !loop && !barrel) {
        plane.view = 1;
    }
    if (two && !loop && !barrel) {
        plane.view = 2;
    }
    if (three && !loop && !barrel) {
        plane.view = 3;
    }
    if (four && !loop && !barrel) {
        plane.view = 4;
    }
    if (five && !loop && !barrel) {
        plane.view = 5;
    }
    if (zero && !loop && !barrel) {
    }
    if (space && !loop && !barrel) {
        if (emt - prevplanemissile > 0.3) {
            system("aplay -c 1 -t wav -q ./../sound/missile.wav&");
            missiles[midx].fired = true;
            prevplanemissile = emt;
            midx++;
            if (midx == 30) {
                midx = 0;
                for (int i = 0; i < 30; i++) {
                    missiles[i].fired = false;
                }
            }
        }
    }
    if (shootm) {
        if (emt - prevplanemissile > 0.3) {
            system("aplay -c 1 -t wav -q ./../sound/missile.wav&");
            missiles[midx].fired = true;
            prevplanemissile = emt;
            midx++;
            if (midx == 30) {
                midx = 0;
                for (int i = 0; i < 30; i++) {
                    missiles[i].fired = false;
                }
            }
        }
        shootm = 0;
    }
    if (zero && !loop && !barrel) {
        if (emt - prevbomb > 0.3) {
            system("aplay -c 1 -t wav -q ./../sound/bombsound.wav&");
            bombs[bidx].fired = true;
            prevbomb = emt;
            bidx++;
            if (bidx == 30) {
                bidx = 0;
                for (int i = 0; i < 30; i++) {
                    bombs[i].fired = false;
                }
            }
        }
    }
    if (shootb) {
        if (emt - prevbomb > 0.3) {
            system("aplay -c 1 -t wav -q ./../sound/bombsound.wav&");
            bombs[bidx].fired = true;
            prevbomb = emt;
            bidx++;
            if (bidx == 30) {
                bidx = 0;
                for (int i = 0; i < 30; i++) {
                    bombs[i].fired = false;
                }
            }
        }
        shootb = 0;
    }
}

void tick_elements() {
    // system("aplay -c 1 -t wav -q ./../sound/plane.wav&");
    // plane.tick();
    // camera_rotation_angle += 1;
    fuelmeter.flag -= 0.5;
    if (fuelmeter.flag == 3 * 900.0) curr_fuel = 9;
    if (fuelmeter.flag == 3 * 800.0) curr_fuel = 8;
    if (fuelmeter.flag == 3 * 700.0) curr_fuel = 7;
    if (fuelmeter.flag == 3 * 600.0) curr_fuel = 6;
    if (fuelmeter.flag == 3 * 500.0) curr_fuel = 5;
    if (fuelmeter.flag == 3 * 400.0) curr_fuel = 4;
    if (fuelmeter.flag == 3 * 300.0) curr_fuel = 3;
    if (fuelmeter.flag == 3 * 200.0) curr_fuel = 2;
    if (fuelmeter.flag == 3 * 100.0) curr_fuel = 1;
    if (fuelmeter.flag == 3 * 000.0) {
        exit(0);
    }
    double diffx = targets.position.x - plane.position.x;
    double diffy = targets.position.y - plane.position.y;
    double diffz = targets.position.z - plane.position.z;
    glm::vec3 diff = normalize(glm::vec3(diffx, diffy, diffz));
    // cout << diffx << " " << diffy << " " << diffz << endl;
    speedometer.tick(plane.speed);
    compass.tick(plane.r[2][0], plane.r[2][1], plane.r[2][2]);
    for (int i = 0; i < 10; i++) {
        fuel[i].tick();
    }
    // for (int i = 0; i < 3; i++) {
    //     for (int j = 0; j < 3; j++) {
    //         targets.r[i][j] = plane.r[i][j];
    //     }
    // }
    for (int i = 0; i < 30; i++) {
        if (missiles[i].fired) {
            missiles[i].position.x += 2.0 * diff.x;
            missiles[i].position.y += 2.0 * diff.y;
            missiles[i].position.z -= 2.0 * diff.z;
        }
    }
    for (int i = 0; i < 30; i++) {
        if (bombs[i].fired) {
            bombs[i].position.y -= 1.0;
        }
    }
    for (int i = 0; i < 30; i++) {
        if (emissiles[i].fired) {
            emissiles[i].position.x += 2.0 * enemies[eidx].r[1][0];
            emissiles[i].position.y += 2.0 * enemies[eidx].r[1][1];
            emissiles[i].position.z += 2.0 * enemies[eidx].r[1][2];
        }
    }
}

/* Initialize the OpenGL rendering properties */
/* Add all the models to be created here */
void initGL(GLFWwindow *window, int width, int height) {
    /* Objects should be created before any other gl function and shaders */
    // Create the models

    plane = Plane(0, 40, 0, COLOR_GREY);
    arrow = Arrow(0.0, 0.0, 0.0, COLOR_RED);
    sea = Sea(0.0, 0.0, 0.0, COLOR_BLUE);
    targets = Target(0.0, 40.0, -40.0, COLOR_BLACK);
    int dx = 0;
    for (int i = 0; i < 5; i++) {
        hearts[i] = Heart(dx + 30, 40.0);
        dx += 3.0;
    }
    double pos = screen_center_x;
    for (int i = 0; i < 4; i++) {
        scores[i] = Score(pos - 45, 40.0f, COLOR_BLACK);
        pos += 3.0f;
    }
    pos = screen_center_x;
    for (int i = 0; i < 10; i++) {
        int yy = rand() % 100;
        yy -= 20;
        int xx = rand() % 1000;
        xx -= 500;
        int zz = rand() % 1000;
        zz -= 500;
        fuel[i] = Fuel(xx, yy, zz, COLOR_FUEL);
    }
    for (int i = 0; i < 30; i++) {
        int yy = rand() % 100;
        yy -= 20;
        int xx = rand() % 1000;
        xx -= 500;
        int zz = rand() % 1000;
        zz -= 500;
        parachutes[i] = Parachute(xx, yy, zz, COLOR_BROWN);
    }
    for (int i = 0; i < 30; i++) {
        int yy = rand() % 50;
        yy -= 20;
        int xx = rand() % 1000;
        xx -= 500;
        int zz = rand() % 1000;
        zz += 20;
        rings[i] = Ring(xx, yy, zz, COLOR_RED);
    }
    for (int i = 0; i < 30; i++) {
        int yy = -39.9;
        int xx = rand() % 1000;
        xx -= 500;
        int zz = rand() % 1000;
        zz -= 500;
        volcanoes[i] = Volcano(xx, yy, zz, COLOR_BROWN);
    }
    for (int i = 0; i < 30; i++) {
        missiles.push_back(Missile(plane.position.x, plane.position.y,
                                   plane.position.z, COLOR_GREEN));
    }
    for (int i = 0; i < 30; i++) {
        bombs.push_back(Missile(plane.position.x, plane.position.y,
                                plane.position.z, COLOR_GREEN));
    }
    for (int i = 0; i < 30; i++) {
        emissiles.push_back(Missile(enemies[eidx].position.x,
                                    enemies[eidx].position.y,
                                    enemies[eidx].position.z, COLOR_BLACK));
    }

    enemies[0] = Enemy(0, 0, 0, COLOR_GREEN);
    for (int i = 1; i < 30; i++) {
        int yy = 0;
        int xx = rand() % 10000;
        xx -= 5000;
        int zz = rand() % 10000;
        zz -= 5000;
        enemies[i] = Enemy(xx, -39.9, zz, COLOR_GREEN);
    }
    compass = Compass(-40.0, -35, COLOR_BLACK);
    fuelmeter = Fuelmeter(40.0, -35.0, COLOR_BLACK);
    speedometer = Speedometer(0.0, 35, COLOR_BLACK);

    // Create and compile our GLSL program from the shaders
    programID = LoadShaders("Sample_GL.vert", "Sample_GL.frag");
    // Get a handle for our "MVP" uniform
    Matrices.MatrixID = glGetUniformLocation(programID, "MVP");
    Matrices1.MatrixID = glGetUniformLocation(programID, "MVP");

    reshapeWindow(window, width, height);

    // Background color of the scene
    glClearColor(COLOR_BACKGROUND.r / 256.0, COLOR_BACKGROUND.g / 256.0,
                 COLOR_BACKGROUND.b / 256.0, 0.0f);  // R, G, B, A
    glClearDepth(1.0f);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);

    cout << "VENDOR: " << glGetString(GL_VENDOR) << endl;
    cout << "RENDERER: " << glGetString(GL_RENDERER) << endl;
    cout << "VERSION: " << glGetString(GL_VERSION) << endl;
    cout << "GLSL: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << endl;
}

int main(int argc, char **argv) {
    srand(time(0));
    int width = 800;
    int height = 800;

    window = initGLFW(width, height);

    initGL(window, width, height);

    /* Draw in loop */
    while (!glfwWindowShouldClose(window)) {
        // Process timers

        if (t60.processTick()) {
            if (plane.position.y <= -40.0) {
                exit(0);
            }
            b_plane.x = plane.position.x;
            b_plane.y = plane.position.y;
            b_plane.z = plane.position.z;
            b_plane.length = 10.0;
            b_plane.width = 7.0;
            b_plane.height = 4.0;
            for (int i = 0; i < 30; i++) {
                b_emissiles[i].x = emissiles[i].position.x;
                b_emissiles[i].y = emissiles[i].position.y;
                b_emissiles[i].z = emissiles[i].position.z;
                b_emissiles[i].length = 4.0;
                b_emissiles[i].width = 4.0;
                b_emissiles[i].height = 4.0;
            }
            for (int i = 0; i < 30; i++) {
                b_rings[i].x = rings[i].position.x;
                b_rings[i].y = rings[i].position.y;
                b_rings[i].z = rings[i].position.z;
                b_rings[i].length = 0.6;
                b_rings[i].width = 7.0;
                b_rings[i].height = 7.0;
            }
            for (int i = 0; i < 30; i++) {
                b_volcano[i].x = volcanoes[i].position.x;
                b_volcano[i].y = volcanoes[i].position.y;
                b_volcano[i].z = volcanoes[i].position.z;
                b_volcano[i].length = 6.0;
                b_volcano[i].width = 6.0;
                b_volcano[i].height = 15.0;
            }
            for (int i = 0; i < 30; i++) {
                b_missiles[i].x = missiles[i].position.x;
                b_missiles[i].y = missiles[i].position.y;
                b_missiles[i].z = missiles[i].position.z;
                b_missiles[i].length = 4.0;
                b_missiles[i].width = 4.0;
                b_missiles[i].height = 4.0;
            }
            for (int i = 0; i < 30; i++) {
                b_enemies[i].x = enemies[i].position.x;
                b_enemies[i].y = enemies[i].position.y;
                b_enemies[i].z = enemies[i].position.z;
                b_enemies[i].length = 12.0;
                b_enemies[i].width = 12.0;
                b_enemies[i].height = 8.0;
            }
            for (int i = 0; i < 30; i++) {
                b_parachute[i].x = parachutes[i].position.x;
                b_parachute[i].y = parachutes[i].position.y;
                b_parachute[i].z = parachutes[i].position.z;
                b_plane.length = 1.3;
                b_plane.width = 1.3;
                b_plane.height = 7.0;
            }
            for (int i = 0; i < 30; i++) {
                b_fuel[i].x = fuel[i].position.x;
                b_fuel[i].y = fuel[i].position.y;
                b_fuel[i].z = fuel[i].position.z;
                b_plane.length = 2.0;
                b_plane.width = 2.0;
                b_plane.height = 4.0;
            }
            for (int i = 0; i < 30; i++) {
                if (detect_collision(b_plane, b_emissiles[i]) &&
                    emissiles[i].fired == true) {
                    plane.health -= 10.0;
                    emissiles[i].fired = false;
                    break;
                }
            }
            for (int i = 0; i < 30; i++) {
                if (detect_collision(b_plane, b_rings[i]) && rings[i].alive) {
                    plane.score += 10.0;
                    rings[i].alive = false;
                    break;
                }
            }
            for (int i = 0; i < 30; i++) {
                if (detect_collision(b_plane, b_volcano[i])) {
                    exit(0);
                }
            }
            for (int i = 0; i < 30; i++) {
                for (int j = 0; j < 30; j++) {
                    if (detect_collision(b_parachute[i], b_missiles[j]) &&
                        parachutes[i].alive && missiles[j].fired) {
                        plane.score += 10.0;
                        parachutes[i].alive = false;
                        break;
                    }
                }
            }
            for (int i = 0; i < 30; i++) {
                if (detect_collision(b_plane, b_parachute[i]) &&
                    parachutes[i].alive) {
                    plane.health -= 10.0;
                    plane.score += 5.0;
                    if (plane.health <= 0.0) {
                        exit(0);
                    }
                    parachutes[i].alive = false;
                    break;
                }
            }
            for (int i = 0; i < 30; i++) {
                if (detect_collision(b_plane, b_fuel[i]) && !fuel[i].taken) {
                    curr_fuel = min(10, curr_fuel + 1);
                    fuel[i].taken = true;
                    break;
                }
            }

            for (int j = 0; j < 30; j++) {
                if (detect_collision(b_enemies[eidx], b_missiles[j]) &&
                    missiles[j].fired && enemies[eidx].alive) {
                    enemies[eidx].health -= 5.0;
                    plane.score += 10.0;
                    if (enemies[eidx].health <= 0.0) {
                        enemies[eidx].alive = false;
                        plane.score += 10.0;
                    }
                    missiles[j].fired = false;
                    break;
                }
            }

            emt += 1.0 / 60.0;
            if (emt - prevmissile > 1.0) {
                emidx++;
                emissiles[emidx].fired = true;
                prevmissile = emt;
                if (emidx == 30) {
                    emidx = 0;
                    for (int i = 0; i < 30; i++) {
                        emissiles[i].fired = false;
                    }
                }
            }
            for (int i = 0; i < 30; i++) {
                if (!missiles[i].fired) {
                    missiles[i].position.x = plane.position.x;
                    missiles[i].position.y = plane.position.y;
                    missiles[i].position.z = plane.position.z;
                }
            }
            for (int i = 0; i < 30; i++) {
                if (!bombs[i].fired) {
                    bombs[i].position.x = plane.position.x;
                    bombs[i].position.y = plane.position.y;
                    bombs[i].position.z = plane.position.z;
                }
            }
            for (int i = 0; i < 30; i++) {
                if (!emissiles[i].fired) {
                    emissiles[i].position.x = enemies[eidx].position.x;
                    emissiles[i].position.y = enemies[eidx].position.y;
                    emissiles[i].position.z = enemies[eidx].position.z;
                }
            }
            arrow.position.x = plane.position.x + 20.0 * plane.r[2][0];
            arrow.position.y = plane.position.y + 10.0 * plane.r[2][1];
            arrow.position.z = plane.position.z + 10.0 * plane.r[2][2];

            double y_x = enemies[eidx].position.x - plane.position.x;
            double y_y = enemies[eidx].position.y - plane.position.y;
            double y_z = enemies[eidx].position.z - plane.position.z;
            double y_mod = sqrt(y_x * y_x + y_y * y_y + y_z * y_z);
            y_x /= y_mod;
            y_y /= y_mod;
            y_z /= y_mod;
            double z_x = y_y * -1.0;
            double z_y = y_x;
            double z_z = 0.0;
            double z_mod = sqrt(z_x * z_x + z_y * z_y + z_z * z_z);
            z_x /= z_mod;
            z_y /= z_mod;
            z_z /= z_mod;
            double x_x = -1.0 * z_y * y_z;
            double x_y = z_x * y_z;
            double x_z = z_y * y_x - z_x * y_y;
            double x_mod = sqrt(x_x * x_x + x_y * x_y + x_z * x_z);
            x_x /= x_mod;
            x_y /= x_mod;
            x_z /= x_mod;
            enemies[eidx].r[1][0] = -1.0 * y_x;
            enemies[eidx].r[1][1] = -1.0 * y_y;
            enemies[eidx].r[1][2] = -1.0 * y_z;
            enemies[eidx].r[2][0] = z_x;
            enemies[eidx].r[2][1] = z_y;
            enemies[eidx].r[2][2] = z_z;
            enemies[eidx].r[0][0] = x_x;
            enemies[eidx].r[0][1] = x_y;
            enemies[eidx].r[0][2] = x_z;

            double az_x = -enemies[eidx].position.x + arrow.position.x;
            double az_y = -enemies[eidx].position.y + arrow.position.y;
            double az_z = -enemies[eidx].position.z + arrow.position.z;
            double az_mod = sqrt(az_x * az_x + az_y * az_y + az_z * az_z);
            az_x /= az_mod;
            az_y /= az_mod;
            az_z /= az_mod;
            double ay_x = az_y * -1.0;
            double ay_y = az_x;
            double ay_z = 0.0;
            double ay_mod = sqrt(ay_x * ay_x + ay_y * ay_y + ay_z * ay_z);
            ay_x /= ay_mod;
            ay_y /= ay_mod;
            ay_z /= ay_mod;
            double ax_x = -1.0 * az_y * ay_z;
            double ax_y = az_x * ay_z;
            double ax_z = az_y * ay_x - az_x * ay_y;
            double ax_mod = sqrt(ax_x * ax_x + ax_y * ax_y + ax_z * ax_z);
            ax_x /= ax_mod;
            ax_y /= ax_mod;
            ax_z /= ax_mod;
            arrow.r[1][0] = ay_x;
            arrow.r[1][1] = ay_y;
            arrow.r[1][2] = ay_z;
            arrow.r[2][0] = az_x;
            arrow.r[2][1] = az_y;
            arrow.r[2][2] = az_z;
            arrow.r[0][0] = ax_x;
            arrow.r[0][1] = ax_y;
            arrow.r[0][2] = ax_z;
            // 60 fps
            // OpenGL Draw commands
            draw();
            // Swap Frame Buffer in double buffering
            glfwSwapBuffers(window);

            tick_elements();
            tick_input(window);
        }

        // Poll for Keyboard and mouse events
        glfwPollEvents();
    }

    quit(window);
}

bool detect_collision(bounding_box_t a, bounding_box_t b) {
    return (abs(a.x - b.x) * 2 < (a.width + b.width)) &&
           (abs(a.y - b.y) * 2 < (a.height + b.height)) &&
           (abs(a.z - b.z) * 2 < (a.length + b.length));
}

void reset_screen() {
    float top = screen_center_y + 50;
    float bottom = screen_center_y - 50;
    float left = screen_center_x - 50;
    float right = screen_center_x + 50;
    Matrices.projection = glm::perspective(45.0, 1.0, 0.1, 1000.0);
    Matrices1.projection = glm::ortho(left, right, bottom, top, 0.1f, 500.0f);
}
