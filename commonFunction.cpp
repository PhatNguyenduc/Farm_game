#include"commonFunction.h"


bool SDLCommonFunction::Checkcollision(const SDL_Rect& object1, const SDL_Rect& object2)
{
	return SDL_HasIntersection(&object1, &object2);
}
