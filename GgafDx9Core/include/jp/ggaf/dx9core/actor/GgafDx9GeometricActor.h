#ifndef GGAFDX9GEOMETRICACTOR_H_
#define GGAFDX9GEOMETRICACTOR_H_

namespace GgafDx9Core {

/**
 * 座標、回転、スケール情報を持ったアクター.
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
    bool _is2DActor;
    /** [r/w]ワールドX座標( _X : DirectXのX座標 : 初期カメラ位置での画面上ピクセル = 1000 : 0.1 : 約 1px  ) */
    coord _X;
    /** [r/w]ワールドY座標( _Y : DirectXのY座標 : 初期カメラ位置での画面上ピクセル = 1000 : 0.1 : 約 1px  ) */
    coord _Y;
    /** [r/w]ワールドZ座標( _Z : DirectXのZ座標 : 初期カメラ位置での画面上ピクセル = 1000 : 0.1 : 約 1px  ) */
    coord _Z;
    /** [r/w]ワールドX軸回転角(_RX : Degree = 1000 : 1度) */
    angle _RX;
    /** [r/w]ワールドY軸回転角(_RY : Degree = 1000 : 1度) */
    angle _RY;
    /** [r/w]ワールドZ軸回転角(_RZ : Degree = 1000 : 1度) */
    angle _RZ;
    /** [r/w]ワールドX軸方向スケール(_SX : 倍率 = 1000 : 1.0倍) */
    scale _SX;
    /** [r/w]ワールドY軸方向スケール(_SY : 倍率 = 1000 : 1.0倍) */
    scale _SY;
    /** [r/w]ワールドZ軸方向スケール(_SZ : 倍率 = 1000 : 1.0倍) */
    scale _SZ;
    /** [r]黒子A */
    GgafDx9KurokoA* _pKurokoA;
    GgafDx9KurokoB* _pKurokoB;
    /** [r]チェッカー */
    GgafDx9Checker* _pChecker;
    /** [r]効果音発生管理オブジェクト */
    GgafDx9SeTransmitter* _pSeTransmitter;

    /** [r/w]境界球の半径(DirectXの単位)。画面外判定に使用される */
    dxcoord _radius_bounding_sphere;
    /** [rw]モデルの境界球半径倍率 */
    dxcoord _rate_BoundingSphereRadius;
    /** [r] 内部で _X から計算されるDirectXのワールドX座標(_X : _fX = 1000 : 0.1) */
    dxcoord _fX;
    /** [r] 内部で _Y から計算されるDirectYのワールドY座標(_Y : _fY = 1000 : 0.1) */
    dxcoord _fY;
    /** [r] 内部で _Z から計算されるDirectZのワールドZ座標(_Z : _fZ = 1000 : 0.1) */
    dxcoord _fZ;
    /** [r]視錐台上面から視野外に向かっての自身の座標までのDirectXの距離、視野内の距離は負の値になる */
    dxcoord _fDist_VpPlnTop;
    /** [r]視錐台下面から視野外に向かっての自身の座標までのDirectXの距離、視野内の距離は負の値になる */
    dxcoord _fDist_VpPlnBottom;
    /** [r]視錐台左面から視野外に向かっての自身の座標までのDirectXの距離、視野内の距離は負の値になる */
    dxcoord _fDist_VpPlnLeft;
    /** [r]視錐台右面から視野外に向かっての自身の座標までのDirectXの距離、視野内の距離は負の値になる */
    dxcoord _fDist_VpPlnRight;
    /** [r]視錐台手前面から視野外に向かっての自身の座標までのDirectXの距離、視野内の距離は負の値になる */
    dxcoord _fDist_VpPlnFront;
    /** [r]視錐台奥面から視野外に向かっての自身の座標までのDirectXの距離、視野内の距離は負の値になる */
    dxcoord _fDist_VpPlnBack;
    /** [r/w]WORLD変換行列計算関数(通常は回転×移動のみ) */
    void (*_pFunc_calcRotMvWorldMatrix)(GgafDx9GeometricActor*, D3DXMATRIX&);

    void (*_pFunc_calcWorldMatrix)(GgafDx9GeometricActor*, D3DXMATRIX&);

    /** [r]自身の現在のWorld変換行列(通常は拡大縮小×回転×移動) */
    D3DXMATRIX _matWorld;
    /** [r]自身の現在のWorld変換行列(回転×移動のみ) */
    D3DXMATRIX _matWorldRotMv;
    /** [r]自身の現在のWorld変換行列の逆行列(回転×移動のインバース) */
    D3DXMATRIX _matInvWorldRotMv;
    /** [r]カレントフレームで自身の現在のWorld変換行列の逆行列(_matInvWorldRotMv)を計算して求めたかどうかのフラグ。 */
    bool _wasCalc_matInvWorldRotMv;

    /** 土台となるアクター(土台が無い場合はNULL) */
    GgafDx9Core::GgafDx9GeometricActor* _pActor_Base;
    /** 土台アクター上でのワールドX座標 */
    coord _X_local;
    /** 土台アクター上でのワールドY座標 */
    coord _Y_local;
    /** 土台アクター上でのワールドZ座標 */
    coord _Z_local;
    /** 土台アクター上でのワールドX軸回転角 */
    angle _RX_local;
    /** 土台アクター上でのワールドY軸回転角 */
    angle _RY_local;
    /** 土台アクター上でのワールドZ軸回転角 */
    angle _RZ_local;

    coord _X_final;
    coord _Y_final;
    coord _Z_final;
    angle _RX_final;
    angle _RY_final;
    angle _RZ_final;
//    coord _X_offset;
//    coord _Y_offset;
//    coord _Z_offset;
//    angle _RX_offset;
//    angle _RY_offset;
//    angle _RZ_offset;

    bool _is_local;

    //補足メモ
    //【_X, _Y, _Z の単位について】
    //　座標値 _X, _Y, _Z は独自の単位である。
    //　DirectX座標(float)系の値の１.0に相当する X, _Y, _Z座標値は、LEN_UNIT(=1000)倍のPX_UNIT(=10)倍の整数値である。
    //　つまり10000倍。DirectX座標単位の１.0は、ゲーム画面上で10px相当の大きさになる（ようにカメラを引いている）。
    //　例えば、_X = 5000 は、画面で初期カメラ位置で 5px の幅に見え、DirectX座標では0.5になる（ように設計している）。
    //　_X,_Y,_Z     → ピクセル の変換。    ・・・ _X,_Y,_Z を LEN_UNIT(=1000)で割る。
    //　DirectX座標  → ピクセル の変換。    ・・・ DirectX座標を、PX_UNIT(=10)を掛け算する。
    //　_X,_Y,_Z     → DirectX座標 の変換。 ・・・ _X,_Y,_Z を LEN_UNIT*PX_UNIT(=10000)で割る。
    //　実は、描画の直前に_X,_Y,_Z を入力として、 LEN_UNIT*PX_UNIT 除算し、ワールド変換行列の値に使用されている。
    //　わざわざこんなことをしているのは、ゲーム中の座標計算は全て整数で行い、少しでも速度を上げたかったため。
    //　昔(ｲﾂﾔﾈﾝ;)はよく使っていた手法と思うのだが、現在では 最適化されている float や double でもかなり速いので、
    //　本当にこの設計でよかったのだろうか…、いや、速くなってると信じる。
    //
    //【_RX, _RY, _RZ の単位について】
    //　独自単位の「アングル値」を採る。
    //　「アングル値」とは 0~3600000 の値で、見た目では 角度値(Degree)の 1000倍の精度の値である。
    //　(但し、実際は内部では Degree の 10倍の精度である。3600方向の単位方向ベクトルテーブルと対応させる設計)
    //　1度は1000、0.5度は500。直角の値は90000、水平は180000である。
    //　中心角と同じく3時の方向を0とし、軸の正方向を向いて反時計回りにアングル値は増えるものとする。
    //
    //【_SX, _SY, _SZ の単位について】
    //　1000が１倍のスケール意味する。したがってデフォルトは1000になっている。
    //　描画の直前に 1000 で除算され、拡大縮小率に変換し使用する。


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
     * 上記①②③と同等の処理を行うようにすべきである。
     * 逆に効果エフェクトなど、上記の考慮が不要なアクターの場合は、本メソッドをオーバーライドし、
     * _fX,_fY,_fZのみ更新等を実装することにより、パフォーマンスを向上させることができる。 <BR>
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
    virtual void locate(coord X, coord Y, coord Z) {
        _X = X;
        _Y = Y;
        _Z = Z;
    }
    virtual void locate(coord X, coord Y) {
        _X = X;
        _Y = Y;
    }

    /**
     * スケールをスケール値で設定します。
     * 【注意】
     * _pScaler->behave(); が存在すると無意味になります。
     * @param S スケール値(1000 で 1.0倍)
     */
    virtual void setScale(scale S) {
        _SX = S;
        _SY = S;
        _SZ = S;
        setBoundingSphereRadiusRate((1.0*S)/1000);
    }

    /**
     * スケールを倍率で設定します。
     * 1.0 で 1.0倍。
     * 【注意】
     * _pScaler->behave(); が存在すると無意味になります。
     * @param prm_rate 倍率
     */
    virtual void setScaleRate(float prm_rate) {
        _SX = 1000*prm_rate;
        _SY = 1000*prm_rate;
        _SZ = 1000*prm_rate;
        setBoundingSphereRadiusRate(prm_rate);
    }

    virtual void addScale(scale dS) {
        _SX += dS;
        _SY += dS;
        _SZ += dS;
        setBoundingSphereRadiusRate((1.0*_SX)/1000);
    }


    /**
     * 未変換座標をコピーして設定 .
     * @param prm_pActor コピー元アクター
     */
    virtual void locateAs(GgafDx9GeometricActor* prm_pActor) {
        _X = prm_pActor->_X;
        _Y = prm_pActor->_Y;
        _Z = prm_pActor->_Z;
    }
    virtual void locateAs(GgafDx9GeoElem* prm_pGeoElem);

    virtual void rotateWith(GgafDx9GeometricActor* prm_pActor);

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


    virtual GgafCore::GgafGroupHead* addSubBone(actorkind prm_kind,
                                                 GgafDx9GeometricActor* prm_pGeoActor,
                                                 int prm_X_init_local,
                                                 int prm_Y_init_local,
                                                 int prm_Z_init_local,
                                                 int prm_RX_init_local,
                                                 int prm_RZ_init_local,
                                                 int prm_RY_init_local);

    virtual GgafCore::GgafGroupHead* addSubBone(GgafDx9GeometricActor* prm_pGeoActor,
                                                 int prm_X_init_local,
                                                 int prm_Y_init_local,
                                                 int prm_Z_init_local,
                                                 int prm_RX_init_local,
                                                 int prm_RZ_init_local,
                                                 int prm_RY_init_local);

    virtual void changeGeoLocal() {
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
    virtual void changeGeoFinal() {
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
     * モデルの境界球半径の倍率設定。
     * 境界球半径とは、ローカル座標の原点から全頂点の距離で最大の長さで、
     * この値は、画面外判定に利用されてるため、モデル表示時に独自に拡大を行った場合。
     * この値を更新しないと画面外判定が正しく行われない。<BR>
     * 例えば、表示時に５倍の拡大で表示した場合、本メソッドで<BR>
     * <BR>
     * setBoundingSphereRadiusRate(5.0)<BR>
     * <BR>
     * とすると、画面外判定が正しくなる。<BR>
     * 画面外判定が正しくなるとは、具体的には、isOutOfView() の判定計算時に影響を与える
     * という意味である。<BR>
     * @param prm_rate 拡大率
     */
    virtual void setBoundingSphereRadiusRate(FLOAT prm_rate) {
        _rate_BoundingSphereRadius = prm_rate;
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
