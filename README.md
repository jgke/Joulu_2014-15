putkijuoksu
===========

putkijuoksu is a dynamic dungeon generator.

compiling
=========

        $ make -j4

depends on:
* ncurses
* c++ compiler

running
=======

        $ ./putkijuoksu

Use ./libtest to run tests against the library.


documentation
=============

        $ make doc

After compilation, documentation is located at doc/*.pdf, and doxygen output
is located at doc/html/index.html.

depends on:
* texi2pdf
* doxygen

usage
=====
| Key        | Action                   |
|------------|--------------------------|
| Arrow keys | move around              |
| q          | quit                     |
| h          | turn full vision on/off  |
| l          | turn local vision on/off |
| g          | go to start              |
