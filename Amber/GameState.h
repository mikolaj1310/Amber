#pragma once

enum class State { MENU, LEVEL };

class GameState
{
public:
	void setCurrentState(State s);
	State getCurrentState();

	enum GState {
		MENU, LEVEL
	};

protected:
	State currentState;
};