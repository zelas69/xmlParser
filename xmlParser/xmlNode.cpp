#include "xmlGlobal.h"
#include "xmlNode.h"

namespace XMLPARSER {
    cXMLnode::~cXMLnode() {
        for (size_t child_number = 0; child_number < children_.size(); ++child_number) {
            delete children_[child_number];
        }
    }

    cXMLnode::cXMLnode(std::string *data, cXMLnode *parent) : data_(data), parent_(parent) {}

    size_t cXMLnode::get_number_of_children() const {
        return children_.size();
    }

    cXMLnode* cXMLnode::get_parent() const {
        return parent_;
    }

    std::vector<cXMLnode*>& cXMLnode::get_children() {
        return children_;
    }

    cXMLnode* cXMLnode::get_child(const size_t &index) const {
        return children_[index];
    }

    void cXMLnode::add_child(cXMLnode* child) {
        //        cout << *child->data_ << '\n';
        children_.push_back(child);
    }

    //std::map<string, string> cXMLnode::extract_params() {}
}