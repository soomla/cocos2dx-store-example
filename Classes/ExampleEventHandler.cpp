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

#define TAG "ExampleEventHandler >>>"

USING_NS_CC;

void ExampleEventHandler::onBillingNotSupported() {
    soomla::CCSoomlaUtils::logDebug(TAG, "BillingNotSupported");
}

void ExampleEventHandler::onBillingSupported() {
    soomla::CCSoomlaUtils::logDebug(TAG, "BillingSupported");
}

void ExampleEventHandler::onCurrencyBalanceChanged(soomla::CCVirtualCurrency *virtualCurrency, int balance, int amountAdded) {
    soomla::CCSoomlaUtils::logDebug(TAG, "CurrencyBalanceChanged");
    CCNotificationCenter::sharedNotificationCenter()->postNotification
        (EVENT_ON_CURRENCY_BALANCE_CHANGED, CCInteger::create(balance));
}

void ExampleEventHandler::onGoodBalanceChanged(soomla::CCVirtualGood *virtualGood, int balance, int amountAdded) {
    soomla::CCSoomlaUtils::logDebug(TAG, "GoodBalanceChanged");
    CCNotificationCenter::sharedNotificationCenter()->postNotification
        (EVENT_ON_GOOD_BALANCE_CHANGED, CCArray::create(virtualGood, CCInteger::create(balance), NULL));
}

void ExampleEventHandler::onGoodEquipped(soomla::CCEquippableVG *equippableVG) {
    soomla::CCSoomlaUtils::logDebug(TAG, "GoodEquipped");
    CCNotificationCenter::sharedNotificationCenter()->postNotification(EVENT_ON_GOOD_EQUIPPED, equippableVG);
}

void ExampleEventHandler::onGoodUnEquipped(soomla::CCEquippableVG *equippableVG) {
    soomla::CCSoomlaUtils::logDebug(TAG, "GoodUnEquipped");
    CCNotificationCenter::sharedNotificationCenter()->postNotification(EVENT_ON_GOOD_UNEQUIPPED, equippableVG);
}

void ExampleEventHandler::onGoodUpgrade(soomla::CCVirtualGood *virtualGood, soomla::CCUpgradeVG *upgradeVG) {
    soomla::CCSoomlaUtils::logDebug(TAG, "GoodUpgrade");
    CCNotificationCenter::sharedNotificationCenter()->postNotification(EVENT_ON_GOOD_UPGRADE, virtualGood);
}

void ExampleEventHandler::onItemPurchased(soomla::CCPurchasableVirtualItem *purchasableVirtualItem, cocos2d::CCString *payload) {
    soomla::CCSoomlaUtils::logDebug(TAG, "ItemPurchased");
}

void ExampleEventHandler::onItemPurchaseStarted(soomla::CCPurchasableVirtualItem *purchasableVirtualItem) {
    soomla::CCSoomlaUtils::logDebug(TAG, "ItemPurchaseStarted");
}

void ExampleEventHandler::onMarketPurchaseCancelled(soomla::CCPurchasableVirtualItem *purchasableVirtualItem) {
    soomla::CCSoomlaUtils::logDebug(TAG, "MarketPurchaseCancelled");
}

void ExampleEventHandler::onMarketPurchase(soomla::CCPurchasableVirtualItem *purchasableVirtualItem, cocos2d::CCString *token, cocos2d::CCString *payload) {
    soomla::CCSoomlaUtils::logDebug(TAG, "MarketPurchase");
}

void ExampleEventHandler::onMarketPurchaseStarted(soomla::CCPurchasableVirtualItem *purchasableVirtualItem) {
    soomla::CCSoomlaUtils::logDebug(TAG, "MarketPurchaseStarted");
}

void ExampleEventHandler::onMarketPurchaseVerification(soomla::CCPurchasableVirtualItem *purchasableVirtualItem) {
    soomla::CCSoomlaUtils::logDebug(TAG, "MarketPurchaseVerification");
}

void ExampleEventHandler::onRestoreTransactionsFinished(bool success) {
    soomla::CCSoomlaUtils::logDebug(TAG, "RestoreTransactions");
}

void ExampleEventHandler::onRestoreTransactionsStarted() {
    soomla::CCSoomlaUtils::logDebug(TAG, "RestoreTransactionsStarted");
}

void ExampleEventHandler::onUnexpectedErrorInStore(cocos2d::CCString *errorMessage) {
    soomla::CCSoomlaUtils::logDebug(TAG, "UnexpectedErrorInStore");
}

void ExampleEventHandler::onSoomlaStoreInitialized() {
    soomla::CCSoomlaUtils::logDebug(TAG, "StoreControllerInitialized");
}

void ExampleEventHandler::onMarketItemsRefreshStarted() {
    soomla::CCSoomlaUtils::logDebug(TAG, "MarketItemsRefreshStarted");
}

void ExampleEventHandler::onMarketItemsRefreshed(cocos2d::CCArray *virtualItems) {
    soomla::CCSoomlaUtils::logDebug(TAG, "MarketItemsRefreshed");
}

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)

void ExampleEventHandler::onMarketRefund(soomla::CCPurchasableVirtualItem *purchasableVirtualItem) {
    soomla::CCSoomlaUtils::logDebug(TAG, "MarketRefund");
}

void ExampleEventHandler::onIabServiceStarted() {
    soomla::CCSoomlaUtils::logDebug(TAG, "IabServiceStarted");
}

void ExampleEventHandler::onIabServiceStopped() {
    soomla::CCSoomlaUtils::logDebug(TAG, "IabServiceStopped");
}
#endif
