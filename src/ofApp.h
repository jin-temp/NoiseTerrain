// original code written by Andreas MŸller
// https://github.com/andreasmuller
//
//https://github.com/andreasmuller/NoiseWorkshopScratchpad/tree/master/NoiseTerrain
//
// Modified and commented by Jinnie Templin
//
//
//

#pragma once

#include "ofMain.h"
#include "Math/MathUtils.h"

class ofApp : public ofBaseApp
{
	public:
	
	
    void setup();
    void update();
    void draw();
    void keyPressed( int _key );
    //void getTerrain ( float _x, float _y, float _frequency, float _magnitude );

	
    ofEasyCam camera;
	
    ofTrueTypeFont fontSmall;
};
