#ifndef GOD_H_
#define GOD_H_

class God : public DefaultGod {

public:
	God(HINSTANCE prm_hInstance, HWND prm_hWnd);

    /**
     * Worldシーンを作成。を実装
	 * ＜OverRide です＞
	 */
	GgafWorld* createWorld();

	virtual ~God();
};

#endif /*GOD_H_*/
