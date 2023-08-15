#ifndef GGAF_DX_CAMERAACTOR_H_
#define GGAF_DX_CAMERAACTOR_H_
#include "jp/ggaf/GgafDxCommonHeader.h"
#include "jp/ggaf/dx/actor/GeometricActor.h"

namespace GgafDx {

/**
 * カメラアクター.
 * カメラを表したアクターです。<BR>
 * 本クラスは管理者(Caretaker)と連動しています。メンバを操作すると、その通りにカメラの位置と注視点が操作できます。<BR>
 * processPreDraw メソッドが実装されており、その中で管理者(Caretaker)のカメラに座標情報を上書きします。<BR>
 * <BR>
 * _x,_y,_z  ・・・ カメラの位置 <BR>
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
    /** [r]視錐台上面、法線は視錐台の内から外に向いている(毎フレーム更新) */
    D3DXPLANE _plnTop;
    /** [r]視錐台下面、法線は視錐台の内から外に向いている(毎フレーム更新) */
    D3DXPLANE _plnBottom;
    /** [r]視錐台左面、法線は視錐台の内から外に向いている(毎フレーム更新) */
    D3DXPLANE _plnLeft;
    /** [r]視錐台右面、法線は視錐台の内から外に向いている(毎フレーム更新) */
    D3DXPLANE _plnRight;
    /** [r]視錐台手前面、法線は視錐台の内から外に向いている(毎フレーム更新) */
    D3DXPLANE _plnInfront;
    /** [r]視錐台奥面、法線は視錐台の内から外に向いている(毎フレーム更新) */
    D3DXPLANE _plnBack;
    /** [r]視錐台を左右に分割する垂直面、左右の効果音のパンに使用(毎フレーム更新) */
    D3DXPLANE _plnVerticalCenter;

    /** [r]カメラのビューポート情報 */
    D3DVIEWPORT9 _viewport;
    /** [r]DirectXビューポート変換行列 */
    D3DXMATRIX _matViewPort;
    /** [r]DirectXビューポート変換逆行列 */
    D3DXMATRIX _matInvViewPort;
    /** [r]DirectX射影変換行列（現在のカメラの射影変換行列） */
    D3DXMATRIX _matProj;
    /** [r]DirectX射影変換逆行列 */
    D3DXMATRIX _matInvProj;
    /** [r]DirectX正射影変換行列 */
    D3DXMATRIX _matProjOrtho;

    /** [r]DirectXカメラの位置(フレーム毎更新) */
    D3DXVECTOR3* _pVecCamFromPoint;
    /** [r]DirectXカメラの注視点(フレーム毎更新) */
    D3DXVECTOR3* _pVecCamLookatPoint;
    /** [r]DirectXカメラの上ベクトル(フレーム毎更新) */
    D3DXVECTOR3* _pVecCamUp;
    /** [r]DirectXビュー変換行列(フレーム毎更新) */
    D3DXMATRIX _matView;
    /** [r]DirectXビュー変換逆行列(フレーム毎更新) */
    D3DXMATRIX _matInvView;
    /** [r]視錐台計算用(フレーム毎更新) */
    D3DXMATRIX _matInvViewPort_Proj_View;
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
    /** [r]表示対象開始の、カメラから最近傍クリップ面まで距離(どこからの距離が表示対象か）≠0 */
    const dxcoord _zn;
    /** [r]表示対象終了の、カメラから最遠クリップ面まで距離(どこまでの距離が表示対象か）> zn */
    const dxcoord _zf;

    /** [r/w]カメラの注視点（自身からの方向が _pVecCamLookatPoint と連動） */
    CameraViewPoint* _pCameraViewPoint;
    /** [r/w]カメラの上方向（自身からの方向が _pVecCamUp と連動） */
    CameraUpVector* _pCameraUpVector;

    /** [r]一つ前の座標 */
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

    /**
     * 準備：カメラの注視点、カメラの上方向アクターの生成 .
     */
    virtual void initialize() override;

    /**
     * 視錐台面の座標情報を更新する。
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

    /**
     * カメラを初期設定に戻す .
     * カメラを初期位置設定し、視点は原点を注視し、上方向をカメラのY軸真上方向ベクトルとします。
     */
    virtual void setDefaultPosition();

    /**
     * カメラからの視点ポイントに位置するアクターを取得 .
     * 生成済みの視点用アクターを取得します。
     * 但し、初めて呼び出した場合、createCameraViewPoint() が呼び出され
     * インスタンスが作成されます。
     * @return 視点ポイントアクター
     */
    virtual CameraViewPoint* getCameraViewPoint();

    /**
     * カメラからの視点ポイントのアクターインスタンスを生成 .
     * オーバーライドしてください。
     * @return 視点ポイントアクター
     */
    virtual CameraViewPoint* createCameraViewPoint() = 0;

    /**
     * カメラの上方向ベクトルのポイントを表すアクターを取得 .
     * 生成済みのアクターを取得します。
     * 但し、初めて呼び出した場合、createCameraUpVector() が呼び出され
     * インスタンスが作成されます。
     * @return カメラの上方向ベクトルのポイントアクター
     */
    virtual CameraUpVector* getCameraUpVector();

    /**
     * カメラの上方向ベクトルのポイントのアクターインスタンスを生成 .
     * オーバーライドしてください。
     * @return 上方向ポイントアクター
     */
    virtual CameraUpVector* createCameraUpVector() = 0;

    /**
     * カメラが移動中か判定します。
     * 注意：注視点、上方向の移動中は判定に含まれません。
     * @return true:移動中（一つ前のフレームと座標が違う）／false:停止中（一つ前のフレームと座標が同じ）
     */
    bool isMoving();

    /**
     * 表示対象終了の、カメラから最遠クリップ面まで距離を取得 .
     * @return  表示対象終了の、カメラから最遠クリップ面まで距離
     */
    inline dxcoord getZFar() const {
        return _zf;
    }

    /**
     * 表示対象開始の、カメラから最近傍クリップ面まで距離を取得 .
     * @return 表示対象開始の、カメラから最近傍クリップ面まで距離
     */
    inline dxcoord getZNear() const {
        return _zn;
    }

    /**
     * カメラの影変換行列を取得 .
     * @return カメラの影変換行列
     */
    inline D3DXMATRIX* getProjectionMatrix()  {
        return &_matProj;
    }

    /**
     * カメラの影変換の逆行列を取得 .
     * @return カメラの影変換の逆行列
     */
    inline D3DXMATRIX* getInvProjectionMatrix()  {
        return &_matInvProj;
    }

    /**
     * 現在のカメラのビュー変換行列(毎フレーム更新)を取得 .
     * @return カメラのビュー変換行列
     */
    inline D3DXMATRIX* getViewMatrix() {
        return &_matView;
    }

    /**
     * カメラの位置ベクトルを取得 .
     * @return カメラの位置ベクトル
     */
    inline D3DXVECTOR3* getVecCamFromPoint() const {
        return _pVecCamFromPoint;
    }

    /**
     * カメラの注視点位置ベクトルを取得 .
     * @return カメラの注視点位置ベクトル
     */
    inline D3DXVECTOR3* getVecCamLookatPoint() const {
        return _pVecCamLookatPoint;
    }

    /**
     * カメラの上を表す地点の位置ベクトルを取得 .
     * @return カメラの上を表す地点の位置ベクトル
     */
    inline D3DXVECTOR3* getVecCamUp() const {
        return _pVecCamUp;
    }

    /**
     * カメラの初期位置のZ座標を取得 .
     * @return カメラの初期位置のZ座標を取得
     */
    inline dxcoord getZOrigin() const {
        return _cameraZ_org;
    }

    /**
     * カメラの表示の深さ（_cameraZ_orgの何倍か) を取得 .
     * @return カメラの表示の深さ
     */
    inline double getDep() {
        return _dep;
    }

    virtual ~Camera();
};

}
#endif /*GGAF_DX_CAMERAACTOR_H_*/
