#include "stdafx.h"
#include "game.h"

wi::ecs::ComponentManager<MyTestComponent>& myComponentLibrary = wi::scene::GetScene().componentLibrary.Register<MyTestComponent>("banana");

void MyTestComponent::Serialize(wi::Archive& archive, wi::ecs::EntitySerializer& seri) {
	// stubbed; Nothing to serialize yet.
}

void GameRenderPath::Load() {
	RenderPath3D::Load();
}

void GameRenderPath::Update(float dt) {

	if (GameApp::tick == 1) {
		GameApp::entDummy = wi::ecs::CreateEntity();
		myComponentLibrary.Create(GameApp::entDummy);
		MyTestComponent* testcomp = myComponentLibrary.GetComponent(GameApp::entDummy);
		// do something with it
	}

	if (GameApp::tick == 2) {
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

	myComponentLibrary = wi::scene::GetScene().componentLibrary.Register<MyTestComponent>("banana");

	renderer.Load();
	ActivatePath(&renderer);
}
