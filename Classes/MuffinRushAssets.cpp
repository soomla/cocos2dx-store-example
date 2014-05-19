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

// Created by Fedor Shubin on 5/24/13.

#include "MuffinRushAssets.h"

#include "CCVirtualCurrency.h"
#include "CCVirtualCurrencyPack.h"
#include "CCVirtualGood.h"
#include "CCSingleUseVG.h"
#include "CCPurchaseWithMarket.h"
#include "CCPurchaseWithVirtualItem.h"
#include "CCVirtualCategory.h"
#include "CCNonConsumableItem.h"
#include "CCUpgradeVG.h"
#include "CCSingleUsePackVG.h"
#include "CCEquippableVG.h"

USING_NS_CC;
using namespace soomla;

#define MUFFIN_CURRENCY_ITEM_ID "currency_muffin"
#define TENMUFF_PACK_PRODUCT_ID "android.test.refunded"
#define FIFTYMUFF_PACK_PRODUCT_ID "android.test.canceled"
#define FOURHUNDMUFF_PACK_PRODUCT_ID "android.test.purchased"
#define THOUSANDMUFF_PACK_PRODUCT_ID "android.test.item_unavailable"
#define NO_ADDS_NONCONS_PRODUCT_ID "no_ads"

#define MUFFINCAKE_ITEM_ID "fruit_cake"
#define PAVLOVA_ITEM_ID "pavlova"
#define CHOCLATECAKE_ITEM_ID "chocolate_cake"
#define CREAMCUP_ITEM_ID "cream_cup"


MuffinRushAssets *MuffinRushAssets::create() {
    MuffinRushAssets *ret = new MuffinRushAssets();
    ret->autorelease();
    ret->init();

    return ret;
}

bool MuffinRushAssets::init() {
    /** Virtual Currencies **/
    CCVirtualCurrency *muffinCurrency = CCVirtualCurrency::create(
            CCString::create("Muffins"),
            CCString::create(""),
            CCString::create(MUFFIN_CURRENCY_ITEM_ID)
    );


    /** Virtual Currency Packs **/

    CCVirtualCurrencyPack *tenmuffPack = CCVirtualCurrencyPack::create(
            CCString::create("10 Muffins"),                                   // name
            CCString::create("Test refund of an item"),                       // description
            CCString::create("muffins_10"),                                   // item id
            CCInteger::create(10),												// number of currencies in the pack
            CCString::create(MUFFIN_CURRENCY_ITEM_ID),                        // the currency associated with this pack
            CCPurchaseWithMarket::create(CCString::create(TENMUFF_PACK_PRODUCT_ID), CCDouble::create(0.99))
    );

    CCVirtualCurrencyPack *fiftymuffPack = CCVirtualCurrencyPack::create(
            CCString::create("50 Muffins"),                                   // name
            CCString::create("Test cancellation of an item"),                 // description
            CCString::create("muffins_50"),                                   // item id
            CCInteger::create(50),												// number of currencies in the pack
            CCString::create(MUFFIN_CURRENCY_ITEM_ID),                        // the currency associated with this pack
            CCPurchaseWithMarket::create(CCString::create(FIFTYMUFF_PACK_PRODUCT_ID), CCDouble::create(1.99))
    );

    CCVirtualCurrencyPack *fourhundmuffPack = CCVirtualCurrencyPack::create(
            CCString::create("400 Muffins"),                                   // name
            CCString::create("Test purchase of an item"),                 // description
            CCString::create("muffins_400"),                                   // item id
            CCInteger::create(400),												// number of currencies in the pack
            CCString::create(MUFFIN_CURRENCY_ITEM_ID),                        // the currency associated with this pack
            CCPurchaseWithMarket::create(CCString::create(FOURHUNDMUFF_PACK_PRODUCT_ID), CCDouble::create(4.99))
    );

    CCVirtualCurrencyPack *thousandmuffPack = CCVirtualCurrencyPack::create(
            CCString::create("1000 Muffins"),                                   // name
            CCString::create("Test item unavailable"),                 // description
            CCString::create("muffins_1000"),                                   // item id
            CCInteger::create(1000),												// number of currencies in the pack
            CCString::create(MUFFIN_CURRENCY_ITEM_ID),                        // the currency associated with this pack
            CCPurchaseWithMarket::create(CCString::create(THOUSANDMUFF_PACK_PRODUCT_ID), CCDouble::create(8.99))
    );

    /** Virtual Goods **/

    CCVirtualGood *muffincakeGood = CCSingleUseVG::create(
            CCString::create("Fruit Cake"),                                       // name
            CCString::create("Customers buy a double portion on each purchase of this cake"), // description
            CCString::create("fruit_cake"),                                       // item id
            CCPurchaseWithVirtualItem::create(
                    CCString::create(MUFFIN_CURRENCY_ITEM_ID), CCInteger::create(225)
            ) // the way this virtual good is purchased
    );

    CCVirtualGood *pavlovaGood = CCSingleUseVG::create(
            CCString::create("Pavlova"),                                       // name
            CCString::create("Gives customers a sugar rush and they call their friends"), // description
            CCString::create("pavlova"),                                       // item id
            CCPurchaseWithVirtualItem::create(CCString::create(MUFFIN_CURRENCY_ITEM_ID), CCInteger::create(175)) // the way this virtual good is purchased
    );

    CCVirtualGood *tenPavlovaGoods = CCSingleUsePackVG::create(
            CCString::create("pavlova"), CCInteger::create(10),
            CCString::create("10 Pavlova"),
            CCString::create("Gives customers a sugar rush and they call their friends"),
            CCString::create("pavlova_10"),
            CCPurchaseWithVirtualItem::create(CCString::create(MUFFIN_CURRENCY_ITEM_ID), CCInteger::create(1750)));

    CCVirtualGood *choclatecakeGood = CCSingleUseVG::create(
            CCString::create("Chocolate Cake"),                                       // name
            CCString::create("A classic cake to maximize customer satisfaction"), // description
            CCString::create("chocolate_cake"),                                       // item id
            CCPurchaseWithVirtualItem::create(
                    CCString::create(MUFFIN_CURRENCY_ITEM_ID), CCInteger::create(250)
            ) // the way this virtual good is purchased
    );

    CCVirtualGood *creamcupGood = CCSingleUseVG::create(
            CCString::create("Cream Cup"),                                       // name
            CCString::create("Increase bakery reputation with this original pastry"), // description
            CCString::create("cream_cup"),                                       // item id
            CCPurchaseWithVirtualItem::create(CCString::create(MUFFIN_CURRENCY_ITEM_ID), CCInteger::create(50)
            ) // the way this virtual good is purchased
    );

    CCVirtualGood *tenCreamcupGoods = CCSingleUsePackVG::create(
            CCString::create("cream_cup"), CCInteger::create(10),
            CCString::create("10 Cream Cup"),
            CCString::create("Increase bakery reputation with this original pastry"),
            CCString::create("cream_cup_10"),
            CCPurchaseWithVirtualItem::create(CCString::create(MUFFIN_CURRENCY_ITEM_ID), CCInteger::create(500)));

    CCVirtualGood *showRoomGood =
            CCLifetimeVG::create(CCString::create("Show Room"), // name
                    CCString::create("Show Room "), // description
                    CCString::create("show_room"), // item id
                    CCPurchaseWithVirtualItem::create(CCString::create(MUFFIN_CURRENCY_ITEM_ID), CCInteger::create(100)));

    CCVirtualGood *showRoomGood0 = CCUpgradeVG::create(
            CCString::create("show_room"),
            NULL,
            CCString::create("show_room_1"),
            CCString::create("Show Room L0"),
            CCString::create(""),
            CCString::create("show_room_0"),
            CCPurchaseWithVirtualItem::create(CCString::create(MUFFIN_CURRENCY_ITEM_ID), CCInteger::create(220)));
	
    CCVirtualGood *showRoomGood1 = CCUpgradeVG::create(
            CCString::create("show_room"),
            CCString::create("show_room_0"),
            CCString::create("show_room_2"),
            CCString::create("Show Room L1"),
            CCString::create(""),
            CCString::create("show_room_1"),
            CCPurchaseWithVirtualItem::create(CCString::create(MUFFIN_CURRENCY_ITEM_ID), CCInteger::create(220)));

	CCVirtualGood *showRoomGood2 = CCUpgradeVG::create(
			CCString::create("show_room"),
			CCString::create("show_room_1"),
			CCString::create("show_room_3"),
			CCString::create("Show Room L2"),
			CCString::create(""),
			CCString::create("show_room_2"),
			CCPurchaseWithVirtualItem::create(CCString::create(MUFFIN_CURRENCY_ITEM_ID), CCInteger::create(220)));

	CCVirtualGood *showRoomGood3 = CCUpgradeVG::create(
			CCString::create("show_room"),
			CCString::create("show_room_2"),
			CCString::create("show_room_4"),
			CCString::create("Show Room L3"),
			CCString::create(""),
			CCString::create("show_room_3"),
			CCPurchaseWithVirtualItem::create(CCString::create(MUFFIN_CURRENCY_ITEM_ID), CCInteger::create(220)));

	CCVirtualGood *showRoomGood4 = CCUpgradeVG::create(
			CCString::create("show_room"),
			CCString::create("show_room_3"),
			NULL,
			CCString::create("Show Room L4"),
			CCString::create(""),
			CCString::create("show_room_4"),
			CCPurchaseWithVirtualItem::create(CCString::create(MUFFIN_CURRENCY_ITEM_ID), CCInteger::create(220)));
	
    CCVirtualGood *deliveryVehicleGood =
            CCLifetimeVG::create(CCString::create("Delivery Vehicle"), // name
                    CCString::create("Delivery Vehicle"), // description
                    CCString::create("delivery_vehicle"), // item id
                    CCPurchaseWithVirtualItem::create(CCString::create(MUFFIN_CURRENCY_ITEM_ID), CCInteger::create(20)));

    CCVirtualGood *deliveryVehicleGood0 = CCUpgradeVG::create(
            CCString::create("delivery_vehicle"),
            NULL,
            CCString::create("delivery_vehicle_1"),
            CCString::create("Delivery Vehicle 0"),
            CCString::create(""),
            CCString::create("delivery_vehicle_0"),
            CCPurchaseWithVirtualItem::create(CCString::create(MUFFIN_CURRENCY_ITEM_ID), CCInteger::create(20)));

    CCVirtualGood *deliveryVehicleGood1 = CCUpgradeVG::create(
            CCString::create("delivery_vehicle"),
            CCString::create("delivery_vehicle_0"),
            CCString::create("delivery_vehicle_2"),
            CCString::create("Delivery Vehicle 1"),
            CCString::create(""),
            CCString::create("delivery_vehicle_1"),
            CCPurchaseWithVirtualItem::create(CCString::create(MUFFIN_CURRENCY_ITEM_ID), CCInteger::create(20)));

    CCVirtualGood *deliveryVehicleGood2 = CCUpgradeVG::create(
			CCString::create("delivery_vehicle"),
			CCString::create("delivery_vehicle_1"),
			CCString::create("delivery_vehicle_3"),
			CCString::create("Delivery Vehicle 2"),
			CCString::create(""),
			CCString::create("delivery_vehicle_2"),
			CCPurchaseWithVirtualItem::create(CCString::create(MUFFIN_CURRENCY_ITEM_ID), CCInteger::create(20)));

    CCVirtualGood *deliveryVehicleGood3 = CCUpgradeVG::create(
			CCString::create("delivery_vehicle"),
			CCString::create("delivery_vehicle_2"),
			CCString::create("delivery_vehicle_4"),
			CCString::create("Delivery Vehicle 3"),
			CCString::create(""),
			CCString::create("delivery_vehicle_3"),
			CCPurchaseWithVirtualItem::create(CCString::create(MUFFIN_CURRENCY_ITEM_ID), CCInteger::create(20)));

	CCVirtualGood *deliveryVehicleGood4 = CCUpgradeVG::create(
			CCString::create("delivery_vehicle"),
			CCString::create("delivery_vehicle_3"),
			NULL,
			CCString::create("Delivery Vehicle 4"),
			CCString::create(""),
			CCString::create("delivery_vehicle_4"),
			CCPurchaseWithVirtualItem::create(CCString::create(MUFFIN_CURRENCY_ITEM_ID), CCInteger::create(20)));
	
    CCVirtualGood *fatCatGood = CCEquippableVG::create(
            CCInteger::create(CCEquippableVG::kCategory),
            CCString::create("Fat Cat"),
            CCString::create("Fat cat description"),
            CCString::create("fat_cat"),
            CCPurchaseWithVirtualItem::create(CCString::create(MUFFIN_CURRENCY_ITEM_ID), CCInteger::create(27)));

    CCVirtualGood *happiHippoGood = CCEquippableVG::create(
            CCInteger::create(CCEquippableVG::kCategory),
            CCString::create("Happi Hippo"),
            CCString::create("Happi Hippo description"),
            CCString::create("happi_hippo"),
            CCPurchaseWithVirtualItem::create(CCString::create(MUFFIN_CURRENCY_ITEM_ID), CCInteger::create(44)));

    CCVirtualGood *funkeyMonkeyGood = CCEquippableVG::create(
            CCInteger::create(CCEquippableVG::kCategory),
            CCString::create("Funkey Monkey"),
            CCString::create("Funkey Monkey description"),
            CCString::create("funkey_monkey"),
            CCPurchaseWithVirtualItem::create(CCString::create(MUFFIN_CURRENCY_ITEM_ID), CCInteger::create(35)));


    /** Virtual Categories **/

    CCVirtualCategory *cakes = CCVirtualCategory::create(
            CCString::create("Cakes"),
            CCArray::create(
                    CCString::create(MUFFINCAKE_ITEM_ID),
                    CCString::create(PAVLOVA_ITEM_ID),
                    CCString::create("pavlova_10"),
                    CCString::create(CHOCLATECAKE_ITEM_ID),
                    CCString::create(CREAMCUP_ITEM_ID),
                    CCString::create("cream_cup_10"),
                    NULL));

    CCVirtualCategory *upgrades = CCVirtualCategory::create(
            CCString::create("Upgrades"),
            CCArray::create(CCString::create("show_room_0"),
							CCString::create("show_room_1"),
							CCString::create("show_room_2"),
							CCString::create("show_room_3"),
							CCString::create("show_room_4"),
							CCString::create("delivery_vehicle_0"),
							CCString::create("delivery_vehicle_1"),
							CCString::create("delivery_vehicle_2"),
							CCString::create("delivery_vehicle_3"),
							CCString::create("delivery_vehicle_4"),
							NULL));

    CCVirtualCategory *characters = CCVirtualCategory::create(
            CCString::create("Characters"),
            CCArray::create(CCString::create("fat_cat"), CCString::create("happi_hippo"), CCString::create("funkey_monkey"), NULL));


    /** Google MANAGED Items **/

    CCNonConsumableItem *noAdsNoncons = CCNonConsumableItem::create(
            CCString::create("No Ads"),
            CCString::create("Test purchase of MANAGED item."),
            CCString::create("no_ads"),
            CCPurchaseWithMarket::createWithMarketItem(CCMarketItem::create(
                    CCString::create(NO_ADDS_NONCONS_PRODUCT_ID),
                    CCInteger::create(CCMarketItem::NONCONSUMABLE), CCDouble::create(1.99))
            )
    );

    mCurrencies = CCArray::create(muffinCurrency, NULL);
    mCurrencies->retain();

    mGoods = CCArray::create(muffincakeGood, pavlovaGood, tenPavlovaGoods, choclatecakeGood, creamcupGood, tenCreamcupGoods,
							 showRoomGood, showRoomGood0, showRoomGood1, showRoomGood2, showRoomGood3, showRoomGood4,
							 deliveryVehicleGood, deliveryVehicleGood0, deliveryVehicleGood1, deliveryVehicleGood2,
							 deliveryVehicleGood3, deliveryVehicleGood4, fatCatGood, happiHippoGood, funkeyMonkeyGood, NULL);
    mGoods->retain();

    mCurrencyPacks = CCArray::create(tenmuffPack, fiftymuffPack, fourhundmuffPack, thousandmuffPack, NULL);
    mCurrencyPacks->retain();

    mCategories = CCArray::create(cakes, upgrades, characters, NULL);
    mCategories->retain();

    mNonConsumableItems = CCArray::create(noAdsNoncons, NULL);
    mNonConsumableItems->retain();

    return true;
}

MuffinRushAssets::~MuffinRushAssets() {
    CC_SAFE_RELEASE(mCurrencies);
    CC_SAFE_RELEASE(mGoods);
    CC_SAFE_RELEASE(mCurrencyPacks);
    CC_SAFE_RELEASE(mCategories);
    CC_SAFE_RELEASE(mNonConsumableItems);
}

int MuffinRushAssets::getVersion() {
    return 0;
}

cocos2d::CCArray *MuffinRushAssets::getCurrencies() {
    return mCurrencies;
}

cocos2d::CCArray *MuffinRushAssets::getGoods() {
    return mGoods;
}

cocos2d::CCArray *MuffinRushAssets::getCurrencyPacks() {
    return mCurrencyPacks;
}

cocos2d::CCArray *MuffinRushAssets::getCategories() {
    return mCategories;
}

cocos2d::CCArray *MuffinRushAssets::getNonConsumableItems() {
    return mNonConsumableItems;
}

