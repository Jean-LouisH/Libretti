#include <libretti.h>
#include <string>
#include <iostream>
#include <string>

#undef main //undo SDLmain definition

int main(int argc, char* argv[])
{
    std::string input_filepath;
    std::string output_filepath = "output.wav";
    int sample_rate = 44100;
    int channel_count = 2;

    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <input.libretti> [options]\n"
                  << "Options:\n"
                  << "  -o <path>    Output WAV path (default: output.wav)\n"
                  << "  -s <rate>    Sample rate (default: 44100)\n"
                  << "  -c <count>   Channel count (default: 2)\n";
        return 1;
    }

    input_filepath = argv[1];

    // Parse optional flags
    for (int i = 2; i < argc; i++) {
        std::string arg = argv[i];

        if (arg == "-o" && i + 1 < argc) {
            output_filepath = argv[++i];
        } else if (arg == "-s" && i + 1 < argc) {
            sample_rate = std::stoi(argv[++i]);
        } else if (arg == "-c" && i + 1 < argc) {
            channel_count = std::stoi(argv[++i]);
        } else {
            std::cerr << "Unknown or incomplete argument: " << arg << "\n";
            return 1;
        }
    }

    lb_Libretti* libretti = lb_create_libretti(input_filepath.c_str());
    if (!libretti) {
        std::cerr << "Error: Could not load libretti file: " << input_filepath << "\n";
        return 1;
    }

    std::cout << "Synthesizing " << input_filepath << " at " << sample_rate << "Hz...\n";

    lb_AudioClip audio_clip = lb_synthesize_audio_clip(libretti, sample_rate, channel_count);
    
    if (lb_save_audio_clip_to_wav_file(&audio_clip, output_filepath.c_str())) {
        std::cout << "Successfully saved to " << output_filepath << "\n";
    } else {
        std::cerr << "Error: Failed to save WAV file.\n";
        return 1;
    }

    return 0;
}
