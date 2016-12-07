CC = gcc
CFLAGS = -s -mwindows
LIBS = -lgdi32
CWISE = wisdom.c
WISE = wisdom

all: $(WISE) 
	@echo  $(WISE) has been compiled
	
$(WISE): $(CWISE)
	$(CC) $(CFLAGS) $(CWISE) -o $(WISE) $(LIBS)

clean: 
	$(RM) wisdom.exe
