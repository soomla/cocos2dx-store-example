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
#include "CCSoomlaMacros.h"

using namespace std;

class ExampleEventHandler : public cocos2d::CCObject{
public:
    
    ExampleEventHandler();

    virtual void onBillingNotSupported(cocos2d::CCDictionary *eventData);

    virtual void onBillingSupported(cocos2d::CCDictionary *eventData);

    virtual void onCurrencyBalanceChanged(cocos2d::CCDictionary *eventData);

    virtual void onGoodBalanceChanged(cocos2d::CCDictionary *eventData);

    virtual void onGoodEquipped(cocos2d::CCDictionary *eventData);

    virtual void onGoodUnEquipped(cocos2d::CCDictionary *eventData);

    virtual void onGoodUpgrade(cocos2d::CCDictionary *eventData);

    virtual void onItemPurchased(cocos2d::CCDictionary *eventData);

    virtual void onItemPurchaseStarted(cocos2d::CCDictionary *eventData);

    virtual void onMarketPurchaseCancelled(cocos2d::CCDictionary *eventData);

    virtual void onMarketPurchase(cocos2d::CCDictionary *eventData);

    virtual void onMarketPurchaseStarted(cocos2d::CCDictionary *eventData);

    virtual void onMarketPurchaseVerification(cocos2d::CCDictionary *eventData);
    virtual void onRestoreTransactionsStarted(cocos2d::CCDictionary *eventData);

    virtual void onRestoreTransactionsFinished(cocos2d::CCDictionary *eventData);

    virtual void onUnexpectedStoreError(cocos2d::CCDictionary *eventData);

    virtual void onSoomlaStoreInitialized(cocos2d::CCDictionary *eventData);

    virtual void onMarketItemsRefreshed(cocos2d::CCDictionary *eventData);

    virtual void onMarketItemsRefreshStarted(cocos2d::CCDictionary *eventData);
    
    virtual void onMarketItemsRefreshFailed(cocos2d::CCDictionary *eventData);

    // Android Only
    virtual void onMarketRefund(cocos2d::CCDictionary *eventData);
	virtual void onIabServiceStarted(cocos2d::CCDictionary *eventData);
	virtual void onIabServiceStopped(cocos2d::CCDictionary *eventData);
};

#endif /* !__ExampleEventHandler__ */
