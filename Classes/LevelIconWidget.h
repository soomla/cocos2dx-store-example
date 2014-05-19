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

// Created by vedi on 2/4/13.


#ifndef __LevelIconWidget_H_
#define __LevelIconWidget_H_

#include "cocos2d.h"
#include "cocos-ext.h"


USING_NS_CC;
USING_NS_CC_EXT;

/**
 \class LevelIconWidget
 \brief This class is a building block of the scroll list in `StoreAScene`.
 */
class LevelIconWidget: public CCNode,
                       public CCBSelectorResolver,
                       public CCBMemberVariableAssigner,
                       public CCNodeLoaderListener {
public:

    CREATE_FUNC(LevelIconWidget);

    LevelIconWidget();

    virtual bool onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode);
    virtual SEL_MenuHandler onResolveCCBCCMenuItemSelector(CCObject *pTarget, char const *pSelectorName);
    virtual SEL_CCControlHandler onResolveCCBCCControlSelector(CCObject * pTarget, const char* pSelectorName);
    virtual void onNodeLoaded(CCNode * pNode, CCNodeLoader * pNodeLoader);

    void setData(char const *itemId, char const *name, char const *description, double price, int balance);
    void setBalance(int balance);
    void setProgress(int progress);
    void setEquiped(bool equiped);

private:
    std::string mItemId;
private:
    CCLabelTTF *mGoodsTitle;
    CCLabelTTF *mDescriptionLabel;
    CCSprite *mProgressBar;
    CCSprite *mProgressLevel1;
    CCNode *mMenu;
    CCMenuItemImage *mButtonBuy;
    CCMenuItemImage *mButtonUpgrade;
    CCMenuItemImage *mEquipment;
    CCLabelTTF *mPrice;
    CCLabelTTF *mBalance;

    bool mEquipable;
    bool mEquiped;

    //selectors
    void onBuy(CCObject *pSender);
    void onUpgrade(CCObject *pSender);
    void onEquipment(CCObject *pSender);
};


class LevelIconWidgetLoader : public cocos2d::extension::CCNodeLoader {
public:
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(LevelIconWidgetLoader, loader);
    CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(LevelIconWidget);
};

#endif //__LevelIconWidget_H_
