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
    enum {
        PROG_INIT   ,
        PROG_SPLINE ,
        PROG_LEAVE ,
        PROG_BANPEI,
    };

    /** フィードイン・フェードアウト支援 */
    GgafDxCore::GgafDxAlphaFader* pAFader_;
    /** 移動スプラインプログラム */
    GgafLib::SplineKurokoLeader* pKurokoLeader_;

    bool scatter_flg_;

    frame delay_;

    bool is_head_;

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
     * 雑魚のがアクティブになった瞬間の処理 .
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
     * @param prm_pOtherActor 衝突対象
     */
    void onHit(GgafCore::GgafActor* prm_pOtherActor) override;


    void onInactive() override;

    /**
     * 散り散りになる .
     */
    void scatter();


    virtual ~Zako();
};

}
#endif /*ZAKO_H_*/

