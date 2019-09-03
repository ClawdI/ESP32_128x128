//#include <Adafruit_SSD1331.h>
#include <Adafruit_ST7735.h>
#include <Adafruit_GFX.h>
#include <LinkedList.h>
#include <SPI.h>

#define WIDTH 128
#define HEIGHT 128

#define SPRITE_SIZE 16
#define SPRITE_RES 256

#define sclk 18 // 18
#define mosi 19 // 23
#define cs   5
#define rst  17
#define dc   16

//Graphics definitions

#define ALLOW_SCREEN_CLIPING false
#define USE_ALPHA_MAPS true

//SPRITES

//PLAYER

bool player_alpha_map[SPRITE_RES] =
{
false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,
false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,
false,false,true,true,true,true,true,true,true,true,true,true,true,true,false,false,
false,false,true,true,true,true,true,true,true,true,true,true,true,true,false,false,
false,false,true,true,false,true,true,true,true,true,false,true,true,true,false,false,
false,false,true,true,false,true,true,true,true,true,false,true,true,true,false,false,
false,false,true,true,true,true,true,true,true,true,true,true,true,true,false,false,
false,false,true,true,true,true,true,false,true,true,true,true,true,true,false,false,
false,false,true,true,true,true,true,false,true,true,true,true,true,true,false,false,
false,false,true,true,true,true,true,true,true,true,true,true,true,true,false,false,
false,false,true,true,false,true,true,true,true,false,true,true,true,true,false,false,
false,false,true,true,false,false,false,false,false,false,true,true,true,true,false,false,
false,false,true,true,true,true,true,true,true,true,true,true,true,true,false,false,
false,false,true,true,true,true,true,true,true,true,true,true,true,true,false,false,
false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,
false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false
};

int16_t player_texture[SPRITE_RES] =
{
0x5AFF,0x5AFF,0x5AFF,0x5AFF,0x5AFF,0x5AFF,0x5AFF,0x5AFF,0x5AFF,0x5AFF,0x5AFF,0x5AFF,0x5AFF,0x5AFF,0x5AFF,0x5AFF,
0x5AFF,0x5AFF,0x5AFF,0x5AFF,0x5AFF,0x5AFF,0x5AFF,0x5AFF,0x5AFF,0x5AFF,0x5AFF,0x5AFF,0x5AFF,0x5AFF,0x5AFF,0x5AFF,
0x5AFF,0x5AFF,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x5AFF,0x5AFF,
0x5AFF,0x5AFF,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x5AFF,0x5AFF,
0x5AFF,0x5AFF,0x0000,0x0000,0xF800,0x0000,0x0000,0x0000,0x0000,0x0000,0xF800,0x0000,0x0000,0x0000,0x5AFF,0x5AFF,
0x5AFF,0x5AFF,0x0000,0x0000,0xF800,0x0000,0x0000,0x0000,0x0000,0x0000,0xF800,0x0000,0x0000,0x0000,0x5AFF,0x5AFF,
0x5AFF,0x5AFF,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x5AFF,0x5AFF,
0x5AFF,0x5AFF,0x0000,0x0000,0x0000,0x0000,0x0000,0xF800,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x5AFF,0x5AFF,
0x5AFF,0x5AFF,0x0000,0x0000,0x0000,0x0000,0x0000,0xF800,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x5AFF,0x5AFF,
0x5AFF,0x5AFF,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x5AFF,0x5AFF,
0x5AFF,0x5AFF,0x0000,0x0000,0xF800,0x0000,0x0000,0x0000,0x0000,0xF800,0x0000,0x0000,0x0000,0x0000,0x5AFF,0x5AFF,
0x5AFF,0x5AFF,0x0000,0x0000,0xF800,0xF800,0xF800,0xF800,0xF800,0xF800,0x0000,0x0000,0x0000,0x0000,0x5AFF,0x5AFF,
0x5AFF,0x5AFF,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x5AFF,0x5AFF,
0x5AFF,0x5AFF,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x5AFF,0x5AFF,
0x5AFF,0x5AFF,0x5AFF,0x5AFF,0x5AFF,0x5AFF,0x5AFF,0x5AFF,0x5AFF,0x5AFF,0x5AFF,0x5AFF,0x5AFF,0x5AFF,0x5AFF,0x5AFF,
0x5AFF,0x5AFF,0x5AFF,0x5AFF,0x5AFF,0x5AFF,0x5AFF,0x5AFF,0x5AFF,0x5AFF,0x5AFF,0x5AFF,0x5AFF,0x5AFF,0x5AFF,0x5AFF
};

// END PLAYER

//MAIN VARIABLES

//Adafruit_ST7735 display = Adafruit_ST7735(cs, dc, mosi, sclk, rst);
SPIClass spiRFID(VSPI);
Adafruit_ST7735 display = Adafruit_ST7735(&spiRFID, cs, dc, rst);

//Create a empty buffer frame for the display
uint16_t bufferTexture[WIDTH * HEIGHT];

//Gets the position of a pixel in 2D coordinates inside the buffer frame
int16_t posBuffer(int16_t x, int16_t y) {
	return x + WIDTH * y;
}

//Gets the position of a pixel in 2D coordinated inside a single dimension array with a certain x(Width) size
int16_t posBuffer(int16_t x, int16_t y, int16_t xSize) {
	return x + xSize * y;
}

void copyTexture(int16_t texOrigin[], int16_t texDestiny[]) {
	for (int16_t index = 0; index < SPRITE_RES; index++)
	{
		texDestiny[index] = texOrigin[index];
	}
}

void copyAlphaMap(bool alphaTexOrigin[], bool alphaTexDestiny[]) {
	for (int16_t index = 0; index < SPRITE_RES; index++)
	{
		alphaTexOrigin[index] = alphaTexDestiny[index];
	}
}

class Object {

public:

	int16_t posX, posY;

};

class Renderer : public Object {

public:

	//Dedicate space for a single texture on this renderer
	int16_t* texture;

	bool* alphaMap;

	virtual void draw() {
		//Determine the starting position of this texture to draw considering it's central pivot
		int16_t bufferStartX = posX - (SPRITE_SIZE / 2);
		int16_t bufferStartY = posY - (SPRITE_SIZE / 2);

		for (int16_t x = 0; x < SPRITE_SIZE; x++)
		{
			for (int16_t y = 0; y < SPRITE_SIZE; y++)
			{
				int16_t renderPosX = bufferStartX + x;
				int16_t renderPosY = bufferStartY + y;
				//If these pixels are out of bounds then skip them
				if ((renderPosX < 0 || renderPosX > WIDTH - 1 || renderPosY < 0 || renderPosY > HEIGHT - 1) && !ALLOW_SCREEN_CLIPING) continue;
				//Draws on the buffer texture the texture given to this object
				if (USE_ALPHA_MAPS && alphaMap[posBuffer(x, y, SPRITE_SIZE)]) continue;
				//bufferTexture[posBuffer(renderPosX, renderPosY)] = texture[posBuffer(x, y, SPRITE_SIZE)];
				bufferTexture[posBuffer(renderPosX, renderPosY)] = *(texture + posBuffer(x, y, SPRITE_SIZE));
			}
		}
	}
};

class GameObject : public Renderer {
	
public:

	virtual void start() {

	}


	virtual void update() {

	}

};

class Player : public GameObject {

public:
	
	int16_t movementSpeed = 2;
	int16_t xSpeed, ySpeed;

	void start() {
		
		posX = random(0, WIDTH);
		posY = random(0, HEIGHT);

		xSpeed = movementSpeed;
		ySpeed = movementSpeed;

		texture = &player_texture[0];
		alphaMap = &player_alpha_map[0];
		//copyTexture(player_texture, texture);
		//copyAlphaMap(player_alpha_map, alphaMap);
	}

	void update() {
		
		if (posX - xSpeed < 0) {
			xSpeed = movementSpeed + random(0, 2);
		}

		if (posX + xSpeed > WIDTH) {
			xSpeed = -movementSpeed - random(0, 2);
		}

		if (posY - ySpeed <= 0) {
			ySpeed = movementSpeed + random(0, 2);
		}

		if (posY + ySpeed >= HEIGHT) {
			ySpeed = -movementSpeed - random(0, 2);
		}

		posX += xSpeed;
		posY += ySpeed;
	}

};
/*
class GameManager {

private:

	LinkedList<GameObject *> gameObjects = LinkedList<GameObject *>();

public:

	void start() {
		for (uint8_t i = 0; i < gameObjects.size(); i++)
		{
			(*gameObjects.get(i)).start();
		}
	}

	void update() {
		for (uint8_t i = 0; i < gameObjects.size(); i++)
		{
			(*gameObjects.get(i)).update();
			(*gameObjects.get(i)).draw();
		}
	}

	void addGameObject(GameObject gO) {
		gameObjects.add(&gO);
	}

} gameManager;
*/

const uint8_t player_size = 6;

Player player[player_size];

void setup() {
	Serial.begin(115200);

	display.initR(INITR_144GREENTAB);

	spiRFID.begin(18, 19, 23, 5);

	for (uint8_t i = 0; i < player_size; i++)
	{
		player[i].start();
	}

	//gameManager.addGameObject(player);
	//gameManager.start();
}

// the loop function runs over and over again until power down or reset
void loop() {
	//Clear bufferframe
	for (uint16_t i = 0; i < WIDTH * HEIGHT; i++)
	{
		bufferTexture[i] = 0x0000;
	}
	//Game code...
	//display.fillScreen(random(0, 65535));
	
	for (uint8_t i = 0; i < player_size; i++)
	{
		player[i].update();
		player[i].draw();
	}

	//gameManager.update();

	//Draw texture to display
	display.drawRGBBitmap(0, 0, bufferTexture, WIDTH, HEIGHT);

	delay(16);
}
