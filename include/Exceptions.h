//
// Created by adirm on 23.06.2020.
//

#ifndef RADMOR_EXCEPTIONS_H
#define RADMOR_EXCEPTIONS_H

#include <string>
#include <errno.h>
#include <exception>

using namespace std;

enum ErrorNumberType
{
    CF_NOTSET,
    CF_EACCES = EACCES,
    CF_EAGAIN = EAGAIN,
    CF_EBADF = EBADF,
    CF_EEXIST = EEXIST,
    CF_EFAULT = EFAULT,
    CF_EFBIG = EFBIG,
    CF_EINTR = EINTR,
    CF_EINVAL = EINVAL,
    CF_EIO = EIO,
    CF_EISDIR = EISDIR,
    CF_EMFILE = EMFILE,
    CF_ENAMETOOLONG = ENAMETOOLONG,
    CF_ENFILE = ENFILE,
    CF_ENOENT = ENOENT,
    CF_ENOMEM = ENOMEM,
    CF_ENOSPC = ENOSPC,
    CF_ENOTDIR = ENOTDIR,
    CF_ENXIO = ENXIO,
    CF_EPERM = EPERM,
    CF_EPIPE = EPIPE,
    CF_EROFS = EROFS
};

class IOException: exception {
    string msg_;
    ErrorNumberType errorNumber_;

public:
    ErrorNumberType errorNumber () const { return errorNumber_; };
    string msg () const { return msg_; };

    const char * what() const throw();
    IOException(const ErrorNumberType& errorNumber, const string& msg);
    ~IOException();
};

class FileException {
    string msg_;
    ErrorNumberType errorNumber_;

public:
    ErrorNumberType errorNumber () const { return errorNumber_; };
    string msg () const { return msg_; };

    FileException(const ErrorNumberType& errorNumber, const string& msg);
    ~FileException();
};

class InvalidFilePointer {
    InvalidFilePointer();
    ~InvalidFilePointer();
};

#endif //RADMOR_EXCEPTIONS_H
