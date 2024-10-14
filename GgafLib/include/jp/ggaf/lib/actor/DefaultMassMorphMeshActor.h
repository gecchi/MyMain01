#ifndef GGAF_LIB_DEFAULTMASSMORPHMESHACTOR_H_
#define GGAF_LIB_DEFAULTMASSMORPHMESHACTOR_H_
#include "jp/ggaf/GgafLibCommonHeader.h"
#include "jp/ggaf/dx/actor/MassMorphMeshActor.h"

namespace GgafLib {

/**
 * ���[�t���b�V���A�N�^�[�̋�ۃN���X.
 * GgafDx::MassMorphMeshActor �������������ۃA�N�^�[�ł��B
 * �{�N���X���p�����ăL�����N�^�[���쐬���܂��傤�B<BR>
 * �ȉ��Ɏg�p�\�Ȏx���I�u�W�F�N�g���L���B<BR>
 * <TABLE border=1>
 * <TR bgcolor="#AABBCC"><TH>�I�u�W�F�N�g�ւ̃A�N�Z�X</TH><TH>�T�v</TH><TH>CLASS��</TH></TR>
 * <TR><TD>getPhase()</TD><TD>�t�F�[�Y�Ǘ�</TD><TD>GgafCore::Phase</TD></TR>
 * <TR><TD>getLocusVehicle()</TD><TD>�ړ��ԗ��B�ړ���]�x��</TD><TD>GgafDx::LocusVehicle</TD></TR>
 * <TR><TD>getSeXmtr()</TD><TD>���ʉ������Ǘ�</TD><TD>GgafDx::SeTransmitter</TD></TR>
 * <TR><TD>getMorpher()</TD><TD>���[�t�B���O�x��</TD><TD>GgafDx::Morpher</TD></TR>
 * <TR><TD>getWorldCollisionChecker()</TD><TD>�Փ˔���x��</TD><TD>GgafLib::WorldCollisionChecker3D</TD></TR>
 * </TABLE>
 * @version 1.00
 * @since 2009/05/08
 * @author Masatoshi Tsuge
 */
class DefaultMassMorphMeshActor : public GgafDx::MassMorphMeshActor {

    struct VERTEX_instancedata {
        float _11, _12, _13, _14;   // : TEXCOORD1  World�ϊ��s��A�P�s��
        float _21, _22, _23, _24;   // : TEXCOORD2  World�ϊ��s��A�Q�s��
        float _31, _32, _33, _34;   // : TEXCOORD3  World�ϊ��s��A�R�s��
        float _41, _42, _43, _44;   // : TEXCOORD4  World�ϊ��s��A�S�s��
        float r, g, b, a;           // : TEXCOORD5  �}�e���A���J���[
        //_14 : ���[�t�^�[�Q�b�g1�̏d�݂̒l�����ߍ��܂��B�V�F�[�_�[���Ŏ��o����0�ɏ㏑���B
        //_24 : ���[�t�^�[�Q�b�g2�̏d�݂̒l�����ߍ��܂��B�V�F�[�_�[���Ŏ��o����0�ɏ㏑���B
        //_34 : ���[�t�^�[�Q�b�g3�̏d�݂̒l�����ߍ��܂��B�V�F�[�_�[���Ŏ��o����0�ɏ㏑���B
        //_44 : ���[�t�^�[�Q�b�g4�̏d�݂̒l�����ߍ��܂��B�V�F�[�_�[���Ŏ��o����1�ɏ㏑���B
    };

    static VERTEX_instancedata _aInstancedata[];
    static void createVertexInstanceData(void* prm, GgafDx::MassModel::VertexInstanceDataInfo* out_info);

public:
    /** �Փ˔���x���I�u�W�F�N�g */
    WorldCollisionChecker* _pWorldCollisionChecker;

public:
    DefaultMassMorphMeshActor(const char* prm_name, const char* prm_model);

    virtual void onCreateModel() override {
    }

    virtual void initialize() override {
    }

    virtual void processBehavior() override {
    }

    virtual void processJudgement() override {
    }

    virtual void processDraw() override;

    virtual void onCatchEvent(eventval prm_event_val, void* prm_pSource) override {
    }

    virtual void onHit(const GgafCore::Checker* prm_pOtherChecker, const GgafCore::Actor* prm_pOtherActor) override {
    }

    virtual void drawHitArea() override;

    virtual GgafDx::CollisionChecker* createChecker() override;
    inline WorldCollisionChecker* getWorldCollisionChecker() {
        return _pWorldCollisionChecker;
    }

    virtual ~DefaultMassMorphMeshActor();
};

}
#endif /*GGAF_LIB_DEFAULTMASSMORPHMESHACTOR_H_*/
