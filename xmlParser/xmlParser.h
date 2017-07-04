#pragma once

#ifndef XML_PARSER_H
#define XML_PARSER_H

#include <string>
#include <vector>
#include <fstream>
#include <map>


//typedef std::vector<std::string> VSTR;
//using VSTR = std::vector<std::string>;
typedef unsigned short ushort;

namespace XMLPARSER {
    void get_lines_from_fstream(std::ifstream &stream, std::vector<std::string> &file_lines);

    class cTagStack {
    private:
        std::vector<std::string> tags_;
        const char OPEN_BRACKET = '<';
        const char CLOSE_BRACKET = '>';
        const char SPACE = ' ';
        const char SLASH = '/';

    public:
        bool empty() const;

        void push(const std::string& tag);

        void pop();

        std::string extract_tag(const std::string &line);

        int check_tag(std::string &tag) const;

        bool match_top(const std::string &tag);
    };


    class cXMLnode {
    private:
        std::string *data_;
        cXMLnode *parent_;
        std::vector<cXMLnode*> children_;

    public:
        ~cXMLnode();

        cXMLnode(std::string *data=NULL, cXMLnode *parent=NULL);

        size_t get_number_of_children() const;

        cXMLnode* get_parent() const;

        std::vector<cXMLnode*>& get_children();

        cXMLnode* get_child(const size_t &index) const;

        void add_child(cXMLnode *child);

        std::map<std::string, std::string> extract_params();
    };


    class cXMLtree {
    private:
        std::vector<std::string> data_;
        std::map<std::string, std::vector<cXMLnode*> > tag_positions_;
        cXMLnode *current_;
        cXMLnode *head_;
        
        cXMLnode* get_current() const;

        cXMLnode* go_to_head();

        cXMLnode* go_to_child(const size_t &index);

        cXMLnode* go_to_parent();

    public:
        cXMLtree(std::vector<std::string>& file_lines);   // swap

        ~cXMLtree();

        bool build_tree();

    };
}

#endif // XML_PARSER_H
