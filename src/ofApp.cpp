// original code written by Andreas Müller
// https://github.com/andreasmuller
//
//https://github.com/andreasmuller/NoiseWorkshopScratchpad/tree/master/NoiseTerrain
//
// Modified and commented by Jinnie Templin
//
//
//

#include "ofApp.h"
#include "Math/MathUtils.h"

//--------------------------------------------------------------
void ofApp::setup(){
    //load a font
    fontSmall.loadFont("Fonts/DIN.otf", 8 );
    
    camera.setAutoDistance( false );
    //set the camera position
    camera.setPosition( ofVec3f(0,1,4) );
    //clip the "plane" so that you can move through the 3d space
    camera.setNearClip( 0.001 );

}

//--------------------------------------------------------------
void ofApp::update(){
    
}

ofVec3f getTerrain( float _x, float _y, float _frequency, float _magnitude ){
    ofVec3f p( _x, 0, _y );
    //p.y = ofNoise( p.x * _frequency, p.z * _frequency ) * _magnitude;
    p.y = MathUtils::fbm( ofVec2f(p.x * _frequency, p.z * _frequency), 4, 2.0, 0.5 ) * _magnitude;
    return p;
    
}
//--------------------------------------------------------------
void ofApp::draw(){
    //draw a gradient background
    ofBackgroundGradient( ofColor(55), ofColor(0), OF_GRADIENT_CIRCULAR );
    
    //set variable t equal to the time elapsed
    float t = ofGetElapsedTimef();
    
    //make mx and my variables a percentage of the screen width and height, dependent upon mouse position
    float mx = ofNormalize( ofGetMouseX(), 0, ofGetWidth() );
    float my = ofNormalize( ofGetMouseY(), 0, ofGetHeight() );
    
    //remap mx from .1 to 1
    float frequency = ofMap( mx, 0, 1, 0.1, 1.0 );
    
    int res = 100;
    ofVec3f size(5, 1, 5);
    
    //make a new mesh made of triangles
    ofMesh mesh;
    mesh.setMode( OF_PRIMITIVE_TRIANGLES );
    
    
    //iterate through y points on the terrain
    for( int y = 0; y < res; y++ )
    {
        //iterate through x points on the terrain
        for( int x = 0; x < res; x++ )
        {
            ofVec3f p = getTerrain( ofMap( x, 0, res, size.x * -0.5f, size.x * 0.5f ),
                                   ofMap( y, 0, res, size.z * -0.5f, size.z * 0.5f ),
                                   frequency, size.y );
            
            ofVec3f pRight = getTerrain( ofMap( x + 1, 0, res, size.x * -0.5f, size.x * 0.5f ),
                                        ofMap( y, 0, res, size.z * -0.5f, size.z * 0.5f ),
                                        frequency, size.y );
            
            ofVec3f pBot = getTerrain(  ofMap( x, 0, res, size.x * -0.5f, size.x * 0.5f ),
                                      ofMap( y + 1, 0, res, size.z * -0.5f, size.z * 0.5f ),
                                      frequency, size.y );
            
            //ofVec3f normal = (pRight-p).getCrossed( (pBot-p) ).getNormalized();
            ofVec3f normal = (pBot-p).getCrossed( (pRight-p) ).getNormalized();
            
            mesh.addVertex( p );
            mesh.addNormal( normal );
            
            //mesh.addVertex( p );
            //mesh.addVertex( p + (normal * 1));
            
        }
    }
    
    
    for( int y = 0; y < res-1; y++ )
    {
        for( int x = 0; x < res-1; x++ )
        {
            int tmp = (y * res) + x;
            
            //mesh.addIndex( tmp ); mesh.addIndex( tmp + 1 );
            //mesh.addIndex( tmp ); mesh.addIndex( tmp + res );
            
            mesh.addTriangle( tmp, tmp + 1, tmp + 1 + res );
            mesh.addTriangle( tmp, tmp + 1 + res, tmp + res );
            
        }
    }
    
    ofEnableDepthTest();
    
    camera.begin();
    
				// set the color and draw the grid
				ofSetColor( ofColor(60) );
				ofPushMatrix();
    ofRotate(90, 0, 0, -1);
    ofDrawGridPlane( size.x, (int)size.x, false );
				ofPopMatrix();
    
				//make a light and position it so that we can see the mesh
                ofLight light;
				light.setPosition( ofVec3f(1,4,0) );
				light.enable();
                ofEnableLighting();
    
    //set the color of the mesh
    ofSetColor( ofColor::white );
    //draw the mesh
    mesh.draw();
	//turn off the lighting
    ofDisableLighting();
    //draw a spehere where the light is positioned
				ofSphere( light.getPosition(), 0.1 );
    
    //"close" the 3d world
    camera.end();
    ofDisableDepthTest();
}






// --------------------------------
//--------------------------------------------------------------
void ofApp::keyPressed(int _key){
   //I commented out this line because it didn't do anything
    // if( _key == ' ' )
    
}