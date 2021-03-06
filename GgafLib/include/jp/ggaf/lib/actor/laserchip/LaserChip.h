#ifndef GGAF_LIB_LASERCHIP_H_
#define GGAF_LIB_LASERCHIP_H_
#include "GgafLibCommonHeader.h"
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

private:

    /** onAcive() でリセットされる振る舞い時フレーム数 */
    frame _frame_of_behaving_from_onActive;

    /** 自身を管理してるアクター発送者 */
    LaserChipDepository* _pDepo;
    /** registerHitAreaCube_AutoGenMidColli() メソッドにより登録時の当たり判定立方体の１辺の長さ */
    coord _hitarea_edge_length;
    ucoord _hitarea_edge_length_2;
    coord _hitarea_edge_length_3;
    ucoord _hitarea_edge_length_3_2;
    coord _hitarea_edge_length_6;
    ucoord _hitarea_edge_length_6_2;
    /** registerHitAreaCube_AutoGenMidColli() メソッドにより登録時の当たり判定立方体の１辺の長さの半分 */
//    int _harf_hitarea_edge_length;

    /** 一つ前方のレーザーチップ */
    LaserChip* _pChip_infront;
    /** 一つ後方のレーザーチップ */
    LaserChip* _pChip_behind;

public:

    struct VERTEX_instancedata {
        float _11, _12, _13, _14;   // : TEXCOORD1  World変換行列、１行目
        float _21, _22, _23, _24;   // : TEXCOORD2  World変換行列、２行目
        float _31, _32, _33, _34;   // : TEXCOORD3  World変換行列、３行目
        float _41, _42, _43, _44;   // : TEXCOORD4  World変換行列、４行目

        float _f_11, _f_12, _f_13, _f_14;   // : TEXCOORD5  前方チップWorld変換行列、１行目
        float _f_21, _f_22, _f_23, _f_24;   // : TEXCOORD6  前方チップWorld変換行列、２行目
        float _f_31, _f_32, _f_33, _f_34;   // : TEXCOORD7  前方チップWorld変換行列、３行目
        float _f_41, _f_42, _f_43, _f_44;   // : TEXCOORD8  前方チップWorld変換行列、４行目

        float _chip_kind, _force_alpha, _power, _infront_chip_power;   // : TEXCOORD9  チップ種別、強制α、火力率、前方チップ火力率
    };

    static VERTEX_instancedata _aInstancedata[];
    CollisionChecker* _pColliChecker;

    /** レーザーテクスチャ種別  0:不明 1:末尾 2:中間 3:先頭から２番目で先頭のテクスチャ （末尾かつ先頭は末尾が優先） 4:本当の先頭(但し描画できない) */
    int _chip_kind;
    /** [r]強制上書きアルファ値。（出現時は遠方であっても表示させるため) */
    float _force_alpha;
    /** [r]trueならば、前方チップと離れすぎた場合に中間当たり判定自動生成 */
    bool _middle_colli_able;

    float _rate_of_length;
    /** [r] 火力率、攻撃力に乗じられる値 */
    float _power;
public:
    LaserChip(const char* prm_name, const char* prm_model);

    static bool initStatic(LaserChip* prm_pLaserChip);

    virtual void executeHitChk_MeAnd(GgafCore::Actor* prm_pOtherActor) override;

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
     * 本メソッドで設定せず、通常 getCollisionChecker()->createCollisionArea(1);<BR>
     * を行ったほうがパフォーマンスが良い。<BR>
     * @param prm_edge_length
     */
    virtual void registerHitAreaCube_AutoGenMidColli(int prm_edge_length);

    inline CollisionChecker* getCollisionChecker() {
        return _pColliChecker;
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

    virtual ~LaserChip();

};

}
#endif /*GGAF_LIB_LASERCHIP_H_*/

