#ifndef GGAFLIB_CUBEMAPMORPHMESHACTOR_H_
#define GGAFLIB_CUBEMAPMORPHMESHACTOR_H_
#include "jp/ggaf/dxcore/actor/ex/GgafDxCubeMapMorphMeshActor.h"

namespace GgafLib {

/**
 * ���}�b�v���[�t���b�V���A�N�^�[�̋�ۃN���X .
 * GgafDxCore::GgafDxMorphMeshActor �������������ۃA�N�^�[�ł��B
 * �{�N���X���p�����ăL�����N�^�[���쐬���܂��傤�B<BR>
 * �ȉ��Ɏg�p�\�Ȏx���I�u�W�F�N�g���L���B<BR>
 * <TABLE border=1>
 * <TR bgcolor="#AABBCC"><TH>�Q�ƕϐ�</TH><TH>�T�v</TH><TH>CLASS��</TH></TR>
 * <TR><TD>_pProg</TD><TD>�i���Ǘ�</TD><TD>GgafCore::GgafProgress</TD></TR>
 * <TR><TD>_pKrokoA</TD><TD>���߁B�ړ���]�x��</TD><TD>GgafDxCore::GgafDxKuroko</TD></TR>
 * <TR><TD>_pAFader</TD><TD>�t�B�[�h�C���E�A�E�g�x��</TD><TD> GgafDxCore::GgafDxAlphaFader</TD></TR>
 * <TR><TD>_pSeTx</TD><TD>���ʉ������Ǘ�</TD><TD>GgafDxCore::GgafDxSeTransmitter</TD></TR>
 * <TR><TD>_pScaler</TD><TD>�g��k���x��</TD><TD>GgafDxCore::GgafDxScaler</TD></TR>
 * <TR><TD>_pMorpher</TD><TD>���[�t�B���O�x��</TD><TD>GgafDxCore::GgafDxMorpher</TD></TR>
 * <TR><TD>_pColliChecker</TD><TD>�Փ˔���x��</TD><TD>GgafLib::CollisionChecker3D</TD></TR>
 * </TABLE>
 * @version 1.00
 * @since 2009/05/08
 * @author Masatoshi Tsuge
 */
class CubeMapMorphMeshActor : public GgafDxCore::GgafDxCubeMapMorphMeshActor {

public:
    /** �g��k���x���I�u�W�F�N�g */
    GgafDxCore::GgafDxScaler* const _pScaler;
    /** �Փ˔���x���I�u�W�F�N�g */
    CollisionChecker3D* _pColliChecker;

public:
    CubeMapMorphMeshActor(const char* prm_name, const char* prm_model_id, GgafCore::GgafStatus* prm_pStat=nullptr);

    virtual void onCreateModel() override {
    }

    virtual void initialize() override {
    }

    virtual void processBehavior() override {
    }

    virtual void processJudgement() override {
    }

    virtual void onHit(GgafCore::GgafActor* prm_pOtherActor) override {
    }

    virtual void drawHitArea() override;

    virtual ~CubeMapMorphMeshActor();
};

}
#endif /*GGAFLIB_CUBEMAPMORPHMESHACTOR_H_*/
