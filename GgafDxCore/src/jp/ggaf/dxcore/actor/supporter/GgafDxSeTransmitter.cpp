#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDxCore;


GgafDxSeTransmitter::GgafDxSeTransmitter(GgafDxGeometricActor* prm_pActor) :
                                       GgafObject() {
    _pActor = prm_pActor;
    _se_num = 0;
    _papSeCon = NULL;
    _pa_is3D = NULL;
}

void GgafDxSeTransmitter::useSe(int prm_se_num) {
    _se_num = prm_se_num;
    _papSeCon = NEW GgafDxSeConnection*[_se_num];
    _pa_is3D = NEW bool[_se_num];
    for (int i = 0; i < _se_num; i++) {
        _papSeCon[i] = NULL;
        _pa_is3D[i] = false;
    }
}

void GgafDxSeTransmitter::set(int prm_id, const char* prm_se_name, int prm_cannel) {
#ifdef MY_DEBUG
    if (_se_num <= 0) {
        throwGgafCriticalException("GgafDxSeTransmitter::set() useSe�Ŏg�p����Se�������O�ɐ錾���Ă��������B_pActor="<<_pActor->getName()<<" prm_id="<<prm_id);
    }
    if (prm_id < 0 || prm_id >= _se_num) {
        throwGgafCriticalException("GgafDxSeTransmitter::set() ID���͈͊O�ł��B0~"<<(_se_num-1)<<"�ł��肢���܂��B_pActor="<<_pActor->getName()<<" prm_id="<<prm_id);
    }
#endif
    char idstr[129];
    sprintf(idstr, "%d/%s", prm_cannel, prm_se_name);
    _papSeCon[prm_id] = connectSeManager(idstr);
}

void GgafDxSeTransmitter::playImmed(int prm_id) {
#ifdef MY_DEBUG
    if (prm_id < 0 || prm_id >= _se_num) {
        throwGgafCriticalException("GgafDxSeTransmitter::play() ID���͈͊O�ł��B0~"<<(_se_num-1)<<"�ł��肢���܂��B_pActor="<<_pActor->getName()<<" prm_id="<<prm_id);
    }
#endif
    _papSeCon[prm_id]->use()->play(GGAF_MAX_VOLUME, 0.0);
    _pa_is3D[prm_id] = false;
}


void GgafDxSeTransmitter::play(int prm_id) {
#ifdef MY_DEBUG
    if (prm_id < 0 || prm_id >= _se_num) {
        throwGgafCriticalException("GgafDxSeTransmitter::play() ID���͈͊O�ł��B0~"<<(_se_num-1)<<"�ł��肢���܂��B_pActor="<<_pActor->getName()<<" prm_id="<<prm_id);
    }
#endif
    P_UNIVERSE->registSe(_papSeCon[prm_id]->use(), GGAF_MAX_VOLUME, 0.0, 1.0, 0);
    _pa_is3D[prm_id] = false;
}
void GgafDxSeTransmitter::play3D(int prm_id) {
#ifdef MY_DEBUG
    if (prm_id < 0 || prm_id >= _se_num) {
        throwGgafCriticalException("GgafDxSeTransmitter::play3D() ID���͈͊O�ł��B0~"<<(_se_num-1)<<"�ł��肢���܂��B_pActor="<<_pActor->getName()<<" prm_id="<<prm_id);
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
    LONG vol =  VOLUME_MIN_3D + ((1.0 - (d / (pCam->_zf*PX_UNIT*0.6))) * VOLUME_RANGE_3D); // 0.6 �͒����␳�A�ŉ��ł�MAX*0.4�{�̉��ʂƂȂ�B
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

    angle ang = GgafDxUtil::getAngle2D(fDist_VpVerticalCenter, -_pActor->_dest_from_vppln_front );
    float pan = GgafDxUtil::COS[ang/SANG_RATE] * 0.7; //0.7�͊��S�ɉE�݈̂����͍��݂̂��畷������̂�����邽��

    int delay = (d / (pCam->_zf*PX_UNIT))*MAX_SE_DELAY-10; //10�t���[����グ
    if (delay < 0) {
        delay = 0;
    } else if (delay > MAX_SE_DELAY) {
        delay = MAX_SE_DELAY;
    }

    float rate_frequency = 1.0;
    if (_pActor->_dest_from_vppln_front > 0) { //�w��̏ꍇ���g���������A���������������点��B
        if (_pActor->_dest_from_vppln_front > PX2DX(800)) {
            //�w��800px �`
            rate_frequency = 0.9;
        } else {
            //�w��0px �` 800px
            rate_frequency = 1.0 - (0.1 * (_pActor->_dest_from_vppln_front / PX2DX(800)));
        }
    }


    P_UNIVERSE->registSe(_papSeCon[prm_id]->use(), vol, pan, rate_frequency, delay); // + (GgafDxSe::VOLUME_RANGE / 6) �͉��ʒ�グ

    _pa_is3D[prm_id] = true;
    //�^�񒆂���̋���
   //                float dPlnLeft = abs(_dest_from_vppln_left);
   //                float dPlnRight = abs(_dest_from_vppln_right);
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

void GgafDxSeTransmitter::updatePanVolume3D() {
    static const int VOLUME_MAX_3D = GGAF_MAX_VOLUME;
    static const int VOLUME_MIN_3D = GGAF_MIN_VOLUME;
    static const int VOLUME_RANGE_3D = VOLUME_MAX_3D - VOLUME_MIN_3D;
    float pan;
    LONG vol;
    float rate_frequency;
    bool calc_flg = true;
    GgafDxCamera* pCam = P_CAM;
    for (int i = 0; i < _se_num; i++) {
        if (_pa_is3D[i]) {
            if (_papSeCon[i]->use()->isPlaying()) {
                rate_frequency = 1.0;
                if (calc_flg) {
                    calc_flg = false;

                    //�����v�Z
                    //�x���Ȃ��A����100���̏ꏊ��P_CAM�̏ꏊ�Ƃ���
                    //���g��P_CAM�̋���
                    int DX = (pCam->_X - _pActor->_X) / LEN_UNIT;
                    int DY = (pCam->_Y - _pActor->_Y) / LEN_UNIT;
                    int DZ = (pCam->_Z - _pActor->_Z) / LEN_UNIT;

                    //���Y�^
                    //�Ⴆ�Ώ��Ŏ��̔����������ꍇ�A_pActor->_X �݂����ɁA���Ō���l���Q�Ƃ������B
                    //������ GGAF_SAYONARA_DELAY ���d�v�ɂȂ��Ă���

                    //���A���^�C���̉��ʂ��v�Z
                    double d = GgafUtil::sqrt_fast(double(DX*DX + DY*DY + DZ*DZ));
                    vol =  VOLUME_MIN_3D + ((1.0 - (d / (pCam->_zf*PX_UNIT*0.6))) * VOLUME_RANGE_3D); //0.6 �͒����␳
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
                    angle ang = GgafDxUtil::getAngle2D(fDist_VpVerticalCenter, -_pActor->_dest_from_vppln_front );
                    pan = GgafDxUtil::COS[ang/SANG_RATE] * 0.7; //0.7�Ӗ��́A���S�ɉE�݈̂����͍��݂̂��畷������̂�����邽��
                                                                //�ō��� 0.3 : 0.7 �̊����ɗ��߂邽�߁B
                    //���A���^�C���̃p�����v�Z
                    if (_pActor->_dest_from_vppln_front > 0) { //�w��̏ꍇ���g���������A���������������点��B
                        if (_pActor->_dest_from_vppln_front > PX2DX(800)) {
                            //�w��800px �`
                            rate_frequency = 0.9;
                        } else {
                            //�w��0px �` 800px
                            rate_frequency = 1.0 - (0.1 * (_pActor->_dest_from_vppln_front / PX2DX(800)));
                        }
                    }
                    //�[���RD��
                    _papSeCon[i]->use()->setPan(pan);
                    _papSeCon[i]->use()->setVolume(vol);
                    _papSeCon[i]->use()->setFrequencyRate(rate_frequency);
                }
            } else {
                _pa_is3D[i] = false;
            }
        }
    }
}

void GgafDxSeTransmitter::behave() {
    if (_pActor->_frame_of_life % 2 == 0) {
        //�[���RD�����ʂ̈�2�t���[���ɂP��SE�̊����ʍX�V���A
        updatePanVolume3D();

    }
}

GgafDxSeTransmitter::~GgafDxSeTransmitter() {
    for (int i = 0; i < _se_num; i++) {
        if (_papSeCon[i]) {
            _papSeCon[i]->close();
        }
    }
    DELETEARR_POSSIBLE_NULL(_papSeCon);
    DELETEARR_POSSIBLE_NULL(_pa_is3D);
}

