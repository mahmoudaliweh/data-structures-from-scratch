#include <iostream>
using namespace std;

class String {
private:
    char *buffer;
    int length;

public:
    String(): buffer(nullptr), length(0) {
    }

    String(const char *string) {
        if (!string) {
            buffer = nullptr;
            length = 0;
            return;
        }

        int len = 0;
        while (string[len] != '\0') len++;

        buffer = new char[len];
        length = len;

        for (int i = 0; i < length; i++) {
            buffer[i] = string[i];
        }
    }

    ~String() {
        delete[] buffer;
    }

    char char_at(int index) {
        if(index >= length) {
            cout << "Index out of bounds\n";
        } else {
            return buffer[index];
        }
    }

    bool equals(const String& other) {

        if(other.length != this->length) {
            return false;
        }

        for(int i = 0; i < length; i ++) {
            if(other.buffer[i] != this->buffer[i]) return false;
        }
        return true;
    }

    String concat(const String& other) {
        int newLen = this->length + other.length;
        char *newBuffer = new char[newLen];
        for(int i = 0 ; i < length; i ++) {
            newBuffer[i] = buffer[i];
        }
        for(int i = 0; i < other.length; i++) {
            newBuffer[i + length] = other.buffer[i];
        }
        String newString;
        newString.buffer = newBuffer;
        newString.length = newLen;
        return newString;
    }

    String substring(int start, int end) {
        if(start > end || end > length) {
            throw std::out_of_range("Invalid substring range");
        }
        int newLen = end - start;
        char *newBuffer = nullptr;

        if(newLen > 0) {
            newBuffer = new char[newLen];
            for(int i = 0; i < newLen; i++) {
                newBuffer[i] = buffer[i + start];
            }
        }

        String newString;
        newString.buffer = newBuffer;
        newString.length = newLen;
        return newString;
    }

    void print() {
        for(int i = 0; i < length; i++) {
            cout << buffer[i];
        }
        cout << endl;
    }
};



    int main() {
        String s1("Hello");
        String s2("World");

        String s3 = s1.concat(s2);
        s3.print();  // HelloWorld

        String sub = s3.substring(5, 10);
        sub.print(); // World

        std::cout << (s1.equals(s2) ? "Equal" : "Not equal") << std::endl; // Not equal

        std::cout << s1.char_at(1) << std::endl; // e

        return 0;
    }

