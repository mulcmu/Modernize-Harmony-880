# Modernize Harmony 880
 Modernize a Logitech Harmony 880 universal remote

# Details

The Logitech Harmony 880 is a universal infrared remote intended to control the numerous parts of a home theater system with one remote. The Harmony remotes are programmable allowing sequences of IR commands to be sent to start an activity. So "Watch Blu-ray" could be configured to turn on TV, receiver, and blu-ray player player, and set TV and receiver to correct inputs. Convenient to keep from needing numerous remotes to start an activity. Programming is performed using Logitech internet based software to update the remote via a USB connection. In 2021, Logitech announced that they would discontinue Harmony Remote [manufacturing](https://support.logi.com/hc/en-us/community/posts/1500000658341). The release indicates support would still continue software support, who knows how long that will remain.

The 880 remote build is great quality. I'm not sure exactly when I got mine but it is upwards of 15 years of service with only some cosmetic wear to the buttons. It has a rechargeable battery, that charges in a storage cradle. Over the years the universality of the remote has diminished as more devices use RF remote protocols. To keep the 880 working after getting a Roku box, an ESP8266 needed to be setup to [translate IR remote](https://github.com/mulcmu/IRtoRokuBridge) signals to HTTP POST commands.

This project is undertaking an upgrade for the 880 universal remote to, update screen to TFT with better resolution, build in wifi connectivity, and provide an open source software solution for setup and programming.

# Project Logs

https://hackaday.io/project/185926-modernize-harmony-880
