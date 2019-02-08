#ifndef PLANE_H
#define PLANE_H

#include <string>

typedef struct plane plane;
struct plane
{
    unsigned int id = 0;
    std::string company = "";
    double readiness = 0;
    plane() {}
    plane(unsigned i, std::string c, double r) : id(i), company(c), readiness(r) {}
};


#endif // PLANE_H
