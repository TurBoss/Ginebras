#include "area.h"

Area* AreaConstructor(int x0, int y0, int radius)
{
	// Variable definition section
	Area* this;
	char areaName[75] = "data/Peana";	
	char radiusChar[5];

	// Alloc memory
	if(!(this = (Area *)malloc(sizeof(Area)))){
		printf("ERROR area: couldn't alloc memory\n");
		return NULL;
	}
	
	// Set radius
	this->radius = radius;
	
	sprintf(radiusChar, "%d", radius);
	strcat(areaName, radiusChar);
	strcat(areaName, ".png");

	// Load sprites image
	if (!(this->sprite = loadImage(areaName))){
		printf("ERROR area: couldn't load %s image\n", areaName);
		return NULL;		
	}
	
	// Load tile sprite for smart draw
	if (!(this->tile = loadImage("data/Peana.png"))){
		printf("ERROR area: couldn't load tile\n");
		return NULL;		
	}

	// Set sprite initial position
	this->rcDest.x = x0 - ((radius-1)*32+16);
	this->rcDest.y = y0 - ((radius-1)*32);
	
	return this;
}

void AreaDestructor(Area *this)
{
	// Free character image
	SDL_FreeSurface(this->sprite);
	SDL_FreeSurface(this->tile);

	// Free character
	free(this);
}

void AreaDraw(Area *this, SDL_Surface *screen, Map *map)
{
	SDL_BlitSurface(this->sprite, NULL, map->surfaceBack, &this->rcDest);	
}

void AreaSetPosition(Area *this, int x, int y)
{
	this->rcDest.x = x - ((this->radius-1)*32+16);
	this->rcDest.y = y - ((this->radius-1)*32);
}

void AreaSmartDraw(Area *this, Map *map, Cursor *cursor)
{
	int i, j;
	int x, y;
	SDL_Rect rcDest;	

	// Get area position 
	GetCoor(this->rcDest.x + 16, this->rcDest.y + 16, &x, &y);
	
	//printf("x: %d, y: %d, sideL: %d\n", x, y, cursor->sideLength);
		
	for(i = 0; i < cursor->sideLength; i++){
		for(j = 0; j < cursor->sideLength; j++){
			if(cursor->collisionArea[i][j] && !map->collisions[y+i][x+j] && !map->charPosition[y+i][x+j]){
				rcDest.x = (x+j) * map->tileWidth;
				rcDest.y = (y+i) * map->tileHeight;
				SDL_BlitSurface(this->tile, NULL, map->surfaceBack, &rcDest);	
			}
		}
	}
}
