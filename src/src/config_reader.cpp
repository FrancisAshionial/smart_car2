#include <fstream>
#include <iostream>
#include <cmath>
#include "../include/common.hpp"
#include "../include/json.hpp"
#include "controlcenter_cal.cpp"

using namespace std;
using nlohmann::json;

class ConfigReader{
public:
     struct Params
    {
        float speedLow = 1.0;                           // 智能车最低速
        float speedHigh = 1.0;                          // 智能车最高速
        float speedDown = 0.6;                          // 特殊区域降速速度
        float speedBridge = 1.0;                        // 坡道（桥）行驶速度
        float speedSlowzone = 1.0;                      // 慢行区行驶速度
        float speedGarage = 1.0;                        // 出入车库速度
        float runP1 = 0.9;                              // 一阶比例系数：直线控制量
        float runP2 = 0.018;                            // 二阶比例系数：弯道控制量
        float runP3 = 0.0;                              // 三阶比例系数：弯道控制量
        float turnP = 3.5;                              // 一阶比例系数：转弯控制量
        float turnD = 3.5;                              // 一阶微分系数：转弯控制量
        bool debug = false;                             // 调试模式使能
        bool saveImage = false;                         // 存图使能
        uint16_t rowCutUp = 10;                         // 图像顶部切行
        uint16_t rowCutBottom = 10;                     // 图像顶部切行
        float disGarageEntry = 0.7;                     // 车库入库距离(斑马线Image占比)
        bool GarageEnable = true;                       // 出入库使能
        bool BridgeEnable = true;                       // 坡道使能
        bool FreezoneEnable = true;                     // 泛行区使能
        bool RingEnable = true;                         // 环岛使能
        bool CrossEnable = true;                        // 十字使能
        bool GranaryEnable = true;                      // 粮仓使能
        bool DepotEnable = true;                        // 修车厂使能
        bool FarmlandEnable = true;                     // 农田使能
        bool SlowzoneEnable = true;                     // 慢行区使能
        uint16_t circles = 2;                           // 智能车运行圈数
        string pathVideo = "../res/samples/sample.mp4"; // 视频路径
        NLOHMANN_DEFINE_TYPE_INTRUSIVE(Params, speedLow, speedHigh, speedDown, speedBridge, speedSlowzone, speedGarage,
                                       runP1, runP2, runP3, turnP, turnD, debug, saveImage, rowCutUp, rowCutBottom, disGarageEntry,
                                       GarageEnable, BridgeEnable, FreezoneEnable, RingEnable, CrossEnable, GranaryEnable, DepotEnable, FarmlandEnable, SlowzoneEnable, circles, pathVideo); // 添加构造函数
    };

    Params params;                   // 读取控制参数

    /**
     * @brief 加载配置参数Json
     */
    void loadParams()
    {
        string jsonPath = "../src/config/motion.json";
        std::ifstream config_is(jsonPath);
        if (!config_is.good())
        {
            std::cout << "Error: Params file path:[" << jsonPath
                      << "] not find .\n";
            exit(-1);
        }

        json js_value;
        config_is >> js_value;

        try
        {
            params = js_value.get<Params>();
        }
        catch (const nlohmann::detail::exception &e)
        {
            std::cerr << "Json Params Parse failed :" << e.what() << '\n';
            exit(-1);
        }

        //motorSpeed = params.speedLow;
        cout << "--- runP1:" << params.runP1 << " | runP2:" << params.runP2 << " | runP3:" << params.runP3 << endl;
        cout << "--- turnP:" << params.turnP << " | turnD:" << params.turnD << endl;
        cout << "--- speedLow:" << params.speedLow << "m/s  |  speedHigh:" << params.speedHigh << "m/s" << endl;
    }
};