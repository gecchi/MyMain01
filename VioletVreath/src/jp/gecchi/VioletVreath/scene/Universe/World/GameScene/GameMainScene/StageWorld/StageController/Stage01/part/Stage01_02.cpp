#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

Stage01_02::Stage01_02(const char* prm_name) : DefaultScene(prm_name) {
    _class_name = "Stage01_02";
    // 以下の gen01 start ～ end はExcelマクロにより自動生成されたコードです。
    // コードの変更は「シーンCreater.xls」から行う事とする（整合性確保のため）。
    // gen01 start
    frame f[] = {1,100,200,500,700,1000,1200,1500,1700,2000,2200,2500,2700,3000,3200,3500,3700,4000,4200,4500,4700,5000,5200,5500,5700,6000,6200,6500,6700,7000,7200,7500,7700,8000,8200,8500,8700,9000,9200,9500,9700,10000,10200,10500,10700,11000,11200,11500,11700,12000,12200,12500,12700,13000,13200,13500,13700,14000,14200,14500,14700,15000,15200,15500,15700,16000,16200,16500,16700,17000,17200,17500,17700,18000,18200,18500,18700,19000,19200,19500,19700,20000,20200,20500,20700,21000,21200,21500,21700,22000,22200,22230,22260,22290,22320,22350,22380,22410,22440,22470,22500,22530,22560,22590,22620,22650,22680,22710,22740,22770,22800,22830,22860,22890,22920,22950,22980,23000,23010,23040,23070,23100,23130,23160,23190,23220,23250,23280,23310,23340,23370,23400,23430,23460,23490,23500,23520,23550,23580,23610,23640,23670,23700,23730,23760,23790,23820,23850,23880,23910,23940,23970,24000,24030,24060,24090,24120,24150,24180,24210,24240,24270,24300,24330,24360,24390,24420,24450,24480,24510,24540,24570,24600,24630,24660,24690,24720,24750,24780,24810,24840,24870,24900,24930,24960,24990,25020,25050,25080,25110,25140,25170,25200,25230,25260,25290,25320,25350,25380,25410,25440,25470,25500,25530,25560,25590,25620,25650,25680,25710,25740,25770,25800,25830,25860,25890,25920,25950,25980,26010,26040,26070,26100,26130,26160,26190,26220,26250,26280,26310,26340,26370,26400,26430,26460,26490,26520,26550,26580,26610,26640,26670,26700,26730,26760,26790,26820,26850,26880,26910,26940,26970,27000,27030,27060,27090,27120,27150,27180,27210,27240,27270,27300,27330,27360,27390,27420,27450,27480,27510,27540,27570,27600,27630,27660,27690,27720,27750,27780,27810,27840,27870,27900,27930,27960,27990,28020,28050,28080,28110,28140,28170,28200,28230,28260,28290,28320,28350,28380,28410,28440,28470,28500,28530,28560,28590,28620,28650,28680,28710,28740,28770,28800,28830,28860,28890,28920,28950,28980,29010,29040,29070,29100,29130,29160,29190,29220,29250,29280,29310,29340,29370,29400,29430,29460,29490,29520,29550,29580,29610,29640,29670,29700,29730,29760,29790,29820,29850,29880,29910,29940,29970,30000,30030,30060,30090,30120,30150,30180,30210,30240,30270,30300,30330,30360,30390,30420,30450,30480,30510,30540,30570,30600,30630,30660,30690,30720,30750,30780,30810,30840,30870,30900,30930,30960,30990,31020,31050,31080,31110,31140,31170,31200,31230,31260,31290,31320,31350,31380,31410,31440,31470,31500,31530,31560,31590,31620,31650,31680,31710,31740,31770,31800,31830,31860,31890,31920,31950,31980,32010,32040,32070,32100,32130,32160,32190,32220,32250,32280,32310,32340,32370,32400,32430,32460,32490,32520,32550,32580,32610,32640,32670,32700,32730,32760,32790,32820,32850,32880,32910,32940,32970,33000,33030,33060,33090,33120,33150,33180,33210,33240,33270,33300,33330,33360,33390,33420,33450,33480,33510,33540,33570,33600,33630,33660,33690,33720,33750,33780,33810,33840,33870,33900,33930,33960,33990,34020,34050,34080,34110,34140,34170,34200,34230,34260,34290,34320,34350,34380,34410,34440,34470,34500,34530,34560,34590,34620,34650,34680,34710,34740,34770,34800,34830,34860,34890,34920,34950,34980,35010,35040,35070,35100,35130,35160,35190,35220,35250,35280,35310,35340,35370,35400,35430,35460,35490,35520,35550,35580,35610,35640,35670,35700,35730,35760,35790,35820,35850,35880,35910,35940,35970,36000,36030,36060,36090,36120,36150,36180,36210,36240,36270,36300,36330,36360,36390,36420,36450,36480,36510,36540,36570,36600,36630,36660,36690,36720,36750,36780,36810,36840,36870,36900,36930,36960,36990,37020,37050,37080,37110,37140,37170,37200,37230,37260,37290,37320,37350,37380,37410,37440,37470,37500,37530,37560,37590,37620,37650,37680,37710,37740,37770,37800,37830,37860,37890,37920,37950,37980,38010,38040,38070,38100,38130,38160,38190,38220,38250,38280,38310,38340,38370,38400,38430,38460,38490,38520,38550,38580,38610,38640,38670,38700,38730,38760,38790,38820,38850,38880,38910,38940,38970,39000,39030,39060,39090,39120,39150,39180,39210,39240,39270,39300,39330,39360,39390,39420,39450,39480,39510,39540,39570,39600,39630,39660,39690,39720,39750,39780,39810,39840,39870,39900,39930,39960,39990,40020,40050,40080,40110,40140,40170,40200,40230,40260,40290,40320,40350,40380,40410,40440,40470,40500,40530,40560,40590,40620,40650,40680,40710,40740,40770,40800,40830,40860,40890,40920,40950,40980,41010,41040,41070,41100,41130,41160,41190,41220,41250,41280,41310,41340,41370,41400,41430,41460,41490,41520,41550,41580,41610,41640,41670,41700,41730,41760,41790,41820,41850,41880,41910,41940,41970,42000,42030,42060,42090,42120,42150,42180,42210,42240,42270,42300,42330,42360,42390,42420,42450,42480,42510,42540,42570,42600,42630,42660,42690,42720,42750,42780,42810,42840,42870,42900,42930,42960,42990,43020,43050,43080,43110,43140,43170,43200,43230,43260,43290,43320,43350,43380,43410,43440,43470,43500,43530,43560,43590,43620,43650,43680,43710,43740,43770,43800,43830,43860,43890,43920,43950,43980,44010,44040,44070,44100,44130,44160,44190,44220,44250,44280,44310,44340,44370,44400,44430,44460,44490,44520,44550,44580,44610,44640,44670,44700,44730,44760,44790,44820,44850,44880,44910,44940,44970,45000,45030,45060,45090,45120,45150,45180,45210,45240,45270,45300,45330,45360,45390,45420,45450,45480,45510,45540,45570,45600,45630,45660,45690,45720,45750,45780,45810,45840,45870,45900,45930,45960,45990,46020,46050,46080,46110,46140,46170,46200,46230,46260,46290,46320,46350,46380,46410,46440,46470,46500,46530,46560,46590,46620,46650,46680,46710,46740,46770,46800,46830,46860,46890,46920,46950,46980,47010,47040,47070,47100,47130,47160,47190,47220,47250,47280,47310,47340,47370,47400,47430,47460,47490,47520,47550,47580,47610,47640,47670,47700,47730,47760,47790,47820,47850,47880,47910,47940,47970,48000,48030,48060,48090,48120,48150,48180,48210,48240,48270,48300,48330,48360,48390,48420,48450,48480,48510,48540,48570,48600,48630,48660,48690,48720,48750,48780,48810,48840,48870,48900,48930,48960,48990,49020,49050,49080,49110,49140,49170,49200,49230,49260,49290,49320,49350,49380,49410,49440,49470,49500,49530,49560,49590,49620,49650,49680,49710,49740,49770,49800,49830,49860,49890,49920,49950,49980,50010,50040,50070,50100,50130,50160,50190,50220,50250,50280,50310,50340,50370,50400,50430,50460,50490,50520,50550,50580,50610,50640,50670,50700,50730,50760,50790,50820,50850,50880,50910,50940,50970,51000,51030,51060,51090,51120,51150,51180,51210,51240,51270,51300,51330,51360,51390,51420,51450,51480,51510,51540,51570,51600,51630,51660,51690,51720,51750,51780,51810,51840,51870,51900,51930,51960,51990,52020,52050,52080,52110,52140,52170,52200,52230,52260,52290,52320,52350,52380,52410,52440,52470,52500,52530,52560,52590,52620,52650,52680,52710,52740,52770,52800,52830,52860,52890,52920,52950,52980,53010,53040,53070,53100,53130,53160,53190,53220,53250,53280,53310,53340,53370,53400,53430,53460,53490,53520,53550,53580,53610,53640,53670,53700,53730,53760,53790,53820,53850,53880,53910,53940,53970,54000,54030,54060,54090,54120,54150,54180,54210,54240,54270,54300,54330,54360,54390,54420,54450,54480,54510,54540,54570,54600,54630,54660,54690,54720,54750,54780,54810,54840,54870,54900,54930,54960,54990,55020,55050,55080,55110,55140,55170,55200,55230,55260,55290,55320,55350,55380,55410,55440,55470,55500,55530,55560,55590,55620,55650,55680,55710,55740,55770,55800,55830,55860,55890,55920,55950,55980,56010,56040,56070,56100,56130,56160,56190,56220,56250,56280,56310,56340,56370,56400,56430,56460,56490,56520,56550,56580,56610,56640,56670,56700,56730,56760,56790,56820,56850,56880,56910,56940,56970,57000,57030,57060,57090,57120,57150,57180,57210,57240,57270,57300,57330,57360,57390,57420,57450,57480,57510,57540,57570,57600,57630,57660,57690,57720,57750,57780,57810,57840,57870,57900,57930,57960,57990,58020,58050,58080,58110,58140,58170,58200,58230,58260,58290,58320,58350,58380,58410,58440,58470,58500,58530,58560,58590,58620,58650,58680,58710,58740,58770,58800,58830,58860,58890,58920,58950,58980,59010,59040,59070,59100,59130,59160,59190,59220,59250,59280,59310,59340,59370,59400,59430,59460,59490,59520,59550,59580,59610,59640,59670,59700,59730,59760,59790,59820,59850,59880,59910,59940,59970,60000,60030,60060,60090,60120,60150,60180,60210,60240,60270,60300,60330,60360,60390,60420,60450,60480,60510,60540,60570,60600,60630,60660,60690,60720,60750,60780,60810,60840,60870,60900,60930,60960,60990,61020,61050,61080,61110,61140,61170,61200,61230,61260,61290,61320,61350,61380,61410,61440,61470,61500,61530,61560,61590,61620,61650,61680,61710,61740,61770,61800,61830,61860,61890,61920,61950,61980};
    _paFrame_NextEvent = new frame[1419];
    memcpy(_paFrame_NextEvent, f, sizeof(f));
    _event_num = 1419;
    orderActorToFactory(40000000, EnemyAstraea, "Astraea_1");

    orderActorToFactory(40000002, FormationPallas001a, "F001a_Pallas_2");
    orderActorToFactory(40000003, FormationPallas001b, "F001b_Pallas_3");
    orderActorToFactory(40000004, FormationPallas001c, "F001c_Pallas_4");
    orderActorToFactory(40000005, FormationPallas001d, "F001d_Pallas_5");
    orderActorToFactory(40000006, FormationPallas001a, "F001a_Pallas_6");
    orderActorToFactory(40000007, FormationPallas001d, "F001d_Pallas_7");
    orderActorToFactory(40000008, FormationPallas001b, "F001b_Pallas_8");
    orderActorToFactory(40000009, FormationPallas001c, "F001c_Pallas_9");
    orderActorToFactory(40000010, FormationPallas001a, "F001a_Pallas_10");
    orderActorToFactory(40000011, FormationPallas001d, "F001d_Pallas_11");
    orderActorToFactory(40000012, FormationPallas001b, "F001b_Pallas_12");
    orderActorToFactory(40000013, FormationPallas001c, "F001c_Pallas_13");
    orderActorToFactory(40000014, EnemyAstraea, "Astraea_14");
    orderActorToFactory(40000015, EnemyAstraea, "Astraea_15");
    orderActorToFactory(40000021, EnemyMetis, "Metis_16");
    orderActorToFactory(40000022, EnemyMetis, "Metis_17");
    // gen01 end
}

void Stage01_02::initialize() {

}

void Stage01_02::processBehavior() {
    // 以下の gen02 start ～ end はExcelマクロにより自動生成されたコードです。
    // コードの変更は「シーンCreater.xls」から行う事とする（整合性確保のため）。
    // gen02 start
    if (getActivePartFrame() == _paFrame_NextEvent[_iCnt_Event]) {
        switch (getActivePartFrame()) {
            case 1: {
                break;
            }
            case 100: {
                EnemyAstraea* pAstraea = (EnemyAstraea*)obtainActorFromFactory(40000000);
                getDirector()->addSubGroup(pAstraea);
                pAstraea->_Z = -1800000;
                pAstraea->_Y = -100000;
                {
                FormationTableScene* ta = NEW FormationTableScene("FormationTable_40000001");
                ta->setMaxPerformFrame(2500);
                addSubLast(ta);
                ta->addToTable(((FormationPallas001a*)obtainActorFromFactory(40000002)), 400);
                ta->addToTable(((FormationPallas001b*)obtainActorFromFactory(40000003)), 400);
                ta->addToTable(((FormationPallas001c*)obtainActorFromFactory(40000004)), 400);
                ta->addToTable(((FormationPallas001d*)obtainActorFromFactory(40000005)), 400);
                ta->addToTable(((FormationPallas001a*)obtainActorFromFactory(40000006)), 1);
                ta->addToTable(((FormationPallas001d*)obtainActorFromFactory(40000007)), 400);
                ta->addToTable(((FormationPallas001b*)obtainActorFromFactory(40000008)), 1);
                ta->addToTable(((FormationPallas001c*)obtainActorFromFactory(40000009)), 400);
                ta->addToTable(((FormationPallas001a*)obtainActorFromFactory(40000010)), 1);
                ta->addToTable(((FormationPallas001d*)obtainActorFromFactory(40000011)), 1);
                ta->addToTable(((FormationPallas001b*)obtainActorFromFactory(40000012)), 1);
                ta->addToTable(((FormationPallas001c*)obtainActorFromFactory(40000013)), 400);
                }
                break;
            }
            case 200: {
                orderActorToFactory(40000023, EnemyMetis, "Metis_18");
                orderActorToFactory(40001339, FormationThalia, "FormationThalia_19");
                break;
            }
            case 500: {
                EnemyAstraea* pAstraea2 = (EnemyAstraea*)obtainActorFromFactory(40000014);
                getDirector()->addSubGroup(pAstraea2);
                pAstraea2->_Z = -1800000;
                pAstraea2->_Y = -100000;
                break;
            }
            case 700: {
                orderActorToFactory(40000016, EnemyAstraea, "Astraea_20");
                orderActorToFactory(40000024, EnemyMetis, "Metis_21");
                break;
            }
            case 1000: {
                EnemyMetis* pMetis1 = (EnemyMetis*)obtainActorFromFactory(40000021);
                getDirector()->addSubGroup(pMetis1);
                break;
            }
            case 1200: {
                orderActorToFactory(40000017, VarietyTorus001, "VarietyTorus001_22");
                orderActorToFactory(40000025, EnemyMetis, "Metis_23");
                break;
            }
            case 1500: {
                EnemyAstraea* pAstraea2 = (EnemyAstraea*)obtainActorFromFactory(40000015);
                getDirector()->addSubGroup(pAstraea2);
                pAstraea2->_Z = -1800000;
                pAstraea2->_Y = -100000;
                EnemyMetis* pMetis1 = (EnemyMetis*)obtainActorFromFactory(40000022);
                getDirector()->addSubGroup(pMetis1);
                break;
            }
            case 1700: {
                orderActorToFactory(40000026, EnemyMetis, "Metis_24");
                break;
            }
            case 2000: {
                EnemyMetis* pMetis1 = (EnemyMetis*)obtainActorFromFactory(40000023);
                getDirector()->addSubGroup(pMetis1);
                FormationThalia* pF = (FormationThalia*)obtainActorFromFactory(40001339);
                getDirector()->addSubGroup(pF);
                break;
            }
            case 2200: {
                orderActorToFactory(40000027, EnemyMetis, "Metis_25");
                orderActorToFactory(40001337, FormationIris002, "F002_Iris_26");
                break;
            }
            case 2500: {
                EnemyAstraea* pAstraea2 = (EnemyAstraea*)obtainActorFromFactory(40000016);
                getDirector()->addSubGroup(pAstraea2);
                pAstraea2->_Z = -1800000;
                pAstraea2->_Y = -100000;
                EnemyMetis* pMetis1 = (EnemyMetis*)obtainActorFromFactory(40000024);
                getDirector()->addSubGroup(pMetis1);
                break;
            }
            case 2700: {
                orderActorToFactory(40000028, EnemyMetis, "Metis_27");
                orderActorToFactory(40001338, FormationIris002, "F002_Iris_28");
                break;
            }
            case 3000: {
                VarietyTorus001* pTorus = (VarietyTorus001*)obtainActorFromFactory(40000017);
                getDirector()->addSubGroup(pTorus);
                EnemyMetis* pMetis1 = (EnemyMetis*)obtainActorFromFactory(40000025);
                getDirector()->addSubGroup(pMetis1);
                break;
            }
            case 3200: {
                orderActorToFactory(40000029, EnemyMetis, "Metis_29");
                orderActorToFactory(40001335, FormationJuno001, "F002_Juno_30");
                break;
            }
            case 3500: {
                EnemyMetis* pMetis1 = (EnemyMetis*)obtainActorFromFactory(40000026);
                getDirector()->addSubGroup(pMetis1);
                break;
            }
            case 3700: {
                orderActorToFactory(40000030, EnemyMetis, "Metis_31");
                break;
            }
            case 4000: {
                EnemyMetis* pMetis1 = (EnemyMetis*)obtainActorFromFactory(40000027);
                getDirector()->addSubGroup(pMetis1);
                FormationIris002* pF1 = (FormationIris002*)obtainActorFromFactory(40001337);
                getDirector()->addSubGroup(pF1);
                break;
            }
            case 4200: {
                orderActorToFactory(40000031, EnemyMetis, "Metis_32");
                break;
            }
            case 4500: {
                EnemyMetis* pMetis1 = (EnemyMetis*)obtainActorFromFactory(40000028);
                getDirector()->addSubGroup(pMetis1);
                FormationIris002* pF2 = (FormationIris002*)obtainActorFromFactory(40001338);
                getDirector()->addSubGroup(pF2);
                break;
            }
            case 4700: {
                orderActorToFactory(40000032, EnemyMetis, "Metis_33");
                break;
            }
            case 5000: {
                EnemyMetis* pMetis1 = (EnemyMetis*)obtainActorFromFactory(40000029);
                getDirector()->addSubGroup(pMetis1);
                FormationJuno001* pF = (FormationJuno001*)obtainActorFromFactory(40001335);
                getDirector()->addSubGroup(pF);
                break;
            }
            case 5200: {
                orderActorToFactory(40000033, EnemyMetis, "Metis_34");
                break;
            }
            case 5500: {
                EnemyMetis* pMetis1 = (EnemyMetis*)obtainActorFromFactory(40000030);
                getDirector()->addSubGroup(pMetis1);
                break;
            }
            case 5700: {
                orderActorToFactory(40000034, EnemyMetis, "Metis_35");
                break;
            }
            case 6000: {
                EnemyMetis* pMetis1 = (EnemyMetis*)obtainActorFromFactory(40000031);
                getDirector()->addSubGroup(pMetis1);
                break;
            }
            case 6200: {
                orderActorToFactory(40000035, EnemyMetis, "Metis_36");
                break;
            }
            case 6500: {
                EnemyMetis* pMetis1 = (EnemyMetis*)obtainActorFromFactory(40000032);
                getDirector()->addSubGroup(pMetis1);
                break;
            }
            case 6700: {
                orderActorToFactory(40000036, EnemyMetis, "Metis_37");
                break;
            }
            case 7000: {
                EnemyMetis* pMetis1 = (EnemyMetis*)obtainActorFromFactory(40000033);
                getDirector()->addSubGroup(pMetis1);
                break;
            }
            case 7200: {
                orderActorToFactory(40000037, EnemyMetis, "Metis_38");
                break;
            }
            case 7500: {
                EnemyMetis* pMetis1 = (EnemyMetis*)obtainActorFromFactory(40000034);
                getDirector()->addSubGroup(pMetis1);
                break;
            }
            case 7700: {
                orderActorToFactory(40000038, EnemyMetis, "Metis_39");
                break;
            }
            case 8000: {
                EnemyMetis* pMetis1 = (EnemyMetis*)obtainActorFromFactory(40000035);
                getDirector()->addSubGroup(pMetis1);
                break;
            }
            case 8200: {
                orderActorToFactory(40000018, VarietyTorus002, "VarietyTorus002_40");
                orderActorToFactory(40000019, VarietyTorus003, "VarietyTorus003_41");
                orderActorToFactory(40000039, EnemyMetis, "Metis_42");
                break;
            }
            case 8500: {
                EnemyMetis* pMetis1 = (EnemyMetis*)obtainActorFromFactory(40000036);
                getDirector()->addSubGroup(pMetis1);
                break;
            }
            case 8700: {
                orderActorToFactory(40000040, EnemyMetis, "Metis_43");
                break;
            }
            case 9000: {
                EnemyMetis* pMetis1 = (EnemyMetis*)obtainActorFromFactory(40000037);
                getDirector()->addSubGroup(pMetis1);
                break;
            }
            case 9200: {
                orderActorToFactory(40000041, EnemyMetis, "Metis_44");
                break;
            }
            case 9500: {
                EnemyMetis* pMetis1 = (EnemyMetis*)obtainActorFromFactory(40000038);
                getDirector()->addSubGroup(pMetis1);
                break;
            }
            case 9700: {
                orderActorToFactory(40000042, EnemyMetis, "Metis_45");
                break;
            }
            case 10000: {
                VarietyTorus002* pTorusA = (VarietyTorus002*)obtainActorFromFactory(40000018);
                getDirector()->addSubGroup(pTorusA);
                VarietyTorus003* pTorusB = (VarietyTorus003*)obtainActorFromFactory(40000019);
                getDirector()->addSubGroup(pTorusB);
                EnemyMetis* pMetis1 = (EnemyMetis*)obtainActorFromFactory(40000039);
                getDirector()->addSubGroup(pMetis1);
                break;
            }
            case 10200: {
                orderActorToFactory(40000043, EnemyMetis, "Metis_46");
                break;
            }
            case 10500: {
                EnemyMetis* pMetis1 = (EnemyMetis*)obtainActorFromFactory(40000040);
                getDirector()->addSubGroup(pMetis1);
                break;
            }
            case 10700: {
                orderActorToFactory(40000044, EnemyMetis, "Metis_47");
                break;
            }
            case 11000: {
                EnemyMetis* pMetis1 = (EnemyMetis*)obtainActorFromFactory(40000041);
                getDirector()->addSubGroup(pMetis1);
                break;
            }
            case 11200: {
                orderActorToFactory(40000045, EnemyMetis, "Metis_48");
                orderActorToFactory(40001336, FormationJuno001, "F002_Juno_49");
                break;
            }
            case 11500: {
                EnemyMetis* pMetis1 = (EnemyMetis*)obtainActorFromFactory(40000042);
                getDirector()->addSubGroup(pMetis1);
                break;
            }
            case 11700: {
                orderActorToFactory(40000046, EnemyMetis, "Metis_50");
                break;
            }
            case 12000: {
                EnemyMetis* pMetis1 = (EnemyMetis*)obtainActorFromFactory(40000043);
                getDirector()->addSubGroup(pMetis1);
                break;
            }
            case 12200: {
                orderActorToFactory(40000047, EnemyMetis, "Metis_51");
                break;
            }
            case 12500: {
                EnemyMetis* pMetis1 = (EnemyMetis*)obtainActorFromFactory(40000044);
                getDirector()->addSubGroup(pMetis1);
                break;
            }
            case 12700: {
                orderActorToFactory(40000048, EnemyMetis, "Metis_52");
                break;
            }
            case 13000: {
                EnemyMetis* pMetis1 = (EnemyMetis*)obtainActorFromFactory(40000045);
                getDirector()->addSubGroup(pMetis1);
                FormationJuno001* pF = (FormationJuno001*)obtainActorFromFactory(40001336);
                getDirector()->addSubGroup(pF);
                break;
            }
            case 13200: {
                orderActorToFactory(40000049, EnemyMetis, "Metis_53");
                break;
            }
            case 13500: {
                EnemyMetis* pMetis1 = (EnemyMetis*)obtainActorFromFactory(40000046);
                getDirector()->addSubGroup(pMetis1);
                break;
            }
            case 13700: {
                orderActorToFactory(40000050, EnemyMetis, "Metis_54");
                break;
            }
            case 14000: {
                EnemyMetis* pMetis1 = (EnemyMetis*)obtainActorFromFactory(40000047);
                getDirector()->addSubGroup(pMetis1);
                break;
            }
            case 14200: {
                orderActorToFactory(40000051, EnemyMetis, "Metis_55");
                break;
            }
            case 14500: {
                EnemyMetis* pMetis1 = (EnemyMetis*)obtainActorFromFactory(40000048);
                getDirector()->addSubGroup(pMetis1);
                break;
            }
            case 14700: {
                orderActorToFactory(40000052, EnemyMetis, "Metis_56");
                break;
            }
            case 15000: {
                EnemyMetis* pMetis1 = (EnemyMetis*)obtainActorFromFactory(40000049);
                getDirector()->addSubGroup(pMetis1);
                break;
            }
            case 15200: {
                orderActorToFactory(40000053, EnemyMetis, "Metis_57");
                orderActorToFactory(40001340, FormationThalia, "FormationThalia_58");
                break;
            }
            case 15500: {
                EnemyMetis* pMetis1 = (EnemyMetis*)obtainActorFromFactory(40000050);
                getDirector()->addSubGroup(pMetis1);
                break;
            }
            case 15700: {
                orderActorToFactory(40000054, EnemyMetis, "Metis_59");
                break;
            }
            case 16000: {
                EnemyMetis* pMetis1 = (EnemyMetis*)obtainActorFromFactory(40000051);
                getDirector()->addSubGroup(pMetis1);
                break;
            }
            case 16200: {
                orderActorToFactory(40000055, EnemyMetis, "Metis_60");
                break;
            }
            case 16500: {
                EnemyMetis* pMetis1 = (EnemyMetis*)obtainActorFromFactory(40000052);
                getDirector()->addSubGroup(pMetis1);
                break;
            }
            case 16700: {
                orderActorToFactory(40000056, EnemyMetis, "Metis_61");
                break;
            }
            case 17000: {
                EnemyMetis* pMetis1 = (EnemyMetis*)obtainActorFromFactory(40000053);
                getDirector()->addSubGroup(pMetis1);
                FormationThalia* pF = (FormationThalia*)obtainActorFromFactory(40001340);
                getDirector()->addSubGroup(pF);
                break;
            }
            case 17200: {
                orderActorToFactory(40000057, EnemyMetis, "Metis_62");
                orderActorToFactory(40001341, FormationThalia, "FormationThalia_63");
                break;
            }
            case 17500: {
                EnemyMetis* pMetis1 = (EnemyMetis*)obtainActorFromFactory(40000054);
                getDirector()->addSubGroup(pMetis1);
                break;
            }
            case 17700: {
                orderActorToFactory(40000058, EnemyMetis, "Metis_64");
                break;
            }
            case 18000: {
                EnemyMetis* pMetis1 = (EnemyMetis*)obtainActorFromFactory(40000055);
                getDirector()->addSubGroup(pMetis1);
                break;
            }
            case 18200: {
                orderActorToFactory(40000020, VarietyTorus004, "VarietyTorus004_65");
                orderActorToFactory(40000059, EnemyMetis, "Metis_66");
                break;
            }
            case 18500: {
                EnemyMetis* pMetis1 = (EnemyMetis*)obtainActorFromFactory(40000056);
                getDirector()->addSubGroup(pMetis1);
                break;
            }
            case 18700: {
                orderActorToFactory(40000060, EnemyMetis, "Metis_67");
                break;
            }
            case 19000: {
                EnemyMetis* pMetis1 = (EnemyMetis*)obtainActorFromFactory(40000057);
                getDirector()->addSubGroup(pMetis1);
                FormationThalia* pF = (FormationThalia*)obtainActorFromFactory(40001341);
                getDirector()->addSubGroup(pF);
                break;
            }
            case 19200: {
                orderActorToFactory(40000061, EnemyMetis, "Metis_68");
                break;
            }
            case 19500: {
                EnemyMetis* pMetis1 = (EnemyMetis*)obtainActorFromFactory(40000058);
                getDirector()->addSubGroup(pMetis1);
                break;
            }
            case 19700: {
                orderActorToFactory(40000062, EnemyMetis, "Metis_69");
                break;
            }
            case 20000: {
                VarietyTorus004* pTorus = (VarietyTorus004*)obtainActorFromFactory(40000020);
                getDirector()->addSubGroup(pTorus);
                EnemyMetis* pMetis1 = (EnemyMetis*)obtainActorFromFactory(40000059);
                getDirector()->addSubGroup(pMetis1);
                break;
            }
            case 20200: {
                orderActorToFactory(40000063, EnemyMetis, "Metis_70");
                break;
            }
            case 20500: {
                EnemyMetis* pMetis1 = (EnemyMetis*)obtainActorFromFactory(40000060);
                getDirector()->addSubGroup(pMetis1);
                break;
            }
            case 20700: {
                orderActorToFactory(40000064, EnemyMetis, "Metis_71");
                break;
            }
            case 21000: {
                EnemyMetis* pMetis1 = (EnemyMetis*)obtainActorFromFactory(40000061);
                getDirector()->addSubGroup(pMetis1);
                break;
            }
            case 21200: {
                orderActorToFactory(40000065, EnemyMetis, "Metis_72");
                break;
            }
            case 21500: {
                EnemyMetis* pMetis1 = (EnemyMetis*)obtainActorFromFactory(40000062);
                getDirector()->addSubGroup(pMetis1);
                break;
            }
            case 21700: {
                orderActorToFactory(40000066, EnemyMetis, "Metis_73");
                break;
            }
            case 22000: {
                EnemyMetis* pMetis1 = (EnemyMetis*)obtainActorFromFactory(40000063);
                getDirector()->addSubGroup(pMetis1);
                break;
            }
            case 22200: {
                orderActorToFactory(40000067, EnemyMetis, "Metis_74");
                orderActorToFactory(40000068, EnemyMetis, "Metis_75");
                break;
            }
            case 22230: {
                orderActorToFactory(40000069, EnemyMetis, "Metis_76");
                break;
            }
            case 22260: {
                orderActorToFactory(40000070, EnemyMetis, "Metis_77");
                break;
            }
            case 22290: {
                orderActorToFactory(40000071, EnemyMetis, "Metis_78");
                break;
            }
            case 22320: {
                orderActorToFactory(40000072, EnemyMetis, "Metis_79");
                break;
            }
            case 22350: {
                orderActorToFactory(40000073, EnemyMetis, "Metis_80");
                break;
            }
            case 22380: {
                orderActorToFactory(40000074, EnemyMetis, "Metis_81");
                break;
            }
            case 22410: {
                orderActorToFactory(40000075, EnemyMetis, "Metis_82");
                break;
            }
            case 22440: {
                orderActorToFactory(40000076, EnemyMetis, "Metis_83");
                break;
            }
            case 22470: {
                orderActorToFactory(40000077, EnemyMetis, "Metis_84");
                break;
            }
            case 22500: {
                EnemyMetis* pMetis1 = (EnemyMetis*)obtainActorFromFactory(40000064);
                getDirector()->addSubGroup(pMetis1);
                orderActorToFactory(40000078, EnemyMetis, "Metis_85");
                break;
            }
            case 22530: {
                orderActorToFactory(40000079, EnemyMetis, "Metis_86");
                break;
            }
            case 22560: {
                orderActorToFactory(40000080, EnemyMetis, "Metis_87");
                break;
            }
            case 22590: {
                orderActorToFactory(40000081, EnemyMetis, "Metis_88");
                break;
            }
            case 22620: {
                orderActorToFactory(40000082, EnemyMetis, "Metis_89");
                break;
            }
            case 22650: {
                orderActorToFactory(40000083, EnemyMetis, "Metis_90");
                break;
            }
            case 22680: {
                orderActorToFactory(40000084, EnemyMetis, "Metis_91");
                break;
            }
            case 22710: {
                orderActorToFactory(40000085, EnemyMetis, "Metis_92");
                break;
            }
            case 22740: {
                orderActorToFactory(40000086, EnemyMetis, "Metis_93");
                break;
            }
            case 22770: {
                orderActorToFactory(40000087, EnemyMetis, "Metis_94");
                break;
            }
            case 22800: {
                orderActorToFactory(40000088, EnemyMetis, "Metis_95");
                break;
            }
            case 22830: {
                orderActorToFactory(40000089, EnemyMetis, "Metis_96");
                break;
            }
            case 22860: {
                orderActorToFactory(40000090, EnemyMetis, "Metis_97");
                break;
            }
            case 22890: {
                orderActorToFactory(40000091, EnemyMetis, "Metis_98");
                break;
            }
            case 22920: {
                orderActorToFactory(40000092, EnemyMetis, "Metis_99");
                break;
            }
            case 22950: {
                orderActorToFactory(40000093, EnemyMetis, "Metis_100");
                break;
            }
            case 22980: {
                orderActorToFactory(40000094, EnemyMetis, "Metis_101");
                break;
            }
            case 23000: {
                EnemyMetis* pMetis1 = (EnemyMetis*)obtainActorFromFactory(40000065);
                getDirector()->addSubGroup(pMetis1);
                break;
            }
            case 23010: {
                orderActorToFactory(40000095, EnemyMetis, "Metis_102");
                break;
            }
            case 23040: {
                orderActorToFactory(40000096, EnemyMetis, "Metis_103");
                break;
            }
            case 23070: {
                orderActorToFactory(40000097, EnemyMetis, "Metis_104");
                break;
            }
            case 23100: {
                orderActorToFactory(40000098, EnemyMetis, "Metis_105");
                break;
            }
            case 23130: {
                orderActorToFactory(40000099, EnemyMetis, "Metis_106");
                break;
            }
            case 23160: {
                orderActorToFactory(40000100, EnemyMetis, "Metis_107");
                break;
            }
            case 23190: {
                orderActorToFactory(40000101, EnemyMetis, "Metis_108");
                break;
            }
            case 23220: {
                orderActorToFactory(40000102, EnemyMetis, "Metis_109");
                break;
            }
            case 23250: {
                orderActorToFactory(40000103, EnemyMetis, "Metis_110");
                break;
            }
            case 23280: {
                orderActorToFactory(40000104, EnemyMetis, "Metis_111");
                break;
            }
            case 23310: {
                orderActorToFactory(40000105, EnemyMetis, "Metis_112");
                break;
            }
            case 23340: {
                orderActorToFactory(40000106, EnemyMetis, "Metis_113");
                break;
            }
            case 23370: {
                orderActorToFactory(40000107, EnemyMetis, "Metis_114");
                break;
            }
            case 23400: {
                orderActorToFactory(40000108, EnemyMetis, "Metis_115");
                break;
            }
            case 23430: {
                orderActorToFactory(40000109, EnemyMetis, "Metis_116");
                break;
            }
            case 23460: {
                orderActorToFactory(40000110, EnemyMetis, "Metis_117");
                break;
            }
            case 23490: {
                orderActorToFactory(40000111, EnemyMetis, "Metis_118");
                break;
            }
            case 23500: {
                EnemyMetis* pMetis1 = (EnemyMetis*)obtainActorFromFactory(40000066);
                getDirector()->addSubGroup(pMetis1);
                break;
            }
            case 23520: {
                orderActorToFactory(40000112, EnemyMetis, "Metis_119");
                break;
            }
            case 23550: {
                orderActorToFactory(40000113, EnemyMetis, "Metis_120");
                break;
            }
            case 23580: {
                orderActorToFactory(40000114, EnemyMetis, "Metis_121");
                break;
            }
            case 23610: {
                orderActorToFactory(40000115, EnemyMetis, "Metis_122");
                break;
            }
            case 23640: {
                orderActorToFactory(40000116, EnemyMetis, "Metis_123");
                break;
            }
            case 23670: {
                orderActorToFactory(40000117, EnemyMetis, "Metis_124");
                break;
            }
            case 23700: {
                orderActorToFactory(40000118, EnemyMetis, "Metis_125");
                break;
            }
            case 23730: {
                orderActorToFactory(40000119, EnemyMetis, "Metis_126");
                break;
            }
            case 23760: {
                orderActorToFactory(40000120, EnemyMetis, "Metis_127");
                break;
            }
            case 23790: {
                orderActorToFactory(40000121, EnemyMetis, "Metis_128");
                break;
            }
            case 23820: {
                orderActorToFactory(40000122, EnemyMetis, "Metis_129");
                break;
            }
            case 23850: {
                orderActorToFactory(40000123, EnemyMetis, "Metis_130");
                break;
            }
            case 23880: {
                orderActorToFactory(40000124, EnemyMetis, "Metis_131");
                break;
            }
            case 23910: {
                orderActorToFactory(40000125, EnemyMetis, "Metis_132");
                break;
            }
            case 23940: {
                orderActorToFactory(40000126, EnemyMetis, "Metis_133");
                break;
            }
            case 23970: {
                orderActorToFactory(40000127, EnemyMetis, "Metis_134");
                break;
            }
            case 24000: {
                EnemyMetis* pMetis1 = (EnemyMetis*)obtainActorFromFactory(40000067);
                getDirector()->addSubGroup(pMetis1);
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000068);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000128, EnemyMetis, "Metis_135");
                break;
            }
            case 24030: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000069);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000129, EnemyMetis, "Metis_136");
                break;
            }
            case 24060: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000070);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000130, EnemyMetis, "Metis_137");
                break;
            }
            case 24090: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000071);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000131, EnemyMetis, "Metis_138");
                break;
            }
            case 24120: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000072);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000132, EnemyMetis, "Metis_139");
                break;
            }
            case 24150: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000073);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000133, EnemyMetis, "Metis_140");
                break;
            }
            case 24180: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000074);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000134, EnemyMetis, "Metis_141");
                break;
            }
            case 24210: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000075);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000135, EnemyMetis, "Metis_142");
                break;
            }
            case 24240: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000076);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000136, EnemyMetis, "Metis_143");
                break;
            }
            case 24270: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000077);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000137, EnemyMetis, "Metis_144");
                break;
            }
            case 24300: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000078);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000138, EnemyMetis, "Metis_145");
                break;
            }
            case 24330: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000079);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000139, EnemyMetis, "Metis_146");
                break;
            }
            case 24360: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000080);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000140, EnemyMetis, "Metis_147");
                break;
            }
            case 24390: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000081);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000141, EnemyMetis, "Metis_148");
                break;
            }
            case 24420: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000082);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000142, EnemyMetis, "Metis_149");
                break;
            }
            case 24450: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000083);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000143, EnemyMetis, "Metis_150");
                break;
            }
            case 24480: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000084);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000144, EnemyMetis, "Metis_151");
                break;
            }
            case 24510: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000085);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000145, EnemyMetis, "Metis_152");
                break;
            }
            case 24540: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000086);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000146, EnemyMetis, "Metis_153");
                break;
            }
            case 24570: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000087);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000147, EnemyMetis, "Metis_154");
                break;
            }
            case 24600: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000088);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000148, EnemyMetis, "Metis_155");
                break;
            }
            case 24630: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000089);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000149, EnemyMetis, "Metis_156");
                break;
            }
            case 24660: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000090);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000150, EnemyMetis, "Metis_157");
                break;
            }
            case 24690: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000091);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000151, EnemyMetis, "Metis_158");
                break;
            }
            case 24720: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000092);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000152, EnemyMetis, "Metis_159");
                break;
            }
            case 24750: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000093);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000153, EnemyMetis, "Metis_160");
                break;
            }
            case 24780: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000094);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000154, EnemyMetis, "Metis_161");
                break;
            }
            case 24810: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000095);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000155, EnemyMetis, "Metis_162");
                break;
            }
            case 24840: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000096);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000156, EnemyMetis, "Metis_163");
                break;
            }
            case 24870: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000097);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000157, EnemyMetis, "Metis_164");
                break;
            }
            case 24900: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000098);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000158, EnemyMetis, "Metis_165");
                break;
            }
            case 24930: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000099);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000159, EnemyMetis, "Metis_166");
                break;
            }
            case 24960: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000100);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000160, EnemyMetis, "Metis_167");
                break;
            }
            case 24990: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000101);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000161, EnemyMetis, "Metis_168");
                break;
            }
            case 25020: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000102);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000162, EnemyMetis, "Metis_169");
                break;
            }
            case 25050: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000103);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000163, EnemyMetis, "Metis_170");
                break;
            }
            case 25080: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000104);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000164, EnemyMetis, "Metis_171");
                break;
            }
            case 25110: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000105);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000165, EnemyMetis, "Metis_172");
                break;
            }
            case 25140: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000106);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000166, EnemyMetis, "Metis_173");
                break;
            }
            case 25170: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000107);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000167, EnemyMetis, "Metis_174");
                break;
            }
            case 25200: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000108);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000168, EnemyMetis, "Metis_175");
                break;
            }
            case 25230: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000109);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000169, EnemyMetis, "Metis_176");
                break;
            }
            case 25260: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000110);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000170, EnemyMetis, "Metis_177");
                break;
            }
            case 25290: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000111);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000171, EnemyMetis, "Metis_178");
                break;
            }
            case 25320: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000112);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000172, EnemyMetis, "Metis_179");
                break;
            }
            case 25350: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000113);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000173, EnemyMetis, "Metis_180");
                break;
            }
            case 25380: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000114);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000174, EnemyMetis, "Metis_181");
                break;
            }
            case 25410: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000115);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000175, EnemyMetis, "Metis_182");
                break;
            }
            case 25440: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000116);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000176, EnemyMetis, "Metis_183");
                break;
            }
            case 25470: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000117);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000177, EnemyMetis, "Metis_184");
                break;
            }
            case 25500: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000118);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000178, EnemyMetis, "Metis_185");
                break;
            }
            case 25530: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000119);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000179, EnemyMetis, "Metis_186");
                break;
            }
            case 25560: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000120);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000180, EnemyMetis, "Metis_187");
                break;
            }
            case 25590: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000121);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000181, EnemyMetis, "Metis_188");
                break;
            }
            case 25620: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000122);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000182, EnemyMetis, "Metis_189");
                break;
            }
            case 25650: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000123);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000183, EnemyMetis, "Metis_190");
                break;
            }
            case 25680: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000124);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000184, EnemyMetis, "Metis_191");
                break;
            }
            case 25710: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000125);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000185, EnemyMetis, "Metis_192");
                break;
            }
            case 25740: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000126);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000186, EnemyMetis, "Metis_193");
                break;
            }
            case 25770: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000127);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000187, EnemyMetis, "Metis_194");
                break;
            }
            case 25800: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000128);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000188, EnemyMetis, "Metis_195");
                break;
            }
            case 25830: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000129);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000189, EnemyMetis, "Metis_196");
                break;
            }
            case 25860: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000130);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000190, EnemyMetis, "Metis_197");
                break;
            }
            case 25890: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000131);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000191, EnemyMetis, "Metis_198");
                break;
            }
            case 25920: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000132);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000192, EnemyMetis, "Metis_199");
                break;
            }
            case 25950: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000133);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000193, EnemyMetis, "Metis_200");
                break;
            }
            case 25980: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000134);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000194, EnemyMetis, "Metis_201");
                break;
            }
            case 26010: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000135);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000195, EnemyMetis, "Metis_202");
                break;
            }
            case 26040: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000136);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000196, EnemyMetis, "Metis_203");
                break;
            }
            case 26070: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000137);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000197, EnemyMetis, "Metis_204");
                break;
            }
            case 26100: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000138);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000198, EnemyMetis, "Metis_205");
                break;
            }
            case 26130: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000139);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000199, EnemyMetis, "Metis_206");
                break;
            }
            case 26160: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000140);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000200, EnemyMetis, "Metis_207");
                break;
            }
            case 26190: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000141);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000201, EnemyMetis, "Metis_208");
                break;
            }
            case 26220: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000142);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000202, EnemyMetis, "Metis_209");
                break;
            }
            case 26250: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000143);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000203, EnemyMetis, "Metis_210");
                break;
            }
            case 26280: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000144);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000204, EnemyMetis, "Metis_211");
                break;
            }
            case 26310: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000145);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000205, EnemyMetis, "Metis_212");
                break;
            }
            case 26340: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000146);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000206, EnemyMetis, "Metis_213");
                break;
            }
            case 26370: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000147);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000207, EnemyMetis, "Metis_214");
                break;
            }
            case 26400: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000148);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000208, EnemyMetis, "Metis_215");
                break;
            }
            case 26430: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000149);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000209, EnemyMetis, "Metis_216");
                break;
            }
            case 26460: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000150);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000210, EnemyMetis, "Metis_217");
                break;
            }
            case 26490: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000151);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000211, EnemyMetis, "Metis_218");
                break;
            }
            case 26520: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000152);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000212, EnemyMetis, "Metis_219");
                break;
            }
            case 26550: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000153);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000213, EnemyMetis, "Metis_220");
                break;
            }
            case 26580: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000154);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000214, EnemyMetis, "Metis_221");
                break;
            }
            case 26610: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000155);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000215, EnemyMetis, "Metis_222");
                break;
            }
            case 26640: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000156);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000216, EnemyMetis, "Metis_223");
                break;
            }
            case 26670: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000157);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000217, EnemyMetis, "Metis_224");
                break;
            }
            case 26700: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000158);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000218, EnemyMetis, "Metis_225");
                break;
            }
            case 26730: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000159);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000219, EnemyMetis, "Metis_226");
                break;
            }
            case 26760: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000160);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000220, EnemyMetis, "Metis_227");
                break;
            }
            case 26790: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000161);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000221, EnemyMetis, "Metis_228");
                break;
            }
            case 26820: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000162);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000222, EnemyMetis, "Metis_229");
                break;
            }
            case 26850: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000163);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000223, EnemyMetis, "Metis_230");
                break;
            }
            case 26880: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000164);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000224, EnemyMetis, "Metis_231");
                break;
            }
            case 26910: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000165);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000225, EnemyMetis, "Metis_232");
                break;
            }
            case 26940: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000166);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000226, EnemyMetis, "Metis_233");
                break;
            }
            case 26970: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000167);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000227, EnemyMetis, "Metis_234");
                break;
            }
            case 27000: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000168);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000228, EnemyMetis, "Metis_235");
                break;
            }
            case 27030: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000169);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000229, EnemyMetis, "Metis_236");
                break;
            }
            case 27060: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000170);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000230, EnemyMetis, "Metis_237");
                break;
            }
            case 27090: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000171);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000231, EnemyMetis, "Metis_238");
                break;
            }
            case 27120: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000172);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000232, EnemyMetis, "Metis_239");
                break;
            }
            case 27150: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000173);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000233, EnemyMetis, "Metis_240");
                break;
            }
            case 27180: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000174);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000234, EnemyMetis, "Metis_241");
                break;
            }
            case 27210: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000175);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000235, EnemyMetis, "Metis_242");
                break;
            }
            case 27240: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000176);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000236, EnemyMetis, "Metis_243");
                break;
            }
            case 27270: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000177);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000237, EnemyMetis, "Metis_244");
                break;
            }
            case 27300: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000178);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000238, EnemyMetis, "Metis_245");
                break;
            }
            case 27330: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000179);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000239, EnemyMetis, "Metis_246");
                break;
            }
            case 27360: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000180);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000240, EnemyMetis, "Metis_247");
                break;
            }
            case 27390: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000181);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000241, EnemyMetis, "Metis_248");
                break;
            }
            case 27420: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000182);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000242, EnemyMetis, "Metis_249");
                break;
            }
            case 27450: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000183);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000243, EnemyMetis, "Metis_250");
                break;
            }
            case 27480: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000184);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000244, EnemyMetis, "Metis_251");
                break;
            }
            case 27510: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000185);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000245, EnemyMetis, "Metis_252");
                break;
            }
            case 27540: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000186);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000246, EnemyMetis, "Metis_253");
                break;
            }
            case 27570: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000187);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000247, EnemyMetis, "Metis_254");
                break;
            }
            case 27600: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000188);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000248, EnemyMetis, "Metis_255");
                break;
            }
            case 27630: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000189);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000249, EnemyMetis, "Metis_256");
                break;
            }
            case 27660: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000190);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000250, EnemyMetis, "Metis_257");
                break;
            }
            case 27690: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000191);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000251, EnemyMetis, "Metis_258");
                break;
            }
            case 27720: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000192);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000252, EnemyMetis, "Metis_259");
                break;
            }
            case 27750: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000193);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000253, EnemyMetis, "Metis_260");
                break;
            }
            case 27780: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000194);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000254, EnemyMetis, "Metis_261");
                break;
            }
            case 27810: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000195);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000255, EnemyMetis, "Metis_262");
                break;
            }
            case 27840: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000196);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000256, EnemyMetis, "Metis_263");
                break;
            }
            case 27870: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000197);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000257, EnemyMetis, "Metis_264");
                break;
            }
            case 27900: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000198);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000258, EnemyMetis, "Metis_265");
                break;
            }
            case 27930: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000199);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000259, EnemyMetis, "Metis_266");
                break;
            }
            case 27960: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000200);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000260, EnemyMetis, "Metis_267");
                break;
            }
            case 27990: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000201);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000261, EnemyMetis, "Metis_268");
                break;
            }
            case 28020: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000202);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000262, EnemyMetis, "Metis_269");
                break;
            }
            case 28050: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000203);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000263, EnemyMetis, "Metis_270");
                break;
            }
            case 28080: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000204);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000264, EnemyMetis, "Metis_271");
                break;
            }
            case 28110: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000205);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000265, EnemyMetis, "Metis_272");
                break;
            }
            case 28140: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000206);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000266, EnemyMetis, "Metis_273");
                break;
            }
            case 28170: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000207);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000267, EnemyMetis, "Metis_274");
                break;
            }
            case 28200: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000208);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000268, EnemyMetis, "Metis_275");
                break;
            }
            case 28230: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000209);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000269, EnemyMetis, "Metis_276");
                break;
            }
            case 28260: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000210);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000270, EnemyMetis, "Metis_277");
                break;
            }
            case 28290: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000211);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000271, EnemyMetis, "Metis_278");
                break;
            }
            case 28320: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000212);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000272, EnemyMetis, "Metis_279");
                break;
            }
            case 28350: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000213);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000273, EnemyMetis, "Metis_280");
                break;
            }
            case 28380: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000214);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000274, EnemyMetis, "Metis_281");
                break;
            }
            case 28410: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000215);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000275, EnemyMetis, "Metis_282");
                break;
            }
            case 28440: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000216);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000276, EnemyMetis, "Metis_283");
                break;
            }
            case 28470: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000217);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000277, EnemyMetis, "Metis_284");
                break;
            }
            case 28500: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000218);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000278, EnemyMetis, "Metis_285");
                break;
            }
            case 28530: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000219);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000279, EnemyMetis, "Metis_286");
                break;
            }
            case 28560: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000220);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000280, EnemyMetis, "Metis_287");
                break;
            }
            case 28590: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000221);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000281, EnemyMetis, "Metis_288");
                break;
            }
            case 28620: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000222);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000282, EnemyMetis, "Metis_289");
                break;
            }
            case 28650: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000223);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000283, EnemyMetis, "Metis_290");
                break;
            }
            case 28680: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000224);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000284, EnemyMetis, "Metis_291");
                break;
            }
            case 28710: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000225);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000285, EnemyMetis, "Metis_292");
                break;
            }
            case 28740: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000226);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000286, EnemyMetis, "Metis_293");
                break;
            }
            case 28770: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000227);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000287, EnemyMetis, "Metis_294");
                break;
            }
            case 28800: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000228);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000288, EnemyMetis, "Metis_295");
                break;
            }
            case 28830: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000229);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000289, EnemyMetis, "Metis_296");
                break;
            }
            case 28860: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000230);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000290, EnemyMetis, "Metis_297");
                break;
            }
            case 28890: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000231);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000291, EnemyMetis, "Metis_298");
                break;
            }
            case 28920: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000232);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000292, EnemyMetis, "Metis_299");
                break;
            }
            case 28950: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000233);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000293, EnemyMetis, "Metis_300");
                break;
            }
            case 28980: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000234);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000294, EnemyMetis, "Metis_301");
                break;
            }
            case 29010: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000235);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000295, EnemyMetis, "Metis_302");
                break;
            }
            case 29040: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000236);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000296, EnemyMetis, "Metis_303");
                break;
            }
            case 29070: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000237);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000297, EnemyMetis, "Metis_304");
                break;
            }
            case 29100: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000238);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000298, EnemyMetis, "Metis_305");
                break;
            }
            case 29130: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000239);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000299, EnemyMetis, "Metis_306");
                break;
            }
            case 29160: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000240);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000300, EnemyMetis, "Metis_307");
                break;
            }
            case 29190: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000241);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000301, EnemyMetis, "Metis_308");
                break;
            }
            case 29220: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000242);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000302, EnemyMetis, "Metis_309");
                break;
            }
            case 29250: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000243);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000303, EnemyMetis, "Metis_310");
                break;
            }
            case 29280: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000244);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000304, EnemyMetis, "Metis_311");
                break;
            }
            case 29310: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000245);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000305, EnemyMetis, "Metis_312");
                break;
            }
            case 29340: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000246);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000306, EnemyMetis, "Metis_313");
                break;
            }
            case 29370: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000247);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000307, EnemyMetis, "Metis_314");
                break;
            }
            case 29400: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000248);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000308, EnemyMetis, "Metis_315");
                break;
            }
            case 29430: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000249);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000309, EnemyMetis, "Metis_316");
                break;
            }
            case 29460: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000250);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000310, EnemyMetis, "Metis_317");
                break;
            }
            case 29490: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000251);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000311, EnemyMetis, "Metis_318");
                break;
            }
            case 29520: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000252);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000312, EnemyMetis, "Metis_319");
                break;
            }
            case 29550: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000253);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000313, EnemyMetis, "Metis_320");
                break;
            }
            case 29580: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000254);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000314, EnemyMetis, "Metis_321");
                break;
            }
            case 29610: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000255);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000315, EnemyMetis, "Metis_322");
                break;
            }
            case 29640: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000256);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000316, EnemyMetis, "Metis_323");
                break;
            }
            case 29670: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000257);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000317, EnemyMetis, "Metis_324");
                break;
            }
            case 29700: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000258);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000318, EnemyMetis, "Metis_325");
                break;
            }
            case 29730: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000259);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000319, EnemyMetis, "Metis_326");
                break;
            }
            case 29760: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000260);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000320, EnemyMetis, "Metis_327");
                break;
            }
            case 29790: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000261);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000321, EnemyMetis, "Metis_328");
                break;
            }
            case 29820: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000262);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000322, EnemyMetis, "Metis_329");
                break;
            }
            case 29850: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000263);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000323, EnemyMetis, "Metis_330");
                break;
            }
            case 29880: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000264);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000324, EnemyMetis, "Metis_331");
                break;
            }
            case 29910: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000265);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000325, EnemyMetis, "Metis_332");
                break;
            }
            case 29940: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000266);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000326, EnemyMetis, "Metis_333");
                break;
            }
            case 29970: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000267);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000327, EnemyMetis, "Metis_334");
                break;
            }
            case 30000: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000268);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000328, EnemyMetis, "Metis_335");
                break;
            }
            case 30030: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000269);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000329, EnemyMetis, "Metis_336");
                break;
            }
            case 30060: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000270);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000330, EnemyMetis, "Metis_337");
                break;
            }
            case 30090: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000271);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000331, EnemyMetis, "Metis_338");
                break;
            }
            case 30120: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000272);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000332, EnemyMetis, "Metis_339");
                break;
            }
            case 30150: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000273);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000333, EnemyMetis, "Metis_340");
                break;
            }
            case 30180: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000274);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000334, EnemyMetis, "Metis_341");
                break;
            }
            case 30210: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000275);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000335, EnemyMetis, "Metis_342");
                break;
            }
            case 30240: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000276);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000336, EnemyMetis, "Metis_343");
                break;
            }
            case 30270: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000277);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000337, EnemyMetis, "Metis_344");
                break;
            }
            case 30300: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000278);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000338, EnemyMetis, "Metis_345");
                break;
            }
            case 30330: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000279);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000339, EnemyMetis, "Metis_346");
                break;
            }
            case 30360: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000280);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000340, EnemyMetis, "Metis_347");
                break;
            }
            case 30390: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000281);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000341, EnemyMetis, "Metis_348");
                break;
            }
            case 30420: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000282);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000342, EnemyMetis, "Metis_349");
                break;
            }
            case 30450: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000283);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000343, EnemyMetis, "Metis_350");
                break;
            }
            case 30480: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000284);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000344, EnemyMetis, "Metis_351");
                break;
            }
            case 30510: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000285);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000345, EnemyMetis, "Metis_352");
                break;
            }
            case 30540: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000286);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000346, EnemyMetis, "Metis_353");
                break;
            }
            case 30570: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000287);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000347, EnemyMetis, "Metis_354");
                break;
            }
            case 30600: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000288);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000348, EnemyMetis, "Metis_355");
                break;
            }
            case 30630: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000289);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000349, EnemyMetis, "Metis_356");
                break;
            }
            case 30660: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000290);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000350, EnemyMetis, "Metis_357");
                break;
            }
            case 30690: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000291);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000351, EnemyMetis, "Metis_358");
                break;
            }
            case 30720: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000292);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000352, EnemyMetis, "Metis_359");
                break;
            }
            case 30750: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000293);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000353, EnemyMetis, "Metis_360");
                break;
            }
            case 30780: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000294);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000354, EnemyMetis, "Metis_361");
                break;
            }
            case 30810: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000295);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000355, EnemyMetis, "Metis_362");
                break;
            }
            case 30840: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000296);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000356, EnemyMetis, "Metis_363");
                break;
            }
            case 30870: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000297);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000357, EnemyMetis, "Metis_364");
                break;
            }
            case 30900: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000298);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000358, EnemyMetis, "Metis_365");
                break;
            }
            case 30930: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000299);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000359, EnemyMetis, "Metis_366");
                break;
            }
            case 30960: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000300);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000360, EnemyMetis, "Metis_367");
                break;
            }
            case 30990: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000301);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000361, EnemyMetis, "Metis_368");
                break;
            }
            case 31020: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000302);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000362, EnemyMetis, "Metis_369");
                break;
            }
            case 31050: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000303);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000363, EnemyMetis, "Metis_370");
                break;
            }
            case 31080: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000304);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000364, EnemyMetis, "Metis_371");
                break;
            }
            case 31110: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000305);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000365, EnemyMetis, "Metis_372");
                break;
            }
            case 31140: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000306);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000366, EnemyMetis, "Metis_373");
                break;
            }
            case 31170: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000307);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000367, EnemyMetis, "Metis_374");
                break;
            }
            case 31200: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000308);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000368, EnemyMetis, "Metis_375");
                break;
            }
            case 31230: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000309);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000369, EnemyMetis, "Metis_376");
                break;
            }
            case 31260: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000310);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000370, EnemyMetis, "Metis_377");
                break;
            }
            case 31290: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000311);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000371, EnemyMetis, "Metis_378");
                break;
            }
            case 31320: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000312);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000372, EnemyMetis, "Metis_379");
                break;
            }
            case 31350: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000313);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000373, EnemyMetis, "Metis_380");
                break;
            }
            case 31380: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000314);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000374, EnemyMetis, "Metis_381");
                break;
            }
            case 31410: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000315);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000375, EnemyMetis, "Metis_382");
                break;
            }
            case 31440: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000316);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000376, EnemyMetis, "Metis_383");
                break;
            }
            case 31470: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000317);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000377, EnemyMetis, "Metis_384");
                break;
            }
            case 31500: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000318);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000378, EnemyMetis, "Metis_385");
                break;
            }
            case 31530: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000319);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000379, EnemyMetis, "Metis_386");
                break;
            }
            case 31560: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000320);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000380, EnemyMetis, "Metis_387");
                break;
            }
            case 31590: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000321);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000381, EnemyMetis, "Metis_388");
                break;
            }
            case 31620: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000322);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000382, EnemyMetis, "Metis_389");
                break;
            }
            case 31650: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000323);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000383, EnemyMetis, "Metis_390");
                break;
            }
            case 31680: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000324);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000384, EnemyMetis, "Metis_391");
                break;
            }
            case 31710: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000325);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000385, EnemyMetis, "Metis_392");
                break;
            }
            case 31740: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000326);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000386, EnemyMetis, "Metis_393");
                break;
            }
            case 31770: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000327);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000387, EnemyMetis, "Metis_394");
                break;
            }
            case 31800: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000328);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000388, EnemyMetis, "Metis_395");
                break;
            }
            case 31830: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000329);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000389, EnemyMetis, "Metis_396");
                break;
            }
            case 31860: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000330);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000390, EnemyMetis, "Metis_397");
                break;
            }
            case 31890: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000331);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000391, EnemyMetis, "Metis_398");
                break;
            }
            case 31920: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000332);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000392, EnemyMetis, "Metis_399");
                break;
            }
            case 31950: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000333);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000393, EnemyMetis, "Metis_400");
                break;
            }
            case 31980: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000334);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000394, EnemyMetis, "Metis_401");
                break;
            }
            case 32010: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000335);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000395, EnemyMetis, "Metis_402");
                break;
            }
            case 32040: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000336);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000396, EnemyMetis, "Metis_403");
                break;
            }
            case 32070: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000337);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000397, EnemyMetis, "Metis_404");
                break;
            }
            case 32100: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000338);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000398, EnemyMetis, "Metis_405");
                break;
            }
            case 32130: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000339);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000399, EnemyMetis, "Metis_406");
                break;
            }
            case 32160: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000340);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000400, EnemyMetis, "Metis_407");
                break;
            }
            case 32190: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000341);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000401, EnemyMetis, "Metis_408");
                break;
            }
            case 32220: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000342);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000402, EnemyMetis, "Metis_409");
                break;
            }
            case 32250: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000343);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000403, EnemyMetis, "Metis_410");
                break;
            }
            case 32280: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000344);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000404, EnemyMetis, "Metis_411");
                break;
            }
            case 32310: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000345);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000405, EnemyMetis, "Metis_412");
                break;
            }
            case 32340: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000346);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000406, EnemyMetis, "Metis_413");
                break;
            }
            case 32370: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000347);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000407, EnemyMetis, "Metis_414");
                break;
            }
            case 32400: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000348);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000408, EnemyMetis, "Metis_415");
                break;
            }
            case 32430: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000349);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000409, EnemyMetis, "Metis_416");
                break;
            }
            case 32460: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000350);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000410, EnemyMetis, "Metis_417");
                break;
            }
            case 32490: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000351);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000411, EnemyMetis, "Metis_418");
                break;
            }
            case 32520: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000352);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000412, EnemyMetis, "Metis_419");
                break;
            }
            case 32550: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000353);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000413, EnemyMetis, "Metis_420");
                break;
            }
            case 32580: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000354);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000414, EnemyMetis, "Metis_421");
                break;
            }
            case 32610: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000355);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000415, EnemyMetis, "Metis_422");
                break;
            }
            case 32640: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000356);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000416, EnemyMetis, "Metis_423");
                break;
            }
            case 32670: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000357);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000417, EnemyMetis, "Metis_424");
                break;
            }
            case 32700: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000358);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000418, EnemyMetis, "Metis_425");
                break;
            }
            case 32730: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000359);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000419, EnemyMetis, "Metis_426");
                break;
            }
            case 32760: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000360);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000420, EnemyMetis, "Metis_427");
                break;
            }
            case 32790: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000361);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000421, EnemyMetis, "Metis_428");
                break;
            }
            case 32820: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000362);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000422, EnemyMetis, "Metis_429");
                break;
            }
            case 32850: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000363);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000423, EnemyMetis, "Metis_430");
                break;
            }
            case 32880: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000364);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000424, EnemyMetis, "Metis_431");
                break;
            }
            case 32910: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000365);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000425, EnemyMetis, "Metis_432");
                break;
            }
            case 32940: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000366);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000426, EnemyMetis, "Metis_433");
                break;
            }
            case 32970: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000367);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000427, EnemyMetis, "Metis_434");
                break;
            }
            case 33000: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000368);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000428, EnemyMetis, "Metis_435");
                break;
            }
            case 33030: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000369);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000429, EnemyMetis, "Metis_436");
                break;
            }
            case 33060: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000370);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000430, EnemyMetis, "Metis_437");
                break;
            }
            case 33090: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000371);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000431, EnemyMetis, "Metis_438");
                break;
            }
            case 33120: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000372);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000432, EnemyMetis, "Metis_439");
                break;
            }
            case 33150: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000373);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000433, EnemyMetis, "Metis_440");
                break;
            }
            case 33180: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000374);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000434, EnemyMetis, "Metis_441");
                break;
            }
            case 33210: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000375);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000435, EnemyMetis, "Metis_442");
                break;
            }
            case 33240: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000376);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000436, EnemyMetis, "Metis_443");
                break;
            }
            case 33270: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000377);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000437, EnemyMetis, "Metis_444");
                break;
            }
            case 33300: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000378);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000438, EnemyMetis, "Metis_445");
                break;
            }
            case 33330: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000379);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000439, EnemyMetis, "Metis_446");
                break;
            }
            case 33360: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000380);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000440, EnemyMetis, "Metis_447");
                break;
            }
            case 33390: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000381);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000441, EnemyMetis, "Metis_448");
                break;
            }
            case 33420: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000382);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000442, EnemyMetis, "Metis_449");
                break;
            }
            case 33450: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000383);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000443, EnemyMetis, "Metis_450");
                break;
            }
            case 33480: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000384);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000444, EnemyMetis, "Metis_451");
                break;
            }
            case 33510: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000385);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000445, EnemyMetis, "Metis_452");
                break;
            }
            case 33540: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000386);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000446, EnemyMetis, "Metis_453");
                break;
            }
            case 33570: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000387);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000447, EnemyMetis, "Metis_454");
                break;
            }
            case 33600: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000388);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000448, EnemyMetis, "Metis_455");
                break;
            }
            case 33630: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000389);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000449, EnemyMetis, "Metis_456");
                break;
            }
            case 33660: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000390);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000450, EnemyMetis, "Metis_457");
                break;
            }
            case 33690: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000391);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000451, EnemyMetis, "Metis_458");
                break;
            }
            case 33720: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000392);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000452, EnemyMetis, "Metis_459");
                break;
            }
            case 33750: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000393);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000453, EnemyMetis, "Metis_460");
                break;
            }
            case 33780: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000394);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000454, EnemyMetis, "Metis_461");
                break;
            }
            case 33810: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000395);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000455, EnemyMetis, "Metis_462");
                break;
            }
            case 33840: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000396);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000456, EnemyMetis, "Metis_463");
                break;
            }
            case 33870: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000397);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000457, EnemyMetis, "Metis_464");
                break;
            }
            case 33900: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000398);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000458, EnemyMetis, "Metis_465");
                break;
            }
            case 33930: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000399);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000459, EnemyMetis, "Metis_466");
                break;
            }
            case 33960: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000400);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000460, EnemyMetis, "Metis_467");
                break;
            }
            case 33990: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000401);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000461, EnemyMetis, "Metis_468");
                break;
            }
            case 34020: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000402);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000462, EnemyMetis, "Metis_469");
                break;
            }
            case 34050: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000403);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000463, EnemyMetis, "Metis_470");
                break;
            }
            case 34080: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000404);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000464, EnemyMetis, "Metis_471");
                break;
            }
            case 34110: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000405);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000465, EnemyMetis, "Metis_472");
                break;
            }
            case 34140: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000406);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000466, EnemyMetis, "Metis_473");
                break;
            }
            case 34170: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000407);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000467, EnemyMetis, "Metis_474");
                break;
            }
            case 34200: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000408);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000468, EnemyMetis, "Metis_475");
                break;
            }
            case 34230: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000409);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000469, EnemyMetis, "Metis_476");
                break;
            }
            case 34260: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000410);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000470, EnemyMetis, "Metis_477");
                break;
            }
            case 34290: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000411);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000471, EnemyMetis, "Metis_478");
                break;
            }
            case 34320: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000412);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000472, EnemyMetis, "Metis_479");
                break;
            }
            case 34350: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000413);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000473, EnemyMetis, "Metis_480");
                break;
            }
            case 34380: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000414);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000474, EnemyMetis, "Metis_481");
                break;
            }
            case 34410: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000415);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000475, EnemyMetis, "Metis_482");
                break;
            }
            case 34440: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000416);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000476, EnemyMetis, "Metis_483");
                break;
            }
            case 34470: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000417);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000477, EnemyMetis, "Metis_484");
                break;
            }
            case 34500: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000418);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000478, EnemyMetis, "Metis_485");
                break;
            }
            case 34530: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000419);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000479, EnemyMetis, "Metis_486");
                break;
            }
            case 34560: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000420);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000480, EnemyMetis, "Metis_487");
                break;
            }
            case 34590: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000421);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000481, EnemyMetis, "Metis_488");
                break;
            }
            case 34620: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000422);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000482, EnemyMetis, "Metis_489");
                break;
            }
            case 34650: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000423);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000483, EnemyMetis, "Metis_490");
                break;
            }
            case 34680: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000424);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000484, EnemyMetis, "Metis_491");
                break;
            }
            case 34710: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000425);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000485, EnemyMetis, "Metis_492");
                break;
            }
            case 34740: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000426);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000486, EnemyMetis, "Metis_493");
                break;
            }
            case 34770: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000427);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000487, EnemyMetis, "Metis_494");
                break;
            }
            case 34800: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000428);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000488, EnemyMetis, "Metis_495");
                break;
            }
            case 34830: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000429);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000489, EnemyMetis, "Metis_496");
                break;
            }
            case 34860: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000430);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000490, EnemyMetis, "Metis_497");
                break;
            }
            case 34890: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000431);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000491, EnemyMetis, "Metis_498");
                break;
            }
            case 34920: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000432);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000492, EnemyMetis, "Metis_499");
                break;
            }
            case 34950: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000433);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000493, EnemyMetis, "Metis_500");
                break;
            }
            case 34980: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000434);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000494, EnemyMetis, "Metis_501");
                break;
            }
            case 35010: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000435);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000495, EnemyMetis, "Metis_502");
                break;
            }
            case 35040: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000436);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000496, EnemyMetis, "Metis_503");
                break;
            }
            case 35070: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000437);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000497, EnemyMetis, "Metis_504");
                break;
            }
            case 35100: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000438);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000498, EnemyMetis, "Metis_505");
                break;
            }
            case 35130: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000439);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000499, EnemyMetis, "Metis_506");
                break;
            }
            case 35160: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000440);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000500, EnemyMetis, "Metis_507");
                break;
            }
            case 35190: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000441);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000501, EnemyMetis, "Metis_508");
                break;
            }
            case 35220: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000442);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000502, EnemyMetis, "Metis_509");
                break;
            }
            case 35250: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000443);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000503, EnemyMetis, "Metis_510");
                break;
            }
            case 35280: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000444);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000504, EnemyMetis, "Metis_511");
                break;
            }
            case 35310: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000445);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000505, EnemyMetis, "Metis_512");
                break;
            }
            case 35340: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000446);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000506, EnemyMetis, "Metis_513");
                break;
            }
            case 35370: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000447);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000507, EnemyMetis, "Metis_514");
                break;
            }
            case 35400: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000448);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000508, EnemyMetis, "Metis_515");
                break;
            }
            case 35430: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000449);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000509, EnemyMetis, "Metis_516");
                break;
            }
            case 35460: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000450);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000510, EnemyMetis, "Metis_517");
                break;
            }
            case 35490: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000451);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000511, EnemyMetis, "Metis_518");
                break;
            }
            case 35520: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000452);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000512, EnemyMetis, "Metis_519");
                break;
            }
            case 35550: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000453);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000513, EnemyMetis, "Metis_520");
                break;
            }
            case 35580: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000454);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000514, EnemyMetis, "Metis_521");
                break;
            }
            case 35610: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000455);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000515, EnemyMetis, "Metis_522");
                break;
            }
            case 35640: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000456);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000516, EnemyMetis, "Metis_523");
                break;
            }
            case 35670: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000457);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000517, EnemyMetis, "Metis_524");
                break;
            }
            case 35700: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000458);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000518, EnemyMetis, "Metis_525");
                break;
            }
            case 35730: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000459);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000519, EnemyMetis, "Metis_526");
                break;
            }
            case 35760: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000460);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000520, EnemyMetis, "Metis_527");
                break;
            }
            case 35790: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000461);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000521, EnemyMetis, "Metis_528");
                break;
            }
            case 35820: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000462);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000522, EnemyMetis, "Metis_529");
                break;
            }
            case 35850: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000463);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000523, EnemyMetis, "Metis_530");
                break;
            }
            case 35880: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000464);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000524, EnemyMetis, "Metis_531");
                break;
            }
            case 35910: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000465);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000525, EnemyMetis, "Metis_532");
                break;
            }
            case 35940: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000466);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000526, EnemyMetis, "Metis_533");
                break;
            }
            case 35970: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000467);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000527, EnemyMetis, "Metis_534");
                break;
            }
            case 36000: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000468);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000528, EnemyMetis, "Metis_535");
                break;
            }
            case 36030: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000469);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000529, EnemyMetis, "Metis_536");
                break;
            }
            case 36060: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000470);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000530, EnemyMetis, "Metis_537");
                break;
            }
            case 36090: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000471);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000531, EnemyMetis, "Metis_538");
                break;
            }
            case 36120: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000472);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000532, EnemyMetis, "Metis_539");
                break;
            }
            case 36150: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000473);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000533, EnemyMetis, "Metis_540");
                break;
            }
            case 36180: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000474);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000534, EnemyMetis, "Metis_541");
                break;
            }
            case 36210: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000475);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000535, EnemyMetis, "Metis_542");
                break;
            }
            case 36240: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000476);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000536, EnemyMetis, "Metis_543");
                break;
            }
            case 36270: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000477);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000537, EnemyMetis, "Metis_544");
                break;
            }
            case 36300: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000478);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000538, EnemyMetis, "Metis_545");
                break;
            }
            case 36330: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000479);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000539, EnemyMetis, "Metis_546");
                break;
            }
            case 36360: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000480);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000540, EnemyMetis, "Metis_547");
                break;
            }
            case 36390: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000481);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000541, EnemyMetis, "Metis_548");
                break;
            }
            case 36420: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000482);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000542, EnemyMetis, "Metis_549");
                break;
            }
            case 36450: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000483);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000543, EnemyMetis, "Metis_550");
                break;
            }
            case 36480: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000484);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000544, EnemyMetis, "Metis_551");
                break;
            }
            case 36510: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000485);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000545, EnemyMetis, "Metis_552");
                break;
            }
            case 36540: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000486);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000546, EnemyMetis, "Metis_553");
                break;
            }
            case 36570: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000487);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000547, EnemyMetis, "Metis_554");
                break;
            }
            case 36600: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000488);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000548, EnemyMetis, "Metis_555");
                break;
            }
            case 36630: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000489);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000549, EnemyMetis, "Metis_556");
                break;
            }
            case 36660: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000490);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000550, EnemyMetis, "Metis_557");
                break;
            }
            case 36690: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000491);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000551, EnemyMetis, "Metis_558");
                break;
            }
            case 36720: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000492);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000552, EnemyMetis, "Metis_559");
                break;
            }
            case 36750: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000493);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000553, EnemyMetis, "Metis_560");
                break;
            }
            case 36780: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000494);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000554, EnemyMetis, "Metis_561");
                break;
            }
            case 36810: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000495);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000555, EnemyMetis, "Metis_562");
                break;
            }
            case 36840: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000496);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000556, EnemyMetis, "Metis_563");
                break;
            }
            case 36870: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000497);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000557, EnemyMetis, "Metis_564");
                break;
            }
            case 36900: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000498);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000558, EnemyMetis, "Metis_565");
                break;
            }
            case 36930: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000499);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000559, EnemyMetis, "Metis_566");
                break;
            }
            case 36960: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000500);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000560, EnemyMetis, "Metis_567");
                break;
            }
            case 36990: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000501);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000561, EnemyMetis, "Metis_568");
                break;
            }
            case 37020: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000502);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000562, EnemyMetis, "Metis_569");
                break;
            }
            case 37050: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000503);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000563, EnemyMetis, "Metis_570");
                break;
            }
            case 37080: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000504);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000564, EnemyMetis, "Metis_571");
                break;
            }
            case 37110: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000505);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000565, EnemyMetis, "Metis_572");
                break;
            }
            case 37140: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000506);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000566, EnemyMetis, "Metis_573");
                break;
            }
            case 37170: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000507);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000567, EnemyMetis, "Metis_574");
                break;
            }
            case 37200: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000508);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000568, EnemyMetis, "Metis_575");
                break;
            }
            case 37230: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000509);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000569, EnemyMetis, "Metis_576");
                break;
            }
            case 37260: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000510);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000570, EnemyMetis, "Metis_577");
                break;
            }
            case 37290: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000511);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000571, EnemyMetis, "Metis_578");
                break;
            }
            case 37320: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000512);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000572, EnemyMetis, "Metis_579");
                break;
            }
            case 37350: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000513);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000573, EnemyMetis, "Metis_580");
                break;
            }
            case 37380: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000514);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000574, EnemyMetis, "Metis_581");
                break;
            }
            case 37410: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000515);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000575, EnemyMetis, "Metis_582");
                break;
            }
            case 37440: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000516);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000576, EnemyMetis, "Metis_583");
                break;
            }
            case 37470: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000517);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000577, EnemyMetis, "Metis_584");
                break;
            }
            case 37500: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000518);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000578, EnemyMetis, "Metis_585");
                break;
            }
            case 37530: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000519);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000579, EnemyMetis, "Metis_586");
                break;
            }
            case 37560: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000520);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000580, EnemyMetis, "Metis_587");
                break;
            }
            case 37590: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000521);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000581, EnemyMetis, "Metis_588");
                break;
            }
            case 37620: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000522);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000582, EnemyMetis, "Metis_589");
                break;
            }
            case 37650: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000523);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000583, EnemyMetis, "Metis_590");
                break;
            }
            case 37680: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000524);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000584, EnemyMetis, "Metis_591");
                break;
            }
            case 37710: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000525);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000585, EnemyMetis, "Metis_592");
                break;
            }
            case 37740: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000526);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000586, EnemyMetis, "Metis_593");
                break;
            }
            case 37770: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000527);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000587, EnemyMetis, "Metis_594");
                break;
            }
            case 37800: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000528);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000588, EnemyMetis, "Metis_595");
                break;
            }
            case 37830: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000529);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000589, EnemyMetis, "Metis_596");
                break;
            }
            case 37860: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000530);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000590, EnemyMetis, "Metis_597");
                break;
            }
            case 37890: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000531);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000591, EnemyMetis, "Metis_598");
                break;
            }
            case 37920: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000532);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000592, EnemyMetis, "Metis_599");
                break;
            }
            case 37950: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000533);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000593, EnemyMetis, "Metis_600");
                break;
            }
            case 37980: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000534);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000594, EnemyMetis, "Metis_601");
                break;
            }
            case 38010: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000535);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000595, EnemyMetis, "Metis_602");
                break;
            }
            case 38040: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000536);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000596, EnemyMetis, "Metis_603");
                break;
            }
            case 38070: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000537);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000597, EnemyMetis, "Metis_604");
                break;
            }
            case 38100: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000538);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000598, EnemyMetis, "Metis_605");
                break;
            }
            case 38130: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000539);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000599, EnemyMetis, "Metis_606");
                break;
            }
            case 38160: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000540);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000600, EnemyMetis, "Metis_607");
                break;
            }
            case 38190: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000541);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000601, EnemyMetis, "Metis_608");
                break;
            }
            case 38220: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000542);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000602, EnemyMetis, "Metis_609");
                break;
            }
            case 38250: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000543);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000603, EnemyMetis, "Metis_610");
                break;
            }
            case 38280: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000544);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000604, EnemyMetis, "Metis_611");
                break;
            }
            case 38310: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000545);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000605, EnemyMetis, "Metis_612");
                break;
            }
            case 38340: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000546);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000606, EnemyMetis, "Metis_613");
                break;
            }
            case 38370: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000547);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000607, EnemyMetis, "Metis_614");
                break;
            }
            case 38400: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000548);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000608, EnemyMetis, "Metis_615");
                break;
            }
            case 38430: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000549);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000609, EnemyMetis, "Metis_616");
                break;
            }
            case 38460: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000550);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000610, EnemyMetis, "Metis_617");
                break;
            }
            case 38490: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000551);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000611, EnemyMetis, "Metis_618");
                break;
            }
            case 38520: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000552);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000612, EnemyMetis, "Metis_619");
                break;
            }
            case 38550: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000553);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000613, EnemyMetis, "Metis_620");
                break;
            }
            case 38580: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000554);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000614, EnemyMetis, "Metis_621");
                break;
            }
            case 38610: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000555);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000615, EnemyMetis, "Metis_622");
                break;
            }
            case 38640: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000556);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000616, EnemyMetis, "Metis_623");
                break;
            }
            case 38670: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000557);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000617, EnemyMetis, "Metis_624");
                break;
            }
            case 38700: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000558);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000618, EnemyMetis, "Metis_625");
                break;
            }
            case 38730: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000559);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000619, EnemyMetis, "Metis_626");
                break;
            }
            case 38760: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000560);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000620, EnemyMetis, "Metis_627");
                break;
            }
            case 38790: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000561);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000621, EnemyMetis, "Metis_628");
                break;
            }
            case 38820: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000562);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000622, EnemyMetis, "Metis_629");
                break;
            }
            case 38850: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000563);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000623, EnemyMetis, "Metis_630");
                break;
            }
            case 38880: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000564);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000624, EnemyMetis, "Metis_631");
                break;
            }
            case 38910: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000565);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000625, EnemyMetis, "Metis_632");
                break;
            }
            case 38940: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000566);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000626, EnemyMetis, "Metis_633");
                break;
            }
            case 38970: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000567);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000627, EnemyMetis, "Metis_634");
                break;
            }
            case 39000: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000568);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000628, EnemyMetis, "Metis_635");
                break;
            }
            case 39030: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000569);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000629, EnemyMetis, "Metis_636");
                break;
            }
            case 39060: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000570);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000630, EnemyMetis, "Metis_637");
                break;
            }
            case 39090: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000571);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000631, EnemyMetis, "Metis_638");
                break;
            }
            case 39120: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000572);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000632, EnemyMetis, "Metis_639");
                break;
            }
            case 39150: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000573);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000633, EnemyMetis, "Metis_640");
                break;
            }
            case 39180: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000574);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000634, EnemyMetis, "Metis_641");
                break;
            }
            case 39210: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000575);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000635, EnemyMetis, "Metis_642");
                break;
            }
            case 39240: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000576);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000636, EnemyMetis, "Metis_643");
                break;
            }
            case 39270: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000577);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000637, EnemyMetis, "Metis_644");
                break;
            }
            case 39300: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000578);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000638, EnemyMetis, "Metis_645");
                break;
            }
            case 39330: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000579);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000639, EnemyMetis, "Metis_646");
                break;
            }
            case 39360: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000580);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000640, EnemyMetis, "Metis_647");
                break;
            }
            case 39390: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000581);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000641, EnemyMetis, "Metis_648");
                break;
            }
            case 39420: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000582);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000642, EnemyMetis, "Metis_649");
                break;
            }
            case 39450: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000583);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000643, EnemyMetis, "Metis_650");
                break;
            }
            case 39480: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000584);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000644, EnemyMetis, "Metis_651");
                break;
            }
            case 39510: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000585);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000645, EnemyMetis, "Metis_652");
                break;
            }
            case 39540: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000586);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000646, EnemyMetis, "Metis_653");
                break;
            }
            case 39570: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000587);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000647, EnemyMetis, "Metis_654");
                break;
            }
            case 39600: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000588);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000648, EnemyMetis, "Metis_655");
                break;
            }
            case 39630: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000589);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000649, EnemyMetis, "Metis_656");
                break;
            }
            case 39660: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000590);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000650, EnemyMetis, "Metis_657");
                break;
            }
            case 39690: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000591);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000651, EnemyMetis, "Metis_658");
                break;
            }
            case 39720: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000592);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000652, EnemyMetis, "Metis_659");
                break;
            }
            case 39750: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000593);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000653, EnemyMetis, "Metis_660");
                break;
            }
            case 39780: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000594);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000654, EnemyMetis, "Metis_661");
                break;
            }
            case 39810: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000595);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000655, EnemyMetis, "Metis_662");
                break;
            }
            case 39840: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000596);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000656, EnemyMetis, "Metis_663");
                break;
            }
            case 39870: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000597);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000657, EnemyMetis, "Metis_664");
                break;
            }
            case 39900: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000598);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000658, EnemyMetis, "Metis_665");
                break;
            }
            case 39930: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000599);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000659, EnemyMetis, "Metis_666");
                break;
            }
            case 39960: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000600);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000660, EnemyMetis, "Metis_667");
                break;
            }
            case 39990: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000601);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000661, EnemyMetis, "Metis_668");
                break;
            }
            case 40020: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000602);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000662, EnemyMetis, "Metis_669");
                break;
            }
            case 40050: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000603);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000663, EnemyMetis, "Metis_670");
                break;
            }
            case 40080: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000604);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000664, EnemyMetis, "Metis_671");
                break;
            }
            case 40110: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000605);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000665, EnemyMetis, "Metis_672");
                break;
            }
            case 40140: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000606);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000666, EnemyMetis, "Metis_673");
                break;
            }
            case 40170: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000607);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000667, EnemyMetis, "Metis_674");
                break;
            }
            case 40200: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000608);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000668, EnemyMetis, "Metis_675");
                break;
            }
            case 40230: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000609);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000669, EnemyMetis, "Metis_676");
                break;
            }
            case 40260: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000610);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000670, EnemyMetis, "Metis_677");
                break;
            }
            case 40290: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000611);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000671, EnemyMetis, "Metis_678");
                break;
            }
            case 40320: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000612);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000672, EnemyMetis, "Metis_679");
                break;
            }
            case 40350: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000613);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000673, EnemyMetis, "Metis_680");
                break;
            }
            case 40380: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000614);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000674, EnemyMetis, "Metis_681");
                break;
            }
            case 40410: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000615);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000675, EnemyMetis, "Metis_682");
                break;
            }
            case 40440: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000616);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000676, EnemyMetis, "Metis_683");
                break;
            }
            case 40470: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000617);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000677, EnemyMetis, "Metis_684");
                break;
            }
            case 40500: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000618);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000678, EnemyMetis, "Metis_685");
                break;
            }
            case 40530: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000619);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000679, EnemyMetis, "Metis_686");
                break;
            }
            case 40560: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000620);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000680, EnemyMetis, "Metis_687");
                break;
            }
            case 40590: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000621);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000681, EnemyMetis, "Metis_688");
                break;
            }
            case 40620: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000622);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000682, EnemyMetis, "Metis_689");
                break;
            }
            case 40650: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000623);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000683, EnemyMetis, "Metis_690");
                break;
            }
            case 40680: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000624);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000684, EnemyMetis, "Metis_691");
                break;
            }
            case 40710: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000625);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000685, EnemyMetis, "Metis_692");
                break;
            }
            case 40740: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000626);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000686, EnemyMetis, "Metis_693");
                break;
            }
            case 40770: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000627);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000687, EnemyMetis, "Metis_694");
                break;
            }
            case 40800: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000628);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000688, EnemyMetis, "Metis_695");
                break;
            }
            case 40830: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000629);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000689, EnemyMetis, "Metis_696");
                break;
            }
            case 40860: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000630);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000690, EnemyMetis, "Metis_697");
                break;
            }
            case 40890: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000631);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000691, EnemyMetis, "Metis_698");
                break;
            }
            case 40920: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000632);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000692, EnemyMetis, "Metis_699");
                break;
            }
            case 40950: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000633);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000693, EnemyMetis, "Metis_700");
                break;
            }
            case 40980: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000634);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000694, EnemyMetis, "Metis_701");
                break;
            }
            case 41010: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000635);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000695, EnemyMetis, "Metis_702");
                break;
            }
            case 41040: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000636);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000696, EnemyMetis, "Metis_703");
                break;
            }
            case 41070: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000637);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000697, EnemyMetis, "Metis_704");
                break;
            }
            case 41100: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000638);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000698, EnemyMetis, "Metis_705");
                break;
            }
            case 41130: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000639);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000699, EnemyMetis, "Metis_706");
                break;
            }
            case 41160: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000640);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000700, EnemyMetis, "Metis_707");
                break;
            }
            case 41190: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000641);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000701, EnemyMetis, "Metis_708");
                break;
            }
            case 41220: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000642);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000702, EnemyMetis, "Metis_709");
                break;
            }
            case 41250: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000643);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000703, EnemyMetis, "Metis_710");
                break;
            }
            case 41280: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000644);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000704, EnemyMetis, "Metis_711");
                break;
            }
            case 41310: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000645);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000705, EnemyMetis, "Metis_712");
                break;
            }
            case 41340: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000646);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000706, EnemyMetis, "Metis_713");
                break;
            }
            case 41370: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000647);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000707, EnemyMetis, "Metis_714");
                break;
            }
            case 41400: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000648);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000708, EnemyMetis, "Metis_715");
                break;
            }
            case 41430: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000649);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000709, EnemyMetis, "Metis_716");
                break;
            }
            case 41460: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000650);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000710, EnemyMetis, "Metis_717");
                break;
            }
            case 41490: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000651);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000711, EnemyMetis, "Metis_718");
                break;
            }
            case 41520: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000652);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000712, EnemyMetis, "Metis_719");
                break;
            }
            case 41550: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000653);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000713, EnemyMetis, "Metis_720");
                break;
            }
            case 41580: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000654);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000714, EnemyMetis, "Metis_721");
                break;
            }
            case 41610: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000655);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000715, EnemyMetis, "Metis_722");
                break;
            }
            case 41640: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000656);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000716, EnemyMetis, "Metis_723");
                break;
            }
            case 41670: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000657);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000717, EnemyMetis, "Metis_724");
                break;
            }
            case 41700: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000658);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000718, EnemyMetis, "Metis_725");
                break;
            }
            case 41730: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000659);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000719, EnemyMetis, "Metis_726");
                break;
            }
            case 41760: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000660);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000720, EnemyMetis, "Metis_727");
                break;
            }
            case 41790: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000661);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000721, EnemyMetis, "Metis_728");
                break;
            }
            case 41820: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000662);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000722, EnemyMetis, "Metis_729");
                break;
            }
            case 41850: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000663);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000723, EnemyMetis, "Metis_730");
                break;
            }
            case 41880: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000664);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000724, EnemyMetis, "Metis_731");
                break;
            }
            case 41910: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000665);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000725, EnemyMetis, "Metis_732");
                break;
            }
            case 41940: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000666);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000726, EnemyMetis, "Metis_733");
                break;
            }
            case 41970: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000667);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000727, EnemyMetis, "Metis_734");
                break;
            }
            case 42000: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000668);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000728, EnemyMetis, "Metis_735");
                break;
            }
            case 42030: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000669);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000729, EnemyMetis, "Metis_736");
                break;
            }
            case 42060: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000670);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000730, EnemyMetis, "Metis_737");
                break;
            }
            case 42090: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000671);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000731, EnemyMetis, "Metis_738");
                break;
            }
            case 42120: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000672);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000732, EnemyMetis, "Metis_739");
                break;
            }
            case 42150: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000673);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000733, EnemyMetis, "Metis_740");
                break;
            }
            case 42180: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000674);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000734, EnemyMetis, "Metis_741");
                break;
            }
            case 42210: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000675);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000735, EnemyMetis, "Metis_742");
                break;
            }
            case 42240: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000676);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000736, EnemyMetis, "Metis_743");
                break;
            }
            case 42270: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000677);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000737, EnemyMetis, "Metis_744");
                break;
            }
            case 42300: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000678);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000738, EnemyMetis, "Metis_745");
                break;
            }
            case 42330: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000679);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000739, EnemyMetis, "Metis_746");
                break;
            }
            case 42360: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000680);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000740, EnemyMetis, "Metis_747");
                break;
            }
            case 42390: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000681);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000741, EnemyMetis, "Metis_748");
                break;
            }
            case 42420: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000682);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000742, EnemyMetis, "Metis_749");
                break;
            }
            case 42450: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000683);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000743, EnemyMetis, "Metis_750");
                break;
            }
            case 42480: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000684);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000744, EnemyMetis, "Metis_751");
                break;
            }
            case 42510: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000685);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000745, EnemyMetis, "Metis_752");
                break;
            }
            case 42540: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000686);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000746, EnemyMetis, "Metis_753");
                break;
            }
            case 42570: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000687);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000747, EnemyMetis, "Metis_754");
                break;
            }
            case 42600: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000688);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000748, EnemyMetis, "Metis_755");
                break;
            }
            case 42630: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000689);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000749, EnemyMetis, "Metis_756");
                break;
            }
            case 42660: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000690);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000750, EnemyMetis, "Metis_757");
                break;
            }
            case 42690: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000691);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000751, EnemyMetis, "Metis_758");
                break;
            }
            case 42720: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000692);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000752, EnemyMetis, "Metis_759");
                break;
            }
            case 42750: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000693);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000753, EnemyMetis, "Metis_760");
                break;
            }
            case 42780: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000694);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000754, EnemyMetis, "Metis_761");
                break;
            }
            case 42810: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000695);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000755, EnemyMetis, "Metis_762");
                break;
            }
            case 42840: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000696);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000756, EnemyMetis, "Metis_763");
                break;
            }
            case 42870: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000697);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000757, EnemyMetis, "Metis_764");
                break;
            }
            case 42900: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000698);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000758, EnemyMetis, "Metis_765");
                break;
            }
            case 42930: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000699);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000759, EnemyMetis, "Metis_766");
                break;
            }
            case 42960: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000700);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000760, EnemyMetis, "Metis_767");
                break;
            }
            case 42990: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000701);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000761, EnemyMetis, "Metis_768");
                break;
            }
            case 43020: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000702);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000762, EnemyMetis, "Metis_769");
                break;
            }
            case 43050: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000703);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000763, EnemyMetis, "Metis_770");
                break;
            }
            case 43080: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000704);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000764, EnemyMetis, "Metis_771");
                break;
            }
            case 43110: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000705);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000765, EnemyMetis, "Metis_772");
                break;
            }
            case 43140: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000706);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000766, EnemyMetis, "Metis_773");
                break;
            }
            case 43170: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000707);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000767, EnemyMetis, "Metis_774");
                break;
            }
            case 43200: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000708);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000768, EnemyMetis, "Metis_775");
                break;
            }
            case 43230: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000709);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000769, EnemyMetis, "Metis_776");
                break;
            }
            case 43260: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000710);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000770, EnemyMetis, "Metis_777");
                break;
            }
            case 43290: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000711);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000771, EnemyMetis, "Metis_778");
                break;
            }
            case 43320: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000712);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000772, EnemyMetis, "Metis_779");
                break;
            }
            case 43350: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000713);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000773, EnemyMetis, "Metis_780");
                break;
            }
            case 43380: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000714);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000774, EnemyMetis, "Metis_781");
                break;
            }
            case 43410: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000715);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000775, EnemyMetis, "Metis_782");
                break;
            }
            case 43440: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000716);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000776, EnemyMetis, "Metis_783");
                break;
            }
            case 43470: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000717);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000777, EnemyMetis, "Metis_784");
                break;
            }
            case 43500: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000718);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000778, EnemyMetis, "Metis_785");
                break;
            }
            case 43530: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000719);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000779, EnemyMetis, "Metis_786");
                break;
            }
            case 43560: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000720);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000780, EnemyMetis, "Metis_787");
                break;
            }
            case 43590: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000721);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000781, EnemyMetis, "Metis_788");
                break;
            }
            case 43620: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000722);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000782, EnemyMetis, "Metis_789");
                break;
            }
            case 43650: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000723);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000783, EnemyMetis, "Metis_790");
                break;
            }
            case 43680: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000724);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000784, EnemyMetis, "Metis_791");
                break;
            }
            case 43710: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000725);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000785, EnemyMetis, "Metis_792");
                break;
            }
            case 43740: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000726);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000786, EnemyMetis, "Metis_793");
                break;
            }
            case 43770: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000727);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000787, EnemyMetis, "Metis_794");
                break;
            }
            case 43800: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000728);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000788, EnemyMetis, "Metis_795");
                break;
            }
            case 43830: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000729);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000789, EnemyMetis, "Metis_796");
                break;
            }
            case 43860: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000730);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000790, EnemyMetis, "Metis_797");
                break;
            }
            case 43890: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000731);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000791, EnemyMetis, "Metis_798");
                break;
            }
            case 43920: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000732);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000792, EnemyMetis, "Metis_799");
                break;
            }
            case 43950: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000733);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000793, EnemyMetis, "Metis_800");
                break;
            }
            case 43980: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000734);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000794, EnemyMetis, "Metis_801");
                break;
            }
            case 44010: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000735);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000795, EnemyMetis, "Metis_802");
                break;
            }
            case 44040: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000736);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000796, EnemyMetis, "Metis_803");
                break;
            }
            case 44070: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000737);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000797, EnemyMetis, "Metis_804");
                break;
            }
            case 44100: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000738);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000798, EnemyMetis, "Metis_805");
                break;
            }
            case 44130: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000739);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000799, EnemyMetis, "Metis_806");
                break;
            }
            case 44160: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000740);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000800, EnemyMetis, "Metis_807");
                break;
            }
            case 44190: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000741);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000801, EnemyMetis, "Metis_808");
                break;
            }
            case 44220: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000742);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000802, EnemyMetis, "Metis_809");
                break;
            }
            case 44250: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000743);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000803, EnemyMetis, "Metis_810");
                break;
            }
            case 44280: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000744);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000804, EnemyMetis, "Metis_811");
                break;
            }
            case 44310: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000745);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000805, EnemyMetis, "Metis_812");
                break;
            }
            case 44340: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000746);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000806, EnemyMetis, "Metis_813");
                break;
            }
            case 44370: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000747);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000807, EnemyMetis, "Metis_814");
                break;
            }
            case 44400: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000748);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000808, EnemyMetis, "Metis_815");
                break;
            }
            case 44430: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000749);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000809, EnemyMetis, "Metis_816");
                break;
            }
            case 44460: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000750);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000810, EnemyMetis, "Metis_817");
                break;
            }
            case 44490: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000751);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000811, EnemyMetis, "Metis_818");
                break;
            }
            case 44520: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000752);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000812, EnemyMetis, "Metis_819");
                break;
            }
            case 44550: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000753);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000813, EnemyMetis, "Metis_820");
                break;
            }
            case 44580: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000754);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000814, EnemyMetis, "Metis_821");
                break;
            }
            case 44610: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000755);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000815, EnemyMetis, "Metis_822");
                break;
            }
            case 44640: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000756);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000816, EnemyMetis, "Metis_823");
                break;
            }
            case 44670: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000757);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000817, EnemyMetis, "Metis_824");
                break;
            }
            case 44700: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000758);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000818, EnemyMetis, "Metis_825");
                break;
            }
            case 44730: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000759);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000819, EnemyMetis, "Metis_826");
                break;
            }
            case 44760: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000760);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000820, EnemyMetis, "Metis_827");
                break;
            }
            case 44790: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000761);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000821, EnemyMetis, "Metis_828");
                break;
            }
            case 44820: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000762);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000822, EnemyMetis, "Metis_829");
                break;
            }
            case 44850: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000763);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000823, EnemyMetis, "Metis_830");
                break;
            }
            case 44880: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000764);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000824, EnemyMetis, "Metis_831");
                break;
            }
            case 44910: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000765);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000825, EnemyMetis, "Metis_832");
                break;
            }
            case 44940: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000766);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000826, EnemyMetis, "Metis_833");
                break;
            }
            case 44970: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000767);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000827, EnemyMetis, "Metis_834");
                break;
            }
            case 45000: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000768);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000828, EnemyMetis, "Metis_835");
                break;
            }
            case 45030: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000769);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000829, EnemyMetis, "Metis_836");
                break;
            }
            case 45060: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000770);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000830, EnemyMetis, "Metis_837");
                break;
            }
            case 45090: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000771);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000831, EnemyMetis, "Metis_838");
                break;
            }
            case 45120: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000772);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000832, EnemyMetis, "Metis_839");
                break;
            }
            case 45150: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000773);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000833, EnemyMetis, "Metis_840");
                break;
            }
            case 45180: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000774);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000834, EnemyMetis, "Metis_841");
                break;
            }
            case 45210: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000775);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000835, EnemyMetis, "Metis_842");
                break;
            }
            case 45240: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000776);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000836, EnemyMetis, "Metis_843");
                break;
            }
            case 45270: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000777);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000837, EnemyMetis, "Metis_844");
                break;
            }
            case 45300: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000778);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000838, EnemyMetis, "Metis_845");
                break;
            }
            case 45330: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000779);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000839, EnemyMetis, "Metis_846");
                break;
            }
            case 45360: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000780);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000840, EnemyMetis, "Metis_847");
                break;
            }
            case 45390: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000781);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000841, EnemyMetis, "Metis_848");
                break;
            }
            case 45420: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000782);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000842, EnemyMetis, "Metis_849");
                break;
            }
            case 45450: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000783);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000843, EnemyMetis, "Metis_850");
                break;
            }
            case 45480: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000784);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000844, EnemyMetis, "Metis_851");
                break;
            }
            case 45510: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000785);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000845, EnemyMetis, "Metis_852");
                break;
            }
            case 45540: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000786);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000846, EnemyMetis, "Metis_853");
                break;
            }
            case 45570: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000787);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000847, EnemyMetis, "Metis_854");
                break;
            }
            case 45600: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000788);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000848, EnemyMetis, "Metis_855");
                break;
            }
            case 45630: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000789);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000849, EnemyMetis, "Metis_856");
                break;
            }
            case 45660: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000790);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000850, EnemyMetis, "Metis_857");
                break;
            }
            case 45690: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000791);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000851, EnemyMetis, "Metis_858");
                break;
            }
            case 45720: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000792);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000852, EnemyMetis, "Metis_859");
                break;
            }
            case 45750: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000793);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000853, EnemyMetis, "Metis_860");
                break;
            }
            case 45780: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000794);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000854, EnemyMetis, "Metis_861");
                break;
            }
            case 45810: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000795);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000855, EnemyMetis, "Metis_862");
                break;
            }
            case 45840: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000796);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000856, EnemyMetis, "Metis_863");
                break;
            }
            case 45870: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000797);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000857, EnemyMetis, "Metis_864");
                break;
            }
            case 45900: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000798);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000858, EnemyMetis, "Metis_865");
                break;
            }
            case 45930: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000799);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000859, EnemyMetis, "Metis_866");
                break;
            }
            case 45960: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000800);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000860, EnemyMetis, "Metis_867");
                break;
            }
            case 45990: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000801);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000861, EnemyMetis, "Metis_868");
                break;
            }
            case 46020: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000802);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000862, EnemyMetis, "Metis_869");
                break;
            }
            case 46050: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000803);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000863, EnemyMetis, "Metis_870");
                break;
            }
            case 46080: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000804);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000864, EnemyMetis, "Metis_871");
                break;
            }
            case 46110: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000805);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000865, EnemyMetis, "Metis_872");
                break;
            }
            case 46140: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000806);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000866, EnemyMetis, "Metis_873");
                break;
            }
            case 46170: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000807);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000867, EnemyMetis, "Metis_874");
                break;
            }
            case 46200: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000808);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000868, EnemyMetis, "Metis_875");
                break;
            }
            case 46230: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000809);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000869, EnemyMetis, "Metis_876");
                break;
            }
            case 46260: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000810);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000870, EnemyMetis, "Metis_877");
                break;
            }
            case 46290: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000811);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000871, EnemyMetis, "Metis_878");
                break;
            }
            case 46320: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000812);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000872, EnemyMetis, "Metis_879");
                break;
            }
            case 46350: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000813);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000873, EnemyMetis, "Metis_880");
                break;
            }
            case 46380: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000814);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000874, EnemyMetis, "Metis_881");
                break;
            }
            case 46410: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000815);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000875, EnemyMetis, "Metis_882");
                break;
            }
            case 46440: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000816);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000876, EnemyMetis, "Metis_883");
                break;
            }
            case 46470: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000817);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000877, EnemyMetis, "Metis_884");
                break;
            }
            case 46500: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000818);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000878, EnemyMetis, "Metis_885");
                break;
            }
            case 46530: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000819);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000879, EnemyMetis, "Metis_886");
                break;
            }
            case 46560: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000820);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000880, EnemyMetis, "Metis_887");
                break;
            }
            case 46590: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000821);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000881, EnemyMetis, "Metis_888");
                break;
            }
            case 46620: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000822);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000882, EnemyMetis, "Metis_889");
                break;
            }
            case 46650: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000823);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000883, EnemyMetis, "Metis_890");
                break;
            }
            case 46680: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000824);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000884, EnemyMetis, "Metis_891");
                break;
            }
            case 46710: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000825);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000885, EnemyMetis, "Metis_892");
                break;
            }
            case 46740: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000826);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000886, EnemyMetis, "Metis_893");
                break;
            }
            case 46770: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000827);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000887, EnemyMetis, "Metis_894");
                break;
            }
            case 46800: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000828);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000888, EnemyMetis, "Metis_895");
                break;
            }
            case 46830: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000829);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000889, EnemyMetis, "Metis_896");
                break;
            }
            case 46860: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000830);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000890, EnemyMetis, "Metis_897");
                break;
            }
            case 46890: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000831);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000891, EnemyMetis, "Metis_898");
                break;
            }
            case 46920: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000832);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000892, EnemyMetis, "Metis_899");
                break;
            }
            case 46950: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000833);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000893, EnemyMetis, "Metis_900");
                break;
            }
            case 46980: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000834);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000894, EnemyMetis, "Metis_901");
                break;
            }
            case 47010: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000835);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000895, EnemyMetis, "Metis_902");
                break;
            }
            case 47040: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000836);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000896, EnemyMetis, "Metis_903");
                break;
            }
            case 47070: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000837);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000897, EnemyMetis, "Metis_904");
                break;
            }
            case 47100: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000838);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000898, EnemyMetis, "Metis_905");
                break;
            }
            case 47130: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000839);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000899, EnemyMetis, "Metis_906");
                break;
            }
            case 47160: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000840);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000900, EnemyMetis, "Metis_907");
                break;
            }
            case 47190: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000841);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000901, EnemyMetis, "Metis_908");
                break;
            }
            case 47220: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000842);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000902, EnemyMetis, "Metis_909");
                break;
            }
            case 47250: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000843);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000903, EnemyMetis, "Metis_910");
                break;
            }
            case 47280: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000844);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000904, EnemyMetis, "Metis_911");
                break;
            }
            case 47310: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000845);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000905, EnemyMetis, "Metis_912");
                break;
            }
            case 47340: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000846);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000906, EnemyMetis, "Metis_913");
                break;
            }
            case 47370: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000847);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000907, EnemyMetis, "Metis_914");
                break;
            }
            case 47400: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000848);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000908, EnemyMetis, "Metis_915");
                break;
            }
            case 47430: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000849);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000909, EnemyMetis, "Metis_916");
                break;
            }
            case 47460: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000850);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000910, EnemyMetis, "Metis_917");
                break;
            }
            case 47490: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000851);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000911, EnemyMetis, "Metis_918");
                break;
            }
            case 47520: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000852);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000912, EnemyMetis, "Metis_919");
                break;
            }
            case 47550: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000853);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000913, EnemyMetis, "Metis_920");
                break;
            }
            case 47580: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000854);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000914, EnemyMetis, "Metis_921");
                break;
            }
            case 47610: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000855);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000915, EnemyMetis, "Metis_922");
                break;
            }
            case 47640: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000856);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000916, EnemyMetis, "Metis_923");
                break;
            }
            case 47670: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000857);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000917, EnemyMetis, "Metis_924");
                break;
            }
            case 47700: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000858);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000918, EnemyMetis, "Metis_925");
                break;
            }
            case 47730: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000859);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000919, EnemyMetis, "Metis_926");
                break;
            }
            case 47760: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000860);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000920, EnemyMetis, "Metis_927");
                break;
            }
            case 47790: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000861);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000921, EnemyMetis, "Metis_928");
                break;
            }
            case 47820: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000862);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000922, EnemyMetis, "Metis_929");
                break;
            }
            case 47850: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000863);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000923, EnemyMetis, "Metis_930");
                break;
            }
            case 47880: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000864);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000924, EnemyMetis, "Metis_931");
                break;
            }
            case 47910: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000865);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000925, EnemyMetis, "Metis_932");
                break;
            }
            case 47940: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000866);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000926, EnemyMetis, "Metis_933");
                break;
            }
            case 47970: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000867);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000927, EnemyMetis, "Metis_934");
                break;
            }
            case 48000: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000868);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000928, EnemyMetis, "Metis_935");
                break;
            }
            case 48030: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000869);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000929, EnemyMetis, "Metis_936");
                break;
            }
            case 48060: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000870);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000930, EnemyMetis, "Metis_937");
                break;
            }
            case 48090: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000871);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000931, EnemyMetis, "Metis_938");
                break;
            }
            case 48120: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000872);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000932, EnemyMetis, "Metis_939");
                break;
            }
            case 48150: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000873);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000933, EnemyMetis, "Metis_940");
                break;
            }
            case 48180: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000874);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000934, EnemyMetis, "Metis_941");
                break;
            }
            case 48210: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000875);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000935, EnemyMetis, "Metis_942");
                break;
            }
            case 48240: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000876);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000936, EnemyMetis, "Metis_943");
                break;
            }
            case 48270: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000877);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000937, EnemyMetis, "Metis_944");
                break;
            }
            case 48300: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000878);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000938, EnemyMetis, "Metis_945");
                break;
            }
            case 48330: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000879);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000939, EnemyMetis, "Metis_946");
                break;
            }
            case 48360: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000880);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000940, EnemyMetis, "Metis_947");
                break;
            }
            case 48390: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000881);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000941, EnemyMetis, "Metis_948");
                break;
            }
            case 48420: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000882);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000942, EnemyMetis, "Metis_949");
                break;
            }
            case 48450: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000883);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000943, EnemyMetis, "Metis_950");
                break;
            }
            case 48480: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000884);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000944, EnemyMetis, "Metis_951");
                break;
            }
            case 48510: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000885);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000945, EnemyMetis, "Metis_952");
                break;
            }
            case 48540: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000886);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000946, EnemyMetis, "Metis_953");
                break;
            }
            case 48570: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000887);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000947, EnemyMetis, "Metis_954");
                break;
            }
            case 48600: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000888);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000948, EnemyMetis, "Metis_955");
                break;
            }
            case 48630: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000889);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000949, EnemyMetis, "Metis_956");
                break;
            }
            case 48660: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000890);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000950, EnemyMetis, "Metis_957");
                break;
            }
            case 48690: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000891);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000951, EnemyMetis, "Metis_958");
                break;
            }
            case 48720: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000892);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000952, EnemyMetis, "Metis_959");
                break;
            }
            case 48750: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000893);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000953, EnemyMetis, "Metis_960");
                break;
            }
            case 48780: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000894);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000954, EnemyMetis, "Metis_961");
                break;
            }
            case 48810: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000895);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000955, EnemyMetis, "Metis_962");
                break;
            }
            case 48840: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000896);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000956, EnemyMetis, "Metis_963");
                break;
            }
            case 48870: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000897);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000957, EnemyMetis, "Metis_964");
                break;
            }
            case 48900: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000898);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000958, EnemyMetis, "Metis_965");
                break;
            }
            case 48930: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000899);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000959, EnemyMetis, "Metis_966");
                break;
            }
            case 48960: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000900);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000960, EnemyMetis, "Metis_967");
                break;
            }
            case 48990: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000901);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000961, EnemyMetis, "Metis_968");
                break;
            }
            case 49020: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000902);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000962, EnemyMetis, "Metis_969");
                break;
            }
            case 49050: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000903);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000963, EnemyMetis, "Metis_970");
                break;
            }
            case 49080: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000904);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000964, EnemyMetis, "Metis_971");
                break;
            }
            case 49110: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000905);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000965, EnemyMetis, "Metis_972");
                break;
            }
            case 49140: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000906);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000966, EnemyMetis, "Metis_973");
                break;
            }
            case 49170: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000907);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000967, EnemyMetis, "Metis_974");
                break;
            }
            case 49200: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000908);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000968, EnemyMetis, "Metis_975");
                break;
            }
            case 49230: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000909);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000969, EnemyMetis, "Metis_976");
                break;
            }
            case 49260: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000910);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000970, EnemyMetis, "Metis_977");
                break;
            }
            case 49290: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000911);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000971, EnemyMetis, "Metis_978");
                break;
            }
            case 49320: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000912);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000972, EnemyMetis, "Metis_979");
                break;
            }
            case 49350: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000913);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000973, EnemyMetis, "Metis_980");
                break;
            }
            case 49380: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000914);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000974, EnemyMetis, "Metis_981");
                break;
            }
            case 49410: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000915);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000975, EnemyMetis, "Metis_982");
                break;
            }
            case 49440: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000916);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000976, EnemyMetis, "Metis_983");
                break;
            }
            case 49470: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000917);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000977, EnemyMetis, "Metis_984");
                break;
            }
            case 49500: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000918);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000978, EnemyMetis, "Metis_985");
                break;
            }
            case 49530: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000919);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000979, EnemyMetis, "Metis_986");
                break;
            }
            case 49560: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000920);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000980, EnemyMetis, "Metis_987");
                break;
            }
            case 49590: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000921);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000981, EnemyMetis, "Metis_988");
                break;
            }
            case 49620: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000922);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000982, EnemyMetis, "Metis_989");
                break;
            }
            case 49650: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000923);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000983, EnemyMetis, "Metis_990");
                break;
            }
            case 49680: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000924);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000984, EnemyMetis, "Metis_991");
                break;
            }
            case 49710: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000925);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000985, EnemyMetis, "Metis_992");
                break;
            }
            case 49740: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000926);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000986, EnemyMetis, "Metis_993");
                break;
            }
            case 49770: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000927);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000987, EnemyMetis, "Metis_994");
                break;
            }
            case 49800: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000928);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000988, EnemyMetis, "Metis_995");
                break;
            }
            case 49830: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000929);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000989, EnemyMetis, "Metis_996");
                break;
            }
            case 49860: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000930);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000990, EnemyMetis, "Metis_997");
                break;
            }
            case 49890: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000931);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000991, EnemyMetis, "Metis_998");
                break;
            }
            case 49920: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000932);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000992, EnemyMetis, "Metis_999");
                break;
            }
            case 49950: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000933);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000993, EnemyMetis, "Metis_1000");
                break;
            }
            case 49980: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000934);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000994, EnemyMetis, "Metis_1001");
                break;
            }
            case 50010: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000935);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000995, EnemyMetis, "Metis_1002");
                break;
            }
            case 50040: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000936);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000996, EnemyMetis, "Metis_1003");
                break;
            }
            case 50070: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000937);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000997, EnemyMetis, "Metis_1004");
                break;
            }
            case 50100: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000938);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000998, EnemyMetis, "Metis_1005");
                break;
            }
            case 50130: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000939);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40000999, EnemyMetis, "Metis_1006");
                break;
            }
            case 50160: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000940);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40001000, EnemyMetis, "Metis_1007");
                break;
            }
            case 50190: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000941);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40001001, EnemyMetis, "Metis_1008");
                break;
            }
            case 50220: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000942);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40001002, EnemyMetis, "Metis_1009");
                break;
            }
            case 50250: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000943);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40001003, EnemyMetis, "Metis_1010");
                break;
            }
            case 50280: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000944);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40001004, EnemyMetis, "Metis_1011");
                break;
            }
            case 50310: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000945);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40001005, EnemyMetis, "Metis_1012");
                break;
            }
            case 50340: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000946);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40001006, EnemyMetis, "Metis_1013");
                break;
            }
            case 50370: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000947);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40001007, EnemyMetis, "Metis_1014");
                break;
            }
            case 50400: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000948);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40001008, EnemyMetis, "Metis_1015");
                break;
            }
            case 50430: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000949);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40001009, EnemyMetis, "Metis_1016");
                break;
            }
            case 50460: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000950);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40001010, EnemyMetis, "Metis_1017");
                break;
            }
            case 50490: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000951);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40001011, EnemyMetis, "Metis_1018");
                break;
            }
            case 50520: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000952);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40001012, EnemyMetis, "Metis_1019");
                break;
            }
            case 50550: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000953);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40001013, EnemyMetis, "Metis_1020");
                break;
            }
            case 50580: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000954);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40001014, EnemyMetis, "Metis_1021");
                break;
            }
            case 50610: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000955);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40001015, EnemyMetis, "Metis_1022");
                break;
            }
            case 50640: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000956);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40001016, EnemyMetis, "Metis_1023");
                break;
            }
            case 50670: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000957);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40001017, EnemyMetis, "Metis_1024");
                break;
            }
            case 50700: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000958);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40001018, EnemyMetis, "Metis_1025");
                break;
            }
            case 50730: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000959);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40001019, EnemyMetis, "Metis_1026");
                break;
            }
            case 50760: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000960);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40001020, EnemyMetis, "Metis_1027");
                break;
            }
            case 50790: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000961);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40001021, EnemyMetis, "Metis_1028");
                break;
            }
            case 50820: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000962);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40001022, EnemyMetis, "Metis_1029");
                break;
            }
            case 50850: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000963);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40001023, EnemyMetis, "Metis_1030");
                break;
            }
            case 50880: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000964);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40001024, EnemyMetis, "Metis_1031");
                break;
            }
            case 50910: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000965);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40001025, EnemyMetis, "Metis_1032");
                break;
            }
            case 50940: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000966);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40001026, EnemyMetis, "Metis_1033");
                break;
            }
            case 50970: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000967);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40001027, EnemyMetis, "Metis_1034");
                break;
            }
            case 51000: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000968);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40001028, EnemyMetis, "Metis_1035");
                break;
            }
            case 51030: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000969);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40001029, EnemyMetis, "Metis_1036");
                break;
            }
            case 51060: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000970);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40001030, EnemyMetis, "Metis_1037");
                break;
            }
            case 51090: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000971);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40001031, EnemyMetis, "Metis_1038");
                break;
            }
            case 51120: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000972);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40001032, EnemyMetis, "Metis_1039");
                break;
            }
            case 51150: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000973);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40001033, EnemyMetis, "Metis_1040");
                break;
            }
            case 51180: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000974);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40001034, EnemyMetis, "Metis_1041");
                break;
            }
            case 51210: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000975);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40001035, EnemyMetis, "Metis_1042");
                break;
            }
            case 51240: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000976);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40001036, EnemyMetis, "Metis_1043");
                break;
            }
            case 51270: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000977);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40001037, EnemyMetis, "Metis_1044");
                break;
            }
            case 51300: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000978);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40001038, EnemyMetis, "Metis_1045");
                break;
            }
            case 51330: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000979);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40001039, EnemyMetis, "Metis_1046");
                break;
            }
            case 51360: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000980);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40001040, EnemyMetis, "Metis_1047");
                break;
            }
            case 51390: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000981);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40001041, EnemyMetis, "Metis_1048");
                break;
            }
            case 51420: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000982);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40001042, EnemyMetis, "Metis_1049");
                break;
            }
            case 51450: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000983);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40001043, EnemyMetis, "Metis_1050");
                break;
            }
            case 51480: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000984);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40001044, EnemyMetis, "Metis_1051");
                break;
            }
            case 51510: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000985);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40001045, EnemyMetis, "Metis_1052");
                break;
            }
            case 51540: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000986);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40001046, EnemyMetis, "Metis_1053");
                break;
            }
            case 51570: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000987);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40001047, EnemyMetis, "Metis_1054");
                break;
            }
            case 51600: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000988);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40001048, EnemyMetis, "Metis_1055");
                break;
            }
            case 51630: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000989);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40001049, EnemyMetis, "Metis_1056");
                break;
            }
            case 51660: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000990);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40001050, EnemyMetis, "Metis_1057");
                break;
            }
            case 51690: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000991);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40001051, EnemyMetis, "Metis_1058");
                break;
            }
            case 51720: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000992);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40001052, EnemyMetis, "Metis_1059");
                break;
            }
            case 51750: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000993);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40001053, EnemyMetis, "Metis_1060");
                break;
            }
            case 51780: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000994);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40001054, EnemyMetis, "Metis_1061");
                break;
            }
            case 51810: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000995);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40001055, EnemyMetis, "Metis_1062");
                break;
            }
            case 51840: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000996);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40001056, EnemyMetis, "Metis_1063");
                break;
            }
            case 51870: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000997);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40001057, EnemyMetis, "Metis_1064");
                break;
            }
            case 51900: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000998);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40001058, EnemyMetis, "Metis_1065");
                break;
            }
            case 51930: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000999);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40001059, EnemyMetis, "Metis_1066");
                break;
            }
            case 51960: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001000);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40001060, EnemyMetis, "Metis_1067");
                break;
            }
            case 51990: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001001);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40001061, EnemyMetis, "Metis_1068");
                break;
            }
            case 52020: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001002);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40001062, EnemyMetis, "Metis_1069");
                break;
            }
            case 52050: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001003);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40001063, EnemyMetis, "Metis_1070");
                break;
            }
            case 52080: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001004);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40001064, EnemyMetis, "Metis_1071");
                break;
            }
            case 52110: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001005);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40001065, EnemyMetis, "Metis_1072");
                break;
            }
            case 52140: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001006);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40001066, EnemyMetis, "Metis_1073");
                break;
            }
            case 52170: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001007);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40001067, EnemyMetis, "Metis_1074");
                break;
            }
            case 52200: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001008);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40001068, EnemyMetis, "Metis_1075");
                break;
            }
            case 52230: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001009);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40001069, EnemyMetis, "Metis_1076");
                break;
            }
            case 52260: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001010);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40001070, EnemyMetis, "Metis_1077");
                break;
            }
            case 52290: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001011);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40001071, EnemyMetis, "Metis_1078");
                break;
            }
            case 52320: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001012);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40001072, EnemyMetis, "Metis_1079");
                break;
            }
            case 52350: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001013);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40001073, EnemyMetis, "Metis_1080");
                break;
            }
            case 52380: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001014);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40001074, EnemyMetis, "Metis_1081");
                break;
            }
            case 52410: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001015);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40001075, EnemyMetis, "Metis_1082");
                break;
            }
            case 52440: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001016);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40001076, EnemyMetis, "Metis_1083");
                break;
            }
            case 52470: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001017);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40001077, EnemyMetis, "Metis_1084");
                break;
            }
            case 52500: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001018);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40001078, EnemyMetis, "Metis_1085");
                break;
            }
            case 52530: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001019);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40001079, EnemyMetis, "Metis_1086");
                break;
            }
            case 52560: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001020);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40001080, EnemyMetis, "Metis_1087");
                break;
            }
            case 52590: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001021);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40001081, EnemyMetis, "Metis_1088");
                break;
            }
            case 52620: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001022);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40001082, EnemyMetis, "Metis_1089");
                break;
            }
            case 52650: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001023);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40001083, EnemyMetis, "Metis_1090");
                break;
            }
            case 52680: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001024);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40001084, EnemyMetis, "Metis_1091");
                break;
            }
            case 52710: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001025);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40001085, EnemyMetis, "Metis_1092");
                break;
            }
            case 52740: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001026);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40001086, EnemyMetis, "Metis_1093");
                break;
            }
            case 52770: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001027);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40001087, EnemyMetis, "Metis_1094");
                break;
            }
            case 52800: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001028);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40001088, EnemyMetis, "Metis_1095");
                break;
            }
            case 52830: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001029);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40001089, EnemyMetis, "Metis_1096");
                break;
            }
            case 52860: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001030);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40001090, EnemyMetis, "Metis_1097");
                break;
            }
            case 52890: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001031);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40001091, EnemyMetis, "Metis_1098");
                break;
            }
            case 52920: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001032);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40001092, EnemyMetis, "Metis_1099");
                break;
            }
            case 52950: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001033);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40001093, EnemyMetis, "Metis_1100");
                break;
            }
            case 52980: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001034);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40001094, EnemyMetis, "Metis_1101");
                break;
            }
            case 53010: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001035);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40001095, EnemyMetis, "Metis_1102");
                break;
            }
            case 53040: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001036);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40001096, EnemyMetis, "Metis_1103");
                break;
            }
            case 53070: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001037);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40001097, EnemyMetis, "Metis_1104");
                break;
            }
            case 53100: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001038);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40001098, EnemyMetis, "Metis_1105");
                break;
            }
            case 53130: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001039);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40001099, EnemyMetis, "Metis_1106");
                break;
            }
            case 53160: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001040);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40001100, EnemyMetis, "Metis_1107");
                break;
            }
            case 53190: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001041);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40001101, EnemyMetis, "Metis_1108");
                break;
            }
            case 53220: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001042);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40001102, EnemyMetis, "Metis_1109");
                break;
            }
            case 53250: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001043);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40001103, EnemyMetis, "Metis_1110");
                break;
            }
            case 53280: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001044);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40001104, EnemyMetis, "Metis_1111");
                break;
            }
            case 53310: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001045);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40001105, EnemyMetis, "Metis_1112");
                break;
            }
            case 53340: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001046);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40001106, EnemyMetis, "Metis_1113");
                break;
            }
            case 53370: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001047);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40001107, EnemyMetis, "Metis_1114");
                break;
            }
            case 53400: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001048);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40001108, EnemyMetis, "Metis_1115");
                break;
            }
            case 53430: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001049);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40001109, EnemyMetis, "Metis_1116");
                break;
            }
            case 53460: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001050);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40001110, EnemyMetis, "Metis_1117");
                break;
            }
            case 53490: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001051);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40001111, EnemyMetis, "Metis_1118");
                break;
            }
            case 53520: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001052);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40001112, EnemyMetis, "Metis_1119");
                break;
            }
            case 53550: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001053);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40001113, EnemyMetis, "Metis_1120");
                break;
            }
            case 53580: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001054);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40001114, EnemyMetis, "Metis_1121");
                break;
            }
            case 53610: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001055);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40001115, EnemyMetis, "Metis_1122");
                break;
            }
            case 53640: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001056);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40001116, EnemyMetis, "Metis_1123");
                break;
            }
            case 53670: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001057);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40001117, EnemyMetis, "Metis_1124");
                break;
            }
            case 53700: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001058);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40001118, EnemyMetis, "Metis_1125");
                break;
            }
            case 53730: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001059);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40001119, EnemyMetis, "Metis_1126");
                break;
            }
            case 53760: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001060);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40001120, EnemyMetis, "Metis_1127");
                break;
            }
            case 53790: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001061);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40001121, EnemyMetis, "Metis_1128");
                break;
            }
            case 53820: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001062);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40001122, EnemyMetis, "Metis_1129");
                break;
            }
            case 53850: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001063);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40001123, EnemyMetis, "Metis_1130");
                break;
            }
            case 53880: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001064);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40001124, EnemyMetis, "Metis_1131");
                break;
            }
            case 53910: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001065);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40001125, EnemyMetis, "Metis_1132");
                break;
            }
            case 53940: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001066);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40001126, EnemyMetis, "Metis_1133");
                break;
            }
            case 53970: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001067);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40001127, EnemyMetis, "Metis_1134");
                break;
            }
            case 54000: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001068);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40001128, EnemyMetis, "Metis_1135");
                break;
            }
            case 54030: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001069);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40001129, EnemyMetis, "Metis_1136");
                break;
            }
            case 54060: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001070);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40001130, EnemyMetis, "Metis_1137");
                break;
            }
            case 54090: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001071);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40001131, EnemyMetis, "Metis_1138");
                break;
            }
            case 54120: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001072);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40001132, EnemyMetis, "Metis_1139");
                break;
            }
            case 54150: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001073);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40001133, EnemyMetis, "Metis_1140");
                break;
            }
            case 54180: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001074);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40001134, EnemyMetis, "Metis_1141");
                break;
            }
            case 54210: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001075);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40001135, EnemyMetis, "Metis_1142");
                break;
            }
            case 54240: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001076);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40001136, EnemyMetis, "Metis_1143");
                break;
            }
            case 54270: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001077);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40001137, EnemyMetis, "Metis_1144");
                break;
            }
            case 54300: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001078);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40001138, EnemyMetis, "Metis_1145");
                break;
            }
            case 54330: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001079);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40001139, EnemyMetis, "Metis_1146");
                break;
            }
            case 54360: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001080);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40001140, EnemyMetis, "Metis_1147");
                break;
            }
            case 54390: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001081);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40001141, EnemyMetis, "Metis_1148");
                break;
            }
            case 54420: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001082);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40001142, EnemyMetis, "Metis_1149");
                break;
            }
            case 54450: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001083);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40001143, EnemyMetis, "Metis_1150");
                break;
            }
            case 54480: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001084);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40001144, EnemyMetis, "Metis_1151");
                break;
            }
            case 54510: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001085);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40001145, EnemyMetis, "Metis_1152");
                break;
            }
            case 54540: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001086);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40001146, EnemyMetis, "Metis_1153");
                break;
            }
            case 54570: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001087);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40001147, EnemyMetis, "Metis_1154");
                break;
            }
            case 54600: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001088);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40001148, EnemyMetis, "Metis_1155");
                break;
            }
            case 54630: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001089);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40001149, EnemyMetis, "Metis_1156");
                break;
            }
            case 54660: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001090);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40001150, EnemyMetis, "Metis_1157");
                break;
            }
            case 54690: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001091);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40001151, EnemyMetis, "Metis_1158");
                break;
            }
            case 54720: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001092);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40001152, EnemyMetis, "Metis_1159");
                break;
            }
            case 54750: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001093);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40001153, EnemyMetis, "Metis_1160");
                break;
            }
            case 54780: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001094);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40001154, EnemyMetis, "Metis_1161");
                break;
            }
            case 54810: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001095);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40001155, EnemyMetis, "Metis_1162");
                break;
            }
            case 54840: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001096);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40001156, EnemyMetis, "Metis_1163");
                break;
            }
            case 54870: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001097);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40001157, EnemyMetis, "Metis_1164");
                break;
            }
            case 54900: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001098);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40001158, EnemyMetis, "Metis_1165");
                break;
            }
            case 54930: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001099);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40001159, EnemyMetis, "Metis_1166");
                break;
            }
            case 54960: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001100);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40001160, EnemyMetis, "Metis_1167");
                break;
            }
            case 54990: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001101);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40001161, EnemyMetis, "Metis_1168");
                break;
            }
            case 55020: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001102);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40001162, EnemyMetis, "Metis_1169");
                break;
            }
            case 55050: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001103);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40001163, EnemyMetis, "Metis_1170");
                break;
            }
            case 55080: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001104);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40001164, EnemyMetis, "Metis_1171");
                break;
            }
            case 55110: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001105);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40001165, EnemyMetis, "Metis_1172");
                break;
            }
            case 55140: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001106);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40001166, EnemyMetis, "Metis_1173");
                break;
            }
            case 55170: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001107);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40001167, EnemyMetis, "Metis_1174");
                break;
            }
            case 55200: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001108);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40001168, EnemyMetis, "Metis_1175");
                break;
            }
            case 55230: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001109);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40001169, EnemyMetis, "Metis_1176");
                break;
            }
            case 55260: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001110);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40001170, EnemyMetis, "Metis_1177");
                break;
            }
            case 55290: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001111);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40001171, EnemyMetis, "Metis_1178");
                break;
            }
            case 55320: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001112);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40001172, EnemyMetis, "Metis_1179");
                break;
            }
            case 55350: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001113);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40001173, EnemyMetis, "Metis_1180");
                break;
            }
            case 55380: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001114);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40001174, EnemyMetis, "Metis_1181");
                break;
            }
            case 55410: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001115);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40001175, EnemyMetis, "Metis_1182");
                break;
            }
            case 55440: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001116);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40001176, EnemyMetis, "Metis_1183");
                break;
            }
            case 55470: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001117);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40001177, EnemyMetis, "Metis_1184");
                break;
            }
            case 55500: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001118);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40001178, EnemyMetis, "Metis_1185");
                break;
            }
            case 55530: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001119);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40001179, EnemyMetis, "Metis_1186");
                break;
            }
            case 55560: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001120);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40001180, EnemyMetis, "Metis_1187");
                break;
            }
            case 55590: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001121);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40001181, EnemyMetis, "Metis_1188");
                break;
            }
            case 55620: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001122);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40001182, EnemyMetis, "Metis_1189");
                break;
            }
            case 55650: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001123);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40001183, EnemyMetis, "Metis_1190");
                break;
            }
            case 55680: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001124);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40001184, EnemyMetis, "Metis_1191");
                break;
            }
            case 55710: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001125);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40001185, EnemyMetis, "Metis_1192");
                break;
            }
            case 55740: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001126);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40001186, EnemyMetis, "Metis_1193");
                break;
            }
            case 55770: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001127);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40001187, EnemyMetis, "Metis_1194");
                break;
            }
            case 55800: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001128);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40001188, EnemyMetis, "Metis_1195");
                break;
            }
            case 55830: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001129);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40001189, EnemyMetis, "Metis_1196");
                break;
            }
            case 55860: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001130);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40001190, EnemyMetis, "Metis_1197");
                break;
            }
            case 55890: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001131);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40001191, EnemyMetis, "Metis_1198");
                break;
            }
            case 55920: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001132);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40001192, EnemyMetis, "Metis_1199");
                break;
            }
            case 55950: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001133);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40001193, EnemyMetis, "Metis_1200");
                break;
            }
            case 55980: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001134);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40001194, EnemyMetis, "Metis_1201");
                break;
            }
            case 56010: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001135);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40001195, EnemyMetis, "Metis_1202");
                break;
            }
            case 56040: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001136);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40001196, EnemyMetis, "Metis_1203");
                break;
            }
            case 56070: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001137);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40001197, EnemyMetis, "Metis_1204");
                break;
            }
            case 56100: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001138);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40001198, EnemyMetis, "Metis_1205");
                break;
            }
            case 56130: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001139);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40001199, EnemyMetis, "Metis_1206");
                break;
            }
            case 56160: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001140);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40001200, EnemyMetis, "Metis_1207");
                break;
            }
            case 56190: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001141);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40001201, EnemyMetis, "Metis_1208");
                break;
            }
            case 56220: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001142);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40001202, EnemyMetis, "Metis_1209");
                break;
            }
            case 56250: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001143);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40001203, EnemyMetis, "Metis_1210");
                break;
            }
            case 56280: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001144);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40001204, EnemyMetis, "Metis_1211");
                break;
            }
            case 56310: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001145);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40001205, EnemyMetis, "Metis_1212");
                break;
            }
            case 56340: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001146);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40001206, EnemyMetis, "Metis_1213");
                break;
            }
            case 56370: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001147);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40001207, EnemyMetis, "Metis_1214");
                break;
            }
            case 56400: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001148);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40001208, EnemyMetis, "Metis_1215");
                break;
            }
            case 56430: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001149);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40001209, EnemyMetis, "Metis_1216");
                break;
            }
            case 56460: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001150);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40001210, EnemyMetis, "Metis_1217");
                break;
            }
            case 56490: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001151);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40001211, EnemyMetis, "Metis_1218");
                break;
            }
            case 56520: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001152);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40001212, EnemyMetis, "Metis_1219");
                break;
            }
            case 56550: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001153);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40001213, EnemyMetis, "Metis_1220");
                break;
            }
            case 56580: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001154);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40001214, EnemyMetis, "Metis_1221");
                break;
            }
            case 56610: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001155);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40001215, EnemyMetis, "Metis_1222");
                break;
            }
            case 56640: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001156);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40001216, EnemyMetis, "Metis_1223");
                break;
            }
            case 56670: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001157);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40001217, EnemyMetis, "Metis_1224");
                break;
            }
            case 56700: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001158);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40001218, EnemyMetis, "Metis_1225");
                break;
            }
            case 56730: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001159);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40001219, EnemyMetis, "Metis_1226");
                break;
            }
            case 56760: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001160);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40001220, EnemyMetis, "Metis_1227");
                break;
            }
            case 56790: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001161);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40001221, EnemyMetis, "Metis_1228");
                break;
            }
            case 56820: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001162);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40001222, EnemyMetis, "Metis_1229");
                break;
            }
            case 56850: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001163);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40001223, EnemyMetis, "Metis_1230");
                break;
            }
            case 56880: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001164);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40001224, EnemyMetis, "Metis_1231");
                break;
            }
            case 56910: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001165);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40001225, EnemyMetis, "Metis_1232");
                break;
            }
            case 56940: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001166);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40001226, EnemyMetis, "Metis_1233");
                break;
            }
            case 56970: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001167);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40001227, EnemyMetis, "Metis_1234");
                break;
            }
            case 57000: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001168);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40001228, EnemyMetis, "Metis_1235");
                break;
            }
            case 57030: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001169);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40001229, EnemyMetis, "Metis_1236");
                break;
            }
            case 57060: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001170);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40001230, EnemyMetis, "Metis_1237");
                break;
            }
            case 57090: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001171);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40001231, EnemyMetis, "Metis_1238");
                break;
            }
            case 57120: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001172);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40001232, EnemyMetis, "Metis_1239");
                break;
            }
            case 57150: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001173);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40001233, EnemyMetis, "Metis_1240");
                break;
            }
            case 57180: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001174);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40001234, EnemyMetis, "Metis_1241");
                break;
            }
            case 57210: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001175);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40001235, EnemyMetis, "Metis_1242");
                break;
            }
            case 57240: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001176);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40001236, EnemyMetis, "Metis_1243");
                break;
            }
            case 57270: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001177);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40001237, EnemyMetis, "Metis_1244");
                break;
            }
            case 57300: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001178);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40001238, EnemyMetis, "Metis_1245");
                break;
            }
            case 57330: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001179);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40001239, EnemyMetis, "Metis_1246");
                break;
            }
            case 57360: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001180);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40001240, EnemyMetis, "Metis_1247");
                break;
            }
            case 57390: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001181);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40001241, EnemyMetis, "Metis_1248");
                break;
            }
            case 57420: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001182);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40001242, EnemyMetis, "Metis_1249");
                break;
            }
            case 57450: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001183);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40001243, EnemyMetis, "Metis_1250");
                break;
            }
            case 57480: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001184);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40001244, EnemyMetis, "Metis_1251");
                break;
            }
            case 57510: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001185);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40001245, EnemyMetis, "Metis_1252");
                break;
            }
            case 57540: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001186);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40001246, EnemyMetis, "Metis_1253");
                break;
            }
            case 57570: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001187);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40001247, EnemyMetis, "Metis_1254");
                break;
            }
            case 57600: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001188);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40001248, EnemyMetis, "Metis_1255");
                break;
            }
            case 57630: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001189);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40001249, EnemyMetis, "Metis_1256");
                break;
            }
            case 57660: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001190);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40001250, EnemyMetis, "Metis_1257");
                break;
            }
            case 57690: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001191);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40001251, EnemyMetis, "Metis_1258");
                break;
            }
            case 57720: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001192);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40001252, EnemyMetis, "Metis_1259");
                break;
            }
            case 57750: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001193);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40001253, EnemyMetis, "Metis_1260");
                break;
            }
            case 57780: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001194);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40001254, EnemyMetis, "Metis_1261");
                break;
            }
            case 57810: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001195);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40001255, EnemyMetis, "Metis_1262");
                break;
            }
            case 57840: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001196);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40001256, EnemyMetis, "Metis_1263");
                break;
            }
            case 57870: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001197);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40001257, EnemyMetis, "Metis_1264");
                break;
            }
            case 57900: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001198);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40001258, EnemyMetis, "Metis_1265");
                break;
            }
            case 57930: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001199);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40001259, EnemyMetis, "Metis_1266");
                break;
            }
            case 57960: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001200);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40001260, EnemyMetis, "Metis_1267");
                break;
            }
            case 57990: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001201);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40001261, EnemyMetis, "Metis_1268");
                break;
            }
            case 58020: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001202);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40001262, EnemyMetis, "Metis_1269");
                break;
            }
            case 58050: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001203);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40001263, EnemyMetis, "Metis_1270");
                break;
            }
            case 58080: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001204);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40001264, EnemyMetis, "Metis_1271");
                break;
            }
            case 58110: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001205);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40001265, EnemyMetis, "Metis_1272");
                break;
            }
            case 58140: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001206);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40001266, EnemyMetis, "Metis_1273");
                break;
            }
            case 58170: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001207);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40001267, EnemyMetis, "Metis_1274");
                break;
            }
            case 58200: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001208);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40001268, EnemyMetis, "Metis_1275");
                break;
            }
            case 58230: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001209);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40001269, EnemyMetis, "Metis_1276");
                break;
            }
            case 58260: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001210);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40001270, EnemyMetis, "Metis_1277");
                break;
            }
            case 58290: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001211);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40001271, EnemyMetis, "Metis_1278");
                break;
            }
            case 58320: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001212);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40001272, EnemyMetis, "Metis_1279");
                break;
            }
            case 58350: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001213);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40001273, EnemyMetis, "Metis_1280");
                break;
            }
            case 58380: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001214);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40001274, EnemyMetis, "Metis_1281");
                break;
            }
            case 58410: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001215);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40001275, EnemyMetis, "Metis_1282");
                break;
            }
            case 58440: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001216);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40001276, EnemyMetis, "Metis_1283");
                break;
            }
            case 58470: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001217);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40001277, EnemyMetis, "Metis_1284");
                break;
            }
            case 58500: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001218);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40001278, EnemyMetis, "Metis_1285");
                break;
            }
            case 58530: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001219);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40001279, EnemyMetis, "Metis_1286");
                break;
            }
            case 58560: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001220);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40001280, EnemyMetis, "Metis_1287");
                break;
            }
            case 58590: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001221);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40001281, EnemyMetis, "Metis_1288");
                break;
            }
            case 58620: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001222);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40001282, EnemyMetis, "Metis_1289");
                break;
            }
            case 58650: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001223);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40001283, EnemyMetis, "Metis_1290");
                break;
            }
            case 58680: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001224);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40001284, EnemyMetis, "Metis_1291");
                break;
            }
            case 58710: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001225);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40001285, EnemyMetis, "Metis_1292");
                break;
            }
            case 58740: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001226);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40001286, EnemyMetis, "Metis_1293");
                break;
            }
            case 58770: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001227);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40001287, EnemyMetis, "Metis_1294");
                break;
            }
            case 58800: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001228);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40001288, EnemyMetis, "Metis_1295");
                break;
            }
            case 58830: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001229);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40001289, EnemyMetis, "Metis_1296");
                break;
            }
            case 58860: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001230);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40001290, EnemyMetis, "Metis_1297");
                break;
            }
            case 58890: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001231);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40001291, EnemyMetis, "Metis_1298");
                break;
            }
            case 58920: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001232);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40001292, EnemyMetis, "Metis_1299");
                break;
            }
            case 58950: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001233);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40001293, EnemyMetis, "Metis_1300");
                break;
            }
            case 58980: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001234);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40001294, EnemyMetis, "Metis_1301");
                break;
            }
            case 59010: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001235);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40001295, EnemyMetis, "Metis_1302");
                break;
            }
            case 59040: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001236);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40001296, EnemyMetis, "Metis_1303");
                break;
            }
            case 59070: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001237);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40001297, EnemyMetis, "Metis_1304");
                break;
            }
            case 59100: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001238);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40001298, EnemyMetis, "Metis_1305");
                break;
            }
            case 59130: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001239);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40001299, EnemyMetis, "Metis_1306");
                break;
            }
            case 59160: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001240);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40001300, EnemyMetis, "Metis_1307");
                break;
            }
            case 59190: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001241);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40001301, EnemyMetis, "Metis_1308");
                break;
            }
            case 59220: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001242);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40001302, EnemyMetis, "Metis_1309");
                break;
            }
            case 59250: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001243);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40001303, EnemyMetis, "Metis_1310");
                break;
            }
            case 59280: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001244);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40001304, EnemyMetis, "Metis_1311");
                break;
            }
            case 59310: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001245);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40001305, EnemyMetis, "Metis_1312");
                break;
            }
            case 59340: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001246);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40001306, EnemyMetis, "Metis_1313");
                break;
            }
            case 59370: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001247);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40001307, EnemyMetis, "Metis_1314");
                break;
            }
            case 59400: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001248);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40001308, EnemyMetis, "Metis_1315");
                break;
            }
            case 59430: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001249);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40001309, EnemyMetis, "Metis_1316");
                break;
            }
            case 59460: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001250);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40001310, EnemyMetis, "Metis_1317");
                break;
            }
            case 59490: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001251);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40001311, EnemyMetis, "Metis_1318");
                break;
            }
            case 59520: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001252);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40001312, EnemyMetis, "Metis_1319");
                break;
            }
            case 59550: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001253);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40001313, EnemyMetis, "Metis_1320");
                break;
            }
            case 59580: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001254);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40001314, EnemyMetis, "Metis_1321");
                break;
            }
            case 59610: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001255);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40001315, EnemyMetis, "Metis_1322");
                break;
            }
            case 59640: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001256);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40001316, EnemyMetis, "Metis_1323");
                break;
            }
            case 59670: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001257);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40001317, EnemyMetis, "Metis_1324");
                break;
            }
            case 59700: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001258);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40001318, EnemyMetis, "Metis_1325");
                break;
            }
            case 59730: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001259);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40001319, EnemyMetis, "Metis_1326");
                break;
            }
            case 59760: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001260);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40001320, EnemyMetis, "Metis_1327");
                break;
            }
            case 59790: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001261);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40001321, EnemyMetis, "Metis_1328");
                break;
            }
            case 59820: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001262);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40001322, EnemyMetis, "Metis_1329");
                break;
            }
            case 59850: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001263);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40001323, EnemyMetis, "Metis_1330");
                break;
            }
            case 59880: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001264);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40001324, EnemyMetis, "Metis_1331");
                break;
            }
            case 59910: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001265);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40001325, EnemyMetis, "Metis_1332");
                break;
            }
            case 59940: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001266);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40001326, EnemyMetis, "Metis_1333");
                break;
            }
            case 59970: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001267);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40001327, EnemyMetis, "Metis_1334");
                break;
            }
            case 60000: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001268);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40001328, EnemyMetis, "Metis_1335");
                break;
            }
            case 60030: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001269);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40001329, EnemyMetis, "Metis_1336");
                break;
            }
            case 60060: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001270);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40001330, EnemyMetis, "Metis_1337");
                break;
            }
            case 60090: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001271);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40001331, EnemyMetis, "Metis_1338");
                break;
            }
            case 60120: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001272);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40001332, EnemyMetis, "Metis_1339");
                break;
            }
            case 60150: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001273);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40001333, EnemyMetis, "Metis_1340");
                break;
            }
            case 60180: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001274);
                getDirector()->addSubGroup(pMetis2);
                orderActorToFactory(40001334, EnemyMetis, "Metis_1341");
                break;
            }
            case 60210: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001275);
                getDirector()->addSubGroup(pMetis2);
                break;
            }
            case 60240: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001276);
                getDirector()->addSubGroup(pMetis2);
                break;
            }
            case 60270: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001277);
                getDirector()->addSubGroup(pMetis2);
                break;
            }
            case 60300: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001278);
                getDirector()->addSubGroup(pMetis2);
                break;
            }
            case 60330: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001279);
                getDirector()->addSubGroup(pMetis2);
                break;
            }
            case 60360: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001280);
                getDirector()->addSubGroup(pMetis2);
                break;
            }
            case 60390: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001281);
                getDirector()->addSubGroup(pMetis2);
                break;
            }
            case 60420: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001282);
                getDirector()->addSubGroup(pMetis2);
                break;
            }
            case 60450: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001283);
                getDirector()->addSubGroup(pMetis2);
                break;
            }
            case 60480: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001284);
                getDirector()->addSubGroup(pMetis2);
                break;
            }
            case 60510: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001285);
                getDirector()->addSubGroup(pMetis2);
                break;
            }
            case 60540: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001286);
                getDirector()->addSubGroup(pMetis2);
                break;
            }
            case 60570: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001287);
                getDirector()->addSubGroup(pMetis2);
                break;
            }
            case 60600: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001288);
                getDirector()->addSubGroup(pMetis2);
                break;
            }
            case 60630: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001289);
                getDirector()->addSubGroup(pMetis2);
                break;
            }
            case 60660: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001290);
                getDirector()->addSubGroup(pMetis2);
                break;
            }
            case 60690: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001291);
                getDirector()->addSubGroup(pMetis2);
                break;
            }
            case 60720: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001292);
                getDirector()->addSubGroup(pMetis2);
                break;
            }
            case 60750: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001293);
                getDirector()->addSubGroup(pMetis2);
                break;
            }
            case 60780: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001294);
                getDirector()->addSubGroup(pMetis2);
                break;
            }
            case 60810: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001295);
                getDirector()->addSubGroup(pMetis2);
                break;
            }
            case 60840: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001296);
                getDirector()->addSubGroup(pMetis2);
                break;
            }
            case 60870: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001297);
                getDirector()->addSubGroup(pMetis2);
                break;
            }
            case 60900: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001298);
                getDirector()->addSubGroup(pMetis2);
                break;
            }
            case 60930: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001299);
                getDirector()->addSubGroup(pMetis2);
                break;
            }
            case 60960: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001300);
                getDirector()->addSubGroup(pMetis2);
                break;
            }
            case 60990: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001301);
                getDirector()->addSubGroup(pMetis2);
                break;
            }
            case 61020: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001302);
                getDirector()->addSubGroup(pMetis2);
                break;
            }
            case 61050: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001303);
                getDirector()->addSubGroup(pMetis2);
                break;
            }
            case 61080: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001304);
                getDirector()->addSubGroup(pMetis2);
                break;
            }
            case 61110: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001305);
                getDirector()->addSubGroup(pMetis2);
                break;
            }
            case 61140: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001306);
                getDirector()->addSubGroup(pMetis2);
                break;
            }
            case 61170: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001307);
                getDirector()->addSubGroup(pMetis2);
                break;
            }
            case 61200: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001308);
                getDirector()->addSubGroup(pMetis2);
                break;
            }
            case 61230: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001309);
                getDirector()->addSubGroup(pMetis2);
                break;
            }
            case 61260: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001310);
                getDirector()->addSubGroup(pMetis2);
                break;
            }
            case 61290: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001311);
                getDirector()->addSubGroup(pMetis2);
                break;
            }
            case 61320: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001312);
                getDirector()->addSubGroup(pMetis2);
                break;
            }
            case 61350: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001313);
                getDirector()->addSubGroup(pMetis2);
                break;
            }
            case 61380: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001314);
                getDirector()->addSubGroup(pMetis2);
                break;
            }
            case 61410: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001315);
                getDirector()->addSubGroup(pMetis2);
                break;
            }
            case 61440: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001316);
                getDirector()->addSubGroup(pMetis2);
                break;
            }
            case 61470: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001317);
                getDirector()->addSubGroup(pMetis2);
                break;
            }
            case 61500: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001318);
                getDirector()->addSubGroup(pMetis2);
                break;
            }
            case 61530: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001319);
                getDirector()->addSubGroup(pMetis2);
                break;
            }
            case 61560: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001320);
                getDirector()->addSubGroup(pMetis2);
                break;
            }
            case 61590: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001321);
                getDirector()->addSubGroup(pMetis2);
                break;
            }
            case 61620: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001322);
                getDirector()->addSubGroup(pMetis2);
                break;
            }
            case 61650: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001323);
                getDirector()->addSubGroup(pMetis2);
                break;
            }
            case 61680: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001324);
                getDirector()->addSubGroup(pMetis2);
                break;
            }
            case 61710: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001325);
                getDirector()->addSubGroup(pMetis2);
                break;
            }
            case 61740: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001326);
                getDirector()->addSubGroup(pMetis2);
                break;
            }
            case 61770: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001327);
                getDirector()->addSubGroup(pMetis2);
                break;
            }
            case 61800: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001328);
                getDirector()->addSubGroup(pMetis2);
                break;
            }
            case 61830: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001329);
                getDirector()->addSubGroup(pMetis2);
                break;
            }
            case 61860: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001330);
                getDirector()->addSubGroup(pMetis2);
                break;
            }
            case 61890: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001331);
                getDirector()->addSubGroup(pMetis2);
                break;
            }
            case 61920: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001332);
                getDirector()->addSubGroup(pMetis2);
                break;
            }
            case 61950: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001333);
                getDirector()->addSubGroup(pMetis2);
                break;
            }
            case 61980: {
                EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40001334);
                getDirector()->addSubGroup(pMetis2);
                break;
            }
            default :
                break;
        }
        _iCnt_Event = (_iCnt_Event < 1419-1 ? _iCnt_Event+1 : _iCnt_Event);
    }
    // gen02 end
}

Stage01_02::~Stage01_02() {

}
