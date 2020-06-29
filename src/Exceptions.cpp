//
// Created by adirm on 22.06.2020.
//

#ifndef RADMOR_FILEIMPL_H
#define RADMOR_FILEIMPL_H

#include "../include/Exceptions.h"

IOException::IOException(const ErrorNumberType &errorNumber, const string &msg) {
    this->errorNumber_ = errorNumber;
    this->msg_ = msg;
}

const char *IOException::what() const noexcept {
    return exception::what();
}

IOException::~IOException() = default;

FileException::FileException(const ErrorNumberType &errorNumber, const string &msg) {
    this->errorNumber_ = errorNumber;
    this->msg_ = msg;
}


#endif //RADMOR_FILEIMPL_H