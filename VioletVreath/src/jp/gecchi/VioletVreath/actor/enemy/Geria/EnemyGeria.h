#ifndef ENEMYGERIA_H_
#define ENEMYGERIA_H_
#include "VioletVreath.h"
#include "jp/ggaf/lib/actor/DefaultMeshSetActor.h"

namespace VioletVreath {

//�Q���A
class EnemyGeria : public GgafLib::DefaultMeshSetActor {

public:
    enum {
        PROG_INIT  ,
        PROG_ENTRY ,
        PROG_MOVE  ,
        PROG_FIRE  ,
        PROG_LEAVE ,
        PROG_BANPEI,
    };
    enum {
        SE_EXPLOSION,
        SE_FIRE     ,
    };

    /** �t�B�[�h�C���E�t�F�[�h�A�E�g�x�� */
    GgafDxCore::GgafDxAlphaFader* pAFader_;

    int iMovePatternNo_;
    /** �e���ˌ��ʃG�t�F�N�g */
    GgafCore::GgafActorDepository* pDepo_effect_;
    bool will_shot_;
    bool can_Shot_;
    frame frame_when_shot_;
    int max_shots_;
    int shot_num_;
    velo velo_mv_begin_;
    coord migration_length_;
    coord mvd_;

public:
    EnemyGeria(const char* prm_name);

    void onCreateModel() override;

    void initialize() override;

    void onActive() override;

    void processBehavior() override;

    void processJudgement() override;

    void onInactive() override;

    void onHit(const GgafCore::GgafActor* prm_pOtherActor) override;

    virtual ~EnemyGeria();

    void setMigrationLength(coord prm_migration_length) {
        migration_length_ = prm_migration_length;
    }
    static void callbackDispatched(GgafDxCore::GgafDxFigureActor* prm_pDispatched,
                                   int prm_dispatched_seq,
                                   int prm_set_seq);
};

}
#endif /*ENEMYGERIA_H_*/

