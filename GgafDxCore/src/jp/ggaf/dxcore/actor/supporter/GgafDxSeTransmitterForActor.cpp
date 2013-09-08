#include "stdafx.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxSeTransmitterForActor.h"

#include "jp/ggaf/core/util/GgafRepeatSeq.h"
#include "jp/ggaf/dxcore/actor/GgafDxCamera.h"
#include "jp/ggaf/dxcore/actor/GgafDxGeometricActor.h"
#include "jp/ggaf/dxcore/exception/GgafDxCriticalException.h"
#include "jp/ggaf/dxcore/GgafDxProperties.h"
#include "jp/ggaf/dxcore/manager/GgafDxSeConnection.h"
#include "jp/ggaf/dxcore/scene/GgafDxUniverse.h"
#include "jp/ggaf/dxcore/sound/GgafDxSe.h"
#include "jp/ggaf/dxcore/util/GgafDxUtil.h"

using namespace GgafCore;
using namespace GgafDxCore;

GgafDxSeTransmitterForActor::GgafDxSeTransmitterForActor(GgafDxGeometricActor* prm_pActor) :
        GgafDxSeTransmitter() {
    _pActor = prm_pActor;
    _paBool_is_playing_3d = nullptr;
}

void GgafDxSeTransmitterForActor::declareSeNum(int prm_se_num) {
    GgafDxSeTransmitter::declareSeNum(prm_se_num);
    _paBool_is_playing_3d = NEW bool[_se_num];
    for (int i = 0; i < _se_num; i++) {
        _paBool_is_playing_3d[i] = false;
    }
}

void GgafDxSeTransmitterForActor::set(int prm_id, const char* prm_se_key, int prm_cannel) {
    if (prm_id < 0) {
        throwGgafCriticalException("GgafDxSeTransmitter::set() ID���͈͊O�ł��B���̐��ł��肢���܂��B prm_id="<<prm_id);
    } else if (prm_id >= _se_num) {
        GGAF_DELETEARR_NULLABLE(_paBool_is_playing_3d);
        //declareSeNum ���ČĂяo������邽�߁A_paBool_is_playing_3d �͍Ċm�ۂ����B
    }
    GgafDxSeTransmitter::set(prm_id, prm_se_key, prm_cannel);
}

void GgafDxSeTransmitterForActor::set(int prm_id, const char* prm_se_key) {
    std::string ch_key = std::string(prm_se_key) + "_CH";
    if (GgafRepeatSeq::isExist(ch_key)) {
        set(prm_id, prm_se_key, GgafRepeatSeq::nextVal(ch_key));
    } else {
        if (GgafProperties::isExistKey(ch_key)) {
            int max_ch_num = GgafProperties::getInt(ch_key);
            GgafRepeatSeq::create(ch_key, 1, max_ch_num);
            set(prm_id, prm_se_key, GgafRepeatSeq::nextVal(ch_key));
        } else {
            set(prm_id, prm_se_key, 0);
        }
    }
}
void GgafDxSeTransmitterForActor::play(int prm_id) {
    GgafDxSeTransmitter::play(prm_id);
    _paBool_is_playing_3d[prm_id] = false;
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
    double DX = C_PX(pCam->_X - _pActor->_X);
    double DY = C_PX(pCam->_Y - _pActor->_Y);
    double DZ = C_PX(pCam->_Z - _pActor->_Z);
    double d = sqrt(DX*DX + DY*DY + DZ*DZ); //d�̓s�N�Z��
    int vol =  VOLUME_MIN_3D + ((1.0 - (d / (DX_PX(pCam->_zf)*0.6) )) * VOLUME_RANGE_3D); // 0.6 �͒����␳�A�ŉ��ł�MAX*0.4�{�̉��ʂƂȂ�B
                                                                                          // �l�����炷�ƁA�����Ă����ʂ����傫���Ȃ�B
    if (VOLUME_MAX_3D < vol) {
        vol = VOLUME_MAX_3D;
    } else if (VOLUME_MIN_3D > vol) {
        vol = VOLUME_MIN_3D;
    }

    dxcoord fDist_VpVerticalCenter  =
            pCam->_plnVerticalCenter.a*_pActor->_fX +
            pCam->_plnVerticalCenter.b*_pActor->_fY +
            pCam->_plnVerticalCenter.c*_pActor->_fZ +
            pCam->_plnVerticalCenter.d;

    angle ang = UTIL::getAngle2D(fDist_VpVerticalCenter, -_pActor->_dest_from_vppln_front );
    float pan = ANG_COS(ang) * 0.9; //0.9�͊��S�ɉE�݈̂����͍��݂̂��畷������̂����ɘa

    int delay = (d / (pCam->_zf*PX_UNIT))*PROPERTY::MAX_SE_DELAY-10; //10�t���[����グ
    if (delay < 0) {
        delay = 0;
    } else if (delay > PROPERTY::MAX_SE_DELAY) {
        delay = PROPERTY::MAX_SE_DELAY;
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


    P_UNIVERSE->registerSe(_papSeConnection[prm_id]->peek(), vol, pan, rate_frequency, delay, _pActor); // + (GgafDxSe::VOLUME_RANGE / 6) �͉��ʒ�グ

    _paBool_is_playing_3d[prm_id] = true;
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
    float pan = 0.0f;
    int vol = 0;
    float rate_frequency = 1.0;
    for (int i = 0; i < _se_num; i++) {
        if (_paBool_is_playing_3d[i]) {
            if (_papSeConnection[i]) {
                GgafDxSe* pSe = _papSeConnection[i]->peek();
                if (pSe->isPlaying() && pSe->_pActor_LastPlayed == _pActor) {
                    if (calc_flg) {
                        calc_flg = false;

                        //�����v�Z
                        //�x���Ȃ��A����100���̏ꏊ��P_CAM�̏ꏊ�Ƃ���
                        //���g��P_CAM�̋���
                        double DX = C_PX(pCam->_X - _pActor->_X);
                        double DY = C_PX(pCam->_Y - _pActor->_Y);
                        double DZ = C_PX(pCam->_Z - _pActor->_Z);

                        //���Y�^
                        //�Ⴆ�Ώ��Ŏ��̔����������ꍇ�A_pActor->_X �݂����ɁA���Ō���l���Q�Ƃ������B
                        //������ GGAF_END_DELAY ���d�v�ɂȂ��Ă���

                        //���A���^�C���̉��ʂ��v�Z
                        double d = sqrt(DX*DX + DY*DY + DZ*DZ); //d�̓s�N�Z��
                        vol =  VOLUME_MIN_3D + ((1.0 - (d / (DX_PX(pCam->_zf)*0.6) )) * VOLUME_RANGE_3D); //0.6 �͒����␳

                        if (VOLUME_MAX_3D < vol) {
                            vol = VOLUME_MAX_3D;
                        } else if (VOLUME_MIN_3D > vol) {
                            vol = VOLUME_MIN_3D;
                        }

                        //���A���^�C���̃p�����v�Z
                        dxcoord fDist_VpVerticalCenter  =
                                pCam->_plnVerticalCenter.a*_pActor->_fX +
                                pCam->_plnVerticalCenter.b*_pActor->_fY +
                                pCam->_plnVerticalCenter.c*_pActor->_fZ +
                                pCam->_plnVerticalCenter.d;
                        angle ang = UTIL::getAngle2D(fDist_VpVerticalCenter, -_pActor->_dest_from_vppln_front );
                        pan = ANG_COS(ang) * 0.8; //0.8�Ӗ��́A���S�ɉE�݈̂����͍��݂̂��畷������̂�����邽��
                                                              //�ō��� 0.2 : 0.8 �̊����ɗ��߂邽�߁B
                        //���A���^�C���̃p�����v�Z
                        if (_pActor->_dest_from_vppln_front > 0) { //�w��̏ꍇ���g���������A���������������点��B
                            if (_pActor->_dest_from_vppln_front > PX_DX(800)) {
                                //�w��800px �`
                                rate_frequency = 0.9;
                            } else {
                                //�w��0px �` 800px
//                                rate_frequency = 1.0 - (0.1 * (_pActor->_dest_from_vppln_front / PX_DX(800)));
                                rate_frequency = 1.0 - (0.1 * (_pActor->_dest_from_vppln_front * (1.0 / PX_DX(800))));
                            }
                        }
                    }
                    //�[���RD��
                    pSe->setPan(pan);
                    pSe->setVolume(vol);
                    pSe->setFrequencyRate(rate_frequency);
                } else {
                    _paBool_is_playing_3d[i] = false;
                }
            }
        }
    }
}

void GgafDxSeTransmitterForActor::behave() {
    if (_pActor->_frame_of_life % 2U == 0) {
        //�[���RD�����ʂ̈�2�t���[���ɂP��SE�̊����ʍX�V
        updatePanVolume3D();
    }
}

GgafDxSeTransmitterForActor::~GgafDxSeTransmitterForActor() {
    GGAF_DELETEARR_NULLABLE(_paBool_is_playing_3d);
}

