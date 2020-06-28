//
// Created by adirm on 22.06.2020.
//

#ifndef RADMOR_FILEIMPL_H
#define RADMOR_FILEIMPL_H

#include "File.h"

class FileImpl : public File {
    int fileDescriptor;

    static void throwException(int errorCode);

public:
    FileImpl(const char *pathToFile, bool readOnly);
    void readFile(OctetSequence *&data,const uint32_t &length) override;
    void writeFile(OctetSequence *data) override;
    uint32_t sizeOf() override;
    void closeFile() override;
    void setFilePointer(const uint32_t &filePointer) override;
};

#endif //RADMOR_FILEIMPL_H
