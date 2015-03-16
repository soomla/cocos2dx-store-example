# cocos2dx-store-example

**cocos2dx-store-example** is an example project demonstrating usage and implementation of SOOMLA's [cocos2dx-store](http://github.com/soomla/cocos2dx-store).

This project contains examples for implementing all of SOOMLA's interfaces and using SOOMLA's various services. Read up on what you can do with SOOMLA in this [wiki](https://github.com/soomla/android-store/wiki) (the wiki is for Android but it applies to all the projects under The SOOMLA Project).

## Getting started

1. Obtain the Cocos2d-x framework either from [git](https://github.com/cocos2d/cocos2d-x) or from the [Cocos2d-x website](http://www.cocos2d-x.org/download). Make sure to use the latest **stable** version (v2.2 as of Oct 25 2013).
    ```
    $ git clone git@github.com:cocos2d/cocos2d-x.git
    ```

2. Recursively clone our [cocos2dx-store](https://github.com/soomla/cocos2dx-store) library into the `extensions` directory in the root of your Cocos2d-x framework.
    ```
    $ cd cocos2dx
    $ git clone --recursive git@github.com:soomla/cocos2dx-store.git extensions/cocos2dx-store
    ```

3. Clone our [fork](https://github.com/soomla/jansson) of the janssen library into the `external` directory in the root of your Cocos2d-x framework.
    ```
    $ git clone git@github.com:soomla/jansson.git external/jansson
    ```

4. Clone cocos2dx-store-example into the `projects` directory at the root of the Cocos2d-x framework.
    ```
    $ git clone git@github.com:soomla/cocos2dx-store-example.git projects/cocos2dx-store-example
    ```

#### Build instructions for Android

1. Run the `build_native.sh` script located in projects/cocos2dx-store-example/proj.android. This step should take a while.
    ```
    $ cd projects/cocos2dx-store-example/proj.android
    $ ./build_native.sh
    ```

2. Finally, open the `proj.android` directory located in `cocos2dx-store-example` in Android Studio (IntelliJ IDEA). `proj.android` is an Android Studio project.
3. Build the project, run ExampleActivity, and you're ready to go! The application should launch in an emulator or on your device.

Take a look around, and get a feel for all you can do with cocos2dx-store.


#### Build instructions for iOS

1. Open the XCode project under `proj.ios`.
2. Build the project, run it, and you're ready to go! The application should launch in the simulator or on your device.

Take a look around, and get a feel for all you can do with cocos2dx-store.

#### CCIStoreAssets

A good example of how to define an economy model can be found in [MuffinRushAssets](https://github.com/soomla/cocos2dx-store-example/blob/master/Classes/MuffinRushAssets.cpp).

Take a look at that file and see how you can define your specific game's economy.

#### Scenes

This project contains three main scenes: MainScene, StoreAScene, and StoreBScene. They are all built with [*CocosBuilder*](http://cocosbuilder.com/)
- **MainScene**: serves as an entry point to the store, use it as a reference how to enter the store in your app.
- **StoreAScene**: contains all of the PurchaseWithVirtualItem items and allows the user to buy them.
- **StoreBScene**: contains all of the PurchaseWithMarket items and allows the user to buy them.

## SOOMLA, Elsewhere ...

+ [Website](http://soom.la/)
+ [On Facebook](https://www.facebook.com/pages/The-SOOMLA-Project/389643294427376)
+ [On AngelList](https://angel.co/the-soomla-project)

## License

MIT License. Copyright (c) 2012 SOOMLA. http://project.soom.la
+ http://www.opensource.org/licenses/MIT
