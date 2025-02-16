#include "../Header_Files/String.h"
String::String(int l)  {
str = new char [l + 1];
*str = NULL;
length=0;
maxlen=l;
fail=false;
}
String::~String() {
delete [] str;
}
void String::concat(int len) {
  char *tstr = new char char[length + len + 1];
int i = 0;
while (str[i]) tstr[i] = str[i++];
tstr[i] = NULL;
delete [] str;
str = tstr;
maxlen = length + len;
}
