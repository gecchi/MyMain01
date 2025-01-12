#ifndef ZAKOKO_H_
#define ZAKOKO_H_
#include "Mogera.h"
#include "jp/ggaf/lib/actor/DefaultMeshSetActor.h"

#include <iostream>
#include <fstream>

namespace Mogera {

/**
 * 敵機雑魚っ子 .
 * @version 1.00
 * @since 2015/02/13
 * @author Masatoshi Tsuge
 */
class Zakoko : public GgafLib::DefaultMeshSetActor {
public:
    std::ofstream* pOs_;

public:
    /**
     * コンストラクタ
     * @param prm_name
     * @return
     */
    Zakoko(const char* prm_name);

    void onCreateModel() override;

    /**
     * 雑魚っ子の初期処理（インスタンス生成後保証）
     */
    void initialize() override;

    /**
     * 雑魚っ子がアクティブになった瞬間の処理 .
     */
    void onActive() override;

    /**
     * 雑魚っ子の振る舞い .
     */
    void processBehavior() override;

    /**
     * 雑魚っ子の振る舞い後の判定処理 .
     */
    void processJudgement() override;

    /**
     * 雑魚っ子の衝突時処理 .
     */
    void onHit(const GgafCore::Checker* prm_pThisHitChecker, const GgafCore::Checker* prm_pOppHitChecker) override;


    void onInactive() override;

    /**
     * 散り散りになる .
     */
    void scatter();


    virtual ~Zakoko();
};

}
#endif /*ZAKOKO_H_*/

