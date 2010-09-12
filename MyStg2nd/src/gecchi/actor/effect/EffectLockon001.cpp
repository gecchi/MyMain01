#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;

EffectLockon001::EffectLockon001(const char* prm_name, const char* prm_model_id) : DefaultSpriteSetActor(prm_name, prm_model_id) {
    _class_name = "EffectLockon001";
    //_pTarget = NULL;
    inactivateImmediately();
    defineRotMvWorldMatrix(GgafDx9Util::setWorldMatrix_RzBxyzMv); //ワールド変換はビルボードでRz回転に強制
    chengeEffectTechnique("DestBlendOne"); //エフェクトテクニックは加算合成に強制
    setZEnable(false);      //Zバッファは考慮無しに強制
    setZWriteEnable(false); //Zバッファは書き込み無しに強制
    setSpecialDrawDepth(1); //描画順序を最前面描画に強制。ロックオンエフェクトが隠れないようにするため。
    setAlpha(9.9);          //α部分があるため、カリングをOFFするため透明オブジェクト扱いにする。

    setHitAble(false); //当たり判定無し
    _pSeTransmitter->useSe(1);                                                //使用効果音数宣言
    _pSeTransmitter->set(0, "humei10", GgafRepeatSeq::nextVal("CH_humei10")); //効果音定義

//    _pEffectLockon001_Release = NEW EffectLockon001_Release("EffectLockon001_R", this);
//    _pEffectLockon001_Release->inactivateImmediately();
//    addSubGroup(_pEffectLockon001_Release);

    //setProgress(EffectLockon001_PROG_NOTHING);
}

void EffectLockon001::initialize() {
    _pUvFlipper->forcePtnNoRange(0, 3);   //アニメ範囲を０～１５
    _pUvFlipper->setFlipMethod(FLIP_ORDER_LOOP, 5); //アニメ順序
    _pScaler->forceScaleRange(60000, 2000); //スケーリング・範囲
}

void EffectLockon001::onActive() {
    _pUvFlipper->setPtnNoToTop();
    setAlpha(0.01);
    _pScaler->forceScaleRange(60000, 2000); //スケーリング・範囲
    _pScaler->setScale(60000); //(6000%)
    _pScaler->intoTargetScaleLinerUntil(2000, 25);//スケーリング・25F費やして2000(200%)に縮小
    _pMover->setFaceAngVelo(AXIS_Z, 1000);        //回転
    _pSeTransmitter->play3D(0); //ロックオンSE
    setGeometry(_pTarget);
    setProgress(EffectLockon001_PROG_LOCK);
}

void EffectLockon001::processBehavior() {
    if (getProgress() == EffectLockon001_PROG_LOCK) {
        if (getAlpha() < 1.0) {
             addAlpha(0.01);
         }
         if (_pScaler->_method[0] == NOSCALE) {
             //縮小完了後、Beat
             _pScaler->forceScaleRange(2000, 4000);
             _pScaler->beat(30, 2, 2, -1); //無限ループ
         }
         if (_pTarget) {
             if (_pTarget->isActive() || _pTarget->_will_activate_after_flg) {
                 if (abs(_pTarget->_X-_X) <= 200000 &&
                     abs(_pTarget->_Y-_Y) <= 200000 &&
                     abs(_pTarget->_Z-_Z) <= 200000) {
                     setGeometry(_pTarget);
                     _pMover->setMvVelo(0);
                 } else {
                     _pMover->setMvAng(_pTarget);
                     _pMover->setMvVelo(200000);
                 }
             } else {
                 setProgress(EffectLockon001_PROG_RELEASE);
             }
         } else {
             setProgress(EffectLockon001_PROG_RELEASE);
         }
    }

    if (getProgress() == EffectLockon001_PROG_RELEASE) {
        addAlpha(-0.04);
        if (_pScaler->_method[0] == NOSCALE || getAlpha() <= 0.0) {
            inactivate();
        }
    }

    _pUvFlipper->behave();
    _pMover->behave();
    _pScaler->behave();
}

void EffectLockon001::processJudgement() {

//    if (_fAlpha < 0) {
//        inactivate();
//    }
}

void EffectLockon001::onInactive() {
   // setProgress(EffectLockon001_PROG_NOTHING);
}

void EffectLockon001::lockon(GgafDx9GeometricActor* prm_pTarget) {
    if (prm_pTarget == NULL || _pTarget == prm_pTarget) {
        return;
    }
    _pTarget = prm_pTarget;
    if (getProgress() == EffectLockon001_PROG_LOCK) {
    } else if (getProgress() == EffectLockon001_PROG_RELEASE) {
    }
    _pScaler->forceScaleRange(60000, 2000); //スケーリング・範囲
    _pScaler->intoTargetScaleLinerUntil(2000, 25);//スケーリング・20F費やして2000(200%)に縮小
    _pMover->setFaceAngVelo(AXIS_Z, 1000);   //回転
    _pSeTransmitter->play3D(0); //ロックオンSE
    setProgress(EffectLockon001_PROG_LOCK);
}


void EffectLockon001::releaseLockon() {
    if (isActive()) {
        if (getProgress() == EffectLockon001_PROG_RELEASE) {
            //何も無し
        } else if (getProgress() == EffectLockon001_PROG_LOCK) {

        }
    }
    _pScaler->forceScaleRange(60000, 2000); //スケーリング・範囲
    _pScaler->intoTargetScaleLinerUntil(60000, 50);//スケーリング
    _pMover->setFaceAngVelo(AXIS_Z, _pMover->_angveloFace[AXIS_Z]*-3); //速く逆回転
    setProgress(EffectLockon001_PROG_RELEASE);
    _pTarget = NULL;
}

EffectLockon001::~EffectLockon001() {
}

void EffectLockon001::dump() {
    _TRACE_("\t\t\t\t\t\t\t\t"<<_class_name<<"("<<this<<")["<<getName()<<"] Target="<<(_pTarget==NULL?"NULL":_pTarget->getName())<<" "<<
                                                                               "@"<<_frame_of_behaving_since_onActive<<
                                                                               "/"<<
                                                                               _frame_of_behaving<<
                                                                               "/"<<
                                                                               _frame_of_life<<
                                                                               ","<<
                                                                               _was_initialize_flg<<
                                                                               ","<<
                                                                               _can_live_flg<<
                                                                               _is_active_flg<<
                                                                               ","<<
                                                                               _will_activate_after_flg<<
                                                                               "("<<_frame_of_life_when_activation<<")"<<
                                                                               _on_change_to_active_flg<<
                                                                               ","<<
                                                                               _will_inactivate_after_flg<<
                                                                               "("<<_frame_of_life_when_inactivation<<")"<<
                                                                               _on_change_to_inactive_flg<<
                                                                               ","<<
                                                                               _will_end_after_flg<<
                                                                               "("<<_frame_of_life_when_end<<")"<<
                                                                               ","<<
                                                                               _progress<<
                                                                               "("<<_progress_nextframe<<")"<<
                                                                               ","<<
                                                                               _was_paused_flg<<
                                                                               _was_paused_flg_in_next_frame<<
                                                                               _will_mv_first_in_next_frame_flg<<
                                                                               _will_mv_last_in_next_frame_flg
                                                                               );

    GgafActor* pActor_tmp = _pSubFirst;
    if (_pSubFirst != NULL) {
        while (true) {
            pActor_tmp->dump("\t\t\t\t\t\t\t\t｜");
            if (pActor_tmp->_pNext != NULL) {
                pActor_tmp = pActor_tmp->_pNext;
            } else {
                _TRACE_("【警告】"<<_class_name<<"("<<this<<")["<<getName()<<"]のnextがNULLにっています");
                break;
            }
            if (pActor_tmp->_is_first_flg) {
                _TRACE_("\t\t\t\t\t\t\t\t└─");
                break;
            }
        }
    }
}

void EffectLockon001::dump(string prm_parent) {
    _TRACE_(prm_parent << _class_name<<"("<<this<<")["<<getName()<<"] Target="<<(_pTarget==NULL?"NULL":_pTarget->getName())<<" "<<
                                                                         "@"<<_frame_of_behaving_since_onActive<<
                                                                         "/"<<
                                                                         _frame_of_behaving<<
                                                                         "/"<<
                                                                         _frame_of_life<<
                                                                         ","<<
                                                                         _was_initialize_flg<<
                                                                         ","<<
                                                                         _can_live_flg<<
                                                                         _is_active_flg<<
                                                                         ","<<
                                                                         _will_activate_after_flg<<
                                                                         "("<<_frame_of_life_when_activation<<")"<<
                                                                         _on_change_to_active_flg<<
                                                                         ","<<
                                                                         _will_inactivate_after_flg<<
                                                                         "("<<_frame_of_life_when_inactivation<<")"<<
                                                                         _on_change_to_inactive_flg<<
                                                                         ","<<
                                                                         _will_end_after_flg<<
                                                                         "("<<_frame_of_life_when_end<<")"<<
                                                                         ","<<
                                                                         _progress<<
                                                                         "("<<_progress_nextframe<<")"<<
                                                                         ","<<
                                                                         _was_paused_flg<<
                                                                         _was_paused_flg_in_next_frame<<
                                                                         _will_mv_first_in_next_frame_flg<<
                                                                         _will_mv_last_in_next_frame_flg
                                                                         );

    GgafActor* pActor_tmp = _pSubFirst;
    if (_pSubFirst != NULL) {
        while (true) {
            pActor_tmp->dump(prm_parent + "｜");
            if (pActor_tmp->_pNext != NULL) {
                pActor_tmp = pActor_tmp->_pNext;
            } else {
                _TRACE_("【警告】"<<_class_name<<"("<<this<<")["<<getName()<<"]のnextがNULLにっています");
                break;
            }
            if (pActor_tmp->_is_first_flg) {
                _TRACE_(prm_parent+"└─");
                break;
            }
        }
    }
}

