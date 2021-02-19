#ifndef _EventQueue_
#define _EventQueue_

#include "Clock.h"
#include "KeyInfo.h"
#include "KeyLayout.h"
#include "Event.h"
#include "Timer.h"

class EventQueue {
  public:
    EventQueue(int maxEventHistory = 200);

    // override to process events before they get put in the queue
    virtual void processEvent(Event* e) { };

    keyswitch_t sendKeys();  // send key events to host, returns number of key events sent
    void sendKey(keycode_t code, boolean pressed);

    bool keyTapped(keycode_t c);
    bool keyDoubleTapped(keycode_t c);
    bool keyTapHeld(keycode_t c);

    Event* getNextEvent();
    Event* peekNextEvent();
    void addEvent(KeyMatrix* m, keyswitch_t k, keycode_t c, millis_t t, bool d);
    void addEvent(keycode_t c, bool d);
    Event* history(int i) { Event* e = _events; while (e && i) { e = e->getPrev(); i--; }; return e; }
    Event* firstEvent() { Event* e = _events; while (e) { if (e->getPrev() == nullptr) break; e = e->getPrev(); } return e; }
    Event* lastEvent(keycode_t c) { Event* e = _events; while (e) { if (e->code() == c) break; e = e->getPrev();  }; return e; }
    Event* lastEvent() { return _events; };
    millis_t lastEventTime() { Event* e = lastEvent();  if (e) return e->time(); else return 0; }
    Event* prevEvent(Event* e) { return e->getPrev(); }
    void removeEvent(Event* e);
    bool keyIsDown(keycode_t c) { Event* e = lastEvent(c); return (e && e->pressed()); }
    inline bool keyIsUp(keycode_t c) { Event* e = lastEvent(c); return (!e || !e->pressed()); }

    char getKeyChar(keycode_t c);

    bool isSoftKeyCode(keycode_t c) { return c <= MAX_SOFT_KEY; }

    void repeat();  // only called by timer callback function

    void printStatus(Stream* c = nullptr);  // dump out the keyboard status, pass null to go to console

    void releaseKeys();  // sends release messages to Keyboard for any pressed keys

  private:

    void truncateHistory();

    static const millis_t _doubleTappedTime = 250;
    static const millis_t _tappedTime = 250;

    void clearKeyChanges();

    int _maxEventHistory;
    Event* _events = nullptr;
    Event* _lastEvent = nullptr;

    CallbackTimer _repeatTimer;
    static const millis_t _repeatInterval = 50;
    static const millis_t _repeatStart = 500;
    millis_t _lastRepeat = 0;
    int8_t _mouseLeftRightAccel = 0;
    int8_t _mouseUpDownAccel = 0;

    bool _click = true;
};

#endif
