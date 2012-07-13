#include "stdafx.h"
using namespace GgafCore;
using namespace GgafDxCore;


GgafDxSeTransmitterForActor::GgafDxSeTransmitterForActor(GgafDxGeometricActor* prm_pActor) :
        GgafDxSeTransmitter() {
    _pActor = prm_pActor;
    _paBool_is_3d = NULL;
}

void GgafDxSeTransmitterForActor::declareSeNum(int prm_se_num) {
    GgafDxSeTransmitter::declareSeNum(prm_se_num);
    _paBool_is_3d = NEW bool[_se_num];
    for (int i = 0; i < _se_num; i++) {
        _paBool_is_3d[i] = false;
    }
}

void GgafDxSeTransmitterForActor::play(int prm_id) {
    GgafDxSeTransmitter::play(prm_id);
    _paBool_is_3d[prm_id] = false;
}

void GgafDxSeTransmitterForActor::play3D(int prm_id) {
#ifdef MY_DEBUG
    if (prm_id < 0 || prm_id >= _se_num) {
        throwGgafCriticalException("GgafDxSeTransmitterForActor::play3D() ID���͈͊O�ł��B0~"<<(_se_num-1)<<"�ł��肢���܂��B_pActor="<<_pActor->getName()<<" prm_id="<<prm_id);
    }
#endif
    static const int VOLUME_MAX_3D = GGAF_MAX_VOLUME;
    static const int VOLUME_MIN_3D = GGAF_MIN_VOLUME;
    static const int VOLUME_RANGE_3D = VOLUME_MAX_3D - VOLUME_MIN_3D;
    GgafDxCamera* pCam = P_CAM;
    //�����v�Z
    //�x���Ȃ��A����100���̏ꏊ��P_CAM�̏ꏊ�Ƃ���
    //���g��P_CAM�̋���
    int DX = (pCam->_X - _pActor->_X) / LEN_UNIT;
    int DY = (pCam->_Y - _pActor->_Y) / LEN_UNIT;
    int DZ = (pCam->_Z - _pActor->_Z) / LEN_UNIT;
    double d = GgafUtil::sqrt_fast(double(DX*DX + DY*DY + DZ*DZ));
    int vol =  VOLUME_MIN_3D + ((1.0 - (d / (pCam->_zf*PX_UNIT*0.6))) * VOLUME_RANGE_3D); // 0.6 �͒����␳�A�ŉ��ł�MAX*0.4�{�̉��ʂƂȂ�B
                                                                                           //�l�����炷�ƁA�����Ă����Ƃ����傫���Ȃ�B
    if (VOLUME_MAX_3D < vol) {
        vol = VOLUME_MAX_3D;
    } else if (VOLUME_MIN_3D > vol) {
        vol = VOLUME_MIN_3D;
    }

    float fDist_VpVerticalCenter  =
            pCam->_plnVerticalCenter.a*_pActor->_fX +
            pCam->_plnVerticalCenter.b*_pActor->_fY +
            pCam->_plnVerticalCenter.c*_pActor->_fZ +
            pCam->_plnVerticalCenter.d;

    angle ang = UTIL::getAngle2D(fDist_VpVerticalCenter, -_pActor->_dest_from_vppln_front );
    float pan = UTIL::COS[ang/SANG_RATE] * 0.7; //0.7�͊��S�ɉE�݈̂����͍��݂̂��畷������̂�����邽��

    int delay = (d / (pCam->_zf*PX_UNIT))*MAX_SE_DELAY-10; //10�t���[����グ
    if (delay < 0) {
        delay = 0;
    } else if (delay > MAX_SE_DELAY) {
        delay = MAX_SE_DELAY;
    }

    float rate_frequency = 1.0;
    if (_pActor->_dest_from_vppln_front > 0) { //�w��̏ꍇ���g���������A���������������点��B
        if (_pActor->_dest_from_vppln_front > PX_DX(800)) {
            //�w��800px �`
            rate_frequency = 0.9;
        } else {
            //�w��0px �` 800px
            rate_frequency = 1.0 - (0.1 * (_pActor->_dest_from_vppln_front / PX_DX(800)));
        }
    }


    P_UNIVERSE->registSe(_papSeCon[prm_id]->fetch(), vol, pan, rate_frequency, delay); // + (GgafDxSe::VOLUME_RANGE / 6) �͉��ʒ�グ

    _paBool_is_3d[prm_id] = true;
    //�^�񒆂���̋���
   //                float dPlnLeft = ABS(_dest_from_vppln_left);
   //                float dPlnRight = ABS(_dest_from_vppln_right);
   //                if (dPlnLeft < dPlnRight) {
   //                    //sin�� = dPlnLeft/d;
   //                    //�� = asin(dPlnLeft/d)
   //                    //X = (_rad_half_fovY - ��)
   //                    //tan X = ���� / d
   //                    //d * tan X = ����
   //                    //d * tan (_rad_half_fovY - ��) = ����
   //                    //d * tan (_rad_half_fovY - asin(dPlnLeft/d)) = ����
   //                    //�{���ɂ������Ȃ���΂����Ȃ��H



   // _papSe[prm_id]->play();
}

void GgafDxSeTransmitterForActor::updatePanVolume3D() {
    static const int VOLUME_MAX_3D = GGAF_MAX_VOLUME;
    static const int VOLUME_MIN_3D = GGAF_MIN_VOLUME;
    static const int VOLUME_RANGE_3D = VOLUME_MAX_3D - VOLUME_MIN_3D;

    bool calc_flg = true;
    GgafDxCamera* pCam = P_CAM;
    float pan;
    int vol;
    float rate_frequency = 1.0;
    for (int i = 0; i < _se_num; i++) {
        if (_papSeCon[i] && _paBool_is_3d[i]) {
            if (_papSeCon[i]->fetch()->isPlaying()) {
                if (calc_flg) {
                    calc_flg = false;

                    //�����v�Z
                    //�x���Ȃ��A����100���̏ꏊ��P_CAM�̏ꏊ�Ƃ���
                    //���g��P_CAM�̋���
                    dxcoord DX = C_DX(pCam->_X - _pActor->_X) / LEN_UNIT;
                    dxcoord DY = C_DX(pCam->_Y - _pActor->_Y) / LEN_UNIT;
                    dxcoord DZ = C_DX(pCam->_Z - _pActor->_Z) / LEN_UNIT;

                    //���Y�^
                    //�Ⴆ�Ώ��Ŏ��̔����������ꍇ�A_pActor->_X �݂����ɁA���Ō���l���Q�Ƃ������B
                    //������ GGAF_SAYONARA_DELAY ���d�v�ɂȂ��Ă���

                    //���A���^�C���̉��ʂ��v�Z
                    dxcoord d = GgafUtil::sqrt_fast(DX*DX + DY*DY + DZ*DZ);
                    vol =  VOLUME_MIN_3D + ((1.0 - (d / (pCam->_zf*PX_UNIT*0.6))) * VOLUME_RANGE_3D); //0.6 �͒����␳

                    vol =  VOLUME_MIN_3D + ( (1.0 - (d / pCam->_zf)) *VOLUME_RANGE_3D); //0.6 �͒����␳

                    if (VOLUME_MAX_3D < vol) {
                        vol = VOLUME_MAX_3D;
                    } else if (VOLUME_MIN_3D > vol) {
                        vol = VOLUME_MIN_3D;
                    }

                    //���A���^�C���̃p�����v�Z
                    float fDist_VpVerticalCenter  =
                            pCam->_plnVerticalCenter.a*_pActor->_fX +
                            pCam->_plnVerticalCenter.b*_pActor->_fY +
                            pCam->_plnVerticalCenter.c*_pActor->_fZ +
                            pCam->_plnVerticalCenter.d;
                    angle ang = UTIL::getAngle2D(fDist_VpVerticalCenter, -_pActor->_dest_from_vppln_front );
                    pan = UTIL::COS[ang/SANG_RATE] * 0.7; //0.7�Ӗ��́A���S�ɉE�݈̂����͍��݂̂��畷������̂�����邽��
                                                          //�ō��� 0.3 : 0.7 �̊����ɗ��߂邽�߁B
                    //���A���^�C���̃p�����v�Z
                    if (_pActor->_dest_from_vppln_front > 0) { //�w��̏ꍇ���g���������A���������������点��B
                        if (_pActor->_dest_from_vppln_front > PX_DX(800)) {
                            //�w��800px �`
                            rate_frequency = 0.9;
                        } else {
                            //�w��0px �` 800px
                            rate_frequency = 1.0 - (0.1 * (_pActor->_dest_from_vppln_front / PX_DX(800)));
                        }
                    }
                }
                //�[���RD��
                _papSeCon[i]->fetch()->setPan(pan);
                _papSeCon[i]->fetch()->setVolume(vol);
                _papSeCon[i]->fetch()->setFrequencyRate(rate_frequency);
            } else {
                _paBool_is_3d[i] = false;
            }
        }
    }
}

void GgafDxSeTransmitterForActor::behave() {
    if (_pActor->_frame_of_life % 2 == 0) {
        //�[���RD�����ʂ̈�2�t���[���ɂP��SE�̊����ʍX�V���A
        updatePanVolume3D();
    }
}

GgafDxSeTransmitterForActor::~GgafDxSeTransmitterForActor() {
    DELETEARR_POSSIBLE_NULL(_paBool_is_3d);
}

