#include "stdafx.h"
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

EffectLockon001::EffectLockon001(const char* prm_name, const char* prm_model_id) :
        DefaultSpriteSetActor(prm_name, prm_model_id, nullptr) {
    _class_name = "EffectLockon001";
    pTarget_ = nullptr;
    inactivateImmed();
    defineRotMvWorldMatrix(UTIL::setWorldMatrix_RzBxyzMv); //ワールド変換はビルボードでRz回転に強制
    effectBlendOne(); //エフェクトテクニックは加算合成に強制
    setZEnable(false);      //Zバッファは考慮無しに強制
    setZWriteEnable(false); //Zバッファは書き込み無しに強制
    setSpecialDrawDepth(1); //描画順序を最前面描画に強制。ロックオンエフェクトが隠れないようにするため。
    setAlpha(0.9);          //α部分があるため、カリングをOFFするため透明オブジェクト扱いにする。

    setHitAble(false); //当たり判定無し
    _pSeTx->set(0, "WAVE_LOCKON_001"); //効果音定義
    useProgress(LOCKON001_PROG_RELEASE);
}

void EffectLockon001::initialize() {
}


void EffectLockon001::onReset() {
    _pProg->reset(LOCKON001_PROG_RELEASE);
}

void EffectLockon001::onActive() {
    if (pTarget_ == nullptr) {
        inactivateImmed();
        return;
    }
}

void EffectLockon001::processBehavior() {
}

void EffectLockon001::processJudgement() {
}

void EffectLockon001::onInactive() {
}


EffectLockon001::~EffectLockon001() {
}

//
//DEBUGモードアプリ終了時のツリー表示時、
//pTarget_が不正になる場合等、必要なときにコメントを外して使用。
//
//
//void EffectLockon001::dump() {
//    _TRACE_("\t\t\t\t\t\t\t\t"<<_class_name<<"("<<this<<")["<<getName()<<"] Target="<<(pTarget_==nullptr?"nullptr":pTarget_->getName())<<" "<<
//                                                                               "@"<<frame_of_behaving_since_onActive_<<
//                                                                               "/"<<
//                                                                               frame_of_behaving_<<
//                                                                               "/"<<
//                                                                               frame_of_life_<<
//                                                                               ","<<
//                                                                               was_initialize_flg_<<
//                                                                               ","<<
//                                                                               can_live_flg_<<
//                                                                               is_active_flg_<<
//                                                                               ","<<
//                                                                               _will_activate_after_flg<<
//                                                                               "("<<frame_of_life_when_activation_<<")"<<
//                                                                               on_change_to_active_flg_<<
//                                                                               ","<<
//                                                                               will_inactivate_after_flg_<<
//                                                                               "("<<frame_of_life_when_inactivation_<<")"<<
//                                                                               on_change_to_inactive_flg_<<
//                                                                               ","<<
//                                                                               will_end_after_flg_<<
//                                                                               "("<<(frame_of_life_when_end_==MAX_FRAME ? 0 : frame_of_life_when_end_)<<")"<<
//                                                                               ","<<
//                                                                               _was_paused_flg<<
//                                                                               was_paused_flg_in_next_frame_<<
//                                                                               will_mv_first_in_next_frame_flg_<<
//                                                                               will_mv_last_in_next_frame_flg_
//                                                                               );
//
//    GgafActor* pActor_tmp = pSubFirst_;
//    if (pSubFirst_) {
//        while (true) {
//            pActor_tmp->dump("\t\t\t\t\t\t\t\t｜");
//            if (pActor_tmp->_pNext) {
//                pActor_tmp = pActor_tmp->_pNext;
//            } else {
//                _TRACE_("【警告】"<<_class_name<<"("<<this<<")["<<getName()<<"]のnextがnullptrっています");
//                break;
//            }
//            if (pActor_tmp->is_first_flg_) {
//                _TRACE_("\t\t\t\t\t\t\t\t└─");
//                break;
//            }
//        }
//    }
//}


//void EffectLockon001::dump(std::string prm_parent) {
//    _TRACE_(prm_parent << _class_name<<"("<<this<<")["<<getName()<<"] Target="<<(pTarget_==nullptr?"nullptr":pTarget_->getName())<<" "<<
//                                                                         "@"<<frame_of_behaving_since_onActive_<<
//                                                                         "/"<<
//                                                                         frame_of_behaving_<<
//                                                                         "/"<<
//                                                                         frame_of_life_<<
//                                                                         ","<<
//                                                                         was_initialize_flg_<<
//                                                                         ","<<
//                                                                         can_live_flg_<<
//                                                                         is_active_flg_<<
//                                                                         ","<<
//                                                                         _will_activate_after_flg<<
//                                                                         "("<<frame_of_life_when_activation_<<")"<<
//                                                                         on_change_to_active_flg_<<
//                                                                         ","<<
//                                                                         will_inactivate_after_flg_<<
//                                                                         "("<<frame_of_life_when_inactivation_<<")"<<
//                                                                         on_change_to_inactive_flg_<<
//                                                                         ","<<
//                                                                         will_end_after_flg_<<
//                                                                         "("<<(frame_of_life_when_end_==MAX_FRAME ? 0 : frame_of_life_when_end_)<<")"<<
//                                                                         ","<<
//                                                                         _was_paused_flg<<
//                                                                         was_paused_flg_in_next_frame_<<
//                                                                         will_mv_first_in_next_frame_flg_<<
//                                                                         will_mv_last_in_next_frame_flg_
//                                                                         );
//
//    GgafActor* pActor_tmp = pSubFirst_;
//    if (pSubFirst_) {
//        while (true) {
//            pActor_tmp->dump(prm_parent + "｜");
//            if (pActor_tmp->_pNext) {
//                pActor_tmp = pActor_tmp->_pNext;
//            } else {
//                _TRACE_("【警告】"<<_class_name<<"("<<this<<")["<<getName()<<"]のnextがnullptrっています");
//                break;
//            }
//            if (pActor_tmp->is_first_flg_) {
//                _TRACE_(prm_parent+"└─");
//                break;
//            }
//        }
//    }
//}

