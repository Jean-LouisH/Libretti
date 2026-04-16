#include <glad/glad.h>
#include "oscilloscope.hpp"

void Oscilloscope::initialize()
{
	if ((!glad_load_gl_loader((GLADloadproc)SDL_GL_GetProcAddress)))
	{
		printf("GLAD failed to initialize.");
	}
}

void Oscilloscope::render_waveforms(SDL_Window* window, lb_Libretti* libretti)
{
	lb_Waveforms waveforms = libretti->playback->current_waveforms;
	const double horizontal_scale = 1.0 + (1.0 / 5.0);
	const double vertical_scale = 0.7;
	gl_clear(GL_COLOR_BUFFER_BIT);

	float max_amplitude = 0;

	/* Scale the ampltidue of the notes to the highest
	   ampltidue in the whole composition.*/
	for (int i = 0; i < libretti->composition->track_count; i++)
	{
		for (int j = 0; j < libretti->composition->tracks[i].note_count; j++)
		{
			float amplitude = libretti->composition->tracks[i].note_events[j].note.dynamic;
			if (amplitude > max_amplitude)
			{
				max_amplitude = amplitude;
			}
		}
	}

	for (int i = 0; i < waveforms.count; i++)
	{
		/*OpenGL compatibility profile fixed-functions are
		sufficient for this simple test oscilloscope.*/
		gl_begin(GL_LINE_STRIP);
		gl_color4ub(255, 255, 255, 255);

		bool start_trigger = false;
		int x_trigger_offset = 0;

		for (int j = 0; j < DEFAULT_STREAM_SAMPLE_SIZE; j++)
		{
			if (j > 0 && !start_trigger)
			{
				Sint16 value_range = 200;
				Sint16 target_value = waveforms.note_meta_data[i].dynamic;
				Sint16 sample_a = waveforms.streams[i][j - 1];
				Sint16 sample_b = waveforms.streams[i][j];

				Sint16 lower = sample_b - (value_range / 2);
				Sint16 upper = sample_b + (value_range / 2);

				start_trigger = (sample_b > sample_a) &&
					(lower <= target_value && target_value <= upper);
			}

			if (!start_trigger)
			{
				x_trigger_offset++;
			}
			else
			{
				double count = double(waveforms.count);

				/* This math function defines the y centre of the individual stream by its
				* count number "i". The value "2" is the top of window, and as "i" increases,
				* the centre is calculated to be lower.*/
				double centre = 2 - ((1.0 / count) + ((i) * (2.0 / count)));

				/* y is defined to be the centre of the individual stream + the ratio of its
				* instantaneous value over the highest amplitude among the streams.*/
				double y = centre + ((vertical_scale / count) * (double(waveforms.streams[i][j]) / max_amplitude)) - 1.0;
				double x = ((double(j - x_trigger_offset) / DEFAULT_STREAM_SAMPLE_SIZE) * 2 * horizontal_scale) - 1.0;

				gl_vertex2f(x, y);
			}
		}
		gl_end();
	}
}
