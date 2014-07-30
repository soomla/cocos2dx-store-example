//
// Created by vedi on 2/4/13.
//


#include "LevelIconWidget.h"
#include "CCStoreInventory.h"
#include "CCStoreUtils.h"


LevelIconWidget::LevelIconWidget() {
    mGoodsTitle = NULL;
    mDescriptionLabel = NULL;
    mProgressBar = NULL;
    mProgressLevel1 = NULL;
    mMenu = NULL;
    mButtonBuy = NULL;
    mButtonUpgrade = NULL;
    mEquipment = NULL;
    mPrice = NULL;
    mBalance = NULL;

}

void LevelIconWidget::onNodeLoaded(CCNode *pNode, CCNodeLoader *pNodeLoader) {
    CC_UNUSED_PARAM(pNode);
    CC_UNUSED_PARAM(pNodeLoader);

    CC_ASSERT(mGoodsTitle);
    CC_ASSERT(mDescriptionLabel);
    CC_ASSERT(mProgressBar);
    CC_ASSERT(mProgressLevel1);
    CC_ASSERT(mMenu);
    CC_ASSERT(mButtonBuy);
    CC_ASSERT(mButtonUpgrade);
    CC_ASSERT(mEquipment);
    CC_ASSERT(mPrice);
    CC_ASSERT(mBalance);

    mEquipable = mEquipment->isVisible();
}

void LevelIconWidget::setData(char const *itemId, char const *name, char const *description, double price, int balance) {
    mItemId = itemId;
    mGoodsTitle->setString(name);
    mDescriptionLabel->setString(description);
    mPrice->setString(CCString::createWithFormat("%.2f", price)->getCString());
    setBalance(balance);
}

void LevelIconWidget::setBalance(int balance) {
    mBalance->setString(CCString::createWithFormat("%d", balance)->getCString());
    if (mEquipable) {
        mButtonBuy->setVisible(balance == 0);
        mEquipment->setVisible(balance != 0);
    }
}

void LevelIconWidget::setProgress(int progress) {
    CCAssert(progress >= 0 && progress <= 5, "Sorry UI does not support such progress");
    mProgressLevel1->setScaleX(progress);
}

void LevelIconWidget::setEquiped(bool equiped) {
    this->mEquiped = equiped;
    mEquipment->setNormalSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(
            equiped ? "equipped_O.png" : "equip_O.png"));
}

bool LevelIconWidget::onAssignCCBMemberVariable(CCObject *pTarget, char const *pMemberVariableName, CCNode *pNode) {
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mGoodsTitle", CCLabelTTF*, mGoodsTitle)
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mDescriptionLabel", CCLabelTTF*, mDescriptionLabel)
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mProgressBar", CCSprite*, mProgressBar)
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mProgressLevel1", CCSprite*, mProgressLevel1)
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mMenu", CCNode*, mMenu)
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mButtonBuy", CCMenuItemImage*, mButtonBuy)
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mButtonUpgrade", CCMenuItemImage*, mButtonUpgrade)
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mEquipment", CCMenuItemImage*, mEquipment)
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mPrice", CCLabelTTF*, mPrice)
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mBalance", CCLabelTTF*, mBalance)

    return false;
}

SEL_CCControlHandler LevelIconWidget::onResolveCCBCCControlSelector(CCObject *pTarget, char const *pSelectorName) {
    CC_UNUSED_PARAM(pTarget);
    CC_UNUSED_PARAM(pSelectorName);

    return NULL;
}

SEL_MenuHandler LevelIconWidget::onResolveCCBCCMenuItemSelector(CCObject *pTarget, char const *pSelectorName) {
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onBuy", LevelIconWidget::onBuy)
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onUpgrade", LevelIconWidget::onUpgrade)
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onEquipment", LevelIconWidget::onEquipment)

    return NULL;
}

void LevelIconWidget::onBuy(CCObject *pSender) {

    CC_UNUSED_PARAM(pSender);

    soomla::CCError *soomlaError = NULL;
    soomla::CCStoreInventory::sharedStoreInventory()->buyItem(mItemId.c_str(), &soomlaError);
    if (soomlaError) {
        soomla::CCStoreUtils::logException("LevelIconWidget::onBuy", soomlaError);
    }
}

void LevelIconWidget::onUpgrade(CCObject *pSender) {

    CC_UNUSED_PARAM(pSender);

    soomla::CCError *soomlaError = NULL;
    soomla::CCStoreInventory::sharedStoreInventory()->upgradeGood(mItemId.c_str(), &soomlaError);
    if (soomlaError) {
        soomla::CCStoreUtils::logException("LevelIconWidget::onUpgrade", soomlaError);
    }
}

void LevelIconWidget::onEquipment(CCObject *pSender) {

    CC_UNUSED_PARAM(pSender);

    soomla::CCError *soomlaError = NULL;
    if (!this->mEquiped) {
        soomla::CCStoreInventory::sharedStoreInventory()->equipVirtualGood(mItemId.c_str(), &soomlaError);
    } else {
        soomla::CCStoreInventory::sharedStoreInventory()->unEquipVirtualGood(mItemId.c_str(), &soomlaError);
    }
    if (soomlaError) {
        soomla::CCStoreUtils::logException("LevelIconWidget::onEquipment", soomlaError);
    }
}

