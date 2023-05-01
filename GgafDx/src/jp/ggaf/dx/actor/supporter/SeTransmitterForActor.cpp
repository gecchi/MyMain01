#include "jp/ggaf/dx/actor/supporter/SeTransmitterForActor.h"

#include "jp/ggaf/core/util/RepeatSeq.h"
#include "jp/ggaf/dx/Caretaker.h"
#include "jp/ggaf/dx/actor/camera/Camera.h"
#include "jp/ggaf/dx/actor/GeometricActor.h"
#include "jp/ggaf/dx/exception/CriticalException.h"
#include "jp/ggaf/dx/Config.h"
#include "jp/ggaf/dx/manager/SeConnection.h"
#include "jp/ggaf/dx/scene/Spacetime.h"
#include "jp/ggaf/dx/sound/Se.h"
#include "jp/ggaf/dx/util/Util.h"

using namespace GgafDx;

frame SeTransmitterForActor::_se_delay_max_depth = MSEC_F(CONFIG::FRAME_OF_SE_DELAY_MAX_DEPTH);

SeTransmitterForActor::SeTransmitterForActor(GeometricActor* prm_pActor) : SeTransmitter() ,
        _pActor(prm_pActor),
        _px_d_cam_acter_prev(1.0) {
    _playing_3d_freames = 0;
}

void SeTransmitterForActor::set(int prm_se_no, const char* prm_se_key, int prm_cannel) {
    int se_num = _vec_is_playing_3d.size();
    if (prm_se_no >= se_num) {
        for (int i = se_num; i <= prm_se_no; i++) {
            _vec_is_playing_3d.push_back(0);
        }
    }
    SeTransmitter::set(prm_se_no, prm_se_key, prm_cannel);
}

void SeTransmitterForActor::set(int prm_se_no, const char* prm_se_key) {
    std::string ch_key = std::string(prm_se_key) + std::string("_CH");
    if (GgafCore::RepeatSeq::isExist(ch_key)) {
        set(prm_se_no, prm_se_key, GgafCore::RepeatSeq::nextVal(ch_key));
    } else {
        if (GgafCore::Config::_properties.isExistKey(ch_key)) {
            int max_ch_num = GgafCore::Config::_properties.getInt(ch_key);
            GgafCore::RepeatSeq::create(ch_key, 1, max_ch_num);
            set(prm_se_no, prm_se_key, GgafCore::RepeatSeq::nextVal(ch_key));
        } else {
            set(prm_se_no, prm_se_key, 0);
        }
    }
}
void SeTransmitterForActor::play(int prm_se_no, bool prm_can_looping) {
    SeTransmitter::play(prm_se_no, prm_can_looping);
    _vec_is_playing_3d[prm_se_no] = 0;
}

void SeTransmitterForActor::play3D(int prm_se_no, bool prm_can_looping) {
    Spacetime* const pSpacetime = pCARETAKER->getSpacetime();
#ifdef MY_DEBUG
    if (prm_se_no < 0 || prm_se_no >= _se_num) {
        throwCriticalException("ID���͈͊O�ł��B0~"<<(_se_num-1)<<"�ł��肢���܂��B_pActor="<<_pActor->getName()<<" prm_se_no="<<prm_se_no);
    }
#endif
//    static const int VOLUME_RANGE_3D = GGAF_MAX_VOLUME - GGAF_MIN_VOLUME;
    const Camera* const pCam = pSpacetime->getCamera();
    //�����v�Z
    //�x���Ȃ��A����100���̏ꏊ��P_CAM�̏ꏊ�Ƃ���
    //���g��P_CAM�̋���
    const double DX = C_PX(pCam->_x - _pActor->_x);
    const double DY = C_PX(pCam->_y - _pActor->_y);
    const double DZ = C_PX(pCam->_z - _pActor->_z);
    const double px_d = sqrt(DX*DX + DY*DY + DZ*DZ); //d�̓s�N�Z��
    pixcoord px_cam_zf = DX_PX(pCam->getZFar());
    int vol = RCNV(0, px_cam_zf, px_d, GGAF_MAX_VOLUME*1.1, GGAF_MAX_VOLUME * CONFIG::SE_VOLUME_RATE_MAX_DEPTH);
//    int vol =  GGAF_MIN_VOLUME + ((1.0 - (d / (DX_PX(pCam->getZFar())*0.6) )) * VOLUME_RANGE_3D); // 0.6 �͒����␳�A�ŉ��ł�MAX*0.4�{�̉��ʂƂȂ�B
//                                                                                          // �l�����炷�ƁA�����Ă����ʂ����傫���Ȃ�B
    if (GGAF_MAX_VOLUME < vol) {
        vol = GGAF_MAX_VOLUME;
    } else if (GGAF_MIN_VOLUME > vol) {
        vol = GGAF_MIN_VOLUME;
    }

    const dxcoord fDist_VpVerticalCenter  =
            pCam->_plnVerticalCenter.a*_pActor->_fX +
            pCam->_plnVerticalCenter.b*_pActor->_fY +
            pCam->_plnVerticalCenter.c*_pActor->_fZ +
            pCam->_plnVerticalCenter.d;

    const angle ang = UTIL::getAngle2D(fDist_VpVerticalCenter, -_pActor->_dest_from_vppln_infront );
    const float pan = ANG_COS(ang) * 0.95; //0.95�͊��S�ɉE�݈̂����͍��݂̂��畷������̂����ɘa

    int delay = RCNV(0.0, px_cam_zf, px_d, -10, SeTransmitterForActor::_se_delay_max_depth);
//    int delay = (px_d / DX_PX(pCam->getZFar()))*SeTransmitterForActor::_se_delay_max_depth - 10; //10�t���[����グ
//                                                                    //pCam->getZFar() �̓J�����̕\���͈͂̍ŉ�����
//                                                                    //�ŉ��Ɉʒu�����A�N�^�[��SE��SeTransmitterForActor::_se_delay_max_depth�t���[���x���
    if (delay < 0) {
        delay = 0;
    } else if (delay > SeTransmitterForActor::_se_delay_max_depth) {
        delay = SeTransmitterForActor::_se_delay_max_depth;
    }

    float rate_frequency = 1.0; //���t���[���͋߂Â����x���v�Z�ł��Ȃ��̂�1.0
//    if (_pActor->_dest_from_vppln_infront > 0) { //�w��̏ꍇ���g���������A���������������点��B
//        if (_pActor->_dest_from_vppln_infront > PX_DX(800)) {
//            //�w��800px �`
//            rate_frequency = 0.9;
//        } else {
//            //�w��0px �` 800px
//            rate_frequency = 1.0 - (0.1 * (_pActor->_dest_from_vppln_infront / PX_DX(800)));
//        }
//    }

    pSpacetime->registerSe(getSe(prm_se_no), vol, pan, rate_frequency, delay, prm_can_looping, _pActor); // + (Se::VOLUME_RANGE / 6) �͉��ʒ�グ
    _vec_is_playing_3d[prm_se_no] = 1;
    _playing_3d_freames = 0;
    _px_d_cam_acter_prev = px_d;
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
   // _papSe[prm_se_no]->play();
}

void SeTransmitterForActor::updatePanVolume3D() {
//    static const int VOLUME_RANGE_3D = GGAF_MAX_VOLUME - GGAF_MIN_VOLUME;
    bool calc_flg = true; //�ŏ��̂P��ڂ̃��[�v���� true
    float pan = 0.0f;
    int vol = 0;
    float rate_frequency = 1.0;
    const int se_num = _se_num;
    for (int i = 0; i < se_num; i++) {
        Se* pSe = getSe(i);
        //_vec_is_playing_3d[i]�̈Ӗ�
        if (pSe->isPlaying()) {
            if (_vec_is_playing_3d[i] == 1) {
                _vec_is_playing_3d[i] = 2;
            }
        } else {
            if (_vec_is_playing_3d[i] == 1) {
                if (_playing_3d_freames > SeTransmitterForActor::_se_delay_max_depth) {
                    _vec_is_playing_3d[i] = 0;
                }
            } else if (_vec_is_playing_3d[i] == 2) {
                _vec_is_playing_3d[i] = 0;
            }
        }
        if (_vec_is_playing_3d[i] > 0 && pSe->_pActor_last_played == _pActor) {
            if (calc_flg) { //����̂݌v�Z
                calc_flg = false; //�ŏ��̂P��ڂ̃��[�v���������v�Z

                static const Camera* pCam = pCARETAKER->getSpacetime()->getCamera();
                static pixcoord px_cam_zf = DX_PX(pCam->getZFar());
                const double DX = C_PX(pCam->_x - _pActor->_x);
                const double DY = C_PX(pCam->_y - _pActor->_y);
                const double DZ = C_PX(pCam->_z - _pActor->_z);

                //���Y�^
                //�Ⴆ�Ώ��Ŏ��̔����������ꍇ�A_pActor->_x �݂����ɁA���Ō���l���Q�Ƃ������B
                //������ GGAF_END_DELAY ���d�v�ɂȂ��Ă���

                //���A���^�C���̉��ʂ��v�Z
                const double px_d = sqrt(DX*DX + DY*DY + DZ*DZ); //d�̓s�N�Z��

//                        vol =  GGAF_MIN_VOLUME + ((1.0 - (d / (DX_PX(pCam->getZFar())*0.6) )) * VOLUME_RANGE_3D); //0.6 �͒����␳
                vol = RCNV(0, px_cam_zf, px_d, GGAF_MAX_VOLUME*1.1, GGAF_MAX_VOLUME*CONFIG::SE_VOLUME_RATE_MAX_DEPTH);
                //TODO:SeTransmitterForActor::_se_delay_max_depth ���l�ŉ��{�����[���������O�����I
                if (GGAF_MAX_VOLUME < vol) {
                    vol = GGAF_MAX_VOLUME;
                } else if (GGAF_MIN_VOLUME > vol) {
                    vol = GGAF_MIN_VOLUME;
                }

                //���A���^�C���̃p�����v�Z
                const dxcoord fDist_VpVerticalCenter  =
                        pCam->_plnVerticalCenter.a * _pActor->_fX +
                        pCam->_plnVerticalCenter.b * _pActor->_fY +
                        pCam->_plnVerticalCenter.c * _pActor->_fZ +
                        pCam->_plnVerticalCenter.d;
                const angle ang = UTIL::getAngle2D(fDist_VpVerticalCenter, -_pActor->_dest_from_vppln_infront );
                pan = ANG_COS(ang) * 0.95; //0.95�Ӗ��́A���S�ɉE�݈̂����͍��݂̂��畷������̂�����邽��
                                                      //�ō��� 0.05 : 0.95 �̊����ɗ��߂邽�߁B
                //���A���^�C���̎��g�����v�Z
                double px_v = _px_d_cam_acter_prev - px_d; //v���ϑ��҂����Actor���x
                static double px_svos = 1.0 * px_cam_zf / (SeTransmitterForActor::_se_delay_max_depth); //����
                if (ZEROd_EQ(px_svos-px_v)) {
                    rate_frequency = 0.0; //������
                } else {
                    rate_frequency = px_svos / (px_svos-px_v);
                    if (rate_frequency < 0) {
                        rate_frequency = 0.0; //������
                    }
                }
                // �J�����Ƃ̋�����ۑ�
                _px_d_cam_acter_prev = px_d;
            } //����v�Z

            //int delay = RCNV(0.0, px_cam_zf, px_d, -10, SeTransmitterForActor::_se_delay_max_depth);//TODO:�x�点�Ă������R��ݒ�
//            if (strcmp(_pActor->getName(),"SeActor3") == 0) {
//                _TRACE_("pan="<<pan<<"\tvol="<<vol<<"\trate_frequency="<<rate_frequency);
//            }
            pSe->setPan(pan);
            pSe->setVolume(vol);
            pSe->setFrequencyRate(rate_frequency);
        }
    }
}

void SeTransmitterForActor::behave() {
    _playing_3d_freames++;
//    if ((_pActor->_frame_of_life & 1) == 0) {//2���1��
//        //�[���RD�����ʂ̈�2�t���[���ɂP��SE�̊����ʍX�V
        updatePanVolume3D();
//    }
}

SeTransmitterForActor::~SeTransmitterForActor() {
}

