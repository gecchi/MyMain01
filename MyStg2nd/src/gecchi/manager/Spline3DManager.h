#ifndef SPLINE3DMANAGER_H_
#define SPLINE3DMANAGER_H_
namespace MyStg2nd {

/**
 * Spline �Ǘ��N���X .
 * �����ς� Spline3D �I�u�W�F�N�g��o�^���Ă����A�g���܂킵�܂��B
 * @version 1.00
 * @since 2010/05/31
 * @author Masatoshi Tsuge
 */
class Spline3DManager : public GgafCore::GgafResourceManager<GgafDx9Core::Spline3D> {

public:

    /**
     * �R���X�g���N�^
     * @param prm_manager_name �}�l�[�W������(���e�����K�{)
     */
    Spline3DManager(const char* prm_manager_name);

    GgafDx9Core::Spline3D* processCreateResource(char* prm_idstr, void* prm_p);

    GgafCore::GgafResourceConnection<GgafDx9Core::Spline3D>* processCreateConnection(char* prm_idstr, GgafDx9Core::Spline3D* prm_pResource);


    virtual ~Spline3DManager() {
    }
};

}
#endif /*SPLINE3DMANAGER_H_*/
