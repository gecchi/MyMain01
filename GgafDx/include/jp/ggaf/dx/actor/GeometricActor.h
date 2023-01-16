#ifndef GGAF_DX_GEOMETRICACTOR_H_
#define GGAF_DX_GEOMETRICACTOR_H_
#include "GgafDxCommonHeader.h"
#include "jp/ggaf/dx/actor/BaseActor.h"

#include "jp/ggaf/dx/util/curve/CurveManufacture.h"
#include <D3dx9math.h>

namespace GgafDx {

/**
 * 座標、回転、スケール情報を持ったアクター.
 * ワールド座標、或いは変換済み座標の何れかを持ち、<BR>
 * 座標関連メソッドを備えたアクターです。<BR>
 * (旧UntranceformedActor とTranceformedActor を統合)
 * @version 1.00
 * @since 2008/09/08
 * @author Masatoshi Tsuge
 */
class GeometricActor : public BaseActor {

private:
    /**
     * 下位で使用禁止 .
     */
    void processFinal() override {
    }

    /** [r]力車 */
    VecVehicle* _pVecVehicle;
    /** [r]駕籠(平行移動支援) */
    AxisVehicle* _pAxisVehicle;

    GeoVehicle* _pGeoVehicle;

    /** [r]拡大縮小支援 */
    Scaler* _pScaler;
    /** [r]効果音発生管理オブジェクト */
    SeTransmitterForActor* _pSeTransmitter;

    VehicleLeader* _pVehicleLeader;

public:
    /** [r] 変換済み座標であるか(true:本アクターは変換済み座標/false:本アクターはワールド座標) */
    bool _is_fix_2D;
    /** [r] 画面外種別。isOutOfView()が内部で使用。未計算時は -1 */
    int _offscreen_kind;

    /** [r/w]ワールドX座標( _x : DirectXのX座標 : 初期カメラ位置での画面上ピクセル = 1000 : 0.1 : 約 1px  ) */
    coord _x;
    /** [r/w]ワールドY座標( _y : DirectXのY座標 : 初期カメラ位置での画面上ピクセル = 1000 : 0.1 : 約 1px  ) */
    coord _y;
    /** [r/w]ワールドZ座標( _z : DirectXのZ座標 : 初期カメラ位置での画面上ピクセル = 1000 : 0.1 : 約 1px  ) */
    coord _z;
    /** [r/w]ワールドX軸回転角(_rx : Degree = 1000 : 1度) */
    angle _rx;
    /** [r/w]ワールドY軸回転角(_ry : Degree = 1000 : 1度) */
    angle _ry;
    /** [r/w]ワールドZ軸回転角(_rz : Degree = 1000 : 1度) */
    angle _rz;
    /** [r/w]ワールドX軸方向スケール(_sx : 倍率 = 1000 : 1.0倍) */
    scale _sx;
    /** [r/w]ワールドY軸方向スケール(_sy : 倍率 = 1000 : 1.0倍) */
    scale _sy;
    /** [r/w]ワールドZ軸方向スケール(_sz : 倍率 = 1000 : 1.0倍) */
    scale _sz;
    /** [r]チェッカー */
    CollisionChecker* _pChecker;

    /** [r]モデルの境界球半径倍率 */
    dxcoord _rate_of_bounding_sphere_radius;
    /** [r]内部で _x から計算されるDirectXのワールドX座標(_x : _fX = 1000 : 0.1) */
    dxcoord _fX;
    /** [r]内部で _y から計算されるDirectYのワールドY座標(_y : _fY = 1000 : 0.1) */
    dxcoord _fY;
    /** [r]内部で _z から計算されるDirectZのワールドZ座標(_z : _fZ = 1000 : 0.1) */
    dxcoord _fZ;
    /** [r]視錐台上面から視野外に向かっての自身の座標までのDirectXの距離、視野内の距離は負の値になる */
    dxcoord _dest_from_vppln_top;
    /** [r]視錐台下面から視野外に向かっての自身の座標までのDirectXの距離、視野内の距離は負の値になる */
    dxcoord _dest_from_vppln_bottom;
    /** [r]視錐台左面から視野外に向かっての自身の座標までのDirectXの距離、視野内の距離は負の値になる */
    dxcoord _dest_from_vppln_left;
    /** [r]視錐台右面から視野外に向かっての自身の座標までのDirectXの距離、視野内の距離は負の値になる */
    dxcoord _dest_from_vppln_right;
    /** [r]視錐台手前面から視野外に向かっての自身の座標までのDirectXの距離、視野内の距離は負の値になる */
    dxcoord _dest_from_vppln_infront;
    /** [r]視錐台奥面から視野外に向かっての自身の座標までのDirectXの距離、視野内の距離は負の値になる */
    dxcoord _dest_from_vppln_back;
    /** [r/w]WORLD変換(回転×移動)行列計算関数 */
    void (*_pFunc_calc_rot_mv_world_matrix)(const GeometricActor* const, D3DXMATRIX&);
    /** [r]自身の現在のWorld変換行列(通常は「拡大縮小×回転×移動」)。土台がある場合は、その土台と行列の積になっている。 */
    D3DXMATRIX _matWorld;
    /** [r]自身の現在のWorld変換行列の「回転×移動」のみ。土台がある場合は、その土台と行列の積になっている。 */
    D3DXMATRIX _matWorldRotMv;
    /** [r]自身の現在のWorld変換行列の「回転×移動」の逆行列(回転×移動のインバース) */
    D3DXMATRIX _matInvWorldRotMv;
    /** [r]カレントフレームで自身の現在のWorld変換行列の逆行列(_matInvWorldRotMv)を計算して求めたかどうかのフラグ。 */
    bool _was_calculated_matInvWorldRotMv;

    /** [r]土台となるアクター、土台が無い場合はnullptr（FK用） */
    GeometricActor* _pActor_base;
    /** [r]土台アクター上でのワールドX座標 */
    coord _x_local;
    /** [r]土台アクター上でのワールドY座標 */
    coord _y_local;
    /** [r]土台アクター上でのワールドZ座標 */
    coord _z_local;
    /** [r]土台アクター上でのワールドX軸回転角 */
    angle _rx_local;
    /** [r]土台アクター上でのワールドY軸回転角 */
    angle _ry_local;
    /** [r]土台アクター上でのワールドZ軸回転角 */
    angle _rz_local;

    coord _x_final;
    coord _y_final;
    coord _z_final;
    angle _rx_final;
    angle _ry_final;
    angle _rz_final;

    bool _is_local;

    //補足メモ
    //【_x, _y, _z の単位について】
    //本フレームワークでは、３つの座標単位(スケール)がある。
    //dxcoord  ・・・ DirectX座標単位。
    //coord    ・・・ アプリケーション独自の内部座標単位。（これがメイン）
    //pixcoord ・・・ カメラが初期位置かつ、z=0 の xy平面にキャラがいた場合の、画面上でのピクセル値単位
    //座標値 _x, _y, _z は coord (これがメイン)である。
    //DirectX座標(float)系の値の1.0に相当する _x, _y, _z 座標値は、LEN_UNIT(=1000)倍のPX_UNIT(=10)倍の整数値である。
    //また、DirectX座標系単位の1.0は、ゲーム画面上で10px相当の大きさになる（ようにカメラを引いている）。
    //例えば、_x = 5000 は、画面で初期カメラ位置で 5px の幅に見え、DirectX座標では0.5になる（ように設計している）。
    //_x,_y,_z     → ピクセル の変換。    ・・・ _x,_y,_z を LEN_UNIT(=1000)で割る。
    //DirectX座標  → ピクセル の変換。    ・・・ DirectX座標を、PX_UNIT(=10)を掛け算する。
    //_x,_y,_z     → DirectX座標 の変換。 ・・・ _x,_y,_z を LEN_UNIT*PX_UNIT(=10000)で割る。
    //実は、描画の直前に_x,_y,_z を入力として、 LEN_UNIT*PX_UNIT 除算し、ワールド変換行列の値に使用されている。
    //わざわざこんなことをしているのは、ゲーム中の座標計算は全て整数で行い、少しでも速度を上げたかったため。
    //昔(ｲﾂﾔﾈﾝ;)はよく使っていた手法と思うのだが、現在では 最適化されている float や double でもかなり速いので、
    //本当にこの設計でよかったのだろうか…、いや、速くなってると信じる。
    //
    //【_rx, _ry, _rz の単位について】
    //独自単位の「アングル値」を採る。
    //「アングル値」とは 0~3600000 の値で、見た目では 角度値(Degree)の 1000倍の精度の値である。
    //(但し、実際は内部では Degree の 10倍の精度である。3600方向の単位方向ベクトルテーブルと対応させる設計)
    //1度は1000、0.5度は500。直角の値は90000、水平は180000である。
    //中心角と同じく3時の方向を0とし、軸の正方向を向いて反時計回りにアングル値は増えるものとする。
    //
    //【_sx, _sy, _sz の単位について】
    //値1000が1.0倍のスケール意味する。したがってデフォルトは1000になっている。
    //描画の直前に 1000 で除算され、拡大縮小率に変換し使用する。

public:
    /**
     * コンストラクタ .
     * @param prm_name アクター名
     * @param prm_pChecker チェッカー(使用しない時 nullptr)
     * @return
     */
    GeometricActor(const char* prm_name,
                   CollisionChecker* prm_pChecker);

    virtual GeometricActor* getPrev() const override { //共変の戻り値
        return (GeometricActor*)GgafCore::Actor::getPrev();
    }

    virtual GeometricActor* getNext() const override { //共変の戻り値
        return (GeometricActor*)GgafCore::Actor::getNext();
    }

    void setCollisionChecker(CollisionChecker* prm_pChecker);

    CollisionChecker* getCollisionChecker() {
        return _pChecker;
    }
    /**
     * 本アクターの力車を取得 .
     * @return 力車
     */
    VecVehicle* getVecVehicle();

    /**
     * 本アクターの駕籠(平行移動支援)オブジェクトを取得 .
     * @return 駕籠(平行移動支援)オブジェクト
     */
    AxisVehicle* getAxisVehicle();

    GeoVehicle* getGeoVehicle();

    virtual VehicleLeader* createCurveVehicleLeader(CurveManufacture* prm_pCurveManufacture);

    /**
     * VehicleLeader を FeatureScene に関連付ける。
     * FeatureSceneの影響をVehicleLeaderを設定する。
     * @param prm_pVehicleLeader
     */
    void setVehicleLeader(GgafDx::VehicleLeader* prm_pVehicleLeader) {
        _pVehicleLeader = prm_pVehicleLeader;
    }

    VehicleLeader* getVehicleLeader() {
        return _pVehicleLeader;
    }

    /**
     * 本アクターの拡大縮小支援オブジェクトを取得 .
     * @return 拡大縮小支援オブジェクト
     */
    Scaler* getScaler();

    /**
     * 本アクターのサウンドエフェクト出力支援オブジェクトを取得 .
     * @return サウンドエフェクト出力支援オブジェクト
     */
    SeTransmitterForActor* getSeTransmitter();

    /**
     * 判定処理事前処理 .
     * processBehavior() 後、座標計算事後処理として次の処理を行う <BR>
     * ① 土台がアクターがある場合は、合成ワールド変換行列を求める。<BR>
     * ② 拡大縮小＞回転＞平行移動のワールド変換行列を構築。<BR>
     * ③ 土台がアクターがある場合は、合成ワールド変換行列実行後の絶対座標を求める。<BR>
     * ④ 自身の座標情報(_x,_y,_z)から以下のメンバの更新を行う。 <BR>
     *     _fX <BR>
     *     _fY <BR>
     *     _fZ <BR>
     * ⑤ 画面内外を判定するための、視錐台の各面との距離を計算以下のメンバの更新を行う。 <BR>
     *     _dest_from_vppln_top <BR>
     *     _dest_from_vppln_bottom <BR>
     *     _dest_from_vppln_left <BR>
     *     _dest_from_vppln_right <BR>
     *     _dest_from_vppln_infront <BR>
     *     _dest_from_vppln_back <BR>
     * 本メソッドはオーバーライド可能とするが、フレームワークの描画や判定に関わる
     * 重要な事前処理のため、オーバーライドは推奨できない。<BR>
     * どうしてもオーバーライドが必要な場合は、オーバーライド先で、 <BR>
     * GeometricActor::processSettlementBehavior() を呼び出すか、 <BR>
     * 上記と同等の処理を行うようにすべきである。
     * 逆に効果エフェクトなど、上記の考慮が不要なアクターの場合は、本メソッドをオーバーライドし、
     * _fX,_fY,_fZのみ更新等を実装することにより、パフォーマンスを向上させることができる。 <BR>
     */
    virtual void processSettlementBehavior() override;

    virtual void processPreJudgement() override;

    /**
     * 共通の描画事後処理 .
     * 俺デバッグモード (MY_DEBUG が 1)の場合は
     * 当たり判定領域を描画する。
     * (といっても drawHitArea() をコールするだけ)
     */
    virtual void processAfterDraw() override;

    /**
     * 絶対座標計算後の処理 .
     * 土台となるアクター(_pActor_base) がある場合、processSettlementBehavior() 内で
     * 絶対座標計算後に行割れた後から、八分木登録の直前にコールバックされる。
     * 土台に乗っかるアクターから弾を発射したい場合等を想定。絶対座標で指定できる。
     */
    virtual void processChangeGeoFinal() {
    }

    /**
     * 当たり判定ロジック .
     * 当たり判定ロジックを実装している。<BR>
     * チェッカーオブジェクトがある場合、<BR>
     * CollisionChecker::isHit() で判定する。<BR>
     * チェッカーオブジェクトが無い場合、<BR>
     * ヒットしていないこととする。<BR>
     * @param prm_pOtherActor 相手のアクター
     * @return true：ヒットしている／false：ヒットしていない
     */
    virtual bool processHitChkLogic(GgafCore::Actor* prm_pOtherActor) override;

    /**
     * 当たり判定領域を描画 .
     * 実際の処理は下位クラスに任せる。
     */
    virtual void drawHitArea() {};

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
     * 現在の座標がこの世の外側なのか否か .
     * 画面内、画面外とは無関係
     * @return true:この世の外側/false:この世の内側
     */
    virtual bool isOutOfSpacetime() const;

    /**
     * 座標を設定 .
     * @param x
     * @param y
     * @param z
     */
    virtual void setPosition(coord x, coord y, coord z) {
        _x = x;
        _y = y;
        _z = z;
    }

    /**
     * 座標を設定 .
     * z座標は更新しない。
     * @param x
     * @param y
     */
    virtual void setPosition(coord x, coord y) {
        _x = x;
        _y = y;
    }

    /**
     * 座標を指定座標付近に適当に設定 .
     * @param x 範囲中心X座標
     * @param y 範囲中心Y座標
     * @param z 範囲中心Z座標
     * @param r 範囲球の半径
     */
    virtual void setPositionAround(coord x, coord y, coord z, coord r);

    /**
     * 座標を指定座標付近に適当に設定 .
     * @param x 範囲中心X座標
     * @param y 範囲中心Y座標
     * @param r 範囲円の半径
     */
    virtual void setPositionAround(coord x, coord y, coord r);

    /**
     * 3Dアクターについて、ビュー座標で指定により、自身を対応するワールド座標に配置する .
     * @param prm_view_x ビュー座標X軸要素
     * @param prm_view_y ビュー座標Y軸要素
     * @param prm_depth カメラ視点からの距離
     */
    void setPositionByViewCoord(coord prm_view_x, coord prm_view_y, coord prm_depth);

    /**
     * 2Dアクターについて、自身のビュー座標より、対応するワールド座標を取得する .
     * @param prm_depth 取得したいワールド座標のカメラ視点からの距離を指定
     * @param out_world_x 対応するワールド座標X軸要素
     * @param out_world_y 対応するワールド座標Y軸要素
     * @param out_world_z 対応するワールド座標Z軸要素
     */
    void getWorldPosition(coord prm_depth, coord& out_world_x, coord& out_world_y, coord& out_world_z);

    /**
     * 2Dアクターについて、ワールド座標で指定により、自身を対応するビュー座標に配置する .
     * @param prm_world_x ワールド座標X軸要素
     * @param prm_world_y ワールド座標Y軸要素
     * @param prm_world_z ワールド座標Z軸要素
     */
    void setPositionByWorldCoord(coord prm_world_x, coord prm_world_y, coord prm_world_z);

    /**
     * 3Dアクターについて、自身のワールド座標より、対応するビュー座標を取得する .
     * @param out_view_x 対応するビュー座標X軸要素
     * @param out_view_y 対応するビュー座標Y軸要素
     */
    void getViewPosition(coord& out_view_x, coord& out_view_y);
    /**
     * X軸Y軸Z軸各軸スケール _sx, _sy, _sz を同じ値で設定 .
     * 【注意】
     * pScaler_->behave(); が存在すると上書きされますよ。
     * @param S スケール値(1000 で 1.0倍)
     */
    virtual void setScale(scale s) {
        _sx = s;
        _sy = s;
        _sz = s;
        setBoundingSphereRadiusRate(SC_R(s));
    }

    /**
     * X軸Y軸Z軸スケール _sx, _sy, _sz をそれぞれ値で設定 .
     * 【注意】
     * pScaler_->behave(); が存在すると上書きされますよ！。
     * @param sx X軸スケール値(1000 で 1.0倍)
     * @param sy Y軸スケール値(1000 で 1.0倍)
     * @param sz Z軸スケール値(1000 で 1.0倍)
     */
    virtual void setScale(scale sx, scale sy, scale sz) {
        _sx = sx;
        _sy = sy;
        _sz = sz;
        setBoundingSphereRadiusRate(SC_R(MAX3(_sx,_sy,_sz)));
    }

    /**
     * X軸Y軸スケール(_sx, _sy)のみを値で設定 .
     * 【注意】
     * pScaler_->behave(); が存在すると上書きされますよ！。
     * @param sx X軸スケール値(1000 で 1.0倍)
     * @param sy Y軸スケール値(1000 で 1.0倍)
     */
    virtual void setScale(scale sx, scale sy) {
        _sx = sx;
        _sy = sy;
        setBoundingSphereRadiusRate(SC_R(MAX3(_sx,_sy,_sz)));
    }

    /**
     * X軸Y軸Z軸全ての軸スケールを割合で設定 .
     * 1.0 で 元のモデルの大きさから1.0倍。
     * 【注意】
     * pScaler_->behave(); が存在すると上書きされますよ！。
     * @param prm_rate 倍率
     */
    virtual void setScaleR(float prm_rate) {
        _sx = R_SC(prm_rate);
        _sy = R_SC(prm_rate);
        _sz = R_SC(prm_rate);
        setBoundingSphereRadiusRate(prm_rate);
    }

    /**
     * X軸Y軸Z軸各軸スケールを割合で設定 .
     * 1.0 で 元のモデルの大きさから1.0倍。
     * 【注意】
     * pScaler_->behave(); が存在すると上書きされますよ！。
     * @param prm_x_rate X軸倍率
     * @param prm_y_rate Y軸倍率
     * @param prm_z_rate Z軸倍率
     */
    virtual void setScaleR(float prm_x_rate, float prm_y_rate, float prm_z_rate) {
        _sx = R_SC(prm_x_rate);
        _sy = R_SC(prm_y_rate);
        _sz = R_SC(prm_z_rate);
        setBoundingSphereRadiusRate(MAX3(prm_x_rate, prm_y_rate, prm_z_rate));
    }

    /**
     * X軸Y軸のみスケールを割合で設定 .
     * 1.0 で 元のモデルの大きさから1.0倍。
     * 【注意】
     * pScaler_->behave(); が存在すると上書きされますよ！。
     * @param prm_x_rate X軸倍率
     * @param prm_y_rate Y軸倍率
     */
    virtual void setScaleR(float prm_x_rate, float prm_y_rate) {
        _sx = R_SC(prm_x_rate);
        _sy = R_SC(prm_y_rate);
        setBoundingSphereRadiusRate(MAX3(prm_x_rate, prm_y_rate, SC_R(_sz)));
    }

    /**
     * X軸Y軸Z軸各軸スケール _sx, _sy, _sz を同じ値で加算 .
     * 【注意】
     * pScaler_->behave(); が存在すると上書きされますよ！。
     * @param dS 加算するスケール値
     */
    virtual void addScale(scale dS) {
        _sx += dS;
        _sy += dS;
        _sz += dS;
        setBoundingSphereRadiusRate(SC_R(MAX3(_sx,_sy,_sz)));
    }

    virtual void addScaleX(scale dsx) {
        _sx += dsx;
        setBoundingSphereRadiusRate(SC_R(MAX3(_sx,_sy,_sz)));
    }
    virtual void addScaleY(scale dsy) {
        _sy += dsy;
        setBoundingSphereRadiusRate(SC_R(MAX3(_sx,_sy,_sz)));
    }
    virtual void addScaleZ(scale dsz) {
        _sz += dsz;
        setBoundingSphereRadiusRate(SC_R(MAX3(_sx,_sy,_sz)));
    }
    /**
     * 座標(_x, _y, _z)をコピーして設定 .
     * @param prm_pActor 座標コピー元アクター
     */
    virtual void setPositionAt(const GeometricActor* prm_pActor) {
        _x = prm_pActor->_x;
        _y = prm_pActor->_y;
        _z = prm_pActor->_z;
    }

    /**
     * 指定のアクターと軸Y軸Z軸各軸スケール _sx, _sy, _sz をコピーして設定 .
     * @param prm_pActor 座標コピー元アクター
     */
    virtual void setScaleAt(const GeometricActor* prm_pActor) {
        setScale(prm_pActor->_sx, prm_pActor->_sy, prm_pActor->_sz);
    }

    /**
     * 指定のアクターと同じ座標(_x, _y, _z)をコピーして設定 .
     * @param prm_pGeoElem 座標オブジェクト
     */
    virtual void setPositionAt(const GeoElem* prm_pGeoElem);

    /**
     * 指定のアクターと同じ座標(_x, _y, _z)にランダムな遊びを加算して設定 .
     * @param prm_pActor 座標コピー元アクター
     * @param r 範囲球の半径
     */
    virtual void setPositionAroundAt(const GeometricActor* prm_pActor, coord r);

    /**
     * 指定の座標オブジェクトにランダムな遊びを加算して設定 .
     * @param prm_pGeoElem  座標オブジェクト
     * @param r 範囲球の半径
     */
    virtual void setPositionAroundAt(const GeoElem* prm_pGeoElem, coord r);

    /**
     * 回転角度 _rx, _ry, _rz をコピーして設定 .
     * @param prm_pActor コピー元アクター
     */
    virtual void setFaceAngAs(const GeometricActor* prm_pActor);

    /**
     * 回転角度 _rx, _ry, _rz をコピーして設定 .
     * @param prm_pGeoElem 座標オブジェクト
     */
    virtual void setFaceAngAs(const GeoElem* prm_pGeoElem);

    /**
     * X軸方角のアングル値を設定 .
     * @param prm_face アングル値(-360,000～360,000)
     */
    virtual void setRzFaceAng(angle prm_face);

    /**
     * Y軸方角のアングル値を設定 .
     * @param prm_face アングル値(-360,000～360,000)
     */
    virtual void setRyFaceAng(angle prm_face);

    /**
     * Z軸方角のアングル値を設定 .
     * @param prm_face アングル値(-360,000～360,000)
     */
    virtual void setRxFaceAng(angle prm_face);

    virtual void setRollFaceAng(angle prm_face) {
        setRxFaceAng(prm_face);
    }

    virtual void setRzRyFaceAng(angle prm_rz_face, angle prm_ry_face);

    virtual void addRzFaceAng(angle prm_rz) {
        setRzFaceAng(_rz + prm_rz);
    }

    virtual void addRyFaceAng(angle prm_ry) {
        setRyFaceAng(_ry + prm_ry);
    }

    virtual void addRxFaceAng(angle prm_ang_rx) {
        setRxFaceAng(_rx + prm_ang_rx);
    }

    virtual void addRollFaceAng(angle prm_ang_rx) {
        setRxFaceAng(prm_ang_rx);
    }

    /**
     * Actorの正面方角を設定 .
     * @param prm_axis_x_face X軸方角のアングル値(-360,000～360,000)
     * @param prm_axis_z_face Z軸方角のアングル値(-360,000～360,000)
     * @param prm_axis_y_face Y軸方角のアングル値(-360,000～360,000)
     */
    virtual void setRollPitchYawFaceAng(angle prm_axis_x_face,
                                        angle prm_axis_z_face,
                                        angle prm_axis_y_face) {
        setRxFaceAng(prm_axis_x_face);
        setRzFaceAng(prm_axis_z_face);
        setRyFaceAng(prm_axis_y_face);
    }

    inline void setFaceAngZero() {
        _rx = _rz = _ry = 0;
    }

    /**
     * Actorの自身の座標から対象座標点に向いた方向に、Z軸回転方角とY軸回転方角を設定<BR>
     * @param prm_tx 対象点X座標
     * @param prm_ty 対象点Y座標
     * @param prm_tz 対象点Z座標
     */
    virtual void setFaceAngTwd(coord prm_tx, coord prm_ty, coord prm_tz);

    /**
     * Actorの自身の座標から対象アクターに向いた方向に、Z軸回転方角とY軸回転方角を設定<BR>
     * @param prm_pActor 対象アクター
     */
    virtual void setFaceAngTwd(const GeometricActor* prm_pActor);

    /**
     * 自身の内部ワールド変換(_matWorldRotMv) の逆行列を未計算なら計算し、計算済みならそのまま返す .
     * @return _matInvWorldRotMv
     */
    inline D3DXMATRIX* getInvMatWorldRotMv() {
        if (_was_calculated_matInvWorldRotMv) {
            return &_matInvWorldRotMv;
        } else {
            D3DXMatrixInverse(&_matInvWorldRotMv, nullptr, &_matWorldRotMv);
            _was_calculated_matInvWorldRotMv = true; //processSettlementBehavior()でリセットされる
            return &_matInvWorldRotMv;
        }
    }

    /**
     * 引数のアクターを、自身の子アクターとして追加し、姿勢をフォワードキネマティクスで設定する .
     * 引数の従属アクターは、次の２つのメソッドの使用が可能となります。 <BR>
     * _x,_y,_z,_rx,_ry,_rz をローカル（thisからの相対）に切り替える・・・changeGeoLocal()<BR>
     * _x,_y,_z,_rx,_ry,_rz 絶対座標に切り替える                    ・・・changeGeoFinal()<BR>
     * 【注意】<BR>
     * 力車(getVecVehicle()) は、ローカル座標系でのみ使用可能となります。<BR>
     * 従属アクターprocessBehavior() の処理を抜ける前には、changeGeoFinal() で絶対座標に戻しておく必要があります。<BR>
     * @param prm_kind     種別
     * @param prm_pGeoActor 従属させるアクター
     * @param prm_x_init_local  従属アクターのローカル(this)位置からのX座標位置
     * @param prm_y_init_local  従属アクターのローカル(this)位置からのY座標位置
     * @param prm_z_init_local  従属アクターのローカル(this)位置からのZ座標位置
     * @param prm_rx_init_local 従属アクターのローカル(this)回転からのX軸回転値
     * @param prm_ry_init_local 従属アクターのローカル(this)回転からのY軸回転値
     * @param prm_rz_init_local 従属アクターのローカル(this)回転からのZ軸回転値
     * @return 種別トップの団長
     */
    virtual GgafCore::GroupHead* appendGroupChildAsFk(kind_t prm_kind,
                                                      GeometricActor* prm_pGeoActor,
                                                      int prm_x_init_local,
                                                      int prm_y_init_local,
                                                      int prm_z_init_local,
                                                      int prm_rx_init_local,
                                                      int prm_ry_init_local,
                                                      int prm_rz_init_local);

    /**
     * 引数のアクターを、自身の子アクターとして追加し、姿勢をフォワードキネマティクスで設定する .
     * 引数の従属アクターは、次の２つのメソッドの使用が可能となります。 <BR>
     * _x,_y,_z,_rx,_ry,_rz をローカル（thisからの相対）に切り替える・・・changeGeoLocal()<BR>
     * _x,_y,_z,_rx,_ry,_rz 絶対座標に切り替える                    ・・・changeGeoFinal()<BR>
     * 【注意】<BR>
     * 力車(getVecVehicle()) は、ローカル座標系でのみ使用可能となります。<BR>
     * 従属アクターprocessBehavior() の処理を抜ける前には、changeGeoFinal() で絶対座標に戻しておく必要があります。<BR>
     * @param prm_pGeoActor 従属させるアクター
     * @param prm_x_init_local  従属アクターのローカル(this)位置からのX座標位置
     * @param prm_y_init_local  従属アクターのローカル(this)位置からのY座標位置
     * @param prm_z_init_local  従属アクターのローカル(this)位置からのZ座標位置
     * @param prm_rx_init_local 従属アクターのローカル(this)回転からのX軸回転値
     * @param prm_ry_init_local 従属アクターのローカル(this)回転からのY軸回転値
     * @param prm_rz_init_local 従属アクターのローカル(this)回転からのZ軸回転値
     * @return 種別トップの団長
     */
    virtual GgafCore::GroupHead* appendGroupChildAsFk(GeometricActor* prm_pGeoActor,
                                                      int prm_x_init_local,
                                                      int prm_y_init_local,
                                                      int prm_z_init_local,
                                                      int prm_rx_init_local,
                                                      int prm_ry_init_local,
                                                      int prm_rz_init_local);

    /**
     * 座標と回転 _x,_y,_z,_rx,_ry,_rz を絶対座標系を退避して、ローカル座標(土台からの相対座標)に置き換える .
     */
    void changeGeoLocal();

    /**
     * 座標と回転 _x,_y,_z,_rx,_ry,_rz を退避していた絶対座標に戻す .
     * ローカル座標の変更に伴う絶対座標の更新は、processSettlementBehavior()で行われる作りになっている。<BR>
     * processBehavior() の処理の最後で実行することを想定。<BR>
     * したがって、changeGeoFinal() で座標更新されるわけではないので注意。<BR>
     */
    void changeGeoFinal();

//    void updateGeoFinalFromLocal();

    /**
     * 本アクターが3Dの場合、 回転×移動のワールド変換行列を計算する関数を定義 .
     * 共通処理（ processSettlementBehavior() ）で、拡大縮小はこのワールド変換行列の前に乗じられ、
     * 最終的な行列を完成させる。よって、ワールド変換はデフォルトで、拡大縮小×回転×移動。<BR>
     * 通常の描画可能なアクターは、Util::setWorldMatrix_RxRzRyMv() 等が設定済みのため
     * 呼び出す必要がない。<BR>
     * 描画されないアクターや、ビルボードを行いたい場合等の場合に必要と目論む。<BR>
     * @param prm_pFunc 回転×移動の行列作成関数へのポインタ
     */
    void defineRotMvWorldMatrix(void (*prm_pFunc)(const GeometricActor*, D3DXMATRIX&));

    /**
     * ワールド変換行列を Billboard に設定する .
     * 但し _rz 変化の回転が有効。
     */
    void defineRotMvWorldMatrix_Billboard();

    /**
     * モデルの境界球半径の倍率設定 .
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
    inline void setBoundingSphereRadiusRate(FLOAT prm_rate) {
        _rate_of_bounding_sphere_radius = prm_rate;
    }


    virtual void onEnd() override;

    /**
     * 土台となるアクターを取得 .
     * 土台とは、appendGroupChildAsFk() によって追加された側のオブジェクトが、
     * appendGroupChildAsFk()を実行したアクターを指す。
     * @return 土台となるアクター
     */
    inline GeometricActor* getBaseActor() const {
        return _pActor_base;
    }

    /**
     * デストラクタ
     */
    virtual ~GeometricActor();

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
#endif /*GGAF_DX_GEOMETRICACTOR_H_*/
