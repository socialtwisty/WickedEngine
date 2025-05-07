#include "stdafx.h"
#include "game.h"

wi::ecs::ComponentManager<MyTestComponent>* GameApp::myComponentLibrary;

void MyTestComponent::Serialize(wi::Archive& archive, wi::ecs::EntitySerializer& seri) {
	// stubbed; Nothing to serialize yet.
}

void GameRenderPath::Load() {
	RenderPath3D::Load();
}

void GameRenderPath::Update(float dt) {
	static wi::ecs::Entity e1, e2;

	if (GameApp::tick == 1) {
		e1 = wi::ecs::CreateEntity();
		e2 = wi::ecs::CreateEntity();

		MyTestComponent& c1 = GameApp::myComponentLibrary->Create(e1);
		MyTestComponent& c2 = GameApp::myComponentLibrary->Create(e2);

		c1.value = 10;
		c2.value = 20;
	}

	if (GameApp::tick == 2) {
		MyTestComponent* c1 = GameApp::myComponentLibrary->GetComponent(e1);
		MyTestComponent* c2 = GameApp::myComponentLibrary->GetComponent(e2);
		assert(c1->value == 10);
		assert(c2->value == 20);
	}

	if (GameApp::tick == 3) {
		wi::scene::Scene src;
		wi::scene::LoadModel(src, "../../Content/models/teapot.wiscene");
		wi::scene::GetScene().Merge(src);
	}

	GameApp::tick++;
	RenderPath3D::Update(dt);
}

uint64_t GameApp::tick = 0;
wi::ecs::Entity GameApp::entDummy = wi::ecs::INVALID_ENTITY;

void GameApp::Initialize() {
	Application::Initialize();
	renderer.init(canvas);

	myComponentLibrary = &wi::scene::GetScene().componentLibrary.Register<MyTestComponent>("banana");

	renderer.Load();
	ActivatePath(&renderer);
}
