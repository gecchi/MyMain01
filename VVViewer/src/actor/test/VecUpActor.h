#ifndef VECUPACTOR_H_
#define VECUPACTOR_H_
#include "VVViewer.h"
#include "jp/ggaf/lib/actor/DefaultMeshActor.h"

namespace VVViewer {

/**
 * テスト敵キャラクタ .
 * @version 1.00
 * @since 2014/12/15
 * @author Masatoshi Tsuge
 */
class VecUpActor : public GgafLib::DefaultMeshActor {

public:

    int up_face_no_;
    int up_face_no_prev_;

    /**
     * コンストラクタ
     * @param prm_name
     * @return
     */
    VecUpActor(const char* prm_name);

    /**
     * キャラの初期処理 .
     */
    void initialize() override;

    /**
     * キャラの振る舞い処理 .
     */
    void processBehavior() override;

    virtual ~VecUpActor();
};

}
#endif /*VECUPACTOR_H_*/

