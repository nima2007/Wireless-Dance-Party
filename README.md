# Wireless-LED-Dance-Party
Music reactive LED strips over LAN. Needs server app running on pc. Also needs Particle Photn/Arduino with WS2182 strip
Server app uses JAVA.


Purpose:
========
Use your computer's audio to create one or more music reactive light strips wirelessly. The server app uses the system audio and sends the data to the reciever connected to the strip over UDP. The reciever visualizes the music data. 

Setup Reciever (Particle Photon):
===============
Flash the Photon with the ino file in the reciever folder and run it.
Connect the pins as described in the header of the ino file
If needed, use Serial to get the ip address of the Photon if you don't know it.


Setup Server:
===============
Download Processing 2 for your operating system and open the server program in the server folder.
Replace ip1 with the ip address of your Photon. Repeat with ip2 and ip3 if there are multiple, otherwise leave them null.
The program will use the default input sound card, so verify that the correct sound card is set as default. For windows, use Stereo Mix but for Mac you must use a 3rd party driver like SoundFlower.
Run the program. A box should appear. This means that the program is running.

Recommnded Hardware:
======================
Although many different hardware could work with minor tweaks, Below is what I have tested.
-Particle Photon
-Processing 2
-WS2812 (neopixels)
-Server and Reciever must be on same network

Video:
======================
coming soon