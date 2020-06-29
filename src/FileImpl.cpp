//
// Created by adirm on 22.06.2020.
//

#include "../include/Exceptions.h"
#include <fcntl.h>
#include "FileImpl.h"
#include <sys/types.h>
#include <unistd.h>

FileImpl::FileImpl(const char *pathToFile, bool readOnly) {
    int openMode = readOnly ? O_RDONLY : O_RDWR;
    this->fileDescriptor = open(pathToFile, openMode);

    if(this->fileDescriptor == -1) {
        int errorCode = errno;
        throwException(errorCode);
    }
}

void FileImpl::readFile(OctetSequence *&data, const uint32_t &length) {
    bool tryReadMoreThanExist = (length + this->filePointer()) > this->sizeOf();
    uint32_t lengthOfTextToRead = tryReadMoreThanExist ? this->sizeOf() - this->filePointer() : length;

    ssize_t bytesRead = read(this->fileDescriptor, data->data(), lengthOfTextToRead);

    if(bytesRead == -1) {
        int errorCode = errno;
        throwException(errorCode);
    }
}

void FileImpl::writeFile(OctetSequence *data) {
    ssize_t writeBytes = write(this->fileDescriptor, data->data(), data->size());

    if(writeBytes == -1) {
        int errorCode = errno;
        throwException(errorCode);
    }
}

uint32_t FileImpl::sizeOf() {
    long size = lseek(this->fileDescriptor, 0, SEEK_END);
    lseek(this->fileDescriptor, this->filePointer_, SEEK_SET);

    return size;
}

void FileImpl::closeFile() {
    int status = close(this->fileDescriptor);

    if(status == -1) {
        int errorCode = errno;
        throwException(errorCode);
    }
}

void FileImpl::setFilePointer(const uint32_t &filePointer) {
    int status = lseek(this->fileDescriptor, filePointer, SEEK_SET);
    if(status == -1) {
        int errorCode = errno;
        throwException(errorCode);
    }

    if(filePointer > this->sizeOf()) throw new InvalidFilePointer();
    this->filePointer_ = filePointer;
}