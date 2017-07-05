#pragma once

#ifndef XML_NODE_H
#define XML_NODE_H

#include <string>
#include <vector>
#include <map>

//typedef std::vector<std::string> VSTR;
//using VSTR = std::vector<std::string>;

namespace XMLPARSER {
    class cXMLnode {
    private:
        std::string *data_;
        cXMLnode *parent_;
        std::vector<cXMLnode*> children_;

    public:
        ~cXMLnode();

        cXMLnode(std::string* data=NULL, cXMLnode* parent=NULL);

        size_t get_number_of_children() const;

        cXMLnode* get_parent() const;

        std::vector<cXMLnode*>& get_children();

        cXMLnode* get_child(const size_t& index) const;

        void add_child(cXMLnode* child);

        std::map<std::string, std::string> extract_params();
    };
}

#endif  XML_NODE_H
