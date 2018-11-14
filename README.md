
# Motion Photo Extractor
A simple command line tool to extract video and photo parts from the Motion Photos created by Samsung phones.

## Usage as command line tool
Usage:  
&nbsp;&nbsp;&nbsp;&nbsp;`mpe [OPTIONS...]`  
  
&nbsp;&nbsp;`-i`, `--input` `path`  Input file (motion photo)  
&nbsp;&nbsp;`-v`, `--video` `path`  [optional] Video file to extract from motion photo  
&nbsp;&nbsp;`-p`, `--photo` `path`  [optional] Photo file to extract from motion photo  
&nbsp;&nbsp;`-h`, `--help` &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; Print this help information  
  
Example usage to extract both video and photo parts from the input file:  
&nbsp;&nbsp;&nbsp;&nbsp;`mpe -i motion_photo.jpg -v video.mp4 -p photo.jpg`  
  
You can optionally ommit either output photo path or output video path.  

## Install
Using terminal in any folder where you would like to download the application:

   1. `git clone https://github.com/eduard-netsajev/motion-photo-extractor.git`
   2. `cd motion-photo-extractor`
   3. `cmake .`
   4. `make`
   5. (Optional) `sudo make install`
   
The last step will make the `mpe` binary be available through the local user bin folder (i.e. it will be available globally). Or you can just do whatever you want with the built binary file.

## Example usage to mimic viewing on a smartphone
Flexible interface allows to chain this tool with other applications. For example one can use [**feh**](https://feh.finalrewind.org/) image viewer and its custom action command to mimic viewing images on a smartphone:  
  
`feh -A ";""mpe -i %F -v /dev/shm/mpe.mp4 && vlc /dev/shm/mpe.mp4 --intf dummy --play-and-exit --no-video-title --no-repeat --no-loop --quiet -f" -Z -F`  
  
With such command pressing `action_0` key (`Enter` by default) extracts the video part from the opened motion photo into `/dev/shm` and immediately opens [**VLC**](https://www.videolan.org/vlc/) media player without any interface and which closes itself after the file is finished playing.
