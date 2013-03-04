#ifndef ENEMYSYLVIA_H_
#define ENEMYSYLVIA_H_
namespace VioletVreath {


HASHVAL(SYLVIA_EXPLOSION);

/**
 * �V�����B�A .
 * �ŏ��ɍ�����n�`�V�����B�A
 * @version 1.00
 * @since 2010/05/08
 * @author Masatoshi Tsuge
 */
//class EnemySylvia : public GroundMeshActor {
class EnemySylvia : public GgafLib::CubeMapMeshActor {

public:
    enum {
        PROG_INIT = 1  ,
        PROG_FLOAT_MOVE   ,
        PROG_EXPLOSION    ,
        PROG_NOTHING    ,
    };

    /** �g�[���X�̔��a1(�ւ̔��a) */
    coord r1_;
    /** �g�[���X�̔��a2(�����̔��a) */
    coord r2_;
    int colli_part_num_;

public:
    /**
     * �R���X�g���N�^ .
     * @param prm_name
     * @param prm_model
     * @param prm_r1 �g�[���X�̔��a1(�ւ̔��a)
     * @param prm_r2 �g�[���X�̔��a2(�����̔��a)
     * @return
     */
    EnemySylvia(const char* prm_name, const char* prm_model, coord prm_r1, coord prm_r2);

    virtual void onCreateModel() override;

    virtual void initialize() override;

    virtual void onActive() override;

    virtual void processBehavior() override;

    virtual void processJudgement() override;

    virtual void onHit(GgafCore::GgafActor* prm_pOtherActor) override;

    virtual void onCatchEvent(hashval prm_no, void* prm_pSource) override;

    virtual int isOutOfView() override;

    virtual bool isOutOfUniverse() override {
        if (GgafDxCore::GgafDxUniverse::_X_gone_left < _X) {
            return false;
        } else {
            return true;
        }
    }
    virtual ~EnemySylvia();

protected:
    /**
     * �V�����B�A�̓����蔻��̈���쐬���ݒ肷�� .
     * @param prm_nSphere �����蔻�苅�̐�
     */
    void makeCollisionArea(int prm_nSphere);

    /**
     * �V�����B�A�̕\�ʂɃT�u�{�[����ǉ�
     * @param prm_pGeoActor �ǉ�����A�N�^�[
     * @param prm_angPos1 �ւ̊p�x�ʒu
     * @param prm_angPos2 �֎���̊p�x�ʒu
     */
    void addSubGroupAsFkOnSurface(GgafDxCore::GgafDxGeometricActor* prm_pGeoActor, angle prm_angPos1, angle prm_angPos2);

};

}
#endif /*ENEMYSYLVIA_H_*/

