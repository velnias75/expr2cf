#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.68])
AC_INIT([expr2cf], [0.3], [heiko@rangun.de])
AC_CONFIG_SRCDIR([src])
AC_CONFIG_HEADERS([config.h])
AC_CONFIG_MACRO_DIR([m4])
AM_INIT_AUTOMAKE([foreign dist-xz no-dist-gzip tar-pax no-installinfo no-texinfo.tex])
AM_MAINTAINER_MODE
LT_INIT

# Checks for programs.
AC_PROG_CXX
PKG_PROG_PKG_CONFIG([0.22])
AX_CXX_COMPILE_STDCXX_11([noext], [mandatory])

# Checks for libraries.
PKG_CHECK_MODULES([RATIONAL], [rational >= 2.5])

# Checks for header files.

# Checks for typedefs, structures, and compiler characteristics.

# Checks for library functions.

AC_LANG_PUSH([C++])
AX_APPEND_COMPILE_FLAGS([-finline-functions '--param inline-min-speedup=2' -fexceptions -ffunction-sections -fdata-sections -fno-rtti])
AX_APPEND_LINK_FLAGS([-Wl,--gc-sections -Wl,--as-needed])
AC_LANG_POP([C++])

CPPFLAGS="${CPPFLAGS} -Wno-inline"
AC_SUBST([CPPFLAGS])

AC_OUTPUT([Makefile src/Makefile])
