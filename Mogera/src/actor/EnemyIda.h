#ifndef ENEMYIDA_H_
#define ENEMYIDA_H_
#include "Mogera.h"

#include <iostream>
#include <fstream>
#include "jp/ggaf/lib/actor/DefaultMeshSetActor.h"

namespace Mogera {

/**
 * 敵機イーダ .
 * スペハリのIDAみたいなんでいこうか。
 * 最初のFKフォーメション。
 * @version 1.00
 * @since 2013/06/18
 * @author Masatoshi Tsuge
 */
class EnemyIda : public GgafLib::DefaultMeshSetActor {

public:
    std::ofstream* pOs_;

    /**
     * コンストラクタ
     * @param prm_name
     * @return
     */
    EnemyIda(const char* prm_name);

    void onCreateModel() override;

    /**
     * イーダの初期処理（インスタンス生成後保証）
     */
    void initialize() override;

    /**
     * イーダがアクティブになった瞬間の処理 .
     */
    void onActive() override;

    /**
     * イーダの振る舞い .
     */
    void processBehavior() override;

    /**
     * イーダの振る舞い後の判定処理 .
     */
    void processJudgement() override;

    void onInactive() override;

    virtual ~EnemyIda();
};

}
#endif /*ENEMYIDA_H_*/

