#pragma once

#include "ofMain.h"

typedef struct{
	float length;
	ofPoint degree3D;
} Point3D;

class ofApp : public ofBaseApp{

public:
	void setup();
	void update();
	void draw();

	void keyPressed(int key);
	void keyReleased(int key);
	void mouseMoved(int x, int y);
	void mouseDragged(int x, int y, int button);
	void mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);
	void windowResized(int w, int h);
	void dragEvent(ofDragInfo dragInfo);
	void gotMessage(ofMessage msg);

	ofMesh mesh;
	vector<Point3D> point3D;
	ofEasyCam cam;

	vector<ofVec3f> point3DRaw;
	float distance;
    
    ofSpherePrimitive sphere;

};
