#ifndef MYBUNSHINCONTROLLER_H_
#define MYBUNSHINCONTROLLER_H_
#include "VioletVreath.h"

#include "jp/ggaf/lib/actor/DefaultGeometricActor.h"
#include "jp/ggaf/dxcore/util/GgafDxGeoElem.h"

namespace VioletVreath {

/**
 * 分身土台 .
 * @version 1.00
 * @since 2015/04/17
 * @author Masatoshi Tsuge
 */
class MyBunshinBase : public GgafLib::DefaultGeometricActor {

private:
    class Pos {
    public:
        coord x, y, z;
        Pos() : x(0), y(0), z(0) {}
        void set(coord prm_x, coord prm_y, coord prm_z) {
            x = prm_x;   y = prm_y;   z = prm_z;
        }
        void set(const GgafDxCore::GgafDxGeometricActor* p) {
            x = p->_x;   y = p->_y;   z = p->_z;
        }
        void add(coord prm_x, coord prm_y, coord prm_z) {
            x += prm_x;  y += prm_y;  z += prm_z;
        }
    };
    class PosTrace {
    public:
        Pos* _paPos;
        int _num;
        int _p;
        PosTrace(int n) {
            _p = 0;
            _num = n;
            _paPos = NEW Pos[_num];
        }
        /**
         * カレント要素を一つ進め、進めた後のPosを得る .
         * @return
         */
        Pos* next() {
            if (_p == _num-1) {
                _p = 0;
            } else {
                _p++;
            }
            return &(_paPos[_p]);
        }
        Pos* getPrev() {
            return &(_paPos[ (_p == 0 ? _num-1 : _p-1) ]);
        }
        Pos* getNext() {
            return &(_paPos[ (_p == _num-1 ? 0 : _p+1) ]);
        }
        Pos* get2Next() {
            return &(_paPos[ (_p == _num-1 ? 1 : (_p == _num-2 ? 0 : _p+2) ) ]);
        }
        ~PosTrace() {
            GGAF_DELETEARR(_paPos);
        }
    };
    inline void positionAs(Pos *pPos) {
         position(pPos->x, pPos->y, pPos->z);
    }

    /** [r]分身操作の上下入力時土台回転軸ベクトルX軸要素 */
    float c_ax_x_;
    /** [r]分身操作の上下入力時土台回転軸ベクトルY軸要素 */
    float c_ax_y_;
    /** [r]分身操作の上下入力時土台回転軸ベクトルZ軸要素 */
    float c_ax_z_;
    /**
     * 本体の軸回転 .
     * 回転角度は MyBunshinBase::ANGVELO_TURN
     * @param prm_ax_x 回転軸ベクトルX軸要素
     * @param prm_ax_y 回転軸ベクトルY軸要素
     * @param prm_ax_z 回転軸ベクトルZ軸要素
     */
    void addTurnAngleAroundAx1(float prm_ax_x, float prm_ax_y, float prm_ax_z);

    /**
     * 本体の軸回転 .
     * 回転角度は MyBunshinBase::ANGVELO_TURN
     * VB_UP,VB_DOWN 時の分身の回転軸ベクトル(c_ax_x_, c_ax_y_, c_ax_z_) も、一緒に軸回転させる。
     * @param prm_ax_x 回転軸ベクトルX軸要素
     * @param prm_ax_y 回転軸ベクトルY軸要素
     * @param prm_ax_z 回転軸ベクトルZ軸要素
     */
    void addTurnAngleAroundAx2(float prm_ax_x, float prm_ax_y, float prm_ax_z);

public:
    enum {
        TRACE_TWINBEE,   //ツインビーの分身のようなトレース
        TRACE_GRADIUS,   //グラディウスのオプションのようなトレース
        TRACE_FREEZE,    //グラディウスVのType1のオプションフリーズのような動き
    };

    enum {
        PROG_INIT,
        PROG_BUNSHIN_NOMAL_TRACE,
        PROG_BUNSHIN_FREE_MODE_IGNITED,
        PROG_BUNSHIN_FREE_MODE_READY,
        PROG_BUNSHIN_FREE_MODE_MOVE,
        PROG_BUNSHIN_FREE_MODE_STOP,
        PROG_BUNSHIN_FREE_MODE_BACK_TO_DEFAULT_POS,
        PROG_BANPEI,
    };

    /** 最大分身数 */
    static const int MAX_BUNSHIN_NUM;
    /** [r]分身と分身の間隔 */
    static const frame BUNSHIN_D;
    /** [r]分身の向きの角速度 */
    static const angvelo ANGVELO_TURN;
    /** [r]分身向きの広がり回転角速度 */
    static const angvelo ANGVELO_EXPANSE;
    /** [r]分身が戻ってくる時のMAX速さ */
    static const int RENGE;
    /** 分身フリー移動時の分身の移動速度 */
    static const velo VELO_BUNSHIN_FREE_MV;

    static int now_bunshin_num_;


    /** [r]分身本体 */
    MyBunshin* pBunshin_;
    /** 分身用のトレース座標の歴史（絶対座標）。カレントが自機座標。 */
    PosTrace* pPosTrace_;
    /** 自機トレースの座標からのオフセット(フリーでない場合は0) */
    GgafDxCore::GgafDxGeoElem trace_offset_;
    /** 分身番号(1〜) */
    unsigned int no_;
    /** 分身番号1〜MAXによって、バラける演出のための乗ずる割合が入る */
    double delay_r_;
    /** [r]自身を中心とした、分身の半径距離の位置(初期値) */
    coord bunshin_default_radius_position_;
    /** [r]自身を中心とした、分身の公転軌道上の位置(初期値) */
    angle bunshin_default_ang_position_;
    /** [r]分身の広がり角度(初期値) */
    angle bunshin_default_expanse_;
    /** [r]自身を中心とした、分身の公転の角速度(初期値) */
    angvelo bunshin_default_angvelo_mv_;
    /** [r]分身位置の広がり移動速度 */
    velo bunshin_velo_mv_radius_pos_;
    /** [r]自身を中心とした、分身の半径距離の位置(標準状態) */
    velo bunshin_radius_pos_;

    /** [r]平行移動支援 */
    GgafDxCore::GgafDxAxesMover* pAxsMver_;

    /** [r]このフレーム以上連続で移動すると、TRACE_TWINBEE→TRACE_GRADIUS に移行する */
    frame moving_frames_since_default_pos_;
    /** [r]現在のトレースモード */
    int trace_mode_;
    /** 分身がリセット操作で元の位置に戻るときに費やす基準の時間(フレーム) */
    frame return_default_pos_frames_;

    /** フリーモード時 true */
    bool is_free_mode_;
    /** 分離モード（自機がやられて孤立）時 true */
    bool is_isolate_mode_;

public:
    /**
     * コンストラクタ .
     * @param prm_name
     * @param prm_no 分身番号 (1〜)
     */
    MyBunshinBase(const char* prm_name, unsigned int prm_no);

    /**
     * 分身の設定 .
     * new 直後に実行してください。
     * @param prm_radius_position 分身の位置。中心からの距離（半径）を設定。
     * @param prm_ang_position    分身の位置。どの角度の場所を初期位置とするかを設定。
     * @param prm_expanse         分身の外に広がる角度。
     * @param prm_angvelo_mv      分身の通常時の周回軌道の移動速度
     */
    void config(
            coord prm_radius_position,
            angle prm_ang_position,
            angle prm_expanse,
            angvelo prm_angvelo_mv);

    virtual void initialize() override;

    virtual void onReset() override;

    virtual void onActive() override;

    virtual void onInactive() override;

    virtual void processBehavior() override;

    virtual void processJudgement() override {}

//DefaultMeshActor等で表示したい場合はコメントにすること
//GgafDxGeometricActorの場合はコメントを外すこと
    //virtual void processDraw() override {}

    virtual void onCatchEvent(hashval prm_no, void* prm_pSource) override {}

    virtual void onHit(const GgafCore::GgafActor* prm_pOtherActor) override {}

    virtual ~MyBunshinBase();

    void resetBunshin(int prm_mode);



    /**
     * 分身数を設定 .
     * @param prm_num 分身の数
     */
    static void setBunshinNum(int prm_num);


};

}
#endif /*MYBUNSHINCONTROLLER_H_*/

