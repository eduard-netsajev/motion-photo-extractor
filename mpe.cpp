#include <iostream>
#include <cxxopts.hpp>
#include <string>
#include <cstdlib>

using namespace std;

struct Task {
    string input_file;
    string out_photo;
    string out_video;
};

Task parse_options(int argc, char* argv[]) {
    cxxopts::Options options_config("Motion Photo Extractor", "Simple tool to work with motion photos\n\n"
                             "Example usage to extract both video and photo parts from the input file:\n"
                             "mpe -i motion_photo.jpg -v video.mp4 -p photo.jpg\n");
    
    options_config.add_options()
        ("i,input", "Input file (motion photo)", cxxopts::value<string>())
        ("v,video", "[optional] Video file to extract from motion photo", cxxopts::value<string>())
        ("p,photo", "[optional] Photo file to extract from motion photo", cxxopts::value<string>())
        ("h,help", "Print this help information")
        ;

    auto options = options_config.parse(argc, argv);
        
    if (options.count("help")) {
        cout << options_config.help();
        exit(EXIT_SUCCESS);
    }
    if (!options.count("input")) {
        cout << "No input file specified, use -h to see an example of a valid usage.\n";
        exit(EXIT_FAILURE);
    }
    if (!options.count("video") && !options.count("photo")) {
        cout << "Not a single output file specified (no photo or video output argument), use -h to see an example of a valid usage.\n";
        exit(EXIT_FAILURE);
    }

    Task task;
    
    task.input_file = options["input"].as<string>();
    if (options.count("video")) task.out_video = options["video"].as<string>();
    if (options.count("photo")) task.out_photo = options["photo"].as<string>();
    
    return Task{};
}

int main(int argc, char* argv[]) try {
    Task task = parse_options(argc, argv);
} catch (cxxopts::OptionException e) {
    cerr << e.what() << ". Use --help for a list of valid options.\n";
} catch (...) {
    cerr << "Unexpected error" << endl;
}
