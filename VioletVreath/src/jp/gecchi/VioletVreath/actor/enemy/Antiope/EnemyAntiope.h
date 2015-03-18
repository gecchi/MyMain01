#ifndef ENEMYANTIOPE_H_
#define ENEMYANTIOPE_H_
#include "VioletVreath.h"
#include "jp/ggaf/lib/actor/DefaultMeshSetActor.h"

#include "jp/ggaf/dxcore/util/GgafDxGeoElem.h"

namespace VioletVreath {

/**
 * 敵機アンティオペ .
 * 物質と反物質の瞬きのようなイメージの動き
 * @version 1.00
 * @since 2013/04/08
 * @author Masatoshi Tsuge
 */
class EnemyAntiope :
    public GgafLib::DefaultMeshSetActor {

public:
    enum {
        SE_EXPLOSION,
    };

    enum {
        PROG_INIT  ,
        PROG_ENTRY ,
        PROG_MOVE01,
        PROG_LEAVE ,
        PROG_RUSH,
        PROG_BANPEI,
    };

    /** フィードイン・フェードアウト支援 */
    GgafDxCore::GgafDxAlphaFader* pAFader_;
    /** 平行移動支援 */
    GgafDxCore::GgafDxAxesMover* pAxsMver_;

    GgafDxCore::GgafDxGeoElem mv_velo_twd_;

    /** 相方 */
    EnemyAntiope* pP_;
public:
    /**
     * コンストラクタ
     * @param prm_name
     * @return
     */
    EnemyAntiope(const char* prm_name, const char* prm_model, GgafCore::GgafStatus* prm_pStat);

    void onCreateModel() override;

    /**
     * アンティオペの初期処理（インスタンス生成後保証）
     */
    void initialize() override;

    /**
     * アンティオペのがアクティブになった瞬間の処理 .
     */
    void onActive() override;

    /**
     * アンティオペの振る舞い .
     */
    void processBehavior() override;

    /**
     * アンティオペの振る舞い後の判定処理 .
     */
    void processJudgement() override;

    /**
     * アンティオペの衝突時処理 .
     * @param prm_pOtherActor 衝突対象
     */
    void onHit(const GgafCore::GgafActor* prm_pOtherActor) override;

    void onInactive() override;

    virtual ~EnemyAntiope();
};

}
#endif /*ENEMYANTIOPE_H_*/

