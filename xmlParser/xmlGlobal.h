#pragma once
#ifndef XML_GLOBAL_H
#define XML_GLOBAL_H

#include <fstream>
#include <string>
#include <vector>
//typedef std::vector<std::string> VSTR;
//using VSTR = std::vector<std::string>;
typedef unsigned short ushort;

namespace XMLPARSER {
    //enum class
    enum { OPEN, CLOSE, SINGLE };

    void get_lines_from_fstream(std::ifstream* stream, std::vector<std::string>* file_lines);

    std::string extract_tag(const std::string& line);

    int check_tag_type(std::string& tag); //!!@#!@#!@$!@$!@$@!#!@!#!#@!@#@!#!@#!@#@!#@!##@!$#@!!$^#^$#!^!#$^$
}

#endif  XML_GLOBAL_H