#ifndef TORUS_H_
#define TORUS_H_
namespace MyStg2nd {

/**
 * �n�`�g�[���X .
 * �ŏ��ɍ�����n�`
 * @version 1.00
 * @since 2010/05/08
 * @author Masatoshi Tsuge
 */
//class Torus : public GroundMeshActor {
class Torus : public GgafLib::CubeMapMeshActor {
public:
    /** �g�[���X���a1(��) */
    coord _r1;
    /** �g�[���X���a2(����) */
    coord _r2;

    /**
     * �R���X�g���N�^ .
     * @param prm_name
     * @param prm_model
     * @param prm_r1 �g�[���X���a1(��)
     * @param prm_r2 �g�[���X���a2(�ւ̑���)
     * @return
     */
    Torus(const char* prm_name, const char* prm_model, coord prm_r1, coord prm_r2);

    virtual void onCreateModel() override;

    virtual void onActive() override;

    virtual void processJudgement() override;

    virtual void onHit(GgafCore::GgafActor* prm_pOtherActor) override;

    virtual int isOutOfView() override;

    virtual bool isOutOfUniverse() override {
        if (GgafDxCore::GgafDxUniverse::_X_goneLeft < _X) {
            return false;
        } else {
            return true;
        }
    }
    virtual ~Torus();

protected:
    /**
     * �g�[���X�̓����蔻��̈���쐬���ݒ肷�� .
     * @param prm_nSphere �����蔻�苅�̐�
     */
    void makeCollisionArea(int prm_nSphere);

    /**
     * �g�[���X�̕\�ʂɃT�u�{�[����ǉ�
     * @param prm_pGeoActor �ǉ�����A�N�^�[
     * @param prm_angPos1 �ւ̊p�x�ʒu
     * @param prm_angPos2 �֎���̊p�x�ʒu
     */
    void addSubBoneOnSurface(GgafDxCore::GgafDxGeometricActor* prm_pGeoActor, angle prm_angPos1, angle prm_angPos2);

};

}
#endif /*TORUS_H_*/

