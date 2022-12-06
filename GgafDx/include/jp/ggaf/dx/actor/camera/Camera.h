#ifndef GGAF_DX_CAMERAACTOR_H_
#define GGAF_DX_CAMERAACTOR_H_
#include "GgafDxCommonHeader.h"
#include "jp/ggaf/dx/actor/GeometricActor.h"

namespace GgafDx {

/**
 * カメラアクター.
 * カメラを表したアクターです。<BR>
 * 本クラスは管理者(Caretaker)と連動しています。メンバを操作すると、その通りにカメラの位置と注視点が操作できます。<BR>
 * processPreDraw メソッドが実装されており、その中で管理者(Caretaker)のカメラに座標情報を上書きします。<BR>
 * <BR>
 * _x,_y,_z             ・・・ カメラの位置 <BR>
 * <BR>
 * ＜使い方＞<BR>
 * 継承し、processBehavior() 等を オーバーライドして好きに座標を動かすがよい<BR>
 * <BR>
 * @version 1.00
 * @since 2009/02/12
 * @author Masatoshi Tsuge
 */
class Camera : public GeometricActor {
    friend Caretaker;
    friend Util;
    friend GeometricActor;
    friend SeTransmitterForActor;

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
    D3DXPLANE _plnInfront;
    /** [r]視錐台面、奥(読み込み専用、毎フレーム更新) */
    D3DXPLANE _plnBack;
    /** [r]視錐台を左右に分割する垂直面、左右の効果音のパンに使用(読み込み専用、毎フレーム更新) */
    D3DXPLANE _plnVerticalCenter;

    /** [r]DirectX射影変換行列（現在のカメラの射影変換行列） */
    D3DXMATRIX _matProj;
    /** [r]DirectX正射影変換行列 */
    D3DXMATRIX _matOrthoProj;

    /** [r]DirectXカメラの位置(フレーム毎更新) */
    D3DXVECTOR3* _pVecCamFromPoint;
    /** [r]DirectXカメラの注視点(フレーム毎更新) */
    D3DXVECTOR3* _pVecCamLookatPoint;
    /** [r]DirectXカメラの上ベクトル(フレーム毎更新) */
    D3DXVECTOR3* _pVecCamUp;
    /** [r]DirectXVIEW変換行列(フレーム毎更新) */
    D3DXMATRIX _matView;

    /** [r]視野角Xラジアン */
    const double _rad_fovX;
    /** [r]深さ（_cameraZ_orgの何倍か)  */
    const double _dep;
    /** [r]視野角Xラジアンの半分 */
    const double _rad_half_fovX;
    /** [r]アスペクト比 */
    const double _screen_aspect;
    /** [r]視野角Yラジアン */
    const double _rad_fovY;
    /** [r]視野角Yラジアンの半分 */
    const double _rad_half_fovY;
    /** [r]視野角Xタンジェントの半分 */
    const double _tan_half_fovX;
    /** [r]視野角Yタンジェントの半分 */
    const double _tan_half_fovY;
    /** [r]カメラのZ座標初期位置 */
    const dxcoord _cameraZ_org;
    /** [r]カメラから近くのクリップ面までの距離(どこからの距離が表示対象か）≠0 */
    const dxcoord _zn;
    /** [r]カメラから遠くのクリップ面までの距離(どこまでの距離が表示対象か）> zn */
    const dxcoord _zf;
    const coord _x_buffer_left;
    const coord _x_buffer_right;
    const coord _y_buffer_top;
    const coord _y_buffer_bottom;

    /** [r/w]注視点（座標が _pVecCamLookatPoint と連動） **/
    CameraViewPoint* _pCameraViewPoint;
    CameraUpVector* _pCameraUpVector;

    coord _x_prev, _y_prev, _z_prev;

public:
    /**
     * コンストラクタ .
     * 視野角と表示深さを設定する。
     * 視野角によって、カメラの初期Z位置が決定する。
     * このカメラの初期Z位置は、原点付近でDirectXの長さ1（のオブジェクト）を
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
    Camera(const char* prm_name, double prm_rad_fovX, double prm_dep);

    virtual void initialize() override;

    /**
     * 視錐台面情報を更新する。
     */
    virtual void processBehavior() override;

    /**
     * DirectXのカメラへ反映 .
     * 自身の座標を _pVecCamFromPoint へコピー
     * _pCameraViewPoint の座標を _pVecCamLookatPoint へコピー。
     * _pCameraUpVector の位置ベクトルを _pVecCamUp ヘコピー。
     * _pVecCamFromPoint, _pVecCamLookatPoint, _pVecCamUp で
     * D3DXMatrixLookAtLH() を実行。
     */
    virtual void processSettlementBehavior() override;


    virtual void setDefaultPosition();

    /**
     * 視点用アクターを取得 .
     * 生成済みの視点用アクターを取得します。
     * 但し、初めて呼び出した場合、createCameraViewPoint() が呼び出され
     * インスタンスが作成されます。
     * @return 生成済み視点用アクター
     */
    virtual CameraViewPoint* getCameraViewPoint();

    /**
     * 視点用アクターのインスタンスを生成 .
     * 独自のインスタンスを生成したい場合は、オーバーライドしてください。
     * @return 生成された視点用アクター
     */
    virtual CameraViewPoint* createCameraViewPoint() = 0;

    virtual CameraUpVector* getCameraUpVector();

    virtual CameraUpVector* createCameraUpVector() = 0;

    bool isMoving();

    inline dxcoord getZFar() const {
        return _zf;
    }

    inline dxcoord getZNear() const {
        return _zn;
    }

    inline D3DXMATRIX* getProjectionMatrix()  {
        return &_matProj;
    }

    inline D3DXMATRIX* getViewMatrix() {
        return &_matView;
    }

    inline D3DXVECTOR3* getVecCamFromPoint() const {
        return _pVecCamFromPoint;
    }

    inline D3DXVECTOR3* getVecCamLookatPoint() const {
        return _pVecCamLookatPoint;
    }

    inline dxcoord getZOrigin() const {
        return _cameraZ_org;
    }
    inline double getDep() {
        return _dep;
    }
    virtual ~Camera(); //デストラクタ
};

}
#endif /*GGAF_DX_CAMERAACTOR_H_*/
