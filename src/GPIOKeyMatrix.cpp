#include "GPIOKeyMatrix.h"

//////////////////////////////////////////////////
// GPIOKeyMatrix
//////////////////////////////////////////////////
GPIOKeyMatrix::GPIOKeyMatrix(const keylayout_t* keylayout, const keymap_t* keymap, uint8_t rows, uint8_t columns, const pinNumber* rowPins, const pinNumber* columnPins) {
  _numRows = rows;
  _numColumns = columns;
  _curState = new uint8_t[_numColumns];
  _lastState = new uint8_t[_numColumns];
  _changedKeys = new uint8_t[_numColumns];
  _rowPin = rowPins;
  _columnPin = columnPins;
  _defaultMap = keymap;
  _defaultLayout = keylayout;
}

GPIOKeyMatrix::~GPIOKeyMatrix() {
  delete(_curState);
  delete(_lastState);
  delete(_changedKeys);
}

// Diodes have cathodes (positive) on rows, anodes on columns
void GPIOKeyMatrix::begin(EventQueue* queue) {
  KeyMatrix::begin(queue);
  for (int i = 0; i < _numRows;i++) {
    pinMode(_rowPin[i], OUTPUT);
    digitalWrite(_rowPin[i], HIGH);
  }

  for (int i = 0; i < _numColumns; i++) {
    pinMode(_columnPin[i], INPUT_PULLUP);
  }
}

void GPIOKeyMatrix::scanMatrix() {
  for (int i = 0; i < _numColumns; i++) {
    _curState[i] = 0;
  }

  for (int i = 0; i < _numRows; i++) {
    digitalWrite(_rowPin[i], LOW);
    delayMicroseconds(500);
    for (int j = 0; j < _numColumns; j++) {
      // active low
      if (!digitalRead(_columnPin[j])) {
        _curState[j] = _curState[j] | (0x01 << i);
      }
    }
    digitalWrite(_rowPin[i], HIGH);
  }

  for (int i = 0; i < _numColumns; i++) {
    _changedKeys[i] = _lastState[i] ^ _curState[i];
  }

  // save the last state
  for (int i = 0; i < _numColumns; i++) {
    _lastState[i] = _curState[i];
  }
}

boolean GPIOKeyMatrix::idle() {

  keyswitch_t count = 0;

  clearKeyChanges();

  millis_t now = Uptime::millis();

  //console.debugf("checking now: %d.%03d _nextScan: %d.%03d\n", (int)(now/1000),(int)(now%1000), (int)(_nextScan/1000),(int)(_nextScan%1000));

  if (now >= _nextScan) {
    //console.debugln("scanning");
    scanMatrix();
    keyswitch_t total = _numRows * _numColumns;

    for (keyswitch_t i = 0; i < total; i++) {
      if ((i != NO_KEY) && ((_changedKeys[i/_numRows] >> (i%_numRows)) & 0x01)) {
        count++;
        bool d = switchIsDown(i);
        if (keyDebug) console.debugf("GPIO key %d %s\n", i, d ? "down" : "up");
        _queue->addEvent(this, i,getCode(i),now, d);
      }
    }
    if (count) {
      _nextScan = now + _debounceInterval;
      if (keyDebug) console.debugf("update found %d key events, next scan: %d.%03d\n",count, (int)(_nextScan/1000),(int)(_nextScan%1000));
    } else {
      _nextScan = now + _minScanInterval;
    }
  }
  return count != 0;
}

void GPIOKeyMatrix::clearKeyChanges() {
  // save the last state
  for (int i = 0; i < _numColumns; i++) {
    _changedKeys[i] = 0;
  }
}

