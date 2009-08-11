#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;


LaserChip::LaserChip(const char* prm_name, const char* prm_model) :
    GgafDx9MeshSetActor(prm_name,
                     prm_model,
                     "LaserChipEffect",
                     "LaserChipTechnique",
                     NEW StgChecker(this) ) {
    _pStgChecker = (StgChecker*)_pChecker;
    _pMover = NEW GgafDx9GeometryMover(this);


    _class_name = "LaserChip";
    _pChip_front = NULL;
    _pChip_behind = NULL;
    _pDispatcher = NULL; //LaserChipDispatcherの new 時に設定される。
    _chiptex_kind = 1;
    _ahKind[0]  = _pMeshSetEffect->_pID3DXEffect->GetParameterByName( NULL, "g_kind001" );
    _ahKind[1]  = _pMeshSetEffect->_pID3DXEffect->GetParameterByName( NULL, "g_kind002" );
    _ahKind[2]  = _pMeshSetEffect->_pID3DXEffect->GetParameterByName( NULL, "g_kind003" );
    _ahKind[3]  = _pMeshSetEffect->_pID3DXEffect->GetParameterByName( NULL, "g_kind004" );
    _ahKind[4]  = _pMeshSetEffect->_pID3DXEffect->GetParameterByName( NULL, "g_kind005" );
    _ahKind[5]  = _pMeshSetEffect->_pID3DXEffect->GetParameterByName( NULL, "g_kind006" );
    _ahKind[6]  = _pMeshSetEffect->_pID3DXEffect->GetParameterByName( NULL, "g_kind007" );
    _ahKind[7]  = _pMeshSetEffect->_pID3DXEffect->GetParameterByName( NULL, "g_kind008" );
    _ahRevPosZ[0]  = _pMeshSetEffect->_pID3DXEffect->GetParameterByName( NULL, "g_RevPosZ001" );
    _ahRevPosZ[1]  = _pMeshSetEffect->_pID3DXEffect->GetParameterByName( NULL, "g_RevPosZ002" );
    _ahRevPosZ[2]  = _pMeshSetEffect->_pID3DXEffect->GetParameterByName( NULL, "g_RevPosZ003" );
    _ahRevPosZ[3]  = _pMeshSetEffect->_pID3DXEffect->GetParameterByName( NULL, "g_RevPosZ004" );
    _ahRevPosZ[4]  = _pMeshSetEffect->_pID3DXEffect->GetParameterByName( NULL, "g_RevPosZ005" );
    _ahRevPosZ[5]  = _pMeshSetEffect->_pID3DXEffect->GetParameterByName( NULL, "g_RevPosZ006" );
    _ahRevPosZ[6]  = _pMeshSetEffect->_pID3DXEffect->GetParameterByName( NULL, "g_RevPosZ007" );
    _ahRevPosZ[7]  = _pMeshSetEffect->_pID3DXEffect->GetParameterByName( NULL, "g_RevPosZ008" );
    _ahMatWorld_front[0]  = _pMeshSetEffect->_pID3DXEffect->GetParameterByName( NULL, "g_matWorld_front001" );
    _ahMatWorld_front[1]  = _pMeshSetEffect->_pID3DXEffect->GetParameterByName( NULL, "g_matWorld_front002" );
    _ahMatWorld_front[2]  = _pMeshSetEffect->_pID3DXEffect->GetParameterByName( NULL, "g_matWorld_front003" );
    _ahMatWorld_front[3]  = _pMeshSetEffect->_pID3DXEffect->GetParameterByName( NULL, "g_matWorld_front004" );
    _ahMatWorld_front[4]  = _pMeshSetEffect->_pID3DXEffect->GetParameterByName( NULL, "g_matWorld_front005" );
    _ahMatWorld_front[5]  = _pMeshSetEffect->_pID3DXEffect->GetParameterByName( NULL, "g_matWorld_front006" );
    _ahMatWorld_front[6]  = _pMeshSetEffect->_pID3DXEffect->GetParameterByName( NULL, "g_matWorld_front007" );
    _ahMatWorld_front[7]  = _pMeshSetEffect->_pID3DXEffect->GetParameterByName( NULL, "g_matWorld_front008" );
}

void LaserChip::initialize() {

    _pMover->setMoveVelocity(30000);
    _pStgChecker->useHitAreaBoxNum(1);
    _pStgChecker->setHitAreaBox(0, -30000, -30000, -30000, 30000, 30000, 30000);
    //_pStgChecker->setHitAreaBox(1, -30000, -30000, -30000, 30000, 30000, 30000);
    setBumpable(true);
    _fAlpha = 0.9;
}


void LaserChip::onActive() {
    //出現時
    _chiptex_kind = 1;
    if (_pChip_front == NULL) {
        if (_pDispatcher->_pSeConnection) {
            _pDispatcher->_pSeConnection->view()->play();
        }
    }

    _pDispatcher->_num_chip_active++;
    //レーザーは、真っ直ぐ飛ぶだけなので、ココで行列をつくり計算回数を節約。
    //後でdx,dy,dzだけ更新する。
    GgafDx9GeometricActor::getWorldMatrix_ScRxRzRyMv(this, _matWorld);
}

void LaserChip::onInactive() {
    //消失時
    _pDispatcher->_num_chip_active--;
    //前後の繋がりを切断
    if (_pChip_front) {
        _pChip_front->_pChip_behind = NULL;
    }
    _pChip_front = NULL;
    if (_pChip_behind) {
        _pChip_behind->_pChip_front = NULL;
    }
    _pChip_behind = NULL;

}

void LaserChip::processBehavior() {

    //座標に反映
    _pMover->behave();
/*
    //中間地点にも当たり判定
    static int centerX, centerY, centerZ;
    if (_pChip_front != NULL) {
      centerX = (_X - _pChip_front->_X) / 2;
      centerY = (_Y - _pChip_front->_Y) / 2;
      centerZ = (_Z - _pChip_front->_Z) / 2;
      _pStgChecker->setHitAreaBox(
                      1,
                      centerX - 30000,
                      centerY - 30000,
                      centerZ - 30000,
                      centerX + 30000,
                      centerY + 30000,
                      centerZ + 30000
                 ); //中間の当たり判定
      _pStgChecker->getHitAreaBoxs()->enable(1);
    } else {
      _pStgChecker->getHitAreaBoxs()->disable(1);

    }
*/

}

void LaserChip::processJudgement() {
    if (isOffScreen()) {
        inactivate();
    }

    //レーザー種別  1:末尾 2:中間 3:先頭 （末尾かつ先頭は末尾が優先）
    if (_pChip_front) {
        if (_pChip_behind) {
            if (_pChip_behind->isActive()) {
                if (_pChip_front->_pChip_front) {
                    _chiptex_kind = 2; //中間テクスチャ
                } else {
                    _chiptex_kind = 3; //先頭テクスチャ
                }
            } else {
                _chiptex_kind = 1; //発射元の末尾テクスチャ
            }
        } else {
            _chiptex_kind = 1; //末尾テクスチャ
        }
    } else {
        _chiptex_kind = 4; //何も描画したくない
    }

    //【注意】4/15 メモ
    //奥から描画となるので processDrawXxxx は、同一フレーム内で _pChip_front が必ずしも先に実行されとは限らない。
    //processBehavior,processJudgementは _pChip_front が必ず先に実行される。
    //描画時に_pChip_frontも使用するためここで設定しとく必要がある。
    GgafDx9GeometricActor::updateWorldMatrix_Mv(this, _matWorld);
}

void LaserChip::processDrawMain() {
    _draw_set_num = 1; //同一描画深度に、GgafDx9MeshSetActorの同じモデルが連続しているカウント数
    GgafDx9DrawableActor* _pNextDrawActor = _pNext_TheSameDrawDepthLevel;
    while (true) {
        if (_pNextDrawActor != NULL)  {
            GgafDx9Model* pGgafDx9Model =  _pNextDrawActor->_pGgafDx9Model;
            if (pGgafDx9Model == _pMeshSetModel && _pNextDrawActor->isActive()) {
                _draw_set_num++;
                if (_draw_set_num > 8) {
                    _draw_set_num = 8;
                    break;
                }
                _pNextDrawActor= _pNextDrawActor->_pNext_TheSameDrawDepthLevel;
            } else {
                break;
            }
        } else {
            break;
        }
    }
    static ID3DXEffect* pID3DXEffect;
    pID3DXEffect = _pMeshSetEffect->_pID3DXEffect;

    HRESULT hr;

    //VIEW変換行列
    hr = pID3DXEffect->SetMatrix(_pMeshSetEffect->_hMatView, &pCAM->_vMatrixView);
    mightDx9Exception(hr, D3D_OK, "LaserChip::processDrawMain() SetMatrix(_hMatView) に失敗しました。");
    hr = pID3DXEffect->SetInt(_pMeshSetEffect->_h_nVertexs, _pMeshSetModel->_nVertices);
    mightDx9Exception(hr, D3D_OK, "LaserChip::processDrawMain() SetInt(_h_nVertexs) に失敗しました。2");

    LaserChip *pDrawLaserChipActor;
    pDrawLaserChipActor = this;

    bool rev_pos_Z; //true = 頂点のZを-1を乗ずる。false = 何もしない
    float slant;
    float crossCamX;

//    float x1;
//    float y1;
//    float z1;
//    float x2;
//    float y2;
//    float z2;
    float DBF;
    float DBT;
    float DLF; //distance left from
    float DLT; //distance left to
    float DRF; //distance right from
    float DRT; //distance right to






    for (int i = 0; i < _draw_set_num; i++) {
        hr = pID3DXEffect->SetMatrix(_pMeshSetEffect->_ahMatWorld[i], &(pDrawLaserChipActor->_matWorld));
        mightDx9Exception(hr, D3D_OK, "LaserChip::processDrawMain() SetMatrix(g_matWorld) に失敗しました。");

        //テクスチャ種類
        hr = pID3DXEffect->SetInt(_ahKind[i], pDrawLaserChipActor->_chiptex_kind);
        mightDx9Exception(hr, D3D_OK, "LaserChip::processDrawMain() SetInt(_hKind) に失敗しました。2");

        if (pDrawLaserChipActor->_pChip_front != NULL) {
            hr = pID3DXEffect->SetMatrix(_ahMatWorld_front[i], &(pDrawLaserChipActor->_pChip_front->_matWorld));
            mightDx9Exception(hr, D3D_OK, "LaserChip::processDrawMain() SetMatrix(_hMatWorld_front) に失敗しました。1");

            //手前な向きなチップか、奥向きなチップか
            //自身の座標 ～ 視錐台奥面 の距離(D1)、前方チップ座標 ～ 視錐台奥面 の距離(D2) を比較して
            //D1 > D2 ならば手前な向きなチップ。
            //D1 < D2 ならば奥向きなチップ。
            //D1 = D2 ならば真横
//            x1 = pDrawLaserChipActor->_matWorld._41;
//            y1 = pDrawLaserChipActor->_matWorld._42;
//            z1 = pDrawLaserChipActor->_matWorld._43;
//            x2 = pDrawLaserChipActor->_pChip_front->_matWorld._41;
//            y2 = pDrawLaserChipActor->_pChip_front->_matWorld._42;
//            z2 = pDrawLaserChipActor->_pChip_front->_matWorld._43;
//
//            _TRACE_("(x1,y1,z1)=("<<x1<<","<<y1<<","<<z1<<")");
//            _TRACE_("(x2,y2,z2)=("<<x2<<","<<y2<<","<<z2<<")");
//
//
//            D1 = GgafDx9Universe::_pCamera->_plnBack.a*x1 +
//                 GgafDx9Universe::_pCamera->_plnBack.b*y1 +
//                 GgafDx9Universe::_pCamera->_plnBack.c*z1 +
//                 GgafDx9Universe::_pCamera->_plnBack.d;
//            D2 = GgafDx9Universe::_pCamera->_plnBack.a*x2 +
//                 GgafDx9Universe::_pCamera->_plnBack.b*y2 +
//                 GgafDx9Universe::_pCamera->_plnBack.c*z2 +
//                 GgafDx9Universe::_pCamera->_plnBack.d;


            DBF = -1.0 * pDrawLaserChipActor->_fDistance_plnBack;
            DBT = -1.0 * pDrawLaserChipActor->_pChip_front->_fDistance_plnBack;

            DLF = -1.0 * pDrawLaserChipActor->_fDistance_plnLeft;
            DLT = -1.0 * pDrawLaserChipActor->_pChip_front->_fDistance_plnLeft;
            DRF = -1.0 * pDrawLaserChipActor->_fDistance_plnRight;
            DRT = -1.0 * pDrawLaserChipActor->_pChip_front->_fDistance_plnRight;
            //  DLF / DLT  = DRF / DRT となった場合、
            // 視点を通るのじゃないのか？
            //  DLF / DLT  < DRF / DRT となった場合、
            // 左の壁にぶつかるのじゃないのか？
            //  DLF / DLT  < DRF / DRT となった場合、
            // 右の壁にぶつかるのじゃないのか？

            if (DLF / DLT  < DRF / DRT) {
                //視錐台左平面にぶつかる
                rev_pos_Z = true;
            } else if (DLF / DLT  > DRF / DRT) {
                //視錐台右平面にぶつかる
                rev_pos_Z = false;
            } else {
                rev_pos_Z = false;
            }



//            DBF = -1.0 * pDrawLaserChipActor->_fDistance_plnBack;
//            DBT = -1.0 * pDrawLaserChipActor->_pChip_front->_fDistance_plnBack;
//
//            DLF = -1.0 * pDrawLaserChipActor->_fDistance_plnLeft;
//            DLT = -1.0 * pDrawLaserChipActor->_pChip_front->_fDistance_plnLeft;
//            DRF = -1.0 * pDrawLaserChipActor->_fDistance_plnRight;
//            DRT = -1.0 * pDrawLaserChipActor->_pChip_front->_fDistance_plnRight;
//            if (DBF < DBT) {
//                if (DLF < DLT) {
//                    //視錐台右平面にぶつかる
//                    rev_pos_Z = false;
//                } else if (DRF < DRT) {
//                    //視錐台左平面にぶつかる
//                    rev_pos_Z = true;
//                } else if (DLF > DLT && DRF > DRT) {
//                    if (DLF < DRF && DLT < DRT) {
//                        //視錐台左平面にぶつかる
//                        rev_pos_Z = true;
//                    } else if (DLF > DRF && DLT > DRT) {
//                        //視錐台右平面にぶつかる
//                        rev_pos_Z = false;
//                    } else if (DLF < DRF && DLT > DRT) {
//                        //視錐台右平面にぶつかる
//                        rev_pos_Z = false;
//                    } else if (DLF > DRF && DLT < DRT) {
//                        //視錐台左平面にぶつかる
//                        rev_pos_Z = true;
//                    }
//                } else {
//                    _TRACE_("おかしいのではA？ DBF="<<DBF<<",DBT="<<DBT<<",DLF="<<DLF<<",DLT="<<DLT<<",DRF="<<DRF<<",DRT="<<DRT<<"");
//                }
//            } else {
//                if (DLF < DLT) {
//                    //視錐台左平面にぶつかる
//                    rev_pos_Z = true;
//                } else if (DRF < DRT) {
//                    //視錐台右平面にぶつかる
//                    rev_pos_Z = false;
//                } else if (DLF > DLT && DRF > DRT) {
//                    if (DLF < DRF && DLT < DRT) {
//                        //視錐台右平面にぶつかる
//                        rev_pos_Z = false;
//                    } else if (DLF > DRF && DLT > DRT) {
//                        //視錐台左平面にぶつかる
//                        rev_pos_Z = true;
//                    } else if (DLF < DRF && DLT > DRT) {
//                        //視錐台左平面にぶつかる
//                        rev_pos_Z = true;
//                    } else if (DLF > DRF && DLT < DRT) {
//                        //視錐台右平面にぶつかる
//                        rev_pos_Z = false;
//                    }
//                } else {
//                    _TRACE_("おかしいのではB？ DBF="<<DBF<<",DBT="<<DBT<<",DLF="<<DLF<<",DLT="<<DLT<<",DRF="<<DRF<<",DRT="<<DRT<<"");
//                }
//            }

//            _TRACE_("D1="<<D1<<"  D2="<<D2<<"");
//
//
//           if (D1 > D2){
//               _TRACE_("手前向き！");
//           } else if (D1 < D2) {
//               _TRACE_("奥前向き！");
//           } else {
//               _TRACE_("まよっこ");
//           }
//


//            //チップの十字の左右の羽の描画順序を考える。
//            slant = (pDrawLaserChipActor->_pChip_front->_Z - pDrawLaserChipActor->_Z)*1.0 / (pDrawLaserChipActor->_pChip_front->_X - pDrawLaserChipActor->_X)*1.0;
//            if (pDrawLaserChipActor->_pChip_front->_X == pDrawLaserChipActor->_X) {
//                rev_pos_Z = false;
//            } else if (pCAM->_view_border_slant2_XZ < slant && slant < pCAM->_view_border_slant1_XZ) {
//                if (pDrawLaserChipActor->_pChip_front->_X > pDrawLaserChipActor->_X ) {
//                    rev_pos_Z = false;
//                } else {
//                    rev_pos_Z = true;
//                }
//            } else {
//                if (pDrawLaserChipActor->_pChip_front->_Z == pDrawLaserChipActor->_Z) {
//                    rev_pos_Z = false;
//                } else {
//                    //＜2009/5/19 メモ：rev_pos_Zは何を判定しようとしているのか＞
//                    //頂点Z座標を反転(-1倍)して描画とはチップの羽の描画順序を逆にするかどうかの判断をする。
//                    //羽とは下図（レーザーのチップのローカル座標図）の①と④のポリゴンのことを指す。
//                    //頂点インデックス（＝描画順序）は①②③④の順番になっている。
//                    //ワールド変換後、カメラから下図ような角度でチップが見える場合、 ①が一番奥まった場所、④は一番手前側にあるので綺麗に描画されるが、
//                    //①、④の奥手前が逆になってしまう角度（＝カメラの左を通過するような角度）だと、ギザギザな描画になってしまう。
//                    //
//                    //         ↑ｙ軸
//                    //         │
//                    //
//                    //          ＼
//                    //         │ ＼
//                    //         │② ＼
//                    //  (0,0,0)│    ┃        ｚ軸
//                    // ────┘----┃─   ─→
//                    //  ＼  ④ ：＼  ┃   ＼
//                    //    ＼   ：  ＼┃  ① ＼
//                    //       ━━━━╋━━━━
//                    //         │    ┃
//                    //          ＼ ③┃  ＼
//                    //            ＼ ┃    ＼ ｘ軸（方向）
//                    //               ┃      ┘
//                    //
//                    //XZ平面において、レーザーチップがカメラの右を通過するのか左を通過するのか、
//                    //２点(X1,Z1)(X2,Z2) を通る直線の方程式において、 Z = CamZ の時のX座標は
//                    //X = ((CamZ-Z1)*(X2-X1)/ (Z2-Z1))+X1 となる。２点にチップの座標、一つ先のチップの座標を代入し
//                    //この式のXがCamXより小さければのカメラ左を通過することになる。その場合チップの頂点バッファのZ座標を反転(-1倍)し描画する。
//                    //Z座標を反転描画しなければならない場合 rev_pos_Z = true としてシェーダーに渡すこととする。
//                    crossCamX = ((float)(pCAM->_Z - pDrawLaserChipActor->_Z)) *
//                                 ((float)(pDrawLaserChipActor->_pChip_front->_X - pDrawLaserChipActor->_X) /
//                                  (float)(pDrawLaserChipActor->_pChip_front->_Z - pDrawLaserChipActor->_Z)
//                                 ) + pDrawLaserChipActor->_X;
//
//                    //TODO:
//                    //それよりXZ平面においｔ、チップ座標とViewPointを結ぶ直線の傾きと
//                    //チップと次のチップが作る傾きを比較すればよい
//                    //ViewPointが第１～４象限によって判定は変わるでしょう。注意
//
//
//                    if (crossCamX < pCAM->_X) {
//                        rev_pos_Z = true;
//                    } else {
//                        rev_pos_Z = false;
//                    }
//                }
//
//                if (pDrawLaserChipActor->_pChip_front->_Z > pDrawLaserChipActor->_Z) {
//                    //これまでの上記の判定は全てレーザーは奥から手前へ来てる場合の判定。
//                    //もし手前から奥へ飛んでいる場合は、Z座標を反転の判定は逆になる。
//
//
//                    //TODO:何を持って奥とするか。今はZ座標にしているが・・・
//                    rev_pos_Z = !rev_pos_Z;
//                }
//            }
            hr = pID3DXEffect->SetBool(_ahRevPosZ[i], rev_pos_Z);
            mightDx9Exception(hr, D3D_OK, "LaserChip::processDrawMain() SetBool(_hRevPosZ) に失敗しました。1");

        } else {
            hr = pID3DXEffect->SetMatrix(_ahMatWorld_front[i], &(pDrawLaserChipActor->_matWorld) ); //先頭がないので自信の_matWorld
            mightDx9Exception(hr, D3D_OK, "LaserChip::processDrawMain() SetMatrix(_hMatWorld_front) に失敗しました。2");
            hr = pID3DXEffect->SetBool(_ahRevPosZ[i], false);
            mightDx9Exception(hr, D3D_OK, "LaserChip::processDrawMain() SetBool(_hRevPosZ) に失敗しました。2");
        }
        pDrawLaserChipActor = (LaserChip*)(pDrawLaserChipActor -> _pNext_TheSameDrawDepthLevel);
        if (i > 0) {
            //アクティブを進める
            GgafDx9Universe::_pActor_DrawActive = GgafDx9Universe::_pActor_DrawActive->_pNext_TheSameDrawDepthLevel;
        }
    }

    _pMeshSetModel->draw(this);
}

#ifdef OREDEBUG

void LaserChip::processDrawTerminate() {
    //当たり判定領域表示
    if (GgafDx9God::_d3dfillmode == D3DFILL_WIREFRAME) {
        GgafDx9God::_pID3DDevice9->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
        DelineateActor::get()->drawHitarea(_pStgChecker);
        GgafDx9God::_pID3DDevice9->SetRenderState(D3DRS_FILLMODE, GgafDx9God::_d3dfillmode);
    }
}

#else

void LaserChip::processDrawTerminate() {}

#endif

void LaserChip::processOnHit(GgafActor* prm_pActor_Opponent) {
}

LaserChip::~LaserChip() {
    DELETE_IMPOSSIBLE_NULL(_pStgChecker);
    DELETE_IMPOSSIBLE_NULL(_pMover);

}

