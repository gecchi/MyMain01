#include "jp/ggaf/dx/actor/supporter/SeTransmitterForActor.h"

#include "jp/ggaf/core/actor/ex/Formation.h"
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

frame SeTransmitterForActor::_se_delay_max_depth = MSEC_F(CONFIG::MILLISEC_OF_SE_DELAY_MAX_DEPTH);

SeTransmitterForActor::SeTransmitterForActor(GeometricActor* prm_pActor) : SeTransmitter() ,
        _pActor(prm_pActor),
        _pFormation(nullptr),
        _px_d_cam_acter_prev(1.0) {
    _playing_3d_freames = 0;
}

SeTransmitterForActor::SeTransmitterForActor(GgafCore::Formation* prm_pFormation) : SeTransmitter() ,
        _pActor(nullptr),
        _pFormation(prm_pFormation),
        _px_d_cam_acter_prev(1.0) {
    _playing_3d_freames = 0;
}

void SeTransmitterForActor::set(t_se_id prm_se_id, const char* prm_se_key, int prm_cannel) {
    SeTransmitter::set(prm_se_id, prm_se_key, prm_cannel);
    _map_is_playing_3d[prm_se_id] = 0;
}

void SeTransmitterForActor::set(t_se_id prm_se_id, const char* prm_se_key) {
    std::string ch_key = std::string(prm_se_key) + std::string("_CH");
    if (GgafCore::RepeatSeq::isExist(ch_key)) {
        set(prm_se_id, prm_se_key, GgafCore::RepeatSeq::nextVal(ch_key));
    } else {
        if (GgafCore::Config::_properties.isExistKey(ch_key)) {
            int max_ch_num = GgafCore::Config::_properties.getInt(ch_key);
            GgafCore::RepeatSeq::create(ch_key, 1, max_ch_num);
            set(prm_se_id, prm_se_key, GgafCore::RepeatSeq::nextVal(ch_key));
        } else {
            set(prm_se_id, prm_se_key, 0);
        }
    }
}

t_se_id SeTransmitterForActor::set(const char* prm_se_key) {
    t_se_id se_id = HASHVAL(prm_se_key);
    set(se_id, prm_se_key);
    return se_id;
}

void SeTransmitterForActor::play(t_se_id prm_se_id, bool prm_can_looping) {
    SeTransmitter::play(prm_se_id, prm_can_looping);
    _map_is_playing_3d[prm_se_id] = 0;
}

void SeTransmitterForActor::play3D(t_se_id prm_se_id, bool prm_can_looping) {
    Spacetime* const pSpacetime = pCARETAKER->getSpacetime();
#ifdef MY_DEBUG
    if (_map_is_playing_3d.find(prm_se_id) == _map_is_playing_3d.end()) {
        throwCriticalException("SeTransmitterForActor::play3D() Se�ԍ������ݒ�ł��Bprm_se_id="<<prm_se_id);
    }
#endif
    if (_pFormation) {
        if (_pFormation->_pLastDestroyedActor) {
            if (_pFormation->_pLastDestroyedActor->instanceOf(Obj_GgafDx_GeometricActor)) {
                _pActor = (GeometricActor*)_pFormation->_pLastDestroyedActor;
            }
        }
        if (!_pActor) {
            _TRACE_("�y�x���z SeTransmitterForActor::play3D() �t�H�[���[�V�����̍ŏI�j��A�N�^�[����SE�𔭐������悤�Ƃ��܂������A�ŏI�j��A�N�^�[������܂���B���������Ȃ��ł��傤���H _pFormation="<<_pFormation->getName()<<"("<<_pFormation<<")");
            return;
        }
    }
    static const int VOLUME_RANGE_3D = GGAF_MAX_VOLUME - GGAF_MIN_VOLUME;
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

    pSpacetime->registerSe(getSe(prm_se_id), vol, pan, rate_frequency, delay, prm_can_looping, _pActor); // + (Se::VOLUME_RANGE / 6) �͉��ʒ�グ
    _map_is_playing_3d[prm_se_id] = 1;
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
   // _papSe[prm_se_id]->play();
}

void SeTransmitterForActor::updatePanVolume3D() {
//    static const int VOLUME_RANGE_3D = GGAF_MAX_VOLUME - GGAF_MIN_VOLUME;
    bool calc_flg = true; //�ŏ��̂P��ڂ̃��[�v���� true
    float pan = 0.0f;
    int vol = 0;
    float rate_frequency = 1.0;
//    const int se_num = _se_num;

    //    for (int i = 0; i < se_num; i++) {
    for (std::map<t_se_id, SeConnection*>::iterator it = _mapSeConnection.begin(); it != _mapSeConnection.end(); ++it) {
        t_se_id se_id = it->first;
        Se* pSe = getSe(se_id);
        //_map_is_playing_3d[se_id]�̈Ӗ�
        if (pSe->isPlaying()) {
            if (_map_is_playing_3d[se_id] == 1) {
                _map_is_playing_3d[se_id] = 2;
            }
        } else {
            if (_map_is_playing_3d[se_id] == 1) {
                if (_playing_3d_freames > SeTransmitterForActor::_se_delay_max_depth) {
                    _map_is_playing_3d[se_id] = 0;
                }
            } else if (_map_is_playing_3d[se_id] == 2) {
                _map_is_playing_3d[se_id] = 0;
            }
        }
        if (_map_is_playing_3d[se_id] > 0 && pSe->_pActor_last_played == _pActor) {
            if (calc_flg) { //����̂݌v�Z
                calc_flg = false; //�ŏ��̂P��ڂ̃��[�v���������v�Z

                static const Camera* pCam = pCARETAKER->getSpacetime()->getCamera();
                static pixcoord px_cam_zf = DX_PX(pCam->getZFar());
                const double DX = C_PX(pCam->_x - _pActor->_x);
                const double DY = C_PX(pCam->_y - _pActor->_y);
                const double DZ = C_PX(pCam->_z - _pActor->_z);

                //���Y�^
                //�Ⴆ�Ώ��Ŏ��̔����������ꍇ�A_pActor->_x �݂����ɁA���Ō���l���Q�Ƃ������B
                //������ CONFIG::END_DELAY_FRAME ���d�v�ɂȂ��Ă���

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
    //�[���RD�����ʂ̊����ʍX�V
    updatePanVolume3D();
}

SeTransmitterForActor::~SeTransmitterForActor() {
}

