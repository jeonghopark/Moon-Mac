#pragma once

#include "ofMain.h"
#include "ofxGui.h"


typedef struct{
	
    ofVec3f point3DRaw;
    
    ofVec3f p1;
    ofVec3f p2;
    
    ofVec3f norm;
    
    ofVec3f u; //x axis unit vector
    ofVec3f v;

    ofMesh createrMesh;
    float radiusCreater;
    ofVbo vbo;
    
    float theta;
    float phi;
    float radius;

    
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
    ofMesh darkMesh;
	vector<Point3D> point3D;
	ofEasyCam cam;

	float distance;
    

    bool fullScreen;
    ofLight light;
    
    
    ofSpherePrimitive sphere;
    
    ofMesh baseLunar;
    
    ofVbo vboLine;
    ofMesh allMesh;
    
    
    bool oneShot;
    
    int creatorNum;
    
    
    bool bHide;
    
    ofxIntSlider numCreators;
    ofxButton reSetting;
    ofxToggle innerCircle;
    ofxPanel gui;
    ofxFloatSlider randomHeight;
    ofxFloatSlider innerCircleSize;
    
    void setPoint3D(int _num);
    
};
