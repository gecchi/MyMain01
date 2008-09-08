#ifndef GGAFDX9INPUT_H_
#define GGAFDX9INPUT_H_

class GgafDx9Input {

public:
	/** IDirectInput8インターフェイス */
	static LPDIRECTINPUT8 _pIDirectInput8;
	/** キーボードインプットデバイス */
	static LPDIRECTINPUTDEVICE8 _pIDirectInputDevice8_Keyboard;
	/** ジョイスティックインプットデバイス */
	static LPDIRECTINPUTDEVICE8 _pIDirectInputDevice8_Joystick;
	/** ジョイスティックの性能 */
	static DIDEVCAPS _didevcap;

	static const int BUFFER_SIZE;
	
	/** キーボードの状態 */	
	static char _caKeyboardState[256];
	/** ジョイスティックの状態 */
	static DIJOYSTATE _dijoystate;


	static bool _isReleasedKey[256];
	static bool _isReleasedJoyRgbButton[32];
	static bool _isReleasedJoyUp;
	static bool _isReleasedJoyDown;
	static bool _isReleasedJoyLeft;
	static bool _isReleasedJoyRight;

	static bool _isReleasedJoyDirection[10];

 	/**
	 * コンストラクタ<BR>
	 */
	GgafDx9Input();

 	/**
	 * 初期化<BR>
	 */
	static HRESULT init();

	static void updateKeyboardState();
	static bool isBeingPressedKey(int prm_DIK);
	static bool isPressedKey(int prm_DIK);

	static void updateJoystickState();
	static bool isBeingPressedJoyRgbButton(int prm_iRgbButtonNo);
	static bool isBeingPressedJoyUp();
	static bool isBeingPressedJoyDown();
	static bool isBeingPressedJoyLeft();
	static bool isBeingPressedJoyRight();
	static bool isBeingPressedJoyDirection(int prm_iDirectionNo);
	static bool isPressedJoyRgbButton(int prm_iButtonNo);
	static bool isPressedJoyUp();
	static bool isPressedJoyDown();
	static bool isPressedJoyLeft();
	static bool isPressedJoyRight();
	static bool isPressedJoyDirection(int prm_iDirectionNo); //テンキーの方向ナンバー（１～９。但し５を除く）

	static void release();

};



#endif /*GGAFDX9INPUT_H_*/
