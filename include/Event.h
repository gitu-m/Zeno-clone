#ifndef EVENT_H

#define EVENT_H

#include <QKeyEvent>
#include <chrono>

class Event {

public:
    QKeyEvent * key; // The key event that occured
    std::chrono::steady_clock::duration key_time; // Time (since player was created) at which key was pressed
};

#endif
