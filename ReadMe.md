# Glib resource compiler example using cmake

I couldn't find any working examples of this so I thought it might be useful to
create one.

This example uses glib-compile-resources to create a C source file which is then
compiled and linked into the main program. The program reads the resource (which
is just a short text file) and prints it to stdout.