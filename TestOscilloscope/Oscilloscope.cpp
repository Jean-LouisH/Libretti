#include "Oscilloscope.hpp"
#include <SDL.h>
#include <SDL_opengl.h>
#include <string>

void Oscilloscope::renderWaveforms(SDL_Window* window, Libretti* libretti)
{
	lb_NoteWaves* noteWaves = libretti->noteWaves;
	const double scale = 1.0 + (1.0 / 5.0);
	glClear(GL_COLOR_BUFFER_BIT);

	for (int i = 0; i < noteWaves->count; i++)
	{
		glBegin(GL_LINE_STRIP);
		glColor4ub(255, 255, 255, 255);

		bool startTrigger = false;
		int xTriggerOffset = 0;

		for (int j = 0; j < SAMPLE_SIZE; j++)
		{
			if (j > 0 && !startTrigger)
			{
				Sint16 valueRange = 200;
				Sint16 targetValue = noteWaves->metaData[i].amplitude;
				Sint16 sampleA = noteWaves->streams[i][j - 1];
				Sint16 sampleB = noteWaves->streams[i][j];

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
				double maxAmplitude = 0;
				for (int k = 0; k < noteWaves->count; k++)
				{
					if (noteWaves->metaData[k].amplitude > maxAmplitude)
					{
						maxAmplitude = noteWaves->metaData[k].amplitude;
					}
				}

				double count = double(noteWaves->count);

				/* This math function defines the y centre of the individual stream by its
				* count number "i". The value "2" is the top of window, and as "i" increases,
				* the centre is calculated to be lower.*/
				double centre = 2 - ((1.0 / count) + ((i) * (2.0 / count)));

				/* y is defined to be the centre of the individual stream + the ratio of its
				* instantaneous value over the highest amplitude among the streams.*/
				double y = centre + ((0.7 / count) * (double(noteWaves->streams[i][j]) / maxAmplitude)) - 1.0;
				double x = ((double(j - xTriggerOffset) / SAMPLE_SIZE) * 2 * scale) - 1.0;

				glVertex2f(x, y);
			}
		}
		glEnd();
	}
}
