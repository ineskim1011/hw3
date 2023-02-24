#ifndef EVENT_H
#define EVENT_H
#include "wire.h"

struct Event
{
    uint64_t time;
    Wire* wire;
    char state;
};

// new EventLess functor for help implementation 
typedef struct EventLess {
    // takes 2 Event*'s as input 
    bool operator()(Event* e1, Event* e2) {
        // uses time data member to create a in-heap 
        // by returning TRUE if LHS is less than RHS
        return (e1->time) < (e2->time);
    }
} EventLess;
	
#endif
