#include <stdio.h>
#include <stdlib.h>
#include <tos.h>

#define VsetScreen(laddr, paddr, mode) xbios(5, laddr, paddr, 3, mode)
#define SCREEN_MODE_340X240X65536 276
#define SCREEN_MODE_640X480X256 3 | (1 << 3) | (1 << 4)

int main(void)
{
    int previousScreenMode;
    long *previousLogicalBase;
    long *previousPhysicalBase;
    long newScreenSize;
    int *newSharedBase;
    long pixelCount;
    long currentPixelOffset;

    previousLogicalBase = (long *)Logbase();
    previousPhysicalBase = (long *)Physbase();

    newScreenSize = VgetSize(SCREEN_MODE_640X480X256);
    newSharedBase = (int *)malloc(newScreenSize);

    previousScreenMode = VsetScreen(newSharedBase, newSharedBase, SCREEN_MODE_640X480X256);
    pixelCount = 640*480;
    
    Vsync();
    for (currentPixelOffset = 0; currentPixelOffset < pixelCount; ++currentPixelOffset)
    {
        *(newSharedBase + currentPixelOffset) = 0x10;
    }
    

    getchar();

    VsetScreen(previousLogicalBase, previousPhysicalBase, previousScreenMode);
    return 0;
}