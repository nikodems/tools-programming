#pragma once

struct InputCommands
{
	bool forward;
	bool back;
	bool right;
	bool left;
	bool up;
	bool down;
	bool rotRight;
	bool rotLeft;
	bool rotUp;
	bool rotDown;
	bool goTo;
	bool lctrl;

	int mouse_X;
	int mouse_Y;
	bool mouse_LB_Down;
};
