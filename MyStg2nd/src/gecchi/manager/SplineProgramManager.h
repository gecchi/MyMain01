#ifndef SPLINEPROGRAMMANAGER_H_
#define SPLINEPROGRAMMANAGER_H_
namespace MyStg2nd {

/**
 * Spline �Ǘ��N���X .
 * �����ς� GgafDx9SplineProgram �I�u�W�F�N�g��o�^���Ă����A�g���܂킵�܂��B
 * @version 1.00
 * @since 2010/05/31
 * @author Masatoshi Tsuge
 */
class SplineProgramManager : public GgafCore::GgafResourceManager<GgafDx9Core::GgafDx9SplineProgram> {

public:

    /**
     * �R���X�g���N�^
     * @param prm_manager_name �}�l�[�W������(���e�����K�{)
     */
    SplineProgramManager(const char* prm_manager_name);

    /**
     * �f�B�X�p�b�`���[�����ʕ����񂩂琶���B
     * �{�A�v���̃X�v���C�����W�Z�b�g�̓R�R�ɏW�񂵂悤�Ǝv���Ă���B
     * @param prm_idstr
     * @return GgafDx9SplineProgram�I�u�W�F�N�g
     */
    GgafDx9Core::GgafDx9SplineProgram* processCreateResource(char* prm_idstr, void* prm_p);

    GgafCore::GgafResourceConnection<GgafDx9Core::GgafDx9SplineProgram>* processCreateConnection(char* prm_idstr, GgafDx9Core::GgafDx9SplineProgram* prm_pResource);

    virtual ~SplineProgramManager() {
    }
};

}
#endif /*SPLINEPROGRAMMANAGER_H_*/
