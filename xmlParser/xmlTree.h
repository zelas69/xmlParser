#pragma once
#ifndef XML_TREE_H
#define XML_TREE_H

#include <string>
#include <vector>
#include <map>

namespace XMLPARSER {
    class cXMLnode;

    class cTagStack {
    private:
        std::vector<std::string> tags_;

    public:
        bool empty() const;

        void push(const std::string& tag);

        void pop();

        bool match_top(const std::string &tag);
    };

    class cXMLtree {
    private:
        std::vector<std::string> data_;
        std::map<std::string, std::vector<cXMLnode*> > tag_positions_;
        cXMLnode *current_;
        cXMLnode *head_;

        cXMLnode* get_current() const;

        cXMLnode* go_to_head();

        cXMLnode* go_to_child(size_t index);

        cXMLnode* go_to_parent();

    public:
        cXMLtree(std::vector<std::string>* file_lines);

        ~cXMLtree();

        bool build_tree();

    };
}

#endif  XML_TREE_H