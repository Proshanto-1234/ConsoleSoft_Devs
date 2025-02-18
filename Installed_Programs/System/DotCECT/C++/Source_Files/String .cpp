#include "String.h"
#include <cstring> // Required for strlen, strcpy, etc.

// Constructor from C-style string
String::String(const char* s) : str(nullptr), length(0), capacity(0) {
    if (s) {
        length = std::strlen(s);
        capacity = length + 1;
        str = new char[capacity];
        std::strcpy(str, s);
    } else {
        capacity = 1;
        str = new char[capacity];
        str[0] = '\0';
    }
}

// Constructor with specified length
String::String(int len) : str(nullptr), length(0), capacity(len + 1) {
    str = new char[capacity];
    str[0] = '\0';
}

// Copy Constructor
String::String(const String& other) : str(nullptr), length(other.length), capacity(other.capacity) {
    str = new char[capacity];
    std::strcpy(str, other.str);
}

// Move Constructor
String::String(String&& other) noexcept : str(other.str), length(other.length), capacity(other.capacity) {
    other.str = nullptr;
    other.length = 0;
    other.capacity = 0;
}

// Destructor
String::~String() {
    delete[] str;
}

// Assignment Operator
String& String::operator=(const String& other) {
    if (this != &other) {
        if (capacity < other.length + 1) {
            delete[] str;
            capacity = other.length + 1;
            str = new char[capacity];
        }
        length = other.length;
        std::strcpy(str, other.str);
    }
    return *this;
}

// Move Assignment Operator
String& String::operator=(String&& other) noexcept {
    if (this != &other) {
        delete[] str;
        str = other.str;
        length = other.length;
        capacity = other.capacity;

        other.str = nullptr;
        other.length = 0;
        other.capacity = 0;
    }
    return *this;
}

int String::GetLength() const {
    return length;
}

int String::GetCapacity() const {
    return capacity;
}

char String::CharAt(int i) const {
    if (i < 0 || i >= length) {
        return '\0'; // Or throw an exception, depending on your error handling strategy
    }
    return str[i];
}

String String::Substring(int from, int to) const {
    if (from < 0 || to > length || from > to) {
        return String(); // Or throw an exception
    }
    int newLength = to - from;
    String result(newLength);
    for (int i = 0; i < newLength; ++i) {
        result.str[i] = str[from + i];
    }
    result.str[newLength] = '\0';
    result.length = newLength;
    return result;
}

String String::Substring(int from) const {
    return Substring(from, length);
}

String& String::Append(const char* s) {
    if (!s) return *this;
    int sLen = std::strlen(s);
    if (length + sLen >= capacity) {
        Allocate(length + sLen);
    }
    std::strcpy(str + length, s);
    length += sLen;
    return *this;
}

String& String::Append(const String& other) {
    return Append(other.str);
}

char& String::operator[](int i) {
    return str[i];
}

char String::operator[](int i) const {
    return str[i];
}

String String::operator+(const String& other) const {
    String result(length + other.length);
    std::strcpy(result.str, str);
    std::strcpy(result.str + length, other.str);
    result.length = length + other.length;
    return result;
}

String String::operator+(const char* s) const {
    String result(length + std::strlen(s));
    std::strcpy(result.str, str);
    std::strcpy(result.str + length, s);
    result.length = length + std::strlen(s);
    return result;
}

bool String::operator==(const String& other) const {
    return (length == other.length) && (std::strcmp(str, other.str) == 0);
}

bool String::operator!=(const String& other) const {
    return !(*this == other);
}

void String::Allocate(int newCapacity) {
    char* newStr = new char[newCapacity + 1];
    if (str) {
        std::strcpy(newStr, str);
        delete[] str;
    }
    str = newStr;
    capacity = newCapacity + 1;
}
