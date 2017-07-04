#include "xmlGlobal.h"
#include "xmlTree.h"
#include "xmlNode.h"
#include "xmlException.h"

using std::vector;
using std::string;

namespace XMLPARSER {
    bool cTagStack::empty() const {
        return tags_.empty();
    }

    void cTagStack::push(const std::string& tag) {
        tags_.push_back(tag);
    }

    void cTagStack::pop() {
        tags_.pop_back();
    }

    bool cTagStack::match_top(const std::string& tag) {
        if (tags_.size() > 0 && tags_.back() == tag) {
            pop();
            return true;
        }
        return false;
    }

    cXMLtree::cXMLtree(std::vector<std::string>& file_lines) {
        data_.swap(file_lines);
        head_ = new cXMLnode();
        current_ = head_;
    }

    cXMLtree::~cXMLtree() {
        delete head_;
    }

    cXMLnode* cXMLtree::get_current() const {
        return current_;
    }

    cXMLnode* cXMLtree::go_to_head() {
        current_ = head_;
        return current_;
    }

    cXMLnode* cXMLtree::go_to_child(const size_t &index) {
        current_ = current_->get_child(index);
        return current_;
    }

    cXMLnode* cXMLtree::go_to_parent() {
        current_ = current_->get_parent();
        return current_;
    }

    bool cXMLtree::build_tree() {
        cTagStack tag_stack;
        for (size_t line_number = 0; line_number < data_.size(); ++line_number) {
            string tag = extract_tag(data_[line_number]);
            int tag_type = check_tag_type(tag);
            
            if (tag_type == CLOSE) {
                if (tag_stack.match_top(tag)) {
                    go_to_parent();
                } else {
                    //error!!!
                    throw cXMLexception("ERROR!");
                }
            } else {
                cXMLnode *new_node = new cXMLnode(&data_[line_number], current_);
                current_->add_child(new_node);

                if (tag_type == OPEN) {
                    tag_stack.push(tag);
                    current_ = new_node;
                }
                tag_positions_[tag].push_back(current_);
            }
        }
        current_ = head_;
        return true;
    }

    //bool test_xml_tree(cXMLtree& xml_tree) {

    //}

    //std::string cXMLtree::extract_tag() {}                                          //?

    //std::map<string, string> cXMLtree::extract_params() {}
}
