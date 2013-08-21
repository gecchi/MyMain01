#ifndef GGAFDXCAMERAACTOR_H_
#define GGAFDXCAMERAACTOR_H_
#include "jp/ggaf/dxcore/actor/GgafDxGeometricActor.h"

namespace GgafDxCore {

/**
 * カメラアクター.
 * GgafDxGeometricActor を継承し、カメラを表したアクターです。<BR>
 * 本クラスは神(GgafDxGod)と連動ています。メンバを操作すると、その通りにカメラの位置と注視点が操作できます。<BR>
 * processPreDraw メソッドが実装されており、その中で神(GgafDxGod)のカメラに座標情報を上書きします。<BR>
 * <BR>
 * _X,_Y,_Z             ・・・ カメラの位置 <BR>
 * <BR>
 * ＜使い方＞<BR>
 * 継承し、processBehavior() 等を オーバーライドして好きに座標を動かすがよい<BR>
 * <BR>
 * @version 1.00
 * @since 2009/02/12
 * @author Masatoshi Tsuge
 */
class GgafDxCamera : public GgafDxGeometricActor {

public:
    D3DVIEWPORT9 _viewport;

    // 視錐台の6つの面の頂点座標
    /** [r]視錐台面、手前の四角形の頂点(読み込み専用、毎フレーム更新) */
    D3DXVECTOR3 _vecNear[4];
    /** [r]視錐台面、奥の四角形の頂点(読み込み専用、毎フレーム更新) */
    D3DXVECTOR3 _vecFar[4];

    D3DXVECTOR3 _vecVerticalCenter[4];

    // 視錐台の6つの面
    /** [r]視錐台面、上(読み込み専用、毎フレーム更新) */
    D3DXPLANE _plnTop;
    /** [r]視錐台面、下(読み込み専用、毎フレーム更新) */
    D3DXPLANE _plnBottom;
    /** [r]視錐台面、左(読み込み専用、毎フレーム更新) */
    D3DXPLANE _plnLeft;
    /** [r]視錐台面、右(読み込み専用、毎フレーム更新) */
    D3DXPLANE _plnRight;
    /** [r]視錐台面、手前(読み込み専用、毎フレーム更新) */
    D3DXPLANE _plnFront;
    /** [r]視錐台面、奥(読み込み専用、毎フレーム更新) */
    D3DXPLANE _plnBack;
    /** [r]視錐台を左右に分割する垂直面、左右の効果音のパンに使用(読み込み専用、毎フレーム更新) */
    D3DXPLANE _plnVerticalCenter;

    /** [r]射影変換行列 */
    D3DXMATRIX _matProj;
    /** [r]正射影変換行列 */
    D3DXMATRIX _vMatrixOrthoProj;

    /** [r]カメラの位置(フレーム毎更新) */
    D3DXVECTOR3* _pVecCamFromPoint;
    /** [r]カメラの注視点(フレーム毎更新) */
    D3DXVECTOR3* _pVecCamLookatPoint;
    /** [r]カメラの上ベクトル(フレーム毎更新) */
    D3DXVECTOR3* _pVecCamUp;
    /** [r]VIEW変換行列(フレーム毎更新) */
    D3DXMATRIX _matView;
    /** [r]視野角Xラジアン */
    double _rad_fovX;
    /** [r]視野角Xラジアンの半分 */
    double _rad_half_fovX;
    /** [r]視野角Yラジアン */
    double _rad_fovY;
    /** [r]視野角Yラジアンの半分 */
    double _rad_half_fovY;
    /** [r]カメラのZ座標 */
    dxcoord _cameraZ;
    /** [r]カメラのZ座標初期位置 */
    dxcoord _cameraZ_org;
    /** [r]アスペクト比 */
    double _screen_aspect;
    /** [r]視野角Yタンジェントの半分 */
    double _tan_half_fovY;
    /** [r]視野角Xタンジェントの半分 */
    double _tan_half_fovX;
    /** [r]カメラから近くのクリップ面までの距離(どこからの距離が表示対象か）≠0 */
    dxcoord _zn;
    /** [r]カメラから遠くのクリップ面までの距離(どこまでの距離が表示対象か）> zn */
    dxcoord _zf;
    /** [r]深さ（_cameraZ_orgの何倍か)  */
    double _dep;
    /** [r/w]注視点 **/
    GgafDxCameraViewPoint* _pViewPoint;

    coord _X_prev, _Y_prev, _Z_prev;

    coord _X_buffer_left;
    coord _X_buffer_right;
    coord _Y_buffer_top;
    coord _Y_buffer_bottom;

public:
    /**
     * コンストラクタ .
     * 視野角と表示深さを設定する。
     * 視野角によって、カメラの初期Z位置が決定する。
     * このカメラの初期Z位置は、原点付近でDirctXの長さ1（のオブジェクト）を
     * 画面上10ピクセル相当で表示する位置へカメラを引くように自動計算される。（_cameraZ_orgに保持)
     * この原点から、初期のカメラZ位置までを1.0として、表示範囲の深さの倍数を引数 prm_dep で設定する。
     * prm_dep=1.0とした場合。表示範囲は 原点を中心とし、半径を初期カメラZ位置の距離の球となる。
     * また、表示範囲＋αが、アクター達のゲーム内での可動範囲となるように設計しているため、カメラの初期設定値は
     * 非常に重要である。
     * 通常視野角を狭めればズームアップの効果が得られるが、本ライブラリでは、
     * 上記の初期Z位置までカメラを自動で引くため、視野角を変更してもアクターの表示の大きさは画面上変わらない。
     * ただし視野角を狭くすれば、初期のカメラを引く距離も伸びることになり、結果として
     * 世界の表示範囲を拡大する効果をえることができる。
     * 逆に視野角が広ければ、カメラの初期Z位置は原点に近くなり、実は世界の表示範囲は狭くなる。
     *
     * @param prm_name 名前(デバックで表示。何でもよい)
     * @param prm_rad_fovX 左右の視野角（ラジアン）
     * @param prm_dep 深さ（_cameraZ_orgの何倍か)
     * @return
     */
    GgafDxCamera(const char* prm_name, double prm_rad_fovX, double prm_dep);

    virtual void initialize() override;

    virtual void processBehavior() override;

    virtual void processJudgement() override;

    virtual void processPreDraw() override {
    }

    virtual void processDraw() override {
    }

    virtual void processAfterDraw() override {
    }

    virtual void onCatchEvent(hashval prm_no, void* prm_pSource) override {
    }

    virtual void processFinal() override {
    }

    virtual void onHit(GgafCore::GgafActor* prm_pOtherActor) override {
    }

    virtual void setDefaultPosition();

    virtual GgafDxCameraViewPoint* getViewPoint();

    bool isMoving();

    virtual ~GgafDxCamera(); //デストラクタ
};

}
#endif /*GGAFDXCAMERAACTOR_H_*/
