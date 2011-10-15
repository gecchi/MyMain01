#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDxCore;

GgafDxFormationActor::GgafDxFormationActor(const char* prm_name, frame prm_offset_frames_end) :
    GgafDxGeometricActor(prm_name, NULL, NULL)
{
    _obj_class |= Obj_GgafFormation;
    _class_name = "GgafDxFormationActor";
    _offset_frames_end = prm_offset_frames_end;
    _num_sub = 0;
    setHitAble(false);
    _is_init = false;
    _pDepo = NULL;
    _num_destory = 0;
//    _num_inactive = 0;
    _is_called_up = false;
    _was_all_destroyed = false;
}
void GgafDxFormationActor::setFormationAbleActorDepository(GgafActorDepository* prm_pDepo) {
    _pDepo = prm_pDepo;
    GgafMainActor* pActor = _pDepo->getSubFirst();
    if (pActor) {
//        //最初の１つ目の要素だけIFormationAbleチェック
//         IFormationAble* pIFormationAbleActor = dynamic_cast<IFormationAble*>(pActor);
//         if (pIFormationAbleActor) {
//             //OK
//         } else {
//             throwGgafCriticalException("GgafDxFormationActor::setFormationAbleActorDepository("<<prm_pDepo->getName()<<")  IFormationAble*へクロスキャスト失敗。"<<
//                                        "_pDepo->getSubFirst()="<<pActor->getName()<<" のクラスから IFormationAble が見えません。public 継承して下さい。 this="<<getName()<<" _num_sub="<<_num_sub);
//         }

    } else {
        throwGgafCriticalException("GgafDxFormationActor::setFormationAbleActorDepository("<<prm_pDepo->getName()<<") 引数デポジトリのサブが存在しません this="<<getName());
    }
}

void GgafDxFormationActor::addSubLast(GgafActor* prm_pSub) {
    if (wasDeclaredEnd() || _will_inactivate_after_flg) {
        //終了を待つのみ
        throwGgafCriticalException("GgafDxFormationActor::addSubLast("<<prm_pSub->getName()<<") 既に死にゆく定めのFormationです。サブに追加することはおかしいでしょう。this="<<getName());
    }
    if (_pDepo) {
        _TRACE_("＜警告＞ GgafDxFormationActor::addSubLast("<<prm_pSub->getName()<<") Depository指定モード時に addSubLast すると全滅判定は出来ません。意図的ですか？callUp()は不要ですか？ "<<
                "this="<<getName()<<" _num_sub="<<_num_sub);
    }
    if (_pSubFirst == NULL) {
        //種別を引き継ぐ
        _pStatus->set(STAT_DEFAULT_ACTOR_KIND, prm_pSub->_pStatus->get(STAT_DEFAULT_ACTOR_KIND));
    } else {
        //同一種別かチェック
        if (_pStatus->get(STAT_DEFAULT_ACTOR_KIND) != prm_pSub->_pStatus->get(STAT_DEFAULT_ACTOR_KIND)) {
            throwGgafCriticalException("GgafDxFormationActor::addSubLast 異なる種別のアクターを登録しようとしています。this="<<getName()<<"("<<this<<") \n"<<
                                       "想定kind="<<_pStatus->get(STAT_DEFAULT_ACTOR_KIND)<<" _pSubFirst="<<_pSubFirst->getName()<<" \n"<<
                                       "引数kind="<<prm_pSub->_pStatus->get(STAT_DEFAULT_ACTOR_KIND)<<" prm_pSub="<<prm_pSub->getName()<<"("<<prm_pSub<<")");
        }
    }
    if (prm_pSub->_obj_class & Obj_GgafDxGeometricActor) {
        _num_sub++;
        ((GgafDxGeometricActor*)prm_pSub)->_pFormation = this; //メンバーへフォーメーションを設定
        _listFllower.addLast((GgafDxGeometricActor*)prm_pSub, false); //フォーメーションメンバーとして内部保持
    } else {
        _TRACE_("＜警告＞ GgafDxFormationActor::addSubLast("<<prm_pSub->getName()<<") Obj_GgafDxGeometricActor 以外のアクターが追加されます。GgafDxFormationActor使用意図は正しいですか？。"<<
                "this="<<getName()<<" _num_sub="<<_num_sub);
    }
    GgafDxGeometricActor::addSubLast(prm_pSub);
}

GgafDxGeometricActor* GgafDxFormationActor::callUp() {
    if (wasDeclaredEnd() || _will_inactivate_after_flg) {
        //終了を待つのみ
        return NULL;
    }
#ifdef MY_DEBUG
    if (!_pDepo) {
        throwGgafCriticalException("GgafDxFormationActor::callUp "<<getName()<<"は、Depositoryが指定されてません。setFormationAbleActorDepositoryが必要です。"<<
                                   "this="<<getName()<<" _num_sub="<<_num_sub);
    }
#endif
    GgafMainActor* pActor = _pDepo->dispatch();
    if (pActor) {
        if (pActor->_obj_class & Obj_GgafDxGeometricActor) {
            //OK
        } else {
            throwGgafCriticalException("GgafDxFormationActor::callUp() Obj_GgafDxGeometricActor 以外のアクターが取り出されました。"<<
                                       "this="<<getName()<<" pActor="<<pActor->getName()<<" _num_sub="<<_num_sub);
        }
        _num_sub++;
//        IFormationAble* p = dynamic_cast<IFormationAble*>(pActor);
//        if (p == NULL) {
//            throwGgafCriticalException("GgafDxFormationActor::callUp() IFormationAble*へクロスキャスト失敗。pActor="<<pActor->getName()<<" のクラスから IFormationAble が見えません。public 継承して下さい。"<<
//                                       "this="<<getName()<<" _num_sub="<<_num_sub);
//        }
//        p->_pFormation = this;
        ((GgafDxGeometricActor*)pActor)->_pFormation = this;
        _listFllower.addLast((GgafDxGeometricActor*)pActor, false);
    }
    _is_called_up = true;
    return (GgafDxGeometricActor*)pActor;
}

void GgafDxFormationActor::processJudgement() {
    if (wasDeclaredEnd() || _will_inactivate_after_flg) {
        //終了を待つのみ
    } else {
        if (_pDepo) {
            if (_is_called_up && _num_sub == 0) { //デポジトリモード時、いきなり借りれない場合、フォーメーションはなかったことになり、自身を終了
                sayonara(_offset_frames_end);
            }
        } else {
            if (getSubFirst() == NULL) {          //配下がない場合、フォーメーションはなかったことになり、自身を終了
                sayonara(_offset_frames_end);
            }
        }
    }

    if (_listFllower.length() == 0) {
        if (_num_sub > 0) {
            //過去に１度でも追加した後、メンバーが0の場合はさよなら
            sayonara(_offset_frames_end);
        } else {
            //メンバーが0だが、過去に１度も追加していない。つまり、生成直後あたり。
            return;
        }
    } else {
        //不正ポインタのチェック
        GgafDxGeometricActor* pFllower = _listFllower.getCurrent();
        int num_follwer = _listFllower.length();
        for (int i = 0; i < num_follwer; i++) {
            if (_can_live_flg && (pFllower->_is_active_flg || pFllower->_will_activate_after_flg)) {
                pFllower = _listFllower.next();
            } else {
                _listFllower.remove();
            }
        }
    }


}
void GgafDxFormationActor::onGarbaged() {
    GgafDxGeometricActor::onGarbaged();
    sayonaraFollwer();
}

void GgafDxFormationActor::sayonaraFollwer() {
    if (_listFllower.length() == 0) {
        return;
    }
#ifdef MY_DEBUG
    if (_pDepo) {
        _TRACE_("GgafDxFormationActor::sayonaraFollwer 所属を残したまま、GgafDxFormationActor の方が先に消されています。wasInactiveFollower() コール漏れはありませんか？ "<<
                "this="<<getName()<<" _num_sub="<<_num_sub<<" _listFllower.length()="<<_listFllower.length());
    }
#endif
    while (_listFllower.length() > 0) {

//        IFormationAble* p = dynamic_cast<IFormationAble*>(_listFllower.getCurrent());
//        if (p == NULL) {
//            throwGgafCriticalException("GgafDxFormationActor::sayonaraFollwer IFormationAble*へクロスキャスト失敗。_listFllower.getCurrent()="<<_listFllower.getCurrent()->getName()<<" のクラスから IFormationAble が見えません。public 継承して下さい。 this="<<getName()<<" _num_sub="<<_num_sub);
//        }
//        if (p->_pFormation == this) {
//            _TRACE_("GgafDxFormationActor::sayonaraFollwer _listFllowerの"<<_listFllower.getCurrent()->getName()<<"をsayonaraします。");
//            _listFllower.getCurrent()->sayonara();
//        }

        GgafDxGeometricActor* pFllower =  _listFllower.getCurrent();
        if (pFllower->_pFormation == this) {
            _TRACE_("GgafDxFormationActor::sayonaraFollwer _listFllowerの"<<_listFllower.getCurrent()->getName()<<"をsayonaraします。");
            _listFllower.getCurrent()->sayonara();
        }
        _listFllower.remove();
    }

}

GgafDxFormationActor::~GgafDxFormationActor() {

}
