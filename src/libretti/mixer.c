#include "include/mixer.h"
#include "include/constants.h"

void interleave_waveform_to_stream(int16_t* output_stream, lb_Playback* playback)
{
	lb_Waveforms* waveforms = &playback->current_waveforms;
	lb_Note* meta_data = waveforms->note_meta_data;

	for (int i = 0; i < waveforms->count; i++)
	{
		if (meta_data[i].panning == LB_PANNING_FRONT_LEFT)
			for (int j = 0; j < SAMPLE_SIZE; j++)
				output_stream[0 + (6 * j)] += playback->output_volume * waveforms->streams[i][j] * CHANNELS;
		else if (meta_data[i].panning == LB_PANNING_FRONT_RIGHT)
			for (int j = 0; j < SAMPLE_SIZE; j++)
				output_stream[1 + (6 * j)] += playback->output_volume * waveforms->streams[i][j] * CHANNELS;
		else if (meta_data[i].panning == LB_PANNING_CENTRE)
			for (int j = 0; j < SAMPLE_SIZE; j++)
				output_stream[2 + (6 * j)] += playback->output_volume * waveforms->streams[i][j] * CHANNELS;
		else if (meta_data[i].panning == LB_PANNING_CENTRE && meta_data->key < 125)
			for (int j = 0; j < SAMPLE_SIZE; j++)
				output_stream[3 + (6 * j)] += playback->output_volume * waveforms->streams[i][j] * CHANNELS;
		else if (meta_data[i].panning == LB_PANNING_REAR_LEFT)
			for (int j = 0; j < SAMPLE_SIZE; j++)
				output_stream[4 + (6 * j)] += playback->output_volume * waveforms->streams[i][j] * CHANNELS;
		else if (meta_data[i].panning == LB_PANNING_REAR_RIGHT)
			for (int j = 0; j < SAMPLE_SIZE; j++)
				output_stream[5 + (6 * j)] += playback->output_volume * waveforms->streams[i][j] * CHANNELS;
	}
}