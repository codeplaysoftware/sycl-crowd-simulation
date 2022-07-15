# Get rid of any previous virtual frame buffer
pkill -9 Xvfb
rm /var/tmp/Xvfb_screen0

# Create a virtual screen :99.0 with given dimensions & color depth
# mapping output to /var/tmp/Xvfb_screen_0
Xvfb :99 -screen 0 1920x1080x16 -fbdir /var/tmp &

# Run crowd simulation, using script argument as input file config
DISPLAY=:99.0 ../build/crowdsim ../input/$1 &

# Use the x11grab device to write to video file
ffmpeg -video_size 1920x1080 -framerate 25 -f x11grab -i :99.0+0,0 output.mp4
