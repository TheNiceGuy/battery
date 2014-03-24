CFLAGS=-W -Wall -pedantic
LDFLAGS=
EXEC=battery
BINDIR=/usr/bin

all: $(EXEC)

$(EXEC): mkdir battery.o main.o
	gcc -o bin/$(EXEC) src/battery.o src/main.o $(LDFLAGS)
	rm -rf src/*.o

main.o: src/main.c src/global.h
	gcc -o src/main.o -c src/main.c $(CFLAGS)

battery.o: src/battery.h src/global.h
	gcc -o src/battery.o -c src/battery.c $(CFLAGS)

mkdir:
	mkdir -p bin/

clean:
	rm -rf src/*.o

mrproper:
	rm -rf src/*.o
	rm -rf bin/$(EXEC)

install:
	cp bin/$(EXEC) $(BINDIR)/$(EXEC)

uninstall:
	rm $(BINDIR)/$(EXEC)

