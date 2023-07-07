#include "include/Mixer.h"
#include "include/Constants.h"

void interleaveWaveformToStream(Sint16 outputStream[], lb_Waveform* waveform)
{
	for (int i = 0; i < waveform->count; i++)
	{
		if (waveform->metaData[i].panning == LB_PANNING_FRONT_LEFT)
			for (int j = 0; j < SAMPLE_SIZE; j++)
				outputStream[0 + (6 * j)] += waveform->streams[i][j] * CHANNELS;
		else if (waveform->metaData[i].panning == LB_PANNING_FRONT_RIGHT)
			for (int j = 0; j < SAMPLE_SIZE; j++)
				outputStream[1 + (6 * j)] += waveform->streams[i][j] * CHANNELS;
		else if (waveform->metaData[i].panning == LB_PANNING_CENTRE)
			for (int j = 0; j < SAMPLE_SIZE; j++)
				outputStream[2 + (6 * j)] += waveform->streams[i][j] * CHANNELS;
		else if (waveform->metaData[i].panning == LB_PANNING_CENTRE && waveform->metaData->key < 125)
			for (int j = 0; j < SAMPLE_SIZE; j++)
				outputStream[3 + (6 * j)] += waveform->streams[i][j] * CHANNELS;
		else if (waveform->metaData[i].panning == LB_PANNING_REAR_LEFT)
			for (int j = 0; j < SAMPLE_SIZE; j++)
				outputStream[4 + (6 * j)] += waveform->streams[i][j] * CHANNELS;
		else if (waveform->metaData[i].panning == LB_PANNING_REAR_RIGHT)
			for (int j = 0; j < SAMPLE_SIZE; j++)
				outputStream[5 + (6 * j)] += waveform->streams[i][j] * CHANNELS;
	}
}