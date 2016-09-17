#ifndef WICHERTOOLKIT_H_INCLUDED
#define WICHERTOOLKIT_H_INCLUDED

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <ctime>

namespace Wicher{
class Toolkit{
    public:
        static void log(std::string str);
        static std::string itostr(int i);
        static int strtoi(std::string str);
        static std::string time();
};
}

#endif // UTILS_H_INCLUDED
