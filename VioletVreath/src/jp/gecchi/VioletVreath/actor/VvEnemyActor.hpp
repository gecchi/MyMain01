#ifndef VVENEMYACTOR_H_
#define VVENEMYACTOR_H_
#include "jp/gecchi/VioletVreath/VioletVreath.h"
#include "VvActor.hpp"
#include "jp/ggaf/core/actor/GroupHead.h"
#include "jp/gecchi/VioletVreath/scene/Spacetime/World/GameScene/GameMainScene/StageWorld/RankUpStageController/RankUpStage.h"
namespace VioletVreath {

template<class T>
class VvEnemyActor : public VvActor<T> {

public:
    VvEnemyActor(const char* prm_name, const char* prm_model, void* prm_pPrm1 = nullptr)
            : VvActor<T>(prm_name, prm_model) {
        T::getStatus()->reset((GgafCore::Status* (*)(GgafCore::Status*))prm_pPrm1);
#ifdef MY_DEBUG
        if (!(T::getDefaultKind() & KIND_ENEMRY)) {
            throwCriticalException("KIND_ENEMRY �ƁA�X�e�[�^�X���قȂ��Ă��܂��Bname="<<prm_name);
        }
#endif
    }

    /**
     * �G�L�����q�b�g���̕W���I�ȏ��� .
     * ���j�󂳂ꂽ�ꍇ��<br>
     * �E�j�󎞓��_���Z<br>
     * �E�����N���Z<br>
     * �E�A�C�e���o��             activateItemOf()<br>
     * �E���Ŏ�����G�t�F�N�g�J�n activateDestroyedEffectOf()<br>
     * �E�ł��Ԃ��e�o��           activateRevengeShotOf()<br>
     * �E�����G�t�F�N�g�o��       activateExplosionEffectOf()<br>
     * �E�ґ��S�Ŕ���<br>
     * �E�ґ��S�Ŏ��A�C�e���o��(STAT_ItemKind)<br>
     * ���j�󂳂�Ȃ������ꍇ��<br>
     * �E�_���[�W��^�������_���Z<br>
     * �E�_���[�W�t���b�V���\��       STAT_FlushAble<br>
     * �E�_���[�W������G�t�F�N�g�o�� activateDamagedEffectOf()<br>
     * @param prm_pOther �q�b�g��������̃A�N�^�[��n��
     * @return true:�j�󂳂ꂽ/false:�j�󂳂�ĂȂ�
     */
    bool performEnemyHit(const GgafDx::GeometricActor* const prm_pOther) {
        GgafCore::Status* pThisStatus  = VvActor<T>::getStatus();
        if (VvActor<T>::calcStamina(prm_pOther) <= 0) { //�̗͂������Ȃ�����
            //���j�󂳂ꂽ�ꍇ��
            VvActor<T>::setHitAble(false); //�����蔻�����
            if (prm_pOther->_pGroupHead->_kind & KIND_MY) {
                //����(���@)�̎�ʂ� MY*** �i���@�֘A�j �Ȃ��
                G_SCORE += pThisStatus->get(STAT_AddDestroyScorePoint);   //�j�󎞓��_
                double rp = pThisStatus->getDouble(STAT_AddRankPoint);    //���Z���������N�l
                if (!ZEROd_EQ(rp)) {
                    double rp_r = pThisStatus->getDouble(STAT_AddRankPoint_Reduction); //���t���[���̃����N�{��
                    if (ZEROd_EQ(rp_r)) { //�{����0.0�Ȃ��
                        //�Ȃɂ����Ȃ�
                    } else if (ONEd_EQ(rp_r)) {
                        G_RANK += rp; //�{����1.0�Ȃ�΁A���̂܂܉��Z���������N�l���v���X
                        if (G_RANK > G_MAX_RANK) {
                            G_RANK = G_MAX_RANK;
                        }
                        if (G_RANK < G_MIN_RANK) {
                            G_RANK = G_MIN_RANK;
                        }
                    } else if (rp_r > 0) {
                        frame n = VvActor<T>::getActiveFrame();   //�ғ��t���[��
                        G_RANK += (rp * pow(rp_r, (double)n)); //rp * (rp_r ^ n)  �����N���Z
                        if (G_RANK > G_MAX_RANK) {
                            G_RANK = G_MAX_RANK;
                        }
                        if (G_RANK < G_MIN_RANK) {
                            G_RANK = G_MIN_RANK;
                        }
                    } else {
                        //�Ȃɂ����Ȃ�
                    }

                }
                VvActor<T>::notifyDestroyedToFormation();     //�ґ��S�Ŕ���ɗL���Ȕj��̂�����ł�����A�ƒʒm
                UTIL::activateItemOf(this);             //�A�C�e���o��
                UTIL::activateDestroyedEffectOf(this);  //���ꂽ�G�t�F�N�g
                GgafCore::Scene* pThisPlatformScene = VvActor<T>::getSceneChief()->getPlatformScene();
                if (pThisPlatformScene->instanceOf(Obj_RankUpStage)) {
                    //�����N�A�b�v�X�e�[�W�̓G�Ȃ�΁A
                    RankUpStage* pRankUpStage = (RankUpStage*)(pThisPlatformScene);
                    pRankUpStage->onDestroyedEnemy(this, prm_pOther);
                }
            }
            UTIL::activateRevengeShotOf(this);     //�ł��Ԃ��e
            UTIL::activateExplosionEffectOf(this); //�����G�t�F�N�g
            return true;
        } else {
            //����j�󎞁A�_���[�W���󂯂��ꍇ��
            if (prm_pOther->_pGroupHead->_kind & KIND_MY) { //����(���@)�̎�ʂ� MY*** �i���@�֘A�j �Ȃ��
                G_SCORE += pThisStatus->get(STAT_AddDamagedScorePoint);   //�_���[�W�����_
            }
            if (pThisStatus->get(STAT_FlushAble)) { //�_���[�W�t���b�V�����邩�ǂ���
                VvActor<T>::effectFlush(2); //�t���b�V���I
            }
            UTIL::activateDamagedEffectOf(this); //�_���[�W�G�t�F�N�g
            return false;
        }
    }

    virtual ~VvEnemyActor() {
    }
};

}

#endif /* VVTEKIACTOR_H_ */
