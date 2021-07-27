High Frequency FIX Parser
C++ library for high frequency messaging with the Financial Information Exchange (FIX) protocol.

https://jamesdbrock.github.io/hffix/index.html

Introduction
The High Frequency FIX Parser library is an open source implementation of tagvalue FIX (classic FIX) intended for use by developers of high frequency, low latency financial software. The purpose of the library is to do fast, efficient encoding and decoding of FIX in place, at the location of the I/O buffer. The library does not use intermediate message objects, and it does no memory allocation on the free store (the “heap”).

hffix library is not certified by any industry-leading committees. It is not an “engine.” It is not an “adaptor.” It has no threading, no I/O, no object-oriented subtyping. It is just a superfast parser and serializer in plain modern generic-iterator-style C++98.
