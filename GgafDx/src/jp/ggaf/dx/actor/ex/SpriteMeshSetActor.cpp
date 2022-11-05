#include "jp/ggaf/dx/actor/ex/SpriteMeshSetActor.h"

#include "jp/ggaf/dx/actor/supporter/UvFlipper.h"
#include "jp/ggaf/dx/effect/MeshSetEffect.h"
#include "jp/ggaf/dx/exception/CriticalException.h"
#include "jp/ggaf/dx/Config.h"
#include "jp/ggaf/dx/manager/TextureConnection.h"
#include "jp/ggaf/dx/model/MeshSetModel.h"
#include "jp/ggaf/dx/scene/Spacetime.h"
#include "jp/ggaf/dx/util/Util.h"


using namespace GgafDx;

SpriteMeshSetActor::SpriteMeshSetActor(const char* prm_name,
                                       const char* prm_model,
                                       CollisionChecker* prm_pChecker) :

                                               MeshSetActor(prm_name,
                                                            prm_model,
                                                            "SpriteMeshSetEffect",
                                                            "SpriteMeshSetTechnique",
                                                            prm_pChecker) {

    _obj_class |= Obj_GgafDx_SpriteMeshSetActor;
    _class_name = "SpriteMeshSetActor";

    Texture* pTexture = getModel()->getDefaultTextureConnection()->peek();
    _pUvFlipper = NEW UvFlipper(pTexture);
    _pUvFlipper->locatePatternNo(1, 1);
    _pUvFlipper->setActivePtn(0);
    _pUvFlipper->exec(NOT_ANIMATED, 1);
}


void SpriteMeshSetActor::processDraw() {

    int draw_set_num = 0; //SpriteMeshSetActorの同じモデルで同じテクニックが
                       //連続しているカウント数。同一描画深度は一度に描画する。
    ID3DXEffect* const pID3DXEffect = _pMeshSetEffect->_pID3DXEffect;
    HRESULT hr;
    FigureActor* pDrawActor = this;
    SpriteMeshSetActor* pSpriteMeshSetActor = nullptr;
    int model_draw_set_num = _pMeshSetModel->_draw_set_num;
    float u = 0;
    float v = 0;
    while (pDrawActor) {
        if (pDrawActor->getModel() == _pMeshSetModel && pDrawActor->_hash_technique == _hash_technique) {
            pSpriteMeshSetActor = (SpriteMeshSetActor*)pDrawActor;

            hr = pID3DXEffect->SetMatrix(_pMeshSetEffect->_ah_matWorld[draw_set_num], &(pSpriteMeshSetActor->_matWorld));
            checkDxException(hr, D3D_OK, "SetMatrix(g_matWorld) に失敗しました。");
            hr = pID3DXEffect->SetValue(_pMeshSetEffect->_ah_materialDiffuse[draw_set_num], &(pSpriteMeshSetActor->_paMaterial[0].Diffuse), sizeof(D3DCOLORVALUE) );
            checkDxException(hr, D3D_OK, "SetValue(g_colMaterialDiffuse) に失敗しました。");
#ifdef MY_DEBUG
            if (pDrawActor->instanceOf(Obj_GgafDx_SpriteMeshSetActor)) {
                //OK
            } else {
                throwCriticalException("pDrawActor["<<pDrawActor->getName()<<"] はSpriteMeshSetActorではありません。");
            }
#endif
            //[MEMO]
            //SpriteMeshSetActor は、MeshSetActor から派生しているため、モデルクラスは同じMeshSetModelである。
            //SpriteMeshSetActorが使用するモデル名("x,10,Flora"等)と、MeshSetActorが使用するモデル名が
            //同じものが存在する場合、pDrawActor は、MeshSetActor の可能性もある。
            //これは、draw_set_num を求めるロジックは同一深度で連続の同一(アドレス)モデルである。という判定しか行っていないため。
            //実はここで、SpriteMeshSetActor と MeshSetActor で同一モデル名を使用することは禁止にしたいのである。
            //本来は Actor の種類に関係なく、同じ Model で連続ならば、ステート切り替えぜず高速化することがウリであるのだが、
            //SpriteMeshSetActor は、MeshSetActor から派生しているにもかかわらず、無理やりエフェクト自体を変更している。
            //誠実に実装するならば、別物としてそれぞれ別の Model クラスを作成するべきかもしれないが、Modelクラスとしての処理自体は
            //SpriteMeshSetActor、MeshSetActor 共に全く同じで良い。
            //悩んだ結果、Model クラスを分けて実装せず、やや危険なキャストを行うこととする。
            //とりあえずSpriteMeshSetActor と、MeshSetActor のモデル名重複させないようひたすら意識することにする。
            //デバックモードで十分テストせよ。
            //Actor は派生しているのに、ModelのEffectは、親のActorと違う、しかもSet系。そんな関係に注意せよ。（レーザーチップとか・・・）
            //TODO:重複しないようにする仕組みをなんとかする

            //UVオフセット設定
            pSpriteMeshSetActor->_pUvFlipper->getUV(u, v);
            hr = pID3DXEffect->SetFloat(_pMeshSetEffect->_ah_offset_u[draw_set_num], u);
            checkDxException(hr, D3D_OK, "SetMatrix(_h_offset_u) に失敗しました。");
            hr = pID3DXEffect->SetFloat(_pMeshSetEffect->_ah_offset_v[draw_set_num], v);
            checkDxException(hr, D3D_OK, "SetMatrix(_h_offset_v) に失敗しました。");

            draw_set_num++;
            if (draw_set_num >= model_draw_set_num) {
                break;
            }
            pDrawActor = pDrawActor->_pNextRenderActor;
        } else {
            break;
        }
    }
    Spacetime::_pActor_draw_active = pSpriteMeshSetActor; //描画セットの最後アクターをセット
    _pMeshSetModel->MeshSetModel::draw(this, draw_set_num);
}


SpriteMeshSetActor::~SpriteMeshSetActor() {
    GGAF_DELETE(_pUvFlipper);
}
