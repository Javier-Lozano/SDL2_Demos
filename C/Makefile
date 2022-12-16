# #####
# Autor: Javier Lozano
# Descripción: C SDL Demos Makefile
# #####

# Variables
CC		= gcc
SRC		=
OPT		= -Wall -Werror
LINK	= -lSDL2
PREFIX	= Demo_SDL2_

all: OPT += -O2
all: Starfield Waves Box_Collision

debug: Starfield-Debug Waves-Debug Box_Collision-Debug 

Starfield: SRC = starfield/starfield.c common/demo.c common/math.c common/vector.c common/texture.c common/star.c
Starfield:
	$(CC) $(OPT) $(SRC) -o $(PREFIX)$@ $(LINK)

Starfield-Debug: OPT += -g
Starfield-Debug: Starfield

Waves: SRC =  waves/waves.c common/demo.c common/math.c common/vector.c common/texture.c
Waves:
	$(CC) $(OPT) $(SRC) -o $(PREFIX)$@ $(LINK)

Waves-Debug: OPT += -g
Waves-Debug: Waves

Box_Collision: SRC = box_collision/box_collision.c common/demo.c
Box_Collision:
	$(CC) $(OPT) $(SRC) -o $(PREFIX)$@ $(LINK)

Box_Collision-Debug: OPT += -g
Box_Collision-Debug: Box_Collision
