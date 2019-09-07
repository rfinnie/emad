#include <panel.h>
#include <ncurses.h>
#include <string.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>

/*
 * Emad In Mindjail
 *   Based on a true story.
 * Copyright (C) Nick Moffitt et al
 * Emad is a registered Emad of Emad
 * This program is GPL'd
 */

#include "emads.h"

PANEL *messagepanel;

void heistrapped(emad_struct *self)
{
    show_panel(messagepanel);
    top_panel(messagepanel);
    update_panels();
    return;
}

void retitle(PANEL *title, const char* str)
{
    WINDOW *titlewin = panel_window(title);
    wresize(titlewin, 1, strlen(str));
    replace_panel(title, titlewin);
    move_panel(title, 0, (COLS - strlen(str)) / 2);
    mvwaddstr(titlewin, 0, 0, str);
    update_panels();
    return;
}


void newmessage(const char* str)
{
    WINDOW *messagewin = panel_window(messagepanel);
    wresize(messagewin, 3, strlen(str) + 2);
    replace_panel(messagepanel, messagewin);
    move_panel(messagepanel, (LINES / 2) - 1, ((COLS - strlen(str)) / 2) - 1);
    mvwaddstr(messagewin, 1, 1, str);
    box(messagewin, ACS_VLINE, ACS_HLINE);
    update_panels();

    return;
}

void cybanimatemad(emad_struct *self)
{
    static int i;
    char *eyes[] = { "(,o)", "(;*)", "(^*)", "(;*)", "(,*)" };
    char *legs[] = { " /L ", " |\\, ", " |L ", " /L "};

    i++;
    self->change(self, NULL, eyes[i % 5], NULL, legs[i % 4]);
    return;
}

void augment(emad_struct *emad, PANEL *title)
{
    emad->resize(emad, 4, 4);
    emad->change(emad,   "\\||/",    
			  "(..)", 
			  "-||-", 
			  " /\\ ");
    retitle(title, " [WE CAN REBUILD HIM] ");
    emad->change(emad, NULL, "(..)", NULL, NULL);
    doupdate();
    sleep(1);

    retitle(title, " [WE HAVE THE TECHNOLOGY] ");
    emad->change(emad, NULL, "(.o)", NULL, NULL);
    doupdate();
    sleep(1);

    retitle(title, " [WE HAVE THE CABABILITY TO MAKE THE WORLD'S FIRST CYBERNETIC EMAD] ");
    emad->change(emad, NULL, NULL, "-||=", NULL);
    doupdate();
    sleep(1);

    retitle(title, " [EMAD WILL BE THAT EMAD] ");
    emad->change(emad, NULL, "(,o)", NULL, NULL);
    doupdate();
    sleep(1);

    retitle(title, " [BETTER, STRONGER, FASTER] ");
    emad->change(emad, NULL, NULL, NULL, " /L ");
    doupdate();
    sleep(1);

    retitle(title, " [HE IS EMAD, BUT HE HAS A LASER GUN] ");
    emad->change(emad, NULL, "(,*)", NULL, NULL);
    doupdate();
    sleep(1);

    retitle(title, " [Cybernetic Emad In Mindjail] ");

    emad->animate = cybanimatemad;

    return;

}
void fire_laser(emad_struct *emad)
{
    int x, y;
    WINDOW *w;
    PANEL *p;

    x = emad->x + emad->width;
    y = emad->y + 2;

    w = newwin(1, COLS - x - 1, y, x);
    p = new_panel(w);
    mvwhline(w, 0, 0, ACS_HLINE, COLS);
    show_panel(p);
    top_panel(p);
    
    newmessage("He is trapped, but powerful!");
    show_panel(messagepanel);
    top_panel(messagepanel);

    update_panels();
    doupdate();
    sleep(2);
    
    bottom_panel(p);
    wclear(w); 
    wnoutrefresh(w);
    del_panel(p);
    delwin(w);

    show_panel(messagepanel);
    top_panel(messagepanel);
    update_panels();
    return;
}


void xerocimate(emad_struct *emad)
{
    return;
}
void xeroc(emad_struct *emad, PANEL *title)
{
    emad->resize(emad, 1, 1);
    emad->change(emad,  "X");
    retitle(title, " [Xeroc In Mindjail] ");
    emad->animate = xerocimate;
    return;
}

void cownimate(emad_struct *emad)
{
    static int i;
    char *eyes[] = { "        (..)",
     	             "        (.o)",
     	             "        (oO)",
     	             "        (Oo)",
     	             "        (o.)"};
		     
    emad->change(emad, NULL, eyes[++i % 5], NULL, NULL, NULL, NULL);
    return;
}
void cowmad(emad_struct *emad, PANEL *title)
{
    emad->resize(emad, 12, 6);
    emad->change(emad,  "        (__)",
			"        (oo)",
			"  /------\\/ ",
			" / |    ||  ",
			"*  /\\---/\\  ",
			"   ~~   ~~  ");
    retitle(title, " [Cow In Mindjail] ");
    emad->animate = cownimate;
    return;
}

void cthulimate(emad_struct *emad)
{
    static int i;
    char *eyes[] = { "(..)",
     	             "(.o)",
     	             "(oO)",
     	             "(Oo)",
     	             "(o.)"};
		     
    emad->change(emad, NULL, eyes[++i % 5], NULL, NULL);
    return;
}
void cthulhu(emad_struct *emad, PANEL *title)
{
    emad->resize(emad, 4, 4);
    emad->change(emad, "\\||/",
     			"(..)",
     			"//\\\\",
     			"|  |");
    retitle(title, " [Cthulhu In Mindjail] ");
    emad->animate = cthulimate;
    return;
}

void lobstimate(emad_struct *emad)
{
    static int i;
    char *eyes[] = { "(|)__<o_O>__(\\/)",
                     "(\\/)__<O_o>__(|)",
                     "(|)__<o_O>__(\\/)",
                     "(\\/)__<O_o>__(|)",
                     "(|)__<o_O>__(\\/)",
                     "(\\/)__<O_o>__(|)",
                     "(\\/)__<-_->__(|)",
                     "(\\/)__<O_o>__(|)"};
    emad->change(emad, eyes[++i % 8]);
    return;
}
void lobster(emad_struct *emad, PANEL *title)
{
    emad->resize(emad, 16, 1);
    emad->change(emad,  "(\\/)__<O_o>__(|)");
    retitle(title, " [Lobster In Mindjail] ");
    emad->animate = lobstimate;
    return;
}

void notemad(emad_struct *emad, PANEL *title)
{
    static int i;
    void *notemads[] = { xeroc, cowmad, cthulhu, lobster };
    void (*f)(emad_struct*, PANEL*);

    f = notemads[++i % 4];
    f(emad, title);

    newmessage("NO EMADS!");
    show_panel(messagepanel);
    top_panel(messagepanel);
    update_panels();
    doupdate();
    sleep(2);
    hide_panel(messagepanel);
    bottom_panel(messagepanel);
    update_panels();

    return;
}

/* bailout is called upon signal or progam exit */
void bailout(int sig)
{
        endwin();
	exit(0);
}

void mindjail(int sig)
{
    /* NO ESCAPE */
    show_panel(messagepanel);
    top_panel(messagepanel);
    update_panels();
    doupdate();
    return;
}

int main(int argc, char *argv[])
{
    char ch, *str;
    int i, augmented;
    emad_struct *spritemad;
    WINDOW *fieldwin, *emadwin, *messagewin, *titlewin;
    PANEL *field, *emad, *message, *titlepanel;
    void (*oldanim)(emad_struct*); /* to store default emadimation */

    signal(SIGINT, mindjail);
    initscr();
    keypad(stdscr, TRUE);
    nonl();
    intrflush(stdscr, FALSE);
    noecho();
    cbreak();

    fieldwin = subwin(stdscr, 0, 0, 0, 0);
    field = new_panel(fieldwin);
    box(fieldwin, ACS_VLINE, ACS_HLINE);

    titlewin = newwin(0, 0, 0, 0);
    titlepanel = new_panel(titlewin);
    top_panel(titlepanel);
    retitle(titlepanel, " [Emad In Mindjail] ");

    str = "He is trapped!";
    messagewin = newwin(3, strlen(str) + 2, (LINES / 2) - 1, ((COLS - strlen(str)) / 2) - 1 );
    message = new_panel(messagewin);
    box(messagewin, ACS_VLINE, ACS_HLINE);
    mvwaddstr(messagewin, 1, 1, str);
    bottom_panel(message);
    hide_panel(message);
    messagepanel = message; /* bah, globals... */

    spritemad = new_emad();
    spritemad->borderalert = heistrapped; /* overload alert with our 
					     emad */

    doupdate();

    oldanim = spritemad->animate;
    augmented = 0;

    while(1) {
	if(ch == 'q' || ch == 'c')
	    newmessage("He is trapped!");

	ch = getch();

	spritemad->animate(spritemad);
	hide_panel(message);
	bottom_panel(message);
	update_panels();
	switch(ch)
	{
	    case 2:
	    case 'j':	spritemad->walk(spritemad, 0, 1);
			break;
	    case 3:
	    case 'k':	spritemad->walk(spritemad, 0, -1);
			break;
	    case 4:
	    case 'h':	spritemad->walk(spritemad, -1, 0);
			break;
	    case 5:
	    case 'l':	spritemad->walk(spritemad, 1, 0);
			break;
	    case 'n':	spritemad->walk(spritemad, 1, 1);
			break;
	    case 'b':	spritemad->walk(spritemad, -1, 1);
			break;
	    case 'u':	spritemad->walk(spritemad, 1, -1);
			break;
	    case 'y':	spritemad->walk(spritemad, -1, -1);
			break;
	    case 'q':

			newmessage("GET HIM OUT!!!");
			show_panel(messagepanel);
			top_panel(messagepanel);
			update_panels();
			break;
	    case 'c':
			if(augmented) {
			    fire_laser(spritemad);
			} else {
			    augment(spritemad, titlepanel);
			    augmented = 1;
			}
			break;
	    case 'e':
			retitle(titlepanel, " [Emad In Mindjail] ");
			spritemad->resize(spritemad, 4, 4);
			spritemad->change(spritemad, "\\||/",    
						      "(..)", 
						      "-||-", 
						      " /\\ ");
			spritemad->animate = oldanim;
			newmessage("He is trapped!");
			augmented = 0;
			break;
	    case 's':
	    case 'S':
			notemad(spritemad, titlepanel);
			augmented = 0;
			break;

	}
	
	doupdate();
    }

    bailout(0);
}
