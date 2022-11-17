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

debug: OPT += -g
debug: Starfield Waves

Starfield: SRC = starfield/starfield.c common/math.c common/vector.c common/texture.c common/star.c
Starfield:
	$(CC) $(OPT) $(SRC) -o $(PREFIX)$@ $(LINK)

Waves: SRC =  waves/waves.c common/vector.c common/texture.c
Waves:
	$(CC) $(OPT) $(SRC) -o $(PREFIX)$@ $(LINK)