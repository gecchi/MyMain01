#ifndef GRID26ACTOR_H_
#define GRID26ACTOR_H_
#include "VVViewer.h"
#include "jp/ggaf/lib/actor/DefaultMeshActor.h"

namespace VVViewer {

/**
 * テスト敵キャラクタ .
 * @version 1.00
 * @since 2014/12/15
 * @author Masatoshi Tsuge
 */
class Grid26Actor : public GgafLib::DefaultMeshActor {

public:

    /**
     * コンストラクタ
     * @param prm_name
     * @return
     */
    Grid26Actor(const char* prm_name);

    /**
     * キャラの初期処理 .
     */
    void initialize() override;

    /**
     * キャラの振る舞い処理 .
     */
    void processBehavior() override;

    virtual ~Grid26Actor();
};

}
#endif /*GRID26ACTOR_H_*/

