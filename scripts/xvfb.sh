# -------------------------------------------------------------------------
# Copyright (C) 2022 Codeplay Software Ltd.
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
#
# Codeplay's crowd-simulation
#
# xvfb.sh
#
# Description:
#   Bash script runs headless crowd simulation and records output as mp4
# -------------------------------------------------------------------------

# Get rid of any previous virtual frame buffer
pkill -9 Xvfb
rm /var/tmp/Xvfb_screen0

# Create a virtual screen :99.0 with given dimensions & color depth
# mapping output to /var/tmp/Xvfb_screen_0
Xvfb :99 -screen 0 1920x1080x16 -fbdir /var/tmp &

# Run crowd simulation, using script argument as input file config
DISPLAY=:99.0 ../build/crowdsim $1 &

# Use the x11grab device to write to video file
ffmpeg -video_size 1920x1080 -framerate 25 -f x11grab -i :99.0+0,0 output.mp4
