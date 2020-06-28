//
// Created by adirm on 28.06.2020.
//

#include <fcntl.h>
#include <string>

#include "gtest/gtest.h"

#include "FileImpl.h"
#include "Exceptions.h"

const string FOLDER_WITH_TXT_FILES = "./../files_for_tests/";

void createFile(const string& filePath, int mode) {
    int fd = creat(filePath.c_str(), mode);
}

/*
 * 3.1.3.4.1.5.1 read
 * 3.1.3.4.1.5.1.3 Behavior
    The read operation shall read, from the referenced file, the number of octets specified by the
    input length parameter and advance the value of the filePointer attribute by the number of octets
    actually read.
 */
TEST(FileImplTest, WhenCreatingFileImplThenReadFile) {
    auto fileImpl = new FileImpl("./../files_for_tests/dataToRead.txt", false);
    auto *buffer = new OctetSequence(fileImpl->sizeOf());

    fileImpl->readFile(buffer, fileImpl->sizeOf());

    string teskt = "Przykladowy plik z tekstem, nowym tekstem!";
    auto *expected = new OctetSequence(teskt.begin(), teskt.end());

    EXPECT_EQ(string(expected->begin(), expected->end()), string(buffer->begin(), buffer->end()));
}

/*
 * 3.1.3.4.1.5.2 write
 * 3.1.3.4.1.5.2.3 Behavior
    The write operation shall write data to the file referenced. The write operation shall increment
    the filePointer attribute to reflect the number of octets written, when the operation is successful.
 */
TEST(FileImplTest, WhenCreatingFileImplThenWriteText) {
    createFile(FOLDER_WITH_TXT_FILES + "nowyPlik.txt", S_IWUSR);
    auto fileImpl = new FileImpl("./../files_for_tests/nowyPlik.txt", false);

    auto *expected = new OctetSequence(fileImpl->sizeOf());
    fileImpl->readFile(expected, fileImpl->sizeOf());

    EXPECT_EQ("", string(expected->begin(), expected->end()));

    string text = "Example text written in new file";
    expected = new OctetSequence(text.begin(), text.end());

    fileImpl->writeFile(expected);

    EXPECT_EQ(text, string(expected->begin(), expected->end()));
}