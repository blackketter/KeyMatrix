#ifndef _TypeCommand_
#include "Console.h"
#include "Commands/ShellCommands.h"

////////////////// Type Command
class TypeCommand : public ShellCommand {
  public:
    const char* getName() { return "type"; }
    const char* getHelp() { return ("<...> - Type data to host"); }
    void execute(Console* c, uint8_t paramCount, char** params) {

      for (uint8_t i = 1; i <= paramCount; i++ ) {
        if (i!=1) {
          Keyboard.write(' ');
        }
        Keyboard.print(params[i]);
      }
    }
};
TypeCommand theTypeCommand;

#endif
