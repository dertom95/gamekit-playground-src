/*
The zlib/libpng License

Copyright (c) 2005-2010 harkon.kr(http://gamekit.googlecode.com/)

This software is provided 'as-is', without any express or implied warranty. In no event will
the authors be held liable for any damages arising from the use of this software.

Permission is granted to anyone to use this software for any purpose, including commercial 
applications, and to alter it and redistribute it freely, subject to the following
restrictions:

    1. The origin of this software must not be misrepresented; you must not claim that 
		you wrote the original software. If you use this software in a product, 
		an acknowledgment in the product documentation would be appreciated but is 
		not required.

    2. Altered source versions must be plainly marked as such, and must not be 
		misrepresented as being the original software.

    3. This notice may not be removed or altered from any source distribution.
*/

#include "OISInputManager.h"
#include "OISFactoryCreator.h"
#include "OISKeyboard.h"
#include "OISMultiTouch.h"
#include "OISJoyStick.h"

#ifndef OIS_AndroidInputManager_H
#define OIS_AndroidInputManager_H

namespace OIS
{

class AndroidKeyboard : public Keyboard
{
	char mKeyBuffer[256];

public:
	AndroidKeyboard(InputManager* creator);
	
	virtual void setBuffered(bool buffered) {}
	virtual void capture(){}
	virtual Interface* queryInterface(Interface::IType type) {return 0;}
	virtual void _initialize() {}
	virtual bool isKeyDown(KeyCode key) const;	
	virtual const std::string& getAsString(KeyCode kc);
	
	virtual void copyKeyStates(char keys[256]) const;

	void injectKey(int action, int uniChar, int keyCode);
	void injectTextCommit(char* txt,int newcursorpos);

	void resetBuffer();
	static KeyEvent convertKey(int action, int keyCode, int modifier);
};

class AndroidMultiTouch : public MultiTouch
{
	int mOffsetX, mOffsetY;

public:
	AndroidMultiTouch(InputManager* creator);
	
	virtual void setBuffered(bool buffered) {}
	virtual void capture() {}
	virtual Interface* queryInterface(Interface::IType type) {return 0;}
	virtual void _initialize(){}
	

	void injectTouch(int action, float x, float y);
	void injectMultiTouch(int action,int pointerId, float x, float y, float size, float pressure);
	void setOffsets(int x, int y) { mOffsetX = x; mOffsetY = y; }


};

class OuyaJoystick : public JoyStick
{
public:
	OuyaJoystick(InputManager* creator, bool buffered);
	virtual ~OuyaJoystick();

	/** @copydoc Object::setBuffered */
	virtual void setBuffered(bool buffered);

	/** @copydoc Object::capture */
	virtual void capture();

	/** @copydoc Object::queryInterface */
	virtual Interface* queryInterface(Interface::IType type);

	/** @copydoc Object::_initialize */
	virtual void _initialize();

	void _injectValues(int player,int stickNr,float x,float y);
	void _injectButton(int player,int button,bool pressed);
};

class AndroidAccelerometer : public JoyStick
{
public:
	AndroidAccelerometer(InputManager* creator, bool buffered);
	virtual ~AndroidAccelerometer();

	/** @copydoc Object::setBuffered */
	virtual void setBuffered(bool buffered);

    void setUpdateInterval(float interval) {
        mUpdateInterval = interval;
        setUpdateInterval(1.0f / mUpdateInterval);
    }

    virtual Vector3 getAccelerometerVector3(void) { return mState.mVectors[0]; }
	/** @copydoc Object::capture */
	virtual void capture();

	/** @copydoc Object::queryInterface */
	virtual Interface* queryInterface(Interface::IType type) {return 0;}

	/** @copydoc Object::_initialize */
	virtual void _initialize();


    void injectAcceleration(float x,float y,float z);

//protected:
//    iPhoneAccelerometerDelegate *accelerometerDelegate;
//
//    /** The update frequency of the accelerometer.  Represented in times per second. */
    float mUpdateInterval;
    Vector3 mTempState;
};

class AndroidInputManager : public InputManager, public FactoryCreator
{
	AndroidMultiTouch* mTouch;
	AndroidKeyboard* mKeyboard;
	typedef std::vector< OuyaJoystick* > JoystickList;
	JoystickList mJoysticks;

public:
	AndroidInputManager();
	~AndroidInputManager();

	void _initialize(ParamList &paramList);

	DeviceList freeDeviceList();		
	int totalDevices(Type iType);	
	int freeDevices(Type iType);
	int getNumberOfDevices( Type iType ){ return totalDevices(iType);}

	bool vendorExist(Type iType, const std::string & vendor);

	Object* createObject(InputManager* creator, Type iType, bool bufferMode, const std::string & vendor);
	void destroyObject(Object* obj);

	virtual MultiTouch* _getMultiTouch() { return static_cast<MultiTouch*>(mTouch);};

	//--
//	void injectAcceleration(float x,float y,float z)
//	{
//		if (mAccelerometer) mAccelerometer->injectAcceleration(x,y,z);
//	}

	void injectTextCommit(char* txt,int newcursorpos)
	{
		if (mKeyboard)
			mKeyboard->injectTextCommit(txt,newcursorpos);
	}

	void injectKey(int action, int modifiers, int keyCode)
	{
		if (mKeyboard)
			mKeyboard->injectKey(action, modifiers, keyCode);
	}

	void injectTouch(int action, float x, float y)
	{
		if (mTouch) mTouch->injectTouch(action, x, y);
	}

	void injectMultiTouch(int action,int pointerId, float x, float y, float size, float pressure)
	{
		if (mTouch) mTouch->injectMultiTouch(action,pointerId,x,y,size,pressure);
	};

	void injectJoystick(int player,int stick,float x,float y)
	{
		OuyaJoystick* joystick = mJoysticks[player];
		if (!joystick)
		{
			joystick = new OuyaJoystick(this,true);
			mJoysticks[player]=joystick;
		}
		joystick->_injectValues(player,stick,x,y);
	}

	void injectJoystickButton(int player,int button,bool pressed)
	{
		OuyaJoystick* joystick = mJoysticks[player];
		if (!joystick)
		{
			joystick = new OuyaJoystick(this,true);
			mJoysticks[player]=joystick;
		}
		joystick->_injectButton(player,button,pressed);
	}

	void setOffsets(int x, int y) { if (mTouch) mTouch->setOffsets(x,y); }
	void setWindowSize(int w, int h) { if (mTouch) mTouch->setWindowSize(w,h); }
};

}

#endif
