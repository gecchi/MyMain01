#ifndef ZAKO_H_
#define ZAKO_H_
#include "Mogera.h"
#include "jp/ggaf/lib/actor/DefaultMeshSetActor.h"
#include <iostream>
#include <fstream>

namespace Mogera {

/**
 * 敵機雑魚 .
 * @version 1.00
 * @since 2015/02/12
 * @author Masatoshi Tsuge
 */
class Zako : public GgafLib::DefaultMeshSetActor {

public:
    /** 移動スプラインプログラム */
    GgafDx::VehicleLeader* pVehicleLeader_;

    std::ofstream* pOs_;
public:
    /**
     * コンストラクタ
     * @param prm_name
     * @return
     */
    Zako(const char* prm_name);

    void onCreateModel() override;

    /**
     * 雑魚の初期処理（インスタンス生成後保証）
     */
    void initialize() override;

    /**
     * 雑魚がアクティブになった瞬間の処理 .
     */
    void onActive() override;

    /**
     * 雑魚の振る舞い .
     */
    void processBehavior() override;

    /**
     * 雑魚の振る舞い後の判定処理 .
     */
    void processJudgement() override;

    /**
     * 雑魚の衝突時処理 .
     */
    void onHit(const GgafCore::Checker* prm_pThisHitChecker, const GgafCore::Checker* prm_pOppHitChecker) override;


    void onInactive() override;


    virtual ~Zako();
};

}
#endif /*ZAKO_H_*/

