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
    lseek(this->fileDescriptor, filePointer, SEEK_SET);
    this->filePointer_ = filePointer;
}

void FileImpl::throwException(int errorCode) {
    switch(errorCode) {
        case CF_EACCES:
            throw new IOException(CF_EACCES, "Permission Denied");
            break;
        case CF_EAGAIN:
            throw new IOException(CF_EAGAIN, "Resource temporarily unavailable");
            break;
        case CF_EBADF:
            throw new IOException(CF_EBADF, "Bad file descriptor");
            break;
        case CF_EEXIST:
            throw new IOException(CF_EEXIST, "File exists");
            break;
        case CF_EINTR:
            throw new IOException(CF_EINTR, "Interrupted function call");
            break;
        case CF_EIO:
            throw new IOException(CF_EIO, "Input/output error");
            break;
        case CF_EISDIR:
            throw new IOException(CF_EISDIR, "Is a directory");
            break;
        case CF_EMFILE:
            throw new IOException(CF_EMFILE, "Too many open files");
            break;
        case CF_ENAMETOOLONG:
            throw new IOException(CF_ENAMETOOLONG, "Filename too long (91 in Cyg?)");
            break;
        case CF_ENFILE:
            throw new IOException(CF_ENFILE, "Too many open files in system");
            break;
        case CF_ENOENT:
            throw new IOException(CF_ENOENT, "No such file or directory");
            break;
        case CF_ENOMEM:
            throw new IOException(CF_ENOMEM, "Not enough space");
            break;
        case CF_ENOSPC:
            throw new IOException(CF_ENOSPC, "No space left on device");
            break;
        case CF_ENOTDIR:
            throw new IOException(CF_ENOTDIR, "Not a directory");
            break;
        case CF_ENXIO:
            throw new IOException(CF_ENXIO, "No such device or address");
            break;
        case CF_EROFS:
            throw new IOException(CF_EROFS, "Read-only file system");
            break;
        case CF_EFAULT:
            throw new IOException(CF_EFAULT, "Bad address");
            break;
        case CF_EINVAL:
            throw new IOException(CF_EINVAL, "Invalid argument");
            break;
        case CF_EFBIG:
            throw new IOException(CF_EFBIG, "File too large");
            break;
        case CF_EPERM:
            throw new IOException(CF_EPERM, "Operation not permitted");
            break;
        case CF_EPIPE:
            throw new IOException(CF_EPIPE, "Broken pipe");
            break;
        default:
            throw new IOException(CF_NOTSET, "Unknown error");
    }
}
