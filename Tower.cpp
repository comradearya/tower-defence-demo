#include "Tower.hpp"

bool Tower::canShoot()
{
	if (reloading == 0)
	{
		reloading = reload_time;
		return true;
	}
	return false;
}
