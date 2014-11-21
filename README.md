# Franko Core [FRK, ₣]
================================
![Franko](https://33.media.tumblr.com/2081874970d82c1ce3517a99cd4b3f2e/tumblr_nfep2lfAPf1u3d47eo1_250.png)
http://www.frankos.org

Copyright (c) 2009-2013 Bitcoin Developers
Copyright (c) 2011-2013 Litecoin Developers
Copyright (c) 2012-2013 Franko Developers

## What is Franko?
----------------
More than just a Crypto Currency. Franko is a new corporate model that promotes financial freedom and global unity for everyone. Non nobis solum, sed omnibus!

 - 30 second transaction times
 - coin creation halves in 22m blocks (~22 years)
 - ~11 million total coins
 - 0.25 coins created per block discovered
 - Dynamic difficulty adjusts every block

For more information, as well as an immediately usable, binary version of
the Franko client sofware, see http://www.frankos.org.

## License
-------

Franko is released under the terms of the MIT license. See `COPYING` for more
information or see http://opensource.org/licenses/MIT.

### Compiling on your native platform
-------------------------------------

#### Linux Quick Compile
-------------------------
git clone -b master-0.9 https://github.com/franko-org/franko.git
cd franko
chmod 777 autogen.sh
./autogen
./configure --disable-tests --disable-debug
make
or make install

  The following are developer notes on how to build Franko on your native platform. They are not complete guides, but include notes on the necessary libraries, compile flags, etc.

  - [OSX Build Notes](doc/build-osx.md)
  - [Unix Build Notes](doc/build-unix.md)
  - [Windows Build Notes](doc/build-msw.md)

### FRK ports
RPC 7913
P2P 7912

### Testing
-------

Testing and code review is the bottleneck for development; we get more pull
requests than we can review and test. Please be patient and help out, and
remember this is a security-critical project where any mistake might cost people
lots of money.

### Automated Testing

Developers are strongly encouraged to write unit tests for new code, and to
submit new unit tests for old code.

Unit tests for the core code are in `src/test/`. To compile and run them:

    cd src; make -f makefile.unix test

Unit tests for the GUI code are in `src/qt/test/`. To compile and run them:

    qmake BITCOIN_QT_TEST=1 -o Makefile.test bitcoin-qt.pro
    make -f Makefile.test
    ./franko-qt_test

![Franko](https://31.media.tumblr.com/dcbb189e5c143d61a5f44496bdb67768/tumblr_nf1wxyA0Wj1u3d47eo1_1280.png)
