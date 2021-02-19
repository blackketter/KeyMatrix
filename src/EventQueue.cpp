#include "KeyMatrix.h"
#include "EventQueue.h"
#include "Console.h"
#include "KeyInfo.h"
#include "Keyboard.h"
#include "Mouse.h"

#ifndef CORE_TEENSY
#define MOUSE_BACK 8
#define MOUSE_FORWARD 16
#endif

bool keyDebug = false;

void repeatTimerCallback(void* kq) { ((EventQueue*)kq)->repeat(); };

EventQueue::EventQueue(int maxEventHistory) {
  _maxEventHistory = maxEventHistory;
  _repeatTimer.setMillis(_repeatInterval, repeatTimerCallback, this, true);
}

keyswitch_t EventQueue::sendKeys() {
  Event* event = peekNextEvent();
  keyswitch_t count = 0;

  while (event) {
    if (event->time() > Uptime::millis()) {
      if (keyDebug) console.debugln("key in future, not sending");
      break;
    }
    event = getNextEvent();
    sendKey(event->code(), event->pressed());
    count++;
    event = peekNextEvent();
  }
  return count;
}

void EventQueue::releaseKeys() {
  if (keyDebug)  console.debugln("release keys");
  Event* k = lastEvent();
  while (k) {
    if (keyIsDown(k->code())) {
      Keyboard.release(k->code());
    }
    k = prevEvent(k);
  }
}

void EventQueue::sendKey(keycode_t code, boolean pressed) {
  if (!isSoftKeyCode(code)) {
    if (pressed) {
      Keyboard.press(code);
      if (keyDebug)  console.debugf("send key press[%d]\n", code);
    } else {
      Keyboard.release(code);
      if (keyDebug)  console.debugf("send key release[%d]\n", code);
    }
  } else {
    switch (code) {
      case KEY_MOUSE_MOVE_UP:
        if (pressed) {
          if (_mouseUpDownAccel >= 0) {
            _mouseUpDownAccel = -10;
          } else if (_mouseUpDownAccel > -100) {
            _mouseUpDownAccel += _mouseUpDownAccel / 10;
          }
          Mouse.move(0, _mouseUpDownAccel);
        } else {
          _mouseUpDownAccel = 0;
        }
        break;
      case KEY_MOUSE_MOVE_DOWN:
        if (pressed) {
          if (_mouseUpDownAccel <= 0) {
            _mouseUpDownAccel = 10;
          } else if (_mouseUpDownAccel < 100) {
            _mouseUpDownAccel += _mouseUpDownAccel / 10;
          }
          Mouse.move(0, _mouseUpDownAccel);
        } else {
          _mouseUpDownAccel = 0;
        }
        break;
      case KEY_MOUSE_MOVE_LEFT:
        if (pressed) {
          if (_mouseLeftRightAccel >= 0) {
            _mouseLeftRightAccel = -10;
          } else if (_mouseLeftRightAccel > -100) {
            _mouseLeftRightAccel += _mouseLeftRightAccel / 10;
          }
          Mouse.move(_mouseLeftRightAccel, 0);
        } else {
          _mouseLeftRightAccel = 0;
        }
        break;
      case KEY_MOUSE_MOVE_RIGHT:
        if (pressed) {
          if (_mouseLeftRightAccel <= 0) {
            _mouseLeftRightAccel = 10;
          } else if (_mouseLeftRightAccel < 100) {
            _mouseLeftRightAccel += _mouseLeftRightAccel / 10;
          }
          Mouse.move(_mouseLeftRightAccel, 0);
        } else {
          _mouseLeftRightAccel = 0;
        }
        break;
      case KEY_MOUSE_BUTTON_LEFT:
        pressed ? Mouse.press(MOUSE_LEFT) : Mouse.release(MOUSE_LEFT);
        break;
      case KEY_MOUSE_BUTTON_MIDDLE:
        pressed ? Mouse.press(MOUSE_MIDDLE) : Mouse.release(MOUSE_MIDDLE);
        break;
      case KEY_MOUSE_BUTTON_RIGHT:
        pressed ? Mouse.press(MOUSE_RIGHT) : Mouse.release(MOUSE_RIGHT);
        break;
      case KEY_MOUSE_BUTTON_BACK:
        pressed ? Mouse.press(MOUSE_BACK) : Mouse.release(MOUSE_BACK);
        break;
      case KEY_MOUSE_BUTTON_FORWARD:
        pressed ? Mouse.press(MOUSE_FORWARD) : Mouse.release(MOUSE_FORWARD);
        break;
      case KEY_MOUSE_SCROLL_UP:
        if (pressed) Mouse.move(0,0,-1);
        break;
      case KEY_MOUSE_SCROLL_DOWN:
        if (pressed) Mouse.move(0,0,+1);
        break;
#ifdef CORE_TEENSY
      case KEY_MOUSE_SCROLL_LEFT:
        if (pressed) Mouse.scroll(0, -1);
        break;
      case KEY_MOUSE_SCROLL_RIGHT:
        if (pressed) Mouse.scroll(0, 1);
        break;
#endif
      default:
        // ignore
        break;

    }
  }
}

const keycode_t mouseRepeatKeys[] = {
  KEY_MOUSE_MOVE_UP,
  KEY_MOUSE_MOVE_DOWN,
  KEY_MOUSE_MOVE_LEFT,
  KEY_MOUSE_MOVE_RIGHT,
  KEY_MOUSE_SCROLL_UP,
  KEY_MOUSE_SCROLL_DOWN,
  KEY_MOUSE_SCROLL_LEFT,
  KEY_MOUSE_SCROLL_RIGHT,
  NO_CODE
};

void EventQueue::repeat() {
  int i = 0;
  keycode_t c = mouseRepeatKeys[i];
  millis_t now = Uptime::millis();
  while (c != NO_CODE) {
    Event* e = lastEvent(c);
    if (e && e->pressed() && ((now - e->time() > _repeatStart) || ((now - _lastRepeat) < _repeatStart))) {
      if (keyDebug)  console.debugf(" repeating code:%d\n",c);
      if (!e->isMouseMoveKey()) { sendKey(c,0); }
      sendKey(c,1);
      _lastRepeat = now;
    }
    c = mouseRepeatKeys[i++];
  }
}

void EventQueue::truncateHistory() {
  Event* curr = _events;

  // find the nth event
  for (int i = 0; i < _maxEventHistory; i++) {
    if (curr == nullptr) {
      //console.debugln("not enough events");
      return;
    }
    curr = curr->getPrev();
  }

  // if there is one, remove the reference to it to truncate
  if (curr) {
    curr->getNext()->setPrev(nullptr);
  }

  // delete it and all the ones after it
  while (curr) {
    Event* last = curr;
    curr = curr->getPrev();
    delete last;
    if (keyDebug) console.debugln("deleted old event");
  }
}

Event* EventQueue::peekNextEvent() {
  Event* next = _lastEvent;
  if (next == nullptr) {
    next = firstEvent();
  } else {
    next = _lastEvent->getNext();
  }
  return next;
}

Event* EventQueue::getNextEvent() {
  Event* next = peekNextEvent();
  if (next) {
    _lastEvent = next;
  }
  return next;
}

class KeyDebugCommand : public Command {
  public:
    const char* getName() { return "keys"; }
    const char* getHelp() { return "toggle key event debug output"; }
    void execute(Console* c, uint8_t paramCount, char** params) {
      keyDebug = !keyDebug;
      c->printf("Key event debug: %s", keyDebug ? "enabled\n" : "disabled\n");
    }
};
KeyDebugCommand theKeyDebugCommand;

void EventQueue::addEvent(keycode_t c, bool d) {
  addEvent(nullptr, NO_KEY, c, Uptime::millis(), d);
}

void EventQueue::addEvent(KeyMatrix* m, keyswitch_t k, keycode_t c, millis_t t, bool d) {
// note that this may be called recursively

/*
  if (d && keyIsDown(c)) {
    console.debugln(" ignoring duplicate key down event");
    return;
  } else if (!d && keyIsUp(c)) {
    console.debugln(" ignoring duplicate key up event");
    return;
  }
*/

  char ch = getKeyChar(c);
  Event* e = new Event(m, k,c,ch,t,d);
  if (e == nullptr) {
    console.debugln("Failed to allocate new Event!");
    return;
  }
  if (keyDebug) {
      console.debugf("key addEvent: \"%s\", switch: %d, code: %d, char: 0x%02x, %s, %s, time:%d.%03d\n",
        getKeyLabel(c), k, c, ch, d ? "pressed" : "released", m == nullptr ? "soft" : "hard", (int)(t/1000), (int)((t%1000)));
     }
  if (_events) {
    _events->setNext(e);
    e->setPrev(_events);
  }

  _events = e;

  processEvent(e);

//  console.debugln("truncating");
  truncateHistory();

//  console.debugln("done addEvent");

}

void EventQueue::removeEvent(Event* k) {
  if (keyDebug) {
    console.debugf("key removeEvent: switch: %d, code: %d, char: %c, pressed: %d, %s\n",
                k->keyswitch(), k->code(), k->character(), k->pressed(), k->matrix() == nullptr ? "soft" : "hard");
  }
  Event* curr = _events;
  while (curr) {
    if (curr == k) {
      Event* prev = k->getPrev();
      Event* next = k->getNext();
      if (prev) {
        prev->setNext(next);
      }
      if (next) {
        next->setPrev(prev);
      }
      if (_events == k) {
        _events = prev;
      }
      if (_lastEvent == k) {
        _lastEvent = next;
      }
      delete k;
      curr = nullptr;
    } else {
      curr = curr->getPrev();
    }
  }
};


bool EventQueue::keyTapped(keycode_t c) {
  Event* h0 = history(0);
  Event* h1 = history(1);
  if (h0 && h1 &&
        (h1->code() == c) && h1->pressed() &&
        (h0->code() == c) && h0->released() &&
        ((h0->time() - h1->time()) < _tappedTime)
     ) {
    return true;
  } else {
    return false;
  }
}

bool EventQueue::keyTapHeld(keycode_t c) {
  Event* h0 = history(0);
  Event* h1 = history(1);
  Event* h2 = history(2);
  if (h0 && h1 && h2) {
    if (
        (h2->code() == c) && h2->pressed() &&
        (h1->code() == c) && h1->released() &&
        (h0->code() == c) && h0->pressed() &&
        ((h0->time() - h2->time()) < _doubleTappedTime)
       ) {
      return true;
    } else {
      return false;
    }
  }
  return false;
}

bool EventQueue::keyDoubleTapped(keycode_t c) {
  Event* h0 = history(0);
  Event* h2 = history(2);
  Event* h3 = history(3);
  if ( h0 && h2 && h3 &&
         keyTapped(c) &&
        (h3->code() == c) && h3->pressed() &&
        (h2->code() == c) && h2->released() &&
        (h0->time() - h3->time() < _doubleTappedTime)
     ) {
    return true;
  } else {
    return false;
  }
}


char EventQueue::getKeyChar(keycode_t c) {
  const keyinfo_t* info = getKeyInfo(c);
  if (info) {
    bool shifted = keyIsDown(MODIFIERKEY_LEFT_SHIFT) || keyIsDown(MODIFIERKEY_RIGHT_SHIFT);
    if (shifted) {
      int i = 0;
      while (shiftedKeys[i].code != NO_CODE) {
        if (shiftedKeys[i].code == c) {
          return shiftedKeys[i].c;
        }
        i++;
      }
    }
    return info->c;
  } else {
    return 0;
  }
}

void EventQueue::printStatus(Stream* c) {
  if (c == nullptr) { c = &console; }
  c->println("---------------");
  c->println("Key Events:");
  Event* event = _events;
  int i = 0;
  while (event) {
    c->printf("  Key event[%2d] =%8d.%03d '%s' code:%d switch:%d %s %s\n",
      i, ((int)(event->time()))/1000, ((int)(event->time()))%1000,
      getKeyLabel(event->code()),event->code(), event->keyswitch(),
      event->pressed() ? "down" : "up", event->matrix() ? "hard" : "soft");
    event = event->getPrev();
    i++;
  }
  c->println("---------------");
}

