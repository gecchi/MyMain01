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
    /** 画面外種別。isOffscreen()が内部で使用。未計算時は -1 */
    int _offscreenkind;

public:
    /** [r] 変換済み座標であるか(true:本アクターは変換済み座標/false:本アクターはワールド座標) */
    bool _isTransformed;
    /** [r/w]ワールドX座標(画面ピクセル : _X  = 1px : 1000) */
    int _X;
    /** [r/w]ワールドY座標(画面ピクセル : _Y  = 1px : 1000) */
    int _Y;
    /** [r/w]ワールドZ座標(画面ピクセル : _Z  = 1px : 1000) */
    int _Z;
    /** [r/w]ワールドX軸回転角(Degree : _RX = 1度 : 1000) */
    angle _RX;
    /** [r/w]ワールドY軸回転角(Degree : _RY = 1度 : 1000) */
    angle _RY;
    /** [r/w]ワールドZ軸回転角(Degree : _RZ = 1度 : 1000) */
    angle _RZ;
    /** [r/w]ワールドX軸方向スケール(倍率 : _SX = 1.0倍 : 1000) */
    int _SX;
    /** [r/w]ワールドY軸方向スケール(倍率 : _SY = 1.0倍 : 1000) */
    int _SY;
    /** [r/w]ワールドZ軸方向スケール(倍率 : _SZ = 1.0倍 : 1000) */
    int _SZ;
    /** [r]ワールド座標計算支援オブジェクト */
    GgafDx9GeometryMover* _pMover;
    /** [r]チェッカーオブジェクト */
    GgafDx9Checker* _pChecker;
    /** [r/w]境界球の半径(DirectXのt単位)。画面外判定に使用される */
    FLOAT _fBoundingSphereRadius;
    /** [r]DirectXのワールドX座標(_fX : _X = 0.1 : 1000) */
    FLOAT _fX;
    /** [r]DirectYのワールドY座標(_fY : _Y = 0.1 : 1000) */
    FLOAT _fY;
    /** [r]DirectZのワールドZ座標(_fZ : _Z = 0.1 : 1000) */
    FLOAT _fZ;
    /** [r]視野外の自身の座標から視錐台上面までのDirectXの距離、視野内の距離は負の値になる */
    FLOAT _fDist_VpPlnTop;
    /** [r]視野外の自身の座標から視錐台下面までのDirectXの距離、視野内の距離は負の値になる */
    FLOAT _fDist_VpPlnBottom;
    /** [r]視野外の自身の座標から視錐台左面までのDirectXの距離、視野内の距離は負の値になる */
    FLOAT _fDist_VpPlnLeft;
    /** [r]視野外の自身の座標から視錐台右面までのDirectXの距離、視野内の距離は負の値になる */
    FLOAT _fDist_VpPlnRight;
    /** [r]視野外の自身の座標から視錐台手前面までのDirectXの距離、視野内の距離は負の値になる */
    FLOAT _fDist_VpPlnFront;
    /** [r]視野外の自身の座標から視錐台奥面までのDirectXの距離、視野内の距離は負の値になる */
    FLOAT _fDist_VpPlnBack;
    /** [r/w]WORLD変換行列計算関数 */
    void (*_pFunc_calcWorldMatrix)(GgafDx9GeometricActor*, D3DXMATRIX&);

    /** [r/w]自身の現在のWorld変換行列(回転と移動のみ) */
    D3DXMATRIX _matWorld_RM;
    /** [r/w]自身の現在のWorld変換行列 */
    D3DXMATRIX _matWorld;
    /** 土台となるアクター */
    GgafDx9Core::GgafDx9GeometricActor* _pActor_Foundation;
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
    //　採り得る値は DirectX座標(float)の LEN_UNIT(=1000)倍のPX_UNIT(=10)倍の整数値である。つまり10000倍。
    //　DirectX座標単位の1は、ゲーム画面上で10px相当の大きさになる（ようにカメラを引いている）。
    //　例えば、_X = 5000 は、画面では5pxの位置、DirectX座標では50になる（ように設計）。
    //　_X,_Y,_Z をピクセルで考えたい場合は、LEN_UNIT(=1000)で割る。
    //　DirectX座標単位をピクセルで考えたい場合は、PX_UNIT(=10)を掛け算する。
    //　描画の直前に_X,_Y,_Z は (LEN_UNIT*PX_UNIT) で除算されワールド変換に使用される。
    //　なぜこんなややこしいことをするかというと、座標計算をすべて整数で行い、少しでも速くしたかった。
    //　floatのままだと、掛け算割り算の時に、「あぁ、いちいちdoubleにせんでもいいのに」と毎回思うのが、体に悪い・・・。
    //　全部整数で計算してやろう、というのが発端。
    //　昔(BASICの時)は良く使った手法なのだが、もはやfloatでもかなり速いので、良いのかどうか微妙。
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
     * ① processBehavior() 後、座標計算事後処理として <BR>
     *    以下のメンバの更新を行う。 <BR>
     *     _fX <BR>
     *     _fY <BR>
     *     _fZ <BR>
     *     _fDist_VpPlnTop <BR>
     *     _fDist_VpPlnBottom <BR>
     *     _fDist_VpPlnLeft <BR>
     *     _fDist_VpPlnRight <BR>
     *     _fDist_VpPlnFront <BR>
     *     _fDist_VpPlnBack <BR>
     * ② ワールド変換行列を作成し_matWorldに保持
     * ③ processJudgement() を呼び出すのため準備処理として、 <BR>
     *    アクターの線形８分木配列への登録を行う。 <BR>
     *
     * <B>[注意]</B> <BR>
     * 本メソッドはオーバーライド可能とするが、フレームワークの描画や判定に関わる
     * 重要な事前処理のため、オーバーライドは推奨できない。<BR>
     * どうしてもオーバーライドが必要な場合は、オーバーライド先で、 <BR>
     * GgafDx9GeometricActor::processPreJudgement() を呼び出すか、 <BR>
     * 同等の処理を行うようにすべきである。 <BR>
     */
    virtual void processPreJudgement() override;

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
     * @return 0:Viewport範囲内
     *         6:Viewport視錐台の奥平面より奥で範囲外
     *         5:Viewport視錐台の手前平面より手前で範囲外
     *         4:Viewport視錐台の右平面より右で範囲外
     *         3:Viewport視錐台の左平面より左で範囲外
     *         2:Viewport視錐台の下平面より下で範囲外
     *         1:Viewport視錐台の上平面より上で範囲外
     */
    virtual int isOffscreen();

    /**
     * 現在の座標がゲーム活動範囲内かどうか判定 .
     * 画面内、画面外とは無関係
     * @return true:活動範囲外/false:活動範囲内
     */
    virtual bool isOutOfGameSpace();

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
    void defineWorldMatrix(void (*prm_pFunc)(GgafDx9GeometricActor*, D3DXMATRIX&)) {
        _pFunc_calcWorldMatrix = prm_pFunc;
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
