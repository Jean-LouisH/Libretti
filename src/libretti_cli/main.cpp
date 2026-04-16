#include <libretti.h>
#include <string>

#undef main //undo SDLmain definition

int main(int argc, char* argv[])
{
	std::string input_filepath;
	std::string output_filepath;
	int sample_rate = 44100;
	int channel_count = 2;

	lb_Libretti* libretti = lb_create_empty_libretti();
	lb_compile_composition_from_script_file(
		libretti->composition, 
		input_filepath.c_str()
	);
	lb_AudioClip audio_clip = lb_synthesize_audio_clip(libretti, sample_rate, channel_count);
	lb_save_audio_clip_to_wav_file(&audio_clip, "output.wav");
	return 0;
}
