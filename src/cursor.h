#ifndef _CURSOR_H_
#define _CURSOR_H_

#include "SDL.h"
#include "SDL_image.h"
#include "gameUtilities.h"

typedef struct Cursor{

	SDL_Surface* sprite;
	SDL_Rect	 rcSrc;
	SDL_Rect     rcDest; 

} Cursor;

extern Cursor* CursorConstructor(int x0, int y0);
extern void CursorDestructor(Cursor *this);
extern void CursorDraw(Cursor* cursor, SDL_Surface* screen);
extern void CursorMove(Cursor* cursor, Orientation orientation);

#endif // _CURSOR_H_
