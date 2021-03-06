/* Copyright (C) 2012 Jauria Studios
 *
 * Sons of Battle is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * Sons of Battle is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Sons of battle. if not, see <http://www.gnu.org/licenses/>.
 */

#ifndef _MENU_H_
#define _MENU_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CB  4

/**********************************************************
 *** STRUCTS
 **********************************************************/
typedef struct Menu{
	char **root;
	int	 *endBranch;
	char ***subMenus;
	int  numSubMenus;
	int  position;
	int  numRows;
	int  *numRowsSubMenu;
	int  countSubMenus;
	
	char **actualMenu;
	int actualMenuRows;
	
	char **previusMenu;
	int previusMenuRows;
	int previusPosition;

	int isRoot;

	int visible;

	int colorRow;

    // Callbacks
    int (**MenuRootCallBacks)(void *data);
    int (***MenuSubCallBacks)(void *data);

    // Data callbacks
    void **menuRootData;
    void ***menuSubData;

	// Back callback
	int (*MenuBack)(void *data);
	void *menuBackData;

} Menu;

/**********************************************************
 *** METHODS
 **********************************************************/
extern Menu* MenuConstructor(char **root, int numRows, int *endBranch, int numSubMenus, int (**handler)(void*), void **data);
extern int	 MenuAddSubMenu(Menu *this, char **subMenu, int numRows, int (**handler)(void*), void **data);
extern void  MenuDestructor(Menu *this);
extern int 	 MenuOk(Menu *this);
extern int	 MenuBack(Menu *this);
extern int 	 MenuUp(Menu *this);
extern int	 MenuDown(Menu *this);
extern void  MenuClose(Menu *this);

#endif // _MENU_H_
