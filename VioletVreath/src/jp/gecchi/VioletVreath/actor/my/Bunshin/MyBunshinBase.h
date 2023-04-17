#ifndef MYBUNSHINBASE_H_
#define MYBUNSHINBASE_H_
#include "jp/gecchi/VioletVreath/VioletVreath.h"

#include "jp/ggaf/lib/actor/DefaultGeometricActor.h"
#include "jp/ggaf/dx/util/GeoElem.h"

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
        void set(const GgafDx::GeometricActor* p) {
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
    inline void setPosAt(Pos *pPos) {
         setPosition(pPos->x, pPos->y, pPos->z);
    }

    /** [r]分身操作の上下入力時土台回転軸ベクトルX軸要素 */
    double c_ax_x_;
    /** [r]分身操作の上下入力時土台回転軸ベクトルY軸要素 */
    double c_ax_y_;
    /** [r]分身操作の上下入力時土台回転軸ベクトルZ軸要素 */
    double c_ax_z_;
    /**
     * 本体の軸回転 .
     * 回転角度は MyBunshinBase::ANGVELO_TURN
     * @param prm_ax_x 回転軸ベクトルX軸要素
     * @param prm_ax_y 回転軸ベクトルY軸要素
     * @param prm_ax_z 回転軸ベクトルZ軸要素
     */
    void addTurnAngleAroundAx1(double prm_ax_x, double prm_ax_y, double prm_ax_z);

    /**
     * 本体の軸回転 .
     * 回転角度は MyBunshinBase::ANGVELO_TURN
     * VVB_UP,VVB_DOWN 時の分身の回転軸ベクトル(c_ax_x_, c_ax_y_, c_ax_z_) も、一緒に軸回転させる。
     * @param prm_ax_x 回転軸ベクトルX軸要素
     * @param prm_ax_y 回転軸ベクトルY軸要素
     * @param prm_ax_z 回転軸ベクトルZ軸要素
     */
    void addTurnAngleAroundAx2(double prm_ax_x, double prm_ax_y, double prm_ax_z);

public:
    /** [r]トレース時の分身と分身の間隔 */
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


    /** [r]分身本体操作 */
    MyBunshinController* pMyBunshinController_;
    /** 分身用のトレース座標の歴史（絶対座標）。カレントが自機座標。 */
    PosTrace* pPosTrace_;
    /** 自機トレースの座標からのオフセット(フリーでない場合は0) */
    GgafDx::GeoElem trace_offset_;
    /** 分身番号(1～) */
    unsigned int bunshin_no_;
    /** 分身番号1～MAXによって、バラける演出のための乗ずる割合が入る */
    double delay_r_;
    /** [r]自身を中心とした、分身の半径距離の位置(初期値) */
    coord bunshin_default_radius_pos_;
    /** [r]自身を中心とした、分身の公転軌道上の位置(初期値) */
    angle bunshin_default_ang_pos_;
    /** [r]分身の広がり角度(初期値) */
    angle bunshin_default_expanse_;
    /** [r]自身を中心とした、分身の公転の角速度(初期値) */
    angvelo bunshin_default_angvelo_mv_;
    /** [r]分身位置の広がり移動速度 */
    velo bunshin_velo_mv_radius_pos_;
    /** [r]自身を中心とした、分身の半径距離の位置(標準状態) */
    velo bunshin_radius_pos_;

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
     * @param prm_event_val 分身番号 (1～)
     */
    MyBunshinBase(const char* prm_name, unsigned int prm_bunshin_no);

    /**
     * 分身の設定 .
     * new 直後に実行してください。
     * @param prm_radius_pos 分身の位置。中心からの距離（半径）を設定。
     * @param prm_ang_pos    分身の位置。どの角度の場所を初期位置とするかを設定。
     * @param prm_expanse         分身の外に広がる角度。
     * @param prm_angvelo_mv      分身の通常時の周回軌道の移動速度
     */
    void config(
            coord prm_radius_pos,
            angle prm_ang_pos,
            angle prm_expanse,
            angvelo prm_angvelo_mv);

    virtual void initialize() override;

    virtual void onReset() override;

    virtual void onActive() override;

    virtual void onInactive() override;

    virtual void processBehavior() override;

    virtual void processJudgement() override {}

//DefaultMeshActor等で表示したい場合はコメントにすること
//GeometricActorの場合はコメントを外すこと
    //virtual void processDraw() override {}

    virtual void onCatchEvent(eventval prm_event_val, void* prm_pSource) override {}

    virtual void onHit(const GgafCore::Actor* prm_pOtherActor) override {}

    virtual ~MyBunshinBase();

    void resetBunshin(int prm_mode);



    /**
     * 分身数を設定 .
     * @param prm_num 分身の数
     */
    static void setBunshinNum(int prm_num);


};

}
#endif /*MYBUNSHINBASE_H_*/

