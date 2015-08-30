
#include "MuffinRushAssets.h"

#include "CCVirtualCurrency.h"
#include "CCVirtualCurrencyPack.h"
#include "CCVirtualGood.h"
#include "CCSingleUseVG.h"
#include "CCPurchaseWithMarket.h"
#include "CCPurchaseWithVirtualItem.h"
#include "CCVirtualCategory.h"
#include "CCUpgradeVG.h"
#include "CCSingleUsePackVG.h"
#include "CCEquippableVG.h"

USING_NS_CC;
using namespace soomla;

MuffinRushAssets *MuffinRushAssets::create() {
    MuffinRushAssets *ret = new MuffinRushAssets();
    ret->autorelease();
    ret->init();

    return ret;
}

bool MuffinRushAssets::init() {
    /** Virtual Currencies **/
    CCVirtualCurrency *muffinCurrency = CCVirtualCurrency::create(
            __String::create("Muffins"),
            __String::create(""),
            __String::create(MUFFIN_CURRENCY_ITEM_ID)
    );


    /** Virtual Currency Packs **/

    CCVirtualCurrencyPack *tenmuffPack = CCVirtualCurrencyPack::create(
            __String::create("10 Muffins"),                                   // name
            __String::create("Test refund of an item"),                       // description
            __String::create("muffins_10"),                                   // item id
            __Integer::create(10),												// number of currencies in the pack
            __String::create(MUFFIN_CURRENCY_ITEM_ID),                        // the currency associated with this pack
            CCPurchaseWithMarket::create(__String::create(TENMUFF_PACK_PRODUCT_ID), CCDouble::create(0.99))
    );

    CCVirtualCurrencyPack *fiftymuffPack = CCVirtualCurrencyPack::create(
            __String::create("50 Muffins"),                                   // name
            __String::create("Test cancellation of an item"),                 // description
            __String::create("muffins_50"),                                   // item id
            __Integer::create(50),												// number of currencies in the pack
            __String::create(MUFFIN_CURRENCY_ITEM_ID),                        // the currency associated with this pack
            CCPurchaseWithMarket::create(__String::create(FIFTYMUFF_PACK_PRODUCT_ID), CCDouble::create(1.99))
    );

    CCVirtualCurrencyPack *fourhundmuffPack = CCVirtualCurrencyPack::create(
            __String::create("400 Muffins"),                                   // name
            __String::create("Test purchase of an item"),                 // description
            __String::create("muffins_400"),                                   // item id
            __Integer::create(400),												// number of currencies in the pack
            __String::create(MUFFIN_CURRENCY_ITEM_ID),                        // the currency associated with this pack
            CCPurchaseWithMarket::create(__String::create(FOURHUNDMUFF_PACK_PRODUCT_ID), CCDouble::create(4.99))
    );

    CCVirtualCurrencyPack *thousandmuffPack = CCVirtualCurrencyPack::create(
            __String::create("1000 Muffins"),                                   // name
            __String::create("Test item unavailable"),                 // description
            __String::create("muffins_1000"),                                   // item id
            __Integer::create(1000),												// number of currencies in the pack
            __String::create(MUFFIN_CURRENCY_ITEM_ID),                        // the currency associated with this pack
            CCPurchaseWithMarket::create(__String::create(THOUSANDMUFF_PACK_PRODUCT_ID), CCDouble::create(8.99))
    );

    /** Virtual Goods **/

    CCVirtualGood *muffincakeGood = CCSingleUseVG::create(
            __String::create("Fruit Cake"),                                       // name
            __String::create("Customers buy a double portion on each purchase of this cake"), // description
            __String::create("fruit_cake"),                                       // item id
            CCPurchaseWithVirtualItem::create(
                    __String::create(MUFFIN_CURRENCY_ITEM_ID), __Integer::create(225)
            ) // the way this virtual good is purchased
    );

    CCVirtualGood *pavlovaGood = CCSingleUseVG::create(
            __String::create("Pavlova"),                                       // name
            __String::create("Gives customers a sugar rush and they call their friends"), // description
            __String::create("pavlova"),                                       // item id
            CCPurchaseWithVirtualItem::create(__String::create(MUFFIN_CURRENCY_ITEM_ID), __Integer::create(175)) // the way this virtual good is purchased
    );

    CCVirtualGood *tenPavlovaGoods = CCSingleUsePackVG::create(
            __String::create("pavlova"), __Integer::create(10),
            __String::create("10 Pavlova"),
            __String::create("Gives customers a sugar rush and they call their friends"),
            __String::create("pavlova_10"),
            CCPurchaseWithVirtualItem::create(__String::create(MUFFIN_CURRENCY_ITEM_ID), __Integer::create(1750)));

    CCVirtualGood *choclatecakeGood = CCSingleUseVG::create(
            __String::create("Chocolate Cake"),                                       // name
            __String::create("A classic cake to maximize customer satisfaction"), // description
            __String::create("chocolate_cake"),                                       // item id
            CCPurchaseWithVirtualItem::create(
                    __String::create(MUFFIN_CURRENCY_ITEM_ID), __Integer::create(250)
            ) // the way this virtual good is purchased
    );

    CCVirtualGood *creamcupGood = CCSingleUseVG::create(
            __String::create("Cream Cup"),                                       // name
            __String::create("Increase bakery reputation with this original pastry"), // description
            __String::create("cream_cup"),                                       // item id
            CCPurchaseWithVirtualItem::create(__String::create(MUFFIN_CURRENCY_ITEM_ID), __Integer::create(50)
            ) // the way this virtual good is purchased
    );

    CCVirtualGood *tenCreamcupGoods = CCSingleUsePackVG::create(
            __String::create("cream_cup"), __Integer::create(10),
            __String::create("10 Cream Cup"),
            __String::create("Increase bakery reputation with this original pastry"),
            __String::create("cream_cup_10"),
            CCPurchaseWithVirtualItem::create(__String::create(MUFFIN_CURRENCY_ITEM_ID), __Integer::create(500)));

    CCVirtualGood *showRoomGood =
            CCLifetimeVG::create(__String::create("Show Room"), // name
                    __String::create("Show Room "), // description
                    __String::create("show_room"), // item id
                    CCPurchaseWithVirtualItem::create(__String::create(MUFFIN_CURRENCY_ITEM_ID), __Integer::create(100)));

    CCVirtualGood *showRoomGood0 = CCUpgradeVG::create(
            __String::create("show_room"),
            NULL,
            __String::create("show_room_1"),
            __String::create("Show Room L0"),
            __String::create(""),
            __String::create("show_room_0"),
            CCPurchaseWithVirtualItem::create(__String::create(MUFFIN_CURRENCY_ITEM_ID), __Integer::create(220)));

    CCVirtualGood *showRoomGood1 = CCUpgradeVG::create(
            __String::create("show_room"),
            __String::create("show_room_0"),
            __String::create("show_room_2"),
            __String::create("Show Room L1"),
            __String::create(""),
            __String::create("show_room_1"),
            CCPurchaseWithVirtualItem::create(__String::create(MUFFIN_CURRENCY_ITEM_ID), __Integer::create(220)));

	CCVirtualGood *showRoomGood2 = CCUpgradeVG::create(
			__String::create("show_room"),
			__String::create("show_room_1"),
			__String::create("show_room_3"),
			__String::create("Show Room L2"),
			__String::create(""),
			__String::create("show_room_2"),
			CCPurchaseWithVirtualItem::create(__String::create(MUFFIN_CURRENCY_ITEM_ID), __Integer::create(220)));

	CCVirtualGood *showRoomGood3 = CCUpgradeVG::create(
			__String::create("show_room"),
			__String::create("show_room_2"),
			__String::create("show_room_4"),
			__String::create("Show Room L3"),
			__String::create(""),
			__String::create("show_room_3"),
			CCPurchaseWithVirtualItem::create(__String::create(MUFFIN_CURRENCY_ITEM_ID), __Integer::create(220)));

	CCVirtualGood *showRoomGood4 = CCUpgradeVG::create(
			__String::create("show_room"),
			__String::create("show_room_3"),
			NULL,
			__String::create("Show Room L4"),
			__String::create(""),
			__String::create("show_room_4"),
			CCPurchaseWithVirtualItem::create(__String::create(MUFFIN_CURRENCY_ITEM_ID), __Integer::create(220)));

    CCVirtualGood *deliveryVehicleGood =
            CCLifetimeVG::create(__String::create("Delivery Vehicle"), // name
                    __String::create("Delivery Vehicle"), // description
                    __String::create("delivery_vehicle"), // item id
                    CCPurchaseWithVirtualItem::create(__String::create(MUFFIN_CURRENCY_ITEM_ID), __Integer::create(20)));

    CCVirtualGood *deliveryVehicleGood0 = CCUpgradeVG::create(
            __String::create("delivery_vehicle"),
            NULL,
            __String::create("delivery_vehicle_1"),
            __String::create("Delivery Vehicle 0"),
            __String::create(""),
            __String::create("delivery_vehicle_0"),
            CCPurchaseWithVirtualItem::create(__String::create(MUFFIN_CURRENCY_ITEM_ID), __Integer::create(20)));

    CCVirtualGood *deliveryVehicleGood1 = CCUpgradeVG::create(
            __String::create("delivery_vehicle"),
            __String::create("delivery_vehicle_0"),
            __String::create("delivery_vehicle_2"),
            __String::create("Delivery Vehicle 1"),
            __String::create(""),
            __String::create("delivery_vehicle_1"),
            CCPurchaseWithVirtualItem::create(__String::create(MUFFIN_CURRENCY_ITEM_ID), __Integer::create(20)));

    CCVirtualGood *deliveryVehicleGood2 = CCUpgradeVG::create(
			__String::create("delivery_vehicle"),
			__String::create("delivery_vehicle_1"),
			__String::create("delivery_vehicle_3"),
			__String::create("Delivery Vehicle 2"),
			__String::create(""),
			__String::create("delivery_vehicle_2"),
			CCPurchaseWithVirtualItem::create(__String::create(MUFFIN_CURRENCY_ITEM_ID), __Integer::create(20)));

    CCVirtualGood *deliveryVehicleGood3 = CCUpgradeVG::create(
			__String::create("delivery_vehicle"),
			__String::create("delivery_vehicle_2"),
			__String::create("delivery_vehicle_4"),
			__String::create("Delivery Vehicle 3"),
			__String::create(""),
			__String::create("delivery_vehicle_3"),
			CCPurchaseWithVirtualItem::create(__String::create(MUFFIN_CURRENCY_ITEM_ID), __Integer::create(20)));

	CCVirtualGood *deliveryVehicleGood4 = CCUpgradeVG::create(
			__String::create("delivery_vehicle"),
			__String::create("delivery_vehicle_3"),
			NULL,
			__String::create("Delivery Vehicle 4"),
			__String::create(""),
			__String::create("delivery_vehicle_4"),
			CCPurchaseWithVirtualItem::create(__String::create(MUFFIN_CURRENCY_ITEM_ID), __Integer::create(20)));

    CCVirtualGood *fatCatGood = CCEquippableVG::create(
            __Integer::create(CCEquippableVG::kCategory),
            __String::create("Fat Cat"),
            __String::create("Fat cat description"),
            __String::create("fat_cat"),
            CCPurchaseWithVirtualItem::create(__String::create(MUFFIN_CURRENCY_ITEM_ID), __Integer::create(27)));

    CCVirtualGood *happiHippoGood = CCEquippableVG::create(
            __Integer::create(CCEquippableVG::kCategory),
            __String::create("Happi Hippo"),
            __String::create("Happi Hippo description"),
            __String::create("happi_hippo"),
            CCPurchaseWithVirtualItem::create(__String::create(MUFFIN_CURRENCY_ITEM_ID), __Integer::create(44)));

    CCVirtualGood *funkeyMonkeyGood = CCEquippableVG::create(
            __Integer::create(CCEquippableVG::kCategory),
            __String::create("Funkey Monkey"),
            __String::create("Funkey Monkey description"),
            __String::create("funkey_monkey"),
            CCPurchaseWithVirtualItem::create(__String::create(MUFFIN_CURRENCY_ITEM_ID), __Integer::create(35)));


    /** Virtual Categories **/

    CCVirtualCategory *cakes = CCVirtualCategory::create(
            __String::create("Cakes"),
            __Array::create(
                    __String::create(MUFFINCAKE_ITEM_ID),
                    __String::create(PAVLOVA_ITEM_ID),
                    __String::create("pavlova_10"),
                    __String::create(CHOCLATECAKE_ITEM_ID),
                    __String::create(CREAMCUP_ITEM_ID),
                    __String::create("cream_cup_10"),
                    NULL));

    CCVirtualCategory *upgrades = CCVirtualCategory::create(
            __String::create("Upgrades"),
            __Array::create(__String::create("show_room_0"),
							__String::create("show_room_1"),
							__String::create("show_room_2"),
							__String::create("show_room_3"),
							__String::create("show_room_4"),
							__String::create("delivery_vehicle_0"),
							__String::create("delivery_vehicle_1"),
							__String::create("delivery_vehicle_2"),
							__String::create("delivery_vehicle_3"),
							__String::create("delivery_vehicle_4"),
							NULL));

    CCVirtualCategory *characters = CCVirtualCategory::create(
            __String::create("Characters"),
            __Array::create(__String::create("fat_cat"), __String::create("happi_hippo"), __String::create("funkey_monkey"), NULL));


    /** Google MANAGED Items **/
    CCVirtualGood *noAdsLTVG = CCLifetimeVG::create(
              __String::create("No Ads"),
              __String::create("No More Ads!"),
              __String::create("no_ads"),
              CCPurchaseWithMarket::createWithMarketItem(CCMarketItem::create(
                            __String::create(NO_ADDS_LTVG_PRODUCT_ID), CCDouble::create(1.99))
              )
    );
    mCurrencies = __Array::create(muffinCurrency, NULL);
    mCurrencies->retain();

    mGoods = __Array::create(muffincakeGood, pavlovaGood, tenPavlovaGoods, choclatecakeGood, creamcupGood, tenCreamcupGoods,
							 showRoomGood, showRoomGood0, showRoomGood1, showRoomGood2, showRoomGood3, showRoomGood4,
							 deliveryVehicleGood, deliveryVehicleGood0, deliveryVehicleGood1, deliveryVehicleGood2,
							 deliveryVehicleGood3, deliveryVehicleGood4, fatCatGood, happiHippoGood, funkeyMonkeyGood,
                             noAdsLTVG, NULL);
    mGoods->retain();

    mCurrencyPacks = __Array::create(tenmuffPack, fiftymuffPack, fourhundmuffPack, thousandmuffPack, NULL);
    mCurrencyPacks->retain();

    mCategories = __Array::create(cakes, upgrades, characters, NULL);
    mCategories->retain();

    return true;
}

MuffinRushAssets::~MuffinRushAssets() {
    CC_SAFE_RELEASE(mCurrencies);
    CC_SAFE_RELEASE(mGoods);
    CC_SAFE_RELEASE(mCurrencyPacks);
    CC_SAFE_RELEASE(mCategories);
}

int MuffinRushAssets::getVersion() {
    return 0;
}

cocos2d::__Array *MuffinRushAssets::getCurrencies() {
    return mCurrencies;
}

cocos2d::__Array *MuffinRushAssets::getGoods() {
    return mGoods;
}

cocos2d::__Array *MuffinRushAssets::getCurrencyPacks() {
    return mCurrencyPacks;
}

cocos2d::__Array *MuffinRushAssets::getCategories() {
    return mCategories;
}

