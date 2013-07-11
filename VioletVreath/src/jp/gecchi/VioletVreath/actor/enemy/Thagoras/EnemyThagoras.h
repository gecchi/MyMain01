#ifndef ENEMYTHAGORAS_H_
#define ENEMYTHAGORAS_H_
#include "jp/ggaf/lib/actor/DefaultMeshSetActor.h"

#include "jp/ggaf/dxcore/util/GgafDxGeoElem.h"

namespace VioletVreath {

/**
 * 敵機タゴラス .
 * トランジットレベル１
 * @version 1.00
 * @since 2013/07/10
 * @author Masatoshi Tsuge
 */
class EnemyThagoras : public GgafLib::DefaultMeshSetActor {

public:
    enum {
        SE_EXPLOSION ,
    };

    enum {
        PROG_INIT   ,
        PROG_ENTRY  ,
        PROG_MOVE01 ,
        PROG_MOVE02 ,
        PROG_MOVE03 ,
        PROG_MOVE04 ,
    };
    /** [r]出現座標(フォーメーションオブジェクトが設定) */
    GgafDxCore::GgafDxGeoElem entry_pos_;
    /** [r]ウロウロする座標(フォーメーションオブジェクトが設定) */
    GgafDxCore::GgafDxGeoElem hanging_pos_;
    /** [r]退出座標(フォーメーションオブジェクトが設定) */
    GgafDxCore::GgafDxGeoElem leave_pos_;
public:
    /**
     * コンストラクタ
     * @param prm_name
     * @return
     */
    EnemyThagoras(const char* prm_name);

    void onCreateModel() override;

    /**
     * タゴラスの初期処理（インスタンス生成後保証）
     */
    void initialize() override;

    /**
     * タゴラスのがアクティブになった瞬間の処理 .
     */
    void onActive() override;

    /**
     * タゴラスの振る舞い .
     */
    void processBehavior() override;

    /**
     * タゴラスの振る舞い後の判定処理 .
     */
    void processJudgement() override;

    /**
     * タゴラスの衝突時処理 .
     * @param prm_pOtherActor 衝突対象
     */
    void onHit(GgafCore::GgafActor* prm_pOtherActor) override;


    void onInactive() override;


    virtual ~EnemyThagoras();
};

}
#endif /*ENEMYTHAGORAS_H_*/

