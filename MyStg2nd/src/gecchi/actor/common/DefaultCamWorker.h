#ifndef DEFAULTCAMWORKER_H_
#define DEFAULTCAMWORKER_H_


namespace MyStg2nd {

/**
 * �J����.
 * @version 1.00
 * @since 2009/02/12
 * @author Masatoshi Tsuge
 */
class DefaultCamWorker : public CameraWorker {

public:

    DefaultCamWorker(const char* prm_name);

    virtual ~DefaultCamWorker(); //�f�X�g���N�^
};

}
#endif /*DEFAULTCAMWORKER_H_*/
