#ifndef GGAFDX9BASEACTOR_H_
#define GGAFDX9BASEACTOR_H_
namespace GgafDx9Core {

/**
 * GgafDx9Core���O��Ԃ̊��A�N�^�[�N���X.
 * GgafMainActor���p�����������ł��B<BR>
 * GgafDx9Core���O��ԓ��ł́A���̃N���X�����A�N�^�[�Ƃ��܂��B<BR>
 * @version 1.00
 * @since 2009/09/08
 * @author Masatoshi Tsuge
 */
class GgafDx9BaseActor : public GgafCore::GgafMainActor {

public:

    GgafDx9BaseActor(const char* prm_name);

    virtual ~GgafDx9BaseActor(); //�f�X�g���N�^

};

}
#endif /*GGAFDX9BASEACTOR_H_*/
