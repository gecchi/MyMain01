#ifndef GGAFDXBASEACTOR_H_
#define GGAFDXBASEACTOR_H_
namespace GgafDxCore {

/**
 * GgafDxCore���O��Ԃ̊��A�N�^�[�N���X.
 * GgafMainActor���p�����������ł��B<BR>
 * GgafDxCore���O��ԓ��ł́A���̃N���X�����A�N�^�[�Ƃ��܂��B<BR>
 * @version 1.00
 * @since 2009/09/08
 * @author Masatoshi Tsuge
 */
class GgafDxBaseActor : public GgafCore::GgafMainActor {

public:

    GgafDxBaseActor(const char* prm_name, GgafCore::GgafStatus* prm_pStat);

    virtual ~GgafDxBaseActor(); //�f�X�g���N�^

};

}
#endif /*GGAFDXBASEACTOR_H_*/