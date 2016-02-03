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
PKG_CHECK_MODULES([RATIONAL], [rational >= 2.10])

# Checks for header files.

# Checks for typedefs, structures, and compiler characteristics.

# Checks for library functions.

AC_ARG_WITH([boost], [AS_HELP_STRING([--with-boost], [use boost])],
[ AC_LANG_PUSH([C++])
  if test x$with_boost = xyes; then
    AC_CHECK_LIB([boost_system], [main], [
      AC_SUBST([BOOST_SYSTEM_LIBS], [-lboost_system])
      AC_DEFINE([BOOST_POOL_ALLOC], [1], [define to 1 to use boost::pool_allocator])])
  fi
  AC_LANG_POP([C++])
])

AC_ARG_WITH([stxxl], [AS_HELP_STRING([--with-stxxl], [use STXXL])],
[ if test x$with_stxxl = xyes; then
    PKG_CHECK_MODULES([STXXL], [stxxl >= 1.4.1],
      [ AC_DEFINE([HAVE_STXXL], [1], [define to 1 to use STXXL]) ],
      [ PKG_CHECK_MODULES([STXXL], [stxxl_gentoo >= 1.4.1],
        [ AC_DEFINE([HAVE_STXXL], [1], [define to 1 to use STXXL]) ]) ])
  fi
])

AC_LANG_PUSH([C++])
AX_APPEND_COMPILE_FLAGS([-finline-functions '--param inline-min-speedup=2' -fexceptions -ffunction-sections -fdata-sections])
AX_APPEND_LINK_FLAGS([-Wl,--gc-sections -Wl,--as-needed])
AC_LANG_POP([C++])

CPPFLAGS="${CPPFLAGS} -Wno-inline"
AC_SUBST([CPPFLAGS])

AC_OUTPUT([Makefile src/Makefile])
