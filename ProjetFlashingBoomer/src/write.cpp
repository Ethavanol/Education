/*#include "write.h"

write::write():
    WritingPosX(0),
    WritingPosY(0),
    WritingWidth(300),
    WritingHeight(300),
    srcRectWritingZone{int(WritingPosX), int(WritingPosY), int(WritingWidth), int (WritingHeight)}
{}

write::write(unsigned int x, unsigned int y, unsigned int w, unsigned int h):
    WritingPosX(x),
    WritingPosY(y),
    WritingWidth(w),
    WritingHeight(h),
    srcRectWritingZone{int(WritingPosX), int(WritingPosY), int(WritingWidth), int (WritingHeight)}
{}

write::~write()
{
}


    // ----> Accesseurs


unsigned int write::getWritingPosX() const{
    return WritingPosX;
}

unsigned int write::getWritingPosY() const{
    return WritingPosY;
}


int write::getWritingWidth() const{
    return WritingWidth;
}

int write::getWritingHeight() const{
    return WritingHeight;
}

SDL_Rect& write::getsrcRectWritingZone(){
    return srcRectWritingZone;
}


    // -----> Mutateurs


void write::setWritingPosX(unsigned int value){
    WritingPosX = value;
}

void write::setWritingPosY(unsigned int value){
    WritingPosY = value;
}

void write::setWritingWidth(int value){
    WritingWidth = value;
}

void write::setWritingHeight(int value){
    WritingHeight = value;
}*/