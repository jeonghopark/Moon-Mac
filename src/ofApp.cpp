// http://en.wikibooks.org/wiki/Mathematica/Uniform_Spherical_Distribution
// http://mathworld.wolfram.com/SpherePointPicking.html
// http://mathworld.wolfram.com/SphericalCoordinates.html
// http://forum.openframeworks.cc/t/vector-maths-cross-vectors-and-a-circle-on-a-sphere/15760/9



#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    ofBackground(10);
    ofSetFrameRate(60);
    
    ofEnableAntiAliasing();
    ofEnableDepthTest();
//        ofEnableBlendMode(OF_BLENDMODE_ADD);
    
    baseColor = ofColor::fromHsb(255, 0, 255, 120);

    mesh.setMode(OF_PRIMITIVE_LINES);
    darkMesh.setMode(OF_PRIMITIVE_TRIANGLES);
    baseLunar.setMode(OF_PRIMITIVE_TRIANGLES);
    allMesh.setMode(OF_PRIMITIVE_LINES);
    
    creatorNum = 1200;
    
    gui.setup();
    gui.add(numCreators.setup("Num Creators", 1200, 0, 4000));
    gui.add(randomHeight.setup("Random Height", 0.025, 0, 0.05));
    gui.add(reSetting.setup("ReDrawing"));
    gui.add(innerCircle.setup("Base Sphere", true));
    gui.add(innerCircleSize.setup("Inner Size", 0.95, 0.9, 1.1));
    
    setPoint3D(creatorNum);
    

    glPointSize(1);
    
    fullScreen = false;
    oneShot = false;
    bHide = true;
//    innerCircle = true;
    
    light.setAttenuation();
    light.setPosition(0,0,-1000);
    
    
}

//--------------------------------------------------------------
void ofApp::update(){
    
    if (reSetting) setPoint3D(numCreators);
    
}


//--------------------------------------------------------------
void ofApp::draw(){
    
    ofEnableDepthTest();
    
    cam.begin();
    
    if (innerCircle) {
        ofPushStyle();
        baseLunar.draw();
        ofPopStyle();
    }
    
    mesh.draw();
    darkMesh.draw();
    
    for (int i=0; i<point3D.size(); i++) {
        point3D[i].vbo.draw(GL_LINE_STRIP, 0, 36);
        
        ofPushStyle();
        ofSetColor(baseColor);
        ofLine(point3D[i].p2*0.9, point3D[i].p2*1.05);
        ofPopStyle();
    }
    
    arcDrawing();
    
    cam.end();
    
    ofPushStyle();
    ofSetColor(255);
    ofDrawBitmapString(ofToString(ofGetFrameRate(),1), 10, ofGetHeight()-15);
    ofPopStyle();
    
    if (bHide) {
        ofPushStyle();
        ofDisableDepthTest();
        gui.draw();
        ofPopStyle();
    }
    
    
    
}

//--------------------------------------------------------------
void ofApp::setPoint3D(int _num) {
    
    point3D.resize(_num);
    
    mesh.clear();
    darkMesh.clear();
    
    for (int i = 0; i < point3D.size(); i++){
        
        point3D[i].createrMesh.clear();
        
        point3D[i].radius = ofRandom(1-randomHeight, 1+randomHeight)*ofGetHeight()*0.4;
        //        point3D[i].radius = ofGetHeight()*0.4;
        
        point3D[i].theta = ofRandom(TWO_PI);
        point3D[i].phi = acos(2*ofRandom(1)-1);
        
        float _x = point3D[i].radius * cos(point3D[i].theta) * sin(point3D[i].phi);
        float _y = point3D[i].radius * cos(point3D[i].phi);
        float _z = point3D[i].radius * sin(point3D[i].theta) * sin(point3D[i].phi);
        
        ofVec3f _point3D = ofVec3f(_x, _y, _z);
        mesh.addVertex(_point3D);
        mesh.addNormal(_point3D);
        
        darkMesh.addVertex(_point3D);
        
        ofColor _c = ofColor(baseColor);
        mesh.addColor(_c);

        ofColor _cB = ofColor(0, 80);
        darkMesh.addColor(_cB);
        point3D[i].point3DRaw = _point3D;
        
        point3D[i].radiusCreater = ofRandom(20);
        
        point3D[i].p1 = ofVec3f(0,0,0);
        point3D[i].p2 = mesh.getVertex(i);
        point3D[i].createrMesh.setMode(OF_PRIMITIVE_LINE_STRIP);
        
        point3D[i].norm = (point3D[i].p2 - point3D[i].p1).normalize();
        
        point3D[i].u = point3D[i].norm.crossed(ofVec3f(1, 0, 0)); //x axis unit vector
        point3D[i].v = point3D[i].norm.crossed(point3D[i].u);
        
        for (int t = 0; t <= 360; t+=10) {
            float rad = ofDegToRad(t);
            ofVec3f pt = point3D[i].p2 + point3D[i].radiusCreater * cos(rad) * point3D[i].u + point3D[i].radiusCreater * sin(rad) * point3D[i].v;
            
            ofColor _c = ofColor(baseColor);
            point3D[i].createrMesh.addColor(_c);
            point3D[i].createrMesh.addVertex(pt);
            
            point3D[i].vbo.setMesh(point3D[i].createrMesh, GL_STATIC_DRAW);
        }
        
    }
    
    distance = 50;
    
    int numVerts = mesh.getNumVertices();
    for (int a = 0; a<numVerts; a++) {
        ofVec3f verta = mesh.getVertex(a);
        for (int b = a + 1; b<numVerts; b++) {
            ofVec3f vertb = mesh.getVertex(b);
            float _distanceM = verta.distance(vertb);
            if (_distanceM <= distance) {
                mesh.addIndex(a);
                mesh.addIndex(b);
            }
            if ((_distanceM < 100)&&(_distanceM > 50)) {
                darkMesh.addIndex(a);
                darkMesh.addIndex(b);
            }
        }
    }
    
    
    sphere.setRadius(point3D[0].radius*innerCircleSize);
    baseLunar = sphere.getMesh();
    for (int i=0; i<baseLunar.getNumVertices(); i++) {
        ofColor _c = ofColor(0, 150);
        baseLunar.addColor(_c);
    }

    
}


//--------------------------------------------------------------
void ofApp::arcDrawing(){
    
    ofPushStyle();
    ofSetColor(baseColor);
    
    for (int i=0; i<mesh.getNumVertices()-1; i+=2) {
        ofVec3f _startPoint = mesh.getVertex(i);
        ofVec3f _endPoint = mesh.getVertex(i+1);
        
        ofVec3f _middlePoint = ((_endPoint-_startPoint)*0.5).normalize();
        
        ofVec3f _norm = (_middlePoint - ofVec3f(0,0,0)).normalize();
        
        ofVec3f _u = _norm.crossed(ofVec3f(0, 0, 1)); //x axis unit vector
        ofVec3f _v = _norm.crossed(_u);
        
        ofVec3f _pt = _middlePoint * point3D[i].radius;
        
        ofLine(_pt, _startPoint);
        ofLine(_pt, _endPoint);
        
    }
    ofPopStyle();

    
}



//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    
    if(key=='f') {
        fullScreen = !fullScreen;
        ofSetFullscreen(fullScreen);
    }
    
    if( key == 's' ){
        oneShot = true;
    }
    
    if (key == 'h') bHide = !bHide;
    
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
    
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){
    
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){
    
}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){
    
}
