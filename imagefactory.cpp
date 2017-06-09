#include "imagefactory.h"

ImageFactory::ImageFactory() {
}

Image *ImageFactory::createImage(QString path) {
    FileInfo *info = new FileInfo(path);
    Image *img;
    if(info->getType() == ANIMATED) {
        img = new ImageAnimated(path);
    } else if(info->getType() == VIDEO) {
        img = new Video(path);
    } else {
        img = new ImageStatic(path);
    }
    img->load();
    delete info;
    return img;
}

Image *ImageFactory::createImage(FileInfo *info) {
    Image *img;
    if(info->getType() == ANIMATED) {
        img = new ImageAnimated(info->filePath());
    } else if(info->getType() == VIDEO) {
        img = new Video(info->filePath());
    } else {
        img = new ImageStatic(info->filePath());
    }
    img->load();
    delete info;
    return img;
}
