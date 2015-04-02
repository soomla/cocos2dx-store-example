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
#include "Cocos2dxStore.h"
#include "cocos2d.h"
#include "MuffinRushAssets.h"

#define TAG "ExampleEventHandler >>>"

USING_NS_CC;
using namespace soomla;

ExampleEventHandler::ExampleEventHandler() {
    CCNotificationCenter::sharedNotificationCenter()->addObserver(this, callfuncO_selector(ExampleEventHandler::onBillingNotSupported), CCStoreConsts::EVENT_BILLING_NOT_SUPPORTED, NULL);
    CCNotificationCenter::sharedNotificationCenter()->addObserver(this, callfuncO_selector(ExampleEventHandler::onBillingSupported), CCStoreConsts::EVENT_BILLING_SUPPORTED, NULL);
    CCNotificationCenter::sharedNotificationCenter()->addObserver(this, callfuncO_selector(ExampleEventHandler::onCurrencyBalanceChanged), CCStoreConsts::EVENT_CURRENCY_BALANCE_CHANGED, NULL);
    CCNotificationCenter::sharedNotificationCenter()->addObserver(this, callfuncO_selector(ExampleEventHandler::onGoodBalanceChanged), CCStoreConsts::EVENT_GOOD_BALANCE_CHANGED, NULL);
    CCNotificationCenter::sharedNotificationCenter()->addObserver(this, callfuncO_selector(ExampleEventHandler::onGoodEquipped), CCStoreConsts::EVENT_GOOD_EQUIPPED, NULL);
    CCNotificationCenter::sharedNotificationCenter()->addObserver(this, callfuncO_selector(ExampleEventHandler::onGoodUnEquipped), CCStoreConsts::EVENT_GOOD_UNEQUIPPED, NULL);
    CCNotificationCenter::sharedNotificationCenter()->addObserver(this, callfuncO_selector(ExampleEventHandler::onGoodUpgrade), CCStoreConsts::EVENT_GOOD_UPGRADE, NULL);
    CCNotificationCenter::sharedNotificationCenter()->addObserver(this, callfuncO_selector(ExampleEventHandler::onItemPurchaseStarted), CCStoreConsts::EVENT_ITEM_PURCHASE_STARTED, NULL);
    CCNotificationCenter::sharedNotificationCenter()->addObserver(this, callfuncO_selector(ExampleEventHandler::onItemPurchased), CCStoreConsts::EVENT_ITEM_PURCHASED, NULL);
    CCNotificationCenter::sharedNotificationCenter()->addObserver(this, callfuncO_selector(ExampleEventHandler::onMarketItemsRefreshFailed),
                                                                  CCStoreConsts::EVENT_MARKET_ITEMS_REFRESH_FAILED, NULL);
    CCNotificationCenter::sharedNotificationCenter()->addObserver(this, callfuncO_selector(ExampleEventHandler::onMarketItemsRefreshStarted),
                                                                  CCStoreConsts::EVENT_MARKET_ITEMS_REFRESH_STARTED, NULL);
    CCNotificationCenter::sharedNotificationCenter()->addObserver(this, callfuncO_selector(ExampleEventHandler::onMarketItemsRefreshed), CCStoreConsts::EVENT_MARKET_ITEMS_REFRESHED, NULL);
    CCNotificationCenter::sharedNotificationCenter()->addObserver(this, callfuncO_selector(ExampleEventHandler::onMarketPurchase), CCStoreConsts::EVENT_MARKET_PURCHASE, NULL);
    CCNotificationCenter::sharedNotificationCenter()->addObserver(this, callfuncO_selector(ExampleEventHandler::onMarketPurchaseCancelled),
                                                                  CCStoreConsts::EVENT_MARKET_PURCHASE_CANCELED, NULL);
    CCNotificationCenter::sharedNotificationCenter()->addObserver(this, callfuncO_selector(ExampleEventHandler::onMarketPurchaseStarted), CCStoreConsts::EVENT_MARKET_PURCHASE_STARTED, NULL);
    CCNotificationCenter::sharedNotificationCenter()->addObserver(this, callfuncO_selector(ExampleEventHandler::onMarketPurchaseVerification),
                                                                  CCStoreConsts::EVENT_MARKET_PURCHASE_VERIFICATION, NULL);
    CCNotificationCenter::sharedNotificationCenter()->addObserver(this, callfuncO_selector(ExampleEventHandler::onRestoreTransactionsFinished),
                                                                  CCStoreConsts::EVENT_RESTORE_TRANSACTION_FINISHED, NULL);
    CCNotificationCenter::sharedNotificationCenter()->addObserver(this, callfuncO_selector(ExampleEventHandler::onMarketItemsRefreshStarted),
                                                                  CCStoreConsts::EVENT_RESTORE_TRANSACTION_STARTED, NULL);
    CCNotificationCenter::sharedNotificationCenter()->addObserver(this, callfuncO_selector(ExampleEventHandler::onSoomlaStoreInitialized), CCStoreConsts::EVENT_SOOMLA_STORE_INITIALIZED, NULL);
    CCNotificationCenter::sharedNotificationCenter()->addObserver(this, callfuncO_selector(ExampleEventHandler::onUnexpectedErrorInStore),
                                                                  CCStoreConsts::EVENT_UNEXPECTED_ERROR_IN_STORE, NULL);
    CCNotificationCenter::sharedNotificationCenter()->addObserver(this, callfuncO_selector(ExampleEventHandler::onIabServiceStarted), CCStoreConsts::EVENT_IAB_SERVICE_STARTED, NULL);
    CCNotificationCenter::sharedNotificationCenter()->addObserver(this, callfuncO_selector(ExampleEventHandler::onIabServiceStopped), CCStoreConsts::EVENT_IAB_SERVICE_STOPPED, NULL);
    CCNotificationCenter::sharedNotificationCenter()->addObserver(this, callfuncO_selector(ExampleEventHandler::onMarketRefund), CCStoreConsts::EVENT_MARKET_REFUND, NULL);
}

void ExampleEventHandler::onBillingNotSupported(CCDictionary *eventData) {
    soomla::CCSoomlaUtils::logDebug(TAG, "BillingNotSupported");
}

void ExampleEventHandler::onBillingSupported(CCDictionary *eventData) {
    soomla::CCSoomlaUtils::logDebug(TAG, "BillingSupported");
}

void ExampleEventHandler::onCurrencyBalanceChanged(CCDictionary *eventData) {
    CCVirtualCurrency *currency = dynamic_cast<CCVirtualCurrency *>(eventData->objectForKey(CCStoreConsts::DICT_ELEMENT_CURRENCY));
    CCInteger *balance = dynamic_cast<CCInteger *>(eventData->objectForKey(CCStoreConsts::DICT_ELEMENT_BALANCE));
    CCInteger *amountAdded = dynamic_cast<CCInteger *>(eventData->objectForKey(CCStoreConsts::DICT_ELEMENT_AMOUNT_ADDED));
    CCSoomlaUtils::logDebug(TAG, CCString::createWithFormat("CurrencyBalanceChanged: %s %d %d",
                                                            currency->getItemId()->getCString(),
                                                            balance->getValue(),
                                                            amountAdded->getValue())->getCString());
}

void ExampleEventHandler::onGoodBalanceChanged(CCDictionary *eventData) {
    CCVirtualGood *good = dynamic_cast<CCVirtualGood *>(eventData->objectForKey(CCStoreConsts::DICT_ELEMENT_GOOD));
    CCInteger *balance = dynamic_cast<CCInteger *>(eventData->objectForKey(CCStoreConsts::DICT_ELEMENT_BALANCE));
    CCInteger *amountAdded = dynamic_cast<CCInteger *>(eventData->objectForKey(CCStoreConsts::DICT_ELEMENT_AMOUNT_ADDED));
    CCSoomlaUtils::logDebug(TAG, CCString::createWithFormat("GoodBalanceChanged: %s %d %d",
                                                            good->getItemId()->getCString(),
                                                            balance->getValue(),
                                                            amountAdded->getValue())->getCString());
}

void ExampleEventHandler::onGoodEquipped(CCDictionary *eventData) {
    CCEquippableVG *equippable = dynamic_cast<CCEquippableVG *>(eventData->objectForKey(CCStoreConsts::DICT_ELEMENT_EQUIPPABLEVG));
    CCSoomlaUtils::logDebug(TAG, CCString::createWithFormat("GoodEquipped: %s", equippable->getItemId()->getCString())->getCString());
}

void ExampleEventHandler::onGoodUnEquipped(CCDictionary *eventData) {
    CCEquippableVG *equippable = dynamic_cast<CCEquippableVG *>(eventData->objectForKey(CCStoreConsts::DICT_ELEMENT_EQUIPPABLEVG));
    CCSoomlaUtils::logDebug(TAG, CCString::createWithFormat("GoodUnEquipped: %s", equippable->getItemId()->getCString())->getCString());
}

void ExampleEventHandler::onGoodUpgrade(CCDictionary *eventData) {
    CCVirtualGood *good = dynamic_cast<CCVirtualGood *>(eventData->objectForKey(CCStoreConsts::DICT_ELEMENT_GOOD));
    CCUpgradeVG *upgrade = dynamic_cast<CCUpgradeVG *>(eventData->objectForKey(CCStoreConsts::DICT_ELEMENT_UPGRADEVG));
    CCSoomlaUtils::logDebug(TAG, CCString::createWithFormat("GoodUpgrade: %s with upgrade %s", good->getItemId()->getCString(),
                                                            upgrade->getItemId()->getCString())->getCString());
}

void ExampleEventHandler::onItemPurchased(CCDictionary *eventData) {
    CCPurchasableVirtualItem *purchasable = dynamic_cast<CCPurchasableVirtualItem *>(eventData->objectForKey(CCStoreConsts::DICT_ELEMENT_PURCHASABLE));
    CCString *payload = dynamic_cast<CCString *>(eventData->objectForKey(CCStoreConsts::DICT_ELEMENT_DEVELOPERPAYLOAD));
    CCSoomlaUtils::logDebug(TAG, CCString::createWithFormat("ItemPurchased: %s %s",
                                                            purchasable->getItemId()->getCString(),
                                                            payload->getCString())->getCString());
}

void ExampleEventHandler::onItemPurchaseStarted(CCDictionary *eventData) {
    CCPurchasableVirtualItem *purchasable = dynamic_cast<CCPurchasableVirtualItem *>(eventData->objectForKey(CCStoreConsts::DICT_ELEMENT_PURCHASABLE));
    CCSoomlaUtils::logDebug(TAG, CCString::createWithFormat("ItemPurchaseStarted: %s", purchasable->getItemId()->getCString())->getCString());
}

void ExampleEventHandler::onMarketPurchaseCancelled(CCDictionary *eventData) {
    CCPurchasableVirtualItem *purchasable = dynamic_cast<CCPurchasableVirtualItem *>(eventData->objectForKey(CCStoreConsts::DICT_ELEMENT_PURCHASABLE));
    CCSoomlaUtils::logDebug(TAG, CCString::createWithFormat("MarketPurchaseCancelled: %s", purchasable->getItemId()->getCString())->getCString());
}

void ExampleEventHandler::onMarketPurchase(CCDictionary *eventData) {
    CCPurchasableVirtualItem *purchasable = dynamic_cast<CCPurchasableVirtualItem *>(eventData->objectForKey(CCStoreConsts::DICT_ELEMENT_PURCHASABLE));
    CCString *token = dynamic_cast<CCString *>(eventData->objectForKey(CCStoreConsts::DICT_ELEMENT_TOKEN));
    CCString *payload = dynamic_cast<CCString *>(eventData->objectForKey(CCStoreConsts::DICT_ELEMENT_DEVELOPERPAYLOAD));
    CCSoomlaUtils::logDebug(TAG, CCString::createWithFormat("MarketPurchase: %s token: %s payload: %s",
                                                            purchasable->getItemId()->getCString(),
                                                            token->getCString(),
                                                            payload->getCString())->getCString());
    
    // Android ONLY
    CCString *originalJSON = dynamic_cast<CCString *>(eventData->objectForKey(CCStoreConsts::DICT_ELEMENT_ORIGINAL_JSON));
    if (originalJSON != NULL) {
        CCSoomlaUtils::logDebug(TAG, CCString::createWithFormat("MarketPurchase: Original JSON %s", originalJSON->getCString())->getCString());
    }
    CCString *signature = dynamic_cast<CCString *>(eventData->objectForKey(CCStoreConsts::DICT_ELEMENT_SIGNATURE));
    if (signature != NULL) {
        CCSoomlaUtils::logDebug(TAG, CCString::createWithFormat("MarketPurchase: Signature %s", signature->getCString())->getCString());
    }
    CCString *userId = dynamic_cast<CCString *>(eventData->objectForKey(CCStoreConsts::DICT_ELEMENT_USER_ID));
    if (userId != NULL) {
        CCSoomlaUtils::logDebug(TAG, CCString::createWithFormat("MarketPurchase: User ID %s", userId->getCString())->getCString());
    }
}

void ExampleEventHandler::onMarketPurchaseStarted(CCDictionary *eventData) {
    CCPurchasableVirtualItem *purchasable = dynamic_cast<CCPurchasableVirtualItem *>(eventData->objectForKey(CCStoreConsts::DICT_ELEMENT_PURCHASABLE));
    CCSoomlaUtils::logDebug(TAG, CCString::createWithFormat("MarketPurchaseStarted: %s", purchasable->getItemId()->getCString())->getCString());
}

void ExampleEventHandler::onMarketPurchaseVerification(CCDictionary *eventData) {
    CCPurchasableVirtualItem *purchasable = dynamic_cast<CCPurchasableVirtualItem *>(eventData->objectForKey(CCStoreConsts::DICT_ELEMENT_PURCHASABLE));
    CCSoomlaUtils::logDebug(TAG, CCString::createWithFormat("MarketPurchaseVerification: %s", purchasable->getItemId()->getCString())->getCString());
}

void ExampleEventHandler::onRestoreTransactionsStarted(CCDictionary *eventData) {
    CCSoomlaUtils::logDebug(TAG, "RestoreTransactions");
}

void ExampleEventHandler::onRestoreTransactionsFinished(CCDictionary *eventData) {
    CCBool *success = dynamic_cast<CCBool *>(eventData->objectForKey(CCStoreConsts::DICT_ELEMENT_SUCCESS));
    CCSoomlaUtils::logDebug(TAG, CCString::createWithFormat("RestoreTransactionsFinished: %s", success ? "YES" : "NO")->getCString());
}

void ExampleEventHandler::onUnexpectedErrorInStore(CCDictionary *eventData) {
    CCString *errorMessage = dynamic_cast<CCString *>(eventData->objectForKey(CCStoreConsts::DICT_ELEMENT_ERROR_MESSAGE));
    CCSoomlaUtils::logDebug(TAG, CCString::createWithFormat("UnexpectedErrorInStore: %s", errorMessage->getCString())->getCString());
}

void ExampleEventHandler::onSoomlaStoreInitialized(CCDictionary *eventData) {
    soomla::CCSoomlaUtils::logDebug(TAG, "StoreControllerInitialized");
}

void ExampleEventHandler::onMarketItemsRefreshed(CCDictionary *eventData) {
    soomla::CCSoomlaUtils::logDebug(TAG, "MarketItemsRefreshStarted");
    
    CCArray *marketItems = dynamic_cast<CCArray *>(eventData->objectForKey(CCStoreConsts::DICT_ELEMENT_MARKET_ITEMS));
    
    CCObject *object;
    CCARRAY_FOREACH(marketItems, object) {
        CCMarketItem *marketItem = dynamic_cast<CCMarketItem *>(object);
        
        CCSoomlaUtils::logDebug(TAG, CCString::createWithFormat("Market Item: %s %s",
                                                                marketItem->getProductId()->getCString(),
                                                                marketItem->getMarketPriceAndCurrency()->getCString())->getCString());
    }
}

void ExampleEventHandler::onMarketItemsRefreshStarted(CCDictionary *eventData) {
    CCSoomlaUtils::logDebug(TAG, "MarketItemsRefreshStarted");
}

void ExampleEventHandler::onMarketItemsRefreshFailed(CCDictionary *eventData) {
    CCString *errorMessage = dynamic_cast<CCString *>(eventData->objectForKey(CCStoreConsts::DICT_ELEMENT_ERROR_MESSAGE));
    CCSoomlaUtils::logDebug(TAG, CCString::createWithFormat("MarketItemsRefreshFailed %s", errorMessage->getCString())->getCString());
}

void ExampleEventHandler::onMarketRefund(CCDictionary *eventData) {
    soomla::CCSoomlaUtils::logDebug(TAG, "MarketRefund");
}

void ExampleEventHandler::onIabServiceStarted(CCDictionary *eventData) {
    soomla::CCSoomlaUtils::logDebug(TAG, "IabServiceStarted");
}

void ExampleEventHandler::onIabServiceStopped(CCDictionary *eventData) {
    soomla::CCSoomlaUtils::logDebug(TAG, "IabServiceStopped");
}
