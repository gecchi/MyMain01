#ifndef SPLINELINEMANAGER_H_
#define SPLINELINEMANAGER_H_
namespace MyStg2nd {

/**
 * Spline �Ǘ��N���X .
 * �����ς� SplineLine �I�u�W�F�N�g��o�^���Ă����A�g���܂킵�܂��B
 * @version 1.00
 * @since 2010/05/31
 * @author Masatoshi Tsuge
 */
class SplineLineManager : public GgafCore::GgafResourceManager<GgafDx9LibStg::SplineLine> {

public:

    /**
     * �R���X�g���N�^
     * @param prm_manager_name �}�l�[�W������(���e�����K�{)
     */
    SplineLineManager(const char* prm_manager_name);

    GgafDx9LibStg::SplineLine* processCreateResource(char* prm_idstr, void* prm_p);

    GgafCore::GgafResourceConnection<GgafDx9LibStg::SplineLine>* processCreateConnection(char* prm_idstr, GgafDx9LibStg::SplineLine* prm_pResource);


    virtual ~SplineLineManager() {
    }
};

}
#endif /*SPLINELINEMANAGER_H_*/