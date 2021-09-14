CFLAGS    	 = -march=native -ggdb3 -fPIC -std=gnu99 -fshort-wchar -fno-omit-frame-pointer -Wno-multichar -I../include -I../log -mstackrealign -D_XOPEN_SOURCE=600 -D_DARWIN_C_SOURCE
CPPFLAGS  	 = -D_GNU_SOURCE -I. -I../intercept/include
LDFLAGS   	 = $(CFLAGS) -lm -shared
ARCH	  	 = x64
OBJECT_FILES = winstrings.o pe_linker.o crt.o util.o extra.o file_mapping.o hsearch_r.o

ifeq ($(ARCH),x86)
	CFLAGS  += -m32
	LDFLAGS += -m32
else ifneq ($(ARCH),x64)
$(error Supported target architectures: x86 or x64)
endif

RELEASE_CFLAGS 	 = -O3
RELEASE_CPPFLAGS = -DNDEBUG
DEBUG_CFLAGS 	 = -O0 -g

.PHONY: clean

# This glob matches all the winapi exports we provide.
WINAPI  = $(patsubst %.c,%.o,$(wildcard winapi/*.c))

TARGETS=libpeloader.so

all: CFLAGS += $(RELEASE_CFLAGS)
all: CPPFLAGS += $(RELEASE_CPPFLAGS)
all: $(TARGETS)

debug: CFLAGS += $(DEBUG_CFLAGS)
debug: $(TARGETS)

libpeloader.so: $(WINAPI) $(OBJECT_FILES)
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)

clean:
	rm -f a.out core *.o core.* vgcore.* gmon.out winapi/*.o $(TARGETS)