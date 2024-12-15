#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(25);
	ofSetWindowTitle("openFrameworks");

	ofBackground(39);

	ofEnableBlendMode(ofBlendMode::OF_BLENDMODE_ADD);
}

//--------------------------------------------------------------
void ofApp::update() {

	this->mesh.clear();

	if (ofGetFrameNum() % 50 < 30) {

		this->noise_step += ofMap(ofGetFrameNum() % 50, 0, 30, 0.1, 0);
	}

	float size = 2;
	ofColor color;
	for (float x = -300; x <= 300; x += size) {

		for (float y = -300; y <= 300; y += size) {

			float deg = ofMap(ofNoise(x * 0.0025, y * 0.0025, this->noise_step), 0, 1, -360 * 2, 360 * 2);
			this->mesh.addVertex(glm::vec3(
				x + size * 6 * cos(deg * DEG_TO_RAD),
				y + size * 6 * sin(deg * DEG_TO_RAD),
				0));

			color.setHsb((int)ofMap(x, -300, 300, 128, 255 + 128) % 255, 200, 80);
			this->mesh.addColor(color);
		}
	}
}

//--------------------------------------------------------------
void ofApp::draw() {

	this->cam.begin();
	ofRotateZ(ofGetFrameNum() * 1.44);

	this->mesh.drawVertices();

	this->cam.end();

	/*
	int start = 500;
	if (ofGetFrameNum() > start) {

		ostringstream os;
		os << setw(4) << setfill('0') << ofGetFrameNum() - start;
		ofImage image;
		image.grabScreen(0, 0, ofGetWidth(), ofGetHeight());
		image.saveImage("image/cap/img_" + os.str() + ".jpg");
		if (ofGetFrameNum() - start >= 25 * 20) {

			std::exit(1);
		}
	}
	*/
}


//--------------------------------------------------------------
int main() {
	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}