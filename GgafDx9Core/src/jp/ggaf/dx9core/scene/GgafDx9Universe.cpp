#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;

GgafDx9DrawableActor* GgafDx9Universe::_apAlphaActorList_DrawDepthLevel[MAX_DRAW_DEPTH_LEVEL];
GgafDx9DrawableActor* GgafDx9Universe::_pActors_DrawMaxDrawDepth = NULL;
GgafDx9DrawableActor* GgafDx9Universe::_pActor_DrawActive = NULL;
GgafDx9Camera* GgafDx9Universe::_pCamera = NULL;

int GgafDx9Universe::_X_goneLeft   = 0;
int GgafDx9Universe::_X_goneRight  = 0;
int GgafDx9Universe::_Y_goneTop    = 0;
int GgafDx9Universe::_Y_goneBottom = 0;
int GgafDx9Universe::_Z_goneFar   = 0;
int GgafDx9Universe::_Z_goneNear  = 0;

GgafDx9Universe::GgafDx9Universe(const char* prm_name) : GgafUniverse(prm_name) {
    _class_name = "GgafDx9Universe";
    for (int i = 0; i < MAX_DRAW_DEPTH_LEVEL; i++) {
        _apAlphaActorList_DrawDepthLevel[i] = NULL;
    }
    //先にカメラはNEWしておかないといけない。
    _pCamera = NEW GgafDx9Camera("CAMERA", PI * 80.0f / 180.0f, GGAFDX9_PROPERTY(GAME_SPACE_DEPTH));    //FovX視野角80度、深さ×15.0
    getLordActor()->addSubGroup(_pCamera);
    _pActor_DrawActive = NULL;

    //カメラの写すちょっと余裕をもった範囲。
    _X_goneLeft   = GgafDx9Camera::_X_ScreenLeft * 4;
    _X_goneRight  = +_pCamera->_zf*PX_UNIT*LEN_UNIT + (abs(_pCamera->_cameraZ)*PX_UNIT*LEN_UNIT);
    _Y_goneTop    = +_pCamera->_zf*PX_UNIT*LEN_UNIT + (abs(_pCamera->_cameraZ)*PX_UNIT*LEN_UNIT);
    _Y_goneBottom = -_pCamera->_zf*PX_UNIT*LEN_UNIT - (abs(_pCamera->_cameraZ)*PX_UNIT*LEN_UNIT);
    _Z_goneFar   = +_pCamera->_zf*PX_UNIT*LEN_UNIT + (abs(_pCamera->_cameraZ)*PX_UNIT*LEN_UNIT);
    _Z_goneNear  = -_pCamera->_zf*PX_UNIT*LEN_UNIT - (abs(_pCamera->_cameraZ)*PX_UNIT*LEN_UNIT);
    _TRACE_("Gone=X ("<<_X_goneLeft<<" ~ "<<_X_goneRight<<") Y("<<_Y_goneBottom<<" ~ "<<_Y_goneTop<<") Z("<<_Z_goneFar<<" ~ "<<_Z_goneNear<<")");

    _papSeCon = NEW GgafDx9SeConnection*[10];
    _papSe    = NEW GgafDx9Se*[10];
    for (int i = 0; i < 10; i++) {
        _papSeCon[i] = NULL;
        _papSe[i] = NULL;
    }
}

void GgafDx9Universe::draw() {
    GgafDx9ModelConnection* pModelCon = GgafDx9God::_pModelManager->getFirstConnection();
    while (pModelCon != NULL) {
        pModelCon->view()->_pTextureBlinker->behave();
        pModelCon = (GgafDx9ModelConnection*)(pModelCon->getNext());
    }


    //段階レンダリング不要（最深部等、背景、最善面の文字等）の描画。
    //※TODO:本来は手前から描画のほうが効率良い。が、その内最適化
    _pActor_DrawActive = _pActors_DrawMaxDrawDepth;
    while (_pActor_DrawActive != NULL && _pActor_DrawActive->_is_active_flg && _pActor_DrawActive->_can_live_flg) {
        if (_pActor_DrawActive->_fAlpha < 1.0) {
            GgafDx9God::_pID3DDevice9->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE); //半透明要素ありということでカリングを一時OFF
            //但し、段階レンダリング不要であるにもかかわらず、半透明表示は、前後がうまく表示されないので避けるべき。
        }
        _pActor_DrawActive->processDraw();
        if (_pActor_DrawActive->_fAlpha < 1.0) {
            GgafDx9God::_pID3DDevice9->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);  //カリング有りに戻す
        }
        _pActor_DrawActive = _pActor_DrawActive->_pNext_TheSameDrawDepthLevel;
    }
    _pActors_DrawMaxDrawDepth = NULL; //次回のためにリセット

    //段階レンダリングが必要なオブジェクトを描画
    //float tmpAlpah;
    //int alphapoint = MAX_DRAW_DEPTH_LEVEL/4*3;
    for (int i = MAX_DRAW_DEPTH_LEVEL - 1; i >= 0; i--) {
        _pActor_DrawActive = _apAlphaActorList_DrawDepthLevel[i];
        while (_pActor_DrawActive != NULL && _pActor_DrawActive->_is_active_flg && _pActor_DrawActive->_can_live_flg) {
            if (_pActor_DrawActive->_fAlpha < 1.0) {
                GgafDx9God::_pID3DDevice9->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE); //半透明要素ありということでカリングを一時OFF
            }
            //TODO:奥は暗く
//            if (alphapoint < i) {
//                tmpAlpah = _pActor_DrawActive->getAlpha();
//                _pActor_DrawActive->addAlpha((1.0/(MAX_DRAW_DEPTH_LEVEL - alphapoint))*i - 3.0);
//            }
            _pActor_DrawActive->processDraw();
//            if (alphapoint < i) {
//                _pActor_DrawActive->setAlpha(tmpAlpah);
//            }
            if (_pActor_DrawActive->_fAlpha < 1.0) {
                GgafDx9God::_pID3DDevice9->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);  //カリング有りに戻す
            }
            _pActor_DrawActive = _pActor_DrawActive->_pNext_TheSameDrawDepthLevel;
        }
        _apAlphaActorList_DrawDepthLevel[i] = NULL; //次回のためにリセット
    }

    //最後のEndPass
    HRESULT hr;
    if (GgafDx9EffectManager::_pEffect_Active != NULL) {
        TRACE4("EndPass: /_pEffect_Active="<<GgafDx9EffectManager::_pEffect_Active->_effect_name);
        hr = GgafDx9EffectManager::_pEffect_Active->_pID3DXEffect->EndPass();
        checkDxException(hr, D3D_OK, "GgafDx9Universe::processDraw() EndPass() に失敗しました。");
        hr = GgafDx9EffectManager::_pEffect_Active->_pID3DXEffect->End();
        checkDxException(hr, D3D_OK, "GgafDx9Universe::processDraw() End() に失敗しました。");
        GgafDx9EffectManager::_pEffect_Active = NULL;
        GgafDx9ModelManager::_pModelLastDraw = NULL;
        GgafDx9DrawableActor::_hash_technique_last_draw = 0;
    }
}

//void GgafDx9Universe::setDrawDepthMaxLevel(GgafDx9DrawableActor* prm_pActor) {
//    static GgafDx9DrawableActor* pActorTmp;
//    if (_pActors_DrawMaxDrawDepth == NULL) {
//        //最初のアクターの場合
//        prm_pActor->_pNext_TheSameDrawDepthLevel = NULL;
//        _pActors_DrawMaxDrawDepth = prm_pActor;
//        return;
//    } else {
//        //既にアクター登録済みだった場合
//        pActorTmp = _pActors_DrawMaxDrawDepth;
//        prm_pActor->_pNext_TheSameDrawDepthLevel = pActorTmp;
//        _pActors_DrawMaxDrawDepth = prm_pActor;
//        return;
//    }
//}
int GgafDx9Universe::setDrawDepthLevel(int prm_draw_depth_level, GgafDx9DrawableActor* prm_pActor) {
    int draw_depth_level;
    static GgafDx9DrawableActor* pActorTmp;
    //上限下限カット
    if (prm_draw_depth_level > MAX_DRAW_DEPTH_LEVEL - 1) {
        draw_depth_level = MAX_DRAW_DEPTH_LEVEL - 1;
    } else if (prm_draw_depth_level < 0) {
        draw_depth_level = 0;
    } else {
        draw_depth_level = prm_draw_depth_level;
    }

    if (_apAlphaActorList_DrawDepthLevel[draw_depth_level] == NULL) {
        //そのprm_draw_depth_levelで最初のアクターの場合
        prm_pActor->_pNext_TheSameDrawDepthLevel = NULL;
        _apAlphaActorList_DrawDepthLevel[draw_depth_level] = prm_pActor;
    } else {
        //そのprm_draw_depth_levelで既にアクター登録済みだった場合
        //固まらないように、お尻から追加(キュー)、或いは、前に積み上げ(スタック)を、フレームよって交互に行う。
        //何故ならば、テクスチャに半透明が存在するZバッファ有りの半透明オブジェクトが交差した場合、
        //同一深度なので、描画順によっては透けない部分が生じ、おかしな表示となる。これを高速交互表示で若干のごまかしを行う。
        if ((GgafGod::_pGod->_pUniverse->_frame_of_behaving & 1) == 1) {
            //お尻に追加
            pActorTmp = _apAlphaActorList_DrawDepthLevel[draw_depth_level];
            prm_pActor->_pNext_TheSameDrawDepthLevel = pActorTmp;
            _apAlphaActorList_DrawDepthLevel[draw_depth_level] = prm_pActor;
        } else {
            //前に追加
            pActorTmp = _apAlphaActorList_DrawDepthLevel[draw_depth_level];
            while(pActorTmp->_pNext_TheSameDrawDepthLevel != NULL) {
                pActorTmp = pActorTmp->_pNext_TheSameDrawDepthLevel;
            }
            pActorTmp->_pNext_TheSameDrawDepthLevel = prm_pActor;
            prm_pActor->_pNext_TheSameDrawDepthLevel = NULL;
        }
    }
    return draw_depth_level;

}

void GgafDx9DrawableActor::prepareSe(int prm_id, const char* prm_se_name, int prm_cannel) {
    char idstr[129];
    sprintf(idstr, "%d/%s", prm_cannel, prm_se_name);
    _papSeCon[prm_id] = (GgafDx9SeConnection*)GgafDx9Sound::_pSeManager->connect(idstr);
    _papSe[prm_id] = _papSeCon[prm_id]->view();
}

void GgafDx9DrawableActor::playSe(int prm_id) {

    //    /** [r]視錐台上面から視野外に向かっての自身の座標までのDirectXの距離、視野内の距離は負の値になる */
    //    FLOAT _fDist_VpPlnTop;
    //    /** [r]視錐台下面から視野外に向かっての自身の座標までのDirectXの距離、視野内の距離は負の値になる */
    //    FLOAT _fDist_VpPlnBottom;
    //    /** [r]視錐台左面から視野外に向かっての自身の座標までのDirectXの距離、視野内の距離は負の値になる */
    //    FLOAT _fDist_VpPlnLeft;
    //    /** [r]視錐台右面から視野外に向かっての自身の座標までのDirectXの距離、視野内の距離は負の値になる */
    //    FLOAT _fDist_VpPlnRight;
    //    /** [r]視錐台手前面から視野外に向かっての自身の座標までのDirectXの距離、視野内の距離は負の値になる */
    //    FLOAT _fDist_VpPlnFront;
    //    /** [r]視錐台奥面から視野外に向かっての自身の座標までのDirectXの距離、視野内の距離は負の値になる */
    //    FLOAT _fDist_VpPlnBack;
    //#define DSBPAN_LEFT                 -10000
    //#define DSBPAN_CENTER               0
    //#define DSBPAN_RIGHT                10000
    //
    //#define DSBVOLUME_MIN               -10000
    //#define DSBVOLUME_MAX               0
    //    int GgafDx9Sound::_master_volume = 100;
    //    int GgafDx9Sound::_bgm_volume = 100;
    //    int GgafDx9Sound::_se_volume = 100;

    //    /** カメラから近くのクリップ面までの距離(どこからの距離が表示対象か）≠0 */
    //    float _zn;
    //    /** カメラから遠くのクリップ面までの距離(どこまでの距離が表示対象か）> zn  */
    //    float _zf;

    //    まず、同じバッファの音が同時再生できなかった問題は、DuplicateSoundBuffer()関数を使ってバッファの外枠のみのコピーを作っておくことで解決です。例えば、これで8個作っておくと同じバッファの音が8個まで同時再生できます。
    //    ただ、小さな破片は1秒間に数百個も爆発したりするので、さすがに100個くらい同時再生しようとすると音が途切れます…。
    //
    //    後は、再生直前に
    //
    //        lpDSBuf->SetVolume(LONG); //音量設定 減衰するdb 0～-10000
    //        lpDSBuf->SetPan(LONG); //パン設定 -10000～+10000
    //        lpDSBuf->SetFrequency(DWORD); //再生周波数設定
    //
    //    _dwDefaultFrequency
    //    こういう設定が出来ることが分かりました。最後の再生周波数設定は、例えばサンプリングレート44.1KHzのバッファの場合はここへ44100を指定すると通常通りの再生になり、22050を指定すると半分の速度（音程も半分）で再生されるという具合です。
    //    これ、敵の爆破した位置に合わせて設定してやるとすごく立体的でリアル。とくに、遠くの爆発は再生周波数下げるようにすると、爆発音がくぐもった音になってまるで映画みたい。最初は遊び心でいじってたけど、ここまで上手くハマるとは思わなかったな。
    //
    //    ただ、注意点もあって、バッファ初期化時にDSBUFFERDESC構造体の設定で、
    //
    //        DSBufferDesc.dwFlags = DSBCAPS_LOCDEFER | DSBCAPS_CTRLPAN | DSBCAPS_CTRLFREQUENCY | DSBCAPS_CTRLVOLUME;
    //
    //    のようなフラグを設定して、各パラメータをコントロールすることを伝えておく必要がある。MSDN見ても、SetVolume()の解説のところなんかにこのフラグの事が書いて無くて、しばらくネットを探し回ってしまった。あと、SetVolumeの値もMSDNだと正の値だと書いてあるけど、実際は負の値を入れないといけない。MSDNってどっか抜けてる…？？


    //距離計算
    //遅延なし、音量100％の場所をpCAMの場所とする
    //自身とpCAMの距離
    double dX = pCAM->_X - _X;
    double dY = pCAM->_Y - _Y;
    double dZ = pCAM->_Z - _Z;
    double D = GgafUtil::sqrt_fast(dX*dX + dY*dY + dZ*dZ);
    _TRACE_("GgafDx9DrawableActor::playSe 距離 = D");

    _papSe[prm_id]->play();
}

GgafDx9Universe::~GgafDx9Universe() {
    if (_pSeCon) {
        _pSeCon->close();
    }
    for (int i = 0; i < 10; i++) {
        if (_papSeCon[i]) {
            _papSeCon[i]->close();
        }
    }
    DELETEARR_IMPOSSIBLE_NULL(_papSeCon);
    DELETEARR_IMPOSSIBLE_NULL(_papSe);
}
