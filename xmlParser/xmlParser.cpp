#include "xmlParser.h"
#include <iostream>
using std::cout;
using std::cin;
using std::vector;
using std::string;
using std::ifstream;
using std::istream;

namespace {
    //enum class
    enum {OPEN, CLOSE, SINGLE};
    const char OPEN_BRACKET = '<';
    const char CLOSE_BRACKET = '>';
    const char SPACE = ' ';
    const char SLASH = '/';
}

namespace XMLPARSER {
    void get_lines_from_fstream(ifstream &stream, vector<string> &file_lines) {
        string file_line;

        while (!stream.eof()) {
            getline(stream, file_line);
            file_lines.push_back(file_line);
        }
    }

    int check_tag(std::string &tag) const {
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

    string extract_tag(const string &line) {
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

    void cXMLnode::add_child(cXMLnode *child) {
//        cout << *child->data_ << '\n';
        children_.push_back(child);
    }

    //std::map<string, string> cXMLnode::extract_params() {}


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
            int tag_type = check_tag(tag);
            
            if (tag_type == CLOSE) {
                if (tag_stack.match_top(tag)) {
                    go_to_parent();
                } else {
                    //error!!!
                    return false;
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

int main() {
    using namespace XMLPARSER;

    const string path = "E:\\Work\\main\\grandsmeta_xml_smeta\\пример сметы для XML.xml";
    ifstream infile(path);
    vector<string> file_lines;
    get_lines_from_fstream(infile, file_lines);

    cXMLtree xml_tree(file_lines);
    cout << xml_tree.build_tree() << '\n';

    //for (size_t i = 0; i < file_lines.size(); ++i) {
    //  cout << file_lines[i] << '\n';
    //}

    /*vector<cXMLnode> nodes;
    cXMLnode node_1;
    nodes.push_back(node_1);
    

    cXMLnode node_2;
    nodes.push_back(node_2);
    cXMLnode *node_ptr_2 = &nodes.back();

    cXMLnode *node_ptr_1 = &nodes[0];

    node_ptr_1->add_child(node_ptr_2);*/
    

    cout << "It works!\n";

    return 0;
}
