PRGNAME = odflog

OBJS = logdata.o unarchiver.o versionparser.o main.o
INCLUDES = $(shell pkg-config --cflags minizip tinyxml2)
LIBS = $(shell pkg-config --libs minizip tinyxml2)
CXXFLAGS ?= -Wall

DESTDIR=
PREFIX=/usr/local
BINDIR=$(PREFIX)/bin

.PHONY: all
all: $(PRGNAME)

%.o: %.cpp
	$(CXX) $(CXXEXTRA) $(CXXFLAGS) -c $(DEFINES) $(INCLUDES) $<

$(PRGNAME): $(OBJS)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) $(OBJS) $(LIBS) $(LIBDIRS) -o $(PRGNAME)

install: $(PRGNAME)
	install -D -m 755 $(PRGNAME) $(DESTDIR)$(BINDIR)/$(PRGNAME)

clean:
	rm -f $(PRGNAME)
	rm -f *.o
