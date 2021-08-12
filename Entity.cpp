#include "Entity.h"

Entity::Entity()
{
    position = glm::vec3(0);
    acceleration = glm::vec3(0);
    velocity = glm::vec3(0);
    modelMatrix = glm::mat4(1.0f);
    rotation = glm::vec3(0);
    scale = glm::vec3(1);
    speed = 0.0f;

    billboard = false;
    width = 1.0f;
    height = 1.0f;
    depth = 1.0f;

}
bool Entity::CheckCollision(Entity* other)
{



    if (other->collected) return false;
    float xdist = fabs(position.x - other->position.x) - ((width + other->width) / 2.0f);
    float ydist = fabs(position.y - other->position.y) - ((height + other->height) / 2.0f);
    float zdist = fabs(position.z - other->position.z) - ((depth + other->depth) / 2.0f);
    if (xdist < 0 && ydist < 0 && zdist < 0) return true;

    return false;
}

void Entity::CheckCollisionsX(Entity* objects, int objectCount)
{
    for (int i = 0; i < objectCount; i++)
    {
        Entity* object = &objects[i];

        if (CheckCollision(object))
        {
            if (object->entityType == ENEMY) {
                object->collected = true;
                collected = true;
                object->isActive = false;
                live--;
                return;
            }
            if (object->entityType == BALL) {
                object->collected = true;
                object->isActive = false;
                picked = true;
                coinnum--;
                return;
            }
            if (objects->entityType == CRATE) { hitCube = true; }
            float xdist = fabs(position.x - object->position.x);
            float penetrationX = fabs(xdist - (width / 2.0f) - (object->width / 2.0f));
            if (velocity.x > 0) {
                position.x -= penetrationX;
                velocity.x = 0;

            }
            else if (velocity.x < 0) {
                position.x += penetrationX;
                velocity.x = 0;

            }
        }
    }

}
void Entity::CheckCollisionsZ(Entity* objects, int objectCount)
{


    for (int i = 0; i < objectCount; i++)
    {
        Entity* object = &objects[i];

        if (CheckCollision(object))
        {
            if (object->entityType == ENEMY) {
                object->collected = true;
                collected = true;
                object->isActive = false;
                live--;
                return;
            }
            if (object->entityType == BALL) {
                object->collected = true;
                object->isActive = false;
                picked = true;
                coinnum--;
                return;
            }
            if (objects->entityType == CRATE) { hitCube = true; }
            float zdist = fabs(position.z - object->position.z);
            float penetrationZ = fabs(zdist - (width / 2.0f) - (object->width / 2.0f));
            if (velocity.z > 0) {
                position.z -= penetrationZ;
                velocity.z = 0;

            }
            else if (velocity.z < 0) {
                position.z += penetrationZ;
                velocity.z = 0;

            }
        }
    }

}
void Entity::CheckCollisionsY(Entity* objects, int objectCount)
{
    for (int i = 0; i < objectCount; i++)
    {
        Entity* object = &objects[i];

        if (CheckCollision(object))
        {
            if (object->entityType == ENEMY) {
                object->collected = true;
                collected = true;
                object->isActive = false;
                live--;
                return;
            }
            if (object->entityType == BALL) {
                object->collected = true;
                object->isActive = false;
                picked = true;
                coinnum--;
                return;
            }
            float ydist = fabs(position.y - object->position.y);
            float penetrationY = fabs(ydist - (height / 2.0f) - (object->height / 2.0f));
            if (velocity.y > 0) {
                position.y -= penetrationY;
                velocity.y = 0;

            }
            else if (velocity.y < 0) {
                if (object->entityType == CRATE) {
                    onTop = true;
                }
                position.y += penetrationY;
                velocity.y = 0;


            }
        }
    }

}



void Entity::Update(float deltaTime, Entity* player, Entity* objects, int objectCount, Entity* enemy, int enemyCount)

{
    if (isActive == false) { return; }
    glm::vec3 previousPosition = position;
    hitCube = false;
    collected = false;
    onfloor = false;
    onTop = false;
    if (billboard) {
        float directionX = position.x - player->position.x;
        float directionZ = position.z - player->position.z;
        if (coin) {
            rotation.y += glm::degrees(2.97f)*deltaTime;

        }
        else {
            rotation.y = glm::degrees(atan2f(directionX, directionZ));
        }
        
    }


    velocity += acceleration * deltaTime;
    position += velocity * deltaTime;

    if (entityType == PLAYER) {
        
        if (position.y > 0.697f) {
            velocity.y += -9.97f * deltaTime;
        }
        else if(position.y <= 0.697f){
            if (jump) {
                jump = false;

                velocity.y += jumpPower;
            }
            else if (!falling){
                velocity.y = 0;
                position.y = 0.697f;
            }
            
        }
        if (position.z > 9.75 || position.z < -9.75) {
            velocity.y += -1.997f * deltaTime;
            falling = true;
        }
        else if (position.y < 0) {
            velocity.y += -1.997f * deltaTime;
            falling = true;

        }
        for (int i = 0; i < objectCount; i++)
        {
            // Ignore collisions with the floor
            //if ( objects[i].entityType == FLOOR && CheckCollision(&objects[i])) {
                
           // }
                //CheckCollisionsY(objects, objectCount);
            // Ignore collisions with the floor
            CheckCollisionsX(&objects[i], 1);
            CheckCollisionsY(&objects[i], 1);
            CheckCollisionsZ(&objects[i], 1);
            //if (onTop == true) {
            //    position.y = previousPosition.y;
             //   break;
            //}
            if(hitCube == true){
                position.x = previousPosition.x;
                position.z = previousPosition.z;

                break;
            }

        }
        
            for (int i = 0; i < enemyCount; i++)
            {
                if (enemy[i].isActive == true) {

                    CheckCollisionsX(&enemy[i], 1);
                    CheckCollisionsY(&enemy[i], 1);
                    CheckCollisionsZ(&enemy[i], 1);
                }

            }
        

        if (position.y < -6.97) {
            fall = true;
        }
    }



    if (entityType == CUBE) {
        rotation.y += 45 * deltaTime;
        rotation.z += 45 * deltaTime;

    }
    else if (entityType == ENEMY) {
        if (aitype == JUMPER) {
            if (position.y > 0.3297) {
                velocity.y += -3.97f * deltaTime;
            }
            else if (position.y <= 0.3297) {
                    velocity.y += 4.397f;
                }
            
        }
        else if (aitype == PATROLLER) {
            if (position.x <= 0.6) {
                velocity.x += 1.0 * deltaTime;
            }
            else if (position.x >= 4.5) {
                velocity.x -= 1.0f * deltaTime;
            }
        }
        rotation.y += 45 * deltaTime;
        //rotation.z += 45 * deltaTime;
    }
    modelMatrix = glm::mat4(1.0f);
    modelMatrix = glm::translate(modelMatrix, position);
    modelMatrix = glm::rotate(modelMatrix, glm::radians(rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
    modelMatrix = glm::scale(modelMatrix, scale);
    modelMatrix = glm::rotate(modelMatrix, glm::radians(rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
}

void Entity::Render(ShaderProgram *program) {
    if (isActive == false) { return; }
    program->SetModelMatrix(modelMatrix);
   

    glBindTexture(GL_TEXTURE_2D, textureID);

    if (billboard) {
        DrawBillboard(program);
    }
    else {
        mesh->Render(program);
    }

}

void Entity::DrawBillboard(ShaderProgram* program) {
    float vertices[] = { -0.5, -0.5, 0.5, -0.5, 0.5, 0.5, -0.5, -0.5, 0.5, 0.5, -0.5, 0.5 };
    float texCoords[] = { 0.0, 1.0, 1.0, 1.0, 1.0, 0.0, 0.0, 1.0, 1.0, 0.0, 0.0, 0.0 };

    glVertexAttribPointer(program->positionAttribute, 2, GL_FLOAT, false, 0, vertices);
    glEnableVertexAttribArray(program->positionAttribute);

    glVertexAttribPointer(program->texCoordAttribute, 2, GL_FLOAT, false, 0, texCoords);
    glEnableVertexAttribArray(program->texCoordAttribute);

    glDrawArrays(GL_TRIANGLES, 0, 6);

    glDisableVertexAttribArray(program->positionAttribute);
    glDisableVertexAttribArray(program->texCoordAttribute);
}

