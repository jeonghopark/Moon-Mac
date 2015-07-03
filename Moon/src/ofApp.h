#pragma once

#include "ofMain.h"
#include "ofxGui.h"


typedef struct{
	
    ofVec3f degree3D;
    
    ofVec3f point3DRaw;
    
    ofVec3f p1;
    ofVec3f p2;
    
    ofVec3f norm;
    
    ofVec3f u; //x axis unit vector
    ofVec3f v;

    ofMesh createrMesh;
    float radiusCreater;
    ofVbo vboCreator;
    
    float theta;
    float phi;
    float radius;

    
} Point3D;


class ofApp : public ofBaseApp{

public:
	void setup();
	void update();
	void draw();
    void exit();

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
    ofMatrix4x4 camCapture;

	float distance;
    

    bool fullScreen;
    ofLight light;
    
    
    ofSpherePrimitive sphere;
    
    ofMesh baseLunar;
    
    ofVbo vboLine;
    ofMesh allMesh;
    
    void alphaSliderTEst();

    
    int creatorNum;
    
    bool bHide;
    
    ofxIntSlider numCreators;
    ofxToggle innerCircle;
    ofxToggle textureOnOff;
    ofxToggle arcOnOff;
    ofxToggle meshOnOff;
    ofxToggle lineOnOff;
    ofxToggle creatorOnOff;
    ofxToggle darkPlane;
    ofxButton screenCapture;
    ofxPanel gui;
    ofxFloatSlider randomHeight;
    ofxFloatSlider innerCircleSize;
    ofxFloatSlider lineAlpha;
    ofxLabel frameRate;
    ofxLabel fullScreenOnOff;
    ofxLabel hideGui;
    
    void setPoint3D(int _num);
    
    void arcDrawing();
    ofVbo arcLine;
    
    void satellit();
    
    ofColor baseColor;
    
    void polarPositionProb();
    
    void creatorDraw();
    void creatorSetting();
    
    void innerSphere();
    
    void normalLineDraw();
    
    ofImage texture;
    void textureDraw();
    
    void mainDrawing();
    
    ofFbo fbo;
    ofPoint posSize;
    void captureFunction();
    
    void guiDrawing();
    
    void guiMouseReleased(ofMouseEventArgs &m);
    bool inLineAlpha;
    bool inNumCreators;
    bool inRandomHeight;
    
    float rotateY;
    
};
