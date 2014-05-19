/*
 Copyright (C) 2012-2014 Soomla Inc.
 
 Licensed under the Apache License, Version 2.0 (the "License");
 you may not use this file except in compliance with the License.
 You may obtain a copy of the License at
 
 http://www.apache.org/licenses/LICENSE-2.0
 
 Unless required by applicable law or agreed to in writing, software
 distributed under the License is distributed on an "AS IS" BASIS,
 WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 See the License for the specific language governing permissions and
 limitations under the License.
 */

#ifndef  _APP_DELEGATE_H_
#define  _APP_DELEGATE_H_

#include "cocos2d.h"
#include "ExampleEventHandler.h"

/**
 \class AppDelegate
 \brief This class contains functions to launch, stop, and re-start the app.
 
 This class contains functions to launch the application, pause/stop the game, 
 and re-start the game after a pause.
 */
class AppDelegate : private cocos2d::CCApplication {
 private:
    ExampleEventHandler* handler;
 
public:
    /**
     Constructor.
     */
    AppDelegate();
    
    /**
     Destructor. 
     */
    virtual ~AppDelegate();
    
    /**
     Creates the game's Store Assets, initializes `CCStoreController`, and sets 
     the display to be the main screen of the game.
     */
    virtual bool applicationDidFinishLaunching();
    
    /**
     Pauses animation.
     */
    virtual void applicationDidEnterBackground();
    
    /**
     Starts animation.
     */
    virtual void applicationWillEnterForeground();
};

#endif /* !_APP_DELEGATE_H_ */

