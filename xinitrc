# xinitrc file for testing our window manager.

# 1. Start some programs to play with.
xeyes &
sleep 2 && xclock &
sleep 5 && xterm &

# 2. Start our window manager.
exec ~/dev/projects/cpwm/cpwm
