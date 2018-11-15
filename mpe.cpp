#include <iostream>
#include <cxxopts.hpp>
#include <string>
#include <cstdlib>
#include <fstream>
#include <algorithm>
#include <functional>

using namespace std;

struct Task {
    string input_file;
    string out_photo;
    string out_video;
};

Task parse_options(int argc, char* argv[]) {
    cxxopts::Options options_config("mpe", "Motion Photo Extractor - simple tool to work with motion photos\n\n"
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
        cerr << "No input file specified, use -h to see an example of a valid usage.\n";
        exit(EXIT_FAILURE);
    }
    if (!options.count("video") && !options.count("photo")) {
        cerr << "Not a single output file specified (no photo or video output argument), use -h to see an example of a valid usage.\n";
        exit(EXIT_FAILURE);
    }

    Task task;
    
    task.input_file = options["input"].as<string>();
    if (options.count("video")) task.out_video = options["video"].as<string>();
    if (options.count("photo")) task.out_photo = options["photo"].as<string>();
    
    return task;
}

vector<char> read_file(const string& file_name) {
    ifstream ifs {file_name, ios::in | ios::binary | ios::ate};
    if(!ifs) {
        cerr << "Failed to open input file '" << file_name << "'\n";
        exit(EXIT_FAILURE);
    }
    ifs.exceptions (ifstream::failbit | ifstream::badbit);

    ifstream::pos_type file_size = ifs.tellg();
    vector<char> bytes (file_size);
    
    ifs.seekg(0, ios::beg);
    ifs.read(bytes.data(), file_size);

    if(ifs.eof() || ifs.peek() != EOF) {
        cerr << "Error reading input file (unexpected file size)\n";
        exit(EXIT_FAILURE);
    }

    return bytes;
}

void create_file(const string& file_name, char* begin, int size) {
    if (size <= 0) {
        cerr << "No data to create '" << file_name << "'\n";
        exit(EXIT_FAILURE);
    }
    ofstream ofs{file_name, ios::binary | ios::trunc};
    if (!ofs) {
        cerr << "Failed to open file to write '" << file_name << "'\n";
        exit(EXIT_FAILURE);
    }
    ofs.write(begin, size);
}

int main(int argc, char* argv[]) try {
    Task task = parse_options(argc, argv);
    vector<char> bytes = read_file(task.input_file);

    string marker = "MotionPhoto_Data";
    auto photo_end_it = search(bytes.begin(), bytes.end(), boyer_moore_searcher(marker.begin(), marker.end()));

    int photo_size = photo_end_it - bytes.begin();
    int video_size = bytes.size() - photo_size - marker.size(); // negative if photo_size == bytes.size i.e. the marker was not found
    
    if(!task.out_photo.empty()) create_file(task.out_photo, &*bytes.begin(), photo_size);
    if(!task.out_video.empty()) create_file(task.out_video, &*(photo_end_it + marker.size()), video_size);
} catch (const cxxopts::OptionException& e) {
    cerr << e.what() << ". Use --help for a list of valid options.\n";
} catch (const ifstream::failure& e) {
    cerr << "Exception opening/reading/closing file: " << e.what() << '\n';
} catch (...) {
    cerr << "Unexpected error\n";
}
