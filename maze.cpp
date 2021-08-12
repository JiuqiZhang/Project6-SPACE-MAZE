#include "maze.h"
#define OBJECT_COUNT 3
#define ENEMY_COUNT 9
#define BALL_COUNT 1
struct GameState {
    Entity* player;
    Entity* object;
    Entity* enemy;
    Entity* ball;
};

GameState state;
void Initialize() {

    //state.nextScene = -1;

    glClearColor(0.15297f, 0.15297f, 0.15297f, 1.0f);


    state.player = new Entity();
    state.player->entityType = PLAYER;
    state.player->position = glm::vec3(-1, 0.697f, 0);
    state.player->acceleration = glm::vec3(0, 0, 0);
    state.player->speed = 1.0f;
    state.player->jumpPower = 4.0f;
    state.player->height = 0.6f;
    //GLuint shpTextureID = Util::LoadTexture("ship.png");
    //Mesh* shpmesh = new Mesh();
    //state.player->scale = glm::vec3(3.0);
    //shpmesh->LoadOBJ("ship.obj", 1);
    //state.player->textureID = shpTextureID;
    //state.player->mesh = shpmesh;


    state.object = new Entity[OBJECT_COUNT];
    GLuint floorTextureID = Util::LoadTexture("floor2.jpg");
    Mesh* cubemesh = new Mesh();
    cubemesh->LoadOBJ("cube.obj", 20);
    state.object[0].textureID = floorTextureID;
    state.object[0].position = glm::vec3(0, -0.25f, 0);
    state.object[0].mesh = cubemesh;
    state.object[0].rotation = glm::vec3(0, 0, 0);
    state.object[0].acceleration = glm::vec3(0, 0, 0);
    state.object[0].scale = glm::vec3(20, 0.5f, 20);
    state.object[0].entityType = FLOOR;



    GLuint shipTextureID = Util::LoadTexture("ship.png");
    Mesh* shipmesh = new Mesh();
    shipmesh->LoadOBJ("ship.obj", 1);
    state.object[1].textureID = shipTextureID;
    state.object[1].position = glm::vec3(0, 0, -50);
    state.object[1].mesh = shipmesh;
    state.object[1].rotation = glm::vec3(0, 180, 0);
    state.object[1].acceleration = glm::vec3(0, 0, 15);
    state.object[1].entityType = SHIP;

    GLuint crateTextureID = Util::LoadTexture("floor2.jpg");
    Mesh* crateMesh = new Mesh();
    crateMesh->LoadOBJ("cube.obj", 1);

    state.object[2].textureID = crateTextureID;
    state.object[2].mesh = crateMesh;
    state.object[2].position = glm::vec3(0.5, 0.5f, -3.5);
    state.object[2].entityType = CRATE;
    state.object[2].height = 2.0f;
    state.object[2].scale = glm::vec3(1, 2.0f, 1);



    /*state.object[3].textureID = crateTextureID;
    state.object[3].mesh = crateMesh;
    state.object[3].position = glm::vec3(0.5, 1.5f, -3.5);
    state.object[3].entityType = CRATE;

    state.object[4].textureID = crateTextureID;
    state.object[4].mesh = crateMesh;
    state.object[4].position = glm::vec3(1.5, 0.5f, -3.5);
    state.object[4].entityType = CRATE;*/

    state.enemy = new Entity[ENEMY_COUNT];
    GLuint enemyTextureID = Util::LoadTexture("bad.png");
    for (int i = 0; i < ENEMY_COUNT; i++) {
        state.enemy[i].billboard = true;
        state.enemy[i].coin = false;

        state.enemy[i].textureID = enemyTextureID;
        state.enemy[i].position = glm::vec3(rand() % 20 - 10, 0.25, rand() % 20 - 10);
        state.enemy[i].scale = glm::vec3(0.5);
        state.enemy[i].rotation = glm::vec3(0, 0, 0);
        state.enemy[i].acceleration = glm::vec3(0, 0, 0);
    }
    state.ball = new Entity[BALL_COUNT];
    GLuint ballTextureID = Util::LoadTexture("ball.png");
    for (int i = 0; i < BALL_COUNT; i++) {
        state.ball[i].billboard = true;
        state.ball[i].coin = true;
        state.ball[i].width = 0.3f;
        state.ball[i].textureID = ballTextureID;
        state.ball[i].position = glm::vec3(-1, 0.25, -6);
        state.ball[i].scale = glm::vec3(0.5);
        state.ball[i].rotation = glm::vec3(0, 0, 0);
        state.ball[i].acceleration = glm::vec3(0, 0, 0);
    }





}