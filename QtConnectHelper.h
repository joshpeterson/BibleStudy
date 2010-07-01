#ifndef __QT_SIGNAL_CONNECT_HELPER_H
#define __QT_SIGNAL_CONNECT_HELPER_H

#include <stdexcept>
#include <sstream>

#define QT_CONNECT(sender, signal, receiver, slot)\
    if (!QObject::connect(sender, signal, receiver, slot))\
    {\
        std::stringstream error;\
        error << "Unable to connect signal " << signal << " from sender " << sender << " to slot " << slot << " on receiver " << receiver;\
        throw std::logic_error(error.str());\
    }\

#endif  // __QT_SIGNAL_CONNECT_HELPER_H
