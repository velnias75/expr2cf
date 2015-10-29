bin_PROGRAMS = expr2cf cf2expr

expr2cf_CXXFLAGS = -fexceptions $(RATIONAL_CFLAGS)
expr2cf_SOURCES = expr2cf.cpp
expr2cf_LDFLAGS = -Wl,--as-needed
expr2cf_LDADD = $(RATIONAL_LIBS)

cf2expr_CXXFLAGS = -fexceptions $(RATIONAL_CFLAGS)
cf2expr_SOURCES = cf2expr.cpp
cf2expr_LDFLAGS = -Wl,--as-needed
cf2expr_LDADD = $(RATIONAL_LIBS)
