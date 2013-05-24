#ifndef ENEMYJUNO_H_
#define ENEMYJUNO_H_
#include "jp/ggaf/lib/actor/DefaultMeshSetActor.h"

namespace VioletVreath {

//�W���m�[
class EnemyJuno : public GgafLib::DefaultMeshSetActor {

public:
    enum {
        SE_EXPLOSION,
        SE_FIRE     ,
    };

    int iMovePatternNo_;
    /** �e�X�g�b�N */
    GgafCore::GgafActorDepository* pDepo_Shot_;
    /** �e���ˌ��ʃG�t�F�N�g */
    GgafCore::GgafActorDepository* pDepo_ShotEffect_;
    bool do_Shot_;
    bool can_Shot_;
    frame frame_when_shot_;
    int max_shots_;
    int shot_num_;
    velo velo_mv_begin_;

public:
    EnemyJuno(const char* prm_name);

    void onCreateModel() override;

    void initialize() override;

    void onActive() override;

    void processBehavior() override;

    void processJudgement() override;

    void onInactive() override;

    void onHit(GgafCore::GgafActor* prm_pOtherActor) override;

    virtual ~EnemyJuno();

    /**
     * ���˒e�ݒ� .
     * @param prm_pDepo (GgafDxDrawableActor*)�ɃL���X�g�\�ȃA�N�^�[���T�u�Ɏ��f�|�W�g���̃|�C���^
     */
    void setDepository_Shot(GgafCore::GgafActorDepository* prm_pDepo) {
        pDepo_Shot_ = prm_pDepo;
    }

    static void callbackDispatched(GgafDxCore::GgafDxDrawableActor* prm_pDispatched,
                                   int prm_dispatched_seq,
                                   int prm_set_seq);
};

}
#endif /*ENEMYJUNO_H_*/

