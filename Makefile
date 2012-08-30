#
#   Makefile
#
#   Copyright 2007, 2008 Lancer-X/ASCEAI
#
#   This file is part of Meritous.
#
#   Meritous is free software: you can redistribute it and/or modify
#   it under the terms of the GNU General Public License as published by
#   the Free Software Foundation, either version 3 of the License, or
#   (at your option) any later version.
#
#   Meritous is distributed in the hope that it will be useful,
#   but WITHOUT ANY WARRANTY; without even the implied warranty of
#   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#   GNU General Public License for more details.
#
#   You should have received a copy of the GNU General Public License
#   along with Meritous.  If not, see <http://www.gnu.org/licenses/>.
#
LDFLAGS = `sdl-config --libs` -lSDL_image -lSDL_mixer -lz `xml2-config --cflags --libs`
CCFLAGS = -O2 -Wall `sdl-config --cflags` -g `xml2-config --cflags --libs`
#
OBJS = 	src/main.o src/characters.o src/map.o 
#
default:	ginebras

%.o:		%.c
		gcc -c -o $@ $? ${CCFLAGS}

ginebras:	${OBJS}
		gcc -o $@ $+ ${LDFLAGS}

clean:		
		rm ${OBJS} ginebras

