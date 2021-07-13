#ifndef FORMATIONDELHEID001_H_
#define FORMATIONDELHEID001_H_
#include "VioletVreath.h"
#include "jp/gecchi/VioletVreath/actor/enemy/Delheid/FormationDelheid.h"

namespace VioletVreath {

/**
 * �G�@�f���w�C�h�p�t�H�[���[�V����001�O���[�v .
 * @version 1.00
 * @since 2013/04/15
 * @author Masatoshi Tsuge
 */
class FormationDelheid001 : public FormationDelheid {

public:
    /** [r]�X�v���C�����I�u�W�F�N�g�����ւ̐ڑ� */
    GgafDx::CurveManufactureConnection* pConn_pCurveManuf_;

    FormationDelheid001(const char* prm_name);

    /**
     * �ґ������o�[�Ƃ��ď��W���ꂽ�u�ԂɌĂяo�����R�[���o�b�N�����A�ݒu���W�ƌ������Z�b�g�B
     * @param pEnemyDelheid ���W���ꂽ�ґ������o�[
     */
    void onCalledUpDelheid(EnemyDelheid* pEnemyDelheid) override;

    /**
     * �X�v���C�����I�u�W�F�N�g���擾 .
     * @return �X�v���C�����I�u�W�F�N�g
     */
    GgafDx::CurveManufacture* getSplManuf() override;

    /**
     * �U�镑������ .
     */
    virtual void processBehavior() override;

    virtual ~FormationDelheid001();
};

}
#endif /*FORMATIONDELHEID001_H_*/
