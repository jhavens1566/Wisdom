CC = gcc
CFLAGS = -std=c99 -s -mwindows
LIBS = -lgdi32
CWISE = wisdom.c wisdom_win.c
WISE = wisdom

all: $(WISE) 
	@echo  $(WISE) has been compiled
	
$(WISE): $(CWISE)
	$(CC) $(CFLAGS) $(CWISE) -o $(WISE) $(LIBS)

clean: 
	$(RM) -f wisdom.exe wisdom
