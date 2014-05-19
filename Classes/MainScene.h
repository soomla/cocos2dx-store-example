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

#ifndef __MAIN_SCENE_H__
#define __MAIN_SCENE_H__

#include "cocos2d.h"
#include "cocos-ext.h"

USING_NS_CC;
USING_NS_CC_EXT;

class Soomla : public CCSprite, public CCTargetedTouchDelegate {
public:

    CREATE_FUNC(Soomla);

};

/**
 \class MainScene
 \brief This class represents the welcome scene.
 
 This class contains functions that operate the welcome screen.
 In this file you can find example calls to the store's interfaces.
 **/
class MainScene:
    public cocos2d::CCLayer,
    public cocos2d::extension::CCBSelectorResolver,
    public cocos2d::extension::CCBMemberVariableAssigner,
    public cocos2d::extension::CCNodeLoaderListener {

public:
    CREATE_FUNC(MainScene);

    MainScene():
        mBackgroundNode(NULL)
        , mMainNode(NULL)
        , mUnlockArea(NULL)
        , mUnlocker(NULL)
    {}
    static cocos2d::CCScene* getMainScene();

    virtual void keyBackClicked()
	{
		CCDirector::sharedDirector()->end();
	}

    virtual bool ccTouchBegan(CCTouch* touch, CCEvent* event);
    virtual void ccTouchMoved(CCTouch* touch, CCEvent* event);
    virtual void ccTouchEnded(CCTouch* touch, CCEvent* event);

    virtual void onEnter();
    virtual void onExit();

    virtual SEL_MenuHandler onResolveCCBCCMenuItemSelector(CCObject *pTarget, char const *pSelectorName);
    virtual SEL_CCControlHandler onResolveCCBCCControlSelector(CCObject *pTarget, char const *pSelectorName);
    virtual bool onAssignCCBMemberVariable(CCObject *pTarget, char const *pMemberVariableName, CCNode *pNode);
    virtual void onNodeLoaded(CCNode *pNode, CCNodeLoader *pNodeLoader);
    
private:
    CCPoint mOriginalPos;
private:
    CCNode* mBackgroundNode;
    CCNode* mMainNode;
    CCNode* mUnlockArea;
    CCNode* mUnlocker;
        
    };

class MainSceneLoader: public cocos2d::extension::CCLayerLoader {
public:
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(MainSceneLoader, loader);
    CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(MainScene);
};


#endif // __MainScene_SCENE_H__
