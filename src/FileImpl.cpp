//
// Created by adirm on 22.06.2020.
//

#include <iostream>
#include "FileImpl.h"
#include <unistd.h>
#include <sys/types.h>
#include "../include/Exceptions.h"
#include <vector>
#include <fcntl.h>

FileImpl::FileImpl(const char *pathToFile, bool readOnly) {
    int openMode = readOnly ? O_RDONLY : O_RDWR;
    this->fileDescriptor = open(pathToFile, openMode);

    if(this->fileDescriptor == -1) throw new IOException(CF_EIO, "Open Failed");

    // number of characters in file
    this->size = lseek(this->fileDescriptor, 0, SEEK_END);
    lseek(this->fileDescriptor, 0, SEEK_SET);
}

void FileImpl::readFile(OctetSequence *&data, const uint32_t &length) {
    data->clear();
    data = new OctetSequence(length);
    ssize_t bytes_read = read(this->fileDescriptor, data->data() - this->filePointer_, length);

    if(bytes_read == -1) throw new IOException(CF_EINTR, "Read Error");
}

void FileImpl::writeFile(OctetSequence *data) {
    ssize_t write_bytes = write(this->fileDescriptor, data->data(), data->size());

    if(write_bytes == -1) throw new IOException(CF_EIO, "Write Error");
}

uint32_t FileImpl::sizeOf() {
    return this->size;
}

void FileImpl::closeFile() {
    close(this->fileDescriptor);
}

void FileImpl::setFilePointer(const uint32_t &filePointer) {
    this->filePointer_ = filePointer;
}