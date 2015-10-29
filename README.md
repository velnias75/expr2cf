# expr2cf
Converts a simple mathematical expression to a continued fraction sequence

### Requirements

* a C++ compiler which supports **C++11**
* [the GNU Multiple Precision Arithmetic Library](https://gmplib.org/)
* the [rational C++ template class](https://github.com/velnias75/rational)

### Usage

`echo "2 + 0.8031975" | expr2cf` => `[2, 1, 4, 12, 3, 4, 2, 1, 1, 1, 1, 2, 1, 1, 5]`
