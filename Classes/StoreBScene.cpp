/*
 * Copyright (C) 2012 Soomla Inc.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "StoreBScene.h"

#include "Cocos2dxStore.h"
#include "StoreAScene.h"
#include "ExampleEventHandler.h"

/**
 * This is the second scene (the window where the VirtualCurrencyPacks are shown).
 * In this file you can find example calls to the store's interfaces.
 **/

USING_NS_CC;
using namespace soomla;

CCScene* StoreBScene::getStoreBScene() {
    CCNodeLoaderLibrary * ccNodeLoaderLibrary = CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary();

    ccNodeLoaderLibrary->registerCCNodeLoader("StoreBScene", StoreBSceneLoader::loader());

    CCBReader *ccbReader = new CCBReader(ccNodeLoaderLibrary);
    ccbReader->retain();
    CCScene *pScene = ccbReader->createSceneWithNodeGraphFromFile("ccb/StoreBScene.ccbi");
    ccbReader->release();
    return pScene;
}

bool StoreBScene::init() {

    for (unsigned int i = 0; i < GOODS_NUMBER; i++) {
        mGoodTitles[i]       = NULL;
        mGoodDescriptions[i] = NULL;
        mPrices[i]           = NULL;
    }

    return true;
}

void StoreBScene::onBack(CCObject* pSender) {

    CC_UNUSED_PARAM(pSender);

    CCScene *s = StoreAScene::getGoodsStoreScene();
    CCDirector::sharedDirector()->setDepthTest(true);
    CCTransitionScene *transition = CCTransitionMoveInL::create(0.8f, s);

    CCDirector::sharedDirector()->replaceScene(transition);
}


void StoreBScene::onBuy(CCObject* pSender) {
    if (pSender) {
        int tag = ((CCNode*)pSender)->getTag();
        string itemId = itemIdFromTag(tag);
        CCError *soomlaError = NULL;
        CCStoreInventory::sharedStoreInventory()->buyItem(itemId.c_str(), &soomlaError);
        if (soomlaError) {
            CCStoreUtils::logException("StoreBScene::onBuy", soomlaError);
            return;
        }
    }
}

string StoreBScene::itemIdFromTag(int tag) {
    switch (tag) {
        case 0: return "no_ads";
        case 1: return "muffins_10";
        case 2: return "muffins_50";
        case 3: return "muffins_400";
        case 4: return "muffins_1000";
        default: return "ERROR";
    }
}

void StoreBScene::onEnter() {
    CCLayer::onEnter();
    CCNotificationCenter::sharedNotificationCenter()->addObserver(this,
            callfuncO_selector(StoreBScene::updateCurrencyBalance),
            EVENT_ON_CURRENCY_BALANCE_CHANGED, NULL);
}

void StoreBScene::onExit() {
    CCNotificationCenter::sharedNotificationCenter()->removeObserver(this, EVENT_ON_CURRENCY_BALANCE_CHANGED);
    CCLayer::onExit();
}

void StoreBScene::onNodeLoaded(CCNode *pNode, CCNodeLoader *pNodeLoader) {

    CC_UNUSED_PARAM(pNode);
    CC_UNUSED_PARAM(pNodeLoader);

    CC_ASSERT(mBackgroundNode);
    CC_ASSERT(mMainNode);
    CC_ASSERT(mTopNode);
    CC_ASSERT(mBottomNode);
    CC_ASSERT(mMuffinAmount);

    for (unsigned int i = 0; i < GOODS_NUMBER; i++) {
        CC_ASSERT(mGoodTitles[i]       );
        CC_ASSERT(mGoodDescriptions[i] );
        CC_ASSERT(mPrices[i]           );

        CCError *soomlaError = NULL;
        CCVirtualItem *virtualItem = CCStoreInfo::sharedStoreInfo()->getItemByItemId(
                mGoodTitles[i]->getString(), &soomlaError);
        if (soomlaError) {
            CCStoreUtils::logException("StoreBScene", soomlaError);
            continue;
        }
        CC_ASSERT(virtualItem);
        CCPurchasableVirtualItem *purchasableVirtualItem = dynamic_cast<CCPurchasableVirtualItem *>(virtualItem);
        CC_ASSERT(purchasableVirtualItem);
        CCPurchaseWithMarket *purchaseWithMarket = dynamic_cast<CCPurchaseWithMarket *>(purchasableVirtualItem->getPurchaseType());
        CC_ASSERT(purchaseWithMarket);
        double price = purchaseWithMarket->getMarketItem()->getPrice()->getValue();

        mGoodTitles[i]->setString(virtualItem->getName()->getCString());
        mGoodDescriptions[i]->setString(virtualItem->getDescription()->getCString());
        mPrices[i]->setString(CCString::createWithFormat("%.2f", price)->getCString());

    }

    applyScaleForNode(this);
    fill(mBackgroundNode);
    shiftToTop(mTopNode);
    shiftToBottom(mBottomNode);

    this->setKeypadEnabled(true);

    CCError *soomlaError = NULL;
    int balance = CCStoreInventory::sharedStoreInventory()->getItemBalance("currency_muffin", &soomlaError);
    if (soomlaError) {
        CCStoreUtils::logException("StoreBScene", soomlaError);
        balance = 0;
        CCLog("Soomla balance error");
    }
    updateCurrencyBalance(CCInteger::create(balance));
}

SEL_MenuHandler StoreBScene::onResolveCCBCCMenuItemSelector(CCObject *pTarget, char const *pSelectorName) {
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onBuy", StoreBScene::onBuy)
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onBack", StoreBScene::onBack)
    return NULL;
}

bool StoreBScene::onAssignCCBMemberVariable(CCObject *pTarget, char const *pMemberVariableName, CCNode *pNode) {
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mBackgroundNode", CCNode *, mBackgroundNode)
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mMainNode", CCNode *, mMainNode)
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mTopNode", CCNode *, mTopNode)
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mBottomNode", CCNode *, mBottomNode)
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mMuffinAmount", CCLabelTTF *, mMuffinAmount)

    if (strcmp(pMemberVariableName, ("mGoodTitles")) == 0) {
        mGoodTitles[pNode->getTag()] = (CCLabelTTF *) pNode;
        return true;
    }
    if (strcmp(pMemberVariableName, ("mGoodDescriptions")) == 0) {
        mGoodDescriptions[pNode->getTag()] = (CCLabelTTF *) pNode;
        return true;
    }
    if (strcmp(pMemberVariableName, ("mPrices")) == 0) {
        mPrices[pNode->getTag()] = (CCLabelTTF *) pNode;
        return true;
    }

    return false;
}

void StoreBScene::updateCurrencyBalance(CCInteger *pBalance) {
    char buf[20] = "/0";
    sprintf(buf, "%i", pBalance->getValue());
    mMuffinAmount->setString(buf);
}



