lib_LTLIBRARIES = libgmp_rational.la
bin_PROGRAMS = expr2cf cf2expr rd2frac expr2rd

noinst_HEADERS = libgmp_rational.h

libgmp_rational_la_CXXFLAGS = -fexceptions -ffunction-sections -fdata-sections $(RATIONAL_CFLAGS) \
	-fvisibility-inlines-hidden
libgmp_rational_la_CPPFLAGS = -D_GLIBCXX_VISIBILITY=0
libgmp_rational_la_SOURCES = libgmp_rational.cpp
libgmp_rational_la_LIBADD = $(RATIONAL_LIBS)

expr2cf_CXXFLAGS = -fexceptions -ffunction-sections -fdata-sections $(RATIONAL_CFLAGS)
expr2cf_SOURCES = expr2cf.cpp
expr2cf_LDFLAGS = -Wl,--gc-sections -Wl,--as-needed
expr2cf_LDADD = libgmp_rational.la $(RATIONAL_LIBS)

cf2expr_CXXFLAGS = -fexceptions -ffunction-sections -fdata-sections $(RATIONAL_CFLAGS)
cf2expr_SOURCES = cf2expr.cpp
cf2expr_LDFLAGS = -Wl,--gc-sections -Wl,--as-needed
cf2expr_LDADD = libgmp_rational.la $(RATIONAL_LIBS)

rd2frac_CXXFLAGS = -fexceptions -ffunction-sections -fdata-sections $(RATIONAL_CFLAGS)
rd2frac_SOURCES = rd2frac.cpp
rd2frac_LDFLAGS = -Wl,--gc-sections -Wl,--as-needed
rd2frac_LDADD = libgmp_rational.la $(RATIONAL_LIBS)

expr2rd_CXXFLAGS = -fexceptions -ffunction-sections -fdata-sections $(RATIONAL_CFLAGS)
expr2rd_SOURCES = expr2rd.cpp
expr2rd_LDFLAGS = -Wl,--gc-sections -Wl,--as-needed
expr2rd_LDADD = libgmp_rational.la $(RATIONAL_LIBS)
