# dwm - dynamic window manager
# See LICENSE file for copyright and license details.

include config.mk

SRC = dwm.c
OBJ = ${SRC:.c=.o}

all: options dwm

options:
	@echo dwm build options:
	@echo "CFLAGS   = ${CFLAGS}"
	@echo "LDFLAGS  = ${LDFLAGS}"
	@echo "CC       = ${CC}"

.c.o:
	@echo CC $<
	@${CC} -c ${CFLAGS} $<

${OBJ}: config.h config.mk

dwm: ${OBJ}
	@echo CC -o $@
	@${CC} -o bin/$@ ${OBJ} ${LDFLAGS}
	@mv ${OBJ} bin/${OBJ}

clean:
	@echo cleaning
	@rm -f bin/dwm bin/${OBJ} bin/dwm-${VERSION}.tar.gz

dist: clean
	@echo creating dist tarball
	@mkdir -p bin/dwm-${VERSION}
	@cp -R docs/LICENSE Makefile docs/README config.h config.mk \
		docs/dwm.1 ${SRC} bin/dwm-${VERSION}
	@tar -cf bin/dwm-${VERSION}.tar bin/dwm-${VERSION}
	@gzip bin/dwm-${VERSION}.tar
	@rm -rf bin/dwm-${VERSION}

install: all
	@echo installing executable file to ${DESTDIR}${PREFIX}/bin
	@mkdir -p ${DESTDIR}${PREFIX}/bin
	@cp -f bin/dwm ${DESTDIR}${PREFIX}/bin
	@chmod 755 ${DESTDIR}${PREFIX}/bin/dwm
	@echo installing manual page to ${DESTDIR}${MANPREFIX}/man1
	@mkdir -p ${DESTDIR}${MANPREFIX}/man1
	@sed "s/VERSION/${VERSION}/g" < docs/dwm.1 > ${DESTDIR}${MANPREFIX}/man1/dwm.1
	@chmod 644 ${DESTDIR}${MANPREFIX}/man1/dwm.1

uninstall:
	@echo removing executable file from ${DESTDIR}${PREFIX}/bin
	@rm -f ${DESTDIR}${PREFIX}/bin/dwm
	@echo removing manual page from ${DESTDIR}${MANPREFIX}/man1
	@rm -f ${DESTDIR}${MANPREFIX}/man1/dwm.1

.PHONY: all options clean dist install uninstall
