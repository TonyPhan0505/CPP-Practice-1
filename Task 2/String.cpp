#include "String.h"

// define constructor
String :: String(const char *p) {
    shared = new SharedData; // allocate memory to store the shared data for Strings
    int index = 0; // define an index to add more characters into the String's data
    int data_size = 100;
    shared -> n = 0; // at first, the size of the String is 0
    shared -> data = new char[data_size]; // allocate memory to store the String's data
    shared -> count = 1; // at the time this constructor is called, there is 1 string referencing this shared data
    // keep copying characters from the C string into the String's data until the end of the C string
    while ((*p) != '\0') {
        char c = *p; // c = character
        // if we have not gone beyond the default size of the String's data
        if (index <= data_size - 1) {
            (shared -> data)[index] = c; // add another character to the data
            (shared -> n) += 1; // increment the size of the String's data
            index += 1; // move to the next location to store a character in data
        } else {
            // if we have gone beyond the default size of the String's data
            data_size += 1; // increase the size for the String's data
            char *newData = new char[data_size]; // allocate more memory for the String's data
            // copy the characters in the old String's data over to the new allocated memory
            for (int j = 0; j <= data_size - 2; j++) {
                newData[j] = (shared -> data)[j];
            }
            delete [](shared -> data); // free the memory the old String's data took
            newData[index] = c; // add another character to the data
            shared -> data = newData; // assign the updated array of characters to String's data
            (shared -> n) += 1; // increment the size of the String's data
            index += 1; // move to the next location to store a character in data
        }
        p += 1; // move forward in the C string
    }
    if ((*p) == '\0') {
        (shared -> data)[index] = '\0';
    }
}

// define destructor
String :: ~String() {
    if ((shared -> count) == 0) {
        delete [](shared -> data);
        delete shared;
    } else {
        (shared -> count) -= 1;
    }
}

// define copy constructor
String :: String(const String &x) {
    shared = x.shared;
    (shared -> count) += 1;
}

// define assignment constructor
String &String :: operator = (const String &x) {
    shared = x.shared;
    (shared -> count) += 1;
    return *this;
}

// define size()
size_t String :: size() const {
    return shared -> n;
}

// define ref_count()
size_t String :: ref_count() const {
    return shared -> count;
}

// define cstr()
const char *String :: cstr() const {
    return shared -> data;
}