#ifndef _UTIL_H
#define _UTIL_H

extern bool globalVerbose;

#define PRINT(X) {std::cerr << #X << " = " << X << "\n";}

#define CERR(X) {if (globalVerbose) std::cerr << X;}

#endif
