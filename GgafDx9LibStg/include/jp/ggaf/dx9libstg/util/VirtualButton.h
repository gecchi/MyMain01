#ifndef VBRTUALBUTTON_H_
#define VBRTUALBUTTON_H_
namespace GgafDx9LibStg {

#define VB_SHOT1 1
#define VB_SHOT2 2
#define VB_SHOT3 3
#define VB_TURBO 4
#define VB_GUARD 5
#define VB_POWERUP 6
#define VB_PAUSE 7
#define VB_UP 8
#define VB_DOWN 9
#define VB_LEFT 10
#define VB_RIGHT 11

#define VB_UI_UP 12
#define VB_UI_DOWN 13
#define VB_UI_LEFT 14
#define VB_UI_RIGHT 15
#define VB_UI_EXECUTE 16
#define VB_UI_CANCEL 17
#define VB_UI_DEBUG 18

//以下のVB_UP_RIGHT_STC～VB_LEFT_STCは、
//ループのINDEXで使用してるため連番でなければだめ。
//この順番(斜め入力→上下左右)で判定している。
//斜め入力が優先でヒットするようにした。
#define VB_NEUTRAL_STC 20

#define VB_UP_RIGHT_STC 21
#define VB_DOWN_RIGHT_STC 22
#define VB_DOWN_LEFT_STC 23
#define VB_UP_LEFT_STC 24
#define VB_UP_STC 25
#define VB_RIGHT_STC 26
#define VB_DOWN_STC 27
#define VB_LEFT_STC 28

#define VB_MAP_BUFFER 200
#define VB_NUM 29

#define VB VirtualButton


class VirtualButton {

public:

	struct KEYBOARDMAP {
		int SHOT1;
		int SHOT2;
		int SHOT3;
		int TURBO;
		int GUARD;
		int POWERUP;
		int PAUSE;
		int UP;
		int DOWN;
		int LEFT;
		int RIGHT;
		int UI_UP;
		int UI_DOWN;
		int UI_LEFT;
		int UI_RIGHT;
		int UI_EXECUTE;
		int UI_CANCEL;
		int UI_DEBUG;
	};

	struct JOYSTICKMAP {
		int SHOT1;
		int SHOT2;
		int SHOT3;
		int TURBO;
		int GUARD;
		int POWERUP;
		int PAUSE;
		int UI_EXECUTE;
		int UI_CANCEL;
	};

	static KEYBOARDMAP _s_tagKeymap;
	static JOYSTICKMAP _s_tagJoymap;


	class VBMap {
	  public :
		VBMap* _next;  //時系列で次のフレームの入力状態
		VBMap* _prev;  //時系列で前のフレームの入力状態
		bool _state[VB_NUM]; //ボタンの状態
		VBMap() {
			for (int i = 0; i < VB_NUM; i++) { _state[i] = false; }
			_next = NULL;
			_prev = NULL;
		}
		~VBMap() {
		}
	};

	static VBMap* _s_pVBMap; //現在フレームの入力状態

	static VBMap* getPastVBMap(DWORD prm_dwFrameAgo);

	static bool isBeingPressed(int prm_VB);

	static bool wasBeingPressed(int prm_VB, DWORD prm_dwFrameAgo);

	static bool isNotBeingPressed(int prm_VB);

	static bool wasNotBeingPressed(int prm_VB, DWORD prm_dwFrameAgo);

	static bool isPushedDown(int prm_VB);

	static bool wasPushedDown(int prm_VB, DWORD prm_dwFrameAgo);

 	static bool isReleasedUp(int prm_VB);

 	static bool wasReleasedUp(int prm_VB, DWORD prm_dwFrameAgo);

	static bool arePushedDownAtOnce(int prm_aVB[], int prm_iButtonNum);

	static bool arePushedDownAtOnce(int prm_VB1, int prm_VB2) {
		static int vb[2];
		vb[0] = prm_VB1;
		vb[1] = prm_VB2;
		return arePushedDownAtOnce(vb, 2);
	};

	static bool arePushedDownAtOnce(int prm_VB1, int prm_VB2, int prm_VB3) {
		static int vb[3];
		vb[0] = prm_VB1;
		vb[1] = prm_VB2;
		vb[2] = prm_VB3;
		return arePushedDownAtOnce(vb, 3);
	};

	static bool arePushedDownAtOnce(int prm_VB1, int prm_VB2, int prm_VB3, int prm_VB4) {
		static int vb[4];
		vb[0] = prm_VB1;
		vb[1] = prm_VB2;
		vb[2] = prm_VB3;
		vb[3] = prm_VB4;
		return arePushedDownAtOnce(vb, 4);
	};


	/**
	 * 現在押しっぱなしのスティックの番号を返す。
	 * @return 次の何れか
	 * VB_UP_STC
	 * VB_UP_RIGHT_STC
	 * VB_RIGHT_STC
	 * VB_DOWN_RIGHT_STC
	 * VB_DOWN_STC
	 * VB_DOWN_LEFT_STC
	 * VB_LEFT_STC
	 * VB_UP_LEFT_STC
	 * VB_NEUTRAL_STC
	 */
	static int getBeingPressedStick();

	/**
	 * 今PushedDownスティックの番号を返す。
	 * @return 次の何れか
	 * VB_UP_STC
	 * VB_UP_RIGHT_STC
	 * VB_RIGHT_STC
	 * VB_DOWN_RIGHT_STC
	 * VB_DOWN_STC
	 * VB_DOWN_LEFT_STC
	 * VB_LEFT_STC
	 * VB_UP_LEFT_STC
	 * VB_NEUTRAL_STC
	 */
	static int getPushedDownStick();

	/**
	 * 今、prm_VB1と同時にPushedDownされたスティックの番号を返す。
	 * @return 次の何れか
	 * VB_UP_STC
	 * VB_UP_RIGHT_STC
	 * VB_RIGHT_STC
	 * VB_DOWN_RIGHT_STC
	 * VB_DOWN_STC
	 * VB_DOWN_LEFT_STC
	 * VB_LEFT_STC
	 * VB_UP_LEFT_STC
	 * VB_NEUTRAL_STC
	 */
	static int getPushedDownStickWith(int prm_VB);


	static void update();

	static void init();

	static void clear();
};

}
#endif /*VBRTUALBUTTON_H_*/
