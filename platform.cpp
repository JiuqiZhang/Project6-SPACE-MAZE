#include "platform.h"

#define OBJECT_COUNT 97

#define ENEMY_COUNT 10
Mix_Music* bgmusic;

unsigned int mazeMap[] =
{
1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1,
1, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 1,
1, 0, 1, 0, 1, 0, 1, 0, 1, 1, 1, 1, 1,
1, 0, 1, 0, 1, 0, 1, 0, 0, 0, 0, 0, 1,
1, 0, 1, 0, 1, 0, 1, 1, 1, 1, 1, 0, 1,
1, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 1,
1, 0, 1, 1, 1, 0, 1, 0, 1, 0, 1, 0, 1,
1, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1,
1, 0, 1, 0, 1, 1, 1, 1, 1, 0, 1, 0, 1,
1, 0, 1, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1,
1, 0, 1, 0, 1, 0, 1, 0, 1, 1, 1, 0, 1,
1, 0, 1, 0, 0, 0, 1, 0, 1, 0, 0, 0, 1,
1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1
};

void Platform::Initialize(){

    glClearColor(0.286f, 0.315f, 0.3192f, 1.0f);

    bgmusic = Mix_LoadMUS("main.wav");
    Mix_FadeInMusic(bgmusic, -1, 100);
    state.player = new Entity();
    state.player->entityType = PLAYER;
    state.player->position = glm::vec3(1.5, 9.97, 8.5);
    //state.player->width = 0.6;
    state.player->acceleration = glm::vec3(0, 0, 0);
    state.player->speed = 0.8f;
    state.player->jumpPower = 2.0f;
    state.player->height = 0.6f;
    state.player->live = 4;
    state.player->coinnum = 5;
    state.player->timeLeft = 197.97f;
    //GLuint shpTextureID = Util::LoadTexture("ship.png");
    //Mesh* shpmesh = new Mesh();
    //state.player->scale = glm::vec3(3.0);
    //shpmesh->LoadOBJ("ship.obj", 1);
    //state.player->textureID = shpTextureID;
    //state.player->mesh = shpmesh;


    state.object = new Entity[OBJECT_COUNT];
    GLuint floorTextureID = Util::LoadTexture("floor2.jpg");
    Mesh* cubemesh = new Mesh();
    cubemesh->LoadOBJ("cube.obj", 13);
    state.object[0].textureID = floorTextureID;
    state.object[0].position = glm::vec3(0, -0.25f, 0);
    state.object[0].mesh = cubemesh;
    state.object[0].rotation = glm::vec3(0, 0, 0);
    state.object[0].acceleration = glm::vec3(0, 0, 0);
    state.object[0].scale = glm::vec3(19.5, 0.5f, 19.5);
    state.object[0].entityType = FLOOR;


    //ship
    GLuint shipTextureID = Util::LoadTexture("ship.png");
    Mesh* shipmesh = new Mesh();
    shipmesh->LoadOBJ("ship.obj", 1);
    state.object[1].scale = glm::vec3(3, 3, 3);
    state.object[1].textureID = shipTextureID;
    state.object[1].position = glm::vec3(1.5, 10, 8.5);
    state.object[1].mesh = shipmesh;
    state.object[1].rotation = glm::vec3(0, -180, 0);
    state.object[1].acceleration = glm::vec3(0, 0, -15);
    state.object[1].entityType = SHIP;


    
    
    GLuint crateTextureID = Util::LoadTexture("floor2.jpg");
    Mesh* crateMesh = new Mesh();
    crateMesh->LoadOBJ("cube.obj", 1);
    //wall
   //////////////////////////////////////////////////////////////trial line 2
    int line[169] = { 
    1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1,
    1, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 1,
    1, 0, 1, 0, 1, 0, 1, 0, 1, 1, 1, 1, 1,
    1, 0, 1, 0, 1, 0, 1, 0, 0, 0, 0, 0, 1,
    1, 0, 1, 0, 1, 0, 1, 1, 1, 1, 1, 0, 1,
    1, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 1,
    1, 0, 1, 1, 1, 0, 1, 0, 1, 0, 1, 0, 1,
    1, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1,
    1, 0, 1, 0, 1, 1, 1, 1, 1, 0, 1, 0, 1,
    1, 0, 1, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1,
    1, 0, 1, 0, 1, 0, 1, 0, 1, 1, 1, 0, 1,
    1, 0, 1, 0, 0, 0, 1, 0, 1, 0, 0, 0, 1,
    1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1
    };
    int count = 2;
    int row = -1.5;
    for (int i = 0; i < 169; i++) {

        if (i % 13 == 0) {
            row ++;
        }
        
        if (line[i] == 0) { continue; }
        if (count < 97){
            state.object[count].textureID = crateTextureID;
            state.object[count].mesh = crateMesh;
            state.object[count].position = glm::vec3(-9 +(1.5 * (i % 13)), 1.0, -9 + row*1.5);
            state.object[count].entityType = CRATE;
            state.object[count].height = 2.0f;
            state.object[count].scale = glm::vec3(1.5, 2.0f, 1.5);
            count++;
        }
        if(count>= 97) {
            break;

        }
    }

    state.enemy = new Entity[ENEMY_COUNT];
    GLuint enemyTextureID = Util::LoadTexture("bad.png");
    state.enemy[0].billboard = true;
    state.enemy[0].coin = false;
    state.enemy[0].collected = false;
    state.enemy[0].width = 0.5;
    state.enemy[0].height = 0.2;
    state.enemy[0].textureID = enemyTextureID;
    state.enemy[0].position = glm::vec3(1.5, 0.3297, 4.5);
    state.enemy[0].scale = glm::vec3(0.697, 0.697, 0.697);
    state.enemy[0].rotation = glm::vec3(0, 0, 0);
    state.enemy[0].acceleration = glm::vec3(0, 0, 0);
    state.enemy[0].entityType = ENEMY;
    state.enemy[0].aitype = JUMPER;

    state.enemy[1].billboard = true;
    state.enemy[1].coin = false;
    state.enemy[1].collected = false;
    state.enemy[1].width = 0.5;
    state.enemy[1].height = 0.2;
    state.enemy[1].textureID = enemyTextureID;
    state.enemy[1].position = glm::vec3(-1.5, 0.3297, -1.5);
    state.enemy[1].scale = glm::vec3(0.697, 0.697, 0.697);
    state.enemy[1].rotation = glm::vec3(0, 0, 0);
    state.enemy[1].acceleration = glm::vec3(0, 0, 0);
    state.enemy[1].aitype = PATROLLER;
    state.enemy[1].entityType = ENEMY;

    state.enemy[2].billboard = true;
    state.enemy[2].coin = false;
    state.enemy[2].collected = false;
    state.enemy[2].width = 0.5;
    state.enemy[2].height = 0.2;
    state.enemy[2].textureID = enemyTextureID;
    state.enemy[2].position = glm::vec3(-7.5, 0.3297, 7.5);
    state.enemy[2].scale = glm::vec3(0.697, 0.697, 0.697);
    state.enemy[2].rotation = glm::vec3(0, 0, 0);
    state.enemy[2].acceleration = glm::vec3(0, 0, 0);
    state.enemy[2].aitype = JUMPER;
    state.enemy[2].entityType = ENEMY;

    state.enemy[3].billboard = true;
    state.enemy[3].coin = false;
    state.enemy[3].collected = false;
    state.enemy[3].width = 0.5;
    state.enemy[3].height = 0.4;
    state.enemy[3].textureID = enemyTextureID;
    state.enemy[3].position = glm::vec3(4.5, 0.3297, -1.5);
    state.enemy[3].scale = glm::vec3(0.697, 0.697, 0.697);
    state.enemy[3].rotation = glm::vec3(0, 0, 0);
    state.enemy[3].acceleration = glm::vec3(0, 0, 0);
    state.enemy[3].aitype = JUMPER;
    state.enemy[3].entityType = ENEMY;

    state.enemy[4].billboard = true;
    state.enemy[4].coin = false;
    state.enemy[4].collected = false;
    state.enemy[4].width = 0.5;
    state.enemy[4].height = 0.4;
    state.enemy[4].textureID = enemyTextureID;
    state.enemy[4].position = glm::vec3(-4.5, 0.3297, 1.5);
    state.enemy[4].scale = glm::vec3(0.697, 0.697, 0.697);
    state.enemy[4].rotation = glm::vec3(0, 0, 0);
    state.enemy[4].acceleration = glm::vec3(0, 0, 0);
    state.enemy[4].aitype = JUMPER;
    state.enemy[4].entityType = ENEMY;

    GLuint ballTextureID = Util::LoadTexture("ball.png");
    state.enemy[5].billboard = true;
    state.enemy[5].coin = true;
    state.enemy[5].collected = false;
    state.enemy[5].width = 0.5;
    state.enemy[5].height = 0.4;
    state.enemy[5].textureID = ballTextureID;
    state.enemy[5].position = glm::vec3(1.5, 0.5, 6);
    state.enemy[5].scale = glm::vec3(0.5, 0.5, 0.5);
    state.enemy[5].rotation = glm::vec3(0, 0, 0);
    state.enemy[5].acceleration = glm::vec3(0, 0, 0);
    state.enemy[5].entityType = BALL;

    state.enemy[6].billboard = true;
    state.enemy[6].coin = true;
    state.enemy[6].collected = false;
    state.enemy[6].width = 0.5;
    state.enemy[6].height = 0.4;
    state.enemy[6].textureID = ballTextureID;
    state.enemy[6].position = glm::vec3(-7.5, 0.5, 7.5);
    state.enemy[6].scale = glm::vec3(0.5, 0.5, 0.5);
    state.enemy[6].rotation = glm::vec3(0, 0, 0);
    state.enemy[6].acceleration = glm::vec3(0, 0, 0);
    state.enemy[6].entityType = BALL;

    state.enemy[7].billboard = true;
    state.enemy[7].coin = true;
    state.enemy[7].collected = false;
    state.enemy[7].width = 0.5;
    state.enemy[7].height = 0.4;
    state.enemy[7].textureID = ballTextureID;
    state.enemy[7].position = glm::vec3(7.5, 0.5, -7.5);
    state.enemy[7].scale = glm::vec3(0.5, 0.5, 0.5);
    state.enemy[7].rotation = glm::vec3(0, 0, 0);
    state.enemy[7].acceleration = glm::vec3(0, 0, 0);
    state.enemy[7].entityType = BALL;


    state.enemy[8].billboard = true;
    state.enemy[8].coin = true;
    state.enemy[8].collected = false;
    state.enemy[8].width = 0.5;
    state.enemy[8].height = 0.4;
    state.enemy[8].textureID = ballTextureID;
    state.enemy[8].position = glm::vec3(-1.5, 0.5, -7.5);
    state.enemy[8].scale = glm::vec3(0.5, 0.5, 0.5);
    state.enemy[8].rotation = glm::vec3(0, 0, 0);
    state.enemy[8].acceleration = glm::vec3(0, 0, 0);
    state.enemy[8].entityType = BALL;

    state.enemy[9].billboard = true;
    state.enemy[9].coin = true;
    state.enemy[9].collected = false;
    state.enemy[9].width = 0.5;
    state.enemy[9].height = 0.4;
    state.enemy[9].textureID = ballTextureID;
    state.enemy[9].position = glm::vec3(4.5, 0.5, 7.5);
    state.enemy[9].scale = glm::vec3(0.5, 0.5, 0.5);
    state.enemy[9].rotation = glm::vec3(0, 0, 0);
    state.enemy[9].acceleration = glm::vec3(0, 0, 0);
    state.enemy[9].entityType = BALL;




}

void Platform::Update(float deltaTime) {

    state.player->Update(deltaTime, state.player, state.object, OBJECT_COUNT, state.enemy, ENEMY_COUNT);
    for (int i = 0; i < OBJECT_COUNT; i++) {
        state.object[i].Update(deltaTime, state.player, state.object, OBJECT_COUNT, state.enemy, ENEMY_COUNT);
    }

    for (int i = 0; i < ENEMY_COUNT; i++) {
        state.enemy[i].Update(deltaTime, state.player, state.object, OBJECT_COUNT, state.enemy, ENEMY_COUNT);
    }

    


}


void Platform::Render(ShaderProgram* program) {
    for (int i = 0; i < OBJECT_COUNT; i++) {
        state.object[i].Render(program);
    }

    for (int i = 0; i < ENEMY_COUNT; i++) {
        state.enemy[i].Render(program);
    }



    

}