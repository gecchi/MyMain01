#ifndef DEFAULTUNIVERSE_H_
#define DEFAULTUNIVERSE_H_
namespace GgafDx9LibStg {

/**
 * �u���̐��v�N���X�C���^�[�t�F�C�X.
 * GgafDx9Core::GgafDx9Universe ���p�����������̃C���^�[�t�F�[�X�ł��B<BR>
 * Ggaf���C�u�����𗘗p����ꍇ�A�{�N���X���p���������������̐��N���X���K�v�ł��B<BR>
 */
class DefaultUniverse : public GgafDx9Core::GgafDx9Universe {

public:

    GgafCore::GgafLinearOctree<StgChecker>* _pLinearOctree;

    DefaultUniverse(const char* prm_name);

    virtual void nextFrame();

    virtual ~DefaultUniverse();
};

}
#endif /*DEFAULTUNIVERSE_H_*/
