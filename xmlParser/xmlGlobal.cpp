#include "xmlGlobal.h"

using std::ifstream;
using std::vector;
using std::string;

namespace {
    const char OPEN_BRACKET = '<';
    const char CLOSE_BRACKET = '>';
    const char SPACE = ' ';
    const char SLASH = '/';
}

namespace XMLPARSER {
    void get_lines_from_fstream(ifstream* stream, vector<string>* file_lines) {
        string file_line;

        while (!(*stream).eof()) {
            getline((*stream), file_line);
            file_lines->push_back(file_line);
        }
    }

    string extract_tag(const string& line) {
        size_t tag_start_index = line.find_first_of(OPEN_BRACKET) + 1;
        size_t tag_end_index = line.find_first_of(SPACE, tag_start_index);

        // ?????????????
        if (tag_end_index == line.size()) {
            tag_end_index == line.size() - 1;
        }
        string tag = line.substr(tag_start_index, tag_end_index - tag_start_index);

        if (line[line.find_last_of(CLOSE_BRACKET) - 1] == SLASH) {
            tag = tag + SLASH;
        }
        return tag;
    }

    int check_tag_type(std::string& tag) {
        if (tag[0] == SLASH) {
            tag = tag.substr(1);
            return CLOSE;
        }

        if (tag[tag.size() - 1] == SLASH || tag[0] == '?' || tag[0] == '!') {
            tag = tag.substr(0, tag.size() - 1);
            return SINGLE;
        }
        return OPEN;
    }
}