#ifndef CUBEMAPMESHSETACTOR_H_
#define CUBEMAPMESHSETACTOR_H_
namespace GgafLib {

/**
 * ���}�b�v���b�V���Z�b�g�A�N�^�[ �̋�ۃN���X .
 * GgafDxCore::GgafDxCubeMapMeshSetActor �������������ۃA�N�^�[�ł��B
 * �{�N���X���p�����ăL�����N�^�[���쐬���܂��傤�B<BR>
 * �ȉ��Ɏg�p�\�Ȏx���I�u�W�F�N�g���L���B<BR>
 * <TABLE border=1>
 * <TR bgcolor="#AABBCC"><TH>�Q�ƕϐ�</TH><TH>�T�v</TH><TH>CLASS��</TH></TR>
 * <TR><TD>_pProg</TD><TD>�i���Ǘ�</TD><TD>GgafCore::GgafProgress</TD></TR>
 * <TR><TD>_pKrokoA</TD><TD>���qA�B�ړ���]�x��</TD><TD>GgafDxCore::GgafDxKurokoA</TD></TR>
 * <TR><TD>_pKrokoB</TD><TD>���qB�B�ړ��x��</TD><TD>GgafDxCore::GgafDxKurokoB</TD></TR>
 * <TR><TD>_pScaler</TD><TD>�g��k���x��</TD><TD>GgafDxCore::GgafDxScaler</TD></TR>
 * <TR><TD>_pFader</TD><TD>�t�B�[�h�C���E�A�E�g�x��</TD><TD> GgafDxCore::GgafDxAlphaFader</TD></TR>
 * <TR><TD>_pSeTxer</TD><TD>���ʉ������Ǘ�</TD><TD>GgafDxCore::GgafDxSeTransmitter</TD></TR>
 * <TR><TD>_pScaler</TD><TD>�g��k���x��</TD><TD>GgafDxCore::GgafDxScaler</TD></TR>
 * <TR><TD>_pColliChecker</TD><TD>�Փ˔���x��</TD><TD>GgafLib::CollisionChecker</TD></TR>
 * </TABLE>
 * @version 1.00
 * @since 2010/12/24
 * @author Masatoshi Tsuge
 */
class CubeMapMeshSetActor : public GgafDxCore::GgafDxCubeMapMeshSetActor {

public:
    /** �g��k���x���I�u�W�F�N�g */
    GgafDxCore::GgafDxScaler* _pScaler;
    /** �Փ˔���x���I�u�W�F�N�g */
    CollisionChecker* _pColliChecker;

    CubeMapMeshSetActor(const char* prm_name, const char* prm_model, GgafCore::GgafStatus* prm_pStat=NULL);

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

    virtual ~CubeMapMeshSetActor();
};

}
#endif /*CUBEMAPMESHSETACTOR_H_*/
