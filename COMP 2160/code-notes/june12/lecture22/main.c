#define SCREEN_HEIGHT 160
#define SCREEN_WIDTH 240

int main(void)
{
	// Write to the "I/O registers" (ioram);
    // this is setting up video display parameters.
	volatile unsigned char *ioram = (unsigned char *)0x04000000;

	ioram[0] = 0x03; // Use video mode 3 (in BG2, a 16bpp bitmap in VRAM)
	ioram[1] = 0x04; // Enable BG2 (BG0 = 1, BG1 = 2, BG2 = 4, ...)

	volatile unsigned short *vram = (unsigned short *)0x06000000;

  vram[SCREEN_HEIGHT / 2 * SCREEN_WIDTH + 0] = 0x001f; //red
  vram[SCREEN_HEIGHT / 2 * SCREEN_WIDTH + 5] = 0x03e0; //green
  vram[SCREEN_HEIGHT / 2 * SCREEN_WIDTH + 5] = 0x7c00; //blue

  while(1);

    return 0;
}
