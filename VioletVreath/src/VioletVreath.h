#ifndef VIOLETVREATHHEADER_H_
#define VIOLETVREATHHEADER_H_
#include "VioletVreath.h"

//�uDirectX���C�u�����v�𗘗p����i���p�҂͉��I�j�ꍇ
//����"GgafLibCommonHeader.h"�w�b�_���C���N���[�h���܂��B

#include "GgafLibCommonHeader.h"

//��ʒ萔
//�Ӗ��͎����u��ʑ��֒�`�R�s�y�c�[��.xls�v���Q��
#define KIND_EFFECT                    (0x0U)  // 00000000000000000000000000000000
#define KIND_MY_SHOT_CHIKEI_HIT        (0x8U)  // 00000000000000000000000000001000
#define KIND_MY_SHOT_CHIKEI_THRU      (0x10U)  // 00000000000000000000000000010000
#define KIND_MY_BODY_CHIKEI_HIT       (0x20U)  // 00000000000000000000000000100000
#define KIND_MY_BODY_CHIKEI_THRU      (0x40U)  // 00000000000000000000000001000000
#define KIND_ENEMY_SHOT_CHIKEI_HIT    (0x80U)  // 00000000000000000000000010000000
#define KIND_ENEMY_SHOT_CHIKEI_THRU  (0x100U)  // 00000000000000000000000100000000
#define KIND_ENEMY_BODY_CHIKEI_HIT   (0x200U)  // 00000000000000000000001000000000
#define KIND_ENEMY_BODY_CHIKEI_THRU  (0x400U)  // 00000000000000000000010000000000
#define KIND_ITEM_CHIKEI_HIT         (0x800U)  // 00000000000000000000100000000000
#define KIND_ITEM_CHIKEI_THRU       (0x1000U)  // 00000000000000000001000000000000
#define KIND_CHIKEI_CHIKEI_HIT      (0x2000U)  // 00000000000000000010000000000000
#define KIND_CHIKEI_CHIKEI_THRU     (0x4000U)  // 00000000000000000100000000000000
//��ʒ萔�i���@�E�G�A�����ޕʁj
#define KIND_MY_SHOT    (KIND_MY_SHOT_CHIKEI_HIT|KIND_MY_SHOT_CHIKEI_THRU)
#define KIND_MY_BODY    (KIND_MY_BODY_CHIKEI_HIT|KIND_MY_BODY_CHIKEI_THRU)
#define KIND_ENEMY_SHOT (KIND_ENEMY_SHOT_CHIKEI_HIT|KIND_ENEMY_SHOT_CHIKEI_THRU)
#define KIND_ENEMY_BODY (KIND_ENEMY_BODY_CHIKEI_HIT|KIND_ENEMY_BODY_CHIKEI_THRU)
//��ʒ萔�i���@�E�G�A�啪�ޕʁj
#define KIND_MY (KIND_MY_SHOT|KIND_MY_BODY)
#define KIND_ENEMRY (KIND_ENEMY_SHOT|KIND_ENEMY_BODY)
//��ʒ萔�i���̑��A���ޕʁj
#define KIND_MY_CHIKEI_HIT  (KIND_MY_SHOT_CHIKEI_HIT|KIND_MY_BODY_CHIKEI_HIT)
#define KIND_MY_CHIKEI_THRU (KIND_MY_SHOT_CHIKEI_THRU|KIND_MY_BODY_CHIKEI_THRU)
#define KIND_ENEMY_CHIKEI_HIT   (KIND_ENEMY_SHOT_CHIKEI_HIT|KIND_ENEMY_BODY_CHIKEI_HIT)
#define KIND_ENEMY_CHIKEI_THRU  (KIND_ENEMY_SHOT_CHIKEI_THRU|KIND_ENEMY_BODY_CHIKEI_THRU)
#define KIND_ITEM   (KIND_ITEM_CHIKEI_HIT|KIND_ITEM_CHIKEI_THRU)
#define KIND_CHIKEI (KIND_CHIKEI_CHIKEI_HIT|KIND_CHIKEI_CHIKEI_THRU)

#define ATTRIBUTE_NOMAL       (0x0U)    //000
#define ATTRIBUTE_GU          (0x1U)    //001
#define ATTRIBUTE_CHOKI       (0x2U)    //010
#define ATTRIBUTE_PA          (0x4U)    //100

//VirtualButton.h �� define �̕ʖ����`
#define VB_SHOT1    VB_BUTTON1
#define VB_SHOT2    VB_BUTTON2
#define VB_OPTION   VB_BUTTON3
//#define VB_VIEW     VB_BUTTON4
#define VB_TURBO    VB_BUTTON5
#define VB_POWERUP  VB_BUTTON6

#define VB_VIEW_UP    VB_S1_UP
#define VB_VIEW_DOWN  VB_S1_DOWN
#define VB_VIEW_LEFT  VB_S1_LEFT
#define VB_VIEW_RIGHT VB_S1_RIGHT

//STAT_DEFAULT_ACTOR_KIND��0
enum {
    STAT_Attribute = 1,                   //����(uint)
    STAT_LockonAble,                      //���b�N�I����
    STAT_AddDestroyScorePoint,            //�j�󎞉��Z���_
    STAT_AddDamagedScorePoint,            //�_���[�W�����Z���_
    STAT_FlushAble,                       //�_���[�W���t���b�V���v��
    STAT_AddRankPoint,                    //�j�󎞉��Z�����N
    STAT_AddRankPoint_Reduction,          //�j�󎞉��Z�����N������
    STAT_Stamina,                         //�̗�
    STAT_Attack,                          //�U����
    STAT_AttackPowerRate,                 //�U���͂ɏ悶���闦
    STAT_DefaultDefenceRate,              //��h�䗦
    STAT_DominantDefenceRate,             //�D�����̖h�䗦
    STAT_RecessiveDefenceRate,            //�򐫎��̖h�䗦
    STAT_EntryEffectKind,                 //�o���G�t�F�N�g���
    STAT_LeaveEffectKind,                 //�ޏo�G�t�F�N�g���
    STAT_ExplosionEffectKind,             //�����G�t�F�N�g���
    STAT_DamagedEffectKind,               //�_���[�W���G�t�F�N�g���
    STAT_DestroyedEffectKind,             //����G�t�F�N�g���
    STAT_ItemKind,                        //����A�C�e�����
    STAT_FormationDestroyedAddScorePoint, //�ґ��S�Ŏ����Z���_
    STAT_FormationDestroyedEffectKind,    //�ґ��S�Ŏ��G�t�F�N�g
    STAT_ProperEffect01Kind,              //���̑��ŗL�G�t�F�N�g�O�P
    STAT_FormationDestroyedItemKind,      //�ґ��S�Ŏ��A�C�e�����
    STAT_AttackShotKind,                  //�V���b�g���
    STAT_DepositoryKind,                  //�V���b�g���
    STAT_RevengeShotKind,                 //�ł��Ԃ����

    STAT_BANPEI,   //�ԕ��i�z��v�f���Ɏg�p�����A��ԍŌ�ɋL�q���邱�Ɓj
};


// �ȉ��� gen01 start �` end ��Excel�}�N���ɂ�莩���������ꂽ�R�[�h�ł��B
// �R�[�h�ύX�́u�����N��`Creater.xls�v����s�����ƁB
// gen01 start
// �E�m�~�A(EnemyUnomia) �̃����N��
#define RF_EnemyUnomia_ShotWay(X)  (10+(X)*10)  //���˒e(Way)��
// �E�m�~�A�ґ�001(FormationUnomia001) �̃����N��
#define RF_FormationUnomia001_Col(X)  (RF_LL(X, 5, 10))  //��
#define RF_FormationUnomia001_Num(X)  (RF_LL(X, 20, 30))  //����
#define RF_FormationUnomia001_LaunchInterval(X)  (RF_UL(X, 12, 2))  //�o���Ԋu
#define RF_FormationUnomia001_MvVelo(X)  (RF_ULL(X, 10000, 20000))  //�ړ����x
// �E�m�~�A�ґ�002(FormationUnomia002) �̃����N��
#define RF_FormationUnomia002_Col(X)  (RF_LL(X, 5, 7))  //��
#define RF_FormationUnomia002_Num(X)  (RF_LL(X, 20, 30))  //����
#define RF_FormationUnomia002_LaunchInterval(X)  (RF_UL(X, 12, 2))  //�o���Ԋu
#define RF_FormationUnomia002_MvVelo(X)  (RF_ULL(X, 10000, 20000))  //�ړ����x
// ���X(EnemyRis) �̃����N��
#define RF_EnemyRis_ShotWay(X)  (10+(X)*10)  //���˒e(Way)��
// ���X�ґ�001(FormationRis001) �̃����N��
#define RF_FormationRis001_Num(X)  (7 + (X)*7)  //����
#define RF_FormationRis001_LaunchInterval(X)  (5 + (20 - ((X)>1.0?1.0:(X))*20))  //�o���Ԋu
#define RF_FormationRis001_MvVelo(X)  (16000+(X)*1600)  //�ړ����x
// ���X�ґ�002(FormationRis002) �̃����N��
#define RF_FormationRis002_Num(X)  (7 + (X)*7)  //����
#define RF_FormationRis002_LaunchInterval(X)  (5 + (20 - ((X)>1.0?1.0:(X))*20))  //�o���Ԋu
#define RF_FormationRis002_MvVelo(X)  (16000+(X)*1600)  //�ړ����x
// �A���X(EnemyAllas) �̃����N��
#define RF_EnemyAllas_ShotWay(X)  (10+(X)*10)  //���˒e(Way)��
// �A���X�ґ�001(FormationAllas001) �̃����N��
#define RF_FormationAllas001_Num(X)  (12+(X)*8)  //����
#define RF_FormationAllas001_LaunchInterval(X)  (5 + (20 - ((X)>1.0?1.0:(X))*20))  //�o���Ԋu
#define RF_FormationAllas001_MvVelo(X)  (10000 + (X)*10000)  //�ړ����x
// �A���X�ґ�002(FormationAllas002) �̃����N��
#define RF_FormationAllas002_Num(X)  (12+(X)*8)  //����
#define RF_FormationAllas002_LaunchInterval(X)  (5 + (20 - ((X)>1.0?1.0:(X))*20))  //�o���Ԋu
#define RF_FormationAllas002_MvVelo(X)  (10000 + (X)*10000)  //�ړ����x
// �n���A(EnemyHalia) �̃����N��
#define RF_EnemyHalia_ShotWay(X)  (20+(X)*10)  //���˒e(Way)��
// �n���A�ґ�(FormationHalia) �̃����N��
#define RF_FormationHalia_Num(X)  (7+(X)*4)  //����
#define RF_FormationHalia_LaunchInterval(X)  (5 + (20 - ((X)>1.0?1.0:(X)) *20))  //�o���Ԋu
#define RF_FormationHalia_MvVelo(X)  (14000+(X)*10000)  //�ړ����x
// �I�����X(EnemyOmulus) �̃����N��
#define RF_EnemyOmulus_ShotMvVelo(X)  (10 + (10 - ((X)>1.0?1.0:(X)) * 10))  //���˒e���x
#define RF_EnemyOmulus_ShotInterval(X)  (10 + (10 - ((X)>1.0?1.0:(X)) * 10))  //���˒e�Ԋu
// �ėp�V���b�g001(Shot001) �̃����N��
#define RF_Shot001_MvVelo(X)  (5000+(X)*5000)  //�ړ����x
#define RF_Shot001_AngVelo(X)  (6000+(X)*6000)  //�p���x
// �ėp�V���b�g002(Shot002) �̃����N��
#define RF_Shot002_MvVelo(X)  (8000+(X)*8000)  //�ړ����x
#define RF_Shot002_AngVelo(X)  (1000+(X)*1000)  //�p���x
// �G�~���A(EnemyEmilia) �̃����N��
#define RF_EnemyEmilia_ShotWay(X)  (4+(X)*4)  //���˒e(Way)��
// �G�~���A�f��(EnemyEmiliaFragment) �̃����N��
// �G�~���A�f�Ђ̒f��(EnemyEmiliaFragment2) �̃����N��
// �G�~���A�f�Ђ̒f�Ђ̒f��(EnemyEmiliaFragment3) �̃����N��
// �G�~���A�Q(FormationEmilia) �̃����N��
#define RF_FormationEmilia_LaunchInterval(X)  (10  + (20 - ((X)>1.0?1.0:(X))*20))  //�o���Ԋu
#define RF_FormationEmilia_MvVelo(X)  (8000+(X)*8000)  //�ړ����x
#define RF_FormationEmilia_DurationFrames(X)  (60*20)  //��������
// �G�[�x�ґ�(FormationEbe) �̃����N��
#define RF_FormationEbe_Num(X)  (12+(X)*8)  //����
#define RF_FormationEbe_LaunchInterval(X)  (5 + (20 - ((X)>1.0?1.0:(X))*20))  //�o���Ԋu
#define RF_FormationEbe_MvVelo(X)  (10000 + (X)*10000)  //�ړ����x
#define RF_FormationEbe_ShotWay(X)  (4+(X)*4)  //���˒e(Way)��
// �G�X�y���A(EnemyEsperia) �̃����N��
#define RF_EnemyEsperia_Density(X)  (90000 - (((X)>1.0?1.0:(X)) * 50000))  //���x
#define RF_EnemyEsperia_ShotWay(X)  (7 + (((X)>1.0?1.0:(X)) * 4))  //���˒e(Way)��
// �A�b�t�H�[(EnemyAppho) �̃����N��
#define RF_EnemyAppho_MvVelo(X)  (15000 + (X)*10000)  //�ړ����x
#define RF_EnemyAppho_ShotWay(X)  (2+(X)*4)  //���˒e(Way)��
#define RF_EnemyAppho_ShotMvVelo(X)  (1000+(X)*5000)  //���˒e���x
// �A�b�t�H�[�ґ�001(FormationAppho001) �̃����N��
#define RF_FormationAppho001_Num(X)  (10+(X)*5)  //����
#define RF_FormationAppho001_LaunchInterval(X)  (3 + (20 - ((X)>1.0?1.0:(X))*20))  //�o���Ԋu
// �A�e���e�B�I�y(EnemyAntiope) �̃����N��
#define RF_EnemyAntiope_MvVelo(X)  (15000 + (X)*10000)  //�ړ����x
#define RF_EnemyAntiope_ShotWay(X)  (2+(X)*4)  //���˒e(Way)��
#define RF_EnemyAntiope_ShotMvVelo(X)  (1000+(X)*5000)  //���˒e���x
// �A�e���e�B�I�y�ґ�001(FormationAntiope001) �̃����N��
#define RF_FormationAntiope001_Num(X)  (300+(X)*300)  //����
#define RF_FormationAntiope001_LaunchInterval(X)  (2 + (2 - ((X)>1.0?1.0:(X))*2))  //�o���Ԋu
// �f���w�C�h�ґ�(FormationDelheid) �̃����N��
#define RF_FormationDelheid_Num(X)  (30+(X)*10)  //����
#define RF_FormationDelheid_MvVelo(X)  (10000 + (X)*10000)  //�ړ����x
#define RF_FormationDelheid_ShotWay(X)  (7+(X)*5)  //���˒e(Way)��
// �ł��Ԃ��e����(SHOT_RV) �̃����N��
#define RF_SHOT_RV_ShotMvVelo(X)  (3000+((X)*5000))  //���˒e���x
#define RF_SHOT_RV_ShotMvAcce(X)  (100+((X)*400))  //���˒e�����x
// �m�[�}���ł��Ԃ��e001(SHOT_RV_NOMAL001) �̃����N��
#define RF_SHOT_RV_NOMAL001_Density(X)  (D_ANG(15)-((X)*D_ANG(5)))  //���x
#define RF_SHOT_RV_NOMAL001_ShotWay(X)  (3+(2*((X)*2)))  //���˒e(Way)��
#define RF_SHOT_RV_NOMAL001_ShotSetNum(X)  (1+((X)*3))  //���˒e(Way)�e�̃Z�b�g��
// �I���g�D�i(EnemyOrtuna) �̃����N��
#define RF_EnemyOrtuna_MvVelo(X)  (15000 + (X)*10000)  //�ړ����x
#define RF_EnemyOrtuna_ShotWay(X)  (2+(X)*4)  //���˒e(Way)��
#define RF_EnemyOrtuna_ShotMvVelo(X)  (1000+(X)*5000)  //���˒e���x
// �I���g�D�i�ґ�001(FormationOrtuna001) �̃����N��
#define RF_FormationOrtuna001_Num(X)  (10+(X)*5)  //����
#define RF_FormationOrtuna001_LaunchInterval(X)  (3 + (20 - ((X)>1.0?1.0:(X))*20))  //�o���Ԋu
// �O����(EnemyGlaja) �̃����N��
#define RF_EnemyGlaja_MvVelo(X)  (15000 + (X)*10000)  //�ړ����x
#define RF_EnemyGlaja_ShotWay(X)  (16+(X)*16)  //���˒e(Way)��
// �h�D�[�i(EnemyDuna) �̃����N��
#define RF_EnemyDuna_MvVelo(X)  (10000 + (X)*20000)  //�ړ����x
// gen02 end

//1/��2
#define NANAME2D_RATE 0.70710
//1/��3
#define NANAME3D_RATE 0.57735

#define FADE_FRAMES 180

#define VV_DEFAULT_CONFIG_FILE ".\\default_config.properties"
#define VV_CONFIG_FILE         ".\\config.properties"

#define Obj_RankUpStage     ((0x10000ULL) | Obj_SceneBit)    //0b 10000000 00000000 00000000 00000000 00000000 00000001 00000000 00000000

namespace VioletVreath {

//// forward declaration begin
class AliceShot;
class BunshinMagic;
class Camera;
class CameraUpVector;
class CameraViewPoint;
class CameraWorkerConnection;
class CameraWorkerManager;
class CommonScene;
class Config;
class CostDispBar;
class Cursor001;
class CursorConfig001;
class CursorConfig002;
class CursorConfig003;
class CursorConfig004;
class CursorConfig005;
class CursorConfirmMenu;
class CursorNameEntryMenu;
class CursorPauseMenu;
class CursorResolutionSelect;
class CursorTitleMenu;
class DamageDispBar;
class DanmakuAlice;
class DanmakuAlice001;
class DefaultCamWorker;
class DepositoryConnection;
class DepositoryManager;
class EffectBlink;
class EffectBlink001;
class EffectBlink002;
class EffectBlink003;
class EffectBunshinMagic001;
class EffectCondensation001;
class EffectExplosion001;
class EffectExplosion002;
class EffectExplosion003;
class EffectExplosion004;
class EffectLaserMagic;
class EffectLaserRefraction001;
class EffectLockon001;
class EffectLockon001_Main;
class EffectLockon001_Sub;
class EffectLockonMagic;
class EffectMagic001;
class EffectManager;
class EffectMyShipExplosion;
class EffectRatislaviaEye001;
class EffectShotMagic;
class EffectSmileMagic001;
class EffectSpeedMagic;
class EffectTorpedoMagic;
class EffectTurbo001;
class EffectTurbo002;
class EffectVreathMagic001;
class EffectWormhole;
class EffectWormhole001;
class EnemyAlisana;
class EnemyAllas;
class EnemyAntiope;
class EnemyAntiopeN;
class EnemyAntiopeP;
class EnemyAppho;
class EnemyDelheid;
class EnemyDrastea;
class EnemyDuna;
class EnemyEbe;
class EnemyEmilia;
class EnemyEmiliaBase;
class EnemyEmiliaFragment;
class EnemyEmiliaFragment2;
class EnemyEmiliaFragment3;
class EnemyEmus;
class EnemyEmusLaserChip001;
class EnemyErelman;
class EnemyErelmanController;
class EnemyErelmanController001;
class EnemyErelmanController002;
class EnemyErelmanController003;
class EnemyErelmanCore;
class EnemyErelmanCore001;
class EnemyErelmanCore002;
class EnemyErelmanCore003;
class EnemyEres;
class EnemyEresShot001;
class EnemyErmione;
class EnemyErmioneArm;
class EnemyErmioneArmBody;
class EnemyErmioneArmHead;
class EnemyErmioneArmWeak;
class EnemyEsperia;
class EnemyEsperiaLaserChip001;
class EnemyEtis;
class EnemyGeria;
class EnemyGlaja;
class EnemyGlajaLance001;
class EnemyHalia;
class EnemyHisbe;
class EnemyHisbe002;
class EnemyHisbeLaserChip001;
class EnemyHisbeLaserChip002;
class EnemyHisbeLaserChip003;
class EnemyIda;
class EnemyIdaBase;
class EnemyIdaBase001;
class EnemyIrce;
class EnemyOebius;
class EnemyOebiusController;
class EnemyOebiusController001;
class EnemyOebiusController002;
class EnemyOebiusCore;
class EnemyOmulus;
class EnemyOrtuna;
class EnemyOzartia;
class EnemyOzartiaLaserChip01;
class EnemyOzartiaPillar01;
class EnemyOzartiaShot01;
class EnemyRatislavia;
class EnemyRatislaviaEye;
class EnemyRatislaviaEyeStraightLaserChip001;
class EnemyRis;
class EnemyStraea;
class EnemyStraeaLaserChip001;
class EnemyStraeaLaserChip002;
class EnemyStraeaLaserChip003;
class EnemyStraeaLaserChip004;
class EnemyStraightLaserChip001;
class EnemyTalante;
class EnemyTamago01;
class EnemyThagoras;
class EnemyUnomia;
class EnemyUrydike;
class EnemyWateringLaserChip001;
class FormationAllas001;
class FormationAllas001a;
class FormationAllas001b;
class FormationAllas001c;
class FormationAllas001d;
class FormationAllas002;
class FormationAntiope001;
class FormationAppho001;
class FormationAppho001a;
class FormationAppho001b;
class FormationDelheid;
class FormationDelheid001;
class FormationDrastea001;
class FormationEbe;
class FormationEbe001;
class FormationEmilia;
class FormationErelman;
class FormationErelman001;
class FormationErelman002;
class FormationErelman003;
class FormationEres001;
class FormationEres002;
class FormationEtis001;
class FormationGeria;
class FormationGeria001;
class FormationGeria002;
class FormationHalia;
class FormationIda;
class FormationIda001;
class FormationOebius;
class FormationOebius001;
class FormationOebius002;
class FormationOrtuna001;
class FormationOrtuna001a;
class FormationOrtuna001b;
class FormationRis001;
class FormationRis002;
class FormationThagoras;
class FormationThagoras001;
class FormationThagoras002;
class FormationUnomia;
class FormationUnomia001;
class FormationUnomia001a;
class FormationUnomia001b;
class FormationUnomia002;
class FormationUnomia002a;
class FormationUnomia002b;
class FormationUrydike;
class FormationUrydike001;
class FormationUrydike002;
class GameBeginningScene;
class GameDemoScene;
class GameEndingScene;
class GameGlobal;
class GameMainScene;
class GameOverScene;
class GamePreTitleScene;
class GameScene;
class GameTitleScene;
class God;
class GroundMeshActor;
class Horizon001;
class HoshiBoshi;
class HoshiBoshi001;
class HoshiboshiEffect;
class HoshiBoshiRankUp;
class HoshiBoshiTitle;
class HoshiBoshiTransit;
class Item;
class LabelFix16Font01;
class LabelFont16x32;
class LabelFont32x64;
class LabelFont8x16;
class LabelGecchi16Font;
class LabelGecchi32Font;
class LabelGecchi8Font;
class LabelMenuItemFont01;
class LabelMenuTitleFont01;
class LabelRankFont;
class LabelRankingFont;
class LabelSceneSymbol;
class LabelScoreFont;
class LaserMagic;
class LockonMagic;
class Magic;
class MagicLvCursor;
class MagicLvCursor001;
class MagicLvCursor002;
class MagicLvCursor003;
class MagicMeter;
class MagicMeterCursor001;
class MagicMeterStatus;
class MagicPointItem;
class MagicPointItem001;
class MagicPointItem002;
class MagicPointItem003;
class MenuBoard;
class MenuBoardConfig;
class MenuBoardConfirm;
class MenuBoardKeyConfig;
class MenuBoardNameEntry;
class MenuBoardPause;
class MenuBoardResolutionSelect;
class MenuBoardScreenConfig;
class MenuBoardSoundConfig;
class MenuBoardTitle;
class MpBar;
class MyBunshin;
class MyBunshinBase;
class MyBunshinShot001;
class MyBunshinSnipeShot001;
class MyBunshinWateringLaserChip001;
class MyLockonController;
class MyMagicEnergy;
class MyMagicEnergyCore;
class MyShip;
class MyShipDivingCamWorker;
class MyShipScene;
class MyShot001;
class MySnipeShot001;
class MyStgUtil;
class MyStraightLaserChip001;
class MyTorpedo;
class MyTorpedoBlast;
class MyTorpedoController;
class MyTorpedoTail;
class MyVreath;
class MyWave001;
class NameEntryScene;
class PauseCamWorker;
class Planet001;
class Planet001Atmosphere;
class PreDrawScene;
class RankingTable;
class RankUp001;
class RankUp002;
class RankUp003;
class RankUp100;
class RankUpStage;
class RankUpStageController;
class ScoreItem;
class ScoreItem001;
class Shot001;
class Shot002;
class Shot003;
class Shot004;
class Shot004Blue;
class Shot004Yellow;
class ShotMagic;
class SmileMagic;
class Spacetime;
class SpeedMagic;
class SplineManufactureManagerEx;
class SplineSourceManagerEx;
class SpriteFont32x64;
class SpriteLabelBonus001;
class SpriteLabelGecchi32Font;
class SpriteLabelTest;
class Stage;
class Stage01;
class Stage01Part01;
class Stage01Part02;
class Stage01Part03;
class Stage01PartClimax;
class Stage01PartController;
class Stage01PartWall;
class Stage01PartWallSection001;
class Stage02;
class Stage02_01;
class Stage02_Climax;
class Stage02PartController;
class Stage03;
class Stage04;
class Stage05;
class StageController;
class StageDebug;
class StageDebugPart01;
class StageDebugPart02;
class StageDebugPart03;
class StageDebugPartClimax;
class StageDebugPartController;
class StageDebugPartWall;
class StageDebugPartWallSection001;
class StagePartController;
class StageWorld;
class TamagoActor;
class TamagoScene;
class TestCamWorker;
class TestChoki;
class TestChokiShot;
class TestDepository;
class TestEnemy;
class TestGu;
class TestGuShot;
class TestNomal;
class TestNomalShot;
class TestPa;
class TestPaShot;
class TitleBoard;
class TorpedoMagic;
class TractorMagic;
class TransitStage;
class VamSysCamWorker;
class VarietyRatislavia001;
class VarietyRatislavia002;
class VarietyRatislavia003;
class VarietyRatislavia004;
class ViewPointGuide;
class VreathBar;
class VreathItem;
class VreathItem001;
class VreathMagic;
class Wall01;
class World;
class WorldBound001;
class WorldBound002;
class WorldBoundNameEntry;
class WorldBoundRankUp;
class WorldBoundTitle;
class WorldBoundTransit;
class XpmConnection;
class XpmManager;
//// forward declaration end

}


#endif /*VIOLETVREATHHEADER_H_*/
