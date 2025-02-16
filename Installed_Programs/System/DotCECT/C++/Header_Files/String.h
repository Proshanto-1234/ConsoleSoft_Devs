//////////////////////
// Class String
//
//////////////////////
#include <iostream>
#include <cstring>

class String {
public:
    // Constructor
    String(const char* s);
    String(int len = 127);

    // Destructor
    virtual ~String();

    // Getters
    int GetLength() const; // Return the length of the current string
    int GetMaxLength() const;

    // String manipulation methods
    char* GetStrPtr() const;
    char* GetString(int from, int to) const;
    char* GetString(int from) const;
    char CharAt(int i) const; // Return the char value of index i
    char* PeekString(int from, int to) const;
    char* PeekString(int from) const;
    char* PeekString() const;

    // Utility methods
    void SetString(const char* s);
    void ShowStringInfo() const;
    bool IsFail() const;

    // Overloaded operators
    String& operator+=(const char* s);
    String& operator+=(const String& o);
    String& operator+=(long l);
    String& operator+=(double d);

    String& operator=(const String& o);
    String& operator=(const char* s);
    String& operator=(long l);
    String& operator=(double d);

    String& operator>>(char* s);
    String& operator>>(long& l);
    String& operator>>(double& d);

    String operator+(const String& o2) const;
    String operator+(double d) const;
    String operator+(const char* s) const;
    String operator+(long l) const;

    char& operator[](int i) const;

    // Friend operators
    friend String operator+(const char* s, const String& o);
    friend String operator+(long l, const String& o);
    friend String operator+(double d, const String& o);
    friend std::ostream& operator<<(std::ostream& os, const String& o);

private:
    // Private utility methods
    void concat(int len);
    void space(int i);

    // Member variables
    int maxlen;
    int length;
    char* str;
    bool fail;
};
