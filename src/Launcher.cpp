#include "Launcher.h"
#include "Timer.h"
#include "Console.h"
extern Console console;

#include "TypeCommand.h"

void Launcher::begin() {
  return;
  // initialize apps
  App* anApp;
  int i;

  i = 0;
  anApp = App::getFirstApp();
  while (anApp) {
    console.debugf("%d\n",i++);
//    console.debugln(anApp->id());
//    console.debug(anApp->name());
    anApp->init();
//    console.println("...inited");
    anApp = anApp->getNextApp();
//    console.debugf("*** next:%d\n",(int)anApp);
//    console.debugln(anApp->name());
    delay(20);
  }
  console.debugln("apps inited");
}

// todo: sort the app list by priority instead of going through the list over and over again
bool Launcher::event(Event* e) {
  bool consumed = false;
//  console.debugln("\n\n****BEGIN Processing event****");
  App* anApp = App::getFirstApp();
  EventPriority lowestPriority = PRIORITY_NORMAL;
  EventPriority currentPriority = PRIORITY_NORMAL;

  // find the lowest priority to start
  while (anApp != nullptr) {
    currentPriority = anApp->eventPriority();
//    console.debugf("Priority: %s %d\n", anApp->name(), currentPriority);

    if (currentPriority < lowestPriority) {
      lowestPriority = currentPriority;
    }
    anApp = anApp->getNextApp();
  }


  // iterate through the priorities in order, starting with the lowest
  currentPriority = lowestPriority;
  EventPriority nextPriority = currentPriority;

  do {
    anApp = App::getFirstApp();
//    console.debugf("***Current Priority: %d\n", currentPriority);
    // go through list looking for the current priority and process those
    while (anApp != nullptr) {
      EventPriority appPriority = anApp->eventPriority();
//      console.debugf("Checking: %s %d\n", anApp->name(), appPriority);

      if (appPriority == currentPriority) {
        // if this app is eating the event, then return immediately
//        console.debugln("  ---Processing event");
        consumed = anApp->event(e);
        if (consumed) {
//            console.debugln("  EVENT CONSUMED");
            break;
        }

      } else if (appPriority > currentPriority){
        if ((nextPriority == currentPriority) || (appPriority < nextPriority)) {
          nextPriority = appPriority;
        }
      }
      anApp = anApp->getNextApp();
    }
    if (consumed) {
      break;
    }
    if (nextPriority == currentPriority) {
      break;
    } else {
      currentPriority = nextPriority;
    }

  } while (true);
  return consumed;
}

void Launcher::run() {
  //  Do we have a new app to launch
  if (_launchedApp) {
    if (_launchedApp != _currApp) {
      // end the old app
      if (_currApp) {
        _currApp->end();
      }
      // Launch it
      _lastApp = currentApp();
      _currApp = _launchedApp;

      console.debugf("begin app: %s\n", _currApp->name());
      _currApp->begin();
    }
    _launchedApp = nullptr;
  }

// Run it
  if (_currApp) {
    _currApp->run();
  }

// Idle system
  idle();
}

void Launcher::launchApp(App* app) {
  if (app) {
    _launchedApp = app;
  } else {
    console.debugln("Can't switch to null newApp, bailing");
  }
}

void Launcher::launchApp(appid_t id) {
  launchApp(App::getAppByID(id));
}

