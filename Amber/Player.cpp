#include "Player.h"

Player::Player()
{
	velocity.x = 10;
	velocity.y = 10;
	maxVelocity.x = 40;
	maxVelocity.y = 40;
	objectType = PLAYER;
	faceDirState = FD_RIGHT;
	initAnimation();
}

void Player::initAnimation()
{
	chasisIdle1Tex.loadFromFile("gfx/tank idle.png");
	setTexture(&chasisIdle1Tex);

	idleAnimation.addFrame(sf::IntRect(0, 0, 64, 64));
	idleAnimation.addFrame(sf::IntRect(64, 0, 64, 64));
	idleAnimation.addFrame(sf::IntRect(128, 0, 64, 64));
	idleAnimation.addFrame(sf::IntRect(192, 0, 64, 64));
	idleAnimation.addFrame(sf::IntRect(256, 0, 64, 64));
	idleAnimation.addFrame(sf::IntRect(320, 0, 64, 64));
	idleAnimation.addFrame(sf::IntRect(384, 0, 64, 64));
	idleAnimation.addFrame(sf::IntRect(448, 0, 64, 64));
	idleAnimation.addFrame(sf::IntRect(512, 0, 64, 64));
	idleAnimation.setFrameSpeed(1.f / 18.f);
	idleAnimation.setOriginOffset(sf::Vector2f(0, 0));
	idleAnimation.setSpriteSize(sf::Vector2f(64, 64));
	idleAnimation.setVisibleSpriteSize(sf::Vector2f(64, 64));

	chasisAnimation = &idleAnimation;

	setSize(chasisAnimation->getSpriteSize());
	setOrigin(chasisAnimation->getOriginOffset().x + (chasisAnimation->getVisibleSpriteSize().x / 2),
		chasisAnimation->getOriginOffset().y + (chasisAnimation->getVisibleSpriteSize().y / 2));

	setTextureRect(chasisAnimation->getCurrentFrame());
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
	playerShape.SetAsBox((idleAnimation.getSpriteSize().x / 2) / box2dScale, (idleAnimation.getSpriteSize().y / 2) / box2dScale);

	//create fixture
	b2FixtureDef playerFixtureDef;
	playerFixtureDef.shape = &playerShape;
	playerFixtureDef.density = 0.5;
	playerFixtureDef.friction = 1;
	
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


	
	//float force = 0;
	

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

	playerBody->ApplyForceToCenter(((gravForce * 3) * gravity), true);

	if (input->isKeyDown(sf::Keyboard::Space))
	{
		playerBody->ApplyForceToCenter((velocity.y * 100) * gravity, true);
	}

	/*
	if (vel.y > 0.1)
	{
		jumpState = JS_FALLING;
	}
	if (vel.y < -0.1)
	{
		jumpState = JS_JUMPING;
	}
	if (vel.y >= -0.1 && vel.y <= 0.1 && jumpState == JS_FALLING)
	{
		jumpState = JS_GROUNDED;
	}

	if (in->isKeyDown(sf::Keyboard::Space))
	{
 		if (jumpState == JS_GROUNDED)
		{
			float impulse = playerBody->GetMass() * -30;
			playerBody->ApplyLinearImpulse(b2Vec2(0, impulse), playerBody->GetWorldCenter(), true);
		}
	}*/
}

void Player::animatePlayer(float dt)
{
	setTextureRect(chasisAnimation->getCurrentFrame());

	setSize(chasisAnimation->getSpriteSize());
	setOrigin(chasisAnimation->getOriginOffset().x + (chasisAnimation->getVisibleSpriteSize().x / 2),
		chasisAnimation->getOriginOffset().y + (chasisAnimation->getVisibleSpriteSize().y / 2));
	   
	if (faceDirState == FD_LEFT)
		chasisAnimation->setFlipped(true);
	if (faceDirState == FD_RIGHT)
		chasisAnimation->setFlipped(false);


	if (moveState == MS_STOP)
	{
		chasisAnimation = &idleAnimation;
	}
	if (moveState == MS_LEFT)
	{
		//currentAnimation = &runAnimation;
	}
	if (moveState == MS_RIGHT)
	{
		//currentAnimation = &runAnimation;
	}


	
	/*
	if (jumpState == JS_JUMPING)
	{
		currentAnimation = &jumpAnimation;
		if (moveState == MS_LEFT)
			currentAnimation->setFlipped(true);
		if (moveState == MS_RIGHT)
			currentAnimation->setFlipped(false);
	}
	if (jumpState == JS_FALLING)
	{
		currentAnimation = &fallAnimation;
		if (moveState == MS_LEFT)
		if (moveState == MS_RIGHT)
			currentAnimation->setFlipped(false);
 		jumpAnimation.reset();
	}*/


	chasisAnimation->animate(dt);
}

void Player::render(sf::RenderWindow* window)
{

	//window->draw();
}