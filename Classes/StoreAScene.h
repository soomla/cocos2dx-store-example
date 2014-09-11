//
// Created by Alexandr on 31.05.13.
//



#ifndef __StoreAScene_H_
#define __StoreAScene_H_

#include "LevelIconWidget.h"

#include "cocos2d.h"
#include "Cocos2dxStore.h"
#include "cocos-ext.h"

USING_NS_CC;
USING_NS_CC_EXT;

#define NUMBER_OF_ROWS 14

class StoreAScene : public CCLayer,
                        public CCBSelectorResolver,
                        public CCBMemberVariableAssigner,
                        public CCNodeLoaderListener,
                        public CCTableViewDataSource,
                        public CCTableViewDelegate
{
public:
    static CCScene* getGoodsStoreScene();

    CREATE_FUNC(StoreAScene);
    virtual ~StoreAScene();

protected:
    StoreAScene();

    virtual SEL_MenuHandler onResolveCCBCCMenuItemSelector(CCObject *pTarget, char const *pSelectorName);
    virtual SEL_CCControlHandler onResolveCCBCCControlSelector(CCObject *pTarget, char const *pSelectorName) {return NULL;};
    virtual bool onAssignCCBMemberVariable(CCObject *pTarget, char const *pMemberVariableName, CCNode *pNode);
    virtual void onNodeLoaded(CCNode *pNode, CCNodeLoader *pNodeLoader);

    virtual void onEnter();
    virtual void onExit();

private:
    virtual void updateCurrencyBalance(CCInteger *pBalance);
    virtual void updateGoodBalance(CCArray *pParams);
    virtual void onGoodEquipped(soomla::CCVirtualGood *virtualGood);
    virtual void onGoodUnEquipped(soomla::CCVirtualGood *virtualGood);
    virtual void onGoodUpgrade(soomla::CCVirtualGood *virtualGood);

    //ccb
    CCNode *mBackgroundNode;
    CCLayerColor *mBackground;
    CCNode *mMainNode;
    CCNode *mTopNode;
    CCLabelTTF *mMuffinAmount;
    CCTableView *mGoodsTableView;
    CCTableViewCell *mListRows[NUMBER_OF_ROWS];
    LevelIconWidget *mListItem[NUMBER_OF_ROWS];
    CCNode *mBottomNode;
    CCMenuItemImage *mButtonBack;
    CCMenuItemImage *mButtonMoreMuffins;

    //selectors
    void onBack(CCObject *pSender);
    void onMoreMuffins(CCObject *pSender);

    //class vars
    LevelIconWidget *mCacheListItems[NUMBER_OF_ROWS];

    std::basic_string<char> itemIdFromTag(int tag);

    virtual CCTableViewCell *tableCellAtIndex(CCTableView *table, unsigned int idx);
    virtual unsigned int numberOfCellsInTableView(CCTableView *table);
    virtual CCSize tableCellSizeForIndex(CCTableView *table, unsigned int idx);
    virtual void tableCellTouched(CCTableView *table, CCTableViewCell *cell) {}
    virtual void scrollViewDidScroll(CCScrollView *view) {};
    virtual void scrollViewDidZoom(CCScrollView *view) {};

    void setProgressForItem(std::string &itemId, LevelIconWidget *pWidget);
    void setEquippedForItem(std::string &itemId, LevelIconWidget *pWidget);
};

class StoreASceneLoader : public cocos2d::extension::CCLayerLoader {
public:
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(StoreASceneLoader, loader);
    CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(StoreAScene);
};

class CCTableViewLoader : public CCScrollViewLoader {
public:
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(CCTableViewLoader, loader);
protected:
    virtual CCTableView * createCCNode(cocos2d::CCNode * pParent, cocos2d::extension::CCBReader * pCCBReader) {
        CCTableView *pRet = new CCTableView();
        pRet->initWithViewSize(CCSizeZero, NULL);
        pRet->autorelease();
        pRet->setDataSource(NULL);
        return pRet;
    }
};

class CCTableViewCellLoader : public CCNodeLoader {
public:
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(CCTableViewCellLoader, loader);
protected:
    virtual CCTableViewCell * createCCNode(cocos2d::CCNode * pParent, cocos2d::extension::CCBReader * pCCBReader) {
        CCTableViewCell *pRet = new CCTableViewCell();
        pRet->init();
        pRet->autorelease();
        return pRet;
    }
};

//Utils methods
float applyScaleForNode(cocos2d::CCNode* node);

void fill(cocos2d::CCNode* targetNode);

void shiftToLeftBottom(cocos2d::CCNode* targetNode);

void shiftToTop(cocos2d::CCNode* targetNode);

void shiftToBottom(cocos2d::CCNode* targetNode);

void fillWidth(cocos2d::CCNode* targetNode);

void putToCenterMiddleOf(cocos2d::CCNode* targetNode, cocos2d::CCNode* anchorNode);

#endif //__StoreAScene_H_
