DEPSDIR = .
include $(DEVKITPPC)/gamecube_rules

CFLAGS		= -Wall $(MACHDEP) $(INCLUDE) -I/home/lillie/.wine/drive_c/DolphinSDK1.0/include
LDFLAGS		=  -Map $(notdir $@).map
LIBS	:= 
export LD       :=      $(CC)

all: main.dol

main.dol: patcher patchbin orig.dol
	./patcher orig.dol patchbin 0x803FD000 > main.dol

patchbin: patchdol.o patchdol.x hooks.o
#powerpc-eabi-ld -T patchdol.x  $(LIBS) patchdol.o mios.o $(LIBS)
	powerpc-eabi-ld -T patchdol.x hooks.o patchdol.o $(LDFLAGS) -o a.out
	powerpc-eabi-objcopy -O binary a.out patchbin

patcher: patcher.c
	gcc patcher.c -o patcher

clean:
	rm -f *.o patcher main.dol a.out patchbin