# expr2cf
Converts a simple mathematical expression to a continued fraction sequence

### Requirements

* a C++ compiler which supports **C++11**
* [the GNU Multiple Precision Arithmetic Library](https://gmplib.org/)
* the [rational C++ template class](https://github.com/velnias75/rational)

### Usage/examples

* to evaluate an expression:
  `echo "2 + 0.8031975" | expr2cf` => `[2, 1, 4, 12, 3, 4, 2, 1, 1, 1, 1, 2, 1, 1, 5]`

* to get an approximated fraction of pi (from 18 decimal digits):
  `echo "scale=18; 4*a(1)" | BC_LINE_LENGTH=0 bc -l | src/expr2cf | src/cf2expr`
  => `14308127635/4554418479`

* to get an approximated fraction of the golden ratio (Phi):
  `echo "[1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1]" | src/cf2expr`
  => `6765/4181`
 
