#include "StartScene.h"
#include "Player.h"
#include "Sprite.h"
#include "MovementComponent.h"
#include "Transform2D.h"

void StartScene::start()
{
	Player* player = new Player(50, 50, "Player");
	player->getTransform()->setScale({ 50, 50 });

	addActor(player);
}
