bin_PROGRAMS = expr2cf cf2expr rd2frac expr2rd exprpow exprsqrt

expr2cf_CXXFLAGS = $(RATIONAL_CFLAGS)
expr2cf_SOURCES = expr2cf.cpp
expr2cf_LDADD = $(RATIONAL_LIBS)

cf2expr_CXXFLAGS = $(RATIONAL_CFLAGS)
cf2expr_SOURCES = cf2expr.cpp
cf2expr_LDADD = $(RATIONAL_LIBS)

rd2frac_CXXFLAGS = $(RATIONAL_CFLAGS)
rd2frac_SOURCES = rd2frac.cpp
rd2frac_LDADD = $(RATIONAL_LIBS)

expr2rd_CXXFLAGS = $(RATIONAL_CFLAGS) $(STXXL_CFLAGS)
expr2rd_SOURCES = expr2rd.cpp
expr2rd_LDADD = $(RATIONAL_LIBS) $(BOOST_SYSTEM_LIBS) $(STXXL_LIBS)

exprpow_CXXFLAGS = $(RATIONAL_CFLAGS)
exprpow_SOURCES = exprpow.cpp
exprpow_LDADD = $(RATIONAL_LIBS)

exprsqrt_CXXFLAGS = $(RATIONAL_CFLAGS)
exprsqrt_SOURCES = exprsqrt.cpp
exprsqrt_LDADD = $(RATIONAL_LIBS)
