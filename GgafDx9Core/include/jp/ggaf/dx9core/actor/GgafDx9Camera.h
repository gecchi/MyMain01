#ifndef GGAFDX9CAMERAACTOR_H_
#define GGAFDX9CAMERAACTOR_H_
namespace GgafDx9Core {

// (2009/2/12 の脳みそ)
// ２～３個 new して、１カメ、２カメみたいな切り替え操作ができたら良いかもな


/**
 * カメラアクター.
 * GgafDx9GeometricActor を継承し、カメラを表したアクターです。<BR>
 * 本クラスは神(GgafDx9God)と連動ています。メンバを操作すると、その通りにカメラの位置と注視点が操作できます。<BR>
 * processDrawPrior メソッドが実装されており、その中で神(GgafDx9God)のカメラに座標情報を上書きします。<BR>
 * <BR>
 * _X,_Y,_Z             ・・・ カメラの位置 <BR>
 * _gazeX,_gazeY,_gazeZ ・・・ カメラが注視する座標 <BR>
 * <BR>
 * ＜使い方＞<BR>
 * 継承し、processBehavior() 等を オーバーライドして好きに座標を動かすだけで良い<BR>
 * <BR>
 */
class GgafDx9Camera : public GgafDx9GeometricActor {
private:

public:



    // 視錐台の6つの面の頂点座標
    /** 視錐台面、手前の四角形の頂点(読み込み専用、毎フレーム更新) */
    D3DXVECTOR3 _vecNear[4];
    /** 視錐台面、奥の四角形の頂点(読み込み専用、毎フレーム更新) */
    D3DXVECTOR3 _vecFar[4];

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







    /** 座標移動支援オブジェクト */
    GgafDx9Core::GgafDx9GeometryMover* _pMover;


    /** 射影変換魚売れる */
    D3DXMATRIX _vMatrixProj;
    /** 正射影変換魚売れる */
    D3DXMATRIX _vMatrixOrthoProj;

    /** カメラの位置(読み込み専用、フレーム毎更新) */
    D3DXVECTOR3* _pVecCamFromPoint;
    /** カメラの注視点(読み込み専用、フレーム毎更新) */
    D3DXVECTOR3* _pVecCamLookatPoint;
    /** カメラの上ベクトル(読み込み専用、生成後不変) */
    D3DXVECTOR3* _pVecCamUp;
    /** VIEW変換行列(読み込み専用、フレーム毎更新) */
    D3DXMATRIX _vMatrixView;
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

//    /** XY平面座標の視点から注視点を結ぶ直線の傾き */
//    float _view_slant_XZ;
//    /** XY平面座標の視点から注視点を結ぶ直線の傾き */
//    float _view_slant_ZY;

//    float _view_rad_XZ;
//    float _view_rad_ZY;

//    float _view_border_rad1_XZ;
//    float _view_border_rad2_XZ;
//    float _view_border_rad1_ZY;
//    float _view_border_rad2_ZY;

//    float _view_border_slant1_XZ;
//    float _view_border_slant2_XZ;
//    float _view_border_slant1_ZY;
//    float _view_border_slant2_ZY;
    //切片
//    int _view_border_intercept1_XZ;
//    int _view_border_intercept2_XZ;
//    int _view_border_intercept1_ZY;
//    int _view_border_intercept2_ZY;

    /** 注視点（読み書き可) */
    int _gazeX, _gazeY, _gazeZ;

    /**
     * コンストラクタ
     * @param prm_name 名前(デバックで表示。何でもよい)
     * @param prm_rad_fovX 左右の視野角（ラジアン）
     * @return
     */
    GgafDx9Camera(const char* prm_name, float prm_rad_fovX);

    virtual void initialize();

    virtual void processBehavior();

    virtual void processJudgement();

    virtual void processDrawPrior() {
    }

    virtual void processDrawMain() {
    }

    virtual void processDrawTerminate() {
    }

    virtual void processHappen(int prm_no) {
    }

    virtual void processFinal() {
    }

    virtual void processOnHit(GgafCore::GgafActor* prm_pActor_Opponent) {
    }

//    virtual int canView(GgafDx9GeometricActor* pActor) {
//        return canView(pActor, pActor->_max_radius);
//    }
//
//
//    virtual int canView(GgafDx9GeometricActor* pActor, FLOAT radius);


//    virtual bool isInTheViewports_old(int prm_X, int prm_Y, int prm_Z);
//
//    virtual bool isInTheViewports_old(GgafDx9GeometricActor* prm_pActor) {
//        return isInTheViewports_old(prm_pActor->_X, prm_pActor->_Y, prm_pActor->_Z);
//    }

    /**
     * カメラの注視点を設定 .
     * @param prm_tX 注視点X座標
     * @param prm_tY 注視点Y座標
     * @param prm_tZ 注視点Z座標
     */
    void setGaze(int prm_tX, int prm_tY, int prm_tZ) {
        _gazeX = prm_tX;
        _gazeY = prm_tY;
        _gazeZ = prm_tZ;
    }

    /**
     * カメラの注視点を設定 .
     * 引数のアクターのXYZ座標(_X, _Y, _Z)がsetGazeされるだけです。
     * @param prm_pActor 注視するアクター
     */
    void setGaze(GgafDx9GeometricActor* prm_pActor) {
        _gazeX = prm_pActor->_X;
        _gazeY = prm_pActor->_Y;
        _gazeZ = prm_pActor->_Z;
    }

    virtual ~GgafDx9Camera(); //デストラクタ
};

}
#endif /*GGAFDX9CAMERAACTOR_H_*/
