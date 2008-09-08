#ifndef GOD_H_
#define GOD_H_

class God : public DefaultGod {

public:
	God(HINSTANCE prm_hInstance, HWND prm_hWnd);

    /**
     * WorldƒV[ƒ“‚ğì¬B‚ğÀ‘•
	 * ƒOverRide ‚Å‚·„
	 */
	GgafWorld* createWorld();


	virtual ~God();
};

#endif /*GOD_H_*/
