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

#include "ExampleEventHandler.h"
#include "cocos2d.h"
#include "CCStoreInfo.h"
#include "MuffinRushAssets.h"

#define TAG "ExampleEventHandler >>>"

USING_NS_CC;

using namespace soomla;

ExampleEventHandler::ExampleEventHandler() {
    Director::getInstance()->getEventDispatcher()->addCustomEventListener(CCStoreConsts::EVENT_BILLING_NOT_SUPPORTED, CC_CALLBACK_1(ExampleEventHandler::onBillingNotSupported, this));
    Director::getInstance()->getEventDispatcher()->addCustomEventListener(CCStoreConsts::EVENT_BILLING_SUPPORTED, CC_CALLBACK_1(ExampleEventHandler::onBillingSupported, this));
    Director::getInstance()->getEventDispatcher()->addCustomEventListener(CCStoreConsts::EVENT_CURRENCY_BALANCE_CHANGED, CC_CALLBACK_1(ExampleEventHandler::onCurrencyBalanceChanged, this));
    Director::getInstance()->getEventDispatcher()->addCustomEventListener(CCStoreConsts::EVENT_GOOD_BALANCE_CHANGED, CC_CALLBACK_1(ExampleEventHandler::onGoodBalanceChanged, this));
    Director::getInstance()->getEventDispatcher()->addCustomEventListener(CCStoreConsts::EVENT_GOOD_EQUIPPED, CC_CALLBACK_1(ExampleEventHandler::onGoodEquipped, this));
    Director::getInstance()->getEventDispatcher()->addCustomEventListener(CCStoreConsts::EVENT_GOOD_UNEQUIPPED, CC_CALLBACK_1(ExampleEventHandler::onGoodUnEquipped, this));
    Director::getInstance()->getEventDispatcher()->addCustomEventListener(CCStoreConsts::EVENT_GOOD_UPGRADE, CC_CALLBACK_1(ExampleEventHandler::onGoodUpgrade, this));
    Director::getInstance()->getEventDispatcher()->addCustomEventListener(CCStoreConsts::EVENT_ITEM_PURCHASE_STARTED, CC_CALLBACK_1(ExampleEventHandler::onItemPurchaseStarted, this));
    Director::getInstance()->getEventDispatcher()->addCustomEventListener(CCStoreConsts::EVENT_ITEM_PURCHASED, CC_CALLBACK_1(ExampleEventHandler::onItemPurchased, this));
    Director::getInstance()->getEventDispatcher()->addCustomEventListener(CCStoreConsts::EVENT_MARKET_ITEMS_REFRESH_FAILED, CC_CALLBACK_1(ExampleEventHandler::onMarketItemsRefreshFailed, this));
    Director::getInstance()->getEventDispatcher()->addCustomEventListener(CCStoreConsts::EVENT_MARKET_ITEMS_REFRESH_STARTED, CC_CALLBACK_1(ExampleEventHandler::onMarketItemsRefreshStarted, this));
    Director::getInstance()->getEventDispatcher()->addCustomEventListener(CCStoreConsts::EVENT_MARKET_ITEMS_REFRESHED, CC_CALLBACK_1(ExampleEventHandler::onMarketItemsRefreshed, this));
    Director::getInstance()->getEventDispatcher()->addCustomEventListener(CCStoreConsts::EVENT_MARKET_PURCHASE, CC_CALLBACK_1(ExampleEventHandler::onMarketPurchase, this));
    Director::getInstance()->getEventDispatcher()->addCustomEventListener(CCStoreConsts::EVENT_MARKET_PURCHASE_CANCELED, CC_CALLBACK_1(ExampleEventHandler::onMarketPurchaseCancelled, this));
    Director::getInstance()->getEventDispatcher()->addCustomEventListener(CCStoreConsts::EVENT_MARKET_PURCHASE_STARTED, CC_CALLBACK_1(ExampleEventHandler::onMarketPurchaseStarted, this));
    Director::getInstance()->getEventDispatcher()->addCustomEventListener(CCStoreConsts::EVENT_MARKET_PURCHASE_VERIFICATION, CC_CALLBACK_1(ExampleEventHandler::onMarketPurchaseVerification, this));
    Director::getInstance()->getEventDispatcher()->addCustomEventListener(CCStoreConsts::EVENT_RESTORE_TRANSACTION_FINISHED, CC_CALLBACK_1(ExampleEventHandler::onRestoreTransactionsFinished, this));
    Director::getInstance()->getEventDispatcher()->addCustomEventListener(CCStoreConsts::EVENT_RESTORE_TRANSACTION_STARTED, CC_CALLBACK_1(ExampleEventHandler::onMarketItemsRefreshStarted, this));
    Director::getInstance()->getEventDispatcher()->addCustomEventListener(CCStoreConsts::EVENT_SOOMLA_STORE_INITIALIZED, CC_CALLBACK_1(ExampleEventHandler::onSoomlaStoreInitialized, this));
    Director::getInstance()->getEventDispatcher()->addCustomEventListener(CCStoreConsts::EVENT_UNEXPECTED_STORE_ERROR, CC_CALLBACK_1(ExampleEventHandler::onUnexpectedErrorInStore, this));
    Director::getInstance()->getEventDispatcher()->addCustomEventListener(CCStoreConsts::EVENT_IAB_SERVICE_STARTED, CC_CALLBACK_1(ExampleEventHandler::onIabServiceStarted, this));
    Director::getInstance()->getEventDispatcher()->addCustomEventListener(CCStoreConsts::EVENT_IAB_SERVICE_STOPPED, CC_CALLBACK_1(ExampleEventHandler::onIabServiceStopped, this));
    Director::getInstance()->getEventDispatcher()->addCustomEventListener(CCStoreConsts::EVENT_MARKET_REFUND, CC_CALLBACK_1(ExampleEventHandler::onMarketRefund, this));
}

void ExampleEventHandler::onBillingNotSupported(EventCustom *event) {
    CCSoomlaUtils::logDebug(TAG, "BillingNotSupported");
}

void ExampleEventHandler::onBillingSupported(EventCustom *event) {
    CCSoomlaUtils::logDebug(TAG, "BillingSupported");
}

void ExampleEventHandler::onCurrencyBalanceChanged(EventCustom *event) {
    __Dictionary *eventData = (__Dictionary *)event->getUserData();
    CCVirtualCurrency *currency = dynamic_cast<CCVirtualCurrency *>(eventData->objectForKey(CCStoreConsts::DICT_ELEMENT_CURRENCY));
    __Integer *balance = dynamic_cast<__Integer *>(eventData->objectForKey(CCStoreConsts::DICT_ELEMENT_BALANCE));
    __Integer *amountAdded = dynamic_cast<__Integer *>(eventData->objectForKey(CCStoreConsts::DICT_ELEMENT_AMOUNT_ADDED));
    CCSoomlaUtils::logDebug(TAG, __String::createWithFormat("CurrencyBalanceChanged: %s %d %d",
                                                            currency->getItemId()->getCString(),
                                                            balance->getValue(),
                                                            amountAdded->getValue())->getCString());
}

void ExampleEventHandler::onGoodBalanceChanged(EventCustom *event) {
    __Dictionary *eventData = (__Dictionary *)event->getUserData();
    CCVirtualGood *good = dynamic_cast<CCVirtualGood *>(eventData->objectForKey(CCStoreConsts::DICT_ELEMENT_GOOD));
    __Integer *balance = dynamic_cast<__Integer *>(eventData->objectForKey(CCStoreConsts::DICT_ELEMENT_BALANCE));
    __Integer *amountAdded = dynamic_cast<__Integer *>(eventData->objectForKey(CCStoreConsts::DICT_ELEMENT_AMOUNT_ADDED));
    CCSoomlaUtils::logDebug(TAG, __String::createWithFormat("GoodBalanceChanged: %s %d %d",
                                                            good->getItemId()->getCString(),
                                                            balance->getValue(),
                                                            amountAdded->getValue())->getCString());
}

void ExampleEventHandler::onGoodEquipped(EventCustom *event) {
    __Dictionary *eventData = (__Dictionary *)event->getUserData();
    CCEquippableVG *equippable = dynamic_cast<CCEquippableVG *>(eventData->objectForKey(CCStoreConsts::DICT_ELEMENT_EQUIPPABLEVG));
    CCSoomlaUtils::logDebug(TAG, __String::createWithFormat("GoodEquipped: %s", equippable->getItemId()->getCString())->getCString());
}

void ExampleEventHandler::onGoodUnEquipped(EventCustom *event) {
    __Dictionary *eventData = (__Dictionary *)event->getUserData();
    CCEquippableVG *equippable = dynamic_cast<CCEquippableVG *>(eventData->objectForKey(CCStoreConsts::DICT_ELEMENT_EQUIPPABLEVG));
    CCSoomlaUtils::logDebug(TAG, __String::createWithFormat("GoodUnEquipped: %s", equippable->getItemId()->getCString())->getCString());
}

void ExampleEventHandler::onGoodUpgrade(EventCustom *event) {
    __Dictionary *eventData = (__Dictionary *)event->getUserData();
    CCVirtualGood *good = dynamic_cast<CCVirtualGood *>(eventData->objectForKey(CCStoreConsts::DICT_ELEMENT_GOOD));
    CCUpgradeVG *upgrade = dynamic_cast<CCUpgradeVG *>(eventData->objectForKey(CCStoreConsts::DICT_ELEMENT_UPGRADEVG));
    CCSoomlaUtils::logDebug(TAG, __String::createWithFormat("GoodUpgrade: %s with upgrade %s", good->getItemId()->getCString(),
                                                            upgrade->getItemId()->getCString())->getCString());
}

void ExampleEventHandler::onItemPurchased(EventCustom *event) {
    __Dictionary *eventData = (__Dictionary *)event->getUserData();
    CCPurchasableVirtualItem *purchasable = dynamic_cast<CCPurchasableVirtualItem *>(eventData->objectForKey(CCStoreConsts::DICT_ELEMENT_PURCHASABLE));
    __String *payload = dynamic_cast<__String *>(eventData->objectForKey(CCStoreConsts::DICT_ELEMENT_DEVELOPERPAYLOAD));
    CCSoomlaUtils::logDebug(TAG, __String::createWithFormat("ItemPurchased: %s %s",
                                                            purchasable->getItemId()->getCString(),
                                                            payload->getCString())->getCString());
}

void ExampleEventHandler::onItemPurchaseStarted(EventCustom *event) {
    __Dictionary *eventData = (__Dictionary *)event->getUserData();
    CCPurchasableVirtualItem *purchasable = dynamic_cast<CCPurchasableVirtualItem *>(eventData->objectForKey(CCStoreConsts::DICT_ELEMENT_PURCHASABLE));
    CCSoomlaUtils::logDebug(TAG, __String::createWithFormat("ItemPurchaseStarted: %s", purchasable->getItemId()->getCString())->getCString());
}

void ExampleEventHandler::onMarketPurchaseCancelled(EventCustom *event) {
    __Dictionary *eventData = (__Dictionary *)event->getUserData();
    CCPurchasableVirtualItem *purchasable = dynamic_cast<CCPurchasableVirtualItem *>(eventData->objectForKey(CCStoreConsts::DICT_ELEMENT_PURCHASABLE));
    CCSoomlaUtils::logDebug(TAG, __String::createWithFormat("MarketPurchaseCancelled: %s", purchasable->getItemId()->getCString())->getCString());
}

void ExampleEventHandler::onMarketPurchase(EventCustom *event) {
    __Dictionary *eventData = (__Dictionary *)event->getUserData();
    CCPurchasableVirtualItem *purchasable = dynamic_cast<CCPurchasableVirtualItem *>(eventData->objectForKey(CCStoreConsts::DICT_ELEMENT_PURCHASABLE));
    __Dictionary *extraInfo = dynamic_cast<__Dictionary *>(eventData->objectForKey(CCStoreConsts::DICT_ELEMENT_EXTRA_INFO));
    __String *payload = dynamic_cast<__String *>(eventData->objectForKey(CCStoreConsts::DICT_ELEMENT_DEVELOPERPAYLOAD));
    CCSoomlaUtils::logDebug(TAG, __String::createWithFormat("MarketPurchase: %s payload: %s",
            purchasable->getItemId()->getCString(),
            payload->getCString())->getCString());

    if (extraInfo) {
        // Android ONLY
        __String *originalJSON = dynamic_cast<__String *>(extraInfo->objectForKey(CCStoreConsts::DICT_ELEMENT_ORIGINAL_JSON));
        if (originalJSON != NULL) {
            CCSoomlaUtils::logDebug(TAG, __String::createWithFormat("MarketPurchase: Original JSON %s", originalJSON->getCString())->getCString());
        }
        __String *signature = dynamic_cast<__String *>(extraInfo->objectForKey(CCStoreConsts::DICT_ELEMENT_SIGNATURE));
        if (signature != NULL) {
            CCSoomlaUtils::logDebug(TAG, __String::createWithFormat("MarketPurchase: Signature %s", signature->getCString())->getCString());
        }
        __String *userId = dynamic_cast<__String *>(extraInfo->objectForKey(CCStoreConsts::DICT_ELEMENT_USER_ID));
        if (userId != NULL) {
            CCSoomlaUtils::logDebug(TAG, __String::createWithFormat("MarketPurchase: User ID %s", userId->getCString())->getCString());
        }
    }
}

void ExampleEventHandler::onMarketPurchaseStarted(EventCustom *event) {
    __Dictionary *eventData = (__Dictionary *)event->getUserData();
    CCPurchasableVirtualItem *purchasable = dynamic_cast<CCPurchasableVirtualItem *>(eventData->objectForKey(CCStoreConsts::DICT_ELEMENT_PURCHASABLE));
    CCSoomlaUtils::logDebug(TAG, __String::createWithFormat("MarketPurchaseStarted: %s", purchasable->getItemId()->getCString())->getCString());
}

void ExampleEventHandler::onMarketPurchaseVerification(EventCustom *event) {
    __Dictionary *eventData = (__Dictionary *)event->getUserData();
    CCPurchasableVirtualItem *purchasable = dynamic_cast<CCPurchasableVirtualItem *>(eventData->objectForKey(CCStoreConsts::DICT_ELEMENT_PURCHASABLE));
    CCSoomlaUtils::logDebug(TAG, __String::createWithFormat("MarketPurchaseVerification: %s", purchasable->getItemId()->getCString())->getCString());
}

void ExampleEventHandler::onRestoreTransactionsStarted(EventCustom *event) {
    CCSoomlaUtils::logDebug(TAG, "RestoreTransactionsStarted");
}

void ExampleEventHandler::onRestoreTransactionsFinished(EventCustom *event) {
    __Dictionary *eventData = (__Dictionary *)event->getUserData();
    __Bool *success = dynamic_cast<__Bool *>(eventData->objectForKey(CCStoreConsts::DICT_ELEMENT_SUCCESS));
    CCSoomlaUtils::logDebug(TAG, __String::createWithFormat("RestoreTransactionsFinished: %s", success ? "YES" : "NO")->getCString());
}

void ExampleEventHandler::onUnexpectedErrorInStore(EventCustom *event) {
    __Dictionary *eventData = (__Dictionary *)event->getUserData();
    __Integer *errorCode = dynamic_cast<__Integer *>(eventData->objectForKey(CCStoreConsts::DICT_ELEMENT_ERROR_CODE));
    CCSoomlaUtils::logDebug(TAG, __String::createWithFormat("UnexpectedErrorInStore: %d", errorCode->getValue())->getCString());
}

void ExampleEventHandler::onSoomlaStoreInitialized(EventCustom *event) {
    CCSoomlaUtils::logDebug(TAG, "onSoomlaStoreInitialized");
}

void ExampleEventHandler::onMarketItemsRefreshed(EventCustom *event) {
    CCSoomlaUtils::logDebug(TAG, "onMarketItemsRefreshed");
    
    __Dictionary *eventData = (__Dictionary *)event->getUserData();
    __Array *marketItems = dynamic_cast<__Array *>(eventData->objectForKey(CCStoreConsts::DICT_ELEMENT_MARKET_ITEMS));
    
    Ref *object;
    CCARRAY_FOREACH(marketItems, object) {
        CCMarketItem *marketItem = dynamic_cast<CCMarketItem *>(object);
        CCSoomlaUtils::logDebug(TAG, __String::createWithFormat("Market Item: %s %s",
                                                                marketItem->getProductId()->getCString(),
                                                                marketItem->getMarketPriceAndCurrency()->getCString())->getCString());
    }
}

void ExampleEventHandler::onMarketItemsRefreshStarted(EventCustom *event) {
    CCSoomlaUtils::logDebug(TAG, "MarketItemsRefreshStarted");
}

void ExampleEventHandler::onMarketItemsRefreshFailed(EventCustom *event) {
    __Dictionary *eventData = (__Dictionary *)(event->getUserData());
    __String *errorMessage = dynamic_cast<__String *>(eventData->objectForKey(CCStoreConsts::DICT_ELEMENT_ERROR_MESSAGE));
    CCSoomlaUtils::logDebug(TAG, __String::createWithFormat("MarketItemsRefreshFailed %s", errorMessage->getCString())->getCString());
}

void ExampleEventHandler::onMarketRefund(EventCustom *event) {
    CCSoomlaUtils::logDebug(TAG, "MarketRefund");
}

void ExampleEventHandler::onIabServiceStarted(EventCustom *event) {
    CCSoomlaUtils::logDebug(TAG, "IabServiceStarted");
}

void ExampleEventHandler::onIabServiceStopped(EventCustom *event) {
    CCSoomlaUtils::logDebug(TAG, "IabServiceStopped");
}
