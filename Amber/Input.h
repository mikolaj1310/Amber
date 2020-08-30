#pragma once
class Input
{
private:
	//Structure to represent mouse
	struct Mouse
	{
		int x, y;
		bool left;
		bool right;
		int scroll = 0;
	};

public:
	void setKeyDown(int key);
	void setKeyUp(int key);
	bool isKeyDown(int key);

	void setMouseX(int lx);
	void setMouseY(int ly);
	void setMousePosition(int lx, int ly);
	int getMouseX();
	int getMouseY();
	void setMouseLeftDown(bool down);
	bool isMouseLeftDown();
	void setMouseRightDown(bool down);
	bool isMouseRightDown();

	void incrementScroll(float num) { mouse.scroll -= (num * 15);};
	void setScroll(float num) { mouse.scroll = num; };
	int getScroll() { return mouse.scroll;};

private:

	bool keys[256]{ false };
	Mouse mouse;
};