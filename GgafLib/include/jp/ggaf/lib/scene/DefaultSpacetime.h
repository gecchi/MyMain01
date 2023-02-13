#ifndef GGAF_LIB_DEFAULTSPACETIME_H_
#define GGAF_LIB_DEFAULTSPACETIME_H_
#include "GgafLibCommonHeader.h"
#include "jp/ggaf/dx/scene/Spacetime.h"

#include "jp/ggaf/lib/LibConfig.h"
#include "jp/ggaf/core/util/lineartree/LinearOctreeRounder.hpp"
#include "jp/ggaf/core/util/lineartree/LinearQuadtreeRounder.hpp"
#include "jp/ggaf/lib/actor/camera/DefaultCamera.h"


namespace GgafLib {

typedef GgafCore::LinearOctree<GgafCore::Actor> WorldOctree;
typedef GgafCore::LinearOctreeRounder<GgafCore::Actor> WorldOctreeRounder;
typedef GgafCore::LinearQuadtree<GgafCore::Actor> WorldQuadtree;
typedef GgafCore::LinearQuadtreeRounder<GgafCore::Actor> WorldQuadtreeRounder;

typedef GgafCore::LinearQuadtree<GgafCore::Actor> ViewQuadtree;
typedef GgafCore::LinearQuadtreeRounder<GgafCore::Actor> ViewQuadtreeRounder;

/**
 * �u���̐��v�N���X�C���^�[�t�F�C�X.
 * GgafDx::Spacetime ���p�����������̃C���^�[�t�F�[�X�ł��B<BR>
 * ggaf ���C�u�����𗘗p����ꍇ�A�{�N���X���p���������������̐��N���X���K�v�ł��B<BR>
 * (��DefaultWorld)
 * @version 1.00
 * @since 2008/07/30
 * @author Masatoshi Tsuge
 */
class DefaultSpacetime : public GgafDx::Spacetime {

public:
    static WorldOctree* _pWorldOctree;
    static WorldOctreeRounder* _pWorldOctreeRounder;
    static WorldQuadtree* _pWorldQuadtree;
    static WorldQuadtreeRounder* _pWorldQuadtreeRounder;

    static ViewQuadtree* _pViewQuadtree;
    static ViewQuadtreeRounder* _pViewQuadtreeRounder;
#ifdef MY_DEBUG
    /** processSettlementBehavior() ���s�ςݔ��� */
    bool _is_done_processSettlementBehavior;
#endif

public:
    DefaultSpacetime(const char* prm_name, DefaultCamera* prm_pCamera);

    /**
     * ���[���h���W��̃A�N�^�[�́u���A�O���[�v �� ���B�O���[�v�v�� �q�b�g�`�F�b�N ���s��  .
     * �R�����i�W���؁j or �Q�����i�S���؁j
     * processJudgement() �ŌĂԕK�v����B�iprocessSettlementBehavior() �� �c���[�ɓo�^���Ă���ׁj<BR>
     * @param prm_kind_groupA �A�N�^�[���A�O���[�v
     * @param prm_kind_groupB �A�N�^�[���B�O���[�v
     */
    virtual void executeWorldHitCheck(kind_t prm_kind_groupA, kind_t prm_kind_groupB);

    /**
     * �r���[���W��̃A�N�^�[�́u���A�O���[�v �� ���B�O���[�v�v�� �q�b�g�`�F�b�N ���s��  .
     * processJudgement() �ŌĂԕK�v����B�iprocessSettlementBehavior() �� �c���[�ɓo�^���Ă���ׁj<BR>
     * @param prm_kind_groupA �A�N�^�[���A�O���[�v
     * @param prm_kind_groupB �A�N�^�[���B�O���[�v
     */
    virtual void executeViewHitCheck(kind_t prm_kind_groupA, kind_t prm_kind_groupB);


    virtual DefaultCamera* getCamera() override { //���ς̖߂�l
        return (DefaultCamera*)_pCamera;
    }

    virtual void processSettlementBehavior() override;

    virtual void processJudgement() override;

    virtual void processFinal() override;

    virtual ~DefaultSpacetime();
};

}
#endif /*GGAF_LIB_DEFAULTSPACETIME_H_*/
