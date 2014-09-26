// http://en.wikibooks.org/wiki/Mathematica/Uniform_Spherical_Distribution
// http://mathworld.wolfram.com/SpherePointPicking.html
// http://mathworld.wolfram.com/SphericalCoordinates.html
// http://forum.openframeworks.cc/t/vector-maths-cross-vectors-and-a-circle-on-a-sphere/15760/9

#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

	ofBackground(10);

	mesh.setMode(OF_PRIMITIVE_LINES);
	glPointSize(1);

	point3D.resize(1000);
	point3DRaw.resize(point3D.size());

	for (int i = 0; i < point3D.size(); i++){
		point3D[i].length = 300;
		point3D[i].degree3D = ofPoint(acos(2*ofRandom(1)-1), ofRandom(TWO_PI), ofRandom(360));

		float _x = point3D[i].length * cos(point3D[i].degree3D.y) * sin(point3D[i].degree3D.x);
        float _y = point3D[i].length * cos(point3D[i].degree3D.x);
		float _z = point3D[i].length * sin(point3D[i].degree3D.y) * sin(point3D[i].degree3D.x);

        ofVec3f _point3D = ofVec3f(_x, _y, _z);
		mesh.addVertex(_point3D);
        mesh.addNormal(_point3D);

		ofColor _c = ofColor(255, 70);
		mesh.addColor(_c);
		point3DRaw[i] = _point3D;
        
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
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){

	cam.begin();
	
	mesh.draw();

    ofLine( mesh.getVertex(0), ofVec3f(0,0,0) );

    ofVec3f p1 = ofVec3f(0,0,0);
    ofVec3f p2 = mesh.getVertex(0);
    
    ofVec3f norm = (p2 - p1).normalize();
    
    ofVec3f u = norm.crossed(ofVec3f(1, 0, 0)); //x axis unit vector
    ofVec3f v = norm.crossed(u);
    
    sphere.setRadius(2);
    
    float r = 50;
    
    for (int t = 0; t < 360; t += 10) {
        float rad = ofDegToRad(t);
        ofVec3f pt = p2 + r * cos(rad) * u + r * sin(rad) * v;
        sphere.setPosition(pt);
        sphere.draw();
    }
    
    cam.end();

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

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
