#ifndef GGAFDX9INPUT_H_
#define GGAFDX9INPUT_H_

class GgafDx9Input {

public:
	/** IDirectInput8�C���^�[�t�F�C�X */
	static LPDIRECTINPUT8 _pIDirectInput8;
	/** �L�[�{�[�h�C���v�b�g�f�o�C�X */
	static LPDIRECTINPUTDEVICE8 _pIDirectInputDevice8_Keyboard;
	/** �W���C�X�e�B�b�N�C���v�b�g�f�o�C�X */
	static LPDIRECTINPUTDEVICE8 _pIDirectInputDevice8_Joystick;
	/** �W���C�X�e�B�b�N�̐��\ */
	static DIDEVCAPS _didevcap;

	static const int BUFFER_SIZE;
	
	/** �L�[�{�[�h�̏�� */	
	static char _caKeyboardState[256];
	/** �W���C�X�e�B�b�N�̏�� */
	static DIJOYSTATE _dijoystate;


	static bool _isReleasedKey[256];
	static bool _isReleasedJoyRgbButton[32];
	static bool _isReleasedJoyUp;
	static bool _isReleasedJoyDown;
	static bool _isReleasedJoyLeft;
	static bool _isReleasedJoyRight;

	static bool _isReleasedJoyDirection[10];

 	/**
	 * �R���X�g���N�^<BR>
	 */
	GgafDx9Input();

 	/**
	 * ������<BR>
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
	static bool isPressedJoyDirection(int prm_iDirectionNo); //�e���L�[�̕����i���o�[�i�P�`�X�B�A���T�������j

	static void release();

};



#endif /*GGAFDX9INPUT_H_*/
