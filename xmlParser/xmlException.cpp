#include "xmlException.h"

namespace XMLPARSER {
    cXMLexception::cXMLexception(const std::string &exception_text) throw() : exception_text_(exception_text) {}

    cXMLexception::cXMLexception(const cXMLexception &exception) throw() : std::exception(exception), exception_text_(exception.exception_text_) {}

    cXMLexception& cXMLexception::operator= (const cXMLexception &exception) throw() {
        cXMLexception tmp(exception);
        std::swap(*this, tmp);
        return *this;
    }

    const char* cXMLexception::what() const throw() {
        return exception_text_.c_str();
    }
}