#ifndef GGAFLIB_SPRITEMESHACTOR_H_
#define GGAFLIB_SPRITEMESHACTOR_H_
#include "jp/ggaf/dxcore/actor/ex/GgafDxSpriteMeshActor.h"

namespace GgafLib {

/**
 * �e�N�X�`���A�j���[�V�����\���b�V���A�N�^�[�̋�ۃN���X.
 * GgafDxCore::GgafDxSpriteMeshActor �������������ۃA�N�^�[�ł��B
 * �{�N���X���p�����ăL�����N�^�[���쐬���܂��傤�B<BR>
 * �ȉ��Ɏg�p�\�Ȏx���I�u�W�F�N�g���L���B<BR>
 * <TABLE border=1>
 * <TR bgcolor="#AABBCC"><TH>�Q�ƕϐ�</TH><TH>�T�v</TH><TH>CLASS��</TH></TR>
 * <TR><TD>_pProg</TD><TD>�i���Ǘ�</TD><TD>GgafCore::GgafProgress</TD></TR>
 * <TR><TD>_pKrokoA</TD><TD>����A�B�ړ���]�x��</TD><TD>GgafDxCore::GgafDxKurokoA</TD></TR>
 * <TR><TD>_pKrokoB</TD><TD>����B�B�ړ��x��</TD><TD>GgafDxCore::GgafDxKurokoB</TD></TR>
 * <TR><TD>_pAFader</TD><TD>�t�B�[�h�C���E�A�E�g�x��</TD><TD> GgafDxCore::GgafDxAlphaFader</TD></TR>
 * <TR><TD>_pUvFlipper</TD><TD>�e�N�X�`�����[�e�[�V�����x��</TD><TD>GgafDxCore::GgafDxUvFlipper</TD></TR>
 * <TR><TD>_pSeTx</TD><TD>���ʉ������Ǘ�</TD><TD>GgafDxCore::GgafDxSeTransmitter</TD></TR>
 * <TR><TD>_pScaler</TD><TD>�g��k���x��</TD><TD>GgafDxCore::GgafDxScaler</TD></TR>
 * <TR><TD>_pColliChecker</TD><TD>�Փ˔���x��</TD><TD>GgafLib::CollisionChecker3D</TD></TR>
 * </TABLE>
 * @version 1.00
 * @since 2010/02/09
 * @author Masatoshi Tsuge
 */
class SpriteMeshActor : public GgafDxCore::GgafDxSpriteMeshActor {

public:
    /** �g��k���x���I�u�W�F�N�g */
    GgafDxCore::GgafDxScaler* const _pScaler;
    /** �Փ˔���x���I�u�W�F�N�g */
    CollisionChecker3D* _pColliChecker;

public:
    SpriteMeshActor(const char* prm_name, const char* prm_model, GgafCore::GgafStatus* prm_pStat=nullptr);

    virtual void onCreateModel() override {
    }

    virtual void initialize() override {
    }

    virtual void processBehavior() override {
    }

    virtual void processJudgement() override {
    }

    virtual void onCatchEvent(hashval prm_no, void* prm_pSource) override {
    }

    virtual void onHit(GgafCore::GgafActor* prm_pOtherActor) override {
    }

    virtual void drawHitArea() override;


    virtual ~SpriteMeshActor();
};

}
#endif /*GGAFLIB_SPRITEMESHACTOR_H_*/
