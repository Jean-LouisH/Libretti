#include "Oscilloscope.hpp"
#include <SDL.h>
#include <glad/glad.h>
#include <string>

void Oscilloscope::initialize()
{
	if ((!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress)))
	{
		printf("GLAD failed to initialize.");
	}
}

void Oscilloscope::renderWaveforms(SDL_Window* window, lb_Libretti* libretti)
{
	lb_Waveform waveform = libretti->playback->waveform;
	const double horizontalScale = 1.0 + (1.0 / 5.0);
	const double verticalScale = 0.7;
	glClear(GL_COLOR_BUFFER_BIT);

	float maxAmplitude = 0;

	/* Scale the ampltidue of the notes to the highest
	   ampltidue in the whole composition.*/
	for (int i = 0; i < libretti->composition->trackCount; i++)
	{
		for (int j = 0; j < libretti->composition->tracks[i].noteCount; j++)
		{
			float amplitude = libretti->composition->tracks[i].noteEvents[j].note.dynamic;
			if (amplitude > maxAmplitude)
			{
				maxAmplitude = amplitude;
			}
		}
	}

	for (int i = 0; i < waveform.count; i++)
	{
		/*OpenGL compatibility profile fixed-functions are
		sufficient for this simple test oscilloscope.*/
		glBegin(GL_LINE_STRIP);
		glColor4ub(255, 255, 255, 255);

		bool startTrigger = false;
		int xTriggerOffset = 0;

		for (int j = 0; j < SAMPLE_SIZE; j++)
		{
			if (j > 0 && !startTrigger)
			{
				Sint16 valueRange = 200;
				Sint16 targetValue = waveform.metaData[i].dynamic;
				Sint16 sampleA = waveform.streams[i][j - 1];
				Sint16 sampleB = waveform.streams[i][j];

				Sint16 lower = sampleB - (valueRange / 2);
				Sint16 upper = sampleB + (valueRange / 2);

				startTrigger = (sampleB > sampleA) &&
					(lower <= targetValue && targetValue <= upper);
			}

			if (!startTrigger)
			{
				xTriggerOffset++;
			}
			else
			{
				double count = double(waveform.count);

				/* This math function defines the y centre of the individual stream by its
				* count number "i". The value "2" is the top of window, and as "i" increases,
				* the centre is calculated to be lower.*/
				double centre = 2 - ((1.0 / count) + ((i) * (2.0 / count)));

				/* y is defined to be the centre of the individual stream + the ratio of its
				* instantaneous value over the highest amplitude among the streams.*/
				double y = centre + ((verticalScale / count) * (double(waveform.streams[i][j]) / maxAmplitude)) - 1.0;
				double x = ((double(j - xTriggerOffset) / SAMPLE_SIZE) * 2 * horizontalScale) - 1.0;

				glVertex2f(x, y);
			}
		}
		glEnd();
	}
}
