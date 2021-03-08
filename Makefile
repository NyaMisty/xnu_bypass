SDK = $(shell xcrun --sdk iphoneos --show-sdk-path)
CC = $(shell xcrun --sdk $(SDK) --find clang)
CFLAGS = -isysroot $(SDK) -arch arm64 -Wno-string-plus-int -fno-stack-protector -Wno-deprecated-declarations
CFLAGS += -Wno-shorten-64-to-32 -D_FORTIFY_SOURCE=0
CFLAGS += -mllvm -align-all-functions=5

mkfile_path := $(abspath $(lastword $(MAKEFILE_LIST)))
mkfile_dir := $(dir $(mkfile_path))
PROJ_DIR := $(mkfile_dir)
CFLAGS += -I$(PROJ_DIR) -I$(PROJ_DIR)/include

OPDUMP = $(realpath ../opdump/opdump)

export CC
export CFLAGS
export OPDUMP
export SDK

TARGET_DIRS = filter hooks kern utils

all : $(TARGET_DIRS) xnu_bypass

.PHONY : target_dirs $(TARGET_DIRS)

target_dirs : $(TARGET_DIRS)

$(TARGET_DIRS) :
	$(MAKE) -C $@

OBJECT_FILES = $(shell find $(TARGET_DIRS) -type f -name "*.o")

xnu_bypass : $(OBJECT_FILES) xnu_bypass.c
	$(CC) $(CFLAGS) $(LDFLAGS) $(OBJECT_FILES) xnu_bypass.c -o xnu_bypass
	ldid -Sent.xml xnu_bypass
