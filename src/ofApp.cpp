// http://en.wikibooks.org/wiki/Mathematica/Uniform_Spherical_Distribution
// http://mathworld.wolfram.com/SpherePointPicking.html
// http://mathworld.wolfram.com/SphericalCoordinates.html
// http://forum.openframeworks.cc/t/vector-maths-cross-vectors-and-a-circle-on-a-sphere/15760/9



#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

	ofBackground(10);

    ofEnableDepthTest();
//    ofEnableBlendMode(OF_BLENDMODE_ADD);
    
	mesh.setMode(OF_PRIMITIVE_LINES);
    baseLunar.setMode(OF_PRIMITIVE_TRIANGLES);
    
	glPointSize(1);

	point3D.resize(2500);

	for (int i = 0; i < point3D.size(); i++){
        
//		point3D[i].length = ofRandom(0.95,1.01)*ofGetHeight()*0.4;
        point3D[i].length = ofGetHeight()*0.4;
		point3D[i].degree3D = ofPoint(acos(2*ofRandom(1)-1), ofRandom(TWO_PI), ofRandom(360));

		float _x = point3D[i].length * cos(point3D[i].degree3D.y) * sin(point3D[i].degree3D.x);
        float _y = point3D[i].length * cos(point3D[i].degree3D.x);
		float _z = point3D[i].length * sin(point3D[i].degree3D.y) * sin(point3D[i].degree3D.x);

        ofVec3f _point3D = ofVec3f(_x, _y, _z);
		mesh.addVertex(_point3D);
        mesh.addNormal(_point3D);

		ofColor _c = ofColor(255, 80);
		mesh.addColor(_c);
		point3D[i].point3DRaw = _point3D;
        
        point3D[i].radiusCreater = ofRandom(20);
        
        point3D[i].p1 = ofVec3f(0,0,0);
        point3D[i].p2 = mesh.getVertex(i);
        point3D[i].createrMesh.setMode(OF_PRIMITIVE_LINE_STRIP);

        point3D[i].norm = (point3D[i].p2 - point3D[i].p1).normalize();
        
        point3D[i].u = point3D[i].norm.crossed(ofVec3f(1, 0, 0)); //x axis unit vector
        point3D[i].v = point3D[i].norm.crossed(point3D[i].u);

        for (int t = 0; t <= 360; t += 10) {
            float rad = ofDegToRad(t);
            ofVec3f pt = point3D[i].p2 + point3D[i].radiusCreater * cos(rad) * point3D[i].u + point3D[i].radiusCreater * sin(rad) * point3D[i].v;

            ofColor _c = ofColor(255, 120);
            point3D[i].createrMesh.addColor(_c);
            point3D[i].createrMesh.addVertex(pt);
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
		}
	}
    
    sphere.setRadius(point3D[0].length*0.99);
    baseLunar = sphere.getMesh();
    cout << baseLunar.getNumVertices() << endl;
    for (int i=0; i<baseLunar.getNumVertices(); i++) {
        ofColor _c = ofColor(0, 150);
        baseLunar.addColor(_c);
    }
    
}

//--------------------------------------------------------------
void ofApp::update(){

    
}

//--------------------------------------------------------------
void ofApp::draw(){

    cam.begin();
	
    ofPushStyle();
    baseLunar.draw();
    ofPopStyle();
    
	mesh.draw();

    for (int i=0; i<point3D.size(); i++) {
        point3D[i].createrMesh.draw();
        ofPushStyle();
        ofSetColor(255, 70);
        ofLine(point3D[i].p2*0.9, point3D[i].p2*1.05);
        ofPopStyle();
    }

    cam.end();
    
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

    if(key=='f') fullScreen = !fullScreen;
    ofSetFullscreen(fullScreen);

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
