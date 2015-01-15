#include "EnemyStraeaLaserChip004.h"

#include "jp/ggaf/dxcore/actor/supporter/GgafDxSeTransmitterForActor.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxKuroko.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"
#include "jp/gecchi/VioletVreath/God.h"
#include "jp/ggaf/lib/util/spline/SplineKurokoLeader.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

//GgafDxCore::GgafDxTextureConnection* EnemyStraeaLaserChip004::pTexCon1_ = nullptr;
//GgafDxCore::GgafDxTextureConnection* EnemyStraeaLaserChip004::pTexCon2_ = nullptr;

EnemyStraeaLaserChip004::EnemyStraeaLaserChip004(const char* prm_name) :
        HomingLaserChip(prm_name, "StraeaLaserChip001", STATUS(EnemyStraeaLaserChip004)) {
    _class_name = "EnemyStraeaLaserChip004";
    pConn_pSplManuf_ = getConnection_SplineManufactureManager("GURUGURU");
    pKurokoLeader_ = pConn_pSplManuf_->peek()->createKurokoLeader(getKuroko());
//    if (pTexCon1_ == nullptr) {
//        pTexCon1_ = getConnection_ModelTextureManager("StraeaLaserChip001.png");
//        pTexCon2_ = getConnection_ModelTextureManager("EsperiaLaserChip001.png");
//        pModel->setMaterialTexture(0, pTexCon1_);
//
//    }

}

void EnemyStraeaLaserChip004::initialize() {
    registerHitAreaCube_AutoGenMidColli(20000);
    setHitAble(true, false);
    setScaleR(5.0);
    setAlpha(0.9);
}

void EnemyStraeaLaserChip004::onCreateModel() {

}

void EnemyStraeaLaserChip004::onActive() {
    HomingLaserChip::onActive();
    //�X�e�[�^�X���Z�b�g
    getStatus()->reset();
    GgafDxKuroko* pKuroko = getKuroko();
    pKuroko->setMvVelo(10000);
    pKuroko->setMvAcce(300);
    //pKuroko->forceMvVeloRange(0, 70000);
    pKuroko->relateFaceByMvAng(true);
    pKurokoLeader_->stop();
    _force_alpha = 1.50; //�ŏ��͂�����Ɩ����
}

void EnemyStraeaLaserChip004::processBehaviorHeadChip() {
//    //--->debug
//    if (GgafDxInput::isBeingPressedKey(DIK_N)) {
//        GgafDxTextureConnection* a = pModel->_papTextureConnection[0];
//        GgafDxTextureConnection* b = pModel->_papTextureConnection[1];
//        pModel->_papTextureConnection[0] = b;
//        pModel->_papTextureConnection[1] = a;
//    }
//    if (GgafDxInput::isBeingPressedKey(DIK_M)) {
//        pModel->setMaterialTexture(0, pTexCon2_);
//    }
//    //<--debug

    if (getActiveFrame() == 2) {
        pKurokoLeader_->start(SplineKurokoLeader::RELATIVE_DIRECTION); //�����������Ƀ��[���h�ϊ�
    }
    pKurokoLeader_->behave(); //���r���ł���񂬂ꂽ�炾�߂����
    getKuroko()->behave();
}

void EnemyStraeaLaserChip004::onHit(GgafActor* prm_pOtherActor) {
    GgafDxGeometricActor* pOther = (GgafDxGeometricActor*)prm_pOtherActor;
    //�q�b�g��
    //�̗͌v�Z
    int sta = UTIL::calcEnemyStamina(this, pOther);
    if (sta <= 0) {
        //�q�b�g���ď��Ŏ�
        sayonara();
    } else {
        //�q�b�g���Đ�����
    }
}

EnemyStraeaLaserChip004::~EnemyStraeaLaserChip004() {
    GGAF_DELETE(pKurokoLeader_);
    pConn_pSplManuf_->close();
    //if (pTexCon1_) {
    //    pTexCon1_->close();
    //    pTexCon1_ = nullptr;
    //}
    //if (pTexCon2_) {
    //    pTexCon2_->close();
    //    pTexCon2_ = nullptr;
    //}
}

