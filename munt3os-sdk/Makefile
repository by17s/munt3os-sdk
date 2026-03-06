CC = gcc

# Путь к нашему локальному файлу конфигурации picolibc
SPECS_FILE = $(abspath libc/install/lib/picolibc.specs)
SPECS_FLAG = --specs=$(SPECS_FILE)

# Твои флаги компилятора (убрали -ffreestanding, добавили спеки)
CFLAGS = -Wall -Wextra -fno-stack-protector -fno-stack-check -fno-lto \
         -m64 -march=x86-64 -mno-80387 -mno-mmx -mno-sse -mno-sse2 -mno-red-zone \
         -fPIE $(SPECS_FLAG)

# Флаги линковщика
# Используем gcc для линковки. -nostartfiles нужен, чтобы gcc не подставлял
# линуксовый crt0, так как у нас есть свой в папке sys/
LDFLAGS = -static -pie -Wl,-z,text -Wl,-z,max-page-size=0x1000 \
          $(SPECS_FLAG) -nostartfiles

# Списки исходников
SYS_OBJS = sys/crt0.o sys/syscalls.o sys/stubs.o
APP_OBJS = src/main.o

TARGET = app.elf

all: $(TARGET)

# Компиляция системных ассемблерных файлов
sys/%.o: sys/%.S
	$(CC) $(CFLAGS) -c $< -o $@

# Компиляция системных Си-файлов
sys/%.o: sys/%.c
	$(CC) $(CFLAGS) -c $< -o $@

# Компиляция кода приложения
src/%.o: src/%.c
	$(CC) $(CFLAGS) -c $< -o $@

# Линковка
# Важно: crt0.o должен идти ПЕРВЫМ в списке, чтобы точка входа _start была в начале
$(TARGET): $(SYS_OBJS) $(APP_OBJS)
	$(CC) $(LDFLAGS) sys/crt0.o src/main.o sys/stubs.o sys/syscalls.o -o $(TARGET)

clean:
	rm -f sys/*.o src/*.o *.elf