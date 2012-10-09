#include "textbox.h"

TTF_Font* loadFont(char* file, int ptsize)
{
	TTF_Font* tmpfont;
	tmpfont = TTF_OpenFont(file, ptsize);
	if (tmpfont == NULL){
		printf("Unable to load font: %s %s \n", file, TTF_GetError());
		// Handle the error here.
	}
	return tmpfont;
}

Textbox *TextboxConstructor(SDL_Surface *screen, int x, int y, int w, int h)
{
	// Variable definition section
	
	Textbox * textbox;
	
	// Alloc map
	textbox = (Textbox *)malloc(sizeof(Textbox));
	
	// initialize sdl ttf
	if (TTF_Init() == -1) {
		printf("Unable to initialize SDL_ttf: %s \n", TTF_GetError());
	
	}
	
	//init fonts
	textbox->font = NULL;
	textbox->fontMono = NULL;

	// Load fonts and images
	TextboxLoad(textbox);

	// define text color
	textbox->textColor.r = 255;
	textbox->textColor.g = 255;
	textbox->textColor.b = 255;
	
	// message to display
	textbox->textMsg = "Atacar";
	
	//Setup the location on the screen to blit to

	// Text position
	textbox->rcDestText.x = 15;
	textbox->rcDestText.y = 20;
	
	// Window Position in px
	textbox->rcDestWindow.x = x;
	textbox->rcDestWindow.y = y;
	// Text position
	textbox->rcDestText.x = textbox->rcDestWindow.x + 15;
	textbox->rcDestText.y = textbox->rcDestWindow.y + 20;
		
	// Window tiles
	textbox->rcSrcTile.x = 0;
	textbox->rcSrcTile.y = 0;
	textbox->rcSrcTile.w = 16;
	textbox->rcSrcTile.h = 16;
	
	// Window size in 16x tilesize
	textbox->boxWidth = w; //min 3
	textbox->boxHeight = h; // min 2

	//create window Test
	TextboxCreateWindow(textbox);

	return textbox;
}

void TextboxLoad(Textbox * textbox)
{
	// load Fonts
	textbox->font = loadFont("data/font/ChronoTrigger.ttf",20);
	textbox->fontMono = loadFont("data/font/ChronoTriggerMonospaced.ttf",30);

	// load Images
	textbox->bgTileset = loadImage("data/windowTileset.png");
}

void TextboxUpdate(Textbox * textbox, int scrollX, int scrollY)
{
	char *tmpMsg;
	tmpMsg = (char *)malloc(sizeof(char)*50);
	
	sprintf(tmpMsg,"X:%d  Y:%d", scrollX, scrollY);
	//printf("%s", tmpMsg);	
	textbox->textMsg = tmpMsg;
}

int TextboxDraw(Textbox * textbox, SDL_Surface* screen)
{
	textbox->message = TTF_RenderText_Solid(textbox->fontMono, textbox->textMsg, textbox->textColor);
	
	if (textbox->message != NULL){ 
		SDL_BlitSurface(textbox->background, NULL, screen, &textbox->rcDestWindow);
		SDL_BlitSurface(textbox->message, NULL, screen, &textbox->rcDestText);
		SDL_FreeSurface(textbox->message);
		return 1;
	}
	else {
		// report error
		return 0;
	}
}

void TextboxCreateWindow(Textbox * textbox)
{
	SDL_Surface* temp = NULL;
	
	//int x = textbox->windowX; 
	//int y = textbox->windowY;
	
	int width = textbox->boxWidth;
	int height = textbox->boxHeight;
	
	int i, j;
	
	temp = SDL_CreateRGBSurface(SDL_SWSURFACE | SDL_SRCALPHA, (width+1)*16, (height+1)*16, 32, 0, 0, 0, 0x000000FF);
	
	textbox->background = SDL_DisplayFormatAlpha(temp);
	
	for (i = 0; i <= width; i++){
		for (j = 0; j <= height; j++){
			if ((i == 0) && (j == 0)){
				textbox->rcSrcTile.x = 0;
				textbox->rcSrcTile.y = 0;
			}
			else if ((i <  width) && (j == 0)){
				textbox->rcSrcTile.x = 16;
				textbox->rcSrcTile.y = 0;
			}
			else if ((i ==  width) && (j == 0)){
				textbox->rcSrcTile.x = 32;
				textbox->rcSrcTile.y = 0;
			}
			else if ((i ==  width) && (j < height)){
				textbox->rcSrcTile.x = 32;
				textbox->rcSrcTile.y = 16;
			}
			else if ((i == 0 ) && (j < height)){
				textbox->rcSrcTile.x = 0;
				textbox->rcSrcTile.y = 16;
			}
			else if ((i == 0 ) && (j == height)){
				textbox->rcSrcTile.x = 0;
				textbox->rcSrcTile.y = 32;
			}
			else if ((i < width ) && (j == height)){
				textbox->rcSrcTile.x = 16;
				textbox->rcSrcTile.y = 32;
			}
			else if ((i == width ) && (j == height)){
				textbox->rcSrcTile.x = 32;
				textbox->rcSrcTile.y = 32;
			}
			else{
				textbox->rcSrcTile.x = 16;
				textbox->rcSrcTile.y = 16;
			}
			textbox->rcDestTile.x = 16*i;
			textbox->rcDestTile.y = 16*j;
			
			// apply tiles to textbox background
			copySurface(textbox->bgTileset, &textbox->rcSrcTile, textbox->background, &textbox->rcDestTile);
		}
	}
}

void TextboxDestructor(Textbox * textbox)
{
	
	//Free the text_surface surface
	SDL_FreeSurface(textbox->message);
	SDL_FreeSurface(textbox->background);
	SDL_FreeSurface(textbox->bgTileset);

	//Close the font that was used
	TTF_CloseFont(textbox->font);
	TTF_Quit();
	SDL_Quit();
}

