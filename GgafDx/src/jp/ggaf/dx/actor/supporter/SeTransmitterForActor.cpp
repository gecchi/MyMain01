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
        throwCriticalException("SeTransmitterForActor::play3D() Se番号が未設定です。prm_se_id="<<prm_se_id);
    }
#endif
    if (_pFormation) {
        if (_pFormation->_pLastDestroyedActor) {
            if (_pFormation->_pLastDestroyedActor->instanceOf(Obj_GgafDx_GeometricActor)) {
                _pActor = (GeometricActor*)_pFormation->_pLastDestroyedActor;
            }
        }
        if (!_pActor) {
            _TRACE_("【警告】 SeTransmitterForActor::play3D() フォーメーションの最終破壊アクターからSEを発生させようとしましたが、最終破壊アクターがありません。おかしくないでしょうか？ _pFormation="<<_pFormation->getName()<<"("<<_pFormation<<")");
            return;
        }
    }
    static const int VOLUME_RANGE_3D = GGAF_MAX_VOLUME - GGAF_MIN_VOLUME;
    const Camera* const pCam = pSpacetime->getCamera();
    //距離計算
    //遅延なし、音量100％の場所をP_CAMの場所とする
    //自身とP_CAMの距離
    const double DX = C_PX(pCam->_x - _pActor->_x);
    const double DY = C_PX(pCam->_y - _pActor->_y);
    const double DZ = C_PX(pCam->_z - _pActor->_z);
    const double px_d = sqrt(DX*DX + DY*DY + DZ*DZ); //dはピクセル
    pixcoord px_cam_zf = DX_PX(pCam->getZFar());
    int vol = RCNV(0, px_cam_zf, px_d, GGAF_MAX_VOLUME*1.1, GGAF_MAX_VOLUME * CONFIG::SE_VOLUME_RATE_MAX_DEPTH);
//    int vol =  GGAF_MIN_VOLUME + ((1.0 - (d / (DX_PX(pCam->getZFar())*0.6) )) * VOLUME_RANGE_3D); // 0.6 は調整補正、最遠でもMAX*0.4倍の音量となる。
//                                                                                          // 値を減らすと、遠くても音量がより大きくなる。
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
    const float pan = ANG_COS(ang) * 0.95; //0.95は完全に右のみ或いは左のみから聞こえるのをやや緩和

    int delay = RCNV(0.0, px_cam_zf, px_d, -10, SeTransmitterForActor::_se_delay_max_depth);
//    int delay = (px_d / DX_PX(pCam->getZFar()))*SeTransmitterForActor::_se_delay_max_depth - 10; //10フレーム底上げ
//                                                                    //pCam->getZFar() はカメラの表示範囲の最遠距離
//                                                                    //最遠に位置したアクターのSEはSeTransmitterForActor::_se_delay_max_depthフレーム遅れる
    if (delay < 0) {
        delay = 0;
    } else if (delay > SeTransmitterForActor::_se_delay_max_depth) {
        delay = SeTransmitterForActor::_se_delay_max_depth;
    }

    float rate_frequency = 1.0; //初フレームは近づく速度を計算できないので1.0
//    if (_pActor->_dest_from_vppln_infront > 0) { //背後の場合周波数を下げ、音を少しぐぐもらせる。
//        if (_pActor->_dest_from_vppln_infront > PX_DX(800)) {
//            //背後800px ～
//            rate_frequency = 0.9;
//        } else {
//            //背後0px ～ 800px
//            rate_frequency = 1.0 - (0.1 * (_pActor->_dest_from_vppln_infront / PX_DX(800)));
//        }
//    }

    pSpacetime->registerSe(getSe(prm_se_id), vol, pan, rate_frequency, delay, prm_can_looping, _pActor); // + (Se::VOLUME_RANGE / 6) は音量底上げ
    _map_is_playing_3d[prm_se_id] = 1;
    _playing_3d_freames = 0;
    _px_d_cam_acter_prev = px_d;
    //真ん中からの距離
   //                float dPlnLeft = ABS(_dest_from_vppln_left);
   //                float dPlnRight = ABS(_dest_from_vppln_right);
   //                if (dPlnLeft < dPlnRight) {
   //                    //sinθ = dPlnLeft/d;
   //                    //θ = asin(dPlnLeft/d)
   //                    //X = (_rad_half_fovY - θ)
   //                    //tan X = 距離 / d
   //                    //d * tan X = 距離
   //                    //d * tan (_rad_half_fovY - θ) = 距離
   //                    //d * tan (_rad_half_fovY - asin(dPlnLeft/d)) = 距離
   //                    //本当にこうしなければいけない？
   // _papSe[prm_se_id]->play();
}

void SeTransmitterForActor::updatePanVolume3D() {
//    static const int VOLUME_RANGE_3D = GGAF_MAX_VOLUME - GGAF_MIN_VOLUME;
    bool calc_flg = true; //最初の１回目のループだけ true
    float pan = 0.0f;
    int vol = 0;
    float rate_frequency = 1.0;
//    const int se_num = _se_num;

    //    for (int i = 0; i < se_num; i++) {
    for (std::map<t_se_id, SeConnection*>::iterator it = _mapSeConnection.begin(); it != _mapSeConnection.end(); ++it) {
        t_se_id se_id = it->first;
        Se* pSe = getSe(se_id);
        //_map_is_playing_3d[se_id]の意味
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
            if (calc_flg) { //初回のみ計算
                calc_flg = false; //最初の１回目のループだけ距離計算

                static const Camera* pCam = pCARETAKER->getSpacetime()->getCamera();
                static pixcoord px_cam_zf = DX_PX(pCam->getZFar());
                const double DX = C_PX(pCam->_x - _pActor->_x);
                const double DY = C_PX(pCam->_y - _pActor->_y);
                const double DZ = C_PX(pCam->_z - _pActor->_z);

                //備忘録
                //例えば消滅時の爆発だった場合、_pActor->_x みたいに、消滅後も値を参照したい。
                //そこで CONFIG::END_DELAY_FRAME が重要になっている

                //リアルタイムの音量を計算
                const double px_d = sqrt(DX*DX + DY*DY + DZ*DZ); //dはピクセル

//                        vol =  GGAF_MIN_VOLUME + ((1.0 - (d / (DX_PX(pCam->getZFar())*0.6) )) * VOLUME_RANGE_3D); //0.6 は調整補正
                vol = RCNV(0, px_cam_zf, px_d, GGAF_MAX_VOLUME*1.1, GGAF_MAX_VOLUME*CONFIG::SE_VOLUME_RATE_MAX_DEPTH);
                //TODO:SeTransmitterForActor::_se_delay_max_depth 同様最遠ボリューム割合を外だし！
                if (GGAF_MAX_VOLUME < vol) {
                    vol = GGAF_MAX_VOLUME;
                } else if (GGAF_MIN_VOLUME > vol) {
                    vol = GGAF_MIN_VOLUME;
                }

                //リアルタイムのパンを計算
                const dxcoord fDist_VpVerticalCenter  =
                        pCam->_plnVerticalCenter.a * _pActor->_fX +
                        pCam->_plnVerticalCenter.b * _pActor->_fY +
                        pCam->_plnVerticalCenter.c * _pActor->_fZ +
                        pCam->_plnVerticalCenter.d;
                const angle ang = UTIL::getAngle2D(fDist_VpVerticalCenter, -_pActor->_dest_from_vppln_infront );
                pan = ANG_COS(ang) * 0.95; //0.95意味は、完全に右のみ或いは左のみから聞こえるのを避けるため
                                                      //最高で 0.05 : 0.95 の割合に留めるため。
                //リアルタイムの周波数を計算
                double px_v = _px_d_cam_acter_prev - px_d; //vが観測者からのActor速度
                static double px_svos = 1.0 * px_cam_zf / (SeTransmitterForActor::_se_delay_max_depth); //音速
                if (ZEROd_EQ(px_svos-px_v)) {
                    rate_frequency = 0.0; //音無し
                } else {
                    rate_frequency = px_svos / (px_svos-px_v);
                    if (rate_frequency < 0) {
                        rate_frequency = 0.0; //音無し
                    }
                }
                // カメラとの距離を保存
                _px_d_cam_acter_prev = px_d;
            } //初回計算

            //int delay = RCNV(0.0, px_cam_zf, px_d, -10, SeTransmitterForActor::_se_delay_max_depth);//TODO:遅らせてさした３つを設定
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
    //擬似３D音効果の環境効果更新
    updatePanVolume3D();
}

SeTransmitterForActor::~SeTransmitterForActor() {
}

