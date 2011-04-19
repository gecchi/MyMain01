#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;

GgafDx9SpriteMeshSetActor::GgafDx9SpriteMeshSetActor(const char* prm_name,
                                       const char* prm_model,
                                       GgafDx9Checker* prm_pChecker) :

                                        GgafDx9MeshSetActor(prm_name,
                                                           prm_model,
                                                           "SpriteMeshSetEffect",
                                                           "SpriteMeshSetTechnique",
                                                           prm_pChecker) {

    _obj_class |= Obj_GgafDx9SpriteMeshSetActor;
    _class_name = "GgafDx9SpriteMeshSetActor";
    _pUvFlipper = NEW GgafDx9UvFlipper(this);
    _pUvFlipper->forcePtnNoRange(0, 1);
    _pUvFlipper->setPtnNo(0);
    _pUvFlipper->setFlipMethod(NOT_ANIMATED, 1);
}


void GgafDx9SpriteMeshSetActor::processDraw() {

    _draw_set_num = 0; //GgafDx9SpriteMeshSetActorの同じモデルで同じテクニックが
                       //連続しているカウント数。同一描画深度は一度に描画する。
    ID3DXEffect* pID3DXEffect = _pMeshSetEffect->_pID3DXEffect;
    HRESULT hr;
    GgafDx9DrawableActor* pDrawActor = this;
    GgafDx9SpriteMeshSetActor* pSpriteMeshSetActor = NULL;
    float u = 0;
    float v = 0;
    while (true) {
        if (pDrawActor)  {
            if (pDrawActor->_pGgafDx9Model == _pMeshSetModel && pDrawActor->_hash_technique == _hash_technique) {
                pSpriteMeshSetActor = (GgafDx9SpriteMeshSetActor*)pDrawActor;

                hr = pID3DXEffect->SetMatrix(_pMeshSetEffect->_ah_matWorld[_draw_set_num], &(pSpriteMeshSetActor->_matWorld));
                checkDxException(hr, D3D_OK, "GgafDx9SpriteMeshSetActor::processDraw() SetMatrix(g_matWorld) に失敗しました。");
                hr = pID3DXEffect->SetValue(_pMeshSetEffect->_ah_materialDiffuse[_draw_set_num], &(pSpriteMeshSetActor->_paD3DMaterial9[0].Diffuse), sizeof(D3DCOLORVALUE) );
                checkDxException(hr, D3D_OK, "GgafDx9SpriteMeshSetActor::processDraw() SetValue(g_colMaterialDiffuse) に失敗しました。");
        #ifdef MY_DEBUG
                if (pDrawActor->_obj_class & Obj_GgafDx9SpriteMeshSetActor) {
                    //OK
                } else {
                    throwGgafCriticalException("GgafDx9SpriteMeshSetActor::processDraw() pDrawActor["<<pDrawActor->getName()<<"] はGgafDx9SpriteMeshSetActorではありません。");
                }
        #endif
                //[MEMO]
                //GgafDx9SpriteMeshSetActor は、GgafDx9MeshSetActor から派生しているため、モデルクラスは同じGgafDx9MeshSetModelである。
                //GgafDx9SpriteMeshSetActorが使用するモデル名("x/10/Flora"等)と、GgafDx9MeshSetActorが使用するモデル名が
                //同じものが存在する場合、pDrawActor は、GgafDx9MeshSetActor の可能性もある。
                //これは、_draw_set_num を求めるロジックは同一深度で連続の同一(アドレス)モデルである。という判定しか行っていないため。
                //実はここで、GgafDx9SpriteMeshSetActor と GgafDx9MeshSetActor で同一モデル名を使用することは禁止にしたいのである。
                //本来は Actor の種類に関係なく、同じ Model で連続ならば、ステート切り替えぜず高速化することがウリであるのだが、
                //GgafDx9SpriteMeshSetActor は、GgafDx9MeshSetActor から派生しているにもかかわらず、無理やりエフェクト自体を変更している。
                //誠実に実装するならば、別物としてそれぞれ別の Model クラスを作成するべきかもしれないが、Modelクラスとしての処理自体は
                //GgafDx9SpriteMeshSetActor、GgafDx9MeshSetActor 共に全く同じで良い。
                //悩んだ結果、Model クラスを分けて実装せず、やや危険なキャストを行うこととする。
                //とりあえずGgafDx9SpriteMeshSetActor と、GgafDx9MeshSetActor のモデル名重複させないようひたすら意識することにする。
                //デバックモードで十分テストせよ。
                //Actor は派生しているのに、ModelのEffectは、親のActorと違う、しかもSet系。そんな関係に注意せよ。（レーザーチップとか・・・）
                //TODO:重複しないようにする仕組みをなんとかする

                //UVオフセット設定
                pSpriteMeshSetActor->_pUvFlipper->getUV(u, v);
                hr = pID3DXEffect->SetFloat(_pMeshSetEffect->_ahOffsetU[_draw_set_num], u);
                checkDxException(hr, D3D_OK, "GgafDx9SpriteMeshSetActor::processDraw() SetMatrix(_h_offset_u) に失敗しました。");
                hr = pID3DXEffect->SetFloat(_pMeshSetEffect->_ahOffsetV[_draw_set_num], v);
                checkDxException(hr, D3D_OK, "GgafDx9SpriteMeshSetActor::processDraw() SetMatrix(_h_offset_v) に失敗しました。");


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
    GgafDx9Universe::_pActor_DrawActive = pSpriteMeshSetActor; //描画セットの最後アクターをセット
    _pMeshSetModel->draw(this, _draw_set_num);
}


GgafDx9SpriteMeshSetActor::~GgafDx9SpriteMeshSetActor() {
    DELETE_IMPOSSIBLE_NULL(_pUvFlipper);
}
