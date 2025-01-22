#ifndef GGAF_LIB_LASERCHIP_H_
#define GGAF_LIB_LASERCHIP_H_
#include "jp/ggaf/GgafLibCommonHeader.h"
#include "jp/ggaf/dx/actor/MassMeshActor.h"

namespace GgafLib {

/**
 * ポリラインレーザーのチップの基底クラス .
 * ＜注意＞
 * processSettlementBehavior()内の処理により、
 * setHitAble(false); は意味をなしません。
 * 当たり判定を行いたくない場合、
 * registerHitAreaCube_AutoGenMidColli() 等の当たり判定自体を作成しないで下さい。
 * @version 1.00
 * @since 2008/11/24
 * @author Masatoshi Tsuge
 */
class LaserChip : public GgafDx::MassMeshActor {
    friend class WateringLaserChip;
    friend class HomingLaserChip;
    friend class RefractionLaserChip;
    friend class StraightLaserChip;
    friend class NomalLaserChip;
    friend class LaserChipDepository;

public:

    /** onAcive() でリセットされる振る舞い時フレーム数 */
    frame _frame_of_behaving_from_onActive;

    /** 自身を管理してるアクター発送者 */
    LaserChipDepository* _pDepo;
    /** registerHitAreaCube_AutoGenMidColli() メソッドにより登録時の当たり判定立方体の１辺の長さ */
    coord _hitarea_edge_length;
    coord _hitarea_edge_length_harf;
    ucoord _hitarea_edge_length_2;
    coord _hitarea_edge_length_3;
    ucoord _hitarea_edge_length_3_2;
    coord _hitarea_edge_length_6;
    ucoord _hitarea_edge_length_6_2;

    /** 一つ前方のレーザーチップ */
    LaserChip* _pChip_infront;
    /** 一つ後方のレーザーチップ */
    LaserChip* _pChip_behind;

public:

    struct VERTEX_instancedata {
        float _11, _12, _13, _14;   // : TEXCOORD1  World変換行列、１行目 ,  _14 u,v座標の u オフセット（埋め込み,使用時に 0 戻す）
        float _21, _22, _23, _24;   // : TEXCOORD2  World変換行列、２行目 ,  _24 u,v座標の v オフセット（埋め込み,使用時に 0 戻す）
        float _31, _32, _33, _34;   // : TEXCOORD3  World変換行列、３行目
        float _41, _42, _43, _44;   // : TEXCOORD4  World変換行列、４行目

        float _f_11, _f_12, _f_13, _f_14;   // : TEXCOORD5  前方チップWorld変換行列、１行目
        float _f_21, _f_22, _f_23, _f_24;   // : TEXCOORD6  前方チップWorld変換行列、２行目
        float _f_31, _f_32, _f_33, _f_34;   // : TEXCOORD7  前方チップWorld変換行列、３行目
        float _f_41, _f_42, _f_43, _f_44;   // : TEXCOORD8  前方チップWorld変換行列、４行目

        float _chip_kind, _force_alpha, _power, _infront_chip_power;   // : TEXCOORD9  チップ種別、強制α、火力率、前方チップ火力率
    };

    static VERTEX_instancedata _aInstancedata[];
    WorldCollisionChecker* _pWorldCollisionChecker;

    /** レーザーテクスチャ種別  0:不明 1:末尾 2:中間 3:先頭から２番目で先頭のテクスチャ （末尾かつ先頭は末尾が優先） 4:本当の先頭(但し描画できない) */
    int _chip_kind;
    /** [r]強制上書きアルファ値。（出現時は遠方であっても表示させるため) */
    float _force_alpha;
    /** [r]trueならば、前方チップと離れすぎた場合に中間当たり判定自動生成 */
    bool _middle_colli_able;
    /** レーザーチップが画面外であるかの判定に使用 */
    float _rate_of_length;
    /** [r] 火力率、攻撃力に乗じられる値 */
    float _power;

    GgafDx::UvFlipper* _pUvFlipper;
    /** [r]同時フレーム内で複数 dispatch された場合のdispatch数(1 ～)、実際dispatchできたかどうかに関わらず、dispatchN(n) の n が設定される */
    int _n_dispatch_at_once;
    /** [r]同時フレーム内で複数 dispatch された場合の順番 (0 ～ ) */
    int _dispatch_index;


public:
    LaserChip(const char* prm_name, const char* prm_model);

    static bool initStatic(LaserChip* prm_pLaserChip);

    virtual void onActive() override;
    /**
     * 様々な事前処理 .
     * ＜注意＞
     * setHitAble(true);
     * を内部で実行していますので、
     * setHitAble(false);
     * は無意味です。
     */
    virtual void processSettlementBehavior() override;

    virtual void processPreDraw() override;
    virtual void processDraw() override;

    virtual void onInactive() override;

    virtual void drawHitArea() override;
    virtual int isOutOfView() override;
    /**
     * レーザーチップ用当たり判定立方体をセット .
     * レーザーチップ間の距離が離れ、当たり判定のすり抜けを防止するため、<BR>
     * 通常の当たり判定に加え、接続された前方チップとの距離が離れた場合にのみ、<BR>
     * 自動的に中間に当たり判定を自動生成する機能も付与される。<BR>
     * 当たり判定要素数は２つになる。
     * 【注意】<BR>
     * 予めレーザーチップ間の距離が開かず、すり抜けが起こらないとわかっている場合は、<BR>
     * 本メソッドで設定せず、通常 getWorldCollisionChecker()->addCollisionArea(1);<BR>
     * を行ったほうがパフォーマンスが良い。<BR>
     * @param prm_edge_length 当たり判定立方体の１辺
     * @param prm_edge_length_ex 拡張当たり判定立方体の１辺（地形ヒット確認用）
     */
    virtual void registerHitAreaCube_AutoGenMidColli(int prm_edge_length, int prm_edge_length_ex = 0);

    virtual GgafDx::CollisionChecker* createChecker(kind_t prm_kind = 0) override;

    inline WorldCollisionChecker* getWorldCollisionChecker() {
        return _pWorldCollisionChecker;
    }

    /**
     * 自身の一つ前方のレーザーチップを取得 .
     * 取得できる場合は、自身と連結していることとなる。
     * 取得できない場合(戻り値=nullptr)、自身は先頭チップである。
     * @return 一つ前方のレーザーチップ、又は nullptr
     */
    inline LaserChip* getInfrontChip() {
        return _pChip_infront;
    }

    /**
     * 自身の一つ後方のレーザーチップを取得 .
     * 取得できる場合は、自身と連結していることとなる。
     * 取得できない場合(戻り値=nullptr)、自身は末尾チップである。
     * @return 一つ後方のレーザーチップ、又は nullptr
     */
    inline LaserChip* getBehindChip() {
        return _pChip_behind;
    }

    static void createVertexInstanceData(void* prm, GgafDx::MassMeshModel::VertexInstanceDataInfo* out_info);


    /**
     * モデル資源(MassMeshModel/LaserChipインスタンス)を１つ生成して追加する。.
     * 初めて本メソッドを実行すると、内部リストに保持され、そのモデル資源が有効になります。
     * ２回目以降の実行は、生成したモデル資源を内部リストの末尾に追加します。（有効になりません）
     * @param prm_model モデル定義名
     * @return 生成された（＝リストの末尾に追加された）モデル資源
     */
    virtual void addModel(const char* prm_model) override;

    virtual ~LaserChip();

};

}
#endif /*GGAF_LIB_LASERCHIP_H_*/

