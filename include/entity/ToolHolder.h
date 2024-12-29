#pragma once

#include <entity/Tool.h>
#include <entity/Entity.h>

class ToolHolder : protected Entity {
	Tool* held_tool;

public:
	ToolHolder();
};
