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

class FileException: exception {
    string msg_;
    ErrorNumberType errorNumber_;

public:
    ErrorNumberType errorNumber () const { return errorNumber_; };
    string msg () const { return msg_; };

    const char * what() const throw();
    FileException(const ErrorNumberType& errorNumber, const string& msg);
    ~FileException();
};

class InvalidFilePointer {
    ~InvalidFilePointer();

public:
    InvalidFilePointer();
};

static void throwException(int errorCode) {
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
            throw new FileException(CF_EINVAL, "Invalid argument");
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

#endif //RADMOR_EXCEPTIONS_H
