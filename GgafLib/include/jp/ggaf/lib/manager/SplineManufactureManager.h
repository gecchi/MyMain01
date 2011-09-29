#ifndef SPLINEMANUFACTUREMANAGER_H_
#define SPLINEMANUFACTUREMANAGER_H_
namespace GgafLib {
/**
 * SplineManufacture �Ǘ��N���X .
 * �����ς� SplineManufacture �I�u�W�F�N�g��o�^���Ă����A�g���܂킵�܂��B
 * @version 1.00
 * @since 2010/12/14
 * @author Masatoshi Tsuge
 */
class SplineManufactureManager : public GgafCore::GgafResourceManager<SplineManufacture> {

public:

    /**
     * �R���X�g���N�^
     * @param prm_manager_name �}�l�[�W������(���e�����K�{)
     */
    SplineManufactureManager(const char* prm_manager_name);

    /**
     * �f�|�W�g�������ʕ����񂩂琶���B
     * �{�A�v���̃X�v���C�����W�Z�b�g�̓R�R�ɏW�񂵂悤�Ǝv���Ă���B
     * @param prm_idstr
     * @return SplineManufacture�I�u�W�F�N�g
     */
    SplineManufacture* processCreateResource(char* prm_idstr, void* prm_p);

    GgafCore::GgafResourceConnection<SplineManufacture>* processCreateConnection(char* prm_idstr, SplineManufacture* prm_pResource);

    virtual ~SplineManufactureManager() {
    }
};

}
#endif /*SPLINEMANUFACTUREMANAGER_H_*/
