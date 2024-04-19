#include <iostream>
#include <fstream>
#include <string>

using namespace std;

string fileName;

bool bufferCheck() {
    // Open the file in binary mode
    fstream kdbx(fileName, ios::in | ios::binary);
    // Check if the file is open
    if (!kdbx.is_open()) {
        cout << "Not opened" << endl;
        return false;
    }

    // Read the first 8 bytes of the file
    unsigned char buffer[8];
    kdbx.read((char*)buffer, 8);
    kdbx.flush();
    kdbx.close();
    return buffer[0] == 0x03 && buffer[1] == 0xd9 && buffer[2] == 0xa2 && buffer[3] == 0x9a && buffer[4] == 0x67 && buffer[5] == 0xfb && buffer[6]  == 0x4b && buffer[7] == 0xb5;
}

bool bufferReplace(){
    // Open the file in binary mode
    fstream kdbx(fileName, ios::in | ios::out | ios::binary);
    // Check if the file is open
    if (!kdbx.is_open()) {
        cout << "Not opened" << endl;
        return false;
    }

    // Write the first 8 bytes of the file
    unsigned char buffer[8] = {0xbc, 0x69, 0xdf, 0x6a, 0xe4, 0x11, 0xcd, 0x0f};
    kdbx.seekp(0, ios::beg);  // Position at the start of the file
    kdbx.write((char*)buffer, 8);
    kdbx.flush();
    kdbx.close();

    return true;
}

bool bufferCorrection(){
    // Open the file in binary mode
    fstream kdbx(fileName, ios::in | ios::out | ios::binary);
    // Check if the file is open
    if (!kdbx.is_open()) {
        cout << "Not opened" << endl;
        return false;
    }

    // Write the first 8 bytes of the file
    unsigned char buffer[8] = {0x03, 0xd9, 0xa2, 0x9a, 0x67, 0xfb, 0x4b, 0xb5};
    kdbx.seekp(0, ios::beg);  // Position at the start of the file
    kdbx.write((char*)buffer, 8);
    kdbx.flush();
    kdbx.close();

    return true;
}

int main() {
    cout << "File name:" << endl;
    cin >> fileName;
    if (bufferCheck()) {
        if (bufferReplace()){
            cout << "Signature changed" << endl;

        } else {
            cout << "Failed to replace buffer." << endl;
        }
    } else {
        if (bufferCorrection()){
            cout << "Signature restaured" << endl;

        } else {
            cout << "Failed to correct buffer." << endl;
        }
    }
    return 0;
}
