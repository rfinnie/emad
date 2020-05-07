#include <panel.h>
#include <curses.h>
#include <wchar.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include <locale.h>

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

void retitle(PANEL *title, const wchar_t* str)
{
    WINDOW *titlewin = panel_window(title);
    wresize(titlewin, 1, wcslen(str));
    replace_panel(title, titlewin);
    move_panel(title, 0, (COLS - wcslen(str)) / 2);
    mvwaddwstr(titlewin, 0, 0, str);
    update_panels();
    return;
}


void newmessage(const wchar_t* str)
{
    WINDOW *messagewin = panel_window(messagepanel);
    wresize(messagewin, 3, wcslen(str) + 2);
    replace_panel(messagepanel, messagewin);
    move_panel(messagepanel, (LINES / 2) - 1, ((COLS - wcslen(str)) / 2) - 1);
    mvwaddwstr(messagewin, 1, 1, str);
    box(messagewin, ACS_VLINE, ACS_HLINE);
    update_panels();

    return;
}

void cybanimatemad(emad_struct *self)
{
    static int i;
    wchar_t *eyes[] = { L"(,o)", L"(;*)", L"(^*)", L"(;*)", L"(,*)" };
    wchar_t *legs[] = { L" /L ", L" |\\, L", L" |L ", L" /L "};

    i++;
    self->change(self, NULL, eyes[i % 5], NULL, legs[i % 4]);
    return;
}

void augment(emad_struct *emad, PANEL *title)
{
    emad->resize(emad, 4, 4);
    emad->change(emad,   L"\\||/",
			  L"(..)",
			  L"-||-",
			  L" /\\ ");
    retitle(title, L" [WE CAN REBUILD HIM] ");
    emad->change(emad, NULL, L"(..)", NULL, NULL);
    doupdate();
    sleep(1);

    retitle(title, L" [WE HAVE THE TECHNOLOGY] ");
    emad->change(emad, NULL, L"(.o)", NULL, NULL);
    doupdate();
    sleep(1);

    retitle(title, L" [WE HAVE THE CABABILITY TO MAKE THE WORLD'S FIRST CYBERNETIC EMAD] ");
    emad->change(emad, NULL, NULL, L"-||=", NULL);
    doupdate();
    sleep(1);

    retitle(title, L" [EMAD WILL BE THAT EMAD] ");
    emad->change(emad, NULL, L"(,o)", NULL, NULL);
    doupdate();
    sleep(1);

    retitle(title, L" [BETTER, STRONGER, FASTER] ");
    emad->change(emad, NULL, NULL, NULL, L" /L ");
    doupdate();
    sleep(1);

    retitle(title, L" [HE IS EMAD, BUT HE HAS A LASER GUN] ");
    emad->change(emad, NULL, L"(,*)", NULL, NULL);
    doupdate();
    sleep(1);

    retitle(title, L" [Cybernetic Emad In Mindjail] ");

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

    newmessage(L"He is trapped, but powerful!");
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
    emad->change(emad,  L"X");
    retitle(title, L" [Xeroc In Mindjail] ");
    emad->animate = xerocimate;
    return;
}

void cownimate(emad_struct *emad)
{
    static int i;
    wchar_t *eyes[] = { L"        (..)",
     	                L"        (.o)",
     	                L"        (oO)",
     	                L"        (Oo)",
     	                L"        (o.)"};

    emad->change(emad, NULL, eyes[++i % 5], NULL, NULL, NULL, NULL);
    return;
}
void cowmad(emad_struct *emad, PANEL *title)
{
    emad->resize(emad, 12, 6);
    emad->change(emad,  L"        (__)",
			L"        (oo)",
			L"  /------\\/ ",
			L" / |    ||  ",
			L"*  /\\---/\\  ",
			L"   ~~   ~~  ");
    retitle(title, L" [Cow In Mindjail] ");
    emad->animate = cownimate;
    return;
}

void cthulimate(emad_struct *emad)
{
    static int i;
    wchar_t *eyes[] = { L"(..)",
     	                L"(.o)",
     	                L"(oO)",
     	                L"(Oo)",
     	                L"(o.)"};

    emad->change(emad, NULL, eyes[++i % 5], NULL, NULL);
    return;
}
void cthulhu(emad_struct *emad, PANEL *title)
{
    emad->resize(emad, 4, 4);
    emad->change(emad, L"\\||/",
     			L"(..)",
     			L"//\\\\",
     			L"|  |");
    retitle(title, L" [Cthulhu In Mindjail] ");
    emad->animate = cthulimate;
    return;
}

void lobstimate(emad_struct *emad)
{
    static int i;
    wchar_t *eyes[] = { L"(\\/)__<O_o>__(|)",
                        L"(|)__<o_O>__(\\/)",
                        L"(\\/)__<O_o>__(|)",
                        L"(|)__<o_O>__(\\/)",
                        L"(\\/)__<O_o>__(|)",
                        L"(|)__<o_O>__(\\/)",
                        L"(\\/)__<O_o>__(|)",
                        L"(\\/)__<-_->__(|)"};
    emad->change(emad, eyes[++i % 8]);
    return;
}
void lobster(emad_struct *emad, PANEL *title)
{
    emad->resize(emad, 16, 1);
    emad->change(emad,  L"(\\/)__<O_o>__(|)");
    retitle(title, L" [Lobster In Mindjail] ");
    emad->animate = lobstimate;
    return;
}

void shrugimate(emad_struct *emad)
{
    static int i;
    wchar_t *eyes[] = { L"\u00af\\(\u00b0_o)/\u00af",
                        L"\u00af\\(o_\u00b0)/\u00af"};
    emad->change(emad, eyes[++i % 2]);
    return;
}
void shrug(emad_struct *emad, PANEL *title)
{
    emad->resize(emad, 9, 1);
    emad->change(emad, L"\u00af\\(\u00b0_o)/\u00af");
    retitle(title, L" [I Guess I'm In Mindjail?] ");
    emad->animate = shrugimate;
    return;
}

void notemad(emad_struct *emad, PANEL *title)
{
    static int i;
    void *notemads[] = { xeroc, cowmad, cthulhu, lobster, shrug };
    void (*f)(emad_struct*, PANEL*);

    f = notemads[++i % 5];
    f(emad, title);

    newmessage(L"NO EMADS!");
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
    wchar_t *str;
    wint_t ch;
    int i, augmented;
    emad_struct *spritemad;
    WINDOW *fieldwin, *emadwin, *messagewin, *titlewin;
    PANEL *field, *emad, *message, *titlepanel;
    void (*oldanim)(emad_struct*); /* to store default emadimation */

    setlocale(LC_ALL, "");
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
    retitle(titlepanel, L" [Emad In Mindjail] ");

    str = L"He is trapped!";
    messagewin = newwin(3, wcslen(str) + 2, (LINES / 2) - 1, ((COLS - wcslen(str)) / 2) - 1 );
    message = new_panel(messagewin);
    box(messagewin, ACS_VLINE, ACS_HLINE);
    mvwaddwstr(messagewin, 1, 1, str);
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
	if(ch == L'q' || ch == L'c')
	    newmessage(L"He is trapped!");

	get_wch(&ch);

	spritemad->animate(spritemad);
	hide_panel(message);
	bottom_panel(message);
	update_panels();
	switch(ch)
	{
	    case KEY_DOWN:
	    case L'j':	spritemad->walk(spritemad, 0, 1);
			break;
	    case KEY_UP:
	    case L'k':	spritemad->walk(spritemad, 0, -1);
			break;
	    case KEY_LEFT:
	    case L'h':	spritemad->walk(spritemad, -1, 0);
			break;
	    case KEY_RIGHT:
	    case L'l':	spritemad->walk(spritemad, 1, 0);
			break;
	    case L'n':	spritemad->walk(spritemad, 1, 1);
			break;
	    case L'b':	spritemad->walk(spritemad, -1, 1);
			break;
	    case L'u':	spritemad->walk(spritemad, 1, -1);
			break;
	    case L'y':	spritemad->walk(spritemad, -1, -1);
			break;
	    case L'q':

			newmessage(L"GET HIM OUT!!!");
			show_panel(messagepanel);
			top_panel(messagepanel);
			update_panels();
			break;
	    case L'c':
			if(augmented) {
			    fire_laser(spritemad);
			} else {
			    augment(spritemad, titlepanel);
			    augmented = 1;
			}
			break;
	    case L'e':
			retitle(titlepanel, L" [Emad In Mindjail] ");
			spritemad->resize(spritemad, 4, 4);
			spritemad->change(spritemad, L"\\||/",
						     L"(..)",
						     L"-||-",
						     L" /\\ ");
			spritemad->animate = oldanim;
			newmessage(L"He is trapped!");
			augmented = 0;
			break;
	    case L's':
	    case L'S':
			notemad(spritemad, titlepanel);
			augmented = 0;
			break;
	    case L'\u2603':
			spritemad->resize(spritemad, 1, 1);
			spritemad->change(spritemad, L"\u2603");
			retitle(titlepanel, L" [Snowmad in Mindjail] ");
			augmented = 0;
			break;

	}
	
	doupdate();
    }

    bailout(0);
}
