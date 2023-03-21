#include "OtherObject.h"

Object::Object() {
	obj_frame = 0;
	obj_xpos = 0;
	obj_ypos = 0;
	obj_frame_h = 0;
	obj_frame_w = 0;
	rect.x = 0;
	rect.y = 0;
		
}

Object::~Object()
{
}

bool Object::Load_object(string path, SDL_Renderer* grenderer)
{
	bool res = BaseObject::Load_Img(path, grenderer);
	if (res) {
		obj_frame_w = rect.w / 7;
		obj_frame_h = rect.h;
	}
	if (obj_frame_w > 0 && obj_frame_h > 0)
	{
		for (int i = 0; i < 7; i++)
		{
			obj_frame_clip[i].x = i * obj_frame_w;
			obj_frame_clip[i].y = 0;
			obj_frame_clip[i].w = obj_frame_w;
			obj_frame_clip[i].h = obj_frame_h;
		}
	}
	return res;
}
void Object::obj_show(string path, SDL_Renderer* grenderer)
{
	Load_object(path, grenderer);

	SDL_Rect* currentclip = &obj_frame_clip[obj_frame/10];
	SDL_Rect renderQuad = { rect.x,rect.y,obj_frame_w,obj_frame_h };
	SDL_RenderCopy(grenderer, p_object, currentclip, &renderQuad);
	

}

void Object::cycle_obj() {
	
		++obj_frame;
		if (obj_frame / 7 >= 7)obj_frame = 0;
		
}



