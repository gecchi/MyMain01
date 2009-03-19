#ifndef GGAFDX9UNTRANSFORMEDACTOR_H_
#define GGAFDX9UNTRANSFORMEDACTOR_H_
namespace GgafDx9Core {

/**
 * 未変換座標のアクター.
 * 未変換3次元座標（ワールド/ビュー/射影変換をしていない座標）を持ち、<BR>
 * 座標変換メソッドを備えたアクターです。<BR>
 */
class GgafDx9UntransformedActor : public GgafDx9BaseActor {

private:

public:

    /** α (0.0 <= _fAlpha <= 1.0) */
    float _fAlpha;

    /** ワールドX座標 */
    int _X;
    /** ワールドY座標 */
    int _Y;
    /** ワールドZ座標 */
    int _Z;
    /** ワールドX軸回転角 */
    int _RX;
    /** ワールドY軸回転角 */
    int _RY;
    /** ワールドZ軸回転角 */
    int _RZ;
    /** ワールドX軸方向倍率 */
    int _SX;
    /** ワールドY軸方向倍率 */
    int _SY;
    /** ワールドZ軸方向倍率 */
    int _SZ;

    //補足
    //【_X, _Y, _Z の単位について】
    //　採り得る値は DirectXワールド座標(float)の 1000倍の整数値である。
    //　描画の直前に 1000 で除算されワールド変換に使用される。
    //　なんでかというと整数で座標計算して少しでも速くしたかったため。
    //　昔は良く使った手法だが、floatでも早いので、よかったのかどうか微妙。
    //【_RX, _RY, _RZ の単位について】
    //　独自単位の「アングル値」を採る。「アングル値」とは 0~360000 の値で、1000倍の精度の角度値である。
    //　円周角と同じく3時の方向を0とし、反時計回りにアングル値は増えるものとする。直角の値は90000、水平は180000である。
    //【_SX, _SY, _SZ の単位について】
    //　描画の直前に 1000 で除算され、拡大縮小の変換に使用される。
    //　1000が１倍のスケール意味する。したがってデフォルトは1000になっている。


    GgafDx9GeometryMover* _pGeoMover;

    GgafDx9GeometryChecker* _pGeoChecker;

    const int _X_OffScreenLeft;
    const int _X_OffScreenRight;
    const int _Y_OffScreenTop;
    const int _Y_OffScreenBottom;

    /**
     * コンストラクタ<BR>
     * @param	prm_name 識別名
     */
    GgafDx9UntransformedActor(const char* prm_name,
                              GgafDx9GeometryMover* prm_pGeoMover,
                              GgafDx9GeometryChecker* prm_pGeoChecker);

    virtual GgafDx9UntransformedActor* getPrev() {
        return (GgafDx9UntransformedActor*)GgafActor::getPrev();
    }

    virtual GgafDx9UntransformedActor* getNext() {
        return (GgafDx9UntransformedActor*)GgafActor::getNext();
    }

    virtual bool processBumpChkLogic(GgafActor* prm_pActor_Opponent);

    virtual bool isOffScreen() {
        return false;
    }

    virtual void setGeometry(int X, int Y, int Z) {
        _X = X;
        _Y = Y;
        _Z = Z;
    }

    virtual void setGeometry(GgafDx9UntransformedActor* prm_pActor) {
        _X = prm_pActor->_X;
        _Y = prm_pActor->_Y;
        _Z = prm_pActor->_Z;
    }

    /**
     * _Zの値により、大まかにレンダリング順序を設定する。
     * 任意の優先順位でレンダリングしたい場合は、このメソッドをオーバーライドし
     * GgafWorld::_apAlphaActorList_DrawDepthLevel[n] の好きな n に addSubLast(this) を行って下さい。
     * 但し 0 ≦ n ＜ MAX_DRAW_DEPTH_LEVEL
     */
    virtual void processDrawPrior();

    virtual void setAlpha(float prm_fAlpha) {
        _fAlpha = prm_fAlpha;
    }

    virtual float getAlpha() {
        return _fAlpha;
    }

    /**
     * world変換行列取得 .
     * 単位行列 × X軸回転 × Z軸回転 × Y軸回転 × 拡大縮小 × 平行移動　の変換行列を作成＆デバイスに設定<BR>
     * ※XYZの順でないことに注意<BR>
     * @param prm_pActor [in]対象アクター
     * @param out_matWorld [out]world変換行列
     */
    static void getWorldTransformRxRzRyScMv(GgafDx9UntransformedActor* prm_pActor, D3DXMATRIX& out_matWorld);

    /**
     * world変換 .
     * 単位行列 × Z軸回転 × 平行移動　の変換行列を作成＆デバイスに設定 .<BR>
     * @param prm_pActor 対象アクター
     */
    static void getWorldTransformRzMv(GgafDx9UntransformedActor* prm_pActor, D3DXMATRIX& out_matWorld);

    /**
     * world変換 .
     * 単位行列 × 拡大縮小 × Z軸回転 × 平行移動　の変換行列を作成＆デバイスに設定 <BR>
     * @param prm_pActor 対象アクター
     */
    static void getWorldTransformScRzMv(GgafDx9UntransformedActor* prm_pActor, D3DXMATRIX& out_matWorld);

    virtual ~GgafDx9UntransformedActor(); //デストラクタ
};

}
#endif /*GGAFDX9UNTRANSFORMEDACTOR_H_*/
