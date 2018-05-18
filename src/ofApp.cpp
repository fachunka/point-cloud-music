#include "ofApp.h"
#include "base64.h"
#include <zlib.h>

//--------------------------------------------------------------
void ofApp::setup(){

    ofBackground(0);
    
    ofRegisterURLNotification(this);
    
    //convert address to lat/lon coordinates
//    vector<float> latlon = GoogleAddressToLatLon("gent vlasmarkt");
//    vector<float> latlon = GoogleAddressToLatLon("60.1790644,24.8286318"); Alepa Otaniemi
    vector<float> latlon = GoogleAddressToLatLon("60.1840697,24.8304777");
    latOutput = ofToString(latlon[0]);
    lonOutput = ofToString(latlon[1]);
    pos = 0;

    cout << latOutput << endl;

    
    //load google data from lat/lon
    ofHttpRequest request = ofHttpRequest("http://cbk0.google.com/cbk?output=xml&ll=" + ofToString(latlon[0]) + "," + ofToString(latlon[1]) + "&dm=1","");
    ofLoadURLAsync(request.url, "google_data_request");
    
    cam.setNearClip(0.01f);
    cam.setDistance(2);
    cam.tilt(180);
    cam.setPosition(0,0,0);
    cam.roll(4);
    
    
    myTrack.load("danyankeyintheforest.mp3");
//    myTrack.load("InnerCircleSweatSweatboxConstruction.mp3");
//    myTrack.load("PFMThewesternMikesricochetmix.mp3");

    myTrack.play();
//    ofBackground(0);
    

    
}

//--------------------------------------------------------------
void ofApp::update(){
    
    spectrum = ofSoundGetSpectrum(NUM_BANDS);
    
    if (started == false && pointcloud.getVertices().size() > 0) {
        //        cout << pointcloud.getVertices().size() << endl;
        
        for(int i = 0; i< pointcloud.getVertices().size(); i++){
            //              cout << pointcloud.getVertex(i).x << endl;
            //            ofVec3f test;
            
            ofVec3f startV = pointcloud.getVertex(i);
            //            cout << startV.x << endl;
            //            printf("%f", startV.x);

            startValues.push_back(startV);
            
        }
        
        started = true;
        
    }


}

//--------------------------------------------------------------
void ofApp::draw(){
    
    
//    panoimage.draw(0,0,512,256);
//    depthmapimage.draw(0,256, 512, 256);

    cam.begin();
    
    
    if (started == true && pointcloud.getVertices().size() > 0) {


        for(int i = 0; i< startValues.size(); i++){
            
            if (i % 2 == 0) {
                
        //        cout << pointcloud.getVertex(i).x << endl;
        //        cout << startValues.size() << endl;
                
                ofVec3f test;
                ofVec3f getV = startValues[i];
                
        //        float color = pointcloud.getColor(i).r;
        //        cout << color << endl;
        //        cout << typeid(getV.x).name() << endl;
        //        cout << typeid(spectrum[i]).name() << endl;

                float speccy = ofMap(spectrum[0], 0,1,0,ofGetHeight());

        //        cout << speccy << endl;
        //        float nearest = roundf(spectrum[3] * 100) / 100;


                float speccyGetx = (getV.x *= speccy)/1000;
                float speccyGety = (getV.y *= speccy)/1000;
                float speccyGetz = (getV.z *= speccy)/1000;

        //        cout << speccyGetx << endl;
        //        getV.x += 2.0f;

                test.set(speccyGetx, speccyGety, speccyGetz);

                pointcloud.setVertex(i, test);
            }
            
            else if (i % 2 == 1) {
                ofVec3f test;
                ofVec3f getV = startValues[i];
                
                float speccy = ofMap(spectrum[1], 0,1,0,ofGetHeight());
                
                float speccyGetx = (getV.x *= speccy)/1000;
                float speccyGety = (getV.y *= speccy)/1000;
                float speccyGetz = (getV.z *= speccy)/1000;
                
                test.set(speccyGetx, speccyGety, speccyGetz);
                
                pointcloud.setVertex(i, test);
            }
//            else if (i % 4 == 2) {
//                ofVec3f test;
//                ofVec3f getV = startValues[i];
//
//                float speccy = ofMap(spectrum[2], 0,1,0,ofGetHeight());
//
//                float speccyGetx = (getV.x *= speccy)/1000;
//                float speccyGety = (getV.y *= speccy)/1000;
//                float speccyGetz = (getV.z *= speccy)/1000;
//
//                test.set(speccyGetx, speccyGety, speccyGetz);
//
//                pointcloud.setVertex(i, test);
//            }
//            else if (i % 4 == 3) {
//                ofVec3f test;
//                ofVec3f getV = startValues[i];
//
//                float speccy = ofMap(spectrum[3], 0,1,0,ofGetHeight());
//
//                float speccyGetx = (getV.x *= speccy)/1000;
//                float speccyGety = (getV.y *= speccy)/1000;
//                float speccyGetz = (getV.z *= speccy)/1000;
//
//                test.set(speccyGetx, speccyGety, speccyGetz);
//
//                pointcloud.setVertex(i, test);
//            }
        }
    }
    
    
    pointcloud.drawVertices();


    
    
    cam.end();
    

    float heading = cam.getHeadingDeg();
    ofVec3f position = cam.getPosition();
    

    ofDrawBitmapString("Direction: " + ofToString(heading), 20 , 20);
    ofDrawBitmapString("Position: " + ofToString( position), 20 , 40);
    ofDrawBitmapString("Latitude: " + ofToString(latOutput), 20 , 60);
    ofDrawBitmapString("Longitude: " + ofToString(lonOutput), 20 , 80);


    
    

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    
    if (key == '1'){
        //        cam.setPosition(10,50,0);
        float one = 1.0;
        cam.rotate(one, one, one, one);
        //        cam.setTarget(0,0,1);
    }
    if (key == '2'){
        //        cam.setPosition(50,50,50);
        cam.tilt(pos++);
        //        cam.setTarget(0,0,1);
    }
    if (key == '3'){
        //        cam.setPosition(50,50,0);
        cam.pan(3);
        if(pos >= 10){
            pos = 0;
        }

        //        cam.setTarget(0,0,1);
    }
    if (key == '4'){
        cam.roll(pos++);
        //        cam.setTarget(0,0,1);
    }
    if (key == '5'){

        //        cam.(30, cam.getUpDir());
        //        cam.setTarget(0,0,1);
    }
    if (key == '6'){
        //        cam.setPosition(0,pos++,0);
        //        cam.begin();
        //        streetview.draw();
        //        cam.end();


    }
    if (key == '7'){
        //        float set = 1.0;
        ofVec3f Znormal(0, 0, pos++);
        ofVec3f Xnormal(1, 0, 0);
        ofVec3f Ynormal(1, 0, 1);
        ofQuaternion so (Znormal);
        cam.setOrientation(so);
    }

    if (key == '8'){
        //        float set = 1.0;
        ofVec3f Znormal(0, 0, pos--);
        ofVec3f Xnormal(1, 0, 0);
        ofVec3f Ynormal(1, 0, 1);
        ofQuaternion so (Znormal);
        cam.setOrientation(so);
    }
    if (key == '9'){
        pos = 0;
        cam.tilt(90);
//        cam.setPosition(0,0,0);
    }

    if (key == '0'){
    }
    

}


//--------------------------------------------------------------
void ofApp::urlResponse(ofHttpResponse & response) {
    
    if (response.status == 200) {
        
        if (response.request.name == "google_data_request") {
            ofxXmlSettings  XML;
            XML.loadFromBuffer(response.data);
            pano.pano_id = XML.getAttribute("panorama:data_properties", "pano_id", "");
            pano.depthmap = XML.getValue("panorama:model:depth_map", "");
            
            constructPanoImage();
            
        } else if (ofIsStringInString(response.request.name, "TILE")){
            vector<string> split = ofSplitString(response.request.name, "_");
            ofImage im;
            im.load(response.data);
            PanoTile tile;
            tile.x = ofToInt(split[1]);
            tile.y = ofToInt(split[2]);
            tile.image = im;
            panoTiles.push_back(tile);
            imagecounter++;
        }
    } else {
        if (ofIsStringInString(response.request.name, "TILE")) {
            imagecounter++;
        }
    }
    
    if (ofIsStringInString(response.request.name, "TILE")) {
        if (imagecounter == totalimages) {
            
            
            float w = 416 * pow(2, zoom);
            float h = (416 * pow(2, zoom - 1));
            ofFbo firstpass;
            
            firstpass.allocate(w, h);
            firstpass.begin();
            ofPushMatrix();
            ofTranslate(w, 0, 0);
            ofScale(-1, 1, 0);
            ofClear(0);
            for (int i = 0; i < panoTiles.size(); i++) {
                panoTiles[i].image.draw(panoTiles[i].x * 512, panoTiles[i].y * 512);
            }
            ofPopMatrix();
            firstpass.end();
            
            panoimage.allocate(512, 256);
            ofClear(0);
            panoimage.begin();
            firstpass.draw(0, 0, 512, 256);
            panoimage.end();
            
            //create the depthmap
            constructDepthMap();
            
            //create the point cloud
            constructPointCloud();
        }
    }
}

//--------------------------------------------------------------
void ofApp::constructPanoImage() {
//    load the tiles
    zoom = 1.0f;

    int w = pow(2, zoom);

    float h = pow(2, zoom - 1);

    imagecounter = 0;

    totalimages = w*h;

    for (int y = 0; y < h; y++) {

        for (int x = 0; x < w; x++) {
            string url = "http://maps.google.com/cbk?output=tile&panoid="+pano.pano_id+"&zoom=" + ofToString(zoom) + "&x=" + ofToString(x) + "&y=" + ofToString(y);
            ofLoadURLAsync(url, "TILE_" + ofToString(x) + "_" + ofToString(y));
        }
    }
}


//--------------------------------------------------------------
void ofApp::constructDepthMap() {
    
    vector<unsigned char> depth_map_compressed(pano.depthmap.length());
    int compressed_length = decode_base64(&depth_map_compressed[0], &pano.depthmap[0]);

    //Uncompress data with zlib
    //TODO: decompress in a loop so we can accept any size
    unsigned long length = 512 * 256 + 5000;
    vector<unsigned char> depth_map(length);
    int zlib_return = uncompress(&depth_map[0], &length, &depth_map_compressed[0], compressed_length);


    if (zlib_return != Z_OK) {
     cout<<"unable to decompress depthmap"<<endl;
     return;
     }

    //Load standard data
    int headersize = depth_map[0];
    int numberofplanes = depth_map[1] | (depth_map[2] << 8);
    int width = depth_map[3] | (depth_map[4] << 8);
    int height = depth_map[5] | (depth_map[6] << 8);
    int offset = depth_map[7];

    if (headersize != 8 || offset != 8) {
        cout<<"Unexpected depth map header "<<endl;
        return;
    }

    //the values in this vector correspondent to a planeId this pixel belongs to
    //depthMapIndices
    vector <unsigned char> depthmapIndices = vector<unsigned char>(height * width);
    memcpy(&depthmapIndices[0], &depth_map[offset], height * width);

    //depthMapPlanes
    vector<DepthMapPlane> depthmapPlanes = vector<DepthMapPlane>(numberofplanes);
    memcpy(&depthmapPlanes[0], &depth_map[offset + height * width], numberofplanes * sizeof(struct DepthMapPlane));

    //CREATE THE ACTUAL DEPTHMAP
    depthmap.clear();
    depthmap.resize(width*height);

    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {

            float xnormalize = (width-x-1.0f)/(width-1.0f);
            float ynormalize =(height-y-1.0f)/(height-1.0f);

            float theta = xnormalize * (2 * PI) + (PI / 2);
            float phi = ynormalize * PI;

            //convert from spherical to cartesian coordinates
            vector<float> v;
            v.resize(3);
            v[0] = sin(phi) * cos(theta);
            v[1] = sin(phi) * sin(theta);
            v[2] = cos(phi);

            int planeIdx = depthmapIndices[y*width + x];

            if (planeIdx > 0) {
                DepthMapPlane plane = depthmapPlanes[planeIdx];
                float t = abs(plane.d / (v[0] * plane.x + v[1] * plane.y + v[2] * plane.z));
                depthmap[y*width + (width - x - 1)] = t;
            }
            else {
                depthmap[y*width + (width - x - 1)] = 0.0f;
            }
        }
    }

    ofPixels depthPixels;
    depthPixels.allocate(width, height, 1);

    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            float c = depthmap[y*width + x] / 100 * 255;
            depthPixels[y*width + x] = c;
        }
    }

    depthmapimage.setFromPixels(depthPixels);
}


//--------------------------------------------------------------
void ofApp::constructPointCloud() {
    
    pointcloud.setMode(OF_PRIMITIVE_POINTS);
    
    int width = depthmapimage.getWidth();
    int height = depthmapimage.getHeight();
    
    ofPixels mypixels;
    mypixels.allocate(width, height, OF_IMAGE_COLOR_ALPHA);
    panoimage.readToPixels(mypixels);
    
    for (int y = 0; y < height; y++) {
        
//        printf("y %i \n", y);
//        if (y % 4 == 0) {

        
            for (int x = 0; x < width; x++) {
                
//                if (x % 4 == 0) {
                
    //            printf("x %i \n", x);
                
                float xnormalize = (width-x-1.0f)/(width-1.0f);
                float ynormalize =(height-y-1.0f)/(height-1.0f);
                
                float theta = xnormalize * (2 * PI) + (PI / 2);
                float phi = ynormalize * PI;
                
                float depth = depthmap[y*width + x];
                
                ofVec3f pos;
                pos.x = sin(phi) * cos(theta);
                pos.y = sin(phi) * sin(theta);
                pos.z = cos(phi);
                
                //            for (int i = 0; i < NUM_BANDS; i++) {
    //            float spectrumi = spectrum[x] * 10;
                
                //                printf("pos %f \n", pos);
                //                printf("depth %f \n", depth);
                
    //            cout << pos << endl;
    //            cout << depth << endl;
                
                
                if (depth != 0) {
                    pos = pos*depth;
                    
                }
                //            else if (depth > 100723200){
                //                pos = pos*100605696.0f;
                //            }
                
                else {
                    pos = pos*100.0f;
                }
                
                
                
                //            }
                
                
                pointcloud.addVertex(pos);
                int r = (int)mypixels[4 * (y*width + x)];
                int g = (int)mypixels[4 * (y*width + x) + 1];
                int b = (int)mypixels[4 * (y*width + x) + 2];
                
                pointcloud.addColor(ofColor(r, g, b, 255));
                
                }
//            }
        }
//    }
   
}
