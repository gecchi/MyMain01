#ifndef GGAF_LIB_DEFAULTSPACETIME_H_
#define GGAF_LIB_DEFAULTSPACETIME_H_
#include "GgafLibCommonHeader.h"
#include "jp/ggaf/dx/scene/Spacetime.h"

#include "jp/ggaf/lib/LibConfig.h"
#include "jp/ggaf/core/util/lineartree/LinearOctreeRounder.hpp"
#include "jp/ggaf/core/util/lineartree/LinearQuadtreeRounder.hpp"
#include "jp/ggaf/lib/actor/camera/DefaultCamera.h"


namespace GgafLib {

//typedef GgafCore::LinearOctreeRounder<GgafCore::Actor> WorldOctreeRounder;
//typedef GgafCore::LinearQuadtreeRounder<GgafCore::Actor> WorldQuadtreeRounder;
//
//typedef GgafCore::LinearQuadtreeRounder<GgafCore::Actor> ViewQuadtreeRounder;
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
    GgafCore::LinearOctree<GgafCore::Actor>* _pWorldLinearOctree;
    GgafCore::LinearOctreeRounder<GgafCore::Actor>* _pWorldOctreeRounder;
    GgafCore::LinearQuadtree<GgafCore::Actor>* _pWorldLinearQuadtree;
    GgafCore::LinearQuadtreeRounder<GgafCore::Actor>* _pWorldQuadtreeRounder;
    GgafCore::LinearQuadtree<GgafCore::Actor>* _pViewLinearQuadtree;
    GgafCore::LinearQuadtreeRounder<GgafCore::Actor>* _pViewQuadtreeRounder;
#ifdef MY_DEBUG
    /** processPreJudgement() ���s�ςݔ��� */
    bool _is_done_processPreJudgement;
#endif

public:
    DefaultSpacetime(const char* prm_name, DefaultCamera* prm_pCamera);

    inline GgafCore::LinearOctree<GgafCore::Actor>* getLinearOctree() {
#ifdef MY_DEBUG
        if (_pWorldLinearOctree == nullptr) {
            throwCriticalException("DefaultSpacetime::getLinearOctree() �����؂͍쐬����Ă��܂���B\n"
                    "IS_HIT_CHECK_3D �v���p�e�B true �ɂ��Ă��������B\n"
                    "���݂�IS_HIT_CHECK_3D="<<CONFIG::IS_HIT_CHECK_3D );
        }
#endif
        return _pWorldLinearOctree;
    }

    inline GgafCore::LinearQuadtree<GgafCore::Actor>* getLinearQuadtree() {
#ifdef MY_DEBUG
        if (_pWorldLinearQuadtree == nullptr) {
            throwCriticalException("DefaultSpacetime::getLinearQuadtree() �l���؂͍쐬����Ă��܂���B IS_HIT_CHECK_2D �v���p�e�B true �ɂ��Ă��������B���݂�IS_HIT_CHECK_2D="<<CONFIG::IS_HIT_CHECK_2D );
        }
#endif
        return _pWorldLinearQuadtree;
    }
    inline GgafCore::LinearQuadtree<GgafCore::Actor>* getViewLinearQuadtree() {
#ifdef MY_DEBUG
        if (_pViewLinearQuadtree == nullptr) {
            throwCriticalException("DefaultSpacetime::getViewLinearQuadtree() �l���؂͍쐬����Ă��܂���B");
        }
#endif
        return _pViewLinearQuadtree;
    }

    /**
     * ���[���h���W��̃A�N�^�[�́u���A�O���[�v �� ���B�O���[�v�v�� �q�b�g�`�F�b�N ���s��  .
     * �R�����i�W���؁j or �Q�����i�S���؁j
     * processJudgement() �ŌĂԕK�v����B�iprocessPreJudgement() �� �c���[�ɓo�^���Ă���ׁj<BR>
     * @param prm_kind_groupA �A�N�^�[���A�O���[�v
     * @param prm_kind_groupB �A�N�^�[���B�O���[�v
     */
    virtual void executeWorldHitCheck(kind_t prm_kind_groupA, kind_t prm_kind_groupB);

    /**
     * �r���[���W��̃A�N�^�[�́u���A�O���[�v �� ���B�O���[�v�v�� �q�b�g�`�F�b�N ���s��  .
     * processJudgement() �ŌĂԕK�v����B�iprocessPreJudgement() �� �c���[�ɓo�^���Ă���ׁj<BR>
     * @param prm_kind_groupA �A�N�^�[���A�O���[�v
     * @param prm_kind_groupB �A�N�^�[���B�O���[�v
     */
    virtual void executeViewHitCheck(kind_t prm_kind_groupA, kind_t prm_kind_groupB);


    virtual DefaultCamera* getCamera() override { //���ς̖߂�l
        return (DefaultCamera*)_pCamera;
    }

    virtual void processPreJudgement() override;

    virtual void processFinal() override;

    virtual ~DefaultSpacetime();
};

}
#endif /*GGAF_LIB_DEFAULTSPACETIME_H_*/
