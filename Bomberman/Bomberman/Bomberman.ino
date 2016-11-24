#include "Textures.h"

int main()
{
	loadTextures();

	while (1){
		drawTexture(1, 0, 0);
		drawTexture(2, 16, 0);
		drawTexture(3, 32, 0);

		drawTexture(5, 48, 0);
		drawTexture(6, 64, 0);
		drawTexture(7, 80, 0);
		drawTexture(8, 96, 0);

		drawTexture(10, 112, 0);
		drawTexture(11, 128, 0);
		drawTexture(12, 144, 0);

		drawTexture(1, 16, 0);

		drawTexture(14, 160, 0);
		drawTexture(15, 176, 0);
		drawTexture(16, 192, 0);
		drawTexture(17, 208, 0);
	}

	return 0;
}
