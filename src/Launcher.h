#ifndef _Launcher_
#define _Launcher_
#include "App.h"
#include "Console.h"
#include "EventQueue.h"

class Launcher {
  public:
    virtual void begin();  // system setup, calls init() on all apps

    virtual void run();   // event loop calls app run() and idle()

    virtual void idle();   // background processing (esp. for event handling)

    virtual void launchApp(appid_t id);
    virtual void launchApp(App* app);

    App* currentApp() { return _currApp; }
    bool isCurrentApp(App* a) { return currentApp() == a; }
    void exit();

    bool event(Event* e);
    void timeChanged();

    App* getLaunchedApp() { return _launchedApp; }

  protected:
    App* getLastApp() { return _lastApp; }

  private:
    App* _currApp = nullptr;
    App* _launchedApp = nullptr;
    App* _lastApp = nullptr;
};
#endif
