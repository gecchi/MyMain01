#ifndef VBRTUALBUTTON_H_
#define VBRTUALBUTTON_H_
namespace GgafDx9LibStg {

#define VB_BUTTON1 (0x1)
#define VB_BUTTON2 (0x2)
#define VB_BUTTON3 (0x4)
#define VB_BUTTON4 (0x8)
#define VB_BUTTON5 (0x10)
#define VB_BUTTON6 (0x20)

#define VB_PAUSE   (0x400)
#define VB_UP      (0x800)
#define VB_DOWN    (0x1000)
#define VB_LEFT    (0x2000)
#define VB_RIGHT   (0x4000)

#define VB_UI_UP      (0x8000)
#define VB_UI_DOWN    (0x10000)
#define VB_UI_LEFT    (0x20000)
#define VB_UI_RIGHT   (0x40000)
#define VB_UI_EXECUTE (0x80000)
#define VB_UI_CANCEL  (0x100000)
#define VB_UI_DEBUG   (0x200000)

#define VB_NEUTRAL_STC    (0x400000)
#define VB_UP_RIGHT_STC   (0x800000)
#define VB_DOWN_RIGHT_STC (0x1000000)
#define VB_DOWN_LEFT_STC  (0x2000000)
#define VB_UP_LEFT_STC    (0x4000000)
#define VB_UP_STC         (0x8000000)
#define VB_RIGHT_STC      (0x10000000)
#define VB_DOWN_STC       (0x20000000)
#define VB_LEFT_STC       (0x40000000)

#define VB_STC_CLIP_MASK       (0x803FFFFF) //&B 10000000 00111111 11111111 11111111
#define VB_STC_MASK            (0x7FC00000) //&B 01111111 11000000 00000000 00000000

#define VB_MAP_BUFFER 200
#define VB_NUM 29

#define VB VirtualButton
typedef map<string, int> keymap;
typedef unsigned long int vbsta;


class VirtualButton {

public:

    struct KEYBOARDMAP {
        int BUTTON1;
        int BUTTON2;
        int BUTTON3;
        int BUTTON4;
        int BUTTON5;
        int BUTTON6;
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
        int BUTTON1;
        int BUTTON2;
        int BUTTON3;
        int BUTTON4;
        int BUTTON5;
        int BUTTON6;
        int PAUSE;
        int UI_EXECUTE;
        int UI_CANCEL;
    };

    static KEYBOARDMAP _tagKeymap;
    static JOYSTICKMAP _tagJoymap;

    class VBMap {
    public :
        VBMap* _next; //時系列で次のフレームの入力状態
        VBMap* _prev; //時系列で前のフレームの入力状態

        vbsta _state;


        //bool _state[VB_NUM]; //ボタンの状態
        //TODO: あとでビットフィールドにして高速化

        VBMap() {
            //for (int i = 0; i < VB_NUM; i++) {_state[i] = false;}
            _next = NULL;
            _prev = NULL;
            _state = 0;
        }
        ~VBMap() {
        }
    };

    static keymap _mapDIK;

    static VBMap* _pVBMap_Active; //現在フレームの入力状態

    static VBMap* _pVBMap_Reset; //入力状態をリセットする位置

    static VBMap* getPastVBMap(DWORD prm_dwFrameAgo);

    static vbsta isBeingPressed(vbsta prm_VB);

    static vbsta wasBeingPressed(vbsta prm_VB, DWORD prm_dwFrameAgo);

    static vbsta isNotBeingPressed(vbsta prm_VB);

    static vbsta wasNotBeingPressed(vbsta prm_VB, DWORD prm_dwFrameAgo);

    static vbsta isPushedDown(vbsta prm_VB);


    static vbsta wasPushedDown(vbsta prm_VB, DWORD prm_dwFrameAgo);

    static vbsta isReleasedUp(vbsta prm_VB);

    static vbsta wasReleasedUp(vbsta prm_VB, DWORD prm_dwFrameAgo);

    static vbsta arePushedDownAtOnce(vbsta prm_aVB[], int prm_iButtonNum);

    static vbsta arePushedDownAtOnce(vbsta prm_VB1, vbsta prm_VB2) {
        static vbsta vb[2];
        vb[0] = prm_VB1;
        vb[1] = prm_VB2;
        return arePushedDownAtOnce(vb, 2);
    }

    static vbsta arePushedDownAtOnce(vbsta prm_VB1, vbsta prm_VB2, vbsta prm_VB3) {
        static vbsta vb[3];
        vb[0] = prm_VB1;
        vb[1] = prm_VB2;
        vb[2] = prm_VB3;
        return arePushedDownAtOnce(vb, 3);
    }

    static vbsta arePushedDownAtOnce(vbsta prm_VB1, vbsta prm_VB2, vbsta prm_VB3, vbsta prm_VB4) {
        static vbsta vb[4];
        vb[0] = prm_VB1;
        vb[1] = prm_VB2;
        vb[2] = prm_VB3;
        vb[3] = prm_VB4;
        return arePushedDownAtOnce(vb, 4);
    }

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
    static vbsta getBeingPressedStick();

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
    static vbsta getPushedDownStick();

//    /**
//     * 今、prm_VB1と同時にPushedDownされたスティックの番号を返す。
//     * @return 次の何れか
//     * VB_UP_STC
//     * VB_UP_RIGHT_STC
//     * VB_RIGHT_STC
//     * VB_DOWN_RIGHT_STC
//     * VB_DOWN_STC
//     * VB_DOWN_LEFT_STC
//     * VB_LEFT_STC
//     * VB_UP_LEFT_STC
//     * VB_NEUTRAL_STC
//     */
//    static vbsta getPushedDownStickWith(int prm_VB);

    static void update();

    static void init();

    static void clear();
};

}
#endif /*VBRTUALBUTTON_H_*/
