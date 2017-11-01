odflog
======

odflog is a simple command line tool which extracts the stored version log (File -> Versions...) of an ODF file (LibreOffice) and prints them in a "git like" log format. This is meant to be used whenever you have to provide a "log file" for your documents.

Setup
-----

You have to get sure that "minizip" and "tinyxml2" (and the corresponding "dev" packages, if your distribution (Linux Mint, Debian, Ubuntu) uses them) are installed prior compiling. After that you can use "make" to build and "make install" to install:

    make
    sudo make install
