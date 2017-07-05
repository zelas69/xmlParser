#include "xmlTree.h"
#include "xmlGlobal.h"
#include "xmlException.h"
#include <iostream>

using std::ifstream;
using std::cout;
using std::vector;
using std::string;

int main() {
    using namespace XMLPARSER;
    try {
        const string path = "E:\\Work\\main\\grandsmeta_xml_smeta\\пример сметы для XML.xml";
        ifstream infile(path);
        vector<string> file_lines;
        get_lines_from_fstream(&infile, &file_lines);

        cXMLtree xml_tree(&file_lines);
        xml_tree.build_tree();
    }
    catch (const cXMLexception& exception) {
        cout << exception.what() << '\n';
    }

    catch (...) {
        cout << "Other exception!\n";
    }

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
