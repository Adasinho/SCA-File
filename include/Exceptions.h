//
// Created by adirm on 23.06.2020.
//

#ifndef RADMOR_EXCEPTIONS_H
#define RADMOR_EXCEPTIONS_H

#include <string>
#include <exception>
#include <errno.h>

using namespace std;

enum ErrorNumberType
{
    CF_NOTSET,
    CF_E2BIG,
    CF_EACCES = EACCES,
    CF_EAGAIN = EAGAIN,
    CF_EBADF = EBADF,
    CF_EBADMSG,
    CF_EBUSY,
    CF_ECANCELED,
    CF_ECHILD,
    CF_EDEADLK,
    CF_EDOM,
    CF_EEXIST = EEXIST,
    CF_EFAULT = EFAULT,
    CF_EFBIG = EFBIG,
    CF_EINPROGRESS,
    CF_EINTR = EINTR,
    CF_EINVAL = EINVAL,
    CF_EIO = EIO,
    CF_EISDIR = EISDIR,
    CF_EMFILE = EMFILE,
    CF_EMLINK,
    CF_EMSGSIZE,
    CF_ENAMETOOLONG = ENAMETOOLONG,
    CF_ENFILE = ENFILE,
    CF_ENODEV,
    CF_ENOENT = ENOENT,
    CF_ENOEXEC,
    CF_ENOLCK,
    CF_ENOMEM = ENOMEM,
    CF_ENOSPC = ENOSPC,
    CF_ENOSYS,
    CF_ENOTDIR = ENOTDIR,
    CF_ENOTEMPTY,
    CF_ENOTSUP,
    CF_ENOTTY,
    CF_ENXIO = ENXIO,
    CF_EPERM = EPERM,
    CF_EPIPE = EPIPE,
    CF_ERANGE,
    CF_EROFS = EROFS,
    CF_ESPIPE,
    CF_ESRCH,
    CF_ETIMEDOUT,
    CF_EXDEV
};

class IOException {
    string msg_;
    ErrorNumberType errorNumber_;

public:
    ErrorNumberType errorNumber () const { return errorNumber_; };
    string msg () const { return msg_; };

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
