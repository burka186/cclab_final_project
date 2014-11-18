#CC Lab Final Project

So I decided to combine my CCLab final with my Major Studio final project, in which I'm working with an Arduino accelerometer in a punching bag to manipulate audio and visual 'noise' (the general goal being the more someone punches, the quieter the noise becomes until it eventually disappears).

Unfortunately, as of tonight, I haven't been able to fully integrate both sketches together (all attempts to do so have thusfar ended in errors, ugh!), so I'm turning in two separate sketches:

* One sketch connects to my Arduino using Firmata and takes accelerometer readings, smooths them, and, using a calibrated 'threshold' to determine whether a punch has occured, degrades the volume of auditory static noise that is also dynamically created within the sketch.

* The other sketch contains the visual 'noise', a series of phrases and words that are pulled from an XML file I wrote and displayed in a moving cloud on the screen. I solved the problem of how to get my program to iterate through the XML file multiple times to create the desired number of NoiseObjects by creating a custom constructor for the NoiseObjects class that pulls randomly from the XML file each time an individual NoiseObject is created. I'm storing all the NoiseObjects in a vector called noiseCollection and iterating through it to move and draw the words. Right now, I'm using void mousePressed() to simulate the "punch" action and am fading the text of each NoiseObject to black gradually depending on a randomly assigned resistance threshold given when each object is instantiated. I want to be able to dynamically delete objects from the noiseCollection vector when there is a "punch," but I keep getting thread breaks. I'm going to keep working on adding this feature, though. 

*Next Steps:*
* Figure out how to successfully delete from the number of NoiseObjects displayed
* Add more complex physics (a spring / scattering action?) to the words when a punch is registered
* Integrate the visual and audio noise sketch and make the words respond to the accelerometer
* Tinker with the audio degradation values so that it doesn't happen as quickly as it is happening now (I'm keeping the values where they are because they do register a noticeable effect)

*Sources:*
* I consulted the openFrameworks Firmata Example (my audio sketch is still named Firmata Example because openFrameworks decided to be finnicky and the only way I could get it to work was by copying and pasting the example file...) and Audio Output Example
* I figured out how to solve my custom constructor issues in the NoiseObjects class via this thread on [Stack Overflow](http://stackoverflow.com/questions/23163682/invalid-operands-to-binary-expression-c-operator-overload)
* I consulted a few knowledgable and incredibly helpful second-years for help RE: XML data, Arduino to openFrameworks communication, and general openFrameworks error f*kery. Notables include: Gabriel Gianordoli, Dylan Shad, Jocelyn McDonald, and Lucy Matchett (all helpers will receive donuts upon completion of this project)
