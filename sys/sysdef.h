#ifndef __SYSDEF_H
#define __SYSDEF_H

#include <stdint.h>

// IOCTL commands for TTY
#define TTY_IOCTL_CLEAR_SCREEN 0  //input: none
#define TTY_IOCTL_SET_FG_COLOR 1 //input: uint32_t color in 0xRRGGBB format
#define TTY_IOCTL_SET_BG_COLOR 2 //input: uint32_t color in 0xRRGGBB format
#define TTY_IOCTL_SET_CURSOR_POS 3 //input: struct { uint32_t row; uint32_t col; }
#define TTY_IOCTL_GET_CURSOR_POS 4 //output: struct { uint32_t row; uint32_t col; }
#define TTY_IOCTL_GET_LINES 6 //output: uint32_t lines
#define TTY_IOCTL_GET_COLS 7 //output: uint32_t cols
#define TTY_IOCTL_ECHO_ON 20 //input: none
#define TTY_IOCTL_ECHO_OFF 21 //input: none
#define TTY_IOCTL_MAP_FRAMEBUFFER 0x10000
#define TTY_IOCTL_UNMAP_FRAMEBUFFER 0x10001

// IOCTL commands for system control
#define SYSCTL_IOCTL_SHUTDOWN 0x1000
#define SYSCTL_IOCTL_REBOOT 0x1001

// Flags for open
#define O_RDONLY    0x0000
#define O_WRONLY    0x0001
#define O_RDWR      0x0002
#define O_CREAT     0x0040

#include <sys/types.h>

typedef uint64_t off64_t;
typedef int64_t blkcnt64_t;
typedef uint64_t ino64_t;

struct stat {
	dev_t st_dev;
	ino_t st_ino;
	mode_t st_mode;
	nlink_t st_nlink;
	uid_t st_uid;
	gid_t st_gid;
	dev_t st_rdev;
	off_t st_size;
	time_t st_atime;
	time_t st_mtime;
	time_t st_ctime;
	blksize_t st_blksize;
	blkcnt_t st_blocks;
	mode_t st_attr;
}; 

struct stat64 {
	dev_t st_dev;
	ino64_t st_ino;
	mode_t st_mode;
	nlink_t st_nlink;
	uid_t st_uid;
	gid_t st_gid;
	dev_t st_rdev;
	off64_t st_size;
	time_t st_atime;
	time_t st_mtime;
	time_t st_ctime;
	blksize_t st_blksize;
	blkcnt64_t st_blocks;
	mode_t st_attr;
}; 

struct tty_fb_info {
    void* buffer;
    uint32_t width;
    uint32_t height;
    uint32_t pitch;
    uint8_t bpp;
};

struct dirent {
    char name[256];
    uint32_t ino;
};

struct stat {
	dev_t st_dev;
	ino_t st_ino;
	mode_t st_mode;
	nlink_t st_nlink;
	uid_t st_uid;
	gid_t st_gid;
	dev_t st_rdev;
	off_t st_size;
	time_t st_atime;
	time_t st_mtime;
	time_t st_ctime;
	blksize_t st_blksize;
	blkcnt_t st_blocks;
	mode_t st_attr;
}; 

#endif // __SYSDEF_H