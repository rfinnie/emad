# SPDX-PackageName: emad
# SPDX-PackageSupplier: Ryan Finnie <ryan@finnie.org>
# SPDX-PackageDownloadLocation: https://github.com/rfinnie/emad
# SPDX-FileComment: autoconf source
# SPDX-FileCopyrightText: © 2003 Nick Moffitt <nick@zork.net>
# SPDX-FileCopyrightText: © 2003 Atob <atob@zork.net>
# SPDX-FileCopyrightText: © 2020 Ryan Finnie <ryan@finnie.org>
# SPDX-License-Identifier: GPL-2.0-or-later

AC_INIT([emad],[10.0.11.0.0.0.2])
AC_CONFIG_SRCDIR([emads.h])
AM_INIT_AUTOMAKE
AC_CONFIG_MACRO_DIRS([m4])
AC_CONFIG_HEADERS(config.h)
AC_LANG([C])

AC_PROG_CC
LT_INIT
AC_PROG_INSTALL

PKG_CHECK_MODULES([NCURSESW], [ncursesw], [
                  CFLAGS="$NCURSESW_CFLAGS -DNCURSES_WIDECHAR $CFLAGS"
		  LIBS="$NCURSESW_LIBS $LIBS"
		 ])
AC_CHECK_LIB(panelw,new_panel)

AC_CONFIG_FILES([Makefile])
AC_OUTPUT
