#ifndef GGAFDX9GEOMETRICACTOR_H_
#define GGAFDX9GEOMETRICACTOR_H_

namespace GgafDx9Core {

/**
 * 座標情報を持ったアクター.
 * ワールド座標、或いは変換済み座標の何れかを持ち、<BR>
 * 座標関連メソッドを備えたアクターです。<BR>
 * (旧GgafDx9UntranceformedActor とGgafDx9TranceformedActor を統合)
 * @version 1.00
 * @since 2008/09/08
 * @author Masatoshi Tsuge
 */
class GgafDx9GeometricActor : public GgafDx9BaseActor {

private:
    /** 画面外種別。isOutOfView()が内部で使用。未計算時は -1 */
    int _offscreenkind;

public:
    /** [r] 変換済み座標であるか(true:本アクターは変換済み座標/false:本アクターはワールド座標) */
    bool _isTransformed;
    /** [r/w]ワールドX座標( _X : DirectXのX座標 : 初期カメラ位置での画面上ピクセル = 1000 : 0.1 : 1px  ) */
    int _X;
    /** [r/w]ワールドY座標( _Y : DirectXのX座標 : 初期カメラ位置での画面上ピクセル = 1000 : 0.1 : 1px  ) */
    int _Y;
    /** [r/w]ワールドZ座標( _Z : DirectXのX座標 : 初期カメラ位置での画面上ピクセル = 1000 : 0.1 : 1px  ) */
    int _Z;
    /** [r/w]ワールドX軸回転角(_RX : Degree = 1000 : 1度) */
    angle _RX;
    /** [r/w]ワールドY軸回転角(_RY : Degree = 1000 : 1度) */
    angle _RY;
    /** [r/w]ワールドZ軸回転角(_RZ : Degree = 1000 : 1度) */
    angle _RZ;
    /** [r/w]ワールドX軸方向スケール(_SX : 倍率 = 1000 : 1.0倍) */
    int _SX;
    /** [r/w]ワールドY軸方向スケール(_SY : 倍率 = 1000 : 1.0倍) */
    int _SY;
    /** [r/w]ワールドZ軸方向スケール(_SZ : 倍率 = 1000 : 1.0倍) */
    int _SZ;
    /** [r]ワールド座標計算支援オブジェクト */
    GgafDx9GeometryMover* _pMover;
    /** [r]チェッカーオブジェクト */
    GgafDx9Checker* _pChecker;
    /** [r]効果音発生管理オブジェクト */
    GgafDx9SeTransmitter* _pSeTransmitter;

    /** [r/w]境界球の半径(DirectXの単位)。画面外判定に使用される */
    FLOAT _fBoundingSphereRadius;
    /** [r]DirectXのワールドX座標(_fX : _X = 0.1 : 1000) */
    FLOAT _fX;
    /** [r]DirectYのワールドY座標(_fY : _Y = 0.1 : 1000) */
    FLOAT _fY;
    /** [r]DirectZのワールドZ座標(_fZ : _Z = 0.1 : 1000) */
    FLOAT _fZ;
    /** [r]視錐台上面から視野外に向かっての自身の座標までのDirectXの距離、視野内の距離は負の値になる */
    FLOAT _fDist_VpPlnTop;
    /** [r]視錐台下面から視野外に向かっての自身の座標までのDirectXの距離、視野内の距離は負の値になる */
    FLOAT _fDist_VpPlnBottom;
    /** [r]視錐台左面から視野外に向かっての自身の座標までのDirectXの距離、視野内の距離は負の値になる */
    FLOAT _fDist_VpPlnLeft;
    /** [r]視錐台右面から視野外に向かっての自身の座標までのDirectXの距離、視野内の距離は負の値になる */
    FLOAT _fDist_VpPlnRight;
    /** [r]視錐台手前面から視野外に向かっての自身の座標までのDirectXの距離、視野内の距離は負の値になる */
    FLOAT _fDist_VpPlnFront;
    /** [r]視錐台奥面から視野外に向かっての自身の座標までのDirectXの距離、視野内の距離は負の値になる */
    FLOAT _fDist_VpPlnBack;
    /** [r/w]WORLD変換行列計算関数(通常は回転×移動のみ) */
    void (*_pFunc_calcRotMvWorldMatrix)(GgafDx9GeometricActor*, D3DXMATRIX&);


    /** [r]自身の現在のWorld変換行列(通常は拡大縮小×回転×移動) */
    D3DXMATRIX _matWorld;
    /** [r]自身の現在のWorld変換行列(回転×移動のみ) */
    D3DXMATRIX _matWorldRotMv;
    /** [r]自身の現在のWorld変換行列の逆行列(回転×移動のインバース) */
    D3DXMATRIX _matInvWorldRotMv;
    /** [r]カレントフレームで自身の現在のWorld変換行列の逆行列(_matInvWorldRotMv)を計算して求めたかどうかのフラグ。 */
    bool _wasCalc_matInvWorldRotMv;

    /** 土台となるアクター */
    GgafDx9Core::GgafDx9GeometricActor* _pActor_Base;
    int _X_local;
    int _Y_local;
    int _Z_local;
    angle _RX_local;
    angle _RY_local;
    angle _RZ_local;
    int _X_final;
    int _Y_final;
    int _Z_final;
    angle _RX_final;
    angle _RY_final;
    angle _RZ_final;

    int _X_offset;
    int _Y_offset;
    int _Z_offset;
    angle _RX_offset;
    angle _RY_offset;
    angle _RZ_offset;


    bool _is_local;

    /** [r/w]変換済みの場合のX座標(-1.0 <= _x < 1.0) */
    float _x;
    /** [r/w]変換済みの場合のY座標(-1.0 <= _y < 1.0) */
    float _y;
    /** [r/w]変換済みの場合の深度 (0.0 <= _z < 1.0) */
    float _z;

    //補足
    //【_X, _Y, _Z の単位について】
    //　座標値は DirectX座標(float)系の値の LEN_UNIT(=1000)倍のPX_UNIT(=10)倍の整数値である。つまり10000倍。
    //　DirectX座標単位の1は、ゲーム画面上で10px相当の大きさになる（ようにカメラを引いている）。
    //　例えば、_X = 5000 は、画面では5pxの幅に見え、DirectX座標では0.5になる（ように設計）。
    //　_X,_Y,_Z をピクセルで考えたい場合は、LEN_UNIT(=1000)で割る。
    //　DirectX座標単位をピクセルで考えたい場合は、PX_UNIT(=10)を掛け算する。
    //　描画の直前に_X,_Y,_Z は (LEN_UNIT*PX_UNIT) で除算されワールド変換に使用される。
    //　なぜこんなややこしいことをするかというと、座標計算や比較を整数で行い、少しでも速くしたかった。
    //　昔は良く使っていた手法（DEFINT A-Z とか）で、当時はその効果は確かにあった。
    //　しかし、現在では float や double でもかなり速いので、本当にこの設計で良かったのかどうか微妙かもしれない。
    //【_RX, _RY, _RZ の単位について】
    //　独自単位の「アングル値」を採る。「アングル値」とは 0~3600000 の値で、1000倍の精度の角度値である。
    //　1度は1000、0.5度は500。直角の値は90000、水平は180000である。
    //　中心角と同じく3時の方向を0とし、反時計回りにアングル値は増えるものとする。
    //【_SX, _SY, _SZ の単位について】
    //　1000が１倍のスケール意味する。したがってデフォルトは1000になっている。
    //　描画の直前に 1000 で除算され、拡大縮小の変換に使用される。


public:
    /**
     * コンストラクタ .
     * @param prm_name アクター名
     * @param prm_pChecker チェッカー(使用しない時 NULL)
     * @return
     */
    GgafDx9GeometricActor(const char* prm_name,
                          GgafDx9Checker* prm_pChecker);

    /**
     * 次のアクターを取得
     * @return 次のアクター
     */
    virtual GgafDx9GeometricActor* getPrev() override {
        return (GgafDx9GeometricActor*)GgafActor::getPrev();
    }

    /**
     * 前のアクターを取得
     * @return 前のアクター
     */
    virtual GgafDx9GeometricActor* getNext() override {
        return (GgafDx9GeometricActor*)GgafActor::getNext();
    }

    /**
     * 判定処理事前処理 .
     * processBehavior() 後、座標計算事後処理として次の処理を行う <BR>
     * ①自身の座標情報から以下のメンバの更新を行う。 <BR>
     *     _fX <BR>
     *     _fY <BR>
     *     _fZ <BR>
     *     _fDist_VpPlnTop <BR>
     *     _fDist_VpPlnBottom <BR>
     *     _fDist_VpPlnLeft <BR>
     *     _fDist_VpPlnRight <BR>
     *     _fDist_VpPlnFront <BR>
     *     _fDist_VpPlnBack <BR>
     * ② 自身の座標情報からワールド変換行列を作成し_matWorldに保持
     * ③ processJudgement() を呼び出すのため準備処理として、 <BR>
     *    自身の座標情報から線形８分木配列への登録を行う。 <BR>
     *
     * 本メソッドはオーバーライド可能とするが、フレームワークの描画や判定に関わる
     * 重要な事前処理のため、オーバーライドは推奨できない。<BR>
     * どうしてもオーバーライドが必要な場合は、オーバーライド先で、 <BR>
     * GgafDx9GeometricActor::processSettlementBehavior() を呼び出すか、 <BR>
     * 上記①②③と同等の処理を行うようにすべきである。 <BR>
     */
    virtual void processSettlementBehavior() override;

    /**
     * 当たり判定ロジック .
     * 当たり判定ロジックを実装している。<BR>
     * チェッカーオブジェクトがある場合、<BR>
     * GgafDx9Checker::isHit() で判定する。<BR>
     * チェッカーオブジェクトが無い場合、<BR>
     * ヒットしていないこととする。<BR>
     * @param prm_pOtherActor 相手のアクター
     * @return true：ヒットしている／false：ヒットしていない
     */
    virtual bool processHitChkLogic(GgafActor* prm_pOtherActor) override;

    /**
     * 画面内に表示されているか判定 .
     * @return 0(false):Viewport範囲内
     *         1       :Viewport視錐台の上平面より上で範囲外
     *         2       :Viewport視錐台の下平面より下で範囲外
     *         3       :Viewport視錐台の左平面より左で範囲外
     *         4       :Viewport視錐台の右平面より右で範囲外
     *         5       :Viewport視錐台の手前平面より手前で範囲外
     *         6       :Viewport視錐台の奥平面より奥で範囲外
     *         ※判定優先順位順に並んでいます。（例：1 かつ 4 は 1 が返ります）
     */
    virtual int isOutOfView();

    /**
     * 現在の座標がゲーム活動範囲内かどうか判定 .
     * 画面内、画面外とは無関係
     * @return true:活動範囲外/false:活動範囲内
     */
    virtual bool isOutOfUniverse();

    /**
     * 未変換ワールド座標を設定 .
     * @param X
     * @param Y
     * @param Z
     */
    virtual void setGeometry(int X, int Y, int Z) {
        _X = X;
        _Y = Y;
        _Z = Z;
    }

    /**
     * 未変換座標をコピーして設定 .
     * @param prm_pActor コピー元アクター
     */
    virtual void setGeometry(GgafDx9GeometricActor* prm_pActor) {
        _X = prm_pActor->_X;
        _Y = prm_pActor->_Y;
        _Z = prm_pActor->_Z;
    }

    virtual void setRotation(GgafDx9GeometricActor* prm_pActor) {
        _RX = prm_pActor->_RX;
        _RY = prm_pActor->_RY;
        _RZ = prm_pActor->_RZ;
    }

    /**
     * _matInvWorldRotMvの逆行列を返す。
     * 計算済みならばそれを返す。
     * 未計算なら計算してそれを返す
     * @return
     */
    D3DXMATRIX* gatInvMatWorldRotMv() {
        if (_wasCalc_matInvWorldRotMv) {
            return &_matInvWorldRotMv;
        } else {
            D3DXMatrixInverse(&_matInvWorldRotMv, NULL, &_matWorldRotMv);
            _wasCalc_matInvWorldRotMv = true;
            return &_matInvWorldRotMv;
        }
    }


    virtual GgafCore::GgafGroupActor* addSubBone(actorkind prm_kind,
                                                 GgafDx9GeometricActor* prm_pGeoActor,
                                                 int prm_X_init_local,
                                                 int prm_Y_init_local,
                                                 int prm_Z_init_local,
                                                 int prm_RX_init_local,
                                                 int prm_RZ_init_local,
                                                 int prm_RY_init_local);

    virtual GgafCore::GgafGroupActor* addSubBone(GgafDx9GeometricActor* prm_pGeoActor,
                                                 int prm_X_init_local,
                                                 int prm_Y_init_local,
                                                 int prm_Z_init_local,
                                                 int prm_RX_init_local,
                                                 int prm_RZ_init_local,
                                                 int prm_RY_init_local);

    virtual void chengeGeoLocal() {
        if (_is_local) {
            return;
        } else {
            _X_final  = _X;
            _Y_final  = _Y;
            _Z_final  = _Z;
            _RX_final = _RX;
            _RY_final = _RY;
            _RZ_final = _RZ;
            _X  = _X_local;
            _Y  = _Y_local;
            _Z  = _Z_local;
            _RX = _RX_local;
            _RY = _RY_local;
            _RZ = _RZ_local;
            _is_local = true;
        }
    }
    virtual void chengeGeoFinal() {
        if (_is_local) {
            _X_local = _X;
            _Y_local = _Y;
            _Z_local = _Z;
            _RX_local = _RX;
            _RY_local = _RY;
            _RZ_local = _RZ;
            _X  = _X_final;
            _Y  = _Y_final;
            _Z  = _Z_final;
            _RX = _RX_final;
            _RY = _RY_final;
            _RZ = _RZ_final;
            _is_local = false;
        } else {
            return;

        }
    }


    /**
     * ワールド変換行列を計算する関数を定義 .
     * @param prm_pFunc 関数へのポインタ
     */
    void defineRotMvWorldMatrix(void (*prm_pFunc)(GgafDx9GeometricActor*, D3DXMATRIX&)) {
        _pFunc_calcRotMvWorldMatrix = prm_pFunc;
    }

    /**
     * デストラクタ
     */
    virtual ~GgafDx9GeometricActor();

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
