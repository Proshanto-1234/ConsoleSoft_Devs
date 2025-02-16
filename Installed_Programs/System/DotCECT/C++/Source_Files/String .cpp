#include "../Header_Files/String.h"
using namespace std;
String::String(int l) {
    str = new char[l + 1];
    str[0] = '\0';
    length = 0;
    maxlen = l;
    fail = false;
}

String::~String() {
    delete[] str;
}

void String::concat(int len) {
    char* tstr = new char[length + len + 1];
    int i = 0;
    while (str[i]) tstr[i] = str[i++];
    tstr[i] = '\0';
    delete[] str;
    str = tstr;
    maxlen = length + len;
}
void String::Space(int i) {
  if (i) {
      maxlen = strlen(str)-i;
      memmove(
