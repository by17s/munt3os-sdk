#!/bin/bash

# Script to initialize the SDK environment for Munt3OS development.
set -e

OS_NAME="munt3os"
ARCH="x86_64"
CC="gcc"

echo "==== Initializing environment for $OS_NAME ===="

# 1. Create directory structure
echo "[1/3] Creating directory structure..."
mkdir -p libc sys src build

# 2. Clone picolibc
echo "[2/3] Cloning picolibc sources..."
if [ ! -d "libc/src_picolibc" ]; then
    git clone https://github.com/picolibc/picolibc.git libc/src_picolibc

    echo 'SECTIONS { /DISCARD/ : { *(.note.gnu.property) } }' >> libc/src_picolibc/libos/semihost/machine/x86/bios.ld
else
    echo "  picolibc already cloned, skipping."
fi

# 3. Configure and build picolibc
echo "[3/3] Configuring and building picolibc..."
# Create cross-file for meson
cat << EOF > libc/${ARCH}-${OS_NAME}.txt
[binaries]
c = ['${CC}', '-fno-pie', '-no-pie', '-fno-stack-protector', '-fcf-protection=none']
ar = 'ar'
strip = 'strip'

[host_machine]
system = '${OS_NAME}'
cpu_family = '${ARCH}'
cpu = '${ARCH}'
endian = 'little'
EOF

# Build picolibc if not already installed
if [ ! -d "libc/install" ]; then
    meson setup libc/build-${OS_NAME} libc/src_picolibc \
        --cross-file libc/${ARCH}-${OS_NAME}.txt \
        --prefix="$(pwd)/libc/install" \
        -Dspecsdir="$(pwd)/libc/install/lib" \
        -Dposix-console=true \
        -Dtests=false \
        -Dmultilib=false
    
    ninja -C libc/build-${OS_NAME} install
else
    echo "  Library already built in libc/install, skipping."
fi

echo 'SECTIONS { /DISCARD/ : { *(.note.gnu.property) } }' >> libc/src_picolibc/libos/semihost/machine/x86/bios.ld

echo "==== Initialization completed successfully! ===="
echo "Environment is ready. You can now use your Makefile to build (command 'make')."