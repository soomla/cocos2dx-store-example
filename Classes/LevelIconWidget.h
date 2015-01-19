//
// Created by vedi on 2/4/13.
//


#ifndef __LevelIconWidget_H_
#define __LevelIconWidget_H_

#include "cocos2d.h"
#include "cocos-ext.h"


USING_NS_CC;
USING_NS_CC_EXT;


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
    void updateAfford();

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
    bool mUpgradable;
    bool mEquiped;
    int mCurrentBalance;

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
