#ifndef ENEMYGERIA_H_
#define ENEMYGERIA_H_
#include "jp/ggaf/lib/actor/DefaultMeshSetActor.h"

namespace VioletVreath {

//�Q���A
class EnemyGeria : public GgafLib::DefaultMeshSetActor {

public:
    enum {
        SE_EXPLOSION,
        SE_FIRE     ,
    };
    /** ���s�ړ��x�� */
    GgafDxCore::GgafDxAxesMover* pAxsMver_;

    int iMovePatternNo_;
    /** �e���ˌ��ʃG�t�F�N�g */
    GgafCore::GgafActorDepository* pDepo_shotEffect_;
    bool do_Shot_;
    bool can_Shot_;
    frame frame_when_shot_;
    int max_shots_;
    int shot_num_;
    velo velo_mv_begin_;

public:
    EnemyGeria(const char* prm_name);

    void onCreateModel() override;

    void initialize() override;

    void onActive() override;

    void processBehavior() override;

    void processJudgement() override;

    void onInactive() override;

    void onHit(GgafCore::GgafActor* prm_pOtherActor) override;

    virtual ~EnemyGeria();

    static void callbackDispatched(GgafDxCore::GgafDxDrawableActor* prm_pDispatched,
                                   int prm_dispatched_seq,
                                   int prm_set_seq);
};

}
#endif /*ENEMYGERIA_H_*/

