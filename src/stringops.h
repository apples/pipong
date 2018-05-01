#ifndef STRINGOPS_H_INCLUDED
#define STRINGOPS_H_INCLUDED

#include <sstream>

template <class T>
inline std::string to_string (const T& t)
{
    std::stringstream ss;
    ss << t;
    return ss.str();
}

#endif // STRINGOPS_H_INCLUDED
