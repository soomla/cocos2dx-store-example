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

#ifndef __STOREB_SCENE_H__
#define __STOREB_SCENE_H__

#include "cocos2d.h"
#include "cocos-ext.h"
#include <string>

USING_NS_CC;
USING_NS_CC_EXT;

using namespace std;

#define GOODS_NUMBER 5

/**
 \class StoreBScene
 \brief This class represents the screen that displays the store's available 
 currency packs.
 
 This is the second scene (the window where the VirtualCurrencyPacks are shown).
 In this file you can find example calls to the store's interfaces.
 **/
class StoreBScene :
    public CCLayer,
    public CCBSelectorResolver,
    public CCBMemberVariableAssigner,
    public CCNodeLoaderListener {
private:
    string itemIdFromTag(int tag);
		
public:
    CREATE_FUNC(StoreBScene);
    StoreBScene():
        mBackgroundNode(NULL)
        , mMainNode(NULL)
        , mTopNode(NULL)
        , mBottomNode(NULL)
        , mMuffinAmount(NULL)
    {}

    static cocos2d::CCScene*getStoreBScene();

    virtual void onEnter();
    virtual void onExit();

    virtual SEL_MenuHandler onResolveCCBCCMenuItemSelector(CCObject *pTarget, char const *pSelectorName);
    virtual SEL_CCControlHandler onResolveCCBCCControlSelector(CCObject *pTarget, char const *pSelectorName) {return NULL;}
    virtual bool onAssignCCBMemberVariable(CCObject *pTarget, char const *pMemberVariableName, CCNode *pNode);
    virtual void onNodeLoaded(CCNode *pNode, CCNodeLoader *pNodeLoader);

    virtual void updateCurrencyBalance(CCInteger *pBalance);
private:
    CCNode* mBackgroundNode;
    CCNode* mMainNode;
    CCNode *mTopNode;
    CCNode *mBottomNode;

    CCLabelTTF *mMuffinAmount;

    CCLabelTTF *mGoodTitles[GOODS_NUMBER];
    CCLabelTTF *mGoodDescriptions[GOODS_NUMBER];
    CCLabelTTF *mPrices[GOODS_NUMBER];

    virtual bool init();  

	void onBack(CCObject* pSender);
        
	void onBuy(CCObject* pSender);

    virtual void keyBackClicked()
	{
        onBack(NULL);
	}
    
};

class StoreBSceneLoader: public cocos2d::extension::CCLayerLoader {
public:
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(StoreBSceneLoader, loader);
    CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(StoreBScene);
};

#endif // __MainScene_SCENE_H__
