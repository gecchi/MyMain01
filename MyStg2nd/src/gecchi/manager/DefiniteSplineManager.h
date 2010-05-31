#ifndef DEFINITESPLINEMANAGER_H_
#define DEFINITESPLINEMANAGER_H_
namespace MyStg2nd {

/**
 * Spline �Ǘ��N���X .
 * �����ς� GgafDx9Spline3D �I�u�W�F�N�g��o�^���Ă����A�g���܂킵�܂��B
 * @version 1.00
 * @since 2010/05/31
 * @author Masatoshi Tsuge
 */
class DefiniteSplineManager : public GgafCore::GgafResourceManager<GgafDx9Core::GgafDx9Spline3D> {

public:

    /**
     * �R���X�g���N�^
     * @param prm_manager_name �}�l�[�W������(���e�����K�{)
     */
    DefiniteSplineManager(const char* prm_manager_name);

    /**
     * �f�B�X�p�b�`���[�����ʕ����񂩂琶���B
     * �{�A�v���̃X�v���C�����W�Z�b�g�̓R�R�ɏW�񂵂悤�Ǝv���Ă���B
     * @param prm_idstr
     * @return GgafDx9Spline3D�I�u�W�F�N�g
     */
    GgafDx9Core::GgafDx9Spline3D* processCreateResource(char* prm_idstr);

    GgafCore::GgafResourceConnection<GgafDx9Core::GgafDx9Spline3D>* processCreateConnection(char* prm_idstr, GgafDx9Core::GgafDx9Spline3D* prm_pResource);

    virtual ~DefiniteSplineManager() {
    }
};

}
#endif /*GGAFDX9BGMMANAGER_H_*/
