#include "ImageShuffler.h"

//--------------------------------------------------------------
void ImageShuffler::setup(){
    srcImg.loadImage("1.jpg");
    dstImg.loadImage("2.jpg");
    
    srcPx = srcImg.getPixels();
    dstPx = dstImg.getPixels();
    
    masterSectorDim = 8;
    
    analyzeSectors(srcList,srcPx,srcImg.width,srcImg.height,masterSectorDim);
    analyzeSectors(dstList,dstPx,dstImg.width,dstImg.height,masterSectorDim);
    
    
    //pair them up!
    int drawCount = 0;
    int dstListIndex = 0;
    ImgSector* dstSector = dstList.first[dstListIndex];
    
    
    for (int i=0; i<256; i++) {
        
        
        ImgSector* next = srcList.first[i];
        while(next){
            
            while(dstSector == NULL){
                dstListIndex++;
                dstSector = dstList.first[dstListIndex];
            }
            
            /*
            srcImg.drawSubsection((drawCount*masterSectorDim)%srcImg.width,
                                  (drawCount*masterSectorDim)/srcImg.width*masterSectorDim,
                                  masterSectorDim, masterSectorDim, next->imgX, next->imgY);
            */
            next->related = dstSector;
            dstSector->related = next;
            
            next = next->next;
            dstSector = dstSector->next;
            drawCount++;
        }
    }
    
    
    
    
    
    
}

//--------------------------------------------------------------
void ImageShuffler::update(){

}

//--------------------------------------------------------------
void ImageShuffler::draw(){

#ifdef FOR_RETINA
    ofViewport(ofRectangle(0,-ofGetHeight(),ofGetWidth()*2,ofGetHeight()*2));
#endif
    
    //ofScale(0.5, 0.5);
    srcImg.draw(0, 0);
    
    ofPushMatrix();
    ofTranslate(512, 0);
    int drawCount = 0;
    for (int i=0; i<256; i++) {
        ImgSector* next = srcList.first[i];
        while(next){
            /*
            srcImg.drawSubsection((drawCount*masterSectorDim)%srcImg.width,
                                  (drawCount*masterSectorDim)/srcImg.width*masterSectorDim,
                                  masterSectorDim, masterSectorDim, next->imgX, next->imgY);
             */
            dstImg.drawSubsection(next->imgX,
                                  next->imgY,
                                  masterSectorDim, masterSectorDim, next->related->imgX, next->related->imgY);
            next = next->next;
            drawCount++;
        }
    }
    ofPopMatrix();
    
    
    dstImg.draw(0, 512);
    
    ofPushMatrix();
    ofTranslate(512, 512);
    drawCount = 0;
    for (int i=0; i<256; i++) {
        ImgSector* next = dstList.first[i];
        while(next){
            /*
             srcImg.drawSubsection((drawCount*masterSectorDim)%srcImg.width,
             (drawCount*masterSectorDim)/srcImg.width*masterSectorDim,
             masterSectorDim, masterSectorDim, next->imgX, next->imgY);
             */
            srcImg.drawSubsection(next->imgX,
                                  next->imgY,
                                  masterSectorDim, masterSectorDim, next->related->imgX, next->related->imgY);
            next = next->next;
            drawCount++;
        }
    }
    ofPopMatrix();
    
    
    


}

void ImageShuffler::analyzeSectors(ImgSectorList& sectorList, unsigned char* pix, int pixW, int pixH, int sectorDim){
    
    for(int y = 0;y<pixH;y+=sectorDim){
        for(int x = 0;x<pixW;x+=sectorDim){
            
            sectorList.pushSector(getSector(pix, pixW, x, y, sectorDim, sectorDim));
        }
    }

}


ImgSector* ImageShuffler::getSector(unsigned char* pix, int pixW, int sectorX, int sectorY, int sectorW, int sectorH){
    ImgSector* newSector = new ImgSector();

    //Find the average color
    long totalR = 0;
    long totalG = 0;
    long totalB = 0;
    
    for (int y = sectorY; y < sectorY+sectorH; y++) {
        for (int x = sectorX; x < sectorX+sectorW;x++){
            unsigned char* pxptr = pix + 3*(y*pixW+x);
            totalR += pxptr[0];
            totalG += pxptr[1];
            totalB += pxptr[2];
        }
    }
    
    newSector->r = totalR/(sectorW*sectorH);
    newSector->g = totalG/(sectorW*sectorH);
    newSector->b = totalB/(sectorW*sectorH);
    
    ofColor c(newSector->r,newSector->g,newSector->b);
    newSector->hue = c.getHue();
    newSector->brt = c.getBrightness();
    newSector->imgX = sectorX;
    newSector->imgY = sectorY;
    
    return newSector;
}

//--------------------------------------------------------------
void ImageShuffler::keyPressed(int key){

}

//--------------------------------------------------------------
void ImageShuffler::keyReleased(int key){

}

//--------------------------------------------------------------
void ImageShuffler::mouseMoved(int x, int y){

}

//--------------------------------------------------------------
void ImageShuffler::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ImageShuffler::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ImageShuffler::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ImageShuffler::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ImageShuffler::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ImageShuffler::dragEvent(ofDragInfo dragInfo){ 

}