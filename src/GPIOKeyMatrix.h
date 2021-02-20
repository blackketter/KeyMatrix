#ifndef _GPIOKeyMatrix_
#define _GPIOKeyMatrix_
#include "KeyMatrix.h"

class GPIOKeyMatrix : public KeyMatrix {
  public:
    GPIOKeyMatrix(const keylayout_t* keylayout, const keymap_t* keymap, uint8_t rows, uint8_t columnns, const pinNumber* rowPins, const pinNumber* columnPins);
    ~GPIOKeyMatrix();
    void begin(EventQueue* queue);
    boolean idle();
    bool switchIsDown(keyswitch_t k) { return ((_curState[k/_numRows] >> (k%_numRows)) & 0x01); }
    bool switchIsUp(keyswitch_t k) { return !switchIsDown(k); }

  private:
    uint8_t _numRows;
    uint8_t _numColumns;
    const pinNumber* _rowPin;
    const pinNumber* _columnPin;

    void scanMatrix();
    void clearKeyChanges();

    uint8_t* _curState;  // assumes less than 8 rows
    uint8_t* _lastState;
    uint8_t* _changedKeys;


};
#endif
