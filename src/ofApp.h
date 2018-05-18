#pragma once

#include "ofMain.h"
#include "ncGeoFunctions.h"

#define NUM_BANDS 4



struct Pano {
    string pano_id;
    string depthmap;
};

struct PanoTile {
    int x;
    int y;
    ofImage image;
};

struct DepthMapPlane {
    //normal vector
    float x, y, z;
    //distance to camera
    float d;
};

class ofApp : public ofBaseApp{
    
public:
    void setup();
    void update();
    void draw();
    
    void keyPressed(int key);
    void urlResponse(ofHttpResponse & response);
    
    Pano pano;
    
    void constructPanoImage();
    float zoom;
    int imagecounter;
    int totalimages;
    ofFbo panoimage;
    vector<PanoTile> panoTiles;
    
    void constructDepthMap();
    ofImage depthmapimage;
    vector<float> depthmap;
    
    void constructPointCloud();
    ofMesh pointcloud;
    
    ofEasyCam cam;
    
    
    ofSoundPlayer myTrack;
    
    float *spectrum;
    
    bool started = false;
//    ofVec3f startValues;
    
//    float startValues[1000];
    string latOutput;
    string lonOutput;
    float pos;
    
    vector <ofVec3f> startValues;

};
