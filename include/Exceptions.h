//
// Created by adirm on 23.06.2020.
//

#ifndef RADMOR_EXCEPTIONS_H
#define RADMOR_EXCEPTIONS_H

#include <string>

using namespace std;

enum ErrorNumberType
{
    CF_NOTSET, CF_E2BIG, CF_EACCES, CF_EAGAIN, CF_EBADF, CF_EBADMSG,
    CF_EBUSY, CF_ECANCELED, CF_ECHILD, CF_EDEADLK, CF_EDOM,
    CF_EEXIST, CF_EFAULT, CF_EFBIG, CF_EINPROGRESS,
    CF_EINTR,CF_EINVAL, CF_EIO, CF_EISDIR, CF_EMFILE, CF_EMLINK,
    CF_EMSGSIZE, CF_ENAMETOOLONG, CF_ENFILE, CF_ENODEV, CF_ENOENT,
    CF_ENOEXEC, CF_ENOLCK, CF_ENOMEM, CF_ENOSPC, CF_ENOSYS,
    CF_ENOTDIR, CF_ENOTEMPTY, CF_ENOTSUP ,CF_ENOTTY, CF_ENXIO,
    CF_EPERM, CF_EPIPE, CF_ERANGE , CF_EROFS, CF_ESPIPE, CF_ESRCH,
    CF_ETIMEDOUT ,CF_EXDEV
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
    FileException(const ErrorNumberType& errorNumber, const string& msg);
    ~FileException();
};

class InvalidFilePointer {
    InvalidFilePointer();
    ~InvalidFilePointer();
};

#endif //RADMOR_EXCEPTIONS_H
