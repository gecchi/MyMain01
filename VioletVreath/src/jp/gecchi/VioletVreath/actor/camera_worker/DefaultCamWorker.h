#ifndef DEFAULTCAMWORKER_H_
#define DEFAULTCAMWORKER_H_


namespace VioletVreath {

/**
 * �������Ȃ��J�����}�� .
 * @version 1.00
 * @since 2010/10/25
 * @author Masatoshi Tsuge
 */
class DefaultCamWorker : public CameraWorker {

public:

    DefaultCamWorker(const char* prm_name);
    virtual void processBehavior() override;
    virtual ~DefaultCamWorker(); //�f�X�g���N�^
};

}
#endif /*DEFAULTCAMWORKER_H_*/
