putkijuoksu
===========

putkijuoksu is a dynamic dungeon generator.

compiling
=========

        $ make -j4

depends on:
* gl
* glu
* c++ compiler

running
=======

        $ ./putkijuoksu

Use ./libtest to run tests against the library.


documentation
=============

        $ make doc

After compilation, documentation is located at doc/*.pdf. Doxygen output is
located at doc/doxygen/index.html, and test coverage reports are at
doc/coverage/index.html.

depends on:
* texi2pdf
* doxygen
* gcov
* lcov

usage
=====
| Key                      | Action               |
|--------------------------|----------------------|
| wasd                     | move around          |
| left arrow / right arrow | look around          |
| c                        | toggle flying vision |
| q                        | quit                 |
