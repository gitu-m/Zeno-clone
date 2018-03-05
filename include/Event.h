#ifndef EVENT_H

#define EVENT_H

#include <QKeyEvent>
#include <chrono>

class Event {

public:
    /*!
    * The key which was recorded by the object gets stored in this attribute.
    */
    QKeyEvent * key;
    /*!
    * Time at which the above input was recorded.
    */
    std::chrono::steady_clock::duration key_time;
};

#endif
