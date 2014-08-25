#ifndef MAGICLVCURSOR_H_
#define MAGICLVCURSOR_H_
#include "VioletVreath.h"
#include "jp/ggaf/lib/actor/DefaultBoardActor.h"

namespace VioletVreath {

/**
 * ���@���[�^�[�̖��@�̃��x���J�[�\����� .
 * @version 1.00
 * @since 2011/12/12
 * @author Masatoshi Tsuge
 */
class MagicLvCursor : public GgafLib::DefaultBoardActor {

public:
    /** �t�B�[�h�C���E�t�F�[�h�A�E�g�x�� */
    GgafDxCore::GgafDxAlphaFader* pAFader_;
    /** �g��k���x���I�u�W�F�N�g */
    GgafDxCore::GgafDxScaler* pScaler_;
    /** [r]�J�[�\���Ώۂ̖��@ */
    Magic* pMagic_;
    /** [r]���@���[�^�[ */
    MagicMeter* pMagicMeter_;
    /** [r]�J�[�\���Ώۂ̖��@�̃C���f�b�N�X�ԍ� */
    int magic_index_;
    /** [r]���ݎw���Ă��郌�x�� */
    int point_lv_;

    /** �ޔ�p */
    coord tmp_y_;
    /** �ޔ�p */
    float tmp_alpha_;
    /** �ړ��ڕWX���W */
    coord tx_;
    /** �ړ��ڕWY���W */
    coord ty_;

public:
    /**
     * �R���X�g���N�^ .
     * @param prm_name ����
     * @param prm_model ���f�����ʖ���
     * @param prm_pMagicMeter ���@���[�^�[
     * @param prm_pMagic �J�[�\���Ώۂ̖��@
     */
    MagicLvCursor(const char* prm_name, const char* prm_model, MagicMeter* prm_pMagicMeter, Magic* prm_pMagic);

    virtual void initialize() override;
    virtual void processBehavior() override;
    virtual void processPreDraw() override;
    virtual void processAfterDraw() override;

    /**
     * �J�[�\�����u���Ɉړ��B
     * @param prm_lv �ړ��惌�x��
     */
    virtual void moveTo(int prm_lv);

    /**
     * �J�[�\�����Ȃ߂炩�Ɉړ��B
     * @param prm_lv �ړ��惌�x��
     * @param prm_target_frames ��₷����(�t���[����)
     * @param prm_p1 �g�b�v�X�s�[�h�ɒB���鎞������
     * @param prm_p2 �������J�n�����ƂȂ鎞������
     */
    virtual void moveSmoothTo(int prm_lv, frame prm_target_frames, float prm_p1, float prm_p2);

    virtual void blink();

    virtual ~MagicLvCursor();
};

}
#endif /*MAGICLVCURSOR_H_*/

