//
// Created by adirm on 22.06.2020.
//

#ifndef RADMOR_FILEIMPL_H
#define RADMOR_FILEIMPL_H

#include "File.h"
#include <string>

class FileImpl : public File {
    int fileDescriptor;
    off_t size;
public:
    FileImpl(const char *pathToFile, bool readOnly);
    virtual void readFile(OctetSequence *&data,const uint32_t &length);
    virtual void writeFile(OctetSequence *data);
    virtual uint32_t sizeOf();
    virtual void closeFile();
    virtual void setFilePointer(const uint32_t &filePointer);
};

#endif //RADMOR_FILEIMPL_H
