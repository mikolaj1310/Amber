#include "Player.h"

Player::Player()
{
	velocity.x = 7;
	velocity.y = 7;
	maxVelocity.x = 40;
	maxVelocity.y = 40;
	objectType = PLAYER;
	faceDirState = FD_RIGHT;
	initChasisAnimation();
	initTreadsAnimation();
}

void Player::initChasisAnimation()
{
	chasisIdle1Tex.loadFromFile("gfx/Player/tank chasis idle.png");
	setTexture(&chasisIdle1Tex);


	chasisIdleAnimation.addFrame(sf::IntRect(0, 0, 64, 64));
	chasisIdleAnimation.addFrame(sf::IntRect(64, 0, 64, 64));
	chasisIdleAnimation.addFrame(sf::IntRect(128, 0, 64, 64));
	chasisIdleAnimation.addFrame(sf::IntRect(192, 0, 64, 64));
	chasisIdleAnimation.addFrame(sf::IntRect(256, 0, 64, 64));
	chasisIdleAnimation.addFrame(sf::IntRect(320, 0, 64, 64));
	chasisIdleAnimation.addFrame(sf::IntRect(384, 0, 64, 64));
	chasisIdleAnimation.addFrame(sf::IntRect(448, 0, 64, 64));
	chasisIdleAnimation.addFrame(sf::IntRect(512, 0, 64, 64));
	chasisIdleAnimation.setFrameSpeed(1.f / 18.f);
	chasisIdleAnimation.setSpriteSize(sf::Vector2f(64, 64));

	currentChasisAnimation = &chasisIdleAnimation;

	setSize(currentChasisAnimation->getSpriteSize());
	setOrigin(getSize().x / 2, getSize().y / 2);
	setTextureRect(currentChasisAnimation->getCurrentFrame());
}

void Player::initTreadsAnimation()
{
	treadsTex.loadFromFile("gfx/Player/tank treads default.png");
	treads.setTexture(&treadsTex);

	treadsMovingAnimation.addFrame(sf::IntRect(0, 0, 64, 64));
	treadsMovingAnimation.addFrame(sf::IntRect(64, 0, 64, 64));
	treadsMovingAnimation.addFrame(sf::IntRect(128, 0, 64, 64));
	treadsMovingAnimation.addFrame(sf::IntRect(192, 0, 64, 64));
	treadsMovingAnimation.addFrame(sf::IntRect(256, 0, 64, 64));
	treadsMovingAnimation.addFrame(sf::IntRect(320, 0, 64, 64));
	treadsMovingAnimation.addFrame(sf::IntRect(384, 0, 64, 64));
	treadsMovingAnimation.addFrame(sf::IntRect(448, 0, 64, 64));
	treadsMovingAnimation.addFrame(sf::IntRect(512, 0, 64, 64));
	treadsMovingAnimation.setFrameSpeed(1.f / (velocity.x * 5));
	treadsMovingAnimation.setSpriteSize(sf::Vector2f(64, 64));

	currentTreadsAnimation = &treadsMovingAnimation;

	treads.setSize(currentTreadsAnimation->getSpriteSize());
	treads.setOrigin(treads.getSize().x / 2, treads.getSize().y / 2);
	treads.setTextureRect(currentTreadsAnimation->getCurrentFrame());
}

void Player::init(b2Body* gBody)
{
	groundBody = gBody;
}

b2World* Player::initB2Body(b2World* world)
{

	//create physics body
	b2BodyDef playerBodyDef;
	playerBodyDef.type = b2_dynamicBody;
	playerBodyDef.position = b2Vec2(350 / box2dScale, 64 / box2dScale);
	playerBodyDef.linearDamping = 10;
	playerBodyDef.fixedRotation = false;

	playerBody = world->CreateBody(&playerBodyDef);

	//create shape for player
	b2PolygonShape playerShape;
	//playerShape.SetAsBox(67 / box2dScale, 109 / box2dScale);
	playerShape.SetAsBox((chasisIdleAnimation.getSpriteSize().x / 2) / box2dScale, (chasisIdleAnimation.getSpriteSize().y / 2) / box2dScale);

	//create fixture
	b2FixtureDef playerFixtureDef;
	playerFixtureDef.shape = &playerShape;
	playerFixtureDef.density = 0.5;
	playerFixtureDef.friction = 0;
	
	//create fixture on the rigig body
	playerBody->CreateFixture(&playerFixtureDef);

	playerBody->SetUserData(playerBody);

	//update visual sim
	updateFromSimulation(playerBody);

	
	return world;
}

Player::~Player()
{
}

void Player::update(float dt)
{	//add diagonal movement and it should work fine

	animatePlayer(dt);
	rotation = atan(
		(groundBody->GetPosition().y - playerBody->GetPosition().y) / 
		(groundBody->GetPosition().x - playerBody->GetPosition().x));

	//if (groundBody->GetPosition().x - playerBody->GetPosition().x < 0)
		//rotation = -rotation;
	if (groundBody->GetPosition().x - playerBody->GetPosition().x < 0)
		rotation = rotation + (90 * pi / 180);
	else
		rotation = rotation - (90 * pi / 180);

	playerBody->SetTransform(playerBody->GetPosition(), rotation);

	updateFromSimulation(playerBody);
}


void Player::handleInput(float dt, Input* in)
{
	input = in;
	if (input->isKeyDown(sf::Keyboard::A))
	{
		moveState = MS_LEFT;
		faceDirState = FD_LEFT;
	}
	else if (input->isKeyDown(sf::Keyboard::D))
	{
		moveState = MS_RIGHT;
		faceDirState = FD_RIGHT;
	}
	else
	{
		moveState = MS_STOP;
	}


	//velocities based on rotation
	b2Vec2 velDir(0, 0);
	velDir.x = cos(rotation) * velocity.x;
	velDir.y = sin(rotation) * velocity.x;
	switch (moveState)
	{
	case MS_LEFT:
		playerBody->ApplyForceToCenter(b2Vec2(-velDir.x * maxVelocity.x, -velDir.y * maxVelocity.x), true);
		break;
	case MS_RIGHT:	
		playerBody->ApplyForceToCenter(b2Vec2(velDir.x * maxVelocity.x, velDir.y * maxVelocity.x), true);
		break;
	case MS_STOP:
		break;
	}

	playerBody->ApplyForceToCenter(((gravForce * 2) * gravity), true);

	if (input->isKeyDown(sf::Keyboard::Space))
	{
		playerBody->ApplyForceToCenter((velocity.y * 100) * gravity, true);
	}
}

void Player::animatePlayer(float dt)
{
	setTextureRect(currentChasisAnimation->getCurrentFrame());
	treads.setTextureRect(currentTreadsAnimation->getCurrentFrame());
	treads.setPosition(playerBody->GetPosition().x * box2dScale, playerBody->GetPosition().y * box2dScale);
	treads.setRotation(rotation * 180 / pi);


	if (faceDirState == FD_LEFT)
	{
		currentChasisAnimation->setFlipped(true);
		currentTreadsAnimation->setFlipped(true);
	}
	if (faceDirState == FD_RIGHT)
	{
		currentChasisAnimation->setFlipped(false);
		currentTreadsAnimation->setFlipped(false);
	}


	if (moveState == MS_STOP)
	{
		chasisIdleAnimation.setFrameSpeed(1.f / 18.f);
		currentChasisAnimation = &chasisIdleAnimation;
	}
	if (moveState == MS_LEFT)
	{
		chasisIdleAnimation.setFrameSpeed(1.f / 30.f);
		currentTreadsAnimation->animate(dt);
	}
	if (moveState == MS_RIGHT)
	{
		chasisIdleAnimation.setFrameSpeed(1.f / 30.f);
		currentTreadsAnimation->animate(dt);
	}

	currentChasisAnimation->animate(dt);
}

void Player::render(sf::RenderWindow* window)
{
	window->draw(treads);
}