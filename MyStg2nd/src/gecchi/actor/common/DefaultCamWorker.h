#ifndef DEFAULTCAMWORKER_H_
#define DEFAULTCAMWORKER_H_


namespace MyStg2nd {

/**
 * �������Ȃ��J�����}�� .
 * @version 1.00
 * @since 2010/10/25
 * @author Masatoshi Tsuge
 */
class DefaultCamWorker : public CameraWorker {

public:

    DefaultCamWorker(const char* prm_name);

    virtual void onPushed() override {
    }

    virtual void onPoped() override {
    }

    virtual ~DefaultCamWorker(); //�f�X�g���N�^
};

}
#endif /*DEFAULTCAMWORKER_H_*/
