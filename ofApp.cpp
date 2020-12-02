#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(60);
	ofSetWindowTitle("openframeworks");

	ofBackground(239);
	ofEnableDepthTest();

	ofColor color;
	vector<int> hex_list = { 0xef476f, 0xffd166, 0x06d6a0, 0x118ab2, 0x073b4c };
	for (auto hex : hex_list) {

		color.setHex(hex);
		this->base_color_list.push_back(color);
	}
}

//--------------------------------------------------------------
void ofApp::update() {

	ofSeedRandom(39);
}

//--------------------------------------------------------------
void ofApp::draw() {

	this->cam.begin();
	ofRotateX(ofGetFrameNum() * 0.83);
	ofRotateY(ofGetFrameNum() * 1.3);
	
	int size = 60;
	for (int x = -300; x <= 300; x += size) {

		for (int y = -300; y <= 300; y += size) {

			for (int z = -300; z <= 300; z += size) {

				int color_index = (int)ofRandom(this->base_color_list.size());
				ofSetColor(this->base_color_list[color_index]);
				ofFill();

				auto noise_value = ofNoise(x * 0.002, y * 0.002, z * 0.002 + ofGetFrameNum() * 0.04);
				if (noise_value < 0.5) {

					ofDrawBox(glm::vec3(x, y, z), size);

					ofSetColor(239);
					ofNoFill();
					ofDrawBox(glm::vec3(x, y, z), size);
				}
				else {

					ofDrawSphere(glm::vec3(x, y, z), size * 0.45);
				}
			}
		}
	}

	this->cam.end();
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}