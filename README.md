# SolarSystemCalculator
Solar System Calculator

Example program in C and BASIC that exercised floating-point to
compute scaled model of the eight-planets in the solar system.

This is just an interesting problem that includes a fairly
legit excuse at using floating point.

But the real point of the exercise is to explore compilers
that implement support for this float type.

VBC was a compiler used to produce the 6502 Commodore PET compatible
build of the C program.

The project started with the idea of trying to invoke floating
point calls in the existing BASIC ROM (since doing so should
save code space), but setting up the call (and interpreting the result)
proved to be difficult.

See the discussion here:
https://www.lemon64.com/forum/viewtopic.php?t=77702
