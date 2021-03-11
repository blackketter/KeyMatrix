#ifndef _App_
#define _App_

#include "Event.h"

// how early should an app get an opportunity to process events via event()
enum EventPriority {
    PRIORITY_FIRST = -1000,
    PRIORITY_EARLY = -500,
    PRIORITY_MIDDLE = 0,
    PRIORITY_NORMAL = 500,
    PRIORITY_LAST = 1000,
    PRIORITY_END = 9999,
};

typedef const char* appid_t;

class App {
  public:
    App() { addApp(this); };

    virtual const char* name() = 0;
    virtual appid_t id() = 0;

    virtual void init() {};  // initialize app once, typically at system startup
    virtual void begin() {}; // called once when an app is launched
    virtual void run() {};   // called periodically while app is launched
    virtual void end();      // called after final run(), lets app clean up, releasing any memory temporarily allocated for runs

    // give apps an opportuntity to process events before the launched/running app consumes them
    // return true if the event is consumed and should not be further processed
    virtual bool event(Event* key);

    // returns indication of how early this app wants to process events
    virtual EventPriority eventPriority() { return PRIORITY_NORMAL; };

    bool isID(appid_t match);
    static App* getFirstApp() { return _appList; }
    inline App* getNextApp() { return _nextApp; }

    static App* getAppByID(appid_t appID);
    static App* findApp(const char* s);

    static void sortApps();

  protected:
    static const millis_t _maxRunTime = 10;

  private:
    static void setFirstApp(App* a) { _appList = a; }
    inline void setNextApp(App* app) {  _nextApp = app; };
    static void addApp(App* app) {
      app->setNextApp(_appList);
      _appList = app;
    }

    App* _nextApp = nullptr;
    static App* _appList;
};

#endif


