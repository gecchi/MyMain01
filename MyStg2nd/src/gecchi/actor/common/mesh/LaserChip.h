#ifndef LASERCHIP_H_
#define LASERCHIP_H_
namespace MyStg2nd {

class LaserChip : public GgafDx9Core::GgafDx9MeshActor {
    friend class LaserChipDispatcher;
private:
    D3DXHANDLE _hKind, _hX, _hY, _hZ, _hRevPosZ, _hMatWorld_front;


    void processDrawPrior() {
        GgafDx9Core::GgafDx9MeshActor::processDrawPrior();
    }

    void processDrawTerminate();

    /**
     * ＜OverRide です＞
     */
    void processDrawMain();

    /**
     * 出現時コールバック実装
     */
    void onActive();

    /**
     * 消失時コールバック実装
     */
    void onInactive();

public:
    /** 一つ前方のレーザーチップ */
    LaserChip* _pChip_front;
    /** 一つ後方のレーザーチップ */
	LaserChip* _pChip_behind;
	/** レーザーテクスチャ種別  1:末尾 2:中間 3:先頭 （末尾かつ先頭は末尾が優先） */
	int _chiptex_kind;

	/** 自身のWorld変換行列 */
    D3DXMATRIX _matWorld;
    /** 一つ前方のWorld変換行列 */
    D3DXMATRIX _matWorld_front;
    /** 自身を管理してるアクター発送者 */
    LaserChipDispatcher* _pDispatcher;

    GgafDx9LibStg::StgChecker* _pChecker;


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


    virtual ~LaserChip();

};

}
#endif /*LASERCHIP_H_*/

