#ifndef VBRTUALBUTTON_H_
#define VBRTUALBUTTON_H_

typedef std::map<std::string, int> keymap;
typedef unsigned long int vbsta;

namespace GgafLib {

#define VB_BUTTON1 (0x1)               //&B 00000000 00000000 00000000 00000001
#define VB_BUTTON2 (0x2)               //&B 00000000 00000000 00000000 00000010
#define VB_BUTTON3 (0x4)               //&B 00000000 00000000 00000000 00000100
#define VB_BUTTON4 (0x8)               //&B 00000000 00000000 00000000 00001000
#define VB_BUTTON5 (0x10)              //&B 00000000 00000000 00000000 00010000
#define VB_BUTTON6 (0x20)              //&B 00000000 00000000 00000000 00100000
#define VB_BUTTON7 (0x40)              //&B 00000000 00000000 00000000 01000000
#define VB_BUTTON8 (0x80)              //&B 00000000 00000000 00000000 10000000
                                       //&B 00000000 00000000 00000001 00000000
                                       //&B 00000000 00000000 00000010 00000000
#define VB_PAUSE          (0x400)      //&B 00000000 00000000 00000100 00000000
#define VB_UP             (0x800)      //&B 00000000 00000000 00001000 00000000
#define VB_DOWN           (0x1000)     //&B 00000000 00000000 00010000 00000000
#define VB_LEFT           (0x2000)     //&B 00000000 00000000 00100000 00000000
#define VB_RIGHT          (0x4000)     //&B 00000000 00000000 01000000 00000000
#define VB_UI_UP          (0x8000)     //&B 00000000 00000000 10000000 00000000
#define VB_UI_DOWN        (0x10000)    //&B 00000000 00000001 00000000 00000000
#define VB_UI_LEFT        (0x20000)    //&B 00000000 00000010 00000000 00000000
#define VB_UI_RIGHT       (0x40000)    //&B 00000000 00000100 00000000 00000000
#define VB_UI_EXECUTE     (0x80000)    //&B 00000000 00001000 00000000 00000000
#define VB_UI_CANCEL      (0x100000)   //&B 00000000 00010000 00000000 00000000
#define VB_UI_DEBUG       (0x200000)   //&B 00000000 00100000 00000000 00000000
#define VB_NEUTRAL_STC    (0x400000)   //&B 00000000 01000000 00000000 00000000
#define VB_UP_RIGHT_STC   (0x800000)   //&B 00000000 10000000 00000000 00000000
#define VB_DOWN_RIGHT_STC (0x1000000)  //&B 00000001 00000000 00000000 00000000
#define VB_DOWN_LEFT_STC  (0x2000000)  //&B 00000010 00000000 00000000 00000000
#define VB_UP_LEFT_STC    (0x4000000)  //&B 00000100 00000000 00000000 00000000
#define VB_UP_STC         (0x8000000)  //&B 00001000 00000000 00000000 00000000
#define VB_RIGHT_STC      (0x10000000) //&B 00010000 00000000 00000000 00000000
#define VB_DOWN_STC       (0x20000000) //&B 00100000 00000000 00000000 00000000
#define VB_LEFT_STC       (0x40000000) //&B 01000000 00000000 00000000 00000000

#define VB_UDLR           (VB_UP|VB_DOWN|VB_LEFT|VB_RIGHT)
#define VB_UI_UDLR        (VB_UI_UP|VB_UI_DOWN|VB_UI_LEFT|VB_UI_RIGHT)

#define VB_STC_CLIP_MASK  (0x803FFFFF) //&B 10000000 00111111 11111111 11111111
#define VB_STC_MASK       (0x7FC00000) //&B 01111111 11000000 00000000 00000000

#define VB_MAP_BUFFER 120
#define VB_NUM 29

/**
 * 仮想ボタン .
 * @version 1.00
 * @since 2008/09/08
 * @author Masatoshi Tsuge
 */
class VirtualButton : public GgafCore::GgafObject {

public:
    struct KEYBOARDMAP {
        int BUTTON1;
        int BUTTON2;
        int BUTTON3;
        int BUTTON4;
        int BUTTON5;
        int BUTTON6;
        int BUTTON7;
        int BUTTON8;
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
        int BUTTON7;
        int BUTTON8;
        int PAUSE;
        int UI_EXECUTE;
        int UI_CANCEL;
    };

    static KEYBOARDMAP _tagKeymap;
    static JOYSTICKMAP _tagJoymap;

    /**
     * 仮想ボタンコンテナ .
     */
    class VBRecord {
    public :
        VBRecord* _next; //時系列で次のフレームの入力状態
        VBRecord* _prev; //時系列で前のフレームの入力状態

        vbsta _state;
    public:
        VBRecord() {
            _next = nullptr;
            _prev = nullptr;
            _state = (vbsta)0;
        }
        ~VBRecord() {
        }
    };
    /** オートリピート判定用カウンター */
    std::map<vbsta, frame> _auto_repeat_counter;
    /** オートリピート中ならば true */
    bool _is_auto_repeat;

    VBReplayRecorder* _pRpy;

    static keymap _mapDIK;
    static bool _is_init;

    /** [r]リプレイモード時:true／ユーザー入力（リプレイモード記入）モード:false */
    bool _is_replaying;
    /** [r]初期状態:false／リプレイモード終了:true */
    bool _was_replay_done;

public:
    /**
     * コンストラクタ .
     * 引数のリプレイファイルが存在する場合→リプレイーモード。
     * 引数のリプレイファイルが存在しない場合→ユーザー入力受付 ＆ リプレイファイル記入モード。
     * @param prm_replay_file リプレイファイル
     */
    VirtualButton(const char* prm_replay_file = "VirtualButton.rep");

    VBRecord* _pVBRecord_Active; //現在フレームの入力状態

    VBRecord* getPastVBRecord(frame prm_frame_ago);

    /**
     * 現在ボタンが押されているか判定 .
     * @param prm_VB 判定対象仮想ボタン。VB_ で始まる定数(の論理和)
     * @return true/false
     */
    inline vbsta isBeingPressed(vbsta prm_VB) {
        return (_pVBRecord_Active->_state & prm_VB);
    }


    /**
     * 現在ボタンが押されていないか判定 .
     * isBeingPressed(vbsta) の否定の結果が返る。
     * @param prm_VB 判定対象仮想ボタン。VB_ で始まる定数(の論理和)
     * @return true/false
     */
    vbsta isNotBeingPressed(vbsta prm_VB);

    /**
     * 過去にボタンが押されていたかどうか判定 .
     * @param prm_VB 判定対象仮想ボタン。VB_ で始まる定数(の論理和)
     * @param prm_frame_ago 何フレーム前(>0)を判定するのか指定。
     *                      1 で 1フレーム前、2 で 2フレーム前、0 は isBeingPressed(vbsta) と同じ意味になる。
     *                      最大 (VB_MAP_BUFFER-1) フレーム前まで可
     * @return true/false
     */
    vbsta wasBeingPressed(vbsta prm_VB, frame prm_frame_ago);

    /**
     * 過去にボタンが押されていなかったのかどうか判定 .
     * wasBeingPressed(vbsta, frame) の否定の結果が返る。
     * @param prm_VB 判定対象仮想ボタン。VB_ で始まる定数(の論理和)
     * @param prm_frame_ago 何フレーム前(>0)を判定するのか指定。
     *                      1 で 1フレーム前、2 で 2フレーム前、0 は isBeingPressed(vbsta) と同じ意味になる。
     *                      最大 (VB_MAP_BUFFER-1) フレーム前まで可
     * @return true/false
     */
    vbsta wasNotBeingPressed(vbsta prm_VB, frame prm_frame_ago);

    /**
     * 現在ボタンが押された瞬間なのかどうか判定 .
     * 現在は押されている、かつ、１フレーム前は押されていない場合に true
     * @param prm_VB 判定対象仮想ボタン。VB_ で始まる定数(の論理和)
     * @return true/false
     */
    inline vbsta isPushedDown(vbsta prm_VB) {
        return (!(_pVBRecord_Active->_prev->_state & prm_VB) && (_pVBRecord_Active->_state & prm_VB)) ? true : false;
    }

    /**
     * 過去にボタンが押された瞬間があったのかどうか判定 .
     * prm_frame_agoフレーム前は押されていた、かつ、(prm_frame_ago+1)フレーム前は押されていなかった場合に true
     * @param prm_VB 判定対象仮想ボタン。VB_ で始まる定数(の論理和)
     * @param prm_frame_ago 何フレーム前(>0)を判定するのか指定。
     *                      1 で 1フレーム前、2 で 2フレーム前、0 は isPushedDown(vbsta) と同じ意味になる。
     *                      最大 (VB_MAP_BUFFER-1) フレーム前まで可
     * @return true/false
     */
    vbsta wasPushedDown(vbsta prm_VB, frame prm_frame_ago);

    /**
     * 現在ボタンを離した瞬間なのかどうか判定 .
     * 現在は押されていない、かつ、１フレーム前は押されていた場合に true
     * @param prm_VB 判定対象仮想ボタン。VB_ で始まる定数(の論理和)
     * @return true/false
     */
    vbsta isReleasedUp(vbsta prm_VB);

    /**
     * 過去にボタンを離した瞬間があったのかどうか判定 .
     * prm_frame_agoフレーム前は押されていなかった、かつ、(prm_frame_ago+1)フレーム前は押されていた場合に true
     * @param prm_VB 判定対象仮想ボタン。VB_ で始まる定数(の論理和)
     * @param prm_frame_ago 何フレーム前(>0)を判定するのか指定。
     *                      1 で 1フレーム前、2 で 2フレーム前、0 は isReleasedUp(vbsta) と同じ意味になる。
     * @return true/false
     */
    vbsta wasReleasedUp(vbsta prm_VB, frame prm_frame_ago);

    /**
     * チョン押し判定 .
     * 「ボタンを押していなかった→ボタンを押した→ボタンを離した」という状態遷移が、
     * 現在成立したかどうか判定する。
     * 但し押していた期間が prm_frame_push 以上押していると成立しない（チョン押しと認められない）。
     * ※たとえば独歩のGボタン判定なら prm_frame_push=2 を指定。ﾅﾝﾉｺｯﾁｬ;
     * @param prm_VB 判定対象仮想ボタン。VB_ で始まる定数(の論理和)
     * @param prm_frame_push 許容するボタンを押していた期間フレーム(default=5)
     * @return true/false
     */
    vbsta isPushedUp(vbsta prm_VB, frame prm_frame_push = 5);

    /**
     * ダブルプッシュ判定 .
     * 「(a)ボタンを押していなかった→(b)ボタンを押した→(c)ボタンを離した→(d)ボタンを押した」という状態遷移が、
     * 現在成立したかどうか判定する。
     * 但し   (b)～(c)の押していた期間が prm_frame_push 以上押していると成立しない。
     * さらに (c)～(d)の２回目のボタン押しまでの期間が prm_frame_delay 以上開いていると成立しない。
     * @param prm_VB 判定対象仮想ボタン。VB_ で始まる定数(の論理和)
     * @param prm_frame_push 許容する(b)～(c) の期間
     * @param prm_frame_delay 許容する(c)～(d) の期間
     * @return true/false
     */
    vbsta isDoublePushedDown(vbsta prm_VB, frame prm_frame_push = 5, frame prm_frame_delay = 5);

    /**
     * 複数ボタン同時押し判定 .
     * isPushedDown(vbsta) の引数に複数ボタンを指定して判定を行えば、同時押し判定は可能である。
     * しかし、その判定方法は複数ボタンを押す際に1フレームでもバラツキがあれば成立せず、
     * 完全に同時に押さなければならないため、シビアすぎるという問題点がある。
     * そこで、本メソッドは、同時押しのバラツキを許容考慮した同時押し判定である。
     * 具体的には、引数のそれぞれの各ボタンの現在に至るまでの４フレームの状態履歴が、
     * 次のいずれかの状態遷移であれば1回成立という判定を行っている。(つまり3フレーム猶予)
     * <pre>
     * ↑ > ？ > ？ > ↓
     *       or
     * ？ > ↑ > ？ > ↓
     *       or
     * ？ > ？ > ↑ > ↓
     *
     * ※↓：押している ／ ↑：離している ／ ？：任意
     * ※一番右が現在の状態、左が過去
     * </pre>
     * @param prm_aVB (3フレ猶予)同時押し判定対象仮想ボタン配列
     * @param prm_num_button 配列の要素数
     * @return true/false
     */
    vbsta arePushedDownAtOnce(vbsta prm_aVB[], int prm_num_button);

    /**
     * ３フレ猶予の２つボタン同時押し判定 .
     * @param prm_VB1 判定対象仮想ボタン１
     * @param prm_VB2 判定対象仮想ボタン２
     * @return true/false
     */
    vbsta arePushedDownAtOnce(vbsta prm_VB1, vbsta prm_VB2) {
        vbsta vb[2];
        vb[0] = prm_VB1;
        vb[1] = prm_VB2;
        return arePushedDownAtOnce(vb, 2);
    }

    /**
     * ３フレ猶予の３つボタン同時押し判定 .
     * @param prm_VB1 判定対象仮想ボタン１
     * @param prm_VB2 判定対象仮想ボタン２
     * @param prm_VB3 判定対象仮想ボタン３
     * @return true/false
     */
    vbsta arePushedDownAtOnce(vbsta prm_VB1, vbsta prm_VB2, vbsta prm_VB3) {
        vbsta vb[3];
        vb[0] = prm_VB1;
        vb[1] = prm_VB2;
        vb[2] = prm_VB3;
        return arePushedDownAtOnce(vb, 3);
    }

    /**
     * ３フレ猶予の４つボタン同時押し判定 .
     * @param prm_VB1 判定対象仮想ボタン１
     * @param prm_VB2 判定対象仮想ボタン２
     * @param prm_VB3 判定対象仮想ボタン３
     * @param prm_VB4 判定対象仮想ボタン４
     * @return true/false
     */
    vbsta arePushedDownAtOnce(vbsta prm_VB1, vbsta prm_VB2, vbsta prm_VB3, vbsta prm_VB4) {
        vbsta vb[4];
        vb[0] = prm_VB1;
        vb[1] = prm_VB2;
        vb[2] = prm_VB3;
        vb[3] = prm_VB4;
        return arePushedDownAtOnce(vb, 4);
    }

    /**
     * オートリピート入力判定 .
     * @param prm_VB 判定対象仮想ボタン。VB_ で始まる定数(の論理和)
     * @param prm_begin_repeat オートリピート開始フレーム数
     * @param prm_while_repeat オートリピート開始後、リピート間隔フレーム数
     * @return true/false
     */
    vbsta isAutoRepeat(vbsta prm_VB, frame prm_begin_repeat = 20, frame prm_while_repeat = 5);

    /**
     * グルッとポンか否か判定 .
     * ザンギエフのスクリューパイルドライバーコマンド入力判定です。
     * 具体的には、prm_frame_delay 以内に
     * ↑ → ↓ ← の４方向ボタン押しが成立後、isPushedDown(prm_VB) が成立。
     * の場合に true としています。
     * @param prm_VB 「グルッとポン」の「ポン」のボタン
     * @param prm_frame_delay 「グルッとポン」が成立する全体の許容フレーム
     * @return true/false
     */
    bool isRoundPushDown(vbsta prm_VB, frame prm_frame_delay=30);

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
    vbsta getBeingPressedStick();

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
    vbsta getPushedDownStick();


    vbsta isDoublePushedDownStick(frame prm_frame_push = 5, frame prm_frame_delay = 5);


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


    //vbsta isClicked(vbsta prm_VB);

    vbsta getState();

    /**
     * 入力情報を更新 .
     * 通常時はキー入力、ジョイスティック、マウスのデバイスに入力により、内部ステートを更新。
     * 但し、リプレイ再生中は、読み込まれた外部ファイルのデータで、内部ステートを更新。
     */
    void update();

    void init();

    void clear();

    virtual ~VirtualButton();
};

}
#endif /*VBRTUALBUTTON_H_*/
