/*
 * Emad In Mindjail
 *   Based on a true story.
 * Copyright (C) Nick Moffitt et al
 * Emad is a registered Emad of Emad
 * This program is GPL'd
 */

#include <panel.h>
#include <ncurses.h>
#include <string.h>

#include "emads.h"

void bordermad(emad_struct *self)
{
    int max_x, max_y;

    max_x = COLS - self->width - 1;
    max_y = LINES - self->height - 1;

    if(self->x < 1) {
	self->borderalert(self);
	self->x = 1;
    }
    if(self->y < 1) {
	self->borderalert(self);
	self->y = 1;
    }
    if(self->x > max_x) {
	self->borderalert(self);
	self->x = max_x;
    }
    if(self->y > max_y) {
	self->borderalert(self);
	self->y = max_y;
    }

    return;
}

void walkmad(emad_struct *self, int x, int y)
{

    self->x += x;
    self->y += y;

    self->bounds(self);

    move_panel(self->panel, self->y, self->x);

    update_panels();
    return;
}

void changemad(emad_struct *self, ...)
{
    va_list ap;
    int i;
    char *row;

    va_start(ap, self);
    for(i=0; i < self->height; i++) {
	row = va_arg(ap, char*);
	if(row != NULL) {
	    if(self->sprite[i] != NULL) 
		free(self->sprite[i]);
	    self->sprite[i] = strdup(row);
	    mvwaddstr(self->window, i, 0, self->sprite[i]);
	}
    }

    update_panels();
    return;
}

void resizemad(emad_struct *self, int w, int h)
{
    int i;

    wclear(self->window);  
    wnoutrefresh(self->window);

    wresize(self->window, h, w);
    replace_panel(self->panel, self->window);
    self->sprite = (char **)realloc(self->sprite, h * sizeof(char*));
    for(i=self->height; i<h; i++) 
	self->sprite[i] = NULL;
    self->width = w;
    self->height = h;
    self->walk(self, 0, 0); /* force any redraw errors to the surface */
    update_panels();
    return;
}

void defaultalert(emad_struct *self)
{
    return;
}

void del_emad(emad_struct *self)
{
    int i;
    for(i = 0; i < self->height; i++) {
	if(self->sprite[i]) {
	    free(self->sprite[i]);
	}
    }
    free(self->sprite);
    del_panel(self->panel);
    delwin(self->window);
    free(self);
    return;
}

void animemad(emad_struct *self)
{
    static int i;
    char *eyes[] = { "(..)", "(.o)", "(oO)", "(Oo)", "(o.)" };
    char *legs[] = { " /\\ ", " |\\ ", " || ", " /| "};

    i++;
    self->change(self, NULL, eyes[i % 5], NULL, legs[i % 4]);
    return;
}


emad_struct* new_emad(void)
{
    int i;
    /* initialize storage */
    emad_struct *self;
    self = (emad_struct *) malloc(sizeof(emad_struct));

    /* initialize methods */
    self->walk = walkmad;
    self->change = changemad;
    self->resize = resizemad;
    self->bounds = bordermad;
    self->borderalert = defaultalert;
    self->destruct = del_emad;
    self->animate = animemad;

    self->height = 4;
    self->width = 4;
    self->x = 1;
    self->y = 1;

    self->sprite = (char **)malloc(self->height * sizeof(char*));
    for(i=0; i < self->height; i++) 
	self->sprite[i] = NULL;
    
    /* curses froofergee */
    self->window = newwin(self->height, self->width, self->x, self->y);
    self->panel = new_panel(self->window);

    /* default sprite */
    self->change(self, "\\||/",
		 	"(..)",
			"-||-",
			" /\\ "); 

    show_panel(self->panel);
    update_panels();

    return self;
}

