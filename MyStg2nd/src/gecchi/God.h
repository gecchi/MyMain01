#ifndef GOD_H_
#define GOD_H_

class God : public DefaultGod {

public:
	God(HINSTANCE prm_hInstance, HWND prm_hWnd);

    /**
     * World�V�[�����쐬�B������
	 * ��OverRide �ł���
	 */
	GgafWorld* createWorld();


	virtual ~God();
};

#endif /*GOD_H_*/
