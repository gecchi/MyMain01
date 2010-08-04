#ifndef GGAFDX9SEREFLECTOR_H_
#define GGAFDX9SEREFLECTOR_H_
namespace GgafDx9Core {

/**
 * �T�E���h�G�t�F�N�g�o�͎x���N���X .
 * @version 1.00
 * @since 2010/04/19
 * @author Masatoshi Tsuge
 */
class GgafDx9SeTransmitter : public GgafCore::GgafObject {

    /** SE�����ڑ� */
    GgafDx9SeConnection** _papSeCon;


public:
    int _se_num;
    GgafDx9GeometricActor* _pActor;
    /**
     * �R���X�g���N�^ .
     */
    GgafDx9SeTransmitter(GgafDx9GeometricActor* prm_pActor);

    void useSe(int prm_se_num);
    void set(int prm_id, const char* prm_se_name, int prm_cannel = 1);
    void play(int prm_id);
    void play3D(int prm_id);
    void updatePanVolume3D();
    void behave();
    /**
     * �f�X�g���N�^
     */
    virtual ~GgafDx9SeTransmitter();
};

}
#endif /*GGAFDX9SEREFLECTOR_H_*/
