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

class ExampleEventHandler : public soomla::CCEventHandler {
public:

    virtual void onBillingNotSupported();

    virtual void onBillingSupported();

    virtual void onCurrencyBalanceChanged(soomla::CCVirtualCurrency *virtualCurrency, int balance, int amountAdded);

    virtual void onGoodBalanceChanged(soomla::CCVirtualGood *virtualGood, int balance, int amountAdded);

    virtual void onGoodEquipped(soomla::CCEquippableVG *equippableVG);

    virtual void onGoodUnEquipped(soomla::CCEquippableVG *equippableVG);

    virtual void onGoodUpgrade(soomla::CCVirtualGood *virtualGood, soomla::CCUpgradeVG *upgradeVG);

    virtual void onItemPurchased(soomla::CCPurchasableVirtualItem *purchasableVirtualItem);

    virtual void onItemPurchaseStarted(soomla::CCPurchasableVirtualItem *purchasableVirtualItem);

    virtual void onMarketPurchaseCancelled(soomla::CCPurchasableVirtualItem *purchasableVirtualItem);

    virtual void onMarketPurchase(soomla::CCPurchasableVirtualItem *purchasableVirtualItem, cocos2d::CCString *receiptUrl);

    virtual void onMarketPurchaseStarted(soomla::CCPurchasableVirtualItem *purchasableVirtualItem);

    virtual void onMarketPurchaseVerification(soomla::CCPurchasableVirtualItem *purchasableVirtualItem);

    virtual void onRestoreTransactionsFinished(bool success);

    virtual void onRestoreTransactionsStarted();

    virtual void onUnexpectedErrorInStore();

    virtual void onStoreControllerInitialized();

    virtual void onMarketItemsRefreshed();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    virtual void onMarketRefund(soomla::CCPurchasableVirtualItem *purchasableVirtualItem);
	virtual void onIabServiceStarted();
	virtual void onIabServiceStopped();
#endif

};

#endif /* !__ExampleEventHandler__ */
