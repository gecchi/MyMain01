#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;

Stage01MainScene::Stage01MainScene(const char* prm_name) : DefaultScene(prm_name) {

    // 以下の gen01 start ～ end はExcelマクロにより自動生成されたコードです。
    // コード変更は「シーンCreater.xls」を開いて、そこから行うこと（整合性確保のため）。
    // gen01 start
    DWORD dw[] = {1,100,500,530,560,590,620,650,900,1000,1300,1500,1700,2000,2300,2500,2900,3000,3500,3530,3560,3590,3620,3650,3700,3900,4000,4200,4500,4530,4560,4590,4620,4650,5000,5300,5500,5600,6000,6300,6500,6700,6900,7000,7200,7500,7530,7560,7590,7620,7650,7700,7900,8000,8200,8500,8530,8560,8590,8600,8620,8650,9000,9300,9400,9500,9600,10000,10300,10500,10700,10900,11000,11200,11500,11530,11560,11590,11620,11650,11700,11900,12000,12200,12400,12500,12530,12560,12590,12600,12620,12650,13000,13300,13500,13600,14000,14300,14500,14700,14900,15000,15200,15400,15500,15530,15560,15590,15620,15650,15700,15900,16000,16200,16500,16530,16560,16590,16600,16620,16650,17000,17300,17500,18000,18400,18500,18700,18900,19000,19200,19500,19530,19560,19590,19620,19650,20000,20500,21000,21030,21060,21090,21120,21150,21180,21210,21240,21270,21300,21330,21360,21390,21420,21450,21480,21500,21510,21540,21570,21600,21630,21660,21690,21720,21750,21780,21810,21840,21870,21900,21930,21960,21990,22000,22020,22050,22080,22110,22140,22170,22200,22230,22260,22290,22320,22350,22380,22410,22440,22470,22500,22530,22560,22590,22620,22650,22680,22710,22740,22770,22800,22830,22860,22890,22920,22950,22980,23000,23010,23040,23070,23100,23130,23160,23190,23220,23250,23280,23310,23340,23370,23400,23430,23460,23490,23500,23520,23550,23580,23610,23640,23670,23700,23730,23760,23790,23820,23850,23880,23910,23940,23970,24000,24030,24060,24090,24120,24150,24180,24210,24240,24270,24300,24330,24360,24390,24420,24450,24480,24510,24540,24570,24600,24630,24660,24690,24720,24750,24780,24810,24840,24870,24900,24930,24960,24990,25020,25050,25080,25110,25140,25170,25200,25230,25260,25290,25320,25350,25380,25410,25440,25470,25500,25530,25560,25590,25620,25650,25680,25710,25740,25770,25800,25830,25860,25890,25920,25950,25980,26010,26040,26070,26100,26130,26160,26190,26220,26250,26280,26310,26340,26370,26400,26430,26460,26490,26520,26550,26580,26610,26640,26670,26700,26730,26760,26790,26820,26850,26880,26910,26940,26970,27000,27030,27060,27090,27120,27150,27180,27210,27240,27270,27300,27330,27360,27390,27420,27450,27480,27510,27540,27570,27600,27630,27660,27690,27720,27750,27780,27810,27840,27870,27900,27930,27960,27990,28020,28050,28080,28110,28140,28170,28200,28230,28260,28290,28320,28350,28380,28410,28440,28470,28500,28530,28560,28590,28620,28650,28680,28710,28740,28770,28800,28830,28860,28890,28920,28950,28980,29010,29040,29070,29100,29130,29160,29190,29220,29250,29280,29310,29340,29370,29400,29430,29460,29490,29520,29550,29580,29610,29640,29670,29700,29730,29760,29790,29820,29850,29880,29910,29940,29970,30000,30030,30060,30090,30120,30150,30180,30210,30240,30270,30300,30330,30360,30390,30420,30450,30480,30510,30540,30570,30600,30630,30660,30690,30720,30750,30780,30810,30840,30870,30900,30930,30960,30990,31020,31050,31080,31110,31140,31170,31200,31230,31260,31290,31320,31350,31380,31410,31440,31470,31500,31530,31560,31590,31620,31650,31680,31710,31740,31770,31800,31830,31860,31890,31920,31950,31980,32010,32040,32070,32100,32130,32160,32190,32220,32250,32280,32310,32340,32370,32400,32430,32460,32490,32520,32550,32580,32610,32640,32670,32700,32730,32760,32790,32820,32850,32880,32910,32940,32970,33000,33030,33060,33090,33120,33150,33180,33210,33240,33270,33300,33330,33360,33390,33420,33450,33480,33510,33540,33570,33600,33630,33660,33690,33720,33750,33780,33810,33840,33870,33900,33930,33960,33990,34020,34050,34080,34110,34140,34170,34200,34230,34260,34290,34320,34350,34380,34410,34440,34470,34500,34530,34560,34590,34620,34650,34680,34710,34740,34770,34800,34830,34860,34890,34920,34950,34980,35010,35040,35070,35100,35130,35160,35190,35220,35250,35280,35310,35340,35370,35400,35430,35460,35490,35520,35550,35580,35610,35640,35670,35700,35730,35760,35790,35820,35850,35880,35910,35940,35970,36000,36030,36060,36090,36120,36150,36180,36210,36240,36270,36300,36330,36360,36390,36420,36450,36480,36510,36540,36570,36600,36630,36660,36690,36720,36750,36780,36810,36840,36870,36900,36930,36960,36990,37020,37050,37080,37110,37140,37170,37200,37230,37260,37290,37320,37350,37380,37410,37440,37470,37500,37530,37560,37590,37620,37650,37680,37710,37740,37770,37800,37830,37860,37890,37920,37950,37980,38010,38040,38070,38100,38130,38160,38190,38220,38250,38280,38310,38340,38370,38400,38430,38460,38490,38520,38550,38580,38610,38640,38670,38700,38730,38760,38790,38820,38850,38880,38910,38940,38970,39000,39030,39060,39090,39120,39150,39180,39210,39240,39270,39300,39330,39360,39390,39420,39450,39480,39510,39540,39570,39600,39630,39660,39690,39720,39750,39780,39810,39840,39870,39900,39930,39960,39990,40020,40050,40080,40110,40140,40170,40200,40230,40260,40290,40320,40350,40380,40410,40440,40470,40500,40530,40560,40590,40620,40650,40680,40710,40740,40770,40800,40830,40860,40890,40920,40950,40980,41010,41040,41070,41100,41130,41160,41190,41220,41250,41280,41310,41340,41370,41400,41430,41460,41490,41520,41550,41580,41610,41640,41670,41700,41730,41760,41790,41820,41850,41880,41910,41940,41970,42000,42030,42060,42090,42120,42150,42180,42210,42240,42270,42300,42330,42360,42390,42420,42450,42480,42510,42540,42570,42600,42630,42660,42690,42720,42750,42780,42810,42840,42870,42900,42930,42960,42990,43020,43050,43080,43110,43140,43170,43200,43230,43260,43290,43320,43350,43380,43410,43440,43470,43500,43530,43560,43590,43620,43650,43680,43710,43740,43770,43800,43830,43860,43890,43920,43950,43980,44010,44040,44070,44100,44130,44160,44190,44220,44250,44280,44310,44340,44370,44400,44430,44460,44490,44520,44550,44580,44610,44640,44670,44700,44730,44760,44790,44820,44850,44880,44910,44940,44970,45000,45030,45060,45090,45120,45150,45180,45210,45240,45270,45300,45330,45360,45390,45420,45450,45480,45510,45540,45570,45600,45630,45660,45690,45720,45750,45780,45810,45840,45870,45900,45930,45960,45990,46020,46050,46080,46110,46140,46170,46200,46230,46260,46290,46320,46350,46380,46410,46440,46470,46500,46530,46560,46590,46620,46650,46680,46710,46740,46770,46800,46830,46860,46890,46920,46950,46980,47010,47040,47070,47100,47130,47160,47190,47220,47250,47280,47310,47340,47370,47400,47430,47460,47490,47520,47550,47580,47610,47640,47670,47700,47730,47760,47790,47820,47850,47880,47910,47940,47970,48000,48030,48060,48090,48120,48150,48180,48210,48240,48270,48300,48330,48360,48390,48420,48450,48480,48510,48540,48570,48600,48630,48660,48690,48720,48750,48780,48810,48840,48870,48900,48930,48960,48990,49020,49050,49080,49110,49140,49170,49200,49230,49260,49290,49320,49350,49380,49410,49440,49470,49500,49530,49560,49590,49620,49650,49680,49710,49740,49770,49800,49830,49860,49890,49920,49950,49980,50010,50040,50070,50100,50130,50160,50190,50220,50250,50280,50310,50340,50370,50400,50430,50460,50490,50520,50550,50580,50610,50640,50670,50700,50730,50760,50790,50820,50850,50880,50910,50940,50970,51000,51030,51060,51090,51120,51150,51180,51210,51240,51270,51300,51330,51360,51390,51420,51450,51480,51510,51540,51570,51600,51630,51660,51690,51720,51750,51780,51810,51840,51870,51900,51930,51960,51990,52020,52050,52080,52110,52140,52170,52200,52230,52260,52290,52320,52350,52380,52410,52440,52470,52500,52530,52560,52590,52620,52650,52680,52710,52740,52770,52800,52830,52860,52890,52920,52950,52980,53010,53040,53070,53100,53130,53160,53190,53220,53250,53280,53310,53340,53370,53400,53430,53460,53490,53520,53550,53580,53610,53640,53670,53700,53730,53760,53790,53820,53850,53880,53910,53940,53970,54000,54030,54060,54090,54120,54150,54180,54210,54240,54270,54300,54330,54360,54390,54420,54450,54480,54510,54540,54570,54600,54630,54660,54690,54720,54750,54780,54810,54840,54870,54900,54930,54960,54990,55020,55050,55080,55110,55140,55170,55200,55230,55260,55290,55320,55350,55380,55410,55440,55470,55500,55530,55560,55590,55620,55650,55680,55710,55740,55770,55800,55830,55860,55890,55920,55950,55980,56010,56040,56070,56100,56130,56160,56190,56220,56250,56280,56310,56340,56370,56400,56430,56460,56490,56520,56550,56580,56610,56640,56670,56700,56730,56760,56790,56820,56850,56880,56910,56940,56970,57000,57030,57060,57090,57120,57150,57180,57210,57240,57270,57300,57330,57360,57390,57420,57450,57480,57510,57540,57570,57600,57630,57660,57690,57720,57750,57780,57810,57840,57870,57900,57930,57960,57990,58020,58050,58080,58110,58140,58170,58200,58230,58260,58290,58320,58350,58380,58410,58440,58470,58500,58530,58560,58590,58620,58650,58680,58710,58740,58770,58800,58830,58860,58890,58920,58950,58980,59010,59040,59070,59100,59130,59160,59190,59220,59250,59280,59310,59340,59370,59400,59430,59460,59490,59520,59550,59580,59610,59640,59670,59700,59730,59760,59790,59820,59850,59880,59910,59940,59970,60000,60030,60060,60090,60120,60150,60180,60210,60240,60270,60300,60330,60360,60390,60420,60450,60480,60510,60540,60570,60600,60630,60660,60690,60720,60750,60780,60810,60840,60870,60900,60930,60960,60990,61020,61050,61080,61110,61140,61170,61200,61230,61260,61290,61320,61350,61380,61410,61440,61470,61500,61530,61560,61590,61620,61650,61680,61710,61740,61770,61800,61830,61860,61890,61920,61950,61980};
    _paFrame_NextEvent = new DWORD[1510];
    for (int i = 0; i < 1510; i++) {
        _paFrame_NextEvent[i] = dw[i];
    }
    orderActorToFactory(11027100, FormationPallas001a, "F001a_Pallas_1");
    orderActorToFactory(11037500, FormationPallas001b, "F001b_Pallas_2");
    orderActorToFactory(11047900, FormationPallas001c, "F001c_Pallas_3");
    orderActorToFactory(110571300, FormationPallas001d, "F001d_Pallas_4");
    orderActorToFactory(110671700, FormationPallas001a, "F001a_Pallas_5");
    orderActorToFactory(110771700, FormationPallas001d, "F001d_Pallas_6");
    orderActorToFactory(110872000, FormationPallas001b, "F001a_Pallas_7");
    orderActorToFactory(110972000, FormationPallas001c, "F001d_Pallas_8");
    orderActorToFactory(111163000, VarietyTorus001, "VarietyTorus001_9");
    orderActorToFactory(111871000, EnemyMetis, "Metis_10");
    orderActorToFactory(111871500, EnemyMetis, "Metis_11");
    orderActorToFactory(111872000, EnemyMetis, "Metis_12");
    orderActorToFactory(111872500, EnemyMetis, "Metis_13");
    orderActorToFactory(111873000, EnemyMetis, "Metis_14");
    orderActorToFactory(112071000, EnemyAstraea, "Astraea_15");
    orderActorToFactory(112272900, EnemyAstraea, "Astraea_16");
    orderActorToFactory(112971500, EnemyAstraea, "Astraea_17");
    // gen01 end
}

void Stage01MainScene::initialize() {

}

void Stage01MainScene::processBehavior() {
    // 以下の gen02 start ～ end はマクロにより自動生成されたコードです。
    // コード変更は「シーンCreater.xls」を開いて、そこから行うこと（整合性確保のため）。
    // gen02 start
    if (getActivePartFrame() == _paFrame_NextEvent[_iCnt_Event]) {
        switch (getActivePartFrame()) {
            case 1:
                break;
            case 100:
                {
                FormationPallas001a* pFormationActor = (FormationPallas001a*)obtainActorFromFactory(11027100);
                getLordActor()->addSubGroup(pFormationActor);
                }
                break;
            case 500:
                {
                FormationPallas001b* pFormationActor = (FormationPallas001b*)obtainActorFromFactory(11037500);
                getLordActor()->addSubGroup(pFormationActor);
                }
                orderActorToFactory(111873500, EnemyMetis, "Metis_18");
                orderActorWithDpToFactory(114073500, EnemyCeres, "Ceres_19", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
                break;
            case 530:
                orderActorWithDpToFactory(114173530, EnemyCeres, "Ceres_20", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
                break;
            case 560:
                orderActorWithDpToFactory(114273560, EnemyCeres, "Ceres_21", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
                break;
            case 590:
                orderActorWithDpToFactory(114373590, EnemyCeres, "Ceres_22", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
                break;
            case 620:
                orderActorWithDpToFactory(114473620, EnemyCeres, "Ceres_23", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
                break;
            case 650:
                orderActorWithDpToFactory(114573650, EnemyCeres, "Ceres_24", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
                break;
            case 900:
                {
                FormationPallas001c* pFormationActor = (FormationPallas001c*)obtainActorFromFactory(11047900);
                getLordActor()->addSubGroup(pFormationActor);
                }
                break;
            case 1000:
                getLordActor()->addSubGroup(obtainActorFromFactory(111871000));
                orderActorToFactory(111874000, EnemyMetis, "Metis_25");
                {
                EnemyAstraea* pActor = (EnemyAstraea*)obtainActorFromFactory(112071000);
                getLordActor()->addSubGroup(pActor);
                pActor->_X = 8000000;
                pActor->_Z = -200000;
                pActor->_Y = -300000;
                }
                orderActorToFactory(113774000, FormationIris001, "F001_Iris_26");
                break;
            case 1300:
                {
                FormationPallas001d* pFormationActor = (FormationPallas001d*)obtainActorFromFactory(110571300);
                getLordActor()->addSubGroup(pFormationActor);
                }
                break;
            case 1500:
                getLordActor()->addSubGroup(obtainActorFromFactory(111871500));
                orderActorToFactory(111874500, EnemyMetis, "Metis_27");
                {
                EnemyAstraea* pActor = (EnemyAstraea*)obtainActorFromFactory(112971500);
                getLordActor()->addSubGroup(pActor);
                pActor->_Z = 1800000;
                pActor->_Y = -1800000;
                }
                break;
            case 1700:
                {
                FormationPallas001a* pFormationActor = (FormationPallas001a*)obtainActorFromFactory(110671700);
                getLordActor()->addSubGroup(pFormationActor);
                }
                {
                FormationPallas001d* pFormationActor = (FormationPallas001d*)obtainActorFromFactory(110771700);
                getLordActor()->addSubGroup(pFormationActor);
                }
                break;
            case 2000:
                {
                FormationPallas001b* pFormationActor = (FormationPallas001b*)obtainActorFromFactory(110872000);
                getLordActor()->addSubGroup(pFormationActor);
                }
                {
                FormationPallas001c* pFormationActor = (FormationPallas001c*)obtainActorFromFactory(110972000);
                getLordActor()->addSubGroup(pFormationActor);
                }
                getLordActor()->addSubGroup(obtainActorFromFactory(111872000));
                orderActorToFactory(111875000, EnemyMetis, "Metis_28");
                orderActorToFactory(114775000, FormationJuno001, "F002_Juno_29");
                break;
            case 2300:
                orderActorToFactory(113175300, EnemyAstraea, "Astraea_30");
                break;
            case 2500:
                getLordActor()->addSubGroup(obtainActorFromFactory(111872500));
                orderActorToFactory(111875500, EnemyMetis, "Metis_31");
                orderActorToFactory(112975500, EnemyAstraea, "Astraea_32");
                break;
            case 2900:
                {
                EnemyAstraea* pActor = (EnemyAstraea*)obtainActorFromFactory(112272900);
                getLordActor()->addSubGroup(pActor);
                pActor->_Z = -1800000;
                pActor->_Y = -100000;
                }
                break;
            case 3000:
                getLordActor()->addSubGroup(obtainActorFromFactory(111163000));
                getLordActor()->addSubGroup(obtainActorFromFactory(111873000));
                orderActorToFactory(111876000, EnemyMetis, "Metis_33");
                orderActorToFactory(113876000, FormationIris002, "F002_Iris_34");
                break;
            case 3500:
                getLordActor()->addSubGroup(obtainActorFromFactory(111873500));
                orderActorToFactory(111876500, EnemyMetis, "Metis_35");
                {
                EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(114073500);
                getLordActor()->addSubGroup(pActor);
                pActor->_Z = -1500000;
                pActor->_Y_turn = -250000;
                pActor->_veloBegin = 8000;
                }
                break;
            case 3530:
                {
                EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(114173530);
                getLordActor()->addSubGroup(pActor);
                pActor->_Z = -1500000;
                pActor->_Y_turn = -250000;
                pActor->_veloBegin = 8000;
                }
                break;
            case 3560:
                {
                EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(114273560);
                getLordActor()->addSubGroup(pActor);
                pActor->_Z = -1500000;
                pActor->_Y_turn = -250000;
                pActor->_veloBegin = 8000;
                }
                break;
            case 3590:
                {
                EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(114373590);
                getLordActor()->addSubGroup(pActor);
                pActor->_Z = -1500000;
                pActor->_Y_turn = -250000;
                pActor->_veloBegin = 8000;
                }
                break;
            case 3620:
                {
                EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(114473620);
                getLordActor()->addSubGroup(pActor);
                pActor->_Z = -1500000;
                pActor->_Y_turn = -250000;
                pActor->_veloBegin = 8000;
                }
                break;
            case 3650:
                {
                EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(114573650);
                getLordActor()->addSubGroup(pActor);
                pActor->_Z = -1500000;
                pActor->_Y_turn = -250000;
                pActor->_veloBegin = 8000;
                }
                break;
            case 3700:
                orderActorToFactory(112476700, EnemyAstraea, "Astraea_36");
                break;
            case 3900:
                orderActorToFactory(112276900, EnemyAstraea, "Astraea_37");
                break;
            case 4000:
                getLordActor()->addSubGroup(obtainActorFromFactory(111874000));
                orderActorToFactory(111877000, EnemyMetis, "Metis_38");
                {
                FormationIris001* pFormationActor = (FormationIris001*)obtainActorFromFactory(113774000);
                getLordActor()->addSubGroup(pFormationActor);
                }
                break;
            case 4200:
                orderActorToFactory(113277200, EnemyAstraea, "Astraea_39");
                break;
            case 4500:
                getLordActor()->addSubGroup(obtainActorFromFactory(111874500));
                orderActorToFactory(111877500, EnemyMetis, "Metis_40");
                orderActorWithDpToFactory(114077500, EnemyCeres, "Ceres_41", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
                break;
            case 4530:
                orderActorWithDpToFactory(114177530, EnemyCeres, "Ceres_42", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
                break;
            case 4560:
                orderActorWithDpToFactory(114277560, EnemyCeres, "Ceres_43", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
                break;
            case 4590:
                orderActorWithDpToFactory(114377590, EnemyCeres, "Ceres_44", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
                break;
            case 4620:
                orderActorWithDpToFactory(114477620, EnemyCeres, "Ceres_45", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
                break;
            case 4650:
                orderActorWithDpToFactory(114577650, EnemyCeres, "Ceres_46", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
                break;
            case 5000:
                getLordActor()->addSubGroup(obtainActorFromFactory(111875000));
                orderActorToFactory(111878000, EnemyMetis, "Metis_47");
                orderActorToFactory(113778000, FormationIris001, "F001_Iris_48");
                {
                FormationJuno001* pFormationActor = (FormationJuno001*)obtainActorFromFactory(114775000);
                getLordActor()->addSubGroup(pFormationActor);
                }
                break;
            case 5300:
                {
                EnemyAstraea* pActor = (EnemyAstraea*)obtainActorFromFactory(113175300);
                getLordActor()->addSubGroup(pActor);
                pActor->_Z = 1200002;
                pActor->_Y = -1200002;
                }
                break;
            case 5500:
                getLordActor()->addSubGroup(obtainActorFromFactory(111875500));
                orderActorToFactory(111878500, EnemyMetis, "Metis_49");
                {
                EnemyAstraea* pActor = (EnemyAstraea*)obtainActorFromFactory(112975500);
                getLordActor()->addSubGroup(pActor);
                pActor->_Z = 1800000;
                pActor->_Y = -1800000;
                }
                break;
            case 5600:
                orderActorToFactory(112578600, EnemyAstraea, "Astraea_50");
                break;
            case 6000:
                getLordActor()->addSubGroup(obtainActorFromFactory(111876000));
                orderActorToFactory(111879000, EnemyMetis, "Metis_51");
                {
                FormationIris002* pFormationActor = (FormationIris002*)obtainActorFromFactory(113876000);
                getLordActor()->addSubGroup(pFormationActor);
                }
                break;
            case 6300:
                orderActorToFactory(113179300, EnemyAstraea, "Astraea_52");
                break;
            case 6500:
                getLordActor()->addSubGroup(obtainActorFromFactory(111876500));
                orderActorToFactory(111879500, EnemyMetis, "Metis_53");
                orderActorToFactory(112979500, EnemyAstraea, "Astraea_54");
                break;
            case 6700:
                {
                EnemyAstraea* pActor = (EnemyAstraea*)obtainActorFromFactory(112476700);
                getLordActor()->addSubGroup(pActor);
                pActor->_Z = -1200002;
                pActor->_Y = -340002;
                }
                break;
            case 6900:
                {
                EnemyAstraea* pActor = (EnemyAstraea*)obtainActorFromFactory(112276900);
                getLordActor()->addSubGroup(pActor);
                pActor->_Z = -1800000;
                pActor->_Y = -100000;
                }
                break;
            case 7000:
                orderActorToFactory(1112610000, VarietyTorus002, "VarietyTorus002_55");
                orderActorToFactory(1113610000, VarietyTorus003, "VarietyTorus003_56");
                getLordActor()->addSubGroup(obtainActorFromFactory(111877000));
                orderActorToFactory(1118710000, EnemyMetis, "Metis_57");
                orderActorToFactory(1138710000, FormationIris002, "F002_Iris_58");
                break;
            case 7200:
                {
                EnemyAstraea* pActor = (EnemyAstraea*)obtainActorFromFactory(113277200);
                getLordActor()->addSubGroup(pActor);
                pActor->_Z = 900003;
                pActor->_Y = -900003;
                }
                break;
            case 7500:
                getLordActor()->addSubGroup(obtainActorFromFactory(111877500));
                orderActorToFactory(1118710500, EnemyMetis, "Metis_59");
                {
                EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(114077500);
                getLordActor()->addSubGroup(pActor);
                pActor->_Z = -1500000;
                pActor->_Y_turn = -250000;
                pActor->_veloBegin = 8000;
                }
                break;
            case 7530:
                {
                EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(114177530);
                getLordActor()->addSubGroup(pActor);
                pActor->_Z = -1500000;
                pActor->_Y_turn = -250000;
                pActor->_veloBegin = 8000;
                }
                break;
            case 7560:
                {
                EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(114277560);
                getLordActor()->addSubGroup(pActor);
                pActor->_Z = -1500000;
                pActor->_Y_turn = -250000;
                pActor->_veloBegin = 8000;
                }
                break;
            case 7590:
                {
                EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(114377590);
                getLordActor()->addSubGroup(pActor);
                pActor->_Z = -1500000;
                pActor->_Y_turn = -250000;
                pActor->_veloBegin = 8000;
                }
                break;
            case 7620:
                {
                EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(114477620);
                getLordActor()->addSubGroup(pActor);
                pActor->_Z = -1500000;
                pActor->_Y_turn = -250000;
                pActor->_veloBegin = 8000;
                }
                break;
            case 7650:
                {
                EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(114577650);
                getLordActor()->addSubGroup(pActor);
                pActor->_Z = -1500000;
                pActor->_Y_turn = -250000;
                pActor->_veloBegin = 8000;
                }
                break;
            case 7700:
                orderActorToFactory(1124710700, EnemyAstraea, "Astraea_60");
                break;
            case 7900:
                orderActorToFactory(1122710900, EnemyAstraea, "Astraea_61");
                break;
            case 8000:
                getLordActor()->addSubGroup(obtainActorFromFactory(111878000));
                orderActorToFactory(1118711000, EnemyMetis, "Metis_62");
                orderActorToFactory(1134711000, EnemyAstraea, "Astraea_63");
                {
                FormationIris001* pFormationActor = (FormationIris001*)obtainActorFromFactory(113778000);
                getLordActor()->addSubGroup(pFormationActor);
                }
                break;
            case 8200:
                orderActorToFactory(1132711200, EnemyAstraea, "Astraea_64");
                break;
            case 8500:
                getLordActor()->addSubGroup(obtainActorFromFactory(111878500));
                orderActorToFactory(1118711500, EnemyMetis, "Metis_65");
                orderActorWithDpToFactory(1140711500, EnemyCeres, "Ceres_66", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
                break;
            case 8530:
                orderActorWithDpToFactory(1141711530, EnemyCeres, "Ceres_67", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
                break;
            case 8560:
                orderActorWithDpToFactory(1142711560, EnemyCeres, "Ceres_68", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
                break;
            case 8590:
                orderActorWithDpToFactory(1143711590, EnemyCeres, "Ceres_69", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
                break;
            case 8600:
                {
                EnemyAstraea* pActor = (EnemyAstraea*)obtainActorFromFactory(112578600);
                getLordActor()->addSubGroup(pActor);
                pActor->_Z = -900003;
                pActor->_Y = -460003;
                }
                break;
            case 8620:
                orderActorWithDpToFactory(1144711620, EnemyCeres, "Ceres_70", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
                break;
            case 8650:
                orderActorWithDpToFactory(1145711650, EnemyCeres, "Ceres_71", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
                break;
            case 9000:
                getLordActor()->addSubGroup(obtainActorFromFactory(111879000));
                orderActorToFactory(1118712000, EnemyMetis, "Metis_72");
                orderActorToFactory(1137712000, FormationIris001, "F001_Iris_73");
                break;
            case 9300:
                {
                EnemyAstraea* pActor = (EnemyAstraea*)obtainActorFromFactory(113179300);
                getLordActor()->addSubGroup(pActor);
                pActor->_Z = 1200002;
                pActor->_Y = -1200002;
                }
                break;
            case 9400:
                orderActorToFactory(1127712400, EnemyAstraea, "Astraea_74");
                break;
            case 9500:
                getLordActor()->addSubGroup(obtainActorFromFactory(111879500));
                orderActorToFactory(1118712500, EnemyMetis, "Metis_75");
                {
                EnemyAstraea* pActor = (EnemyAstraea*)obtainActorFromFactory(112979500);
                getLordActor()->addSubGroup(pActor);
                pActor->_Z = 1800000;
                pActor->_Y = -1800000;
                }
                break;
            case 9600:
                orderActorToFactory(1125712600, EnemyAstraea, "Astraea_76");
                break;
            case 10000:
                getLordActor()->addSubGroup(obtainActorFromFactory(1112610000));
                getLordActor()->addSubGroup(obtainActorFromFactory(1113610000));
                getLordActor()->addSubGroup(obtainActorFromFactory(1118710000));
                orderActorToFactory(1118713000, EnemyMetis, "Metis_77");
                {
                FormationIris002* pFormationActor = (FormationIris002*)obtainActorFromFactory(1138710000);
                getLordActor()->addSubGroup(pFormationActor);
                }
                orderActorToFactory(1147713000, FormationJuno001, "F002_Juno_78");
                break;
            case 10300:
                orderActorToFactory(1131713300, EnemyAstraea, "Astraea_79");
                break;
            case 10500:
                getLordActor()->addSubGroup(obtainActorFromFactory(1118710500));
                orderActorToFactory(1118713500, EnemyMetis, "Metis_80");
                orderActorToFactory(1129713500, EnemyAstraea, "Astraea_81");
                break;
            case 10700:
                {
                EnemyAstraea* pActor = (EnemyAstraea*)obtainActorFromFactory(1124710700);
                getLordActor()->addSubGroup(pActor);
                pActor->_Z = -1200002;
                pActor->_Y = -340002;
                }
                break;
            case 10900:
                {
                EnemyAstraea* pActor = (EnemyAstraea*)obtainActorFromFactory(1122710900);
                getLordActor()->addSubGroup(pActor);
                pActor->_Z = -1800000;
                pActor->_Y = -100000;
                }
                break;
            case 11000:
                getLordActor()->addSubGroup(obtainActorFromFactory(1118711000));
                orderActorToFactory(1118714000, EnemyMetis, "Metis_82");
                {
                EnemyAstraea* pActor = (EnemyAstraea*)obtainActorFromFactory(1134711000);
                getLordActor()->addSubGroup(pActor);
                pActor->_Z = 300005;
                pActor->_Y = -300005;
                }
                orderActorToFactory(1138714000, FormationIris002, "F002_Iris_83");
                break;
            case 11200:
                {
                EnemyAstraea* pActor = (EnemyAstraea*)obtainActorFromFactory(1132711200);
                getLordActor()->addSubGroup(pActor);
                pActor->_Z = 900003;
                pActor->_Y = -900003;
                }
                break;
            case 11500:
                getLordActor()->addSubGroup(obtainActorFromFactory(1118711500));
                orderActorToFactory(1118714500, EnemyMetis, "Metis_84");
                {
                EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(1140711500);
                getLordActor()->addSubGroup(pActor);
                pActor->_Z = -1500000;
                pActor->_Y_turn = -250000;
                pActor->_veloBegin = 8000;
                }
                break;
            case 11530:
                {
                EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(1141711530);
                getLordActor()->addSubGroup(pActor);
                pActor->_Z = -1500000;
                pActor->_Y_turn = -250000;
                pActor->_veloBegin = 8000;
                }
                break;
            case 11560:
                {
                EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(1142711560);
                getLordActor()->addSubGroup(pActor);
                pActor->_Z = -1500000;
                pActor->_Y_turn = -250000;
                pActor->_veloBegin = 8000;
                }
                break;
            case 11590:
                {
                EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(1143711590);
                getLordActor()->addSubGroup(pActor);
                pActor->_Z = -1500000;
                pActor->_Y_turn = -250000;
                pActor->_veloBegin = 8000;
                }
                break;
            case 11620:
                {
                EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(1144711620);
                getLordActor()->addSubGroup(pActor);
                pActor->_Z = -1500000;
                pActor->_Y_turn = -250000;
                pActor->_veloBegin = 8000;
                }
                break;
            case 11650:
                {
                EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(1145711650);
                getLordActor()->addSubGroup(pActor);
                pActor->_Z = -1500000;
                pActor->_Y_turn = -250000;
                pActor->_veloBegin = 8000;
                }
                break;
            case 11700:
                orderActorToFactory(1124714700, EnemyAstraea, "Astraea_85");
                break;
            case 11900:
                orderActorToFactory(1122714900, EnemyAstraea, "Astraea_86");
                break;
            case 12000:
                getLordActor()->addSubGroup(obtainActorFromFactory(1118712000));
                orderActorToFactory(1118715000, EnemyMetis, "Metis_87");
                orderActorToFactory(1134715000, EnemyAstraea, "Astraea_88");
                {
                FormationIris001* pFormationActor = (FormationIris001*)obtainActorFromFactory(1137712000);
                getLordActor()->addSubGroup(pFormationActor);
                }
                break;
            case 12200:
                orderActorToFactory(1132715200, EnemyAstraea, "Astraea_89");
                break;
            case 12400:
                {
                EnemyAstraea* pActor = (EnemyAstraea*)obtainActorFromFactory(1127712400);
                getLordActor()->addSubGroup(pActor);
                pActor->_Z = -300005;
                pActor->_Y = -700005;
                }
                orderActorToFactory(1127715400, EnemyAstraea, "Astraea_90");
                break;
            case 12500:
                getLordActor()->addSubGroup(obtainActorFromFactory(1118712500));
                orderActorToFactory(1118715500, EnemyMetis, "Metis_91");
                orderActorWithDpToFactory(1140715500, EnemyCeres, "Ceres_92", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
                break;
            case 12530:
                orderActorWithDpToFactory(1141715530, EnemyCeres, "Ceres_93", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
                break;
            case 12560:
                orderActorWithDpToFactory(1142715560, EnemyCeres, "Ceres_94", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
                break;
            case 12590:
                orderActorWithDpToFactory(1143715590, EnemyCeres, "Ceres_95", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
                break;
            case 12600:
                {
                EnemyAstraea* pActor = (EnemyAstraea*)obtainActorFromFactory(1125712600);
                getLordActor()->addSubGroup(pActor);
                pActor->_Z = -900003;
                pActor->_Y = -460003;
                }
                break;
            case 12620:
                orderActorWithDpToFactory(1144715620, EnemyCeres, "Ceres_96", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
                break;
            case 12650:
                orderActorWithDpToFactory(1145715650, EnemyCeres, "Ceres_97", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
                break;
            case 13000:
                getLordActor()->addSubGroup(obtainActorFromFactory(1118713000));
                orderActorToFactory(1118716000, EnemyMetis, "Metis_98");
                orderActorToFactory(1137716000, FormationIris001, "F001_Iris_99");
                {
                FormationJuno001* pFormationActor = (FormationJuno001*)obtainActorFromFactory(1147713000);
                getLordActor()->addSubGroup(pFormationActor);
                }
                break;
            case 13300:
                {
                EnemyAstraea* pActor = (EnemyAstraea*)obtainActorFromFactory(1131713300);
                getLordActor()->addSubGroup(pActor);
                pActor->_Z = 1200002;
                pActor->_Y = -1200002;
                }
                break;
            case 13500:
                getLordActor()->addSubGroup(obtainActorFromFactory(1118713500));
                orderActorToFactory(1118716500, EnemyMetis, "Metis_100");
                {
                EnemyAstraea* pActor = (EnemyAstraea*)obtainActorFromFactory(1129713500);
                getLordActor()->addSubGroup(pActor);
                pActor->_Z = 1800000;
                pActor->_Y = -1800000;
                }
                break;
            case 13600:
                orderActorToFactory(1125716600, EnemyAstraea, "Astraea_101");
                break;
            case 14000:
                getLordActor()->addSubGroup(obtainActorFromFactory(1118714000));
                orderActorToFactory(1118717000, EnemyMetis, "Metis_102");
                {
                FormationIris002* pFormationActor = (FormationIris002*)obtainActorFromFactory(1138714000);
                getLordActor()->addSubGroup(pFormationActor);
                }
                break;
            case 14300:
                orderActorToFactory(1131717300, EnemyAstraea, "Astraea_103");
                break;
            case 14500:
                getLordActor()->addSubGroup(obtainActorFromFactory(1118714500));
                orderActorToFactory(1118717500, EnemyMetis, "Metis_104");
                orderActorToFactory(1129717500, EnemyAstraea, "Astraea_105");
                break;
            case 14700:
                {
                EnemyAstraea* pActor = (EnemyAstraea*)obtainActorFromFactory(1124714700);
                getLordActor()->addSubGroup(pActor);
                pActor->_Z = -1200002;
                pActor->_Y = -340002;
                }
                break;
            case 14900:
                {
                EnemyAstraea* pActor = (EnemyAstraea*)obtainActorFromFactory(1122714900);
                getLordActor()->addSubGroup(pActor);
                pActor->_Z = -1800000;
                pActor->_Y = -100000;
                }
                break;
            case 15000:
                getLordActor()->addSubGroup(obtainActorFromFactory(1118715000));
                orderActorToFactory(1118718000, EnemyMetis, "Metis_106");
                {
                EnemyAstraea* pActor = (EnemyAstraea*)obtainActorFromFactory(1134715000);
                getLordActor()->addSubGroup(pActor);
                pActor->_Z = 300005;
                pActor->_Y = -300005;
                }
                orderActorToFactory(1138718000, FormationIris002, "F002_Iris_107");
                break;
            case 15200:
                {
                EnemyAstraea* pActor = (EnemyAstraea*)obtainActorFromFactory(1132715200);
                getLordActor()->addSubGroup(pActor);
                pActor->_Z = 900003;
                pActor->_Y = -900003;
                }
                break;
            case 15400:
                {
                EnemyAstraea* pActor = (EnemyAstraea*)obtainActorFromFactory(1127715400);
                getLordActor()->addSubGroup(pActor);
                pActor->_Z = -300005;
                pActor->_Y = -700005;
                }
                orderActorToFactory(1127718400, EnemyAstraea, "Astraea_108");
                break;
            case 15500:
                getLordActor()->addSubGroup(obtainActorFromFactory(1118715500));
                orderActorToFactory(1118718500, EnemyMetis, "Metis_109");
                {
                EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(1140715500);
                getLordActor()->addSubGroup(pActor);
                pActor->_Z = -1500000;
                pActor->_Y_turn = -250000;
                pActor->_veloBegin = 8000;
                }
                break;
            case 15530:
                {
                EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(1141715530);
                getLordActor()->addSubGroup(pActor);
                pActor->_Z = -1500000;
                pActor->_Y_turn = -250000;
                pActor->_veloBegin = 8000;
                }
                break;
            case 15560:
                {
                EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(1142715560);
                getLordActor()->addSubGroup(pActor);
                pActor->_Z = -1500000;
                pActor->_Y_turn = -250000;
                pActor->_veloBegin = 8000;
                }
                break;
            case 15590:
                {
                EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(1143715590);
                getLordActor()->addSubGroup(pActor);
                pActor->_Z = -1500000;
                pActor->_Y_turn = -250000;
                pActor->_veloBegin = 8000;
                }
                break;
            case 15620:
                {
                EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(1144715620);
                getLordActor()->addSubGroup(pActor);
                pActor->_Z = -1500000;
                pActor->_Y_turn = -250000;
                pActor->_veloBegin = 8000;
                }
                break;
            case 15650:
                {
                EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(1145715650);
                getLordActor()->addSubGroup(pActor);
                pActor->_Z = -1500000;
                pActor->_Y_turn = -250000;
                pActor->_veloBegin = 8000;
                }
                break;
            case 15700:
                orderActorToFactory(1124718700, EnemyAstraea, "Astraea_110");
                break;
            case 15900:
                orderActorToFactory(1122718900, EnemyAstraea, "Astraea_111");
                break;
            case 16000:
                getLordActor()->addSubGroup(obtainActorFromFactory(1118716000));
                orderActorToFactory(1118719000, EnemyMetis, "Metis_112");
                orderActorToFactory(1134719000, EnemyAstraea, "Astraea_113");
                {
                FormationIris001* pFormationActor = (FormationIris001*)obtainActorFromFactory(1137716000);
                getLordActor()->addSubGroup(pFormationActor);
                }
                break;
            case 16200:
                orderActorToFactory(1132719200, EnemyAstraea, "Astraea_114");
                break;
            case 16500:
                getLordActor()->addSubGroup(obtainActorFromFactory(1118716500));
                orderActorToFactory(1118719500, EnemyMetis, "Metis_115");
                orderActorWithDpToFactory(1140719500, EnemyCeres, "Ceres_116", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
                break;
            case 16530:
                orderActorWithDpToFactory(1141719530, EnemyCeres, "Ceres_117", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
                break;
            case 16560:
                orderActorWithDpToFactory(1142719560, EnemyCeres, "Ceres_118", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
                break;
            case 16590:
                orderActorWithDpToFactory(1143719590, EnemyCeres, "Ceres_119", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
                break;
            case 16600:
                {
                EnemyAstraea* pActor = (EnemyAstraea*)obtainActorFromFactory(1125716600);
                getLordActor()->addSubGroup(pActor);
                pActor->_Z = -900003;
                pActor->_Y = -460003;
                }
                break;
            case 16620:
                orderActorWithDpToFactory(1144719620, EnemyCeres, "Ceres_120", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
                break;
            case 16650:
                orderActorWithDpToFactory(1145719650, EnemyCeres, "Ceres_121", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
                break;
            case 17000:
                orderActorToFactory(1115620000, VarietyTorus004, "VarietyTorus004_122");
                getLordActor()->addSubGroup(obtainActorFromFactory(1118717000));
                orderActorToFactory(1118720000, EnemyMetis, "Metis_123");
                orderActorToFactory(1137720000, FormationIris001, "F001_Iris_124");
                break;
            case 17300:
                {
                EnemyAstraea* pActor = (EnemyAstraea*)obtainActorFromFactory(1131717300);
                getLordActor()->addSubGroup(pActor);
                pActor->_Z = 1200002;
                pActor->_Y = -1200002;
                }
                break;
            case 17500:
                getLordActor()->addSubGroup(obtainActorFromFactory(1118717500));
                orderActorToFactory(1118720500, EnemyMetis, "Metis_125");
                {
                EnemyAstraea* pActor = (EnemyAstraea*)obtainActorFromFactory(1129717500);
                getLordActor()->addSubGroup(pActor);
                pActor->_Z = 1800000;
                pActor->_Y = -1800000;
                }
                break;
            case 18000:
                getLordActor()->addSubGroup(obtainActorFromFactory(1118718000));
                orderActorToFactory(1118721000, EnemyMetis, "Metis_126");
                {
                FormationIris002* pFormationActor = (FormationIris002*)obtainActorFromFactory(1138718000);
                getLordActor()->addSubGroup(pFormationActor);
                }
                break;
            case 18400:
                {
                EnemyAstraea* pActor = (EnemyAstraea*)obtainActorFromFactory(1127718400);
                getLordActor()->addSubGroup(pActor);
                pActor->_Z = -300005;
                pActor->_Y = -700005;
                }
                break;
            case 18500:
                getLordActor()->addSubGroup(obtainActorFromFactory(1118718500));
                orderActorToFactory(1118721500, EnemyMetis, "Metis_127");
                break;
            case 18700:
                {
                EnemyAstraea* pActor = (EnemyAstraea*)obtainActorFromFactory(1124718700);
                getLordActor()->addSubGroup(pActor);
                pActor->_Z = -1200002;
                pActor->_Y = -340002;
                }
                break;
            case 18900:
                {
                EnemyAstraea* pActor = (EnemyAstraea*)obtainActorFromFactory(1122718900);
                getLordActor()->addSubGroup(pActor);
                pActor->_Z = -1800000;
                pActor->_Y = -100000;
                }
                break;
            case 19000:
                getLordActor()->addSubGroup(obtainActorFromFactory(1118719000));
                orderActorToFactory(1118722000, EnemyMetis, "Metis_128");
                {
                EnemyAstraea* pActor = (EnemyAstraea*)obtainActorFromFactory(1134719000);
                getLordActor()->addSubGroup(pActor);
                pActor->_Z = 300005;
                pActor->_Y = -300005;
                }
                break;
            case 19200:
                {
                EnemyAstraea* pActor = (EnemyAstraea*)obtainActorFromFactory(1132719200);
                getLordActor()->addSubGroup(pActor);
                pActor->_Z = 900003;
                pActor->_Y = -900003;
                }
                break;
            case 19500:
                getLordActor()->addSubGroup(obtainActorFromFactory(1118719500));
                orderActorToFactory(1118722500, EnemyMetis, "Metis_129");
                {
                EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(1140719500);
                getLordActor()->addSubGroup(pActor);
                pActor->_Z = -1500000;
                pActor->_Y_turn = -250000;
                pActor->_veloBegin = 8000;
                }
                break;
            case 19530:
                {
                EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(1141719530);
                getLordActor()->addSubGroup(pActor);
                pActor->_Z = -1500000;
                pActor->_Y_turn = -250000;
                pActor->_veloBegin = 8000;
                }
                break;
            case 19560:
                {
                EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(1142719560);
                getLordActor()->addSubGroup(pActor);
                pActor->_Z = -1500000;
                pActor->_Y_turn = -250000;
                pActor->_veloBegin = 8000;
                }
                break;
            case 19590:
                {
                EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(1143719590);
                getLordActor()->addSubGroup(pActor);
                pActor->_Z = -1500000;
                pActor->_Y_turn = -250000;
                pActor->_veloBegin = 8000;
                }
                break;
            case 19620:
                {
                EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(1144719620);
                getLordActor()->addSubGroup(pActor);
                pActor->_Z = -1500000;
                pActor->_Y_turn = -250000;
                pActor->_veloBegin = 8000;
                }
                break;
            case 19650:
                {
                EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(1145719650);
                getLordActor()->addSubGroup(pActor);
                pActor->_Z = -1500000;
                pActor->_Y_turn = -250000;
                pActor->_veloBegin = 8000;
                }
                break;
            case 20000:
                getLordActor()->addSubGroup(obtainActorFromFactory(1115620000));
                getLordActor()->addSubGroup(obtainActorFromFactory(1118720000));
                orderActorToFactory(1118723000, EnemyMetis, "Metis_130");
                {
                FormationIris001* pFormationActor = (FormationIris001*)obtainActorFromFactory(1137720000);
                getLordActor()->addSubGroup(pFormationActor);
                }
                break;
            case 20500:
                getLordActor()->addSubGroup(obtainActorFromFactory(1118720500));
                orderActorToFactory(1118723500, EnemyMetis, "Metis_131");
                break;
            case 21000:
                getLordActor()->addSubGroup(obtainActorFromFactory(1118721000));
                orderActorToFactory(1118724000, EnemyMetis, "Metis_132");
                orderActorToFactory(1119724000, EnemyMetis, "Metis_133");
                break;
            case 21030:
                orderActorToFactory(1119724030, EnemyMetis, "Metis_134");
                break;
            case 21060:
                orderActorToFactory(1119724060, EnemyMetis, "Metis_135");
                break;
            case 21090:
                orderActorToFactory(1119724090, EnemyMetis, "Metis_136");
                break;
            case 21120:
                orderActorToFactory(1119724120, EnemyMetis, "Metis_137");
                break;
            case 21150:
                orderActorToFactory(1119724150, EnemyMetis, "Metis_138");
                break;
            case 21180:
                orderActorToFactory(1119724180, EnemyMetis, "Metis_139");
                break;
            case 21210:
                orderActorToFactory(1119724210, EnemyMetis, "Metis_140");
                break;
            case 21240:
                orderActorToFactory(1119724240, EnemyMetis, "Metis_141");
                break;
            case 21270:
                orderActorToFactory(1119724270, EnemyMetis, "Metis_142");
                break;
            case 21300:
                orderActorToFactory(1119724300, EnemyMetis, "Metis_143");
                break;
            case 21330:
                orderActorToFactory(1119724330, EnemyMetis, "Metis_144");
                break;
            case 21360:
                orderActorToFactory(1119724360, EnemyMetis, "Metis_145");
                break;
            case 21390:
                orderActorToFactory(1119724390, EnemyMetis, "Metis_146");
                break;
            case 21420:
                orderActorToFactory(1119724420, EnemyMetis, "Metis_147");
                break;
            case 21450:
                orderActorToFactory(1119724450, EnemyMetis, "Metis_148");
                break;
            case 21480:
                orderActorToFactory(1119724480, EnemyMetis, "Metis_149");
                break;
            case 21500:
                getLordActor()->addSubGroup(obtainActorFromFactory(1118721500));
                break;
            case 21510:
                orderActorToFactory(1119724510, EnemyMetis, "Metis_150");
                break;
            case 21540:
                orderActorToFactory(1119724540, EnemyMetis, "Metis_151");
                break;
            case 21570:
                orderActorToFactory(1119724570, EnemyMetis, "Metis_152");
                break;
            case 21600:
                orderActorToFactory(1119724600, EnemyMetis, "Metis_153");
                break;
            case 21630:
                orderActorToFactory(1119724630, EnemyMetis, "Metis_154");
                break;
            case 21660:
                orderActorToFactory(1119724660, EnemyMetis, "Metis_155");
                break;
            case 21690:
                orderActorToFactory(1119724690, EnemyMetis, "Metis_156");
                break;
            case 21720:
                orderActorToFactory(1119724720, EnemyMetis, "Metis_157");
                break;
            case 21750:
                orderActorToFactory(1119724750, EnemyMetis, "Metis_158");
                break;
            case 21780:
                orderActorToFactory(1119724780, EnemyMetis, "Metis_159");
                break;
            case 21810:
                orderActorToFactory(1119724810, EnemyMetis, "Metis_160");
                break;
            case 21840:
                orderActorToFactory(1119724840, EnemyMetis, "Metis_161");
                break;
            case 21870:
                orderActorToFactory(1119724870, EnemyMetis, "Metis_162");
                break;
            case 21900:
                orderActorToFactory(1119724900, EnemyMetis, "Metis_163");
                break;
            case 21930:
                orderActorToFactory(1119724930, EnemyMetis, "Metis_164");
                break;
            case 21960:
                orderActorToFactory(1119724960, EnemyMetis, "Metis_165");
                break;
            case 21990:
                orderActorToFactory(1119724990, EnemyMetis, "Metis_166");
                break;
            case 22000:
                getLordActor()->addSubGroup(obtainActorFromFactory(1118722000));
                break;
            case 22020:
                orderActorToFactory(1119725020, EnemyMetis, "Metis_167");
                break;
            case 22050:
                orderActorToFactory(1119725050, EnemyMetis, "Metis_168");
                break;
            case 22080:
                orderActorToFactory(1119725080, EnemyMetis, "Metis_169");
                break;
            case 22110:
                orderActorToFactory(1119725110, EnemyMetis, "Metis_170");
                break;
            case 22140:
                orderActorToFactory(1119725140, EnemyMetis, "Metis_171");
                break;
            case 22170:
                orderActorToFactory(1119725170, EnemyMetis, "Metis_172");
                break;
            case 22200:
                orderActorToFactory(1119725200, EnemyMetis, "Metis_173");
                break;
            case 22230:
                orderActorToFactory(1119725230, EnemyMetis, "Metis_174");
                break;
            case 22260:
                orderActorToFactory(1119725260, EnemyMetis, "Metis_175");
                break;
            case 22290:
                orderActorToFactory(1119725290, EnemyMetis, "Metis_176");
                break;
            case 22320:
                orderActorToFactory(1119725320, EnemyMetis, "Metis_177");
                break;
            case 22350:
                orderActorToFactory(1119725350, EnemyMetis, "Metis_178");
                break;
            case 22380:
                orderActorToFactory(1119725380, EnemyMetis, "Metis_179");
                break;
            case 22410:
                orderActorToFactory(1119725410, EnemyMetis, "Metis_180");
                break;
            case 22440:
                orderActorToFactory(1119725440, EnemyMetis, "Metis_181");
                break;
            case 22470:
                orderActorToFactory(1119725470, EnemyMetis, "Metis_182");
                break;
            case 22500:
                getLordActor()->addSubGroup(obtainActorFromFactory(1118722500));
                orderActorToFactory(1119725500, EnemyMetis, "Metis_183");
                break;
            case 22530:
                orderActorToFactory(1119725530, EnemyMetis, "Metis_184");
                break;
            case 22560:
                orderActorToFactory(1119725560, EnemyMetis, "Metis_185");
                break;
            case 22590:
                orderActorToFactory(1119725590, EnemyMetis, "Metis_186");
                break;
            case 22620:
                orderActorToFactory(1119725620, EnemyMetis, "Metis_187");
                break;
            case 22650:
                orderActorToFactory(1119725650, EnemyMetis, "Metis_188");
                break;
            case 22680:
                orderActorToFactory(1119725680, EnemyMetis, "Metis_189");
                break;
            case 22710:
                orderActorToFactory(1119725710, EnemyMetis, "Metis_190");
                break;
            case 22740:
                orderActorToFactory(1119725740, EnemyMetis, "Metis_191");
                break;
            case 22770:
                orderActorToFactory(1119725770, EnemyMetis, "Metis_192");
                break;
            case 22800:
                orderActorToFactory(1119725800, EnemyMetis, "Metis_193");
                break;
            case 22830:
                orderActorToFactory(1119725830, EnemyMetis, "Metis_194");
                break;
            case 22860:
                orderActorToFactory(1119725860, EnemyMetis, "Metis_195");
                break;
            case 22890:
                orderActorToFactory(1119725890, EnemyMetis, "Metis_196");
                break;
            case 22920:
                orderActorToFactory(1119725920, EnemyMetis, "Metis_197");
                break;
            case 22950:
                orderActorToFactory(1119725950, EnemyMetis, "Metis_198");
                break;
            case 22980:
                orderActorToFactory(1119725980, EnemyMetis, "Metis_199");
                break;
            case 23000:
                getLordActor()->addSubGroup(obtainActorFromFactory(1118723000));
                break;
            case 23010:
                orderActorToFactory(1119726010, EnemyMetis, "Metis_200");
                break;
            case 23040:
                orderActorToFactory(1119726040, EnemyMetis, "Metis_201");
                break;
            case 23070:
                orderActorToFactory(1119726070, EnemyMetis, "Metis_202");
                break;
            case 23100:
                orderActorToFactory(1119726100, EnemyMetis, "Metis_203");
                break;
            case 23130:
                orderActorToFactory(1119726130, EnemyMetis, "Metis_204");
                break;
            case 23160:
                orderActorToFactory(1119726160, EnemyMetis, "Metis_205");
                break;
            case 23190:
                orderActorToFactory(1119726190, EnemyMetis, "Metis_206");
                break;
            case 23220:
                orderActorToFactory(1119726220, EnemyMetis, "Metis_207");
                break;
            case 23250:
                orderActorToFactory(1119726250, EnemyMetis, "Metis_208");
                break;
            case 23280:
                orderActorToFactory(1119726280, EnemyMetis, "Metis_209");
                break;
            case 23310:
                orderActorToFactory(1119726310, EnemyMetis, "Metis_210");
                break;
            case 23340:
                orderActorToFactory(1119726340, EnemyMetis, "Metis_211");
                break;
            case 23370:
                orderActorToFactory(1119726370, EnemyMetis, "Metis_212");
                break;
            case 23400:
                orderActorToFactory(1119726400, EnemyMetis, "Metis_213");
                break;
            case 23430:
                orderActorToFactory(1119726430, EnemyMetis, "Metis_214");
                break;
            case 23460:
                orderActorToFactory(1119726460, EnemyMetis, "Metis_215");
                break;
            case 23490:
                orderActorToFactory(1119726490, EnemyMetis, "Metis_216");
                break;
            case 23500:
                getLordActor()->addSubGroup(obtainActorFromFactory(1118723500));
                break;
            case 23520:
                orderActorToFactory(1119726520, EnemyMetis, "Metis_217");
                break;
            case 23550:
                orderActorToFactory(1119726550, EnemyMetis, "Metis_218");
                break;
            case 23580:
                orderActorToFactory(1119726580, EnemyMetis, "Metis_219");
                break;
            case 23610:
                orderActorToFactory(1119726610, EnemyMetis, "Metis_220");
                break;
            case 23640:
                orderActorToFactory(1119726640, EnemyMetis, "Metis_221");
                break;
            case 23670:
                orderActorToFactory(1119726670, EnemyMetis, "Metis_222");
                break;
            case 23700:
                orderActorToFactory(1119726700, EnemyMetis, "Metis_223");
                break;
            case 23730:
                orderActorToFactory(1119726730, EnemyMetis, "Metis_224");
                break;
            case 23760:
                orderActorToFactory(1119726760, EnemyMetis, "Metis_225");
                break;
            case 23790:
                orderActorToFactory(1119726790, EnemyMetis, "Metis_226");
                break;
            case 23820:
                orderActorToFactory(1119726820, EnemyMetis, "Metis_227");
                break;
            case 23850:
                orderActorToFactory(1119726850, EnemyMetis, "Metis_228");
                break;
            case 23880:
                orderActorToFactory(1119726880, EnemyMetis, "Metis_229");
                break;
            case 23910:
                orderActorToFactory(1119726910, EnemyMetis, "Metis_230");
                break;
            case 23940:
                orderActorToFactory(1119726940, EnemyMetis, "Metis_231");
                break;
            case 23970:
                orderActorToFactory(1119726970, EnemyMetis, "Metis_232");
                break;
            case 24000:
                getLordActor()->addSubGroup(obtainActorFromFactory(1118724000));
                getLordActor()->addSubGroup(obtainActorFromFactory(1119724000));
                orderActorToFactory(1119727000, EnemyMetis, "Metis_233");
                break;
            case 24030:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119724030));
                orderActorToFactory(1119727030, EnemyMetis, "Metis_234");
                break;
            case 24060:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119724060));
                orderActorToFactory(1119727060, EnemyMetis, "Metis_235");
                break;
            case 24090:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119724090));
                orderActorToFactory(1119727090, EnemyMetis, "Metis_236");
                break;
            case 24120:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119724120));
                orderActorToFactory(1119727120, EnemyMetis, "Metis_237");
                break;
            case 24150:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119724150));
                orderActorToFactory(1119727150, EnemyMetis, "Metis_238");
                break;
            case 24180:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119724180));
                orderActorToFactory(1119727180, EnemyMetis, "Metis_239");
                break;
            case 24210:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119724210));
                orderActorToFactory(1119727210, EnemyMetis, "Metis_240");
                break;
            case 24240:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119724240));
                orderActorToFactory(1119727240, EnemyMetis, "Metis_241");
                break;
            case 24270:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119724270));
                orderActorToFactory(1119727270, EnemyMetis, "Metis_242");
                break;
            case 24300:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119724300));
                orderActorToFactory(1119727300, EnemyMetis, "Metis_243");
                break;
            case 24330:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119724330));
                orderActorToFactory(1119727330, EnemyMetis, "Metis_244");
                break;
            case 24360:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119724360));
                orderActorToFactory(1119727360, EnemyMetis, "Metis_245");
                break;
            case 24390:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119724390));
                orderActorToFactory(1119727390, EnemyMetis, "Metis_246");
                break;
            case 24420:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119724420));
                orderActorToFactory(1119727420, EnemyMetis, "Metis_247");
                break;
            case 24450:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119724450));
                orderActorToFactory(1119727450, EnemyMetis, "Metis_248");
                break;
            case 24480:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119724480));
                orderActorToFactory(1119727480, EnemyMetis, "Metis_249");
                break;
            case 24510:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119724510));
                orderActorToFactory(1119727510, EnemyMetis, "Metis_250");
                break;
            case 24540:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119724540));
                orderActorToFactory(1119727540, EnemyMetis, "Metis_251");
                break;
            case 24570:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119724570));
                orderActorToFactory(1119727570, EnemyMetis, "Metis_252");
                break;
            case 24600:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119724600));
                orderActorToFactory(1119727600, EnemyMetis, "Metis_253");
                break;
            case 24630:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119724630));
                orderActorToFactory(1119727630, EnemyMetis, "Metis_254");
                break;
            case 24660:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119724660));
                orderActorToFactory(1119727660, EnemyMetis, "Metis_255");
                break;
            case 24690:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119724690));
                orderActorToFactory(1119727690, EnemyMetis, "Metis_256");
                break;
            case 24720:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119724720));
                orderActorToFactory(1119727720, EnemyMetis, "Metis_257");
                break;
            case 24750:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119724750));
                orderActorToFactory(1119727750, EnemyMetis, "Metis_258");
                break;
            case 24780:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119724780));
                orderActorToFactory(1119727780, EnemyMetis, "Metis_259");
                break;
            case 24810:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119724810));
                orderActorToFactory(1119727810, EnemyMetis, "Metis_260");
                break;
            case 24840:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119724840));
                orderActorToFactory(1119727840, EnemyMetis, "Metis_261");
                break;
            case 24870:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119724870));
                orderActorToFactory(1119727870, EnemyMetis, "Metis_262");
                break;
            case 24900:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119724900));
                orderActorToFactory(1119727900, EnemyMetis, "Metis_263");
                break;
            case 24930:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119724930));
                orderActorToFactory(1119727930, EnemyMetis, "Metis_264");
                break;
            case 24960:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119724960));
                orderActorToFactory(1119727960, EnemyMetis, "Metis_265");
                break;
            case 24990:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119724990));
                orderActorToFactory(1119727990, EnemyMetis, "Metis_266");
                break;
            case 25020:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119725020));
                orderActorToFactory(1119728020, EnemyMetis, "Metis_267");
                break;
            case 25050:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119725050));
                orderActorToFactory(1119728050, EnemyMetis, "Metis_268");
                break;
            case 25080:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119725080));
                orderActorToFactory(1119728080, EnemyMetis, "Metis_269");
                break;
            case 25110:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119725110));
                orderActorToFactory(1119728110, EnemyMetis, "Metis_270");
                break;
            case 25140:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119725140));
                orderActorToFactory(1119728140, EnemyMetis, "Metis_271");
                break;
            case 25170:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119725170));
                orderActorToFactory(1119728170, EnemyMetis, "Metis_272");
                break;
            case 25200:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119725200));
                orderActorToFactory(1119728200, EnemyMetis, "Metis_273");
                break;
            case 25230:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119725230));
                orderActorToFactory(1119728230, EnemyMetis, "Metis_274");
                break;
            case 25260:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119725260));
                orderActorToFactory(1119728260, EnemyMetis, "Metis_275");
                break;
            case 25290:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119725290));
                orderActorToFactory(1119728290, EnemyMetis, "Metis_276");
                break;
            case 25320:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119725320));
                orderActorToFactory(1119728320, EnemyMetis, "Metis_277");
                break;
            case 25350:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119725350));
                orderActorToFactory(1119728350, EnemyMetis, "Metis_278");
                break;
            case 25380:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119725380));
                orderActorToFactory(1119728380, EnemyMetis, "Metis_279");
                break;
            case 25410:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119725410));
                orderActorToFactory(1119728410, EnemyMetis, "Metis_280");
                break;
            case 25440:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119725440));
                orderActorToFactory(1119728440, EnemyMetis, "Metis_281");
                break;
            case 25470:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119725470));
                orderActorToFactory(1119728470, EnemyMetis, "Metis_282");
                break;
            case 25500:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119725500));
                orderActorToFactory(1119728500, EnemyMetis, "Metis_283");
                break;
            case 25530:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119725530));
                orderActorToFactory(1119728530, EnemyMetis, "Metis_284");
                break;
            case 25560:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119725560));
                orderActorToFactory(1119728560, EnemyMetis, "Metis_285");
                break;
            case 25590:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119725590));
                orderActorToFactory(1119728590, EnemyMetis, "Metis_286");
                break;
            case 25620:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119725620));
                orderActorToFactory(1119728620, EnemyMetis, "Metis_287");
                break;
            case 25650:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119725650));
                orderActorToFactory(1119728650, EnemyMetis, "Metis_288");
                break;
            case 25680:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119725680));
                orderActorToFactory(1119728680, EnemyMetis, "Metis_289");
                break;
            case 25710:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119725710));
                orderActorToFactory(1119728710, EnemyMetis, "Metis_290");
                break;
            case 25740:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119725740));
                orderActorToFactory(1119728740, EnemyMetis, "Metis_291");
                break;
            case 25770:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119725770));
                orderActorToFactory(1119728770, EnemyMetis, "Metis_292");
                break;
            case 25800:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119725800));
                orderActorToFactory(1119728800, EnemyMetis, "Metis_293");
                break;
            case 25830:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119725830));
                orderActorToFactory(1119728830, EnemyMetis, "Metis_294");
                break;
            case 25860:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119725860));
                orderActorToFactory(1119728860, EnemyMetis, "Metis_295");
                break;
            case 25890:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119725890));
                orderActorToFactory(1119728890, EnemyMetis, "Metis_296");
                break;
            case 25920:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119725920));
                orderActorToFactory(1119728920, EnemyMetis, "Metis_297");
                break;
            case 25950:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119725950));
                orderActorToFactory(1119728950, EnemyMetis, "Metis_298");
                break;
            case 25980:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119725980));
                orderActorToFactory(1119728980, EnemyMetis, "Metis_299");
                break;
            case 26010:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119726010));
                orderActorToFactory(1119729010, EnemyMetis, "Metis_300");
                break;
            case 26040:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119726040));
                orderActorToFactory(1119729040, EnemyMetis, "Metis_301");
                break;
            case 26070:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119726070));
                orderActorToFactory(1119729070, EnemyMetis, "Metis_302");
                break;
            case 26100:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119726100));
                orderActorToFactory(1119729100, EnemyMetis, "Metis_303");
                break;
            case 26130:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119726130));
                orderActorToFactory(1119729130, EnemyMetis, "Metis_304");
                break;
            case 26160:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119726160));
                orderActorToFactory(1119729160, EnemyMetis, "Metis_305");
                break;
            case 26190:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119726190));
                orderActorToFactory(1119729190, EnemyMetis, "Metis_306");
                break;
            case 26220:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119726220));
                orderActorToFactory(1119729220, EnemyMetis, "Metis_307");
                break;
            case 26250:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119726250));
                orderActorToFactory(1119729250, EnemyMetis, "Metis_308");
                break;
            case 26280:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119726280));
                orderActorToFactory(1119729280, EnemyMetis, "Metis_309");
                break;
            case 26310:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119726310));
                orderActorToFactory(1119729310, EnemyMetis, "Metis_310");
                break;
            case 26340:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119726340));
                orderActorToFactory(1119729340, EnemyMetis, "Metis_311");
                break;
            case 26370:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119726370));
                orderActorToFactory(1119729370, EnemyMetis, "Metis_312");
                break;
            case 26400:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119726400));
                orderActorToFactory(1119729400, EnemyMetis, "Metis_313");
                break;
            case 26430:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119726430));
                orderActorToFactory(1119729430, EnemyMetis, "Metis_314");
                break;
            case 26460:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119726460));
                orderActorToFactory(1119729460, EnemyMetis, "Metis_315");
                break;
            case 26490:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119726490));
                orderActorToFactory(1119729490, EnemyMetis, "Metis_316");
                break;
            case 26520:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119726520));
                orderActorToFactory(1119729520, EnemyMetis, "Metis_317");
                break;
            case 26550:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119726550));
                orderActorToFactory(1119729550, EnemyMetis, "Metis_318");
                break;
            case 26580:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119726580));
                orderActorToFactory(1119729580, EnemyMetis, "Metis_319");
                break;
            case 26610:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119726610));
                orderActorToFactory(1119729610, EnemyMetis, "Metis_320");
                break;
            case 26640:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119726640));
                orderActorToFactory(1119729640, EnemyMetis, "Metis_321");
                break;
            case 26670:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119726670));
                orderActorToFactory(1119729670, EnemyMetis, "Metis_322");
                break;
            case 26700:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119726700));
                orderActorToFactory(1119729700, EnemyMetis, "Metis_323");
                break;
            case 26730:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119726730));
                orderActorToFactory(1119729730, EnemyMetis, "Metis_324");
                break;
            case 26760:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119726760));
                orderActorToFactory(1119729760, EnemyMetis, "Metis_325");
                break;
            case 26790:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119726790));
                orderActorToFactory(1119729790, EnemyMetis, "Metis_326");
                break;
            case 26820:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119726820));
                orderActorToFactory(1119729820, EnemyMetis, "Metis_327");
                break;
            case 26850:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119726850));
                orderActorToFactory(1119729850, EnemyMetis, "Metis_328");
                break;
            case 26880:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119726880));
                orderActorToFactory(1119729880, EnemyMetis, "Metis_329");
                break;
            case 26910:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119726910));
                orderActorToFactory(1119729910, EnemyMetis, "Metis_330");
                break;
            case 26940:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119726940));
                orderActorToFactory(1119729940, EnemyMetis, "Metis_331");
                break;
            case 26970:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119726970));
                orderActorToFactory(1119729970, EnemyMetis, "Metis_332");
                break;
            case 27000:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119727000));
                orderActorToFactory(1119730000, EnemyMetis, "Metis_333");
                break;
            case 27030:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119727030));
                orderActorToFactory(1119730030, EnemyMetis, "Metis_334");
                break;
            case 27060:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119727060));
                orderActorToFactory(1119730060, EnemyMetis, "Metis_335");
                break;
            case 27090:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119727090));
                orderActorToFactory(1119730090, EnemyMetis, "Metis_336");
                break;
            case 27120:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119727120));
                orderActorToFactory(1119730120, EnemyMetis, "Metis_337");
                break;
            case 27150:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119727150));
                orderActorToFactory(1119730150, EnemyMetis, "Metis_338");
                break;
            case 27180:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119727180));
                orderActorToFactory(1119730180, EnemyMetis, "Metis_339");
                break;
            case 27210:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119727210));
                orderActorToFactory(1119730210, EnemyMetis, "Metis_340");
                break;
            case 27240:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119727240));
                orderActorToFactory(1119730240, EnemyMetis, "Metis_341");
                break;
            case 27270:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119727270));
                orderActorToFactory(1119730270, EnemyMetis, "Metis_342");
                break;
            case 27300:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119727300));
                orderActorToFactory(1119730300, EnemyMetis, "Metis_343");
                break;
            case 27330:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119727330));
                orderActorToFactory(1119730330, EnemyMetis, "Metis_344");
                break;
            case 27360:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119727360));
                orderActorToFactory(1119730360, EnemyMetis, "Metis_345");
                break;
            case 27390:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119727390));
                orderActorToFactory(1119730390, EnemyMetis, "Metis_346");
                break;
            case 27420:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119727420));
                orderActorToFactory(1119730420, EnemyMetis, "Metis_347");
                break;
            case 27450:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119727450));
                orderActorToFactory(1119730450, EnemyMetis, "Metis_348");
                break;
            case 27480:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119727480));
                orderActorToFactory(1119730480, EnemyMetis, "Metis_349");
                break;
            case 27510:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119727510));
                orderActorToFactory(1119730510, EnemyMetis, "Metis_350");
                break;
            case 27540:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119727540));
                orderActorToFactory(1119730540, EnemyMetis, "Metis_351");
                break;
            case 27570:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119727570));
                orderActorToFactory(1119730570, EnemyMetis, "Metis_352");
                break;
            case 27600:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119727600));
                orderActorToFactory(1119730600, EnemyMetis, "Metis_353");
                break;
            case 27630:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119727630));
                orderActorToFactory(1119730630, EnemyMetis, "Metis_354");
                break;
            case 27660:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119727660));
                orderActorToFactory(1119730660, EnemyMetis, "Metis_355");
                break;
            case 27690:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119727690));
                orderActorToFactory(1119730690, EnemyMetis, "Metis_356");
                break;
            case 27720:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119727720));
                orderActorToFactory(1119730720, EnemyMetis, "Metis_357");
                break;
            case 27750:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119727750));
                orderActorToFactory(1119730750, EnemyMetis, "Metis_358");
                break;
            case 27780:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119727780));
                orderActorToFactory(1119730780, EnemyMetis, "Metis_359");
                break;
            case 27810:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119727810));
                orderActorToFactory(1119730810, EnemyMetis, "Metis_360");
                break;
            case 27840:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119727840));
                orderActorToFactory(1119730840, EnemyMetis, "Metis_361");
                break;
            case 27870:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119727870));
                orderActorToFactory(1119730870, EnemyMetis, "Metis_362");
                break;
            case 27900:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119727900));
                orderActorToFactory(1119730900, EnemyMetis, "Metis_363");
                break;
            case 27930:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119727930));
                orderActorToFactory(1119730930, EnemyMetis, "Metis_364");
                break;
            case 27960:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119727960));
                orderActorToFactory(1119730960, EnemyMetis, "Metis_365");
                break;
            case 27990:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119727990));
                orderActorToFactory(1119730990, EnemyMetis, "Metis_366");
                break;
            case 28020:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119728020));
                orderActorToFactory(1119731020, EnemyMetis, "Metis_367");
                break;
            case 28050:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119728050));
                orderActorToFactory(1119731050, EnemyMetis, "Metis_368");
                break;
            case 28080:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119728080));
                orderActorToFactory(1119731080, EnemyMetis, "Metis_369");
                break;
            case 28110:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119728110));
                orderActorToFactory(1119731110, EnemyMetis, "Metis_370");
                break;
            case 28140:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119728140));
                orderActorToFactory(1119731140, EnemyMetis, "Metis_371");
                break;
            case 28170:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119728170));
                orderActorToFactory(1119731170, EnemyMetis, "Metis_372");
                break;
            case 28200:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119728200));
                orderActorToFactory(1119731200, EnemyMetis, "Metis_373");
                break;
            case 28230:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119728230));
                orderActorToFactory(1119731230, EnemyMetis, "Metis_374");
                break;
            case 28260:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119728260));
                orderActorToFactory(1119731260, EnemyMetis, "Metis_375");
                break;
            case 28290:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119728290));
                orderActorToFactory(1119731290, EnemyMetis, "Metis_376");
                break;
            case 28320:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119728320));
                orderActorToFactory(1119731320, EnemyMetis, "Metis_377");
                break;
            case 28350:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119728350));
                orderActorToFactory(1119731350, EnemyMetis, "Metis_378");
                break;
            case 28380:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119728380));
                orderActorToFactory(1119731380, EnemyMetis, "Metis_379");
                break;
            case 28410:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119728410));
                orderActorToFactory(1119731410, EnemyMetis, "Metis_380");
                break;
            case 28440:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119728440));
                orderActorToFactory(1119731440, EnemyMetis, "Metis_381");
                break;
            case 28470:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119728470));
                orderActorToFactory(1119731470, EnemyMetis, "Metis_382");
                break;
            case 28500:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119728500));
                orderActorToFactory(1119731500, EnemyMetis, "Metis_383");
                break;
            case 28530:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119728530));
                orderActorToFactory(1119731530, EnemyMetis, "Metis_384");
                break;
            case 28560:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119728560));
                orderActorToFactory(1119731560, EnemyMetis, "Metis_385");
                break;
            case 28590:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119728590));
                orderActorToFactory(1119731590, EnemyMetis, "Metis_386");
                break;
            case 28620:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119728620));
                orderActorToFactory(1119731620, EnemyMetis, "Metis_387");
                break;
            case 28650:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119728650));
                orderActorToFactory(1119731650, EnemyMetis, "Metis_388");
                break;
            case 28680:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119728680));
                orderActorToFactory(1119731680, EnemyMetis, "Metis_389");
                break;
            case 28710:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119728710));
                orderActorToFactory(1119731710, EnemyMetis, "Metis_390");
                break;
            case 28740:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119728740));
                orderActorToFactory(1119731740, EnemyMetis, "Metis_391");
                break;
            case 28770:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119728770));
                orderActorToFactory(1119731770, EnemyMetis, "Metis_392");
                break;
            case 28800:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119728800));
                orderActorToFactory(1119731800, EnemyMetis, "Metis_393");
                break;
            case 28830:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119728830));
                orderActorToFactory(1119731830, EnemyMetis, "Metis_394");
                break;
            case 28860:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119728860));
                orderActorToFactory(1119731860, EnemyMetis, "Metis_395");
                break;
            case 28890:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119728890));
                orderActorToFactory(1119731890, EnemyMetis, "Metis_396");
                break;
            case 28920:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119728920));
                orderActorToFactory(1119731920, EnemyMetis, "Metis_397");
                break;
            case 28950:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119728950));
                orderActorToFactory(1119731950, EnemyMetis, "Metis_398");
                break;
            case 28980:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119728980));
                orderActorToFactory(1119731980, EnemyMetis, "Metis_399");
                break;
            case 29010:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119729010));
                orderActorToFactory(1119732010, EnemyMetis, "Metis_400");
                break;
            case 29040:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119729040));
                orderActorToFactory(1119732040, EnemyMetis, "Metis_401");
                break;
            case 29070:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119729070));
                orderActorToFactory(1119732070, EnemyMetis, "Metis_402");
                break;
            case 29100:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119729100));
                orderActorToFactory(1119732100, EnemyMetis, "Metis_403");
                break;
            case 29130:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119729130));
                orderActorToFactory(1119732130, EnemyMetis, "Metis_404");
                break;
            case 29160:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119729160));
                orderActorToFactory(1119732160, EnemyMetis, "Metis_405");
                break;
            case 29190:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119729190));
                orderActorToFactory(1119732190, EnemyMetis, "Metis_406");
                break;
            case 29220:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119729220));
                orderActorToFactory(1119732220, EnemyMetis, "Metis_407");
                break;
            case 29250:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119729250));
                orderActorToFactory(1119732250, EnemyMetis, "Metis_408");
                break;
            case 29280:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119729280));
                orderActorToFactory(1119732280, EnemyMetis, "Metis_409");
                break;
            case 29310:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119729310));
                orderActorToFactory(1119732310, EnemyMetis, "Metis_410");
                break;
            case 29340:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119729340));
                orderActorToFactory(1119732340, EnemyMetis, "Metis_411");
                break;
            case 29370:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119729370));
                orderActorToFactory(1119732370, EnemyMetis, "Metis_412");
                break;
            case 29400:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119729400));
                orderActorToFactory(1119732400, EnemyMetis, "Metis_413");
                break;
            case 29430:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119729430));
                orderActorToFactory(1119732430, EnemyMetis, "Metis_414");
                break;
            case 29460:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119729460));
                orderActorToFactory(1119732460, EnemyMetis, "Metis_415");
                break;
            case 29490:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119729490));
                orderActorToFactory(1119732490, EnemyMetis, "Metis_416");
                break;
            case 29520:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119729520));
                orderActorToFactory(1119732520, EnemyMetis, "Metis_417");
                break;
            case 29550:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119729550));
                orderActorToFactory(1119732550, EnemyMetis, "Metis_418");
                break;
            case 29580:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119729580));
                orderActorToFactory(1119732580, EnemyMetis, "Metis_419");
                break;
            case 29610:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119729610));
                orderActorToFactory(1119732610, EnemyMetis, "Metis_420");
                break;
            case 29640:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119729640));
                orderActorToFactory(1119732640, EnemyMetis, "Metis_421");
                break;
            case 29670:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119729670));
                orderActorToFactory(1119732670, EnemyMetis, "Metis_422");
                break;
            case 29700:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119729700));
                orderActorToFactory(1119732700, EnemyMetis, "Metis_423");
                break;
            case 29730:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119729730));
                orderActorToFactory(1119732730, EnemyMetis, "Metis_424");
                break;
            case 29760:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119729760));
                orderActorToFactory(1119732760, EnemyMetis, "Metis_425");
                break;
            case 29790:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119729790));
                orderActorToFactory(1119732790, EnemyMetis, "Metis_426");
                break;
            case 29820:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119729820));
                orderActorToFactory(1119732820, EnemyMetis, "Metis_427");
                break;
            case 29850:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119729850));
                orderActorToFactory(1119732850, EnemyMetis, "Metis_428");
                break;
            case 29880:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119729880));
                orderActorToFactory(1119732880, EnemyMetis, "Metis_429");
                break;
            case 29910:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119729910));
                orderActorToFactory(1119732910, EnemyMetis, "Metis_430");
                break;
            case 29940:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119729940));
                orderActorToFactory(1119732940, EnemyMetis, "Metis_431");
                break;
            case 29970:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119729970));
                orderActorToFactory(1119732970, EnemyMetis, "Metis_432");
                break;
            case 30000:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119730000));
                orderActorToFactory(1119733000, EnemyMetis, "Metis_433");
                break;
            case 30030:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119730030));
                orderActorToFactory(1119733030, EnemyMetis, "Metis_434");
                break;
            case 30060:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119730060));
                orderActorToFactory(1119733060, EnemyMetis, "Metis_435");
                break;
            case 30090:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119730090));
                orderActorToFactory(1119733090, EnemyMetis, "Metis_436");
                break;
            case 30120:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119730120));
                orderActorToFactory(1119733120, EnemyMetis, "Metis_437");
                break;
            case 30150:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119730150));
                orderActorToFactory(1119733150, EnemyMetis, "Metis_438");
                break;
            case 30180:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119730180));
                orderActorToFactory(1119733180, EnemyMetis, "Metis_439");
                break;
            case 30210:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119730210));
                orderActorToFactory(1119733210, EnemyMetis, "Metis_440");
                break;
            case 30240:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119730240));
                orderActorToFactory(1119733240, EnemyMetis, "Metis_441");
                break;
            case 30270:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119730270));
                orderActorToFactory(1119733270, EnemyMetis, "Metis_442");
                break;
            case 30300:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119730300));
                orderActorToFactory(1119733300, EnemyMetis, "Metis_443");
                break;
            case 30330:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119730330));
                orderActorToFactory(1119733330, EnemyMetis, "Metis_444");
                break;
            case 30360:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119730360));
                orderActorToFactory(1119733360, EnemyMetis, "Metis_445");
                break;
            case 30390:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119730390));
                orderActorToFactory(1119733390, EnemyMetis, "Metis_446");
                break;
            case 30420:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119730420));
                orderActorToFactory(1119733420, EnemyMetis, "Metis_447");
                break;
            case 30450:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119730450));
                orderActorToFactory(1119733450, EnemyMetis, "Metis_448");
                break;
            case 30480:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119730480));
                orderActorToFactory(1119733480, EnemyMetis, "Metis_449");
                break;
            case 30510:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119730510));
                orderActorToFactory(1119733510, EnemyMetis, "Metis_450");
                break;
            case 30540:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119730540));
                orderActorToFactory(1119733540, EnemyMetis, "Metis_451");
                break;
            case 30570:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119730570));
                orderActorToFactory(1119733570, EnemyMetis, "Metis_452");
                break;
            case 30600:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119730600));
                orderActorToFactory(1119733600, EnemyMetis, "Metis_453");
                break;
            case 30630:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119730630));
                orderActorToFactory(1119733630, EnemyMetis, "Metis_454");
                break;
            case 30660:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119730660));
                orderActorToFactory(1119733660, EnemyMetis, "Metis_455");
                break;
            case 30690:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119730690));
                orderActorToFactory(1119733690, EnemyMetis, "Metis_456");
                break;
            case 30720:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119730720));
                orderActorToFactory(1119733720, EnemyMetis, "Metis_457");
                break;
            case 30750:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119730750));
                orderActorToFactory(1119733750, EnemyMetis, "Metis_458");
                break;
            case 30780:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119730780));
                orderActorToFactory(1119733780, EnemyMetis, "Metis_459");
                break;
            case 30810:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119730810));
                orderActorToFactory(1119733810, EnemyMetis, "Metis_460");
                break;
            case 30840:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119730840));
                orderActorToFactory(1119733840, EnemyMetis, "Metis_461");
                break;
            case 30870:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119730870));
                orderActorToFactory(1119733870, EnemyMetis, "Metis_462");
                break;
            case 30900:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119730900));
                orderActorToFactory(1119733900, EnemyMetis, "Metis_463");
                break;
            case 30930:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119730930));
                orderActorToFactory(1119733930, EnemyMetis, "Metis_464");
                break;
            case 30960:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119730960));
                orderActorToFactory(1119733960, EnemyMetis, "Metis_465");
                break;
            case 30990:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119730990));
                orderActorToFactory(1119733990, EnemyMetis, "Metis_466");
                break;
            case 31020:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119731020));
                orderActorToFactory(1119734020, EnemyMetis, "Metis_467");
                break;
            case 31050:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119731050));
                orderActorToFactory(1119734050, EnemyMetis, "Metis_468");
                break;
            case 31080:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119731080));
                orderActorToFactory(1119734080, EnemyMetis, "Metis_469");
                break;
            case 31110:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119731110));
                orderActorToFactory(1119734110, EnemyMetis, "Metis_470");
                break;
            case 31140:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119731140));
                orderActorToFactory(1119734140, EnemyMetis, "Metis_471");
                break;
            case 31170:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119731170));
                orderActorToFactory(1119734170, EnemyMetis, "Metis_472");
                break;
            case 31200:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119731200));
                orderActorToFactory(1119734200, EnemyMetis, "Metis_473");
                break;
            case 31230:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119731230));
                orderActorToFactory(1119734230, EnemyMetis, "Metis_474");
                break;
            case 31260:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119731260));
                orderActorToFactory(1119734260, EnemyMetis, "Metis_475");
                break;
            case 31290:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119731290));
                orderActorToFactory(1119734290, EnemyMetis, "Metis_476");
                break;
            case 31320:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119731320));
                orderActorToFactory(1119734320, EnemyMetis, "Metis_477");
                break;
            case 31350:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119731350));
                orderActorToFactory(1119734350, EnemyMetis, "Metis_478");
                break;
            case 31380:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119731380));
                orderActorToFactory(1119734380, EnemyMetis, "Metis_479");
                break;
            case 31410:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119731410));
                orderActorToFactory(1119734410, EnemyMetis, "Metis_480");
                break;
            case 31440:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119731440));
                orderActorToFactory(1119734440, EnemyMetis, "Metis_481");
                break;
            case 31470:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119731470));
                orderActorToFactory(1119734470, EnemyMetis, "Metis_482");
                break;
            case 31500:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119731500));
                orderActorToFactory(1119734500, EnemyMetis, "Metis_483");
                break;
            case 31530:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119731530));
                orderActorToFactory(1119734530, EnemyMetis, "Metis_484");
                break;
            case 31560:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119731560));
                orderActorToFactory(1119734560, EnemyMetis, "Metis_485");
                break;
            case 31590:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119731590));
                orderActorToFactory(1119734590, EnemyMetis, "Metis_486");
                break;
            case 31620:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119731620));
                orderActorToFactory(1119734620, EnemyMetis, "Metis_487");
                break;
            case 31650:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119731650));
                orderActorToFactory(1119734650, EnemyMetis, "Metis_488");
                break;
            case 31680:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119731680));
                orderActorToFactory(1119734680, EnemyMetis, "Metis_489");
                break;
            case 31710:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119731710));
                orderActorToFactory(1119734710, EnemyMetis, "Metis_490");
                break;
            case 31740:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119731740));
                orderActorToFactory(1119734740, EnemyMetis, "Metis_491");
                break;
            case 31770:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119731770));
                orderActorToFactory(1119734770, EnemyMetis, "Metis_492");
                break;
            case 31800:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119731800));
                orderActorToFactory(1119734800, EnemyMetis, "Metis_493");
                break;
            case 31830:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119731830));
                orderActorToFactory(1119734830, EnemyMetis, "Metis_494");
                break;
            case 31860:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119731860));
                orderActorToFactory(1119734860, EnemyMetis, "Metis_495");
                break;
            case 31890:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119731890));
                orderActorToFactory(1119734890, EnemyMetis, "Metis_496");
                break;
            case 31920:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119731920));
                orderActorToFactory(1119734920, EnemyMetis, "Metis_497");
                break;
            case 31950:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119731950));
                orderActorToFactory(1119734950, EnemyMetis, "Metis_498");
                break;
            case 31980:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119731980));
                orderActorToFactory(1119734980, EnemyMetis, "Metis_499");
                break;
            case 32010:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119732010));
                orderActorToFactory(1119735010, EnemyMetis, "Metis_500");
                break;
            case 32040:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119732040));
                orderActorToFactory(1119735040, EnemyMetis, "Metis_501");
                break;
            case 32070:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119732070));
                orderActorToFactory(1119735070, EnemyMetis, "Metis_502");
                break;
            case 32100:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119732100));
                orderActorToFactory(1119735100, EnemyMetis, "Metis_503");
                break;
            case 32130:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119732130));
                orderActorToFactory(1119735130, EnemyMetis, "Metis_504");
                break;
            case 32160:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119732160));
                orderActorToFactory(1119735160, EnemyMetis, "Metis_505");
                break;
            case 32190:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119732190));
                orderActorToFactory(1119735190, EnemyMetis, "Metis_506");
                break;
            case 32220:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119732220));
                orderActorToFactory(1119735220, EnemyMetis, "Metis_507");
                break;
            case 32250:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119732250));
                orderActorToFactory(1119735250, EnemyMetis, "Metis_508");
                break;
            case 32280:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119732280));
                orderActorToFactory(1119735280, EnemyMetis, "Metis_509");
                break;
            case 32310:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119732310));
                orderActorToFactory(1119735310, EnemyMetis, "Metis_510");
                break;
            case 32340:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119732340));
                orderActorToFactory(1119735340, EnemyMetis, "Metis_511");
                break;
            case 32370:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119732370));
                orderActorToFactory(1119735370, EnemyMetis, "Metis_512");
                break;
            case 32400:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119732400));
                orderActorToFactory(1119735400, EnemyMetis, "Metis_513");
                break;
            case 32430:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119732430));
                orderActorToFactory(1119735430, EnemyMetis, "Metis_514");
                break;
            case 32460:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119732460));
                orderActorToFactory(1119735460, EnemyMetis, "Metis_515");
                break;
            case 32490:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119732490));
                orderActorToFactory(1119735490, EnemyMetis, "Metis_516");
                break;
            case 32520:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119732520));
                orderActorToFactory(1119735520, EnemyMetis, "Metis_517");
                break;
            case 32550:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119732550));
                orderActorToFactory(1119735550, EnemyMetis, "Metis_518");
                break;
            case 32580:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119732580));
                orderActorToFactory(1119735580, EnemyMetis, "Metis_519");
                break;
            case 32610:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119732610));
                orderActorToFactory(1119735610, EnemyMetis, "Metis_520");
                break;
            case 32640:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119732640));
                orderActorToFactory(1119735640, EnemyMetis, "Metis_521");
                break;
            case 32670:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119732670));
                orderActorToFactory(1119735670, EnemyMetis, "Metis_522");
                break;
            case 32700:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119732700));
                orderActorToFactory(1119735700, EnemyMetis, "Metis_523");
                break;
            case 32730:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119732730));
                orderActorToFactory(1119735730, EnemyMetis, "Metis_524");
                break;
            case 32760:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119732760));
                orderActorToFactory(1119735760, EnemyMetis, "Metis_525");
                break;
            case 32790:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119732790));
                orderActorToFactory(1119735790, EnemyMetis, "Metis_526");
                break;
            case 32820:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119732820));
                orderActorToFactory(1119735820, EnemyMetis, "Metis_527");
                break;
            case 32850:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119732850));
                orderActorToFactory(1119735850, EnemyMetis, "Metis_528");
                break;
            case 32880:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119732880));
                orderActorToFactory(1119735880, EnemyMetis, "Metis_529");
                break;
            case 32910:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119732910));
                orderActorToFactory(1119735910, EnemyMetis, "Metis_530");
                break;
            case 32940:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119732940));
                orderActorToFactory(1119735940, EnemyMetis, "Metis_531");
                break;
            case 32970:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119732970));
                orderActorToFactory(1119735970, EnemyMetis, "Metis_532");
                break;
            case 33000:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119733000));
                orderActorToFactory(1119736000, EnemyMetis, "Metis_533");
                break;
            case 33030:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119733030));
                orderActorToFactory(1119736030, EnemyMetis, "Metis_534");
                break;
            case 33060:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119733060));
                orderActorToFactory(1119736060, EnemyMetis, "Metis_535");
                break;
            case 33090:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119733090));
                orderActorToFactory(1119736090, EnemyMetis, "Metis_536");
                break;
            case 33120:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119733120));
                orderActorToFactory(1119736120, EnemyMetis, "Metis_537");
                break;
            case 33150:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119733150));
                orderActorToFactory(1119736150, EnemyMetis, "Metis_538");
                break;
            case 33180:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119733180));
                orderActorToFactory(1119736180, EnemyMetis, "Metis_539");
                break;
            case 33210:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119733210));
                orderActorToFactory(1119736210, EnemyMetis, "Metis_540");
                break;
            case 33240:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119733240));
                orderActorToFactory(1119736240, EnemyMetis, "Metis_541");
                break;
            case 33270:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119733270));
                orderActorToFactory(1119736270, EnemyMetis, "Metis_542");
                break;
            case 33300:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119733300));
                orderActorToFactory(1119736300, EnemyMetis, "Metis_543");
                break;
            case 33330:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119733330));
                orderActorToFactory(1119736330, EnemyMetis, "Metis_544");
                break;
            case 33360:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119733360));
                orderActorToFactory(1119736360, EnemyMetis, "Metis_545");
                break;
            case 33390:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119733390));
                orderActorToFactory(1119736390, EnemyMetis, "Metis_546");
                break;
            case 33420:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119733420));
                orderActorToFactory(1119736420, EnemyMetis, "Metis_547");
                break;
            case 33450:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119733450));
                orderActorToFactory(1119736450, EnemyMetis, "Metis_548");
                break;
            case 33480:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119733480));
                orderActorToFactory(1119736480, EnemyMetis, "Metis_549");
                break;
            case 33510:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119733510));
                orderActorToFactory(1119736510, EnemyMetis, "Metis_550");
                break;
            case 33540:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119733540));
                orderActorToFactory(1119736540, EnemyMetis, "Metis_551");
                break;
            case 33570:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119733570));
                orderActorToFactory(1119736570, EnemyMetis, "Metis_552");
                break;
            case 33600:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119733600));
                orderActorToFactory(1119736600, EnemyMetis, "Metis_553");
                break;
            case 33630:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119733630));
                orderActorToFactory(1119736630, EnemyMetis, "Metis_554");
                break;
            case 33660:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119733660));
                orderActorToFactory(1119736660, EnemyMetis, "Metis_555");
                break;
            case 33690:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119733690));
                orderActorToFactory(1119736690, EnemyMetis, "Metis_556");
                break;
            case 33720:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119733720));
                orderActorToFactory(1119736720, EnemyMetis, "Metis_557");
                break;
            case 33750:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119733750));
                orderActorToFactory(1119736750, EnemyMetis, "Metis_558");
                break;
            case 33780:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119733780));
                orderActorToFactory(1119736780, EnemyMetis, "Metis_559");
                break;
            case 33810:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119733810));
                orderActorToFactory(1119736810, EnemyMetis, "Metis_560");
                break;
            case 33840:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119733840));
                orderActorToFactory(1119736840, EnemyMetis, "Metis_561");
                break;
            case 33870:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119733870));
                orderActorToFactory(1119736870, EnemyMetis, "Metis_562");
                break;
            case 33900:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119733900));
                orderActorToFactory(1119736900, EnemyMetis, "Metis_563");
                break;
            case 33930:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119733930));
                orderActorToFactory(1119736930, EnemyMetis, "Metis_564");
                break;
            case 33960:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119733960));
                orderActorToFactory(1119736960, EnemyMetis, "Metis_565");
                break;
            case 33990:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119733990));
                orderActorToFactory(1119736990, EnemyMetis, "Metis_566");
                break;
            case 34020:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119734020));
                orderActorToFactory(1119737020, EnemyMetis, "Metis_567");
                break;
            case 34050:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119734050));
                orderActorToFactory(1119737050, EnemyMetis, "Metis_568");
                break;
            case 34080:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119734080));
                orderActorToFactory(1119737080, EnemyMetis, "Metis_569");
                break;
            case 34110:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119734110));
                orderActorToFactory(1119737110, EnemyMetis, "Metis_570");
                break;
            case 34140:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119734140));
                orderActorToFactory(1119737140, EnemyMetis, "Metis_571");
                break;
            case 34170:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119734170));
                orderActorToFactory(1119737170, EnemyMetis, "Metis_572");
                break;
            case 34200:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119734200));
                orderActorToFactory(1119737200, EnemyMetis, "Metis_573");
                break;
            case 34230:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119734230));
                orderActorToFactory(1119737230, EnemyMetis, "Metis_574");
                break;
            case 34260:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119734260));
                orderActorToFactory(1119737260, EnemyMetis, "Metis_575");
                break;
            case 34290:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119734290));
                orderActorToFactory(1119737290, EnemyMetis, "Metis_576");
                break;
            case 34320:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119734320));
                orderActorToFactory(1119737320, EnemyMetis, "Metis_577");
                break;
            case 34350:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119734350));
                orderActorToFactory(1119737350, EnemyMetis, "Metis_578");
                break;
            case 34380:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119734380));
                orderActorToFactory(1119737380, EnemyMetis, "Metis_579");
                break;
            case 34410:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119734410));
                orderActorToFactory(1119737410, EnemyMetis, "Metis_580");
                break;
            case 34440:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119734440));
                orderActorToFactory(1119737440, EnemyMetis, "Metis_581");
                break;
            case 34470:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119734470));
                orderActorToFactory(1119737470, EnemyMetis, "Metis_582");
                break;
            case 34500:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119734500));
                orderActorToFactory(1119737500, EnemyMetis, "Metis_583");
                break;
            case 34530:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119734530));
                orderActorToFactory(1119737530, EnemyMetis, "Metis_584");
                break;
            case 34560:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119734560));
                orderActorToFactory(1119737560, EnemyMetis, "Metis_585");
                break;
            case 34590:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119734590));
                orderActorToFactory(1119737590, EnemyMetis, "Metis_586");
                break;
            case 34620:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119734620));
                orderActorToFactory(1119737620, EnemyMetis, "Metis_587");
                break;
            case 34650:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119734650));
                orderActorToFactory(1119737650, EnemyMetis, "Metis_588");
                break;
            case 34680:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119734680));
                orderActorToFactory(1119737680, EnemyMetis, "Metis_589");
                break;
            case 34710:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119734710));
                orderActorToFactory(1119737710, EnemyMetis, "Metis_590");
                break;
            case 34740:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119734740));
                orderActorToFactory(1119737740, EnemyMetis, "Metis_591");
                break;
            case 34770:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119734770));
                orderActorToFactory(1119737770, EnemyMetis, "Metis_592");
                break;
            case 34800:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119734800));
                orderActorToFactory(1119737800, EnemyMetis, "Metis_593");
                break;
            case 34830:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119734830));
                orderActorToFactory(1119737830, EnemyMetis, "Metis_594");
                break;
            case 34860:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119734860));
                orderActorToFactory(1119737860, EnemyMetis, "Metis_595");
                break;
            case 34890:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119734890));
                orderActorToFactory(1119737890, EnemyMetis, "Metis_596");
                break;
            case 34920:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119734920));
                orderActorToFactory(1119737920, EnemyMetis, "Metis_597");
                break;
            case 34950:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119734950));
                orderActorToFactory(1119737950, EnemyMetis, "Metis_598");
                break;
            case 34980:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119734980));
                orderActorToFactory(1119737980, EnemyMetis, "Metis_599");
                break;
            case 35010:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119735010));
                orderActorToFactory(1119738010, EnemyMetis, "Metis_600");
                break;
            case 35040:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119735040));
                orderActorToFactory(1119738040, EnemyMetis, "Metis_601");
                break;
            case 35070:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119735070));
                orderActorToFactory(1119738070, EnemyMetis, "Metis_602");
                break;
            case 35100:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119735100));
                orderActorToFactory(1119738100, EnemyMetis, "Metis_603");
                break;
            case 35130:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119735130));
                orderActorToFactory(1119738130, EnemyMetis, "Metis_604");
                break;
            case 35160:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119735160));
                orderActorToFactory(1119738160, EnemyMetis, "Metis_605");
                break;
            case 35190:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119735190));
                orderActorToFactory(1119738190, EnemyMetis, "Metis_606");
                break;
            case 35220:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119735220));
                orderActorToFactory(1119738220, EnemyMetis, "Metis_607");
                break;
            case 35250:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119735250));
                orderActorToFactory(1119738250, EnemyMetis, "Metis_608");
                break;
            case 35280:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119735280));
                orderActorToFactory(1119738280, EnemyMetis, "Metis_609");
                break;
            case 35310:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119735310));
                orderActorToFactory(1119738310, EnemyMetis, "Metis_610");
                break;
            case 35340:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119735340));
                orderActorToFactory(1119738340, EnemyMetis, "Metis_611");
                break;
            case 35370:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119735370));
                orderActorToFactory(1119738370, EnemyMetis, "Metis_612");
                break;
            case 35400:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119735400));
                orderActorToFactory(1119738400, EnemyMetis, "Metis_613");
                break;
            case 35430:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119735430));
                orderActorToFactory(1119738430, EnemyMetis, "Metis_614");
                break;
            case 35460:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119735460));
                orderActorToFactory(1119738460, EnemyMetis, "Metis_615");
                break;
            case 35490:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119735490));
                orderActorToFactory(1119738490, EnemyMetis, "Metis_616");
                break;
            case 35520:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119735520));
                orderActorToFactory(1119738520, EnemyMetis, "Metis_617");
                break;
            case 35550:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119735550));
                orderActorToFactory(1119738550, EnemyMetis, "Metis_618");
                break;
            case 35580:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119735580));
                orderActorToFactory(1119738580, EnemyMetis, "Metis_619");
                break;
            case 35610:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119735610));
                orderActorToFactory(1119738610, EnemyMetis, "Metis_620");
                break;
            case 35640:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119735640));
                orderActorToFactory(1119738640, EnemyMetis, "Metis_621");
                break;
            case 35670:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119735670));
                orderActorToFactory(1119738670, EnemyMetis, "Metis_622");
                break;
            case 35700:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119735700));
                orderActorToFactory(1119738700, EnemyMetis, "Metis_623");
                break;
            case 35730:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119735730));
                orderActorToFactory(1119738730, EnemyMetis, "Metis_624");
                break;
            case 35760:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119735760));
                orderActorToFactory(1119738760, EnemyMetis, "Metis_625");
                break;
            case 35790:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119735790));
                orderActorToFactory(1119738790, EnemyMetis, "Metis_626");
                break;
            case 35820:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119735820));
                orderActorToFactory(1119738820, EnemyMetis, "Metis_627");
                break;
            case 35850:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119735850));
                orderActorToFactory(1119738850, EnemyMetis, "Metis_628");
                break;
            case 35880:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119735880));
                orderActorToFactory(1119738880, EnemyMetis, "Metis_629");
                break;
            case 35910:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119735910));
                orderActorToFactory(1119738910, EnemyMetis, "Metis_630");
                break;
            case 35940:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119735940));
                orderActorToFactory(1119738940, EnemyMetis, "Metis_631");
                break;
            case 35970:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119735970));
                orderActorToFactory(1119738970, EnemyMetis, "Metis_632");
                break;
            case 36000:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119736000));
                orderActorToFactory(1119739000, EnemyMetis, "Metis_633");
                break;
            case 36030:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119736030));
                orderActorToFactory(1119739030, EnemyMetis, "Metis_634");
                break;
            case 36060:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119736060));
                orderActorToFactory(1119739060, EnemyMetis, "Metis_635");
                break;
            case 36090:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119736090));
                orderActorToFactory(1119739090, EnemyMetis, "Metis_636");
                break;
            case 36120:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119736120));
                orderActorToFactory(1119739120, EnemyMetis, "Metis_637");
                break;
            case 36150:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119736150));
                orderActorToFactory(1119739150, EnemyMetis, "Metis_638");
                break;
            case 36180:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119736180));
                orderActorToFactory(1119739180, EnemyMetis, "Metis_639");
                break;
            case 36210:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119736210));
                orderActorToFactory(1119739210, EnemyMetis, "Metis_640");
                break;
            case 36240:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119736240));
                orderActorToFactory(1119739240, EnemyMetis, "Metis_641");
                break;
            case 36270:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119736270));
                orderActorToFactory(1119739270, EnemyMetis, "Metis_642");
                break;
            case 36300:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119736300));
                orderActorToFactory(1119739300, EnemyMetis, "Metis_643");
                break;
            case 36330:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119736330));
                orderActorToFactory(1119739330, EnemyMetis, "Metis_644");
                break;
            case 36360:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119736360));
                orderActorToFactory(1119739360, EnemyMetis, "Metis_645");
                break;
            case 36390:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119736390));
                orderActorToFactory(1119739390, EnemyMetis, "Metis_646");
                break;
            case 36420:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119736420));
                orderActorToFactory(1119739420, EnemyMetis, "Metis_647");
                break;
            case 36450:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119736450));
                orderActorToFactory(1119739450, EnemyMetis, "Metis_648");
                break;
            case 36480:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119736480));
                orderActorToFactory(1119739480, EnemyMetis, "Metis_649");
                break;
            case 36510:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119736510));
                orderActorToFactory(1119739510, EnemyMetis, "Metis_650");
                break;
            case 36540:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119736540));
                orderActorToFactory(1119739540, EnemyMetis, "Metis_651");
                break;
            case 36570:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119736570));
                orderActorToFactory(1119739570, EnemyMetis, "Metis_652");
                break;
            case 36600:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119736600));
                orderActorToFactory(1119739600, EnemyMetis, "Metis_653");
                break;
            case 36630:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119736630));
                orderActorToFactory(1119739630, EnemyMetis, "Metis_654");
                break;
            case 36660:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119736660));
                orderActorToFactory(1119739660, EnemyMetis, "Metis_655");
                break;
            case 36690:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119736690));
                orderActorToFactory(1119739690, EnemyMetis, "Metis_656");
                break;
            case 36720:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119736720));
                orderActorToFactory(1119739720, EnemyMetis, "Metis_657");
                break;
            case 36750:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119736750));
                orderActorToFactory(1119739750, EnemyMetis, "Metis_658");
                break;
            case 36780:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119736780));
                orderActorToFactory(1119739780, EnemyMetis, "Metis_659");
                break;
            case 36810:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119736810));
                orderActorToFactory(1119739810, EnemyMetis, "Metis_660");
                break;
            case 36840:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119736840));
                orderActorToFactory(1119739840, EnemyMetis, "Metis_661");
                break;
            case 36870:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119736870));
                orderActorToFactory(1119739870, EnemyMetis, "Metis_662");
                break;
            case 36900:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119736900));
                orderActorToFactory(1119739900, EnemyMetis, "Metis_663");
                break;
            case 36930:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119736930));
                orderActorToFactory(1119739930, EnemyMetis, "Metis_664");
                break;
            case 36960:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119736960));
                orderActorToFactory(1119739960, EnemyMetis, "Metis_665");
                break;
            case 36990:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119736990));
                orderActorToFactory(1119739990, EnemyMetis, "Metis_666");
                break;
            case 37020:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119737020));
                orderActorToFactory(1119740020, EnemyMetis, "Metis_667");
                break;
            case 37050:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119737050));
                orderActorToFactory(1119740050, EnemyMetis, "Metis_668");
                break;
            case 37080:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119737080));
                orderActorToFactory(1119740080, EnemyMetis, "Metis_669");
                break;
            case 37110:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119737110));
                orderActorToFactory(1119740110, EnemyMetis, "Metis_670");
                break;
            case 37140:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119737140));
                orderActorToFactory(1119740140, EnemyMetis, "Metis_671");
                break;
            case 37170:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119737170));
                orderActorToFactory(1119740170, EnemyMetis, "Metis_672");
                break;
            case 37200:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119737200));
                orderActorToFactory(1119740200, EnemyMetis, "Metis_673");
                break;
            case 37230:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119737230));
                orderActorToFactory(1119740230, EnemyMetis, "Metis_674");
                break;
            case 37260:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119737260));
                orderActorToFactory(1119740260, EnemyMetis, "Metis_675");
                break;
            case 37290:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119737290));
                orderActorToFactory(1119740290, EnemyMetis, "Metis_676");
                break;
            case 37320:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119737320));
                orderActorToFactory(1119740320, EnemyMetis, "Metis_677");
                break;
            case 37350:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119737350));
                orderActorToFactory(1119740350, EnemyMetis, "Metis_678");
                break;
            case 37380:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119737380));
                orderActorToFactory(1119740380, EnemyMetis, "Metis_679");
                break;
            case 37410:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119737410));
                orderActorToFactory(1119740410, EnemyMetis, "Metis_680");
                break;
            case 37440:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119737440));
                orderActorToFactory(1119740440, EnemyMetis, "Metis_681");
                break;
            case 37470:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119737470));
                orderActorToFactory(1119740470, EnemyMetis, "Metis_682");
                break;
            case 37500:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119737500));
                orderActorToFactory(1119740500, EnemyMetis, "Metis_683");
                break;
            case 37530:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119737530));
                orderActorToFactory(1119740530, EnemyMetis, "Metis_684");
                break;
            case 37560:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119737560));
                orderActorToFactory(1119740560, EnemyMetis, "Metis_685");
                break;
            case 37590:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119737590));
                orderActorToFactory(1119740590, EnemyMetis, "Metis_686");
                break;
            case 37620:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119737620));
                orderActorToFactory(1119740620, EnemyMetis, "Metis_687");
                break;
            case 37650:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119737650));
                orderActorToFactory(1119740650, EnemyMetis, "Metis_688");
                break;
            case 37680:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119737680));
                orderActorToFactory(1119740680, EnemyMetis, "Metis_689");
                break;
            case 37710:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119737710));
                orderActorToFactory(1119740710, EnemyMetis, "Metis_690");
                break;
            case 37740:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119737740));
                orderActorToFactory(1119740740, EnemyMetis, "Metis_691");
                break;
            case 37770:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119737770));
                orderActorToFactory(1119740770, EnemyMetis, "Metis_692");
                break;
            case 37800:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119737800));
                orderActorToFactory(1119740800, EnemyMetis, "Metis_693");
                break;
            case 37830:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119737830));
                orderActorToFactory(1119740830, EnemyMetis, "Metis_694");
                break;
            case 37860:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119737860));
                orderActorToFactory(1119740860, EnemyMetis, "Metis_695");
                break;
            case 37890:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119737890));
                orderActorToFactory(1119740890, EnemyMetis, "Metis_696");
                break;
            case 37920:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119737920));
                orderActorToFactory(1119740920, EnemyMetis, "Metis_697");
                break;
            case 37950:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119737950));
                orderActorToFactory(1119740950, EnemyMetis, "Metis_698");
                break;
            case 37980:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119737980));
                orderActorToFactory(1119740980, EnemyMetis, "Metis_699");
                break;
            case 38010:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119738010));
                orderActorToFactory(1119741010, EnemyMetis, "Metis_700");
                break;
            case 38040:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119738040));
                orderActorToFactory(1119741040, EnemyMetis, "Metis_701");
                break;
            case 38070:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119738070));
                orderActorToFactory(1119741070, EnemyMetis, "Metis_702");
                break;
            case 38100:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119738100));
                orderActorToFactory(1119741100, EnemyMetis, "Metis_703");
                break;
            case 38130:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119738130));
                orderActorToFactory(1119741130, EnemyMetis, "Metis_704");
                break;
            case 38160:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119738160));
                orderActorToFactory(1119741160, EnemyMetis, "Metis_705");
                break;
            case 38190:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119738190));
                orderActorToFactory(1119741190, EnemyMetis, "Metis_706");
                break;
            case 38220:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119738220));
                orderActorToFactory(1119741220, EnemyMetis, "Metis_707");
                break;
            case 38250:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119738250));
                orderActorToFactory(1119741250, EnemyMetis, "Metis_708");
                break;
            case 38280:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119738280));
                orderActorToFactory(1119741280, EnemyMetis, "Metis_709");
                break;
            case 38310:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119738310));
                orderActorToFactory(1119741310, EnemyMetis, "Metis_710");
                break;
            case 38340:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119738340));
                orderActorToFactory(1119741340, EnemyMetis, "Metis_711");
                break;
            case 38370:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119738370));
                orderActorToFactory(1119741370, EnemyMetis, "Metis_712");
                break;
            case 38400:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119738400));
                orderActorToFactory(1119741400, EnemyMetis, "Metis_713");
                break;
            case 38430:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119738430));
                orderActorToFactory(1119741430, EnemyMetis, "Metis_714");
                break;
            case 38460:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119738460));
                orderActorToFactory(1119741460, EnemyMetis, "Metis_715");
                break;
            case 38490:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119738490));
                orderActorToFactory(1119741490, EnemyMetis, "Metis_716");
                break;
            case 38520:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119738520));
                orderActorToFactory(1119741520, EnemyMetis, "Metis_717");
                break;
            case 38550:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119738550));
                orderActorToFactory(1119741550, EnemyMetis, "Metis_718");
                break;
            case 38580:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119738580));
                orderActorToFactory(1119741580, EnemyMetis, "Metis_719");
                break;
            case 38610:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119738610));
                orderActorToFactory(1119741610, EnemyMetis, "Metis_720");
                break;
            case 38640:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119738640));
                orderActorToFactory(1119741640, EnemyMetis, "Metis_721");
                break;
            case 38670:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119738670));
                orderActorToFactory(1119741670, EnemyMetis, "Metis_722");
                break;
            case 38700:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119738700));
                orderActorToFactory(1119741700, EnemyMetis, "Metis_723");
                break;
            case 38730:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119738730));
                orderActorToFactory(1119741730, EnemyMetis, "Metis_724");
                break;
            case 38760:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119738760));
                orderActorToFactory(1119741760, EnemyMetis, "Metis_725");
                break;
            case 38790:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119738790));
                orderActorToFactory(1119741790, EnemyMetis, "Metis_726");
                break;
            case 38820:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119738820));
                orderActorToFactory(1119741820, EnemyMetis, "Metis_727");
                break;
            case 38850:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119738850));
                orderActorToFactory(1119741850, EnemyMetis, "Metis_728");
                break;
            case 38880:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119738880));
                orderActorToFactory(1119741880, EnemyMetis, "Metis_729");
                break;
            case 38910:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119738910));
                orderActorToFactory(1119741910, EnemyMetis, "Metis_730");
                break;
            case 38940:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119738940));
                orderActorToFactory(1119741940, EnemyMetis, "Metis_731");
                break;
            case 38970:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119738970));
                orderActorToFactory(1119741970, EnemyMetis, "Metis_732");
                break;
            case 39000:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119739000));
                orderActorToFactory(1119742000, EnemyMetis, "Metis_733");
                break;
            case 39030:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119739030));
                orderActorToFactory(1119742030, EnemyMetis, "Metis_734");
                break;
            case 39060:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119739060));
                orderActorToFactory(1119742060, EnemyMetis, "Metis_735");
                break;
            case 39090:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119739090));
                orderActorToFactory(1119742090, EnemyMetis, "Metis_736");
                break;
            case 39120:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119739120));
                orderActorToFactory(1119742120, EnemyMetis, "Metis_737");
                break;
            case 39150:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119739150));
                orderActorToFactory(1119742150, EnemyMetis, "Metis_738");
                break;
            case 39180:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119739180));
                orderActorToFactory(1119742180, EnemyMetis, "Metis_739");
                break;
            case 39210:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119739210));
                orderActorToFactory(1119742210, EnemyMetis, "Metis_740");
                break;
            case 39240:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119739240));
                orderActorToFactory(1119742240, EnemyMetis, "Metis_741");
                break;
            case 39270:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119739270));
                orderActorToFactory(1119742270, EnemyMetis, "Metis_742");
                break;
            case 39300:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119739300));
                orderActorToFactory(1119742300, EnemyMetis, "Metis_743");
                break;
            case 39330:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119739330));
                orderActorToFactory(1119742330, EnemyMetis, "Metis_744");
                break;
            case 39360:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119739360));
                orderActorToFactory(1119742360, EnemyMetis, "Metis_745");
                break;
            case 39390:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119739390));
                orderActorToFactory(1119742390, EnemyMetis, "Metis_746");
                break;
            case 39420:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119739420));
                orderActorToFactory(1119742420, EnemyMetis, "Metis_747");
                break;
            case 39450:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119739450));
                orderActorToFactory(1119742450, EnemyMetis, "Metis_748");
                break;
            case 39480:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119739480));
                orderActorToFactory(1119742480, EnemyMetis, "Metis_749");
                break;
            case 39510:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119739510));
                orderActorToFactory(1119742510, EnemyMetis, "Metis_750");
                break;
            case 39540:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119739540));
                orderActorToFactory(1119742540, EnemyMetis, "Metis_751");
                break;
            case 39570:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119739570));
                orderActorToFactory(1119742570, EnemyMetis, "Metis_752");
                break;
            case 39600:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119739600));
                orderActorToFactory(1119742600, EnemyMetis, "Metis_753");
                break;
            case 39630:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119739630));
                orderActorToFactory(1119742630, EnemyMetis, "Metis_754");
                break;
            case 39660:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119739660));
                orderActorToFactory(1119742660, EnemyMetis, "Metis_755");
                break;
            case 39690:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119739690));
                orderActorToFactory(1119742690, EnemyMetis, "Metis_756");
                break;
            case 39720:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119739720));
                orderActorToFactory(1119742720, EnemyMetis, "Metis_757");
                break;
            case 39750:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119739750));
                orderActorToFactory(1119742750, EnemyMetis, "Metis_758");
                break;
            case 39780:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119739780));
                orderActorToFactory(1119742780, EnemyMetis, "Metis_759");
                break;
            case 39810:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119739810));
                orderActorToFactory(1119742810, EnemyMetis, "Metis_760");
                break;
            case 39840:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119739840));
                orderActorToFactory(1119742840, EnemyMetis, "Metis_761");
                break;
            case 39870:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119739870));
                orderActorToFactory(1119742870, EnemyMetis, "Metis_762");
                break;
            case 39900:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119739900));
                orderActorToFactory(1119742900, EnemyMetis, "Metis_763");
                break;
            case 39930:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119739930));
                orderActorToFactory(1119742930, EnemyMetis, "Metis_764");
                break;
            case 39960:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119739960));
                orderActorToFactory(1119742960, EnemyMetis, "Metis_765");
                break;
            case 39990:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119739990));
                orderActorToFactory(1119742990, EnemyMetis, "Metis_766");
                break;
            case 40020:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119740020));
                orderActorToFactory(1119743020, EnemyMetis, "Metis_767");
                break;
            case 40050:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119740050));
                orderActorToFactory(1119743050, EnemyMetis, "Metis_768");
                break;
            case 40080:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119740080));
                orderActorToFactory(1119743080, EnemyMetis, "Metis_769");
                break;
            case 40110:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119740110));
                orderActorToFactory(1119743110, EnemyMetis, "Metis_770");
                break;
            case 40140:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119740140));
                orderActorToFactory(1119743140, EnemyMetis, "Metis_771");
                break;
            case 40170:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119740170));
                orderActorToFactory(1119743170, EnemyMetis, "Metis_772");
                break;
            case 40200:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119740200));
                orderActorToFactory(1119743200, EnemyMetis, "Metis_773");
                break;
            case 40230:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119740230));
                orderActorToFactory(1119743230, EnemyMetis, "Metis_774");
                break;
            case 40260:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119740260));
                orderActorToFactory(1119743260, EnemyMetis, "Metis_775");
                break;
            case 40290:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119740290));
                orderActorToFactory(1119743290, EnemyMetis, "Metis_776");
                break;
            case 40320:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119740320));
                orderActorToFactory(1119743320, EnemyMetis, "Metis_777");
                break;
            case 40350:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119740350));
                orderActorToFactory(1119743350, EnemyMetis, "Metis_778");
                break;
            case 40380:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119740380));
                orderActorToFactory(1119743380, EnemyMetis, "Metis_779");
                break;
            case 40410:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119740410));
                orderActorToFactory(1119743410, EnemyMetis, "Metis_780");
                break;
            case 40440:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119740440));
                orderActorToFactory(1119743440, EnemyMetis, "Metis_781");
                break;
            case 40470:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119740470));
                orderActorToFactory(1119743470, EnemyMetis, "Metis_782");
                break;
            case 40500:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119740500));
                orderActorToFactory(1119743500, EnemyMetis, "Metis_783");
                break;
            case 40530:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119740530));
                orderActorToFactory(1119743530, EnemyMetis, "Metis_784");
                break;
            case 40560:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119740560));
                orderActorToFactory(1119743560, EnemyMetis, "Metis_785");
                break;
            case 40590:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119740590));
                orderActorToFactory(1119743590, EnemyMetis, "Metis_786");
                break;
            case 40620:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119740620));
                orderActorToFactory(1119743620, EnemyMetis, "Metis_787");
                break;
            case 40650:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119740650));
                orderActorToFactory(1119743650, EnemyMetis, "Metis_788");
                break;
            case 40680:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119740680));
                orderActorToFactory(1119743680, EnemyMetis, "Metis_789");
                break;
            case 40710:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119740710));
                orderActorToFactory(1119743710, EnemyMetis, "Metis_790");
                break;
            case 40740:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119740740));
                orderActorToFactory(1119743740, EnemyMetis, "Metis_791");
                break;
            case 40770:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119740770));
                orderActorToFactory(1119743770, EnemyMetis, "Metis_792");
                break;
            case 40800:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119740800));
                orderActorToFactory(1119743800, EnemyMetis, "Metis_793");
                break;
            case 40830:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119740830));
                orderActorToFactory(1119743830, EnemyMetis, "Metis_794");
                break;
            case 40860:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119740860));
                orderActorToFactory(1119743860, EnemyMetis, "Metis_795");
                break;
            case 40890:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119740890));
                orderActorToFactory(1119743890, EnemyMetis, "Metis_796");
                break;
            case 40920:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119740920));
                orderActorToFactory(1119743920, EnemyMetis, "Metis_797");
                break;
            case 40950:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119740950));
                orderActorToFactory(1119743950, EnemyMetis, "Metis_798");
                break;
            case 40980:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119740980));
                orderActorToFactory(1119743980, EnemyMetis, "Metis_799");
                break;
            case 41010:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119741010));
                orderActorToFactory(1119744010, EnemyMetis, "Metis_800");
                break;
            case 41040:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119741040));
                orderActorToFactory(1119744040, EnemyMetis, "Metis_801");
                break;
            case 41070:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119741070));
                orderActorToFactory(1119744070, EnemyMetis, "Metis_802");
                break;
            case 41100:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119741100));
                orderActorToFactory(1119744100, EnemyMetis, "Metis_803");
                break;
            case 41130:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119741130));
                orderActorToFactory(1119744130, EnemyMetis, "Metis_804");
                break;
            case 41160:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119741160));
                orderActorToFactory(1119744160, EnemyMetis, "Metis_805");
                break;
            case 41190:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119741190));
                orderActorToFactory(1119744190, EnemyMetis, "Metis_806");
                break;
            case 41220:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119741220));
                orderActorToFactory(1119744220, EnemyMetis, "Metis_807");
                break;
            case 41250:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119741250));
                orderActorToFactory(1119744250, EnemyMetis, "Metis_808");
                break;
            case 41280:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119741280));
                orderActorToFactory(1119744280, EnemyMetis, "Metis_809");
                break;
            case 41310:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119741310));
                orderActorToFactory(1119744310, EnemyMetis, "Metis_810");
                break;
            case 41340:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119741340));
                orderActorToFactory(1119744340, EnemyMetis, "Metis_811");
                break;
            case 41370:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119741370));
                orderActorToFactory(1119744370, EnemyMetis, "Metis_812");
                break;
            case 41400:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119741400));
                orderActorToFactory(1119744400, EnemyMetis, "Metis_813");
                break;
            case 41430:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119741430));
                orderActorToFactory(1119744430, EnemyMetis, "Metis_814");
                break;
            case 41460:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119741460));
                orderActorToFactory(1119744460, EnemyMetis, "Metis_815");
                break;
            case 41490:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119741490));
                orderActorToFactory(1119744490, EnemyMetis, "Metis_816");
                break;
            case 41520:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119741520));
                orderActorToFactory(1119744520, EnemyMetis, "Metis_817");
                break;
            case 41550:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119741550));
                orderActorToFactory(1119744550, EnemyMetis, "Metis_818");
                break;
            case 41580:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119741580));
                orderActorToFactory(1119744580, EnemyMetis, "Metis_819");
                break;
            case 41610:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119741610));
                orderActorToFactory(1119744610, EnemyMetis, "Metis_820");
                break;
            case 41640:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119741640));
                orderActorToFactory(1119744640, EnemyMetis, "Metis_821");
                break;
            case 41670:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119741670));
                orderActorToFactory(1119744670, EnemyMetis, "Metis_822");
                break;
            case 41700:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119741700));
                orderActorToFactory(1119744700, EnemyMetis, "Metis_823");
                break;
            case 41730:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119741730));
                orderActorToFactory(1119744730, EnemyMetis, "Metis_824");
                break;
            case 41760:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119741760));
                orderActorToFactory(1119744760, EnemyMetis, "Metis_825");
                break;
            case 41790:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119741790));
                orderActorToFactory(1119744790, EnemyMetis, "Metis_826");
                break;
            case 41820:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119741820));
                orderActorToFactory(1119744820, EnemyMetis, "Metis_827");
                break;
            case 41850:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119741850));
                orderActorToFactory(1119744850, EnemyMetis, "Metis_828");
                break;
            case 41880:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119741880));
                orderActorToFactory(1119744880, EnemyMetis, "Metis_829");
                break;
            case 41910:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119741910));
                orderActorToFactory(1119744910, EnemyMetis, "Metis_830");
                break;
            case 41940:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119741940));
                orderActorToFactory(1119744940, EnemyMetis, "Metis_831");
                break;
            case 41970:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119741970));
                orderActorToFactory(1119744970, EnemyMetis, "Metis_832");
                break;
            case 42000:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119742000));
                orderActorToFactory(1119745000, EnemyMetis, "Metis_833");
                break;
            case 42030:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119742030));
                orderActorToFactory(1119745030, EnemyMetis, "Metis_834");
                break;
            case 42060:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119742060));
                orderActorToFactory(1119745060, EnemyMetis, "Metis_835");
                break;
            case 42090:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119742090));
                orderActorToFactory(1119745090, EnemyMetis, "Metis_836");
                break;
            case 42120:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119742120));
                orderActorToFactory(1119745120, EnemyMetis, "Metis_837");
                break;
            case 42150:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119742150));
                orderActorToFactory(1119745150, EnemyMetis, "Metis_838");
                break;
            case 42180:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119742180));
                orderActorToFactory(1119745180, EnemyMetis, "Metis_839");
                break;
            case 42210:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119742210));
                orderActorToFactory(1119745210, EnemyMetis, "Metis_840");
                break;
            case 42240:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119742240));
                orderActorToFactory(1119745240, EnemyMetis, "Metis_841");
                break;
            case 42270:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119742270));
                orderActorToFactory(1119745270, EnemyMetis, "Metis_842");
                break;
            case 42300:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119742300));
                orderActorToFactory(1119745300, EnemyMetis, "Metis_843");
                break;
            case 42330:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119742330));
                orderActorToFactory(1119745330, EnemyMetis, "Metis_844");
                break;
            case 42360:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119742360));
                orderActorToFactory(1119745360, EnemyMetis, "Metis_845");
                break;
            case 42390:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119742390));
                orderActorToFactory(1119745390, EnemyMetis, "Metis_846");
                break;
            case 42420:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119742420));
                orderActorToFactory(1119745420, EnemyMetis, "Metis_847");
                break;
            case 42450:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119742450));
                orderActorToFactory(1119745450, EnemyMetis, "Metis_848");
                break;
            case 42480:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119742480));
                orderActorToFactory(1119745480, EnemyMetis, "Metis_849");
                break;
            case 42510:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119742510));
                orderActorToFactory(1119745510, EnemyMetis, "Metis_850");
                break;
            case 42540:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119742540));
                orderActorToFactory(1119745540, EnemyMetis, "Metis_851");
                break;
            case 42570:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119742570));
                orderActorToFactory(1119745570, EnemyMetis, "Metis_852");
                break;
            case 42600:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119742600));
                orderActorToFactory(1119745600, EnemyMetis, "Metis_853");
                break;
            case 42630:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119742630));
                orderActorToFactory(1119745630, EnemyMetis, "Metis_854");
                break;
            case 42660:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119742660));
                orderActorToFactory(1119745660, EnemyMetis, "Metis_855");
                break;
            case 42690:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119742690));
                orderActorToFactory(1119745690, EnemyMetis, "Metis_856");
                break;
            case 42720:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119742720));
                orderActorToFactory(1119745720, EnemyMetis, "Metis_857");
                break;
            case 42750:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119742750));
                orderActorToFactory(1119745750, EnemyMetis, "Metis_858");
                break;
            case 42780:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119742780));
                orderActorToFactory(1119745780, EnemyMetis, "Metis_859");
                break;
            case 42810:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119742810));
                orderActorToFactory(1119745810, EnemyMetis, "Metis_860");
                break;
            case 42840:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119742840));
                orderActorToFactory(1119745840, EnemyMetis, "Metis_861");
                break;
            case 42870:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119742870));
                orderActorToFactory(1119745870, EnemyMetis, "Metis_862");
                break;
            case 42900:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119742900));
                orderActorToFactory(1119745900, EnemyMetis, "Metis_863");
                break;
            case 42930:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119742930));
                orderActorToFactory(1119745930, EnemyMetis, "Metis_864");
                break;
            case 42960:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119742960));
                orderActorToFactory(1119745960, EnemyMetis, "Metis_865");
                break;
            case 42990:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119742990));
                orderActorToFactory(1119745990, EnemyMetis, "Metis_866");
                break;
            case 43020:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119743020));
                orderActorToFactory(1119746020, EnemyMetis, "Metis_867");
                break;
            case 43050:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119743050));
                orderActorToFactory(1119746050, EnemyMetis, "Metis_868");
                break;
            case 43080:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119743080));
                orderActorToFactory(1119746080, EnemyMetis, "Metis_869");
                break;
            case 43110:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119743110));
                orderActorToFactory(1119746110, EnemyMetis, "Metis_870");
                break;
            case 43140:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119743140));
                orderActorToFactory(1119746140, EnemyMetis, "Metis_871");
                break;
            case 43170:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119743170));
                orderActorToFactory(1119746170, EnemyMetis, "Metis_872");
                break;
            case 43200:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119743200));
                orderActorToFactory(1119746200, EnemyMetis, "Metis_873");
                break;
            case 43230:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119743230));
                orderActorToFactory(1119746230, EnemyMetis, "Metis_874");
                break;
            case 43260:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119743260));
                orderActorToFactory(1119746260, EnemyMetis, "Metis_875");
                break;
            case 43290:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119743290));
                orderActorToFactory(1119746290, EnemyMetis, "Metis_876");
                break;
            case 43320:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119743320));
                orderActorToFactory(1119746320, EnemyMetis, "Metis_877");
                break;
            case 43350:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119743350));
                orderActorToFactory(1119746350, EnemyMetis, "Metis_878");
                break;
            case 43380:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119743380));
                orderActorToFactory(1119746380, EnemyMetis, "Metis_879");
                break;
            case 43410:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119743410));
                orderActorToFactory(1119746410, EnemyMetis, "Metis_880");
                break;
            case 43440:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119743440));
                orderActorToFactory(1119746440, EnemyMetis, "Metis_881");
                break;
            case 43470:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119743470));
                orderActorToFactory(1119746470, EnemyMetis, "Metis_882");
                break;
            case 43500:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119743500));
                orderActorToFactory(1119746500, EnemyMetis, "Metis_883");
                break;
            case 43530:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119743530));
                orderActorToFactory(1119746530, EnemyMetis, "Metis_884");
                break;
            case 43560:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119743560));
                orderActorToFactory(1119746560, EnemyMetis, "Metis_885");
                break;
            case 43590:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119743590));
                orderActorToFactory(1119746590, EnemyMetis, "Metis_886");
                break;
            case 43620:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119743620));
                orderActorToFactory(1119746620, EnemyMetis, "Metis_887");
                break;
            case 43650:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119743650));
                orderActorToFactory(1119746650, EnemyMetis, "Metis_888");
                break;
            case 43680:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119743680));
                orderActorToFactory(1119746680, EnemyMetis, "Metis_889");
                break;
            case 43710:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119743710));
                orderActorToFactory(1119746710, EnemyMetis, "Metis_890");
                break;
            case 43740:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119743740));
                orderActorToFactory(1119746740, EnemyMetis, "Metis_891");
                break;
            case 43770:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119743770));
                orderActorToFactory(1119746770, EnemyMetis, "Metis_892");
                break;
            case 43800:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119743800));
                orderActorToFactory(1119746800, EnemyMetis, "Metis_893");
                break;
            case 43830:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119743830));
                orderActorToFactory(1119746830, EnemyMetis, "Metis_894");
                break;
            case 43860:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119743860));
                orderActorToFactory(1119746860, EnemyMetis, "Metis_895");
                break;
            case 43890:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119743890));
                orderActorToFactory(1119746890, EnemyMetis, "Metis_896");
                break;
            case 43920:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119743920));
                orderActorToFactory(1119746920, EnemyMetis, "Metis_897");
                break;
            case 43950:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119743950));
                orderActorToFactory(1119746950, EnemyMetis, "Metis_898");
                break;
            case 43980:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119743980));
                orderActorToFactory(1119746980, EnemyMetis, "Metis_899");
                break;
            case 44010:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119744010));
                orderActorToFactory(1119747010, EnemyMetis, "Metis_900");
                break;
            case 44040:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119744040));
                orderActorToFactory(1119747040, EnemyMetis, "Metis_901");
                break;
            case 44070:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119744070));
                orderActorToFactory(1119747070, EnemyMetis, "Metis_902");
                break;
            case 44100:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119744100));
                orderActorToFactory(1119747100, EnemyMetis, "Metis_903");
                break;
            case 44130:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119744130));
                orderActorToFactory(1119747130, EnemyMetis, "Metis_904");
                break;
            case 44160:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119744160));
                orderActorToFactory(1119747160, EnemyMetis, "Metis_905");
                break;
            case 44190:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119744190));
                orderActorToFactory(1119747190, EnemyMetis, "Metis_906");
                break;
            case 44220:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119744220));
                orderActorToFactory(1119747220, EnemyMetis, "Metis_907");
                break;
            case 44250:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119744250));
                orderActorToFactory(1119747250, EnemyMetis, "Metis_908");
                break;
            case 44280:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119744280));
                orderActorToFactory(1119747280, EnemyMetis, "Metis_909");
                break;
            case 44310:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119744310));
                orderActorToFactory(1119747310, EnemyMetis, "Metis_910");
                break;
            case 44340:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119744340));
                orderActorToFactory(1119747340, EnemyMetis, "Metis_911");
                break;
            case 44370:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119744370));
                orderActorToFactory(1119747370, EnemyMetis, "Metis_912");
                break;
            case 44400:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119744400));
                orderActorToFactory(1119747400, EnemyMetis, "Metis_913");
                break;
            case 44430:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119744430));
                orderActorToFactory(1119747430, EnemyMetis, "Metis_914");
                break;
            case 44460:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119744460));
                orderActorToFactory(1119747460, EnemyMetis, "Metis_915");
                break;
            case 44490:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119744490));
                orderActorToFactory(1119747490, EnemyMetis, "Metis_916");
                break;
            case 44520:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119744520));
                orderActorToFactory(1119747520, EnemyMetis, "Metis_917");
                break;
            case 44550:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119744550));
                orderActorToFactory(1119747550, EnemyMetis, "Metis_918");
                break;
            case 44580:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119744580));
                orderActorToFactory(1119747580, EnemyMetis, "Metis_919");
                break;
            case 44610:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119744610));
                orderActorToFactory(1119747610, EnemyMetis, "Metis_920");
                break;
            case 44640:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119744640));
                orderActorToFactory(1119747640, EnemyMetis, "Metis_921");
                break;
            case 44670:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119744670));
                orderActorToFactory(1119747670, EnemyMetis, "Metis_922");
                break;
            case 44700:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119744700));
                orderActorToFactory(1119747700, EnemyMetis, "Metis_923");
                break;
            case 44730:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119744730));
                orderActorToFactory(1119747730, EnemyMetis, "Metis_924");
                break;
            case 44760:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119744760));
                orderActorToFactory(1119747760, EnemyMetis, "Metis_925");
                break;
            case 44790:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119744790));
                orderActorToFactory(1119747790, EnemyMetis, "Metis_926");
                break;
            case 44820:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119744820));
                orderActorToFactory(1119747820, EnemyMetis, "Metis_927");
                break;
            case 44850:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119744850));
                orderActorToFactory(1119747850, EnemyMetis, "Metis_928");
                break;
            case 44880:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119744880));
                orderActorToFactory(1119747880, EnemyMetis, "Metis_929");
                break;
            case 44910:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119744910));
                orderActorToFactory(1119747910, EnemyMetis, "Metis_930");
                break;
            case 44940:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119744940));
                orderActorToFactory(1119747940, EnemyMetis, "Metis_931");
                break;
            case 44970:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119744970));
                orderActorToFactory(1119747970, EnemyMetis, "Metis_932");
                break;
            case 45000:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119745000));
                orderActorToFactory(1119748000, EnemyMetis, "Metis_933");
                break;
            case 45030:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119745030));
                orderActorToFactory(1119748030, EnemyMetis, "Metis_934");
                break;
            case 45060:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119745060));
                orderActorToFactory(1119748060, EnemyMetis, "Metis_935");
                break;
            case 45090:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119745090));
                orderActorToFactory(1119748090, EnemyMetis, "Metis_936");
                break;
            case 45120:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119745120));
                orderActorToFactory(1119748120, EnemyMetis, "Metis_937");
                break;
            case 45150:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119745150));
                orderActorToFactory(1119748150, EnemyMetis, "Metis_938");
                break;
            case 45180:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119745180));
                orderActorToFactory(1119748180, EnemyMetis, "Metis_939");
                break;
            case 45210:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119745210));
                orderActorToFactory(1119748210, EnemyMetis, "Metis_940");
                break;
            case 45240:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119745240));
                orderActorToFactory(1119748240, EnemyMetis, "Metis_941");
                break;
            case 45270:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119745270));
                orderActorToFactory(1119748270, EnemyMetis, "Metis_942");
                break;
            case 45300:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119745300));
                orderActorToFactory(1119748300, EnemyMetis, "Metis_943");
                break;
            case 45330:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119745330));
                orderActorToFactory(1119748330, EnemyMetis, "Metis_944");
                break;
            case 45360:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119745360));
                orderActorToFactory(1119748360, EnemyMetis, "Metis_945");
                break;
            case 45390:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119745390));
                orderActorToFactory(1119748390, EnemyMetis, "Metis_946");
                break;
            case 45420:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119745420));
                orderActorToFactory(1119748420, EnemyMetis, "Metis_947");
                break;
            case 45450:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119745450));
                orderActorToFactory(1119748450, EnemyMetis, "Metis_948");
                break;
            case 45480:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119745480));
                orderActorToFactory(1119748480, EnemyMetis, "Metis_949");
                break;
            case 45510:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119745510));
                orderActorToFactory(1119748510, EnemyMetis, "Metis_950");
                break;
            case 45540:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119745540));
                orderActorToFactory(1119748540, EnemyMetis, "Metis_951");
                break;
            case 45570:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119745570));
                orderActorToFactory(1119748570, EnemyMetis, "Metis_952");
                break;
            case 45600:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119745600));
                orderActorToFactory(1119748600, EnemyMetis, "Metis_953");
                break;
            case 45630:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119745630));
                orderActorToFactory(1119748630, EnemyMetis, "Metis_954");
                break;
            case 45660:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119745660));
                orderActorToFactory(1119748660, EnemyMetis, "Metis_955");
                break;
            case 45690:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119745690));
                orderActorToFactory(1119748690, EnemyMetis, "Metis_956");
                break;
            case 45720:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119745720));
                orderActorToFactory(1119748720, EnemyMetis, "Metis_957");
                break;
            case 45750:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119745750));
                orderActorToFactory(1119748750, EnemyMetis, "Metis_958");
                break;
            case 45780:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119745780));
                orderActorToFactory(1119748780, EnemyMetis, "Metis_959");
                break;
            case 45810:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119745810));
                orderActorToFactory(1119748810, EnemyMetis, "Metis_960");
                break;
            case 45840:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119745840));
                orderActorToFactory(1119748840, EnemyMetis, "Metis_961");
                break;
            case 45870:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119745870));
                orderActorToFactory(1119748870, EnemyMetis, "Metis_962");
                break;
            case 45900:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119745900));
                orderActorToFactory(1119748900, EnemyMetis, "Metis_963");
                break;
            case 45930:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119745930));
                orderActorToFactory(1119748930, EnemyMetis, "Metis_964");
                break;
            case 45960:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119745960));
                orderActorToFactory(1119748960, EnemyMetis, "Metis_965");
                break;
            case 45990:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119745990));
                orderActorToFactory(1119748990, EnemyMetis, "Metis_966");
                break;
            case 46020:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119746020));
                orderActorToFactory(1119749020, EnemyMetis, "Metis_967");
                break;
            case 46050:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119746050));
                orderActorToFactory(1119749050, EnemyMetis, "Metis_968");
                break;
            case 46080:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119746080));
                orderActorToFactory(1119749080, EnemyMetis, "Metis_969");
                break;
            case 46110:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119746110));
                orderActorToFactory(1119749110, EnemyMetis, "Metis_970");
                break;
            case 46140:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119746140));
                orderActorToFactory(1119749140, EnemyMetis, "Metis_971");
                break;
            case 46170:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119746170));
                orderActorToFactory(1119749170, EnemyMetis, "Metis_972");
                break;
            case 46200:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119746200));
                orderActorToFactory(1119749200, EnemyMetis, "Metis_973");
                break;
            case 46230:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119746230));
                orderActorToFactory(1119749230, EnemyMetis, "Metis_974");
                break;
            case 46260:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119746260));
                orderActorToFactory(1119749260, EnemyMetis, "Metis_975");
                break;
            case 46290:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119746290));
                orderActorToFactory(1119749290, EnemyMetis, "Metis_976");
                break;
            case 46320:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119746320));
                orderActorToFactory(1119749320, EnemyMetis, "Metis_977");
                break;
            case 46350:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119746350));
                orderActorToFactory(1119749350, EnemyMetis, "Metis_978");
                break;
            case 46380:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119746380));
                orderActorToFactory(1119749380, EnemyMetis, "Metis_979");
                break;
            case 46410:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119746410));
                orderActorToFactory(1119749410, EnemyMetis, "Metis_980");
                break;
            case 46440:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119746440));
                orderActorToFactory(1119749440, EnemyMetis, "Metis_981");
                break;
            case 46470:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119746470));
                orderActorToFactory(1119749470, EnemyMetis, "Metis_982");
                break;
            case 46500:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119746500));
                orderActorToFactory(1119749500, EnemyMetis, "Metis_983");
                break;
            case 46530:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119746530));
                orderActorToFactory(1119749530, EnemyMetis, "Metis_984");
                break;
            case 46560:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119746560));
                orderActorToFactory(1119749560, EnemyMetis, "Metis_985");
                break;
            case 46590:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119746590));
                orderActorToFactory(1119749590, EnemyMetis, "Metis_986");
                break;
            case 46620:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119746620));
                orderActorToFactory(1119749620, EnemyMetis, "Metis_987");
                break;
            case 46650:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119746650));
                orderActorToFactory(1119749650, EnemyMetis, "Metis_988");
                break;
            case 46680:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119746680));
                orderActorToFactory(1119749680, EnemyMetis, "Metis_989");
                break;
            case 46710:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119746710));
                orderActorToFactory(1119749710, EnemyMetis, "Metis_990");
                break;
            case 46740:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119746740));
                orderActorToFactory(1119749740, EnemyMetis, "Metis_991");
                break;
            case 46770:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119746770));
                orderActorToFactory(1119749770, EnemyMetis, "Metis_992");
                break;
            case 46800:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119746800));
                orderActorToFactory(1119749800, EnemyMetis, "Metis_993");
                break;
            case 46830:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119746830));
                orderActorToFactory(1119749830, EnemyMetis, "Metis_994");
                break;
            case 46860:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119746860));
                orderActorToFactory(1119749860, EnemyMetis, "Metis_995");
                break;
            case 46890:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119746890));
                orderActorToFactory(1119749890, EnemyMetis, "Metis_996");
                break;
            case 46920:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119746920));
                orderActorToFactory(1119749920, EnemyMetis, "Metis_997");
                break;
            case 46950:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119746950));
                orderActorToFactory(1119749950, EnemyMetis, "Metis_998");
                break;
            case 46980:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119746980));
                orderActorToFactory(1119749980, EnemyMetis, "Metis_999");
                break;
            case 47010:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119747010));
                orderActorToFactory(1119750010, EnemyMetis, "Metis_1000");
                break;
            case 47040:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119747040));
                orderActorToFactory(1119750040, EnemyMetis, "Metis_1001");
                break;
            case 47070:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119747070));
                orderActorToFactory(1119750070, EnemyMetis, "Metis_1002");
                break;
            case 47100:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119747100));
                orderActorToFactory(1119750100, EnemyMetis, "Metis_1003");
                break;
            case 47130:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119747130));
                orderActorToFactory(1119750130, EnemyMetis, "Metis_1004");
                break;
            case 47160:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119747160));
                orderActorToFactory(1119750160, EnemyMetis, "Metis_1005");
                break;
            case 47190:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119747190));
                orderActorToFactory(1119750190, EnemyMetis, "Metis_1006");
                break;
            case 47220:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119747220));
                orderActorToFactory(1119750220, EnemyMetis, "Metis_1007");
                break;
            case 47250:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119747250));
                orderActorToFactory(1119750250, EnemyMetis, "Metis_1008");
                break;
            case 47280:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119747280));
                orderActorToFactory(1119750280, EnemyMetis, "Metis_1009");
                break;
            case 47310:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119747310));
                orderActorToFactory(1119750310, EnemyMetis, "Metis_1010");
                break;
            case 47340:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119747340));
                orderActorToFactory(1119750340, EnemyMetis, "Metis_1011");
                break;
            case 47370:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119747370));
                orderActorToFactory(1119750370, EnemyMetis, "Metis_1012");
                break;
            case 47400:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119747400));
                orderActorToFactory(1119750400, EnemyMetis, "Metis_1013");
                break;
            case 47430:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119747430));
                orderActorToFactory(1119750430, EnemyMetis, "Metis_1014");
                break;
            case 47460:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119747460));
                orderActorToFactory(1119750460, EnemyMetis, "Metis_1015");
                break;
            case 47490:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119747490));
                orderActorToFactory(1119750490, EnemyMetis, "Metis_1016");
                break;
            case 47520:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119747520));
                orderActorToFactory(1119750520, EnemyMetis, "Metis_1017");
                break;
            case 47550:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119747550));
                orderActorToFactory(1119750550, EnemyMetis, "Metis_1018");
                break;
            case 47580:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119747580));
                orderActorToFactory(1119750580, EnemyMetis, "Metis_1019");
                break;
            case 47610:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119747610));
                orderActorToFactory(1119750610, EnemyMetis, "Metis_1020");
                break;
            case 47640:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119747640));
                orderActorToFactory(1119750640, EnemyMetis, "Metis_1021");
                break;
            case 47670:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119747670));
                orderActorToFactory(1119750670, EnemyMetis, "Metis_1022");
                break;
            case 47700:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119747700));
                orderActorToFactory(1119750700, EnemyMetis, "Metis_1023");
                break;
            case 47730:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119747730));
                orderActorToFactory(1119750730, EnemyMetis, "Metis_1024");
                break;
            case 47760:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119747760));
                orderActorToFactory(1119750760, EnemyMetis, "Metis_1025");
                break;
            case 47790:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119747790));
                orderActorToFactory(1119750790, EnemyMetis, "Metis_1026");
                break;
            case 47820:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119747820));
                orderActorToFactory(1119750820, EnemyMetis, "Metis_1027");
                break;
            case 47850:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119747850));
                orderActorToFactory(1119750850, EnemyMetis, "Metis_1028");
                break;
            case 47880:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119747880));
                orderActorToFactory(1119750880, EnemyMetis, "Metis_1029");
                break;
            case 47910:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119747910));
                orderActorToFactory(1119750910, EnemyMetis, "Metis_1030");
                break;
            case 47940:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119747940));
                orderActorToFactory(1119750940, EnemyMetis, "Metis_1031");
                break;
            case 47970:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119747970));
                orderActorToFactory(1119750970, EnemyMetis, "Metis_1032");
                break;
            case 48000:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119748000));
                orderActorToFactory(1119751000, EnemyMetis, "Metis_1033");
                break;
            case 48030:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119748030));
                orderActorToFactory(1119751030, EnemyMetis, "Metis_1034");
                break;
            case 48060:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119748060));
                orderActorToFactory(1119751060, EnemyMetis, "Metis_1035");
                break;
            case 48090:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119748090));
                orderActorToFactory(1119751090, EnemyMetis, "Metis_1036");
                break;
            case 48120:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119748120));
                orderActorToFactory(1119751120, EnemyMetis, "Metis_1037");
                break;
            case 48150:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119748150));
                orderActorToFactory(1119751150, EnemyMetis, "Metis_1038");
                break;
            case 48180:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119748180));
                orderActorToFactory(1119751180, EnemyMetis, "Metis_1039");
                break;
            case 48210:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119748210));
                orderActorToFactory(1119751210, EnemyMetis, "Metis_1040");
                break;
            case 48240:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119748240));
                orderActorToFactory(1119751240, EnemyMetis, "Metis_1041");
                break;
            case 48270:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119748270));
                orderActorToFactory(1119751270, EnemyMetis, "Metis_1042");
                break;
            case 48300:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119748300));
                orderActorToFactory(1119751300, EnemyMetis, "Metis_1043");
                break;
            case 48330:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119748330));
                orderActorToFactory(1119751330, EnemyMetis, "Metis_1044");
                break;
            case 48360:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119748360));
                orderActorToFactory(1119751360, EnemyMetis, "Metis_1045");
                break;
            case 48390:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119748390));
                orderActorToFactory(1119751390, EnemyMetis, "Metis_1046");
                break;
            case 48420:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119748420));
                orderActorToFactory(1119751420, EnemyMetis, "Metis_1047");
                break;
            case 48450:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119748450));
                orderActorToFactory(1119751450, EnemyMetis, "Metis_1048");
                break;
            case 48480:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119748480));
                orderActorToFactory(1119751480, EnemyMetis, "Metis_1049");
                break;
            case 48510:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119748510));
                orderActorToFactory(1119751510, EnemyMetis, "Metis_1050");
                break;
            case 48540:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119748540));
                orderActorToFactory(1119751540, EnemyMetis, "Metis_1051");
                break;
            case 48570:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119748570));
                orderActorToFactory(1119751570, EnemyMetis, "Metis_1052");
                break;
            case 48600:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119748600));
                orderActorToFactory(1119751600, EnemyMetis, "Metis_1053");
                break;
            case 48630:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119748630));
                orderActorToFactory(1119751630, EnemyMetis, "Metis_1054");
                break;
            case 48660:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119748660));
                orderActorToFactory(1119751660, EnemyMetis, "Metis_1055");
                break;
            case 48690:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119748690));
                orderActorToFactory(1119751690, EnemyMetis, "Metis_1056");
                break;
            case 48720:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119748720));
                orderActorToFactory(1119751720, EnemyMetis, "Metis_1057");
                break;
            case 48750:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119748750));
                orderActorToFactory(1119751750, EnemyMetis, "Metis_1058");
                break;
            case 48780:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119748780));
                orderActorToFactory(1119751780, EnemyMetis, "Metis_1059");
                break;
            case 48810:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119748810));
                orderActorToFactory(1119751810, EnemyMetis, "Metis_1060");
                break;
            case 48840:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119748840));
                orderActorToFactory(1119751840, EnemyMetis, "Metis_1061");
                break;
            case 48870:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119748870));
                orderActorToFactory(1119751870, EnemyMetis, "Metis_1062");
                break;
            case 48900:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119748900));
                orderActorToFactory(1119751900, EnemyMetis, "Metis_1063");
                break;
            case 48930:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119748930));
                orderActorToFactory(1119751930, EnemyMetis, "Metis_1064");
                break;
            case 48960:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119748960));
                orderActorToFactory(1119751960, EnemyMetis, "Metis_1065");
                break;
            case 48990:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119748990));
                orderActorToFactory(1119751990, EnemyMetis, "Metis_1066");
                break;
            case 49020:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119749020));
                orderActorToFactory(1119752020, EnemyMetis, "Metis_1067");
                break;
            case 49050:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119749050));
                orderActorToFactory(1119752050, EnemyMetis, "Metis_1068");
                break;
            case 49080:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119749080));
                orderActorToFactory(1119752080, EnemyMetis, "Metis_1069");
                break;
            case 49110:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119749110));
                orderActorToFactory(1119752110, EnemyMetis, "Metis_1070");
                break;
            case 49140:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119749140));
                orderActorToFactory(1119752140, EnemyMetis, "Metis_1071");
                break;
            case 49170:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119749170));
                orderActorToFactory(1119752170, EnemyMetis, "Metis_1072");
                break;
            case 49200:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119749200));
                orderActorToFactory(1119752200, EnemyMetis, "Metis_1073");
                break;
            case 49230:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119749230));
                orderActorToFactory(1119752230, EnemyMetis, "Metis_1074");
                break;
            case 49260:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119749260));
                orderActorToFactory(1119752260, EnemyMetis, "Metis_1075");
                break;
            case 49290:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119749290));
                orderActorToFactory(1119752290, EnemyMetis, "Metis_1076");
                break;
            case 49320:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119749320));
                orderActorToFactory(1119752320, EnemyMetis, "Metis_1077");
                break;
            case 49350:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119749350));
                orderActorToFactory(1119752350, EnemyMetis, "Metis_1078");
                break;
            case 49380:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119749380));
                orderActorToFactory(1119752380, EnemyMetis, "Metis_1079");
                break;
            case 49410:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119749410));
                orderActorToFactory(1119752410, EnemyMetis, "Metis_1080");
                break;
            case 49440:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119749440));
                orderActorToFactory(1119752440, EnemyMetis, "Metis_1081");
                break;
            case 49470:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119749470));
                orderActorToFactory(1119752470, EnemyMetis, "Metis_1082");
                break;
            case 49500:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119749500));
                orderActorToFactory(1119752500, EnemyMetis, "Metis_1083");
                break;
            case 49530:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119749530));
                orderActorToFactory(1119752530, EnemyMetis, "Metis_1084");
                break;
            case 49560:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119749560));
                orderActorToFactory(1119752560, EnemyMetis, "Metis_1085");
                break;
            case 49590:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119749590));
                orderActorToFactory(1119752590, EnemyMetis, "Metis_1086");
                break;
            case 49620:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119749620));
                orderActorToFactory(1119752620, EnemyMetis, "Metis_1087");
                break;
            case 49650:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119749650));
                orderActorToFactory(1119752650, EnemyMetis, "Metis_1088");
                break;
            case 49680:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119749680));
                orderActorToFactory(1119752680, EnemyMetis, "Metis_1089");
                break;
            case 49710:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119749710));
                orderActorToFactory(1119752710, EnemyMetis, "Metis_1090");
                break;
            case 49740:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119749740));
                orderActorToFactory(1119752740, EnemyMetis, "Metis_1091");
                break;
            case 49770:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119749770));
                orderActorToFactory(1119752770, EnemyMetis, "Metis_1092");
                break;
            case 49800:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119749800));
                orderActorToFactory(1119752800, EnemyMetis, "Metis_1093");
                break;
            case 49830:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119749830));
                orderActorToFactory(1119752830, EnemyMetis, "Metis_1094");
                break;
            case 49860:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119749860));
                orderActorToFactory(1119752860, EnemyMetis, "Metis_1095");
                break;
            case 49890:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119749890));
                orderActorToFactory(1119752890, EnemyMetis, "Metis_1096");
                break;
            case 49920:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119749920));
                orderActorToFactory(1119752920, EnemyMetis, "Metis_1097");
                break;
            case 49950:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119749950));
                orderActorToFactory(1119752950, EnemyMetis, "Metis_1098");
                break;
            case 49980:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119749980));
                orderActorToFactory(1119752980, EnemyMetis, "Metis_1099");
                break;
            case 50010:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119750010));
                orderActorToFactory(1119753010, EnemyMetis, "Metis_1100");
                break;
            case 50040:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119750040));
                orderActorToFactory(1119753040, EnemyMetis, "Metis_1101");
                break;
            case 50070:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119750070));
                orderActorToFactory(1119753070, EnemyMetis, "Metis_1102");
                break;
            case 50100:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119750100));
                orderActorToFactory(1119753100, EnemyMetis, "Metis_1103");
                break;
            case 50130:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119750130));
                orderActorToFactory(1119753130, EnemyMetis, "Metis_1104");
                break;
            case 50160:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119750160));
                orderActorToFactory(1119753160, EnemyMetis, "Metis_1105");
                break;
            case 50190:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119750190));
                orderActorToFactory(1119753190, EnemyMetis, "Metis_1106");
                break;
            case 50220:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119750220));
                orderActorToFactory(1119753220, EnemyMetis, "Metis_1107");
                break;
            case 50250:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119750250));
                orderActorToFactory(1119753250, EnemyMetis, "Metis_1108");
                break;
            case 50280:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119750280));
                orderActorToFactory(1119753280, EnemyMetis, "Metis_1109");
                break;
            case 50310:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119750310));
                orderActorToFactory(1119753310, EnemyMetis, "Metis_1110");
                break;
            case 50340:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119750340));
                orderActorToFactory(1119753340, EnemyMetis, "Metis_1111");
                break;
            case 50370:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119750370));
                orderActorToFactory(1119753370, EnemyMetis, "Metis_1112");
                break;
            case 50400:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119750400));
                orderActorToFactory(1119753400, EnemyMetis, "Metis_1113");
                break;
            case 50430:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119750430));
                orderActorToFactory(1119753430, EnemyMetis, "Metis_1114");
                break;
            case 50460:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119750460));
                orderActorToFactory(1119753460, EnemyMetis, "Metis_1115");
                break;
            case 50490:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119750490));
                orderActorToFactory(1119753490, EnemyMetis, "Metis_1116");
                break;
            case 50520:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119750520));
                orderActorToFactory(1119753520, EnemyMetis, "Metis_1117");
                break;
            case 50550:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119750550));
                orderActorToFactory(1119753550, EnemyMetis, "Metis_1118");
                break;
            case 50580:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119750580));
                orderActorToFactory(1119753580, EnemyMetis, "Metis_1119");
                break;
            case 50610:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119750610));
                orderActorToFactory(1119753610, EnemyMetis, "Metis_1120");
                break;
            case 50640:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119750640));
                orderActorToFactory(1119753640, EnemyMetis, "Metis_1121");
                break;
            case 50670:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119750670));
                orderActorToFactory(1119753670, EnemyMetis, "Metis_1122");
                break;
            case 50700:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119750700));
                orderActorToFactory(1119753700, EnemyMetis, "Metis_1123");
                break;
            case 50730:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119750730));
                orderActorToFactory(1119753730, EnemyMetis, "Metis_1124");
                break;
            case 50760:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119750760));
                orderActorToFactory(1119753760, EnemyMetis, "Metis_1125");
                break;
            case 50790:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119750790));
                orderActorToFactory(1119753790, EnemyMetis, "Metis_1126");
                break;
            case 50820:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119750820));
                orderActorToFactory(1119753820, EnemyMetis, "Metis_1127");
                break;
            case 50850:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119750850));
                orderActorToFactory(1119753850, EnemyMetis, "Metis_1128");
                break;
            case 50880:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119750880));
                orderActorToFactory(1119753880, EnemyMetis, "Metis_1129");
                break;
            case 50910:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119750910));
                orderActorToFactory(1119753910, EnemyMetis, "Metis_1130");
                break;
            case 50940:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119750940));
                orderActorToFactory(1119753940, EnemyMetis, "Metis_1131");
                break;
            case 50970:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119750970));
                orderActorToFactory(1119753970, EnemyMetis, "Metis_1132");
                break;
            case 51000:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119751000));
                orderActorToFactory(1119754000, EnemyMetis, "Metis_1133");
                break;
            case 51030:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119751030));
                orderActorToFactory(1119754030, EnemyMetis, "Metis_1134");
                break;
            case 51060:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119751060));
                orderActorToFactory(1119754060, EnemyMetis, "Metis_1135");
                break;
            case 51090:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119751090));
                orderActorToFactory(1119754090, EnemyMetis, "Metis_1136");
                break;
            case 51120:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119751120));
                orderActorToFactory(1119754120, EnemyMetis, "Metis_1137");
                break;
            case 51150:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119751150));
                orderActorToFactory(1119754150, EnemyMetis, "Metis_1138");
                break;
            case 51180:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119751180));
                orderActorToFactory(1119754180, EnemyMetis, "Metis_1139");
                break;
            case 51210:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119751210));
                orderActorToFactory(1119754210, EnemyMetis, "Metis_1140");
                break;
            case 51240:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119751240));
                orderActorToFactory(1119754240, EnemyMetis, "Metis_1141");
                break;
            case 51270:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119751270));
                orderActorToFactory(1119754270, EnemyMetis, "Metis_1142");
                break;
            case 51300:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119751300));
                orderActorToFactory(1119754300, EnemyMetis, "Metis_1143");
                break;
            case 51330:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119751330));
                orderActorToFactory(1119754330, EnemyMetis, "Metis_1144");
                break;
            case 51360:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119751360));
                orderActorToFactory(1119754360, EnemyMetis, "Metis_1145");
                break;
            case 51390:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119751390));
                orderActorToFactory(1119754390, EnemyMetis, "Metis_1146");
                break;
            case 51420:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119751420));
                orderActorToFactory(1119754420, EnemyMetis, "Metis_1147");
                break;
            case 51450:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119751450));
                orderActorToFactory(1119754450, EnemyMetis, "Metis_1148");
                break;
            case 51480:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119751480));
                orderActorToFactory(1119754480, EnemyMetis, "Metis_1149");
                break;
            case 51510:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119751510));
                orderActorToFactory(1119754510, EnemyMetis, "Metis_1150");
                break;
            case 51540:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119751540));
                orderActorToFactory(1119754540, EnemyMetis, "Metis_1151");
                break;
            case 51570:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119751570));
                orderActorToFactory(1119754570, EnemyMetis, "Metis_1152");
                break;
            case 51600:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119751600));
                orderActorToFactory(1119754600, EnemyMetis, "Metis_1153");
                break;
            case 51630:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119751630));
                orderActorToFactory(1119754630, EnemyMetis, "Metis_1154");
                break;
            case 51660:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119751660));
                orderActorToFactory(1119754660, EnemyMetis, "Metis_1155");
                break;
            case 51690:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119751690));
                orderActorToFactory(1119754690, EnemyMetis, "Metis_1156");
                break;
            case 51720:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119751720));
                orderActorToFactory(1119754720, EnemyMetis, "Metis_1157");
                break;
            case 51750:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119751750));
                orderActorToFactory(1119754750, EnemyMetis, "Metis_1158");
                break;
            case 51780:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119751780));
                orderActorToFactory(1119754780, EnemyMetis, "Metis_1159");
                break;
            case 51810:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119751810));
                orderActorToFactory(1119754810, EnemyMetis, "Metis_1160");
                break;
            case 51840:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119751840));
                orderActorToFactory(1119754840, EnemyMetis, "Metis_1161");
                break;
            case 51870:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119751870));
                orderActorToFactory(1119754870, EnemyMetis, "Metis_1162");
                break;
            case 51900:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119751900));
                orderActorToFactory(1119754900, EnemyMetis, "Metis_1163");
                break;
            case 51930:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119751930));
                orderActorToFactory(1119754930, EnemyMetis, "Metis_1164");
                break;
            case 51960:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119751960));
                orderActorToFactory(1119754960, EnemyMetis, "Metis_1165");
                break;
            case 51990:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119751990));
                orderActorToFactory(1119754990, EnemyMetis, "Metis_1166");
                break;
            case 52020:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119752020));
                orderActorToFactory(1119755020, EnemyMetis, "Metis_1167");
                break;
            case 52050:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119752050));
                orderActorToFactory(1119755050, EnemyMetis, "Metis_1168");
                break;
            case 52080:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119752080));
                orderActorToFactory(1119755080, EnemyMetis, "Metis_1169");
                break;
            case 52110:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119752110));
                orderActorToFactory(1119755110, EnemyMetis, "Metis_1170");
                break;
            case 52140:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119752140));
                orderActorToFactory(1119755140, EnemyMetis, "Metis_1171");
                break;
            case 52170:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119752170));
                orderActorToFactory(1119755170, EnemyMetis, "Metis_1172");
                break;
            case 52200:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119752200));
                orderActorToFactory(1119755200, EnemyMetis, "Metis_1173");
                break;
            case 52230:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119752230));
                orderActorToFactory(1119755230, EnemyMetis, "Metis_1174");
                break;
            case 52260:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119752260));
                orderActorToFactory(1119755260, EnemyMetis, "Metis_1175");
                break;
            case 52290:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119752290));
                orderActorToFactory(1119755290, EnemyMetis, "Metis_1176");
                break;
            case 52320:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119752320));
                orderActorToFactory(1119755320, EnemyMetis, "Metis_1177");
                break;
            case 52350:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119752350));
                orderActorToFactory(1119755350, EnemyMetis, "Metis_1178");
                break;
            case 52380:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119752380));
                orderActorToFactory(1119755380, EnemyMetis, "Metis_1179");
                break;
            case 52410:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119752410));
                orderActorToFactory(1119755410, EnemyMetis, "Metis_1180");
                break;
            case 52440:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119752440));
                orderActorToFactory(1119755440, EnemyMetis, "Metis_1181");
                break;
            case 52470:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119752470));
                orderActorToFactory(1119755470, EnemyMetis, "Metis_1182");
                break;
            case 52500:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119752500));
                orderActorToFactory(1119755500, EnemyMetis, "Metis_1183");
                break;
            case 52530:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119752530));
                orderActorToFactory(1119755530, EnemyMetis, "Metis_1184");
                break;
            case 52560:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119752560));
                orderActorToFactory(1119755560, EnemyMetis, "Metis_1185");
                break;
            case 52590:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119752590));
                orderActorToFactory(1119755590, EnemyMetis, "Metis_1186");
                break;
            case 52620:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119752620));
                orderActorToFactory(1119755620, EnemyMetis, "Metis_1187");
                break;
            case 52650:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119752650));
                orderActorToFactory(1119755650, EnemyMetis, "Metis_1188");
                break;
            case 52680:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119752680));
                orderActorToFactory(1119755680, EnemyMetis, "Metis_1189");
                break;
            case 52710:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119752710));
                orderActorToFactory(1119755710, EnemyMetis, "Metis_1190");
                break;
            case 52740:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119752740));
                orderActorToFactory(1119755740, EnemyMetis, "Metis_1191");
                break;
            case 52770:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119752770));
                orderActorToFactory(1119755770, EnemyMetis, "Metis_1192");
                break;
            case 52800:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119752800));
                orderActorToFactory(1119755800, EnemyMetis, "Metis_1193");
                break;
            case 52830:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119752830));
                orderActorToFactory(1119755830, EnemyMetis, "Metis_1194");
                break;
            case 52860:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119752860));
                orderActorToFactory(1119755860, EnemyMetis, "Metis_1195");
                break;
            case 52890:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119752890));
                orderActorToFactory(1119755890, EnemyMetis, "Metis_1196");
                break;
            case 52920:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119752920));
                orderActorToFactory(1119755920, EnemyMetis, "Metis_1197");
                break;
            case 52950:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119752950));
                orderActorToFactory(1119755950, EnemyMetis, "Metis_1198");
                break;
            case 52980:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119752980));
                orderActorToFactory(1119755980, EnemyMetis, "Metis_1199");
                break;
            case 53010:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119753010));
                orderActorToFactory(1119756010, EnemyMetis, "Metis_1200");
                break;
            case 53040:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119753040));
                orderActorToFactory(1119756040, EnemyMetis, "Metis_1201");
                break;
            case 53070:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119753070));
                orderActorToFactory(1119756070, EnemyMetis, "Metis_1202");
                break;
            case 53100:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119753100));
                orderActorToFactory(1119756100, EnemyMetis, "Metis_1203");
                break;
            case 53130:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119753130));
                orderActorToFactory(1119756130, EnemyMetis, "Metis_1204");
                break;
            case 53160:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119753160));
                orderActorToFactory(1119756160, EnemyMetis, "Metis_1205");
                break;
            case 53190:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119753190));
                orderActorToFactory(1119756190, EnemyMetis, "Metis_1206");
                break;
            case 53220:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119753220));
                orderActorToFactory(1119756220, EnemyMetis, "Metis_1207");
                break;
            case 53250:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119753250));
                orderActorToFactory(1119756250, EnemyMetis, "Metis_1208");
                break;
            case 53280:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119753280));
                orderActorToFactory(1119756280, EnemyMetis, "Metis_1209");
                break;
            case 53310:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119753310));
                orderActorToFactory(1119756310, EnemyMetis, "Metis_1210");
                break;
            case 53340:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119753340));
                orderActorToFactory(1119756340, EnemyMetis, "Metis_1211");
                break;
            case 53370:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119753370));
                orderActorToFactory(1119756370, EnemyMetis, "Metis_1212");
                break;
            case 53400:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119753400));
                orderActorToFactory(1119756400, EnemyMetis, "Metis_1213");
                break;
            case 53430:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119753430));
                orderActorToFactory(1119756430, EnemyMetis, "Metis_1214");
                break;
            case 53460:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119753460));
                orderActorToFactory(1119756460, EnemyMetis, "Metis_1215");
                break;
            case 53490:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119753490));
                orderActorToFactory(1119756490, EnemyMetis, "Metis_1216");
                break;
            case 53520:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119753520));
                orderActorToFactory(1119756520, EnemyMetis, "Metis_1217");
                break;
            case 53550:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119753550));
                orderActorToFactory(1119756550, EnemyMetis, "Metis_1218");
                break;
            case 53580:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119753580));
                orderActorToFactory(1119756580, EnemyMetis, "Metis_1219");
                break;
            case 53610:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119753610));
                orderActorToFactory(1119756610, EnemyMetis, "Metis_1220");
                break;
            case 53640:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119753640));
                orderActorToFactory(1119756640, EnemyMetis, "Metis_1221");
                break;
            case 53670:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119753670));
                orderActorToFactory(1119756670, EnemyMetis, "Metis_1222");
                break;
            case 53700:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119753700));
                orderActorToFactory(1119756700, EnemyMetis, "Metis_1223");
                break;
            case 53730:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119753730));
                orderActorToFactory(1119756730, EnemyMetis, "Metis_1224");
                break;
            case 53760:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119753760));
                orderActorToFactory(1119756760, EnemyMetis, "Metis_1225");
                break;
            case 53790:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119753790));
                orderActorToFactory(1119756790, EnemyMetis, "Metis_1226");
                break;
            case 53820:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119753820));
                orderActorToFactory(1119756820, EnemyMetis, "Metis_1227");
                break;
            case 53850:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119753850));
                orderActorToFactory(1119756850, EnemyMetis, "Metis_1228");
                break;
            case 53880:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119753880));
                orderActorToFactory(1119756880, EnemyMetis, "Metis_1229");
                break;
            case 53910:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119753910));
                orderActorToFactory(1119756910, EnemyMetis, "Metis_1230");
                break;
            case 53940:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119753940));
                orderActorToFactory(1119756940, EnemyMetis, "Metis_1231");
                break;
            case 53970:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119753970));
                orderActorToFactory(1119756970, EnemyMetis, "Metis_1232");
                break;
            case 54000:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119754000));
                orderActorToFactory(1119757000, EnemyMetis, "Metis_1233");
                break;
            case 54030:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119754030));
                orderActorToFactory(1119757030, EnemyMetis, "Metis_1234");
                break;
            case 54060:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119754060));
                orderActorToFactory(1119757060, EnemyMetis, "Metis_1235");
                break;
            case 54090:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119754090));
                orderActorToFactory(1119757090, EnemyMetis, "Metis_1236");
                break;
            case 54120:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119754120));
                orderActorToFactory(1119757120, EnemyMetis, "Metis_1237");
                break;
            case 54150:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119754150));
                orderActorToFactory(1119757150, EnemyMetis, "Metis_1238");
                break;
            case 54180:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119754180));
                orderActorToFactory(1119757180, EnemyMetis, "Metis_1239");
                break;
            case 54210:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119754210));
                orderActorToFactory(1119757210, EnemyMetis, "Metis_1240");
                break;
            case 54240:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119754240));
                orderActorToFactory(1119757240, EnemyMetis, "Metis_1241");
                break;
            case 54270:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119754270));
                orderActorToFactory(1119757270, EnemyMetis, "Metis_1242");
                break;
            case 54300:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119754300));
                orderActorToFactory(1119757300, EnemyMetis, "Metis_1243");
                break;
            case 54330:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119754330));
                orderActorToFactory(1119757330, EnemyMetis, "Metis_1244");
                break;
            case 54360:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119754360));
                orderActorToFactory(1119757360, EnemyMetis, "Metis_1245");
                break;
            case 54390:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119754390));
                orderActorToFactory(1119757390, EnemyMetis, "Metis_1246");
                break;
            case 54420:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119754420));
                orderActorToFactory(1119757420, EnemyMetis, "Metis_1247");
                break;
            case 54450:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119754450));
                orderActorToFactory(1119757450, EnemyMetis, "Metis_1248");
                break;
            case 54480:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119754480));
                orderActorToFactory(1119757480, EnemyMetis, "Metis_1249");
                break;
            case 54510:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119754510));
                orderActorToFactory(1119757510, EnemyMetis, "Metis_1250");
                break;
            case 54540:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119754540));
                orderActorToFactory(1119757540, EnemyMetis, "Metis_1251");
                break;
            case 54570:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119754570));
                orderActorToFactory(1119757570, EnemyMetis, "Metis_1252");
                break;
            case 54600:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119754600));
                orderActorToFactory(1119757600, EnemyMetis, "Metis_1253");
                break;
            case 54630:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119754630));
                orderActorToFactory(1119757630, EnemyMetis, "Metis_1254");
                break;
            case 54660:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119754660));
                orderActorToFactory(1119757660, EnemyMetis, "Metis_1255");
                break;
            case 54690:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119754690));
                orderActorToFactory(1119757690, EnemyMetis, "Metis_1256");
                break;
            case 54720:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119754720));
                orderActorToFactory(1119757720, EnemyMetis, "Metis_1257");
                break;
            case 54750:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119754750));
                orderActorToFactory(1119757750, EnemyMetis, "Metis_1258");
                break;
            case 54780:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119754780));
                orderActorToFactory(1119757780, EnemyMetis, "Metis_1259");
                break;
            case 54810:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119754810));
                orderActorToFactory(1119757810, EnemyMetis, "Metis_1260");
                break;
            case 54840:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119754840));
                orderActorToFactory(1119757840, EnemyMetis, "Metis_1261");
                break;
            case 54870:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119754870));
                orderActorToFactory(1119757870, EnemyMetis, "Metis_1262");
                break;
            case 54900:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119754900));
                orderActorToFactory(1119757900, EnemyMetis, "Metis_1263");
                break;
            case 54930:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119754930));
                orderActorToFactory(1119757930, EnemyMetis, "Metis_1264");
                break;
            case 54960:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119754960));
                orderActorToFactory(1119757960, EnemyMetis, "Metis_1265");
                break;
            case 54990:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119754990));
                orderActorToFactory(1119757990, EnemyMetis, "Metis_1266");
                break;
            case 55020:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119755020));
                orderActorToFactory(1119758020, EnemyMetis, "Metis_1267");
                break;
            case 55050:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119755050));
                orderActorToFactory(1119758050, EnemyMetis, "Metis_1268");
                break;
            case 55080:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119755080));
                orderActorToFactory(1119758080, EnemyMetis, "Metis_1269");
                break;
            case 55110:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119755110));
                orderActorToFactory(1119758110, EnemyMetis, "Metis_1270");
                break;
            case 55140:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119755140));
                orderActorToFactory(1119758140, EnemyMetis, "Metis_1271");
                break;
            case 55170:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119755170));
                orderActorToFactory(1119758170, EnemyMetis, "Metis_1272");
                break;
            case 55200:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119755200));
                orderActorToFactory(1119758200, EnemyMetis, "Metis_1273");
                break;
            case 55230:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119755230));
                orderActorToFactory(1119758230, EnemyMetis, "Metis_1274");
                break;
            case 55260:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119755260));
                orderActorToFactory(1119758260, EnemyMetis, "Metis_1275");
                break;
            case 55290:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119755290));
                orderActorToFactory(1119758290, EnemyMetis, "Metis_1276");
                break;
            case 55320:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119755320));
                orderActorToFactory(1119758320, EnemyMetis, "Metis_1277");
                break;
            case 55350:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119755350));
                orderActorToFactory(1119758350, EnemyMetis, "Metis_1278");
                break;
            case 55380:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119755380));
                orderActorToFactory(1119758380, EnemyMetis, "Metis_1279");
                break;
            case 55410:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119755410));
                orderActorToFactory(1119758410, EnemyMetis, "Metis_1280");
                break;
            case 55440:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119755440));
                orderActorToFactory(1119758440, EnemyMetis, "Metis_1281");
                break;
            case 55470:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119755470));
                orderActorToFactory(1119758470, EnemyMetis, "Metis_1282");
                break;
            case 55500:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119755500));
                orderActorToFactory(1119758500, EnemyMetis, "Metis_1283");
                break;
            case 55530:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119755530));
                orderActorToFactory(1119758530, EnemyMetis, "Metis_1284");
                break;
            case 55560:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119755560));
                orderActorToFactory(1119758560, EnemyMetis, "Metis_1285");
                break;
            case 55590:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119755590));
                orderActorToFactory(1119758590, EnemyMetis, "Metis_1286");
                break;
            case 55620:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119755620));
                orderActorToFactory(1119758620, EnemyMetis, "Metis_1287");
                break;
            case 55650:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119755650));
                orderActorToFactory(1119758650, EnemyMetis, "Metis_1288");
                break;
            case 55680:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119755680));
                orderActorToFactory(1119758680, EnemyMetis, "Metis_1289");
                break;
            case 55710:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119755710));
                orderActorToFactory(1119758710, EnemyMetis, "Metis_1290");
                break;
            case 55740:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119755740));
                orderActorToFactory(1119758740, EnemyMetis, "Metis_1291");
                break;
            case 55770:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119755770));
                orderActorToFactory(1119758770, EnemyMetis, "Metis_1292");
                break;
            case 55800:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119755800));
                orderActorToFactory(1119758800, EnemyMetis, "Metis_1293");
                break;
            case 55830:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119755830));
                orderActorToFactory(1119758830, EnemyMetis, "Metis_1294");
                break;
            case 55860:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119755860));
                orderActorToFactory(1119758860, EnemyMetis, "Metis_1295");
                break;
            case 55890:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119755890));
                orderActorToFactory(1119758890, EnemyMetis, "Metis_1296");
                break;
            case 55920:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119755920));
                orderActorToFactory(1119758920, EnemyMetis, "Metis_1297");
                break;
            case 55950:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119755950));
                orderActorToFactory(1119758950, EnemyMetis, "Metis_1298");
                break;
            case 55980:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119755980));
                orderActorToFactory(1119758980, EnemyMetis, "Metis_1299");
                break;
            case 56010:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119756010));
                orderActorToFactory(1119759010, EnemyMetis, "Metis_1300");
                break;
            case 56040:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119756040));
                orderActorToFactory(1119759040, EnemyMetis, "Metis_1301");
                break;
            case 56070:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119756070));
                orderActorToFactory(1119759070, EnemyMetis, "Metis_1302");
                break;
            case 56100:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119756100));
                orderActorToFactory(1119759100, EnemyMetis, "Metis_1303");
                break;
            case 56130:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119756130));
                orderActorToFactory(1119759130, EnemyMetis, "Metis_1304");
                break;
            case 56160:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119756160));
                orderActorToFactory(1119759160, EnemyMetis, "Metis_1305");
                break;
            case 56190:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119756190));
                orderActorToFactory(1119759190, EnemyMetis, "Metis_1306");
                break;
            case 56220:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119756220));
                orderActorToFactory(1119759220, EnemyMetis, "Metis_1307");
                break;
            case 56250:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119756250));
                orderActorToFactory(1119759250, EnemyMetis, "Metis_1308");
                break;
            case 56280:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119756280));
                orderActorToFactory(1119759280, EnemyMetis, "Metis_1309");
                break;
            case 56310:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119756310));
                orderActorToFactory(1119759310, EnemyMetis, "Metis_1310");
                break;
            case 56340:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119756340));
                orderActorToFactory(1119759340, EnemyMetis, "Metis_1311");
                break;
            case 56370:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119756370));
                orderActorToFactory(1119759370, EnemyMetis, "Metis_1312");
                break;
            case 56400:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119756400));
                orderActorToFactory(1119759400, EnemyMetis, "Metis_1313");
                break;
            case 56430:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119756430));
                orderActorToFactory(1119759430, EnemyMetis, "Metis_1314");
                break;
            case 56460:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119756460));
                orderActorToFactory(1119759460, EnemyMetis, "Metis_1315");
                break;
            case 56490:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119756490));
                orderActorToFactory(1119759490, EnemyMetis, "Metis_1316");
                break;
            case 56520:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119756520));
                orderActorToFactory(1119759520, EnemyMetis, "Metis_1317");
                break;
            case 56550:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119756550));
                orderActorToFactory(1119759550, EnemyMetis, "Metis_1318");
                break;
            case 56580:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119756580));
                orderActorToFactory(1119759580, EnemyMetis, "Metis_1319");
                break;
            case 56610:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119756610));
                orderActorToFactory(1119759610, EnemyMetis, "Metis_1320");
                break;
            case 56640:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119756640));
                orderActorToFactory(1119759640, EnemyMetis, "Metis_1321");
                break;
            case 56670:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119756670));
                orderActorToFactory(1119759670, EnemyMetis, "Metis_1322");
                break;
            case 56700:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119756700));
                orderActorToFactory(1119759700, EnemyMetis, "Metis_1323");
                break;
            case 56730:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119756730));
                orderActorToFactory(1119759730, EnemyMetis, "Metis_1324");
                break;
            case 56760:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119756760));
                orderActorToFactory(1119759760, EnemyMetis, "Metis_1325");
                break;
            case 56790:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119756790));
                orderActorToFactory(1119759790, EnemyMetis, "Metis_1326");
                break;
            case 56820:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119756820));
                orderActorToFactory(1119759820, EnemyMetis, "Metis_1327");
                break;
            case 56850:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119756850));
                orderActorToFactory(1119759850, EnemyMetis, "Metis_1328");
                break;
            case 56880:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119756880));
                orderActorToFactory(1119759880, EnemyMetis, "Metis_1329");
                break;
            case 56910:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119756910));
                orderActorToFactory(1119759910, EnemyMetis, "Metis_1330");
                break;
            case 56940:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119756940));
                orderActorToFactory(1119759940, EnemyMetis, "Metis_1331");
                break;
            case 56970:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119756970));
                orderActorToFactory(1119759970, EnemyMetis, "Metis_1332");
                break;
            case 57000:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119757000));
                orderActorToFactory(1119760000, EnemyMetis, "Metis_1333");
                break;
            case 57030:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119757030));
                orderActorToFactory(1119760030, EnemyMetis, "Metis_1334");
                break;
            case 57060:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119757060));
                orderActorToFactory(1119760060, EnemyMetis, "Metis_1335");
                break;
            case 57090:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119757090));
                orderActorToFactory(1119760090, EnemyMetis, "Metis_1336");
                break;
            case 57120:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119757120));
                orderActorToFactory(1119760120, EnemyMetis, "Metis_1337");
                break;
            case 57150:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119757150));
                orderActorToFactory(1119760150, EnemyMetis, "Metis_1338");
                break;
            case 57180:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119757180));
                orderActorToFactory(1119760180, EnemyMetis, "Metis_1339");
                break;
            case 57210:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119757210));
                orderActorToFactory(1119760210, EnemyMetis, "Metis_1340");
                break;
            case 57240:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119757240));
                orderActorToFactory(1119760240, EnemyMetis, "Metis_1341");
                break;
            case 57270:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119757270));
                orderActorToFactory(1119760270, EnemyMetis, "Metis_1342");
                break;
            case 57300:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119757300));
                orderActorToFactory(1119760300, EnemyMetis, "Metis_1343");
                break;
            case 57330:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119757330));
                orderActorToFactory(1119760330, EnemyMetis, "Metis_1344");
                break;
            case 57360:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119757360));
                orderActorToFactory(1119760360, EnemyMetis, "Metis_1345");
                break;
            case 57390:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119757390));
                orderActorToFactory(1119760390, EnemyMetis, "Metis_1346");
                break;
            case 57420:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119757420));
                orderActorToFactory(1119760420, EnemyMetis, "Metis_1347");
                break;
            case 57450:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119757450));
                orderActorToFactory(1119760450, EnemyMetis, "Metis_1348");
                break;
            case 57480:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119757480));
                orderActorToFactory(1119760480, EnemyMetis, "Metis_1349");
                break;
            case 57510:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119757510));
                orderActorToFactory(1119760510, EnemyMetis, "Metis_1350");
                break;
            case 57540:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119757540));
                orderActorToFactory(1119760540, EnemyMetis, "Metis_1351");
                break;
            case 57570:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119757570));
                orderActorToFactory(1119760570, EnemyMetis, "Metis_1352");
                break;
            case 57600:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119757600));
                orderActorToFactory(1119760600, EnemyMetis, "Metis_1353");
                break;
            case 57630:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119757630));
                orderActorToFactory(1119760630, EnemyMetis, "Metis_1354");
                break;
            case 57660:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119757660));
                orderActorToFactory(1119760660, EnemyMetis, "Metis_1355");
                break;
            case 57690:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119757690));
                orderActorToFactory(1119760690, EnemyMetis, "Metis_1356");
                break;
            case 57720:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119757720));
                orderActorToFactory(1119760720, EnemyMetis, "Metis_1357");
                break;
            case 57750:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119757750));
                orderActorToFactory(1119760750, EnemyMetis, "Metis_1358");
                break;
            case 57780:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119757780));
                orderActorToFactory(1119760780, EnemyMetis, "Metis_1359");
                break;
            case 57810:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119757810));
                orderActorToFactory(1119760810, EnemyMetis, "Metis_1360");
                break;
            case 57840:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119757840));
                orderActorToFactory(1119760840, EnemyMetis, "Metis_1361");
                break;
            case 57870:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119757870));
                orderActorToFactory(1119760870, EnemyMetis, "Metis_1362");
                break;
            case 57900:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119757900));
                orderActorToFactory(1119760900, EnemyMetis, "Metis_1363");
                break;
            case 57930:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119757930));
                orderActorToFactory(1119760930, EnemyMetis, "Metis_1364");
                break;
            case 57960:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119757960));
                orderActorToFactory(1119760960, EnemyMetis, "Metis_1365");
                break;
            case 57990:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119757990));
                orderActorToFactory(1119760990, EnemyMetis, "Metis_1366");
                break;
            case 58020:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119758020));
                orderActorToFactory(1119761020, EnemyMetis, "Metis_1367");
                break;
            case 58050:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119758050));
                orderActorToFactory(1119761050, EnemyMetis, "Metis_1368");
                break;
            case 58080:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119758080));
                orderActorToFactory(1119761080, EnemyMetis, "Metis_1369");
                break;
            case 58110:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119758110));
                orderActorToFactory(1119761110, EnemyMetis, "Metis_1370");
                break;
            case 58140:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119758140));
                orderActorToFactory(1119761140, EnemyMetis, "Metis_1371");
                break;
            case 58170:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119758170));
                orderActorToFactory(1119761170, EnemyMetis, "Metis_1372");
                break;
            case 58200:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119758200));
                orderActorToFactory(1119761200, EnemyMetis, "Metis_1373");
                break;
            case 58230:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119758230));
                orderActorToFactory(1119761230, EnemyMetis, "Metis_1374");
                break;
            case 58260:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119758260));
                orderActorToFactory(1119761260, EnemyMetis, "Metis_1375");
                break;
            case 58290:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119758290));
                orderActorToFactory(1119761290, EnemyMetis, "Metis_1376");
                break;
            case 58320:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119758320));
                orderActorToFactory(1119761320, EnemyMetis, "Metis_1377");
                break;
            case 58350:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119758350));
                orderActorToFactory(1119761350, EnemyMetis, "Metis_1378");
                break;
            case 58380:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119758380));
                orderActorToFactory(1119761380, EnemyMetis, "Metis_1379");
                break;
            case 58410:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119758410));
                orderActorToFactory(1119761410, EnemyMetis, "Metis_1380");
                break;
            case 58440:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119758440));
                orderActorToFactory(1119761440, EnemyMetis, "Metis_1381");
                break;
            case 58470:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119758470));
                orderActorToFactory(1119761470, EnemyMetis, "Metis_1382");
                break;
            case 58500:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119758500));
                orderActorToFactory(1119761500, EnemyMetis, "Metis_1383");
                break;
            case 58530:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119758530));
                orderActorToFactory(1119761530, EnemyMetis, "Metis_1384");
                break;
            case 58560:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119758560));
                orderActorToFactory(1119761560, EnemyMetis, "Metis_1385");
                break;
            case 58590:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119758590));
                orderActorToFactory(1119761590, EnemyMetis, "Metis_1386");
                break;
            case 58620:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119758620));
                orderActorToFactory(1119761620, EnemyMetis, "Metis_1387");
                break;
            case 58650:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119758650));
                orderActorToFactory(1119761650, EnemyMetis, "Metis_1388");
                break;
            case 58680:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119758680));
                orderActorToFactory(1119761680, EnemyMetis, "Metis_1389");
                break;
            case 58710:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119758710));
                orderActorToFactory(1119761710, EnemyMetis, "Metis_1390");
                break;
            case 58740:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119758740));
                orderActorToFactory(1119761740, EnemyMetis, "Metis_1391");
                break;
            case 58770:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119758770));
                orderActorToFactory(1119761770, EnemyMetis, "Metis_1392");
                break;
            case 58800:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119758800));
                orderActorToFactory(1119761800, EnemyMetis, "Metis_1393");
                break;
            case 58830:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119758830));
                orderActorToFactory(1119761830, EnemyMetis, "Metis_1394");
                break;
            case 58860:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119758860));
                orderActorToFactory(1119761860, EnemyMetis, "Metis_1395");
                break;
            case 58890:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119758890));
                orderActorToFactory(1119761890, EnemyMetis, "Metis_1396");
                break;
            case 58920:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119758920));
                orderActorToFactory(1119761920, EnemyMetis, "Metis_1397");
                break;
            case 58950:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119758950));
                orderActorToFactory(1119761950, EnemyMetis, "Metis_1398");
                break;
            case 58980:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119758980));
                orderActorToFactory(1119761980, EnemyMetis, "Metis_1399");
                break;
            case 59010:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119759010));
                break;
            case 59040:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119759040));
                break;
            case 59070:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119759070));
                break;
            case 59100:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119759100));
                break;
            case 59130:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119759130));
                break;
            case 59160:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119759160));
                break;
            case 59190:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119759190));
                break;
            case 59220:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119759220));
                break;
            case 59250:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119759250));
                break;
            case 59280:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119759280));
                break;
            case 59310:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119759310));
                break;
            case 59340:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119759340));
                break;
            case 59370:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119759370));
                break;
            case 59400:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119759400));
                break;
            case 59430:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119759430));
                break;
            case 59460:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119759460));
                break;
            case 59490:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119759490));
                break;
            case 59520:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119759520));
                break;
            case 59550:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119759550));
                break;
            case 59580:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119759580));
                break;
            case 59610:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119759610));
                break;
            case 59640:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119759640));
                break;
            case 59670:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119759670));
                break;
            case 59700:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119759700));
                break;
            case 59730:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119759730));
                break;
            case 59760:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119759760));
                break;
            case 59790:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119759790));
                break;
            case 59820:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119759820));
                break;
            case 59850:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119759850));
                break;
            case 59880:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119759880));
                break;
            case 59910:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119759910));
                break;
            case 59940:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119759940));
                break;
            case 59970:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119759970));
                break;
            case 60000:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119760000));
                break;
            case 60030:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119760030));
                break;
            case 60060:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119760060));
                break;
            case 60090:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119760090));
                break;
            case 60120:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119760120));
                break;
            case 60150:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119760150));
                break;
            case 60180:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119760180));
                break;
            case 60210:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119760210));
                break;
            case 60240:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119760240));
                break;
            case 60270:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119760270));
                break;
            case 60300:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119760300));
                break;
            case 60330:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119760330));
                break;
            case 60360:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119760360));
                break;
            case 60390:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119760390));
                break;
            case 60420:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119760420));
                break;
            case 60450:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119760450));
                break;
            case 60480:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119760480));
                break;
            case 60510:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119760510));
                break;
            case 60540:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119760540));
                break;
            case 60570:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119760570));
                break;
            case 60600:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119760600));
                break;
            case 60630:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119760630));
                break;
            case 60660:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119760660));
                break;
            case 60690:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119760690));
                break;
            case 60720:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119760720));
                break;
            case 60750:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119760750));
                break;
            case 60780:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119760780));
                break;
            case 60810:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119760810));
                break;
            case 60840:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119760840));
                break;
            case 60870:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119760870));
                break;
            case 60900:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119760900));
                break;
            case 60930:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119760930));
                break;
            case 60960:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119760960));
                break;
            case 60990:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119760990));
                break;
            case 61020:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119761020));
                break;
            case 61050:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119761050));
                break;
            case 61080:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119761080));
                break;
            case 61110:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119761110));
                break;
            case 61140:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119761140));
                break;
            case 61170:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119761170));
                break;
            case 61200:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119761200));
                break;
            case 61230:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119761230));
                break;
            case 61260:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119761260));
                break;
            case 61290:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119761290));
                break;
            case 61320:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119761320));
                break;
            case 61350:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119761350));
                break;
            case 61380:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119761380));
                break;
            case 61410:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119761410));
                break;
            case 61440:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119761440));
                break;
            case 61470:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119761470));
                break;
            case 61500:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119761500));
                break;
            case 61530:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119761530));
                break;
            case 61560:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119761560));
                break;
            case 61590:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119761590));
                break;
            case 61620:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119761620));
                break;
            case 61650:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119761650));
                break;
            case 61680:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119761680));
                break;
            case 61710:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119761710));
                break;
            case 61740:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119761740));
                break;
            case 61770:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119761770));
                break;
            case 61800:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119761800));
                break;
            case 61830:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119761830));
                break;
            case 61860:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119761860));
                break;
            case 61890:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119761890));
                break;
            case 61920:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119761920));
                break;
            case 61950:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119761950));
                break;
            case 61980:
                getLordActor()->addSubGroup(obtainActorFromFactory(1119761980));
                break;
            default :
                break;
        }
        _iCnt_Event = (_iCnt_Event < 1510-1 ? _iCnt_Event+1 : _iCnt_Event);
    }
    // gen02 end

    if (getBehaveingFrame() == 2) {

        _TRACE_("Stage01MainScene::processBehavior はいはいDemoさんありがとう、私も起動しましたよ");
        // 共通シーンを配下に移動
        addSubLast(GameGlobal::_pSceneCommon->extract());

    }

}

void Stage01MainScene::processFinal() {
    //	if (getBehaveingFrame() == 1) {
    //		_TRACE_("Stage01MainScene::processFinally 私はいきなり停止します。GameMainSceneが解除してくれるはずー");
    //		this->inactivateTree(); //GameMainSceneが解除してくれる
    //	}
}

Stage01MainScene::~Stage01MainScene() {

}
