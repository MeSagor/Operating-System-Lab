#include<iostream>
#include <cstdio>
#include<string.h>
#include<fstream>
#include <chrono>
#include <ctime>

using namespace std;

void create_file(string filename) {
    ofstream newFile(filename);

    time_t timenow = chrono::system_clock::to_time_t(chrono::system_clock::now());
    newFile << "File has created\nTime: " << ctime(&timenow) << endl;
    newFile.close();
}

void remove_file(string filename) {
    int result = remove(filename.c_str());
    if (result != 0) {
        cerr << "File deletion failed" << endl;
    } else {
        cout << "File deleted successfully" << endl;
    }
}

void rename_file(string oldname, string newname) {
    int result = rename(oldname.c_str(), newname.c_str());
    if (result != 0) {
        perror("Error renaming file\n");
    } else {
        cout << "File renamed successfully" << endl;
    }
}

void move_file(string filename, string location) {
    // /Users/SAGOR/Experimental\ Folder/Operating\ System\ Lab/File\ Handling/another_location/
    location = location + filename;
    int result = rename(filename.c_str(), location.c_str());
    if (result != 0) {
        perror("Error moving file\n");
    } else {
        cout << "File moved successfully" << endl;
    }
}

void copy_file(string filename, string location) {
    // /Users/SAGOR/Experimental\ Folder/Operating\ System\ Lab/File\ Handling/another_location/
    location = location + filename;

    ofstream newFile(location, ios::binary);
    ifstream prevFile(filename, ios::binary);

    newFile << prevFile.rdbuf();

    newFile.close();
    prevFile.close();
}

int main(int argc, char* argv[]) {
    if (strcmp(argv[1], "create") == 0) {
        create_file(argv[2]);
    } else if (strcmp(argv[1], "delete") == 0) {
        remove_file(argv[2]);
    } else if (strcmp(argv[1], "rename") == 0) {
        rename_file(argv[2], argv[3]);
    } else if (strcmp(argv[1], "move") == 0) {
        move_file(argv[2], argv[3]);
    } else if (strcmp(argv[1], "copy") == 0) {
        copy_file(argv[2], argv[3]);
    }
}