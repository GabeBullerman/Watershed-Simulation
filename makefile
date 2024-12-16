CC = gcc
CFLAGS = -Wall -Wextra -std=c99
LDFLAGS = -lm -Wl,-e,mainCRTStartup

# Source files
SRCS = parta.c util.c bmp.c pointcloud.c

# Object files for stat1
OBJS_STAT1 = parta_stat1.o util.o bmp.o pointcloud.o

# Object files for display
OBJS_DISPLAY = parta_display.o util.o bmp.o pointcloud.o

# Executable names
EXEC_STAT1 = stat1
EXEC_DISPLAY = display

# Default target
all: $(EXEC_STAT1) $(EXEC_DISPLAY)

# Link the stat1 executable
$(EXEC_STAT1): $(OBJS_STAT1)
	$(CC) $(CFLAGS) -o $@ $(OBJS_STAT1) $(LDFLAGS)

# Link the display executable
$(EXEC_DISPLAY): $(OBJS_DISPLAY)
	$(CC) $(CFLAGS) -o $@ $(OBJS_DISPLAY) $(LDFLAGS)

# Compile source files to object files for stat1
parta_stat1.o: parta.c
	$(CC) $(CFLAGS) -DMAIN_STAT1 -c $< -o $@

# Compile source files to object files for display
parta_display.o: parta.c
	$(CC) $(CFLAGS) -DMAIN_DISPLAY -c $< -o $@

# Compile other source files to object files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@


# Clean up build files
clean:
	rm -f $(OBJS_STAT1) $(OBJS_DISPLAY) $(EXEC_STAT1) $(EXEC_DISPLAY) out.gif