#ifndef GGAFLIB_DEFAULTREGULARPOLYGONBOARDACTOR_H_
#define GGAFLIB_DEFAULTREGULARPOLYGONBOARDACTOR_H_
#include "GgafLibCommonHeader.h"
#include "jp/ggaf/dxcore/actor/GgafDxRegularPolygonBoardActor.h"

namespace GgafLib {

/**
 * ���W�ϊ��ς݃X�v���C�g�A�N�^�[�̋�ۃN���X.
 * GgafDxCore::GgafDxBoardActor �������������ۃA�N�^�[�ł��B
 * �{�N���X���p�����ĐF�X��ʕ\�����쐬���܂��傤�B<BR>
 * �ȉ��Ɏg�p�\�Ȏx���I�u�W�F�N�g���L���B<BR>
 * <TABLE border=1>
 * <TR bgcolor="#AABBCC"><TH>�I�u�W�F�N�g�ւ̃A�N�Z�X</TH><TH>�T�v</TH><TH>CLASS��</TH></TR>
 * <TR><TD>getProgress()</TD><TD>�i���Ǘ�</TD><TD>GgafCore::GgafProgress</TD></TR>
 * <TR><TD>getKuroko()</TD><TD>���߁B�ړ��x��(�����ʕ��p��]�@�\��Z����]�̂ݗL��)</TD><TD>GgafDxCore::GgafDxKuroko</TD></TR>
 * <TR><TD>getUvFlipper()</TD><TD>�p���p���A�j���[�V�����x��</TD><TD>GgafDxCore::GgafDxUvFlipper</TD></TR>
 * <TR><TD>getSeTransmitter()</TD><TD>���ʉ������Ǘ�</TD><TD>GgafDxCore::GgafDxSeTransmitter</TD></TR>
 * </TABLE>
 * @version 1.00
 * @since 2018/10/30
 * @author Masatoshi Tsuge
 */
class DefaultRegularPolygonBoardActor : public GgafDxCore::GgafDxRegularPolygonBoardActor {

public:
    DefaultRegularPolygonBoardActor(const char* prm_name, const char* prm_model, GgafCore::GgafStatus* prm_pStat = nullptr);

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

    virtual bool processHitChkLogic(GgafCore::GgafActor* prm_pOtherActor) override {
        return false;
    }

    virtual void onHit(const GgafCore::GgafActor* prm_pOtherActor) override {
    }

    virtual ~DefaultRegularPolygonBoardActor();

};

}
#endif /*GGAFLIB_DEFAULTREGULARPOLYGONBOARDACTOR_H_*/
