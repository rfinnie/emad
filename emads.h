/*
SPDX-PackageName: emad
SPDX-PackageSupplier: Ryan Finnie <ryan@finnie.org>
SPDX-PackageDownloadLocation: https://codeberg.org/rfinnie/emad
SPDX-FileComment: emad source
SPDX-FileCopyrightText: © 2003 Nick Moffitt <nick@zork.net>
SPDX-FileCopyrightText: © 2003 Atob <atob@zork.net>
SPDX-FileCopyrightText: © 2020 Ryan Finnie <ryan@finnie.org>
SPDX-License-Identifier: GPL-2.0-or-later
*/

#include <panel.h>
#include <curses.h>

/*
 * Emad In Mindjail
 *   Based on a true story.
 * Copyright (C) Nick Moffitt et al
 * Emad is a registered Emad of Emad
 * This program is GPL'd
 */


struct struct_emad {
    wchar_t **sprite;
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
