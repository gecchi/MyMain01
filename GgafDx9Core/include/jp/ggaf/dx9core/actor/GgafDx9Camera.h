#ifndef GGAFDX9CAMERAACTOR_H_
#define GGAFDX9CAMERAACTOR_H_


namespace GgafDx9Core {

// (2009/2/12 の脳みそ)
// ２～３個 new して、１カメ、２カメみたいな切り替え操作ができたら良いかもな


/**
 * カメラアクター.
 * GgafDx9GeometricActor を継承し、カメラを表したアクターです。<BR>
 * 本クラスは神(GgafDx9God)と連動ています。メンバを操作すると、その通りにカメラの位置と注視点が操作できます。<BR>
 * processPreDraw メソッドが実装されており、その中で神(GgafDx9God)のカメラに座標情報を上書きします。<BR>
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
class GgafDx9Camera : public GgafDx9GeometricActor {
private:

public:
    D3DVIEWPORT9 _viewport;

    // 視錐台の6つの面の頂点座標
    /** 視錐台面、手前の四角形の頂点(読み込み専用、毎フレーム更新) */
    D3DXVECTOR3 _vecNear[4];
    /** 視錐台面、奥の四角形の頂点(読み込み専用、毎フレーム更新) */
    D3DXVECTOR3 _vecFar[4];

    D3DXVECTOR3 _vecVerticalCenter[4];

    // 視錐台の6つの面
    /** 視錐台面、上(読み込み専用、毎フレーム更新) */
    D3DXPLANE _plnTop;
    /** 視錐台面、下(読み込み専用、毎フレーム更新) */
    D3DXPLANE _plnBottom;
    /** 視錐台面、左(読み込み専用、毎フレーム更新) */
    D3DXPLANE _plnLeft;
    /** 視錐台面、右(読み込み専用、毎フレーム更新) */
    D3DXPLANE _plnRight;
    /** 視錐台面、手前(読み込み専用、毎フレーム更新) */
    D3DXPLANE _plnFront;
    /** 視錐台面、奥(読み込み専用、毎フレーム更新) */
    D3DXPLANE _plnBack;

    D3DXPLANE _plnVerticalCenter;

    /** 射影変換魚売れる */
    D3DXMATRIX _matProj;
    /** 正射影変換魚売れる */
    D3DXMATRIX _vMatrixOrthoProj;

    /** カメラの位置(読み込み専用、フレーム毎更新) */
    D3DXVECTOR3* _pVecCamFromPoint;
    /** カメラの注視点(読み込み専用、フレーム毎更新) */
    D3DXVECTOR3* _pVecCamLookatPoint;
    /** カメラの上ベクトル(読み込み専用、生成後不変) */
    D3DXVECTOR3* _pVecCamUp;
    /** VIEW変換行列(読み込み専用、フレーム毎更新) */
    D3DXMATRIX _matView;
    /** 視野角X(読み込み専用、生成後不変) */
    float _rad_fovX;
    /** 視野角Xの半分(読み込み専用、生成後不変) */
    float _rad_half_fovX;
    /** 視野角Y(読み込み専用、生成後不変) */
    float _rad_fovY;
    /** 視野角Yの半分(読み込み専用、生成後不変) */
    float _rad_half_fovY;
    /** カメラのZ座標(読み込み専用) */
    float _cameraZ;
    /** カメラのZ座標初期位置(読み込み専用、生成後不変) */
    float _cameraZ_org;
    /** アスペクト比(読み込み専用、生成後不変) */
    float _screen_aspect;

    float _tan_half_fovY;
    float _tan_half_fovX;
    float _dCamHarfXfovTan;

    /** カメラから近くのクリップ面までの距離(どこからの距離が表示対象か）≠0 */
    float _zn;
    /** カメラから遠くのクリップ面までの距離(どこまでの距離が表示対象か）> zn  */
    float _zf;

    float _dep;
    /** 注視点 **/
    GgafDx9CameraViewPoint* _pViewPoint;


    static int _X_ScreenLeft;
    static int _X_ScreenRight;
    static int _Y_ScreenTop;
    static int _Y_ScreenBottom;


    /**
     * コンストラクタ .
     * 視野角と表示深さを設定する。
     * 視野角によって、カメラの初期Z位置が決定する。
     * このカメラの初期Z位置は、原点付近でDirctXの長さ1（のオブジェクト）を
     * 画面上10ピクセルで表示する位置へカメラを引くように自動計算される。（_cameraZ_orgに保持)
     * この原点から、初期のカメラZ位置までを1.0として、表示範囲の深さの倍数を引数 prm_dep で設定する。
     * prm_dep=1.0とした場合。表示範囲は 原点を中心とし、半径を初期カメラZ位置の距離の球となる。
     * また、表示範囲＋αが、アクター達のゲーム内での可動範囲となるように設計しているため、カメラの初期設定値は
     * 非常に重要である。
     * 通常視野角を狭めればズームアップの効果が得られるが、本ライブラリでは、
     * 上記の初期Z位置までカメラを自動で引くため、視野角を変更してもアクターの表示の大きさは画面上変わらない。
     * ただし視野角を狭くすれば、初期のカメラを引く距離も伸びることになり、結果として
     * 表示範囲を拡大する効果をえることができる。
     * 逆に視野角が広ければ、カメラの初期Z位置は原点に近くなり、実は表示範囲は狭くなる。
     *
     * @param prm_name 名前(デバックで表示。何でもよい)
     * @param prm_rad_fovX 左右の視野角（ラジアン）
     * @param prm_dep 深さ（_cameraZ_orgの何倍か)
     * @return
     */
    GgafDx9Camera(const char* prm_name, float prm_rad_fovX, float prm_dep);

    virtual void initialize() override;

    virtual void processBehavior() override;

    virtual void processJudgement() override;

    virtual void processPreDraw() override {
    }

    virtual void processDraw() override {
    }

    virtual void processAfterDraw() override {
    }

    virtual void onCatchEvent(UINT32 prm_no, void* prm_pSource) override {
    }

    virtual void processFinal() override {
    }

    virtual void onHit(GgafCore::GgafActor* prm_pOtherActor) override {
    }


    virtual void setDefaultPosition();

    /**
     * カメラの注視点を設定 .
     * @param prm_tX 注視点X座標
     * @param prm_tY 注視点Y座標
     * @param prm_tZ 注視点Z座標
     */
    virtual void setViewPoint(int prm_tX, int prm_tY, int prm_tZ);

    /**
     * カメラの注視点を設定 .
     * 引数のアクターのXYZ座標(_X, _Y, _Z)がsetViewPointされるだけです。
     * @param prm_pActor 注視するアクター
     */
    virtual void setViewPoint(GgafDx9GeometricActor* prm_pActor);

    virtual ~GgafDx9Camera(); //デストラクタ
};

}
#endif /*GGAFDX9CAMERAACTOR_H_*/
