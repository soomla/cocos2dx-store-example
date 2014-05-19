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

#ifndef __ExampleEventHandler__
#define __ExampleEventHandler__

#include <string>
#include "CCEventHandler.h"


#define EVENT_ON_CURRENCY_BALANCE_CHANGED "onCurrencyBalanceChanged"
#define EVENT_ON_GOOD_BALANCE_CHANGED "onGoodBalanceChanged"
#define EVENT_ON_GOOD_EQUIPPED "onGoodEquipped"
#define EVENT_ON_GOOD_UNEQUIPPED "onGoodUnEquipped"
#define EVENT_ON_GOOD_UPGRADE "onGoodUpgrade"

using namespace std;

/**
 \class ExampleEvnetHandler
 \brief Handles events in Muffin Rush.
 
 This class contains functions that handle fired events with behavior that are 
 game-specific to Muffin Rush.
 */
class ExampleEventHandler : public soomla::CCEventHandler {

public:

    /**
     see parent.
     */
    virtual void onBillingNotSupported();

    /**
     see parent.
     */
    virtual void onBillingSupported();

    /**
     see parent.
     */
    virtual void onCurrencyBalanceChanged(soomla::CCVirtualCurrency *virtualCurrency, int balance, int amountAdded);

    /**
     see parent.
     */
    virtual void onGoodBalanceChanged(soomla::CCVirtualGood *virtualGood, int balance, int amountAdded);

    /**
     see parent.
     */
    virtual void onGoodEquipped(soomla::CCEquippableVG *equippableVG);

    /**
     see parent.
     */
    virtual void onGoodUnEquipped(soomla::CCEquippableVG *equippableVG);

    /**
     see parent.
     */
    virtual void onGoodUpgrade(soomla::CCVirtualGood *virtualGood, soomla::CCUpgradeVG *upgradeVG);

    /**
     see parent.
     */
    virtual void onItemPurchased(soomla::CCPurchasableVirtualItem *purchasableVirtualItem);

    /**
     see parent.
     */
    virtual void onItemPurchaseStarted(soomla::CCPurchasableVirtualItem *purchasableVirtualItem);

    /**
     see parent.
     */
    virtual void onMarketPurchaseCancelled(soomla::CCPurchasableVirtualItem *purchasableVirtualItem);

    /**
     see parent.
     */
    virtual void onMarketPurchase(soomla::CCPurchasableVirtualItem *purchasableVirtualItem, cocos2d::CCString *receiptUrl);

    /**
     see parent.
     */
    virtual void onMarketPurchaseStarted(soomla::CCPurchasableVirtualItem *purchasableVirtualItem);

    /**
     see parent.
     */
    virtual void onMarketPurchaseVerification(soomla::CCPurchasableVirtualItem *purchasableVirtualItem);

    /**
     see parent.
     */
    virtual void onRestoreTransactionsFinished(bool success);

    /**
     see parent.
     */
    virtual void onRestoreTransactionsStarted();

    /**
     see parent.
     */
    virtual void onUnexpectedErrorInStore();

    /**
     see parent.
     */
    virtual void onStoreControllerInitialized();

    /**
     see parent.
     */
    virtual void onMarketItemsRefreshed();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    
    /**
     see parent.
     */
    virtual void onMarketRefund(soomla::CCPurchasableVirtualItem *purchasableVirtualItem);
	
    /**
     see parent.
     */
    virtual void onIabServiceStarted();
	
    /**
     see parent.
     */
    virtual void onIabServiceStopped();
#endif

};

#endif /* !__ExampleEventHandler__ */
