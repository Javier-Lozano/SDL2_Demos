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
all: Starfield

debug: OPT += -g
debug: Starfield

Starfield: SRC += starfield/starfield.c common/math.c common/vector.c common/texture.c common/star.c
Starfield:
	$(CC) $(OPT) $(SRC) -o $(PREFIX)$@ $(LINK)