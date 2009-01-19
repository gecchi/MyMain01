#ifndef GOD_H_
#define GOD_H_
namespace MyStg2nd {

class God : public GgafDx9LibStg::DefaultGod {

public:
	God(HINSTANCE prm_hInstance, HWND prm_hWnd);

    /**
     * Worldシーンを作成。を実装
	 * ＜OverRide です＞
	 */
	GgafCore::GgafWorld* createWorld();

	virtual ~God();
};

}
#endif /*GOD_H_*/
