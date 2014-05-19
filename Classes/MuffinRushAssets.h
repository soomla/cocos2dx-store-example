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

#ifndef __MuffinRushAssets_H_
#define __MuffinRushAssets_H_

#include "CCIStoreAssets.h"
#include "cocos2d.h"

class MuffinRushAssets: public soomla::CCIStoreAssets {
    cocos2d::CCArray *mCurrencies;
    cocos2d::CCArray *mGoods;
    cocos2d::CCArray *mCurrencyPacks;
    cocos2d::CCArray *mCategories;
    cocos2d::CCArray *mNonConsumableItems;

public:
    MuffinRushAssets():
    mCurrencies(NULL),
    mGoods(NULL),
    mCurrencyPacks(NULL),
    mCategories(NULL),
    mNonConsumableItems(NULL)
    {}

    /**
     Constructor.
     */
    static MuffinRushAssets *create();
    bool init();
    
    /**
     Destructor.
     */
    virtual ~MuffinRushAssets();

    /**
     see parent.
     */
    virtual int getVersion();

    /**
     see parent.
     */
    virtual cocos2d::CCArray *getCurrencies();

    /**
     see parent.
     */
    virtual cocos2d::CCArray *getGoods();

    /**
     see parent.
     */
    virtual cocos2d::CCArray *getCurrencyPacks();

    /**
     see parent.
     */
    virtual cocos2d::CCArray *getCategories();

    /**
     see parent.
     */
    virtual cocos2d::CCArray *getNonConsumableItems();
};


#endif //__MuffinRushAssets_H_
