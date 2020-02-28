#pragma once

#include "Object.h"

class Shell : public Object
{
	Shell(sf::String ImageFile, sf::String ImageFileAttack, int maxFrameX, int maxFrameY, int maxFrameAttackX, int maxFrameAttackY, double x, double y, double speed = 0, double attackTime = 0);
};

