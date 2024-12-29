#pragma once

#include <SFML/Graphics/Drawable.hpp>
#include <entity/Tool.h>

class Mallet : public Tool {

public:
	Mallet();
	void set_position(int x, int y);
};
