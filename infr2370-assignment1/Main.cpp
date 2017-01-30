//Marc Tremblay 01/24/2017
//100555250


#include "FMOD/SoundEngine.h"
#include "jnaut/graphics/Window.h"

#include <time.h>
#include <math.h>

#define PI 3.14159265

FMOD_VECTOR RotateSound(int step)
{
	int angle = 90 + 5 * step;
	
	return { 2*cosf(angle*PI / 180), 2*sinf(angle*PI / 180), 0 };

}

int main()
{
	char soundFile[256] = "media/drumloop.wav";

	/*
	std::cout << "Please enter the name of a .wav file: ";

	std::cin.get(soundFile, 256);
	*/

	Sound sound = Sound({ 0.0, 0.0, 0.0});
	sound.Load(soundFile);

	//Window window = Window("INFR 2370 - Assignment One");
	using namespace jnaut;
	using namespace graphics;
	Window window("INFR 2370 - Assignment One", 800, 600);

	glClearColor(0.2f, 0.1f, 0.3f, 1.0f);

	sound.Play();
	
	float start, delta = 0;

	float timer = 0;
	int step = 0;

	while (!window.Closed())
	{
		window.Clear();

		start = clock();
		//draw opengl stuff

		sound.SetPos(RotateSound(step));
		Sound::SystemUpdate();
		window.Update();

		if (timer >= 0.5f)
		{
			step++;
			timer = 0.0f;
		}

		delta = (clock() - start) / 1000;
		timer += delta;
	}
	return EXIT_SUCCESS;
}