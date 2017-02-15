#ifndef EXCEPTIONMACROSH
#define EXCEPTIONMACROSH

#include <stdexcept>

#define EXCEPTION(msg) std::runtime_error(std::string(__PRETTY_FUNCTION__) + " - " + msg)
#define FORWARD_EXCEPTION(msg,e) EXCEPTION(msg + ":\n" + e.what())

#endif
