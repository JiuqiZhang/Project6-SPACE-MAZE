#pragma once
#define GL_SILENCE_DEPRECATION

#ifdef _WINDOWS
#include <GL/glew.h>
#endif

#define GL_GLEXT_PROTOTYPES 1

#include <SDL.h>
#include <SDL_opengl.h>
#include "glm/mat4x4.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "ShaderProgram.h"
#include "Mesh.h"
enum EntityType { BALL, PLAYER, PLATFORM, ENEMY, CUBE, SHIP, FLOOR, CRATE };
enum AIType{ JUMPER, PATROLLER};
class Entity {
public:
    EntityType entityType;
    AIType aitype;
    glm::vec3 position;
    glm::vec3 velocity;
    glm::vec3 acceleration;
    glm::vec3 rotation;
    glm::vec3 scale;
    int live;
    int coinnum;
    float speed;
    bool isActive = true;
    float timeLeft;
    float jumpPower;
    GLuint textureID;
    Mesh *mesh;


    bool jump;
    bool billboard;
    bool coin;
    float width;
    float height;
    float depth;
    bool collected = false;
    bool picked = false;
    bool hitCube;
    bool onfloor;
    bool onTop;
    bool inMenu;
    bool fall = false;
    bool falling = false;
    glm::mat4 modelMatrix;
    
    Entity();
    
    bool CheckCollision(Entity* other);
    void Update(float deltaTime, Entity* player, Entity* objects, int objectCount, Entity* enemy, int enemyCount);
    void CheckCollisionsY(Entity* objects, int objectCount);
    void CheckCollisionsX(Entity* objects, int objectCount);
    void Render(ShaderProgram *program);
    void DrawBillboard(ShaderProgram* program);
    void CheckCollisionsZ(Entity* objects, int objectCount);
};



