all: main.gba

.PHONY: clean

main.gba: main.c
	docker run --volume .:/game devkitpro/devkitarm /opt/devkitpro/devkitARM/bin/arm-none-eabi-gcc -c /game/main.c -mthumb-interwork -mthumb -O2 -o /game/main.o
	docker run --volume .:/game devkitpro/devkitarm /opt/devkitpro/devkitARM/bin/arm-none-eabi-gcc /game/main.o -mthumb-interwork -mthumb -specs=gba.specs -o /game/main.elf
	docker run --volume .:/game devkitpro/devkitarm /opt/devkitpro/devkitARM/bin/arm-none-eabi-objcopy -v -O binary /game/main.elf /game/main.gba
	docker run --volume .:/game devkitpro/devkitarm gbafix /game/main.gba

clean:
	rm -f main.gba main.o main.elf
