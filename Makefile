CC = gcc

SPECS_FILE = $(abspath libc/install/lib/picolibc.specs)
SPECS_FLAG = --specs=$(SPECS_FILE)

CFLAGS = -Wall -Wextra -fno-stack-protector -fno-stack-check -fno-lto \
         -m64 -march=x86-64 -mno-80387 -mno-mmx -mno-sse -mno-sse2 -mno-red-zone \
         -fPIE $(SPECS_FLAG)

LDFLAGS = -static -pie -Wl,-z,text -Wl,-z,max-page-size=0x1000 \
          -nostdlib -Llibc/install/lib

LDLIBS = -lc -lgcc

SYS_OBJS = sys/crt0.o sys/syscalls.o sys/stubs.o
APP_OBJS = src/main.o

TARGET = app.elf

all: $(TARGET)

sys/%.o: sys/%.S
	$(CC) $(CFLAGS) -c $< -o $@

sys/%.o: sys/%.c
	$(CC) $(CFLAGS) -c $< -o $@

src/%.o: src/%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(TARGET): $(SYS_OBJS) $(APP_OBJS)
	$(CC) $(LDFLAGS) sys/crt0.o src/main.o sys/stubs.o sys/syscalls.o $(LDLIBS) -o $(TARGET)

clean:
	rm -f sys/*.o src/*.o *.elf