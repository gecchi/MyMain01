#ifndef LASERCHIP_H_
#define LASERCHIP_H_
namespace GgafLib {

/**
 * ポリラインレーザーのチップの基底クラス .
 * @version 1.00
 * @since 2008/11/24
 * @author Masatoshi Tsuge
 */
class LaserChip : public GgafDxCore::GgafDxMeshSetActor {
    friend class WateringLaserChip;
    friend class HomingLaserChip;
    friend class RefractionLaserChip;
    friend class StraightLaserChip;
    friend class LaserChipDepository;
    friend class LaserChipDepositoryStore;

private:
    D3DXHANDLE _ah_kind[11];
    D3DXHANDLE _ah_matWorld_front[11];
    D3DXHANDLE _h_cnt_vertec;


    /** onAcive() でリセットされる振る舞い時フレーム数 */
    frame _frame_of_behaving_from_onActive;

    /** 自身を管理してるアクター発送者 */
    LaserChipDepository* _pDepo;
    /** registHitAreaCube() メソッドにより登録されているかどうか。trueならば、中間当たり判定自動生成機能が使える */
    bool _is_regist_hitarea;
    /** registHitAreaCube() メソッドにより登録時の当たり判定立方体の１辺の長さ */
    int _hitarea_edge_length;
    /** registHitAreaCube() メソッドにより登録時の当たり判定立方体の１辺の長さの半分 */
    int _harf_hitarea_edge_length;

public:


    CollisionChecker* _pColliChecker;

    /** 一つ前方のレーザーチップ */
    LaserChip* _pChip_front;
    /** 一つ後方のレーザーチップ */
    LaserChip* _pChip_behind;
    /** レーザーテクスチャ種別  1:末尾 2:中間 3:先頭から２番目で先頭のテクスチャ （末尾かつ先頭は末尾が優先） 4:本当の先頭(但し描画できない) */
    int _chip_kind;
    /** [r]地形ヒットありチップ(20回に1回) */
    bool _can_chikei_hit;
    /** [r]自身が所属する先端チップ */
    LaserChip* _pLeader;

    LaserChip(const char* prm_name, const char* prm_model, GgafCore::GgafStatus* prm_pStat=NULL);

    virtual void executeHitChk_MeAnd(GgafActor* prm_pOtherActor) override;

    virtual void onActive() override;

    virtual void processSettlementBehavior() override;

    virtual void processPreDraw() override;

    virtual void processDraw() override;

    virtual void onInactive() override;

    virtual void drawHitArea() override;

    virtual void registHitAreaCube(int prm_edge_length);

    virtual ~LaserChip();

};

}
#endif /*LASERCHIP_H_*/

