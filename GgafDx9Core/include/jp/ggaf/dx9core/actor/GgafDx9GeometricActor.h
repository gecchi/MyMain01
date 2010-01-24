#ifndef GGAFDX9GEOMETRICACTOR_H_
#define GGAFDX9GEOMETRICACTOR_H_
namespace GgafDx9Core {

/**
 * 座標を持ったのアクター.
 * ワールド座標、或いは変換済み座標の何れかを持ち、<BR>
 * 座標関連メソッドを備えたアクターです。<BR>
 * (旧GgafDx9UntranceformedActor とGgafDx9TranceformedActor を統合)
 * @version 1.00
 * @since 2008/09/08
 * @author Masatoshi Tsuge
 */
class GgafDx9GeometricActor : public GgafDx9BaseActor {

private:

public:

    /** 変換済み座標であるか(true:本アクターは変換済み座標/false:本アクターはワールド座標) */
    bool _isTransformed;

    /** ワールドX座標 */
    int _X;
    /** ワールドY座標 */
    int _Y;
    /** ワールドZ座標 */
    int _Z;
    /** ワールドX軸回転角 */
    angle _RX;
    /** ワールドY軸回転角 */
    angle _RY;
    /** ワールドZ軸回転角 */
    angle _RZ;
    /** ワールドX軸方向倍率 */
    int _SX;
    /** ワールドY軸方向倍率 */
    int _SY;
    /** ワールドZ軸方向倍率 */
    int _SZ;

    /** このオブジェクトのローカル座標の原点から全頂点の距離で最大の長さ */
    FLOAT _max_radius;

    /** directXのワールドX座標 */
    FLOAT _fX;
    /** directYのワールドY座標 */
    FLOAT _fY;
    /** directZのワールドZ座標 */
    FLOAT _fZ;
    /** 視野外の自身の座標から視錐台上面までの距離、視野内の距離は負の値になる */
    FLOAT _fDistance_plnTop;
    /** 視野外の自身の座標から視錐台下面までの距離、視野内の距離は負の値になる */
    FLOAT _fDistance_plnBottom;
    /** 視野外の自身の座標から視錐台左面までの距離、視野内の距離は負の値になる */
    FLOAT _fDistance_plnLeft;
    /** 視野外の自身の座標から視錐台右面までの距離、視野内の距離は負の値になる */
    FLOAT _fDistance_plnRight;
    /** 視野外の自身の座標から視錐台手前面までの距離、視野内の距離は負の値になる */
    FLOAT _fDistance_plnFront;
    /** 視野外の自身の座標から視錐台奥面までの距離、視野内の距離は負の値になる */
    FLOAT _fDistance_plnBack;

    int _offscreenkind;
    bool _delete_pChecker;



    //TODO:起源アクターと起源アクターからのオフセット受け皿
    GgafDx9GeometricActor* _pActorOrigin;
    velo _offset_origin_veloMove;
    int _offset_origin_X;
    int _offset_origin_Y;
    int _offset_origin_Z;
    angle _offset_origin_angRxMove;
    angle _offset_origin_angRyMove;
    angle _offset_origin_angFace[3];


    /** 自身の現在のWorld変換行列 */
    D3DXMATRIX _matWorld;

    /** 移動用座標計算支援オブジェクト */
    GgafDx9GeometryMover* _pMover;

    //補足
    //【_X, _Y, _Z の単位について】
    //　採り得る値は DirectXワールド座標(float)の 1000倍の整数値である。
    //　描画の直前に 1000 で除算されワールド変換に使用される。
    //　なんでかというと整数で座標計算して少しでも速くしたかったため。
    //　昔は良く使った手法だが、floatでも早いので、よかったのかどうか微妙。
    //【_RX, _RY, _RZ の単位について】
    //　独自単位の「アングル値」を採る。「アングル値」とは 0~360000 の値で、1000倍の精度の角度値である。
    //　中心角と同じく3時の方向を0とし、反時計回りにアングル値は増えるものとする。直角の値は90000、水平は180000である。
    //【_SX, _SY, _SZ の単位について】
    //　描画の直前に 1000 で除算され、拡大縮小の変換に使用される。
    //　1000が１倍のスケール意味する。したがってデフォルトは1000になっている。


    /** 変換済みオブジェクトの場合のX座標(-1.0 <= _x < 1.0) */
    float _x;
    /** 変換済みオブジェクトの場合のY座標(-1.0 <= _y < 1.0) */
    float _y;
    /** 変換済みオブジェクトの場合の深度 (0.0 <= _z < 1.0) */
    float _z;
    /** チェッカーオブジェクト */
    GgafDx9Checker* _pChecker;

    /**
     *
     * @param prm_name アクター名
     * @param prm_pChecker チェッカー(未使用時NULL)
     * @return
     */
    GgafDx9GeometricActor(const char* prm_name,
                              GgafDx9Checker* prm_pChecker);

    virtual GgafDx9GeometricActor* getPrev() override {
        return (GgafDx9GeometricActor*)GgafActor::getPrev();
    }

    virtual GgafDx9GeometricActor* getNext() override {
        return (GgafDx9GeometricActor*)GgafActor::getNext();
    }

    virtual bool processHitChkLogic(GgafActor* prm_pOtherActor) override;

    /** いろいろな計算を行っておく */
    virtual void processPreJudgement() override;

    /**
     * 画面内に表示されているか判定
     * @return 0:Viewport範囲内
     */
    virtual int isOffscreen();

    virtual int isOutOfGameSpace();

    virtual void setGeometry(int X, int Y, int Z) {
        _X = X;
        _Y = Y;
        _Z = Z;
    }

    virtual void setGeometry(GgafDx9GeometricActor* prm_pActor) {
        _X = prm_pActor->_X;
        _Y = prm_pActor->_Y;
        _Z = prm_pActor->_Z;
    }

    /**
     * world変換行列設定 .
     * 拡大縮小 × X軸回転 × Z軸回転 × Y軸回転 × 平行移動 の変換行列を設定<BR>
     * ※XYZの順でないことに注意<BR>
     * @param prm_pActor [in]対象アクター
     * @param out_matWorld [out]world変換行列
     */
    static void getWorldMatrix_ScRxRzRyMv(GgafDx9GeometricActor* prm_pActor, D3DXMATRIX& out_matWorld);


    static void getWorldMatrix_ScRzRyMv(GgafDx9GeometricActor* prm_pActor, D3DXMATRIX& out_matWorld);

    /**
     * world変換行列設定 .
     * X軸回転 × Z軸回転 × Y軸回転 × 拡大縮小 × 平行移動 の変換行列を設定<BR>
     * ※XYZの順でないことに注意<BR>
     * @param prm_pActor [in]対象アクター
     * @param out_matWorld [out]world変換行列
     */
    static void getWorldMatrix_RxRzRyScMv(GgafDx9GeometricActor* prm_pActor, D3DXMATRIX& out_matWorld);

    /**
     * world変換行列設定 .
     * X軸回転 × Y軸回転 × Z軸回転 × 拡大縮小 × 平行移動 の変換行列を設定<BR>
     * @param prm_pActor [in]対象アクター
     * @param out_matWorld [out]world変換行列
     */
    static void getWorldMatrix_RxRyRzScMv(GgafDx9GeometricActor* prm_pActor, D3DXMATRIX& out_matWorld);

    /**
     * world変換行列設定 .
     * X軸回転 × Y軸回転 × X軸回転 × 拡大縮小 × 平行移動 の変換行列を設定<BR>
     * ※Y軸回転がありません。_RYが２回目のX軸回転となる<BR>
     * @param prm_pActor [in]対象アクター
     * @param out_matWorld [out]world変換行列
     */
    static void getWorldMatrix_RxRzRxScMv(GgafDx9GeometricActor* prm_pActor, D3DXMATRIX& out_matWorld);


    static void updateWorldMatrix_Mv(GgafDx9GeometricActor* prm_pActor, D3DXMATRIX& out_matWorld);

    /**
     * world変換行列設定 .
     * 単位行列 × Z軸回転 × 平行移動 の変換行列を設定<BR>
     * @param prm_pActor [in]対象アクター
     * @param out_matWorld [out]world変換行列
     */
    static void getWorldMatrix_RzMv(GgafDx9GeometricActor* prm_pActor, D3DXMATRIX& out_matWorld);

    /**
     * world変換行列設定 .
     * 単位行列 × 拡大縮小 × Z軸回転 × 平行移動 の変換行列を設定<BR>
     * @param prm_pActor [in]対象アクター
     * @param out_matWorld [out]world変換行列
     */
    static void getWorldMatrix_ScRzMv(GgafDx9GeometricActor* prm_pActor, D3DXMATRIX& out_matWorld);

    /**
     * world変換行列設定 .
     * ビルボードX軸回転 × ビルボードY軸回転 × ビルボードZ軸回転  × 拡大縮小 × 平行移動　の変換行列を作成＆デバイスに設定 <BR>
     * @param prm_pActor [in]対象アクター
     * @param out_matWorld [out]world変換行列
     */
    static void getWorldMatrix_BillBoardXYZ_ScMv(GgafDx9GeometricActor* prm_pActor, D3DXMATRIX& out_matWorld);

    static void getWorldMatrix_BillBoardX_RzRyScMv(GgafDx9GeometricActor* prm_pActor, D3DXMATRIX& out_matWorld);
    static void getWorldMatrix_BillBoardX_RyRzScMv(GgafDx9GeometricActor* prm_pActor, D3DXMATRIX& out_matWorld);

    static void getWorldMatrix_BillBoardXYZ_RzScMv(GgafDx9GeometricActor* prm_pActor, D3DXMATRIX& out_matWorld);

    static void getWorldMatrix_ScMvRxRzRy(GgafDx9GeometricActor* prm_pActor, D3DXMATRIX& out_matWorld);


    static int sign(float x) {
        if (x < 0) {
            return -1;
        } else if (x > 0) {
            return 1;
        } else {
            return 0;
        }

    }

    virtual ~GgafDx9GeometricActor(); //デストラクタ

    /**
     * デバッグ用：ツリー構造を表示<BR>
     */
    virtual void dump();

    /**
     * デバッグ用：dump()から使用される<BR>
     */
    virtual void dump(std::string prm_parent);

};

}
#endif /*GGAFDX9GEOMETRICACTOR_H_*/
