#include <panel.h>
#include <ncurses.h>

/*
 * Emad In Mindjail
 *   Based on a true story.
 * Copyright (C) Nick Moffitt et al
 * Emad is a registered Emad of Emad
 * This program is GPL'd
 */


struct struct_emad {
    char **sprite;
    int height, width, x, y;
    PANEL *panel;
    WINDOW *window;
    void (*walk)(struct struct_emad*, int, int);
    void (*change)(struct struct_emad*, ...);
    void (*resize)(struct struct_emad*, int, int);
    void (*bounds)(struct struct_emad*);
    void (*borderalert)(struct struct_emad*);
    void (*destruct)(struct struct_emad*);
    void (*animate)(struct struct_emad*);
};
typedef struct struct_emad emad_struct;

/* function declarations */
emad_struct* new_emad(void);

/* With any luck at all, this is all I'll need, since I have the 
 * prototypes built into the struct here.
 */
