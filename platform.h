#pragma once
#include "Scene.h"
#include <vector>
class Platform : public Scene {
public:
	void Initialize() override;
	void Update(float deltaTime) override;
	void Render(ShaderProgram* program) override;
};