hdrdir = hdr
objdir = obj
srcdir = src

VPATH = $(hdrdir):$(objdir):$(srcdir)

objfiles = $(objdir)/main.o $(objdir)/stdin_helpers.o 

main: main.o stdin_helpers.o
	gcc $(objfiles) -o main

main.o: main.c stdin_helpers.h
	gcc -c $(srcdir)/main.c -I./$(hdrdir) -o $(objdir)/main.o

stdin_helpers.o: stdin_helpers.c
	gcc -c $(srcdir)/stdin_helpers.c -I./$(hdrdir) -o $(objdir)/stdin_helpers.o

clean:
	rm $(objdir)/*  > /dev/null 2>&1 || echo "No files to remove"