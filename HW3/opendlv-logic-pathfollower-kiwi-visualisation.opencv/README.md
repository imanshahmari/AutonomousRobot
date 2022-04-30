# A path planner for the Kiwi robot

To build the program run:
`docker build -t opendlv-logic-pathfollower-kiwi .`

To start the program, run:
`docker run -ti --rm -e DISPLAY=$DISPLAY -v /tmp:/tmp -v /path/to/maps:/opt opendlv-logic-pathfollower-kiwi /usr/bin/opendlv-logic-pathfollower-kiwi --cid=111 --map-file=/opt/simulation-map.txt --freq=10 --start-x=0.0 --start-y=0.0 --end-x=1.0 --end-y=1.0 --frame-id=1 --verbose`

Remember to change the `/path/to/maps` to the folder where you keep your simulation maps. Also remember to run the `xhost +` command after each reboot to allow Docker to use the graphics environment.
