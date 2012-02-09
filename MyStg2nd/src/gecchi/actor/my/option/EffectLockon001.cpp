#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace MyStg2nd;

EffectLockon001::EffectLockon001(const char* prm_name, const char* prm_model_id) :
        DefaultSpriteSetActor(prm_name, prm_model_id, NULL) {
    _class_name = "EffectLockon001";
    _pTarget = NULL;
    inactivateImmed();
    defineRotMvWorldMatrix(GgafDxUtil::setWorldMatrix_RzBxyzMv); //ワールド変換はビルボードでRz回転に強制
    changeEffectTechnique("DestBlendOne"); //エフェクトテクニックは加算合成に強制
    setZEnable(false);      //Zバッファは考慮無しに強制
    setZWriteEnable(false); //Zバッファは書き込み無しに強制
    setSpecialDrawDepth(1); //描画順序を最前面描画に強制。ロックオンエフェクトが隠れないようにするため。
    setAlpha(9.9);          //α部分があるため、カリングをOFFするため透明オブジェクト扱いにする。

    setHitAble(false); //当たり判定無し
    _pSeTransmitter->useSe(1);                                                //使用効果音数宣言
    _pSeTransmitter->set(0, "humei10", GgafRepeatSeq::nextVal("CH_humei10")); //効果音定義
    useProgress(LOCKON001_PROG_RELEASE);
}

void EffectLockon001::initialize() {
}


void EffectLockon001::onReset() {
	_pProg->set(LOCKON001_PROG_RELEASE);
}

void EffectLockon001::onActive() {
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
//_pTargetが不正になる場合があるため、必要なときにコメントを外して仕様することとする。
//
//
//void EffectLockon001::dump() {
//    _TRACE_("\t\t\t\t\t\t\t\t"<<_class_name<<"("<<this<<")["<<getName()<<"] Target="<<(_pTarget==NULL?"NULL":_pTarget->getName())<<" "<<
//                                                                               "@"<<_frame_of_behaving_since_onActive<<
//                                                                               "/"<<
//                                                                               _frame_of_behaving<<
//                                                                               "/"<<
//                                                                               _frame_of_life<<
//                                                                               ","<<
//                                                                               _was_initialize_flg<<
//                                                                               ","<<
//                                                                               _can_live_flg<<
//                                                                               _is_active_flg<<
//                                                                               ","<<
//                                                                               _will_activate_after_flg<<
//                                                                               "("<<_frame_of_life_when_activation<<")"<<
//                                                                               _on_change_to_active_flg<<
//                                                                               ","<<
//                                                                               _will_inactivate_after_flg<<
//                                                                               "("<<_frame_of_life_when_inactivation<<")"<<
//                                                                               _on_change_to_inactive_flg<<
//                                                                               ","<<
//                                                                               _will_end_after_flg<<
//                                                                               "("<<(_frame_of_life_when_end==MAX_FRAME ? 0 : _frame_of_life_when_end)<<")"<<
//                                                                               ","<<
//                                                                               _was_paused_flg<<
//                                                                               _was_paused_flg_in_next_frame<<
//                                                                               _will_mv_first_in_next_frame_flg<<
//                                                                               _will_mv_last_in_next_frame_flg
//                                                                               );
//
//    GgafActor* pActor_tmp = _pSubFirst;
//    if (_pSubFirst) {
//        while (true) {
//            pActor_tmp->dump("\t\t\t\t\t\t\t\t｜");
//            if (pActor_tmp->_pNext) {
//                pActor_tmp = pActor_tmp->_pNext;
//            } else {
//                _TRACE_("【警告】"<<_class_name<<"("<<this<<")["<<getName()<<"]のnextがNULLっています");
//                break;
//            }
//            if (pActor_tmp->_is_first_flg) {
//                _TRACE_("\t\t\t\t\t\t\t\t└─");
//                break;
//            }
//        }
//    }
//}


//void EffectLockon001::dump(string prm_parent) {
//    _TRACE_(prm_parent << _class_name<<"("<<this<<")["<<getName()<<"] Target="<<(_pTarget==NULL?"NULL":_pTarget->getName())<<" "<<
//                                                                         "@"<<_frame_of_behaving_since_onActive<<
//                                                                         "/"<<
//                                                                         _frame_of_behaving<<
//                                                                         "/"<<
//                                                                         _frame_of_life<<
//                                                                         ","<<
//                                                                         _was_initialize_flg<<
//                                                                         ","<<
//                                                                         _can_live_flg<<
//                                                                         _is_active_flg<<
//                                                                         ","<<
//                                                                         _will_activate_after_flg<<
//                                                                         "("<<_frame_of_life_when_activation<<")"<<
//                                                                         _on_change_to_active_flg<<
//                                                                         ","<<
//                                                                         _will_inactivate_after_flg<<
//                                                                         "("<<_frame_of_life_when_inactivation<<")"<<
//                                                                         _on_change_to_inactive_flg<<
//                                                                         ","<<
//                                                                         _will_end_after_flg<<
//                                                                         "("<<(_frame_of_life_when_end==MAX_FRAME ? 0 : _frame_of_life_when_end)<<")"<<
//                                                                         ","<<
//                                                                         _was_paused_flg<<
//                                                                         _was_paused_flg_in_next_frame<<
//                                                                         _will_mv_first_in_next_frame_flg<<
//                                                                         _will_mv_last_in_next_frame_flg
//                                                                         );
//
//    GgafActor* pActor_tmp = _pSubFirst;
//    if (_pSubFirst) {
//        while (true) {
//            pActor_tmp->dump(prm_parent + "｜");
//            if (pActor_tmp->_pNext) {
//                pActor_tmp = pActor_tmp->_pNext;
//            } else {
//                _TRACE_("【警告】"<<_class_name<<"("<<this<<")["<<getName()<<"]のnextがNULLっています");
//                break;
//            }
//            if (pActor_tmp->_is_first_flg) {
//                _TRACE_(prm_parent+"└─");
//                break;
//            }
//        }
//    }
//}

