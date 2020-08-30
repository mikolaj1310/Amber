#include "LevelHub.h"
#include <string>
LevelHub::LevelHub(sf::RenderWindow* hwnd, Input* in)
{
	window = hwnd;
	input = in;

	window->setFramerateLimit(60);
	b2Vec2 gravity(0.0f, 0.0f);
	world = new b2World(gravity);

	bgTex.loadFromFile("gfx/Backgrounds/TestBackground.png");

	background.setTexture(&bgTex);
	background.setSize(sf::Vector2f(1024, 576));
	background.setPosition(0, 0);
	background.setOrigin(background.getSize().x / 2, background.getSize().y / 2);
	
	playerFollowView.setSize(sf::Vector2f(896, 504));
	playerFollowView.setCenter(sf::Vector2f(playerFollowView.getSize().x / 2, playerFollowView.getSize().y / 2));
	playerFollowView.setViewport(sf::FloatRect(0, 0, 1, 1));

	minimap.setSize(sf::Vector2f(1920, 1080));
	minimap.setCenter(sf::Vector2f(minimap.getSize().x / 2, minimap.getSize().y / 2));
	minimap.setViewport(sf::FloatRect(0.77, 0.02, 0.22, 0.22));
	minimap.zoom(1);

	window->setView(playerFollowView);

	cubeTex.loadFromFile("gfx/cube.png");
	cube.setTexture(&cubeTex);
	cube.setSize(sf::Vector2f(100, 100));
	cube.setOrigin(50, 50);
	cube.setType(CUBE);

	
	world = player.initB2Body(world);

	grndTex.loadFromFile("gfx/Asteroid.png");
	ground.setTexture(&grndTex);
	ground.setSize(sf::Vector2f(2400, 2400));
	ground.setOrigin(ground.getSize().x / 2, ground.getSize().y / 2);
	ground.setType(GROUND);


	font.loadFromFile("font/Benja.otf");

	text.setFont(font);
	text.setCharacterSize(24);
	text.setFillColor(sf::Color::Black);
	text.setPosition(2, 2);

	savedText.setFont(font);
	savedText.setCharacterSize(24);
	savedText.setFillColor(sf::Color::White);
	savedText.setPosition(2, 874);

	input->setMouseLeftDown(false);
	input->setMouseRightDown(false);

	initGround();
	initCube();
}

LevelHub::~LevelHub()
{
}

void LevelHub::initGround()
{
	//create physics body
	b2BodyDef groundBodyDef;
	groundBodyDef.type = b2_staticBody;
	groundBodyDef.position = b2Vec2((playerFollowView.getSize().x / 2) / box2dScale, (1500 + (87 / 2) / 2) / box2dScale);
	
	grndBody = world->CreateBody(&groundBodyDef);

	//create shape for body
	b2CircleShape grndShape;
	grndShape.m_p.Set(0, 0);
	grndShape.m_radius = (ground.getSize().x / 2) / box2dScale;


	//create fixture
	b2FixtureDef grndFixtureDef;
	grndFixtureDef.shape = &grndShape;
	grndFixtureDef.density = 0;

	//create fixture on the rigig body
	grndBody->CreateFixture(&grndFixtureDef);

	//update visual sim
	ground.updateFromSimulation(grndBody);
	player.init(grndBody);
}

void LevelHub::initCube()
{
	//create physics body
	b2BodyDef cubeBodyDef;
	cubeBodyDef.type = b2_dynamicBody;
	cubeBodyDef.position = b2Vec2(600 / box2dScale, 100 / box2dScale);

	cubeBody = world->CreateBody(&cubeBodyDef);

	//create shape for player
	b2PolygonShape cubeShape;
	cubeShape.SetAsBox((cube.getSize().x / 2) / box2dScale, (cube.getSize().y / 2) / box2dScale);

	//create fixture
	b2FixtureDef cubeFixtureDef;
	cubeFixtureDef.shape = &cubeShape;
	cubeFixtureDef.density = 0.3;
	cubeFixtureDef.friction = 0.2;


	//create fixture on the rigig body
	cubeBody->CreateFixture(&cubeFixtureDef);

	//update visual sim
	cube.updateFromSimulation(cubeBody);
}

void LevelHub::update(float dt, int load)
{
	window->setView(playerFollowView);
	playerFollowView.setCenter(player.getPosition());
	playerFollowView.setRotation(player.getRotation() * 180 / pi);
	background.setPosition(player.getPosition());
	background.setRotation(player.getRotation() * 180 / pi);

	b2Vec2 vel = player.getB2Body()->GetLinearVelocity();

	text.setString(
		"p body y: " + std::to_string((int)player.getB2Body()->GetPosition().y) +
		"\np y: " + std::to_string((int)player.getPosition().y) +
		"\nx vel: " + std::to_string((float)vel.x) +
		"\ny vel: " + std::to_string((float)vel.y)
	);
	
	

	player.update(dt);
	player.handleInput(dt, input);
	updateSim();

}

void LevelHub::handleInput(float dt)
{
	if (input->isKeyDown(sf::Keyboard::Tab))
	{
		savedText.setString("Map Saved");
	}
	
}

void LevelHub::updateSim()
{
	float timeStep = 1.0f / 60.0f;

	int32 velocityIterations = 15;
	int32 positionIterations = 6;

	world->Step(timeStep, velocityIterations, positionIterations);

	//update objects
	//player.updateFromSimulation(player.getB2Body(), box2dScale);
	ground.updateFromSimulation(grndBody);
	cube.updateFromSimulation(cubeBody);

	//set up radial gravity for everything
	for (b2Body *body = world->GetBodyList(); body; body = body->GetNext()) 
	{
		float G = 10;

		b2Vec2 gravCenter(ground.getPosition().x / box2dScale, ground.getPosition().y / box2dScale);
		b2Vec2 direction = body->GetWorldCenter() - gravCenter;
		float force = (direction.Length() * direction.Length()) / G;

		direction.Normalize();

		
		if (body->GetUserData() == player.getB2Body())
			player.setGravity(direction, -force); //set gravity then store and reset vel inside player
		else
			body->ApplyForceToCenter(-force * direction, true);

	}

	b2Contact* contact = world->GetContactList();

	int contactCount = world->GetContactCount();

	for (int contactNum = 0; contactNum < contactCount; contactNum++)
	{
		if (contact->IsTouching())
		{
			// get the colliding bodies
			b2Body* bodyA = contact->GetFixtureA()->GetBody();
			b2Body* bodyB = contact->GetFixtureB()->GetBody();

			// DO COLLISION RESPONSE HERE
			Player* player = NULL;
			GameObject* ground = NULL;
			GameObject* cube = NULL;


			GameObject* gameObjectA = NULL;
			GameObject* gameObjectB = NULL;

			gameObjectA = (GameObject*)bodyA->GetUserData();
			gameObjectB = (GameObject*)bodyB->GetUserData();

			if (gameObjectA)
			{
				if (gameObjectA->getType() == PLAYER)
					player = (Player*)gameObjectA;
				if (gameObjectA->getType() == GROUND)
					ground = (GameObject*)gameObjectA;
				if (gameObjectA->getType() == CUBE)
					cube = (GameObject*)gameObjectA;
			}

			if (gameObjectB)
			{
				if (gameObjectB->getType() == PLAYER)
					player = (Player*)gameObjectB;
				if (gameObjectB->getType() == GROUND)
					ground = (GameObject*)gameObjectB;
				if (gameObjectB->getType() == CUBE)
					cube = (GameObject*)gameObjectB;
			}
		}

		// Get next contact point
		contact = contact->GetNext();
	}

}

void LevelHub::render()
{
	beginDraw();
	

	window->setView(playerFollowView);
	window->draw(background);
	window->draw(ground);
	window->draw(cube);
	window->draw(player);
	window->draw(text);
	window->draw(savedText);

	endDraw();
}

void LevelHub::beginDraw()
{
	window->clear(sf::Color::Black);
}

void LevelHub::endDraw()
{
	window->display();
}