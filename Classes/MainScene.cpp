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

#include "MainScene.h"
#include "StoreAScene.h"

USING_NS_CC;

#define SEL_GROUP "soomlaCallback"

CCScene* MainScene::getMainScene() {
    CCNodeLoaderLibrary * ccNodeLoaderLibrary = CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary();

    ccNodeLoaderLibrary->registerCCNodeLoader("MainScene", MainSceneLoader::loader());

    CCBReader *ccbReader = new cocos2d::extension::CCBReader(ccNodeLoaderLibrary);

    return ccbReader->createSceneWithNodeGraphFromFile("ccb/MainScreen.ccbi");
}

SEL_MenuHandler MainScene::onResolveCCBCCMenuItemSelector(CCObject *pTarget, char const *pSelectorName) {
    return NULL;
}

SEL_CCControlHandler MainScene::onResolveCCBCCControlSelector(CCObject *pTarget, char const *pSelectorName) {
    return NULL;
}

bool MainScene::onAssignCCBMemberVariable(CCObject *pTarget, char const *pMemberVariableName, CCNode *pNode) {
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mBackgroundNode", CCNode*, mBackgroundNode);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mMainNode", CCNode*, mMainNode);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mUnlockArea", CCNode*, mUnlockArea);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mUnlocker", CCNode*, mUnlocker);
    return false;
}

void MainScene::onNodeLoaded(CCNode *pNode, CCNodeLoader *pNodeLoader) {
    CC_ASSERT(mBackgroundNode);
    CC_ASSERT(mMainNode);
    CC_ASSERT(mUnlockArea);
    CC_ASSERT(mUnlocker);

    applyScaleForNode(this);
    fill(mBackgroundNode);

    this->setKeypadEnabled(true);
}

bool MainScene::ccTouchBegan(CCTouch* touch, CCEvent* event)
{
    mOriginalPos = mUnlocker->getPosition();
    return true;
}

void MainScene::ccTouchMoved(CCTouch* touch, CCEvent* event)
{
    CCPoint touchPoint = touch->getLocation();
    mUnlocker->setPosition(mUnlocker->getParent()->convertToNodeSpace(touchPoint));
}

void MainScene::ccTouchEnded(CCTouch* touch, CCEvent* event)
{
    CCRect rect1 = mUnlocker->boundingBox();
	CCRect rect2 = mUnlockArea->boundingBox();

	if (rect1.intersectsRect(rect2)) {
        CCScene *s = StoreAScene::getGoodsStoreScene();
        CCDirector::sharedDirector()->setDepthTest(true);
        CCTransitionScene *transition = CCTransitionMoveInR::create(0.8f, s);

        CCDirector::sharedDirector()->replaceScene(transition);
    }
	else {
        // Snap
        mUnlocker->runAction(CCMoveTo::create(0.2f, mOriginalPos));
    }
}

void MainScene::onEnter() {
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 0, true);

    CCLayer::onEnter();
}

void MainScene::onExit() {
    CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);

    CCLayer::onExit();
}
