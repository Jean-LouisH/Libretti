#include "include/WaveformGenerator.h"
#include <stdbool.h>
#include <math.h>

void generateWaveform(lb_Waveform* waveform, lb_Note currentNotes[])
{
	static double timesteps[MAX_TRACKS];

	for (int i = 0; i < waveform->count; i++)
	{
		waveform->metaData[i] = currentNotes[i];

		for (int n = 0; n < SAMPLE_SIZE; n++)
		{
			double frequency = waveform->metaData[i].key;
			double time = (timesteps[i] / SAMPLE_FREQUENCY);
			double period = (1.0 / waveform->metaData[i].key);
			double amplitude = waveform->metaData[i].dynamic;

			switch (waveform->metaData[i].timbre)
			{
				case LB_TIMBRE_SQUARE_WAVE:
					waveform->streams[i][n] = amplitude * pow((-1), (int)(frequency * time));
					break;
				case LB_TIMBRE_SINE_WAVE:
					waveform->streams[i][n] = amplitude * sin(2.0 * M_PI * frequency * time);
					break;
				case LB_TIMBRE_TRIANGLE_WAVE:
					waveform->streams[i][n] = (2.0 * amplitude / M_PI) * asin(sin((2.0 * M_PI / period) * time));
					break;
				case LB_TIMBRE_SAWTOOTH_WAVE:
					waveform->streams[i][n] = 2 * amplitude * (time / period - (int)(0.5 + time / period));
					break;
				case LB_TIMBRE_PULSE_10:
					waveform->streams[i][n] = amplitude * 
						(2 * amplitude * (time / period - (int)(0.5 + time / period)) > (amplitude * (1.0 - 0.10)));
					break;
				case LB_TIMBRE_PULSE_25:
					waveform->streams[i][n] = amplitude *
						(2 * amplitude * (time / period - (int)(0.5 + time / period)) > (amplitude * (1.0 - 0.25)));
					break;
				case LB_TIMBRE_NOISE:
					waveform->streams[i][n] = (double)((bool)(frequency) * 
						(rand() % (int)(2 * amplitude) + (int)(-amplitude)));
					break;
			}

			if (frequency <= 0)
				waveform->streams[i][n] = 0.0;

			timesteps[i]++;
		}
	}
}