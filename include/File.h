//
// Created by adirm on 21.06.2020.
//

using namespace std;

#include <cstdint>
#include <vector>
#include <string>

#ifndef RADMOR_FILE_H
#define RADMOR_FILE_H

typedef unsigned char octet;
typedef vector<octet> OctetSequence;

class File {
protected:
    string fileName_;
    uint32_t filePointer_ = 0;

public:
    virtual void readFile(OctetSequence *&data, const uint32_t &length) = 0;
    virtual void writeFile(OctetSequence *data) = 0;
    virtual uint32_t sizeOf() = 0;
    virtual void closeFile() = 0;
    virtual void setFilePointer(const uint32_t &filePointer) = 0;

    string fileName () const { return fileName_; };
    uint32_t filePointer () const { return filePointer_; };
};

#endif //RADMOR_FILE_H
