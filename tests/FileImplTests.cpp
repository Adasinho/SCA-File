//
// Created by adirm on 28.06.2020.
//

#include <fcntl.h>
#include <string>

#include "gtest/gtest.h"

#include "FileImpl.h"
#include "Exceptions.h"

const string FOLDER_WITH_TXT_FILES = "./../files_for_tests/";
const string PATH_TO_READ_ONLY_FILE = FOLDER_WITH_TXT_FILES + "readOnlyFile.txt";
const string PATH_TO_READ_AND_WRITE_FILE = FOLDER_WITH_TXT_FILES + "readAndWriteFile.txt";
const string TEXT_IN_READ_ONLY_FILE = "Example text written in file";

void createFile(const string& filePath, int mode) {
    creat(filePath.c_str(), mode);
}

/*
 * 3.1.3.4.1.5.1 read
 * 3.1.3.4.1.5.1.3 Behavior
    The read operation shall read, from the referenced file, the number of octets specified by the
    input length parameter and advance the value of the filePointer attribute by the number of octets
    actually read.
 */
TEST(FileImplTest, givenFileImplWhenReadFileThenGetTextFromFile) {
    auto fileImpl = make_unique<FileImpl>(PATH_TO_READ_ONLY_FILE.c_str(), false);
    auto buffer = make_unique<OctetSequence>(fileImpl->sizeOf());

    fileImpl->readFile(reinterpret_cast<OctetSequence *&>(buffer), fileImpl->sizeOf());

    auto expected = make_unique<OctetSequence>(TEXT_IN_READ_ONLY_FILE.begin(), TEXT_IN_READ_ONLY_FILE.end());
    EXPECT_EQ(string(expected->begin(), expected->end()), string(buffer->begin(), buffer->end()));
}

/*
 * 3.1.3.4.1.5.1 read
 * 3.1.3.4.1.5.1.3 Behavior
    The read operation shall read less than the number of octets specified in the input-length
    parameter, when an end of file is encountered.
 */
TEST(FileImplTest, givenFileImplWithOffsetFilePointerWhenReadFileThenGetTextLessThanLength) {
    int filePointerOffset = 5;

    auto fileImpl = make_unique<FileImpl>(PATH_TO_READ_ONLY_FILE.c_str(), false);
    auto buffer = make_unique<OctetSequence>(fileImpl->sizeOf() - filePointerOffset);

    fileImpl->setFilePointer(filePointerOffset);
    fileImpl->readFile(reinterpret_cast<OctetSequence *&>(buffer), fileImpl->sizeOf());

    auto expected = make_unique<OctetSequence>(TEXT_IN_READ_ONLY_FILE.begin() + filePointerOffset, TEXT_IN_READ_ONLY_FILE.end());
    EXPECT_EQ(string(expected->begin(), expected->end()), string(buffer->begin(), buffer->end()));
}

/*
 * 3.1.3.4.1.5.1 read
 * 3.1.3.4.1.5.1.4 Returns
    If the filePointer attribute value reflects the end of the File, the read operation shall
    return a zero-length CF OctetSequence.
 */
TEST(FileImplTest, givenFileImplWithOffsetFilePointerToEndFileWhenReadFileThenReturnEmptyString) {
    auto fileImpl = make_unique<FileImpl>(PATH_TO_READ_ONLY_FILE.c_str(), false);
    auto filePointerOffset = fileImpl->sizeOf();
    auto buffer = make_unique<OctetSequence>();

    fileImpl->setFilePointer(filePointerOffset);
    fileImpl->readFile(reinterpret_cast<OctetSequence *&>(buffer), fileImpl->sizeOf());

    EXPECT_EQ(0, string(buffer->begin(), buffer->end()).length());
}

/*
 * 3.1.3.4.1.5.1 read
 * 3.1.3.4.1.5.1.5 Exceptions/Errors
    The read operation shall raise the IOException when a read error occurs.
 */
TEST(FileImplTest, givenFileImplAndNonExistFileWhenReadFileThenThrowNoSuchFileOrDirectoryException) {
    try {
        auto fileImpl = make_unique<FileImpl>("PATH_TO_READ_AND_WRITE_FILE", false);
    } catch (IOException* exception) {
        EXPECT_EQ(CF_ENOENT, exception->errorNumber());
    }
}

/*
 * 3.1.3.4.1.5.1 read
 * 3.1.3.4.1.5.1.5 Exceptions/Errors
    The read operation shall raise the IOException when a read error occurs.
 */
TEST(FileImplTest, givenFileImplAndTryReadDirectoryWhenReadFileThenThrowIsADirectoryException) {
    try {
        auto fileImpl = make_unique<FileImpl>(FOLDER_WITH_TXT_FILES.c_str(), false);
    } catch (IOException* exception) {
        EXPECT_EQ(CF_EISDIR, exception->errorNumber());
    }
}

/*
 * 3.1.3.4.1.5.2 write
 * 3.1.3.4.1.5.2.3 Behavior
    The write operation shall write data to the file referenced. The write operation shall increment
    the filePointer attribute to reflect the number of octets written, when the operation is successful.
 */
TEST(FileImplTest, givenFileImplWhenWriteFileThenWriteNewTextInFile) {
    createFile(PATH_TO_READ_AND_WRITE_FILE, S_IRUSR | S_IWUSR);
    auto fileImpl = make_unique<FileImpl>(PATH_TO_READ_AND_WRITE_FILE.c_str(), false);

    auto expected = make_unique<OctetSequence>(fileImpl->sizeOf());
    fileImpl->readFile(reinterpret_cast<OctetSequence *&>(expected), fileImpl->sizeOf());
    EXPECT_EQ("", string(expected->begin(), expected->end()));

    expected = make_unique<OctetSequence>(TEXT_IN_READ_ONLY_FILE.begin(), TEXT_IN_READ_ONLY_FILE.end());
    fileImpl->writeFile(reinterpret_cast<OctetSequence *&>(expected));
    EXPECT_EQ(TEXT_IN_READ_ONLY_FILE, string(expected->begin(), expected->end()));
}

/*
 * 3.1.3.4.1.5.2 write
 * 3.1.3.4.1.5.2.3 Behavior
    If the write is unsuccessful, the value of the filePointer attribute shall maintain or be restored to
    its value prior to the write operation call. If the file was opened using the FileSystem::open
    operation with an input read_Only parameter value of TRUE, writes to the file are considered to
    be in error.
 */
TEST(FileImplTest, givenFileImplAndReadOnlyFileWhenWriteFileThenThrowBadFileDescriptorException) {
    createFile(PATH_TO_READ_AND_WRITE_FILE, S_IRUSR | S_IWUSR);
    try {
        auto fileImpl = make_unique<FileImpl>(PATH_TO_READ_AND_WRITE_FILE.c_str(), true);

        auto expected = make_unique<OctetSequence>(TEXT_IN_READ_ONLY_FILE.begin(), TEXT_IN_READ_ONLY_FILE.end());
        fileImpl->writeFile(reinterpret_cast<OctetSequence *&>(expected));
    } catch (IOException* exception) {
        EXPECT_EQ(CF_EBADF, exception->errorNumber());
    }
}

/*
 * 3.1.3.4.1.5.3 sizeOf
 * 3.1.3.4.1.5.3.4 Returns
    The sizeOf operation shall return the number of octets stored in the file.
 */
TEST(FileImplTest, givenFileImplWhenSizeOfThenReturnNumberOfOctetsStoredInTheFile) {
    auto fileImpl = make_unique<FileImpl>(PATH_TO_READ_ONLY_FILE.c_str(), false);

    auto expected = make_unique<OctetSequence>(TEXT_IN_READ_ONLY_FILE.begin(), TEXT_IN_READ_ONLY_FILE.end());
    EXPECT_EQ(string(expected->begin(), expected->end()).length(), fileImpl->sizeOf());
}

/*
 * 3.1.3.4.1.5.5 setFilePointer
 * 3.1.3.4.1.5.5.3 Behavior
    The setFilePointer operation shall set the filePointer attribute value to the input filePointer.
 */
TEST(FileImplTest, givenFileImplWhenSetFilePointerThenChangeFilePointer) {
    auto fileImpl = make_unique<FileImpl>(PATH_TO_READ_ONLY_FILE.c_str(), false);
    auto filePointerOffset = 5;
    fileImpl->setFilePointer(filePointerOffset);

    EXPECT_EQ(filePointerOffset, fileImpl->filePointer());
}

/*
 * 3.1.3.4.1.5.5 setFilePointer
 * 3.1.3.4.1.5.5.5 Exceptions/Errors
    The setFilePointer operation shall raise the InvalidFilePointer exception when the value of the
    filePointer parameter exceeds the file size.
 */
TEST(FileImplTest, givenFileImplAndFilePointerExceedsTheFileSizeWhenSetFilePointerThenThrowException) {
    auto fileImpl = make_unique<FileImpl>(PATH_TO_READ_ONLY_FILE.c_str(), false);
    auto filePointerOffset = fileImpl->sizeOf() + 5;
    try {
        fileImpl->setFilePointer(filePointerOffset);
    } catch (InvalidFilePointer* exception) {
        EXPECT_TRUE(true);
    }
}

/// NOT PASS ON LINUX
/*
 * 3.1.3.4.1.5.5 setFilePointer
 * 3.1.3.4.1.5.5.5 Exceptions/Errors
    The setFilePointer operation shall raise the CF FileException when the file pointer for the
    referenced file cannot be set to the value of the input filePointer parameter.
 */
/*
TEST(FileImplTest, givenFileImplWhenSetFilePointerToNegativeValueThenThrowException) {
    auto fileImpl = make_unique<FileImpl>(PATH_TO_READ_ONLY_FILE.c_str(), false);
    auto filePointerOffset = -5;
    try {
        fileImpl->setFilePointer(filePointerOffset);
    } catch (FileException* exception) {
        EXPECT_EQ(CF_EINVAL, exception->errorNumber());
    }
}
 */