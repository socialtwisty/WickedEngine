#pragma once
#include "stdafx.h"

struct MyTestComponent {
	bool dummy;
	int value;
	void Serialize(wi::Archive& archive, wi::ecs::EntitySerializer& seri);
};

class GameRenderPath : public wi::RenderPath3D {
public:
	void Load() override;
	void Update(float dt) override;
};

class GameApp : public wi::Application {
public:
	GameRenderPath renderer;
	static GameApp* App;

	static uint64_t tick;
	static wi::ecs::ComponentManager<MyTestComponent>* myComponentLibrary;
	static wi::ecs::Entity entDummy;

	void Initialize() override;
	GameRenderPath* GetRenderer() { return &renderer; }

};
