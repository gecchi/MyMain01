#ifndef MYTORPEDOTAIL_H_
#define MYTORPEDOTAIL_H_
namespace VioletVreath {

/**
 * �����̈ړ��O�ՃG�t�F�N�g .
 * @version 1.00
 * @since 2010/09/21
 * @author Masatoshi Tsuge
 */
class MyTorpedoTail : public GgafLib::HomingLaserChip {

public:
    /** [r]�O�Ղ�`�����̋����I�u�W�F�N�g */
    MyTorpedo* pTorpedo_;

    /**
     *
     * @param prm_name
     * @param prm_pTorpedo �O�Ղ�`�����̋����I�u�W�F�N�g
     * @return
     */
    MyTorpedoTail(const char* prm_name, MyTorpedo* prm_pTorpedo);

    void initialize() override;

    void onInactive() override;

    void onActive() override;

    /**
     * �擪�`�b�v�̓������` .
     */
    void processBehaviorHeadChip() override;


    virtual ~MyTorpedoTail();

};

}
#endif /*MYTORPEDOTAIL_H_*/
