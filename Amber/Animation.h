#pragma once
#include "SFML\Graphics.hpp"
#include <vector>

class Animation
{
public:
	Animation();

	// Create animation
	void addFrame(sf::IntRect rect);
	void setFrameSpeed(float speed) { animationSpeed = speed; }; // in frames per second
	int getSize();

	// update/reset animation
	void animate(float dt);
	void reset();

	// get current frame of animation
	sf::IntRect getCurrentFrame();

	// Animation controls
	float getFrameSpeed() { return animationSpeed; };
	void setFlipped(bool flip) { flipped = flip; };
	bool getFlipped() { return flipped; };
	void setLooping(bool loop) { isLooping = loop; };
	bool getLooping() { return isLooping; };
	void setPlaying(bool play) { isPlaying = play; };
	bool getPlaying() { return isPlaying; };

	void setOriginOffset(sf::Vector2f ori) { originOffset = ori; };
	sf::Vector2f getOriginOffset() { return originOffset; };
	void setSpriteSize(sf::Vector2f sps) { spriteSize = sps; };
	sf::Vector2f getSpriteSize() { return spriteSize; };
	void setVisibleSpriteSize(sf::Vector2f vsps) { visibleSpriteSize = vsps; };
	sf::Vector2f getVisibleSpriteSize() { return visibleSpriteSize; };

protected:
	sf::Vector2f spriteSize;
	sf::Vector2f visibleSpriteSize;
	sf::Vector2f originOffset;
	std::vector<sf::IntRect>frames;
	sf::IntRect frame;
	int currentFrame;
	float animationSpeed;	// in FPS
	bool flipped;
	bool isLooping;
	bool isPlaying;
	float elapsedTime;
};