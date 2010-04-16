﻿#ifndef LASERCHIP_H_
#define LASERCHIP_H_
namespace MyStg2nd {

/**
 * ポリラインレーザーのチップの基底クラス .
 * @version 1.00
 * @since 2008/11/24
 * @author Masatoshi Tsuge
 */
class LaserChip : public GgafDx9Core::GgafDx9MeshSetActor {
    friend class LaserChipDispatcher;
public:
    D3DXHANDLE _ahKind[16];
    D3DXHANDLE _ahMatWorld_front[16];
    D3DXHANDLE _h_cnt_vertec;

    GgafDx9LibStg::CollisionChecker* _pCollisionChecker;

    /** 一つ前方のレーザーチップ */
    LaserChip* _pChip_front;
    /** 一つ後方のレーザーチップ */
    LaserChip* _pChip_behind;
    /** レーザーテクスチャ種別  1:末尾 2:中間 3:先頭から２番目で先頭のテクスチャ （末尾かつ先頭は末尾が優先） 4:本当の先頭(但し描画できない) */
    int _chip_kind;
    /** 自身を管理してるアクター発送者 */
    LaserChipDispatcher* _pDispatcher;
    /** registHitAreaCube() メソッドにより登録されているかどうか。trueならば、中間当たり判定自動生成昨日が使える */
    bool _is_regist_hitarea;
    /** registHitAreaCube() メソッドにより登録時の当たり判定立方体の１辺の長さ */
    int _hitarea_edge_length;
    /** registHitAreaCube() メソッドにより登録時の当たり判定立方体の１辺の長さの半分 */
    int _harf_hitarea_edge_length;
    /** onAcive() でリセットされる振る舞い時フレーム数 */
    DWORD _frame_of_behaving_from_onActive;

    LaserChip(const char* prm_name, const char* prm_model);

    virtual void onCreateModel() override;

    virtual void initialize() override;

    virtual void onActive() override;

    virtual void processBehavior() override;

    virtual void processPreJudgement() override;

    virtual void processJudgement() override;

    virtual void processDraw() override;

    virtual void processFinal() override {}

    virtual void onInactive() override;

    virtual void processHappen(int prm_no) override {}

    virtual void onHit(GgafCore::GgafActor* prm_pOtherActor) override;

    virtual void drawHitArea() override;

    virtual void registHitAreaCube(int prm_edge_length);

    virtual ~LaserChip();

};

}
#endif /*LASERCHIP_H_*/

