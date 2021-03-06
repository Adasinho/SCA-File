#include <iostream>
#include "include/FileImpl.h"
#include "include/Exceptions.h"

using namespace std;

int main() {
    try {
        auto fileImpl = new FileImpl("./../files_for_tests/dataToRead.txt", false);
        auto *buffer = new OctetSequence(fileImpl->sizeOf());

        auto *readyBuffer = new OctetSequence({'s', 'a', 's', 'w'});
        //fileImpl->writeFile(readyBuffer);

        fileImpl->setFilePointer(5);
        fileImpl->readFile(buffer, fileImpl->sizeOf());

        //for(auto i : *buffer)
            //cout << i;
        //cout << endl;

        cout << buffer->data() << endl;

        fileImpl->closeFile();

    } catch (IOException* e) {
        cout << e->msg() << endl;
    }

    return 0;
}
