#define GL_SILENCE_DEPRECATION

#ifdef _WINDOWS
#include <GL/glew.h>
#endif

#define GL_GLEXT_PROTOTYPES 1

#include <vector>
#include <SDL.h>
#include <SDL_opengl.h>
#include <SDL_mixer.h>
#include "glm/mat4x4.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "ShaderProgram.h"
#include "Util.h"
#include "Entity.h"
#include "Effects.h"

#include <string>

//seperate scene!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
#include "Scene.h"
#include "Menu.h"
#include "Falldown.h"
#include "platform.h"
#define STRING(num) #num

Mix_Music* endmusic;
Mix_Music* menumusic;
Mix_Chunk* bounce;
Mix_Chunk* hit;
Mix_Chunk* coin;

Effects* effects;
bool dead = false;
bool win = false;
bool lost = false;
Scene* currentScene;
Platform* platform;
Menu* menu;
FallDown* falldown;
glm::mat4 uiViewMatrix, uiProjectionMatrix;
GLuint fontTextureID;
GLuint coinballTextureID;

GLuint enemyTextureID;
GLuint cellTextureID;
GLuint fontTexture2ID;
bool gameplaying = false;
bool inMenu = true;
void SwitchToScene(Scene* scene) {
    currentScene = scene;
    currentScene->Initialize();
}
SDL_Window* displayWindow;
bool gameIsRunning = true;

ShaderProgram program;
glm::mat4 viewMatrix, modelMatrix, projectionMatrix;

bool lasthit = false;


void Initialize() {
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);
    displayWindow = SDL_CreateWindow("Project6!", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1280, 720, SDL_WINDOW_OPENGL);
    SDL_GLContext context = SDL_GL_CreateContext(displayWindow);
    SDL_GL_MakeCurrent(displayWindow, context);

#ifdef _WINDOWS
    glewInit();
#endif

    glViewport(0, 0, 1280, 720);

    program.Load("shaders/vertex_textured.glsl", "shaders/fragment_textured.glsl");
    
    
    
    //play music
    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 4096);

   
    menumusic = Mix_LoadMUS("bg.wav");
    Mix_FadeInMusic(menumusic, -1, 100);
    Mix_VolumeMusic(MIX_MAX_VOLUME * 4);

    bounce = Mix_LoadWAV("jump.wav");
    hit = Mix_LoadWAV("hit.wav");
    coin = Mix_LoadWAV("coin.wav");
    viewMatrix = glm::mat4(1.0f);
    modelMatrix = glm::mat4(1.0f);
    projectionMatrix = glm::perspective(glm::radians(45.0f), 1.777f, 0.1f, 100.0f);



    program.SetProjectionMatrix(projectionMatrix);
    program.SetViewMatrix(viewMatrix);
    program.SetColor(1.0f, 1.0f, 1.0f, 1.0f);


    //UI MARICES
    uiViewMatrix = glm::mat4(1.0);
    uiProjectionMatrix = glm::ortho(-6.4f, 6.4f, -3.6f, 3.6f, -1.0f, 1.0f);
    fontTextureID = Util::LoadTexture("font1.png");
    fontTexture2ID = Util::LoadTexture("font2.png");

    //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    coinballTextureID = Util::LoadTexture("smallball.png");
    enemyTextureID = Util::LoadTexture("bad.png");
    cellTextureID = Util::LoadTexture("floor2.jpg");
    glUseProgram(program.programID);




    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_DEPTH_TEST);
    glDepthMask(GL_TRUE);
    glDepthFunc(GL_LEQUAL);

    glClearColor(0.386f, 0.445f, 0.4492f, 1.0f);

    bool gameplaying = false;
    bool inMenu = true;

    bool gameIsRunning = true;


    platform = new Platform();
    menu = new Menu();
    SwitchToScene(menu);

  


    effects = new Effects(projectionMatrix, viewMatrix);
    effects->Start(FADEIN, 0.1);


}
void ProcessInput() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
        case SDL_QUIT:
        case SDL_WINDOWEVENT_CLOSE:
            gameIsRunning = false;
            break;

        case SDL_KEYDOWN:
            switch (event.key.keysym.sym) {
            case SDLK_SPACE:
                if (!currentScene->state.player->falling) {
                    Mix_PlayChannel(-1, bounce, 0);

                    currentScene->state.player->jump = true;
                }

                //Mix_PlayChannel(-1, bounce, 0);
                break;
            case SDLK_RETURN:
                if (gameplaying == false && !dead) {
                    SwitchToScene(platform);
                    gameplaying = true;
                    inMenu = false;
                }
                break;

            }
            break;
        }
    }
    const Uint8* keys = SDL_GetKeyboardState(NULL);
    if (win || lost) { return; }
    if (currentScene->state.player->position.y <= 1.0f) {
        if (keys[SDL_SCANCODE_LEFT]) {
            currentScene->state.player->rotation.y += 1.5f;
        }
        else if (keys[SDL_SCANCODE_RIGHT]) {
            currentScene->state.player->rotation.y -= 1.5f;
        }
        currentScene->state.player->velocity.x = 0;
        currentScene->state.player->velocity.z = 0;

        if (keys[SDL_SCANCODE_D]) {
            currentScene->state.player->velocity.z = cos(glm::radians(currentScene->state.player->rotation.y + 90.0f)) * 2.0f;
            currentScene->state.player->velocity.x = sin(glm::radians(currentScene->state.player->rotation.y + 90.0f)) * 2.0f;

        }
        else if (keys[SDL_SCANCODE_A]) {
            currentScene->state.player->velocity.z = -cos(glm::radians(currentScene->state.player->rotation.y + 90.0f)) * 2.0f;
            currentScene->state.player->velocity.x = -sin(glm::radians(currentScene->state.player->rotation.y + 90.0f)) * 2.0f;
        }
        if (keys[SDL_SCANCODE_W]) {
            currentScene->state.player->velocity.z = cos(glm::radians(currentScene->state.player->rotation.y)) * -2.0f;
            currentScene->state.player->velocity.x = sin(glm::radians(currentScene->state.player->rotation.y)) * -2.0f;
        }
        else if (keys[SDL_SCANCODE_S]) {
            currentScene->state.player->velocity.z = cos(glm::radians(currentScene->state.player->rotation.y)) * 2.0f;
            currentScene->state.player->velocity.x = sin(glm::radians(currentScene->state.player->rotation.y)) * 2.0f;
        }

        if (currentScene->state.player->fall == true) {
            SwitchToScene(menu);
            gameplaying = false;
            dead = true;
        }
    }
    if (currentScene->state.player->collected) {
        Mix_PlayChannel(-1, hit, 0);
        currentScene->state.player->collected = false;
    }
    if (currentScene->state.player->picked){
        Mix_PlayChannel(-1, coin, 0);
        currentScene->state.player->picked = false;
    }

}

#define FIXED_TIMESTEP 0.0166666f
float lastTicks = 0;
float accumulator = 0.0f;

void Update() {

    float ticks = (float)SDL_GetTicks() / 1000.0f;
    float deltaTime = ticks - lastTicks;
    lastTicks = ticks;

    
    if (gameplaying) {
        currentScene->state.player->timeLeft -= 1.0 * deltaTime;
    }
    deltaTime += accumulator;
    if (deltaTime < FIXED_TIMESTEP) {
        accumulator = deltaTime;
        return;
    }

    while (deltaTime >= FIXED_TIMESTEP) {
        currentScene->Update(FIXED_TIMESTEP);
        effects->Update(FIXED_TIMESTEP);

        deltaTime -= FIXED_TIMESTEP;
    }

    accumulator = deltaTime;

    viewMatrix = glm::mat4(1.0f);
    viewMatrix = glm::rotate(viewMatrix, glm::radians(currentScene->state.player->rotation.y), glm::vec3(0, -1.0f, 0));
    viewMatrix = glm::translate(viewMatrix, -currentScene->state.player->position);
}


void Render() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


    program.SetProjectionMatrix(projectionMatrix);
    program.SetViewMatrix(viewMatrix);
    glUseProgram(program.programID);


    currentScene->Render(&program);
    effects->Render();
    program.SetProjectionMatrix(uiProjectionMatrix);
    program.SetViewMatrix(uiViewMatrix);

    std::string lives = std::to_string(currentScene->state.player->live);
    std::string s = std::to_string(currentScene->state.player->timeLeft);
    GLuint heartTextureID = Util::LoadTexture("juese.png");
    if (dead) {
        Util::DrawText(&program, fontTexture2ID, "YOU FELL!", 1.097f, -0.097, glm::vec3(-4.597, 2, 0));
        Util::DrawText(&program, fontTexture2ID, "Good Bye~", 1.097f, -0.097, glm::vec3(-4.597, 0, 0));
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

        SDL_GL_SwapWindow(displayWindow);
        return;

    }
    if (currentScene==platform&&currentScene->state.player->coinnum == 0) {
        win = true;
        Util::DrawText(&program, fontTexture2ID, "YOU WIN!", 1.097f, -0.097, glm::vec3(-4, -1, 0));
        Util::DrawText(&program, fontTexture2ID, "CONGRATS!", 1.097f, -0.097, glm::vec3(-4.597, 0, 0));
        Util::DrawText(&program, fontTexture2ID, "THANKS FOR PLAYING!", 0.297f, -0.097, glm::vec3(-4.597, 1, 0));
        endmusic = Mix_LoadMUS("main.wav");
        Mix_FadeInMusic(endmusic, -1, 100);
        glClearColor(0.2627f, 0.41960784313f, 0.819f, 1.0f);
        gameplaying = false;

    }
    if (currentScene == platform && currentScene->state.player->live == 0) {
        lost = true;
        Util::DrawText(&program, fontTexture2ID, "YOU LOST!", 1.097f, -0.097, glm::vec3(-4, -1, 0));
        Util::DrawText(&program, fontTexture2ID, "THANKS FOR PLAYING!", 0.297f, -0.097, glm::vec3(-4.597, 0, 0));
        endmusic = Mix_LoadMUS("main.wav");
        Mix_FadeInMusic(endmusic, -1, 100);
        glClearColor(0.417f, 0.207f, 0.20f, 1.0f);
        gameplaying = false;

    }
    if (currentScene == platform && currentScene->state.player->timeLeft <= 0) {
        lost = true;
        Util::DrawText(&program, fontTexture2ID, "YOU LOST!", 1.097f, -0.097, glm::vec3(-4, -1, 0));
        Util::DrawText(&program, fontTexture2ID, "THANKS FOR PLAYING!", 0.297f, -0.097, glm::vec3(-4.597, 0, 0));
        endmusic = Mix_LoadMUS("main.wav");
        Mix_FadeInMusic(endmusic, -1, 100);
        glClearColor(0.417f, 0.207f, 0.20f, 1.0f);
        gameplaying = false;
    }
    else if(currentScene->state.player->coinnum == 0){

    }
    if (gameplaying) {
        Util::DrawText(&program, fontTexture2ID, s.substr(0, 6), 0.5, -0.3f,
                glm::vec3(-6.15, 3.1697, 0));
        Util::DrawText(&program, fontTextureID, " seconds left", 0.5, -0.3f,
            glm::vec3(-5, 3.2, 0));

        Util::DrawText(&program, fontTextureID, "Lives left: "+lives, 0.5, -0.3f,
            glm::vec3(0, 3.2, 0));
        for (int i = 0; i < currentScene->state.player->live; i++) {
            Util::DrawIcon(&program, heartTextureID, glm::vec3(3 + (i * 0.5f), 3.2, 0));

        }
        GLuint blackTextureID = Util::LoadTexture("smallballblack.png");
        for (int i = 0; i < 5; i++)
        {
            // These icons are small, so just move 0.3 to the right for each one.
            Util::DrawIcon(&program, blackTextureID, glm::vec3(5 + (i * 0.3f), 3.2, 0));
        }
        for (int i = 0; i < 5-currentScene->state.player->coinnum; i++)
        {
            // These icons are small, so just move 0.3 to the right for each one.
            Util::DrawIcon(&program, coinballTextureID, glm::vec3(5 + (i * 0.3f), 3.2, 0));
        }
    }
    else if (inMenu){

        GLuint CC97TextureID = Util::LoadTexture("logo2.png");

        Util::DrawIcon(&program, cellTextureID, glm::vec3(-5.6, 2, 0));
        Util::DrawIcon(&program, cellTextureID, glm::vec3(-6.6, 2, 0));
        Util::DrawIcon(&program, cellTextureID, glm::vec3(-5.6, 1, 0));
        Util::DrawIcon(&program, cellTextureID, glm::vec3(-6.6, 1, 0));
        Util::DrawIcon(&program, cellTextureID, glm::vec3(-4.6, 2, 0));
        Util::DrawIcon(&program, cellTextureID, glm::vec3(-3.6, 3, 0));

        Util::DrawIcon(&program, cellTextureID, glm::vec3(-2.6, 2, 0));
        Util::DrawIcon(&program, cellTextureID, glm::vec3(-3.6, 2, 0));
        Util::DrawIcon(&program, cellTextureID, glm::vec3(-6.6, 1, 0));


        for (int i = 0; i < 9; i++) {
            Util::DrawIcon(&program, cellTextureID, glm::vec3(1.4 - i, 4, 0));

        }
        Util::DrawIcon(&program, cellTextureID, glm::vec3(-0.6, 1, 0));
        Util::DrawIcon(&program, cellTextureID, glm::vec3(-0.6, 2, 0));

        for (int i = 0; i < 7; i++) {
            if (i == 2) {
                continue;
            }
            Util::DrawIcon(&program, cellTextureID, glm::vec3(-6.597+i, 0, 0));

        }
        for (int i = 0; i < 9; i++) {
            Util::DrawIcon(&program, cellTextureID, glm::vec3(-6.597 + i, -2, 0));
            }

        for (int i = 0; i < 8; i++) {
            Util::DrawIcon(&program, cellTextureID, glm::vec3(1.4, -2 + i, 0));

        }
        Util::DrawIcon(&program, cellTextureID, glm::vec3(1.4, 2, 0));
        Util::DrawText(&program, fontTexture2ID, "SPACE MAZE", 1.097f, -0.097, glm::vec3(-4.597, 2, 0));
        Util::DrawText(&program, fontTexture2ID, "by Jiuqi Zhang", 0.4f, -0.1297f, glm::vec3(2.697, 1.1, 0));
        Util::DrawText(&program, fontTextureID, "''You are trapped in a space maze. You got ", 0.297f, -0.1f, glm::vec3(-5.25, -0.5, 0));
        Util::DrawText(&program, fontTexture2ID, "4", 0.297f, -0.1f, glm::vec3(3.2, -0.5, 0));
        Util::DrawText(&program, fontTextureID, " lives and ", 0.297f, -0.1f, glm::vec3(3.5, -0.5, 0));
        Util::DrawText(&program, fontTexture2ID, "197 ", 0.297f, -0.1f, glm::vec3(-6.25, -1.0, 0));
        Util::DrawText(&program, fontTextureID, "    seconds to collect all      keys to escape.''", 0.297f, -0.1f, glm::vec3(-6.25, -1.0, 0));
        Util::DrawText(&program, fontTexture2ID, "5", 0.297f, -0.1f, glm::vec3(-0.9, -1.0, 0));
        Util::DrawIcon(&program, coinballTextureID, glm::vec3(-0.35, -1, 0));

        Util::DrawIcon(&program, enemyTextureID, glm::vec3(-4.5, 0.9, 0));
        Util::DrawText(&program, fontTextureID, "is deadly!!!", 0.297f, -0.1f, glm::vec3(-3.75, 1, 0));
        Util::DrawText(&program, fontTexture2ID, "Maze", 0.297f, -0.1f, glm::vec3(1.1, -2, 0));

        Util::DrawText(&program, fontTextureID, "is unbreakable.", 0.297f, -0.1f, glm::vec3(2.2, -2, 0));

        Util::DrawText(&program, fontTexture2ID, "<- -> to rotate. W A S D to move.               Enter to start ^_^                      from 'No.97_Coconuthouse'", 0.197f, -0.1f, glm::vec3(-5.5, -3.497, 0));
        Util::DrawIcon(&program, CC97TextureID, glm::vec3(4, -3.0, 0));


        

    }




    SDL_GL_SwapWindow(displayWindow);
}

void Shutdown() {
    SDL_Quit();
}

int main(int argc, char* argv[]) {
    Initialize();

    while (gameIsRunning) {
        ProcessInput();
        Update();
        Render();
    }

    Shutdown();
    return 0;
}
