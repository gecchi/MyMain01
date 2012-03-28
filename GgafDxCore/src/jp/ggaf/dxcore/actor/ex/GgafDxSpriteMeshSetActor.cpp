#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDxCore;

GgafDxSpriteMeshSetActor::GgafDxSpriteMeshSetActor(const char* prm_name,
                                                   const char* prm_model,
                                                   GgafStatus* prm_pStat,
                                                   GgafDxChecker* prm_pChecker) :

                                                    GgafDxMeshSetActor(prm_name,
                                                                       prm_model,
                                                                       "SpriteMeshSetEffect",
                                                                       "SpriteMeshSetTechnique",
                                                                       prm_pStat,
                                                                       prm_pChecker) {

    _obj_class |= Obj_GgafDxSpriteMeshSetActor;
    _class_name = "GgafDxSpriteMeshSetActor";

    GgafDxTexture* pTexture = _pMeshSetModel->_papTextureCon[0]->fetch();
    _pUvFlipper = NEW GgafDxUvFlipper(pTexture);
    _pUvFlipper->setRotation(1, 1);
    _pUvFlipper->setActivePtn(0);
    _pUvFlipper->setFlipMethod(NOT_ANIMATED, 1);
}


void GgafDxSpriteMeshSetActor::processDraw() {

    _draw_set_num = 0; //GgafDxSpriteMeshSetActorの同じモデルで同じテクニックが
                       //連続しているカウント数。同一描画深度は一度に描画する。
    ID3DXEffect* pID3DXEffect = _pMeshSetEffect->_pID3DXEffect;
    HRESULT hr;
    GgafDxDrawableActor* pDrawActor = this;
    GgafDxSpriteMeshSetActor* pSpriteMeshSetActor = NULL;
    float u = 0;
    float v = 0;
    while (true) {
        if (pDrawActor)  {
            if (pDrawActor->_pModel == _pMeshSetModel && pDrawActor->_hash_technique == _hash_technique) {
                pSpriteMeshSetActor = (GgafDxSpriteMeshSetActor*)pDrawActor;

                hr = pID3DXEffect->SetMatrix(_pMeshSetEffect->_ah_matWorld[_draw_set_num], &(pSpriteMeshSetActor->_matWorld));
                checkDxException(hr, D3D_OK, "GgafDxSpriteMeshSetActor::processDraw() SetMatrix(g_matWorld) に失敗しました。");
                hr = pID3DXEffect->SetValue(_pMeshSetEffect->_ah_materialDiffuse[_draw_set_num], &(pSpriteMeshSetActor->_paMaterial[0].Diffuse), sizeof(D3DCOLORVALUE) );
                checkDxException(hr, D3D_OK, "GgafDxSpriteMeshSetActor::processDraw() SetValue(g_colMaterialDiffuse) に失敗しました。");
#ifdef MY_DEBUG
                if (pDrawActor->_obj_class & Obj_GgafDxSpriteMeshSetActor) {
                    //OK
                } else {
                    throwGgafCriticalException("GgafDxSpriteMeshSetActor::processDraw() pDrawActor["<<pDrawActor->getName()<<"] はGgafDxSpriteMeshSetActorではありません。");
                }
#endif
                //[MEMO]
                //GgafDxSpriteMeshSetActor は、GgafDxMeshSetActor から派生しているため、モデルクラスは同じGgafDxMeshSetModelである。
                //GgafDxSpriteMeshSetActorが使用するモデル名("x/10/Flora"等)と、GgafDxMeshSetActorが使用するモデル名が
                //同じものが存在する場合、pDrawActor は、GgafDxMeshSetActor の可能性もある。
                //これは、_draw_set_num を求めるロジックは同一深度で連続の同一(アドレス)モデルである。という判定しか行っていないため。
                //実はここで、GgafDxSpriteMeshSetActor と GgafDxMeshSetActor で同一モデル名を使用することは禁止にしたいのである。
                //本来は Actor の種類に関係なく、同じ Model で連続ならば、ステート切り替えぜず高速化することがウリであるのだが、
                //GgafDxSpriteMeshSetActor は、GgafDxMeshSetActor から派生しているにもかかわらず、無理やりエフェクト自体を変更している。
                //誠実に実装するならば、別物としてそれぞれ別の Model クラスを作成するべきかもしれないが、Modelクラスとしての処理自体は
                //GgafDxSpriteMeshSetActor、GgafDxMeshSetActor 共に全く同じで良い。
                //悩んだ結果、Model クラスを分けて実装せず、やや危険なキャストを行うこととする。
                //とりあえずGgafDxSpriteMeshSetActor と、GgafDxMeshSetActor のモデル名重複させないようひたすら意識することにする。
                //デバックモードで十分テストせよ。
                //Actor は派生しているのに、ModelのEffectは、親のActorと違う、しかもSet系。そんな関係に注意せよ。（レーザーチップとか・・・）
                //TODO:重複しないようにする仕組みをなんとかする

                //UVオフセット設定
                pSpriteMeshSetActor->_pUvFlipper->getUV(u, v);
                hr = pID3DXEffect->SetFloat(_pMeshSetEffect->_ah_offset_u[_draw_set_num], u);
                checkDxException(hr, D3D_OK, "GgafDxSpriteMeshSetActor::processDraw() SetMatrix(_h_offset_u) に失敗しました。");
                hr = pID3DXEffect->SetFloat(_pMeshSetEffect->_ah_offset_v[_draw_set_num], v);
                checkDxException(hr, D3D_OK, "GgafDxSpriteMeshSetActor::processDraw() SetMatrix(_h_offset_v) に失敗しました。");


                _draw_set_num++;
                if (_draw_set_num >= _pMeshSetModel->_set_num) {
                    break;
                }
                pDrawActor = pDrawActor->_pNext_TheSameDrawDepthLevel;
            } else {
                break;
            }
        } else {
            break;
        }
    }
    GgafDxUniverse::_pActor_DrawActive = pSpriteMeshSetActor; //描画セットの最後アクターをセット
    _pMeshSetModel->draw(this, _draw_set_num);
}


GgafDxSpriteMeshSetActor::~GgafDxSpriteMeshSetActor() {
    DELETE_IMPOSSIBLE_NULL(_pUvFlipper);
}
