#ifndef DEFAULTWORLD_H_
#define DEFAULTWORLD_H_
namespace GgafDx9LibStg {

/**
 * �u���E�v�N���X�C���^�[�t�F�C�X.
 * GgafDx9Core::GgafDx9World ���p�����������̃C���^�[�t�F�[�X�ł��B<BR>
 * Ggaf���C�u�����𗘗p����ꍇ�A�{�N���X���p���������������E�N���X���K�v�ł��B<BR>
 */
class DefaultWorld : public GgafDx9Core::GgafDx9World {

public:
    DefaultWorld(const char* prm_name);

    virtual ~DefaultWorld();
};

}
#endif /*DEFAULTWORLD_H_*/
