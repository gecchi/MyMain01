#ifndef LASERCHIP_H_
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

    GgafDx9LibStg::StgChecker* _pStgChecker;

    /** 一つ前方のレーザーチップ */
    LaserChip* _pChip_front;
    /** 一つ後方のレーザーチップ */
    LaserChip* _pChip_behind;
    /** レーザーテクスチャ種別  1:末尾 2:中間 3:先頭から２番目で先頭のテクスチャ （末尾かつ先頭は末尾が優先） 4:本当の先頭(但し描画できない) */
    int _chip_kind;
    /** 自身のWorld変換行列 */
    D3DXMATRIX _matWorld;
    /** 一つ前方のWorld変換行列 */
    D3DXMATRIX _matWorld_front;
    /** 自身を管理してるアクター発送者 */
    LaserChipDispatcher* _pDispatcher;

    DWORD _dwActiveFrame;

    LaserChip(const char* prm_name, const char* prm_model);

    virtual void initialize();

    virtual void processJudgement();

    virtual void processDraw();

    virtual void processFinal() {}

    virtual void onActive();

    virtual void onInactive();

    virtual void processHappen(int prm_no) {}

    virtual void processOnHit(GgafCore::GgafActor* prm_pOtherActor);

    virtual void drawHitArea();

    virtual ~LaserChip();

};

}
#endif /*LASERCHIP_H_*/

