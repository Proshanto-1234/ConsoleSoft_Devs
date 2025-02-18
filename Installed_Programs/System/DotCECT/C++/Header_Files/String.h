#ifndef STRING_H
#define STRING_H

class String {
public:
    // Constructor
    String(const char* s = nullptr); // Constructor from C-style string
    String(int len); // Constructor with specified length

    // Copy Constructor
    String(const String& other);

    // Move Constructor
    String(String&& other) noexcept;

    // Destructor
    ~String();

    // Assignment Operators
    String& operator=(const String& other);
    String& operator=(String&& other) noexcept;

    // Getters
    int GetLength() const;
    int GetCapacity() const;

    // String manipulation
    char CharAt(int i) const;
    String Substring(int from, int to) const;
    String Substring(int from) const;
    String& Append(const char* s);
    String& Append(const String& other);

    // Operators
    char& operator[](int i);
    char operator[](int i) const;
    String operator+(const String& other) const;
    String operator+(const char* s) const;
    bool operator==(const String& other) const;
    bool operator!=(const String& other) const;

private:
    char* str;
    int length;
    int capacity;

    void Allocate(int newCapacity);
};

#endif
