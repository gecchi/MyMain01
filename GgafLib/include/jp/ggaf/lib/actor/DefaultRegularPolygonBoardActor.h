#ifndef GGAF_LIB_DEFAULTREGULARPOLYGONBOARDACTOR_H_
#define GGAF_LIB_DEFAULTREGULARPOLYGONBOARDACTOR_H_
#include "GgafLibCommonHeader.h"
#include "jp/ggaf/dx/actor/RegularPolygonBoardActor.h"

namespace GgafLib {

/**
 * ���W�ϊ��ς݃X�v���C�g�A�N�^�[�̋�ۃN���X.
 * GgafDx::BoardActor �������������ۃA�N�^�[�ł��B
 * �{�N���X���p�����ĐF�X��ʕ\�����쐬���܂��傤�B<BR>
 * �ȉ��Ɏg�p�\�Ȏx���I�u�W�F�N�g���L���B<BR>
 * <TABLE border=1>
 * <TR bgcolor="#AABBCC"><TH>�I�u�W�F�N�g�ւ̃A�N�Z�X</TH><TH>�T�v</TH><TH>CLASS��</TH></TR>
 * <TR><TD>getProgress()</TD><TD>�i���Ǘ�</TD><TD>GgafCore::Progress</TD></TR>
 * <TR><TD>getKuroko()</TD><TD>���߁B�ړ��x��(�����ʕ��p��]�@�\��Z����]�̂ݗL��)</TD><TD>GgafDx::Kuroko</TD></TR>
 * <TR><TD>getUvFlipper()</TD><TD>�p���p���A�j���[�V�����x��</TD><TD>GgafDx::UvFlipper</TD></TR>
 * <TR><TD>getSeTransmitter()</TD><TD>���ʉ������Ǘ�</TD><TD>GgafDx::SeTransmitter</TD></TR>
 * </TABLE>
 * @version 1.00
 * @since 2018/10/30
 * @author Masatoshi Tsuge
 */
class DefaultRegularPolygonBoardActor : public GgafDx::RegularPolygonBoardActor {

public:
    DefaultRegularPolygonBoardActor(const char* prm_name, const char* prm_model);

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

    virtual bool processHitChkLogic(GgafCore::Actor* prm_pOtherActor) override {
        return false;
    }

    virtual void onHit(const GgafCore::Actor* prm_pOtherActor) override {
    }

    virtual ~DefaultRegularPolygonBoardActor();

};

}
#endif /*GGAF_LIB_DEFAULTREGULARPOLYGONBOARDACTOR_H_*/