TARGET = keening
LIBS =
CC = gcc
CFLAGS = -g -Wall

# DESTDIR is / by default and can be left empty
DESTDIR=
PREFIX=/usr/local
BDIR=${DESTDIR}/${PREFIX}

.PHONY: default all clean

default: $(TARGET)
all: default

OBJECTS = $(patsubst %.c, %.o, $(wildcard *.c))
HEADERS = $(wildcard *.h)

%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

.PRECIOUS: $(TARGET) $(OBJECTS)

$(TARGET): $(OBJECTS)
	$(CC) $(OBJECTS) -Wall $(LIBS) -o $@

clean:
	rm -f *.o
	rm -f $(TARGET)

install: $(TARGET)
	install -d ${BDIR}/bin/
	install $(TARGET) ${BDIR}/bin/
	install -d ${BDIR}/share/man/man1/
	install -m644 ${TARGET}.1 ${BDIR}/share/man/man1/

uninstall:
	rm -f ${BDIR}/bin/${TARGET}
	rm -f ${BDIR}/share/man/man1/${TARGET}.1
