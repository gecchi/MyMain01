#ifndef LASERCHIP_H_
#define LASERCHIP_H_
namespace MyStg2nd {

class LaserChip : public GgafDx9Core::GgafDx9MeshSetActor {
    friend class LaserChipDispatcher;
public:
//    D3DXHANDLE _hKind, _hX, _hY, _hZ, _hRevPosZ;
    D3DXHANDLE _ahKind[8];
//    D3DXHANDLE _ahRevPosZ[8];
    D3DXHANDLE _ahMatWorld_front[8];

    D3DXHANDLE _h_cnt_vertec;

    /** チップの頂点バッファをシェーダーでレンダリングする際にZ座標に-1を乗ずるかどうかのフラグ */
    int _rev_pos_Z;
    /** チップの頂点バッファをシェーダーでレンダリングする際にZ座標を2で割るかどうかのフラグ */
    int _div_pos_Z;

    virtual void processPreDraw() {
        GgafDx9Core::GgafDx9MeshSetActor::processPreDraw();
    }



//    void processAfterDraw();

    /**
     * ＜OverRide です＞
     */
    virtual void processDraw();

    /**
     * 出現時コールバック実装
     */
    virtual void onActive();

    /**
     * 消失時コールバック実装
     */
    virtual void onInactive();


    GgafDx9LibStg::StgChecker* _pStgChecker;

    /** 一つ前方のレーザーチップ */
    LaserChip* _pChip_front;
    /** 一つ後方のレーザーチップ */
    LaserChip* _pChip_behind;
    /** レーザーテクスチャ種別  1:末尾 2:中間 3:先頭 （末尾かつ先頭は末尾が優先） */
    int _chip_kind;

    /** 自身のWorld変換行列 */
    D3DXMATRIX _matWorld;
    /** 一つ前方のWorld変換行列 */
    D3DXMATRIX _matWorld_front;
    /** 自身を管理してるアクター発送者 */
    LaserChipDispatcher* _pDispatcher;



    LaserChip(const char* prm_name, const char* prm_model);

    /**
     * 下位クラスでオーバーライドして下さい。
     */
    virtual void initialize();

    /**
     * 下位クラスでオーバーライドして下さい。
     */
    virtual void processBehavior();

    /**
     * 下位クラスでオーバーライドして下さい。
     */
    virtual void processJudgement();

    /**
     * 下位クラスでオーバーライドして下さい。
     */

    virtual void processHappen(int prm_no) {
    }

    /**
     * 下位クラスでオーバーライドして下さい。
     */
    virtual void processFinal() {
    }

    /**
     * 下位クラスでオーバーライドして下さい。
     */
    virtual void processOnHit(GgafCore::GgafActor* prm_pActor_Opponent);

    virtual void drawHitArea();

    virtual ~LaserChip();

};

}
#endif /*LASERCHIP_H_*/

