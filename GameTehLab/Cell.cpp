#include "Cell.h"

Cell::Cell()
{
	value = -1;
	changed = false;
}

int Cell::Put(Player& _Player)
{
	if (changed)
	{
		return 1;
	}
	value = _Player._SIDE;
	changed = true;
	return 0;
}

void Cell::Restart()
{
	value = -1;
	changed = false;
}
