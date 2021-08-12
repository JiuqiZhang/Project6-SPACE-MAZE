#include "Menu.h"
#define OBJECT_COUNT 2
void Menu::Initialize() {
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);
	state.nextScene = -1;
    state.player = new Entity();
    state.player->inMenu = true;


    

    GLuint coinTextureID = Util::LoadTexture("ball.png");
    GLuint enemyTextureID = Util::LoadTexture("bad.png");
    state.object = new Entity[OBJECT_COUNT];
    state.object[0].textureID = coinTextureID;
    state.object[0].position = glm::vec3(0, 1.5f,0);
    state.object[0].billboard = true;
    state.object[0].scale = glm::vec3(0.5);
    state.object[0].rotation = glm::vec3(0, 0, 0);
    state.object[0].acceleration = glm::vec3(0, 0, 0);

    state.object[1].position = glm::vec3(0, 2.5f, 0);
    state.object[1].textureID = enemyTextureID;
    state.object[1].billboard = true;
    state.object[1].scale = glm::vec3(0.5);
    state.object[1].rotation = glm::vec3(0, 0, 0);
    state.object[1].acceleration = glm::vec3(0, 0, 0);
}
void Menu::Update(float deltaTime) {
    for (int i = 0; i < OBJECT_COUNT; i++) {
        state.object[i].Update(deltaTime,state.player, state.object, OBJECT_COUNT, NULL, 0);
    }
}
void Menu::Render(ShaderProgram* program) {

    for (int i = 0; i < OBJECT_COUNT; i++) {
        state.object[i].Render(program);
    }
}
