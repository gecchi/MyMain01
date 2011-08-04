#ifndef SPLINEPROGRAMMANAGER_H_
#define SPLINEPROGRAMMANAGER_H_
namespace MyStg2nd {

/**
 * Spline �Ǘ��N���X .
 * �����ς� SplineSource �I�u�W�F�N�g��o�^���Ă����A�g���܂킵�܂��B
 * @version 1.00
 * @since 2010/12/14
 * @author Masatoshi Tsuge
 */
class SplineManager : public GgafCore::GgafResourceManager<SplineSource> {

public:

    /**
     * �R���X�g���N�^
     * @param prm_manager_name �}�l�[�W������(���e�����K�{)
     */
    SplineManager(const char* prm_manager_name);

    /**
     * �X�g�A�[�����ʕ����񂩂琶���B
     * �{�A�v���̃X�v���C�����W�Z�b�g�̓R�R�ɏW�񂵂悤�Ǝv���Ă���B
     * @param prm_idstr
     * @return SplineSource�I�u�W�F�N�g
     */
    SplineSource* processCreateResource(char* prm_idstr, void* prm_p);

    GgafCore::GgafResourceConnection<SplineSource>* processCreateConnection(char* prm_idstr, SplineSource* prm_pResource);

    virtual ~SplineManager() {
    }
};

}
#endif /*SPLINEPROGRAMMANAGER_H_*/
