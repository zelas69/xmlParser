#pragma once
#ifndef XML_EXCEPTION_H
#define XML_EXCEPTION_H
#include <exception>
#include <string>

namespace XMLPARSER {
    class cXMLexception : std::exception {
        std::string exception_text_;
    public:
        cXMLexception(const std::string &exception_text) throw();
        cXMLexception(const cXMLexception &exception) throw();
        cXMLexception& operator= (const cXMLexception&) throw();
        virtual ~cXMLexception() throw() {};
        virtual const char* what() const throw();
        friend void swap(cXMLexception &left, cXMLexception &right);
    };
}

#endif  XML_EXCEPTION_H
