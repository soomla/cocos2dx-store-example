//
// Created by Alexandr on 31.05.13.
//


#include "StoreAScene.h"
#include "MainScene.h"
#include "StoreBScene.h"
#include "Cocos2dxStore.h"
#include "ExampleEventHandler.h"

using namespace soomla;


StoreAScene::StoreAScene() {
    mBackgroundNode = NULL;
    mBackground = NULL;
    mMainNode = NULL;
    mTopNode = NULL;
    mMuffinAmount = NULL;
    mGoodsTableView = NULL;
    for(int i = 0; i < NUMBER_OF_ROWS; i++ ) {
        mListRows[i] = NULL;
        mListItem[i] = NULL;
        mCacheListItems[i] = NULL;
    }
    mBottomNode = NULL;
    mButtonBack = NULL;
    mButtonMoreMuffins = NULL;
}

StoreAScene::~StoreAScene() {
    for(int i = 0; i < NUMBER_OF_ROWS; i++) {
        CC_SAFE_RELEASE(mListRows[i]);
    }
}

bool StoreAScene::onAssignCCBMemberVariable(CCObject *pTarget, char const *pMemberVariableName, CCNode *pNode) {
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mBackgroundNode", CCNode*, mBackgroundNode)
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mBackground", CCLayerColor*, mBackground)
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mMainNode", CCNode*, mMainNode)
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mTopNode", CCNode*, mTopNode)
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mMuffinAmount", CCLabelTTF*, mMuffinAmount)
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mGoodsTableView", CCTableView*, mGoodsTableView)
    if(strcmp(pMemberVariableName, "mListRows") == 0) {
        mListRows[pNode->getTag()] = static_cast<CCTableViewCell*>(pNode);
        return true;
    } else if(strcmp(pMemberVariableName, "mListItem") == 0) {
        mListItem[pNode->getTag()] = dynamic_cast<LevelIconWidget*>(pNode);
        return true;
    }
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mBottomNode", CCNode*, mBottomNode)
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mButtonBack", CCMenuItemImage*, mButtonBack)
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mButtonMoreMuffins", CCMenuItemImage*, mButtonMoreMuffins)

    return false;
}

void StoreAScene::onNodeLoaded(CCNode *pNode, CCNodeLoader *pNodeLoader) {
    CC_UNUSED_PARAM(pNode);
    CC_UNUSED_PARAM(pNodeLoader);

    CC_ASSERT(mBackgroundNode);
    CC_ASSERT(mBackground);
    CC_ASSERT(mMainNode);
    CC_ASSERT(mTopNode);
    CC_ASSERT(mMuffinAmount);
    CC_ASSERT(mGoodsTableView);
    for(int i = 0; i < NUMBER_OF_ROWS; i++ ) {
        CC_ASSERT(mListRows[i]);
        mListRows[i]->retain();
        mListRows[i]->removeFromParentAndCleanup(false);
        mListRows[i]->setPosition(CCPointZero);

        CC_ASSERT(mListItem[i]);
    }
    CC_ASSERT(mBottomNode);
    CC_ASSERT(mButtonBack);
    CC_ASSERT(mButtonMoreMuffins);

    applyScaleForNode(this);
    fill(mBackgroundNode);
    putToCenterMiddleOf(mMainNode, mBackgroundNode);
    shiftToTop(mTopNode);
    shiftToBottom(mBottomNode);

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    CCSoomlaStore::getInstance()->startIabServiceInBg();
#endif

    ////*****
    for (int i = 0; i < NUMBER_OF_ROWS; i++) {
        string itemId = itemIdFromTag(i);
        if (itemId != "ERROR") {
            std::string name = " ";
            std::string info = " ";

            CCError *soomlaError = NULL;

            CCVirtualItem *virtualItem;
            virtualItem = CCStoreInfo::sharedStoreInfo()->getItemByItemId(itemId.c_str(), &soomlaError);
            if (!soomlaError) {
                name = virtualItem->getName()->getCString();
                info = virtualItem->getDescription()->getCString();
            } else {
                CCSoomlaUtils::logException("StoreAScene::createListViewItem", soomlaError);
            }

            soomlaError = NULL;
            int balance = CCStoreInventory::sharedStoreInventory()->getItemBalance(itemId.c_str(), &soomlaError);
            if (soomlaError) {
                CCSoomlaUtils::logException("StoreAScene::getItemBalance", soomlaError);
                balance = 0;
                CC_ASSERT(false);
            }
            if (itemId.compare("show_room") == 0 || itemId.compare("delivery_vehicle") == 0) {
                setProgressForItem(itemId, mListItem[i]);
            }
            else if (itemId.compare("fat_cat") == 0
                    || itemId.compare("happi_hippo") == 0
                    || itemId.compare("funkey_monkey") == 0) {
                setEquippedForItem(itemId, mListItem[i]);
            }

            CCPurchasableVirtualItem *purchasableVirtualItem = dynamic_cast<CCPurchasableVirtualItem *>(virtualItem);
            double price;
            if (purchasableVirtualItem != NULL) {
                CCPurchaseType *purchaseType = purchasableVirtualItem->getPurchaseType();
                if (dynamic_cast<CCPurchaseWithMarket *>(purchaseType)) {
                    price = static_cast<CCPurchaseWithMarket *>(purchaseType)->getMarketItem()->getPrice()->getValue();
                } else if (dynamic_cast<CCPurchaseWithVirtualItem *>(purchaseType)) {
                    price = static_cast<CCPurchaseWithVirtualItem *>(purchaseType)->getAmount()->getValue();
                } else {
                    price = -1;
                }
            } else {
                price = -1;
            }

            mListItem[i]->setData(itemId.c_str(), name.c_str(), info.c_str(), price, balance);
        }
    }

    //////******
    mGoodsTableView->setBounceable(true);
    mGoodsTableView->setDataSource(this);
    mGoodsTableView->setDelegate(this);
    mGoodsTableView->reloadData();

    CCError *soomlaError = NULL;
    int balance = CCStoreInventory::sharedStoreInventory()->getItemBalance("currency_muffin", &soomlaError);
    if (soomlaError) {
        CCSoomlaUtils::logException("StoreAScene::setCurrencyBalanceLabel", soomlaError);
        balance = 0;
        CCLog("Soomla balance error");
    }

    updateCurrencyBalance(CCInteger::create(balance));
}

SEL_MenuHandler StoreAScene::onResolveCCBCCMenuItemSelector(CCObject *pTarget, char const *pSelectorName) {
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onBack", StoreAScene::onBack)
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onMoreMuffins", StoreAScene::onMoreMuffins)

    return NULL;
}

void StoreAScene::onMoreMuffins(CCObject *pSender) {
    CC_UNUSED_PARAM(pSender);

    CCScene *s = StoreBScene::getStoreBScene();
    CCDirector::sharedDirector()->setDepthTest(true);
    CCTransitionScene *transition = CCTransitionMoveInR::create(0.8f, s);

    CCDirector::sharedDirector()->replaceScene(transition);
}


void StoreAScene::onEnter() {
    CCLayer::onEnter();
    
    CCNotificationCenter::sharedNotificationCenter()->addObserver(this, callfuncO_selector(StoreAScene::onCurrencyBalanceChanged),
                                                                  CCStoreConsts::EVENT_CURRENCY_BALANCE_CHANGED, NULL);
    CCNotificationCenter::sharedNotificationCenter()->addObserver(this, callfuncO_selector(StoreAScene::updateGoodBalance),
                                                                  CCStoreConsts::EVENT_GOOD_BALANCE_CHANGED, NULL);
    CCNotificationCenter::sharedNotificationCenter()->addObserver(this, callfuncO_selector(StoreAScene::onGoodEquipped),
                                                                  CCStoreConsts::EVENT_GOOD_EQUIPPED, NULL);
    CCNotificationCenter::sharedNotificationCenter()->addObserver(this, callfuncO_selector(StoreAScene::onGoodUnEquipped),
                                                                  CCStoreConsts::EVENT_GOOD_UNEQUIPPED, NULL);
    CCNotificationCenter::sharedNotificationCenter()->addObserver(this, callfuncO_selector(StoreAScene::onGoodUpgrade),
                                                                  CCStoreConsts::EVENT_GOOD_UPGRADE, NULL);
}

void StoreAScene::onExit() {
    CCNotificationCenter::sharedNotificationCenter()->removeObserver(this, CCStoreConsts::EVENT_CURRENCY_BALANCE_CHANGED);
    CCNotificationCenter::sharedNotificationCenter()->removeObserver(this, CCStoreConsts::EVENT_GOOD_BALANCE_CHANGED);
    CCNotificationCenter::sharedNotificationCenter()->removeObserver(this, CCStoreConsts::EVENT_GOOD_EQUIPPED);
    CCNotificationCenter::sharedNotificationCenter()->removeObserver(this, CCStoreConsts::EVENT_GOOD_UNEQUIPPED);
    CCNotificationCenter::sharedNotificationCenter()->removeObserver(this, CCStoreConsts::EVENT_GOOD_UPGRADE);
    CCLayer::onExit();
}

void StoreAScene::onBack(CCObject *pSender) {
    CC_UNUSED_PARAM(pSender);

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    CCSoomlaStore::getInstance()->stopIabServiceInBg();
#endif

    CCScene *s = MainScene::getMainScene();
    CCDirector::sharedDirector()->setDepthTest(true);
    CCTransitionScene *transition = CCTransitionMoveInL::create(0.8f, s);

    CCDirector::sharedDirector()->replaceScene(transition);
}

string StoreAScene::itemIdFromTag(int tag) {
    string ret;
    switch (tag) {
        case 1:
            ret = "fruit_cake";
            return ret;
        case 2:
            ret = "pavlova";
            return ret;
        case 3:
            ret = "pavlova_10";
            return ret;
        case 4:
            ret = "chocolate_cake";
            return ret;
        case 5:
            ret = "cream_cup";
            return ret;
        case 6:
            ret = "cream_cup_10";
            return ret;
        case 8:
            ret = "show_room";
            return ret;
        case 9:
            ret = "delivery_vehicle";
            return ret;
        case 11:
            ret = "fat_cat";
            return ret;
        case 12:
            ret = "happi_hippo";
            return ret;
        case 13:
            ret = "funkey_monkey";
            return ret;
        default:
            ret = "ERROR";
            return ret;
    }
}

CCScene *StoreAScene::getGoodsStoreScene() {
    CCNodeLoaderLibrary * ccNodeLoaderLibrary = CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary();

    ccNodeLoaderLibrary->registerCCNodeLoader("StoreAScene", StoreASceneLoader::loader());
    ccNodeLoaderLibrary->registerCCNodeLoader("LevelIconWidget", LevelIconWidgetLoader::loader());
    ccNodeLoaderLibrary->registerCCNodeLoader("CCTableView", CCTableViewLoader::loader());
    ccNodeLoaderLibrary->registerCCNodeLoader("CCTableViewCell", CCTableViewCellLoader::loader());

    CCBReader *ccbReader = new cocos2d::extension::CCBReader(ccNodeLoaderLibrary);

    return ccbReader->createSceneWithNodeGraphFromFile("ccb/StoreAScene.ccbi");
}

void StoreAScene::onCurrencyBalanceChanged(cocos2d::CCDictionary *eventData) {
    CCInteger *pBalance = dynamic_cast<CCInteger *>(eventData->objectForKey(CCStoreConsts::DICT_ELEMENT_BALANCE));
    
    updateCurrencyBalance(pBalance);
}

void StoreAScene::updateCurrencyBalance(CCInteger *pBalance) {
    char buf[20] = "/0";
    sprintf(buf, "%i", pBalance->getValue());
    mMuffinAmount->setString(buf);
    
    for (unsigned int i = 0; i < NUMBER_OF_ROWS; i++) {
        mListItem[i]->updateAfford();
    }
}

void StoreAScene::updateGoodBalance(cocos2d::CCDictionary *eventData) {
    soomla::CCVirtualGood *virtualGood = dynamic_cast<CCVirtualGood *>(eventData->objectForKey(CCStoreConsts::DICT_ELEMENT_GOOD));
    CCInteger *balance = dynamic_cast<CCInteger *>(eventData->objectForKey(CCStoreConsts::DICT_ELEMENT_BALANCE));

    ////*****
    for (unsigned int i = 0; i < NUMBER_OF_ROWS; i++) {
        string itemId = itemIdFromTag(i);
        if (virtualGood->getItemId()->compare(itemId.c_str()) == 0) {
            mListItem[i]->setBalance(balance->getValue());
            break;
        }
    }
}


void StoreAScene::onGoodEquipped(cocos2d::CCDictionary *eventData) {
    soomla::CCEquippableVG *virtualGood = dynamic_cast<CCEquippableVG *>(eventData->objectForKey(CCStoreConsts::DICT_ELEMENT_EQUIPPABLEVG));
    
    for (unsigned int i = 0; i < NUMBER_OF_ROWS; i++) {
        string itemId = itemIdFromTag(i);
        if (virtualGood->getItemId()->compare(itemId.c_str()) == 0) {
            mListItem[i]->setEquiped(true);
            break;
        }
    }
}

void StoreAScene::onGoodUnEquipped(cocos2d::CCDictionary *eventData) {
    soomla::CCEquippableVG *virtualGood = dynamic_cast<CCEquippableVG *>(eventData->objectForKey(CCStoreConsts::DICT_ELEMENT_EQUIPPABLEVG));
    
    for (unsigned int i = 0; i < NUMBER_OF_ROWS; i++) {
        string itemId = itemIdFromTag(i);
        if (virtualGood->getItemId()->compare(itemId.c_str()) == 0) {
            mListItem[i]->setEquiped(false);
            break;
        }
    }
}

void StoreAScene::onGoodUpgrade(cocos2d::CCDictionary *eventData) {
    soomla::CCVirtualGood *virtualGood = dynamic_cast<CCVirtualGood *>(eventData->objectForKey(CCStoreConsts::DICT_ELEMENT_GOOD));
    
    for (unsigned int i = 0; i < NUMBER_OF_ROWS; i++) {
        string itemId = itemIdFromTag(i);
        if (virtualGood->getItemId()->compare(itemId.c_str()) == 0) {
            setProgressForItem(itemId, mListItem[i]);
            break;
        }
    }
}

CCTableViewCell *StoreAScene::tableCellAtIndex(CCTableView *table, unsigned int idx) {
    CC_UNUSED_PARAM(table);

    return mListRows[NUMBER_OF_ROWS - idx - 1];
}

unsigned int StoreAScene::numberOfCellsInTableView(CCTableView *table) {
    CC_UNUSED_PARAM(table);

    return NUMBER_OF_ROWS;
}

CCSize StoreAScene::tableCellSizeForIndex(CCTableView *table, unsigned int idx) {
    CC_UNUSED_PARAM(table);

    return mListRows[NUMBER_OF_ROWS - idx - 1]->getContentSize();
}


void StoreAScene::setProgressForItem(string &itemId, LevelIconWidget *pWidget) {
    CCError *soomlaError = NULL;
    int progress = CCStoreInventory::sharedStoreInventory()->getGoodUpgradeLevel(itemId.c_str(), &soomlaError);
    if (soomlaError) {
        CCSoomlaUtils::logException("StoreAScene::setProgressForItem", soomlaError);
        progress = 0;
        CC_ASSERT(false);
    }
    pWidget->setProgress(progress);
}

void StoreAScene::setEquippedForItem(string &itemId, LevelIconWidget *pWidget) {
    CCError *soomlaError = NULL;
    bool equipped = CCStoreInventory::sharedStoreInventory()->isVirtualGoodEquipped(itemId.c_str(), &soomlaError);
    if (soomlaError) {
        CCSoomlaUtils::logException("StoreAScene::setEquippedForItem", soomlaError);
        equipped = false;
        CC_ASSERT(false);
    }
    pWidget->setEquiped(equipped);
}

//Utils

float applyScaleForNode(cocos2d::CCNode* node) {
    cocos2d::CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    float scale = std::min(winSize.width / node->getContentSize().width,
            winSize.height / node->getContentSize().height);
    node->setScale(scale);
    node->setPosition(ccp((winSize.width - node->getContentSize().width * scale) / 2,
    (winSize.height - node->getContentSize().height * scale) / 2));

    return scale;
}

void fill(cocos2d::CCNode* targetNode) {
    CCPoint leftBottom =
            targetNode->getParent()->convertToWorldSpace(targetNode->getPosition());
    CCPoint rightTop =
            targetNode->getParent()->convertToWorldSpace(
                    ccpAdd(targetNode->getPosition(), ccpFromSize(targetNode->getContentSize())));

    CCSize winSize = CCDirector::sharedDirector()->getWinSize();

    float scaleX = winSize.width / (rightTop.x - leftBottom.x);
    float scaleY = winSize.height / (rightTop.y - leftBottom.y);

    targetNode->setScale(MAX(scaleX, scaleY));
}

void shiftToLeftBottom(cocos2d::CCNode* targetNode) {
    CCPoint position = targetNode->getParent()->convertToNodeSpace(ccp(0, 0));
    targetNode->setPosition(position);
}

void shiftToTop(cocos2d::CCNode* targetNode) {
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    CCPoint position =
            targetNode->getParent()->convertToNodeSpace(ccp(winSize.width, winSize.height));
    targetNode->setPositionY(position.y);
}

void shiftToBottom(cocos2d::CCNode* targetNode) {
    CCPoint position = targetNode->getParent()->convertToNodeSpace(ccp(0, 0));
    targetNode->setPositionY(position.y);
}

void fillWidth(cocos2d::CCNode* targetNode) {
    CCPoint leftBottom =
            targetNode->getParent()->convertToWorldSpace(targetNode->getPosition());
    CCPoint rightTop =
            targetNode->getParent()->convertToWorldSpace(
                    ccpAdd(targetNode->getPosition(), ccpFromSize(targetNode->getContentSize())));

    CCSize winSize = CCDirector::sharedDirector()->getWinSize();

    targetNode->setScale(winSize.width / (rightTop.x - leftBottom.x));
}

void putToCenterMiddleOf(cocos2d::CCNode* targetNode, cocos2d::CCNode* anchorNode) {

    CCPoint leftBottom =
            anchorNode->convertToWorldSpaceAR(
                    ccpSub(CCPointZero, ccpCompMult(
                            ccp(anchorNode->getAnchorPoint().x, anchorNode->getAnchorPoint().y),
                            ccpFromSize(anchorNode->getContentSize()))));
    CCPoint rightTop =
            anchorNode->convertToWorldSpaceAR(
                    ccpAdd(CCPointZero, ccpCompMult(
                            ccp(1 - anchorNode->getAnchorPoint().x, 1 - anchorNode->getAnchorPoint().y),
                            ccpFromSize(anchorNode->getContentSize()))));

    CCPoint globalPosition = ccp(leftBottom.x + (rightTop.x - leftBottom.x) / 2, leftBottom.y + (rightTop.y - leftBottom.y) / 2);

    targetNode->setPosition(targetNode->getParent()->convertToNodeSpace(globalPosition));
}

