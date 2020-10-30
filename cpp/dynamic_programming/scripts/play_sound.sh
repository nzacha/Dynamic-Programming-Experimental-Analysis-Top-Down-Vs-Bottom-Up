#amixer -c 1 -- sset Master playback 40%
echo "playing sound"
aplay --quiet media/tada.wav
#amixer -c 1 -- sset Master playback 100%
