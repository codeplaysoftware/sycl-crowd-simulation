# Get rid of any previous virtual frame buffer
pkill -9 Xvfb
rm /var/tmp/Xvfb_screen0

# Create a virtual screen :99.0 with given dimensions & color depth
# mapping output to /var/tmp/Xvfb_screen_0
Xvfb :99 -screen 0 1920x1080x16 -fbdir /var/tmp &

# Run the nbody simulation on this screen
DISPLAY=:99.0 ../build/crowdsim ../input/$1 &
#DISPLAY=:99.0 ./nbody_cuda 250 5 0.999 0.001 1.0e-3 2.0 &

# To take a screenshot instead of a video (doesn't always work):
# sleep 2
# DISPLAY=:99 xwd -root -silent | convert xwd:- png:/tmp/screenshot.png

# Use the x11grab device to write to video file
ffmpeg -video_size 1920x1080 -framerate 25 -f x11grab -i :99.0+0,0 output.mp4
