#ifndef GGAFDX9CAMERAACTOR_H_
#define GGAFDX9CAMERAACTOR_H_
namespace GgafDx9Core {

// (2009/2/12 の脳みそ)
// ２～３個 new して、１カメ、２カメみたいな切り替え操作ができたら良いかもな


/**
 * カメラアクター.
 * GgafDx9UntransformedActor を継承し、カメラを表したアクターです。<BR>
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
class GgafDx9Camera : public GgafDx9UntransformedActor {
private:

public:
    /** 射影変換魚売れる */
    D3DXMATRIX _vMatrixProj;
    /** 正射影変換魚売れる */
    D3DXMATRIX _vMatrixOrthoProj;

    /** カメラの位置 */
    D3DXVECTOR3* _pVecCamFromPoint;
    /** カメラの注視点 */
    D3DXVECTOR3* _pVecCamLookatPoint;
    /** カメラの上ベクトル */
    D3DXVECTOR3* _pVecCamUp;
    /** VIEW変換行列 */
    D3DXMATRIX _vMatrixView;




    /** カメラのZ座標初期位置 */
    double _cameraZ_org;

    /** カメラのZ座標 */
    double _cameraZ;


    double _rad_fovY;
    double _rad_fovX;

    double _tan_half_fovY;
    double _tan_half_fovX;
    double _dCamHarfXfovTan;
    double _screen_aspect;
    double _border1_XZ;
    double _border2_XZ;



    //int _iPxDep = 0;

    /** 注視点 */
    int _gazeX, _gazeY, _gazeZ;

    GgafDx9Camera(const char* prm_name);

    virtual void initialize();

    virtual void processBehavior();

    virtual void processJudgement() {
    }

    /**
     * カメラの更新
     */
    virtual void processDrawPrior();

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

    void setGaze(int prm_tX, int prm_tY, int prm_tZ) {
        _gazeX = prm_tX;
        _gazeY = prm_tY;
        _gazeZ = prm_tZ;
    }

    void setGaze(GgafDx9UntransformedActor* prm_pActor) {
        _gazeX = prm_pActor->_X;
        _gazeY = prm_pActor->_Y;
        _gazeZ = prm_pActor->_Z;
    }

    virtual ~GgafDx9Camera(); //デストラクタ
};

}
#endif /*GGAFDX9CAMERAACTOR_H_*/
