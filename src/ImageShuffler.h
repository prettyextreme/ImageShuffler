#pragma once

#define FOR_RETINA

#include "ofMain.h"

struct ImgSector{
    int w;
    int h;
    int x;
    int y;
    int r;
    int g;
    int b;
    int hue;
    int brt;
    int imgX;
    int imgY;
    ImgSector* related;
    ImgSector* next;
    ImgSector* prev;
    ImgSector(){
        related = NULL;
        next = NULL;
        prev = NULL;
    }
};

class ImgSectorList{
public:
    ImgSectorList(){
        for(int i=0;i<256;i++){
            first[i]=NULL;
            count[i]=0;
        }
    }
    ImgSector* first[256];
    int count[256];
    
    void pushSector(ImgSector* sector){
        int index = sector->brt;
        if(first[index]==NULL){
            first[index] = sector;
        } else {
            first[index]->prev = sector;
            sector->next = first[index];
            first[index] = sector;
        }
        count[index]++;
    }
};

class ImageShuffler : public ofBaseApp{
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
    
    ofImage srcImg;
    ofImage dstImg;
    unsigned char* srcPx;
    unsigned char* dstPx;
    
    int masterSectorDim;
    
    ImgSector* getSector(unsigned char* pix, int pixW, int sectorX, int sectorY, int sectorW, int sectorH);
    
    void analyzeSectors(ImgSectorList& sectorList, unsigned char* pix, int pixW, int pixH, int sectorDim);
    
    ImgSectorList srcList;
    ImgSectorList dstList;
};
