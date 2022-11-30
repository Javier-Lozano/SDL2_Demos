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
all: Starfield Waves

debug: Starfield-Debug Waves-Debug

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
