#ifndef CAMERA_H_
#define CAMERA_H_
namespace SimpleSample {

/**
 * �J�����̐��` .
 * �J�����N���X�͖{�R�[�h�̂悤�� GgafLib::DefaultCamera ��
 * �p�����č쐬���ĉ������B<BR>
 * �u���̐��v���쐬����ۂɁA�����ŃJ�������K�v�ł��B<BR>
 * @version 1.00
 * @since 2012/02/16
 * @author Masatoshi Tsuge
 */
class Camera : public GgafLib::DefaultCamera {

public:
    Camera(const char* prm_name);

    virtual ~Camera();
};

}
#endif /*CAMERA_H_*/
