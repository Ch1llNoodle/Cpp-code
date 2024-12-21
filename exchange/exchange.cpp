#define NOMINMAX // 防止 Windows.h 宏定义 max 和 min 导致冲突
#include <iostream>
#include <string>
#include <curl/curl.h>
#include <json/json.h>

using namespace std;

// 声明需要调用的函数
void clearScreen();
void currencies();
void calculate(const string& fromCode, const string& toCode);
float fetch_exchange_rate(const string& fromCode, const string& toCode, float money);

// API 配置信息
const string appcode = "19015e4d20284658a3b7a4feac8e1a07";
const string host = "https://tysjhlcx.market.alicloudapi.com";
const string path = "/exchange_rate/convert";

// CURL 回调函数
size_t WriteCallback(void* contents, size_t size, size_t nmemb, string* userp) {
    userp->append((char*)contents, size * nmemb);
    return size * nmemb;
}

int main() {
    char sev_type;
    cout << "--------------------------------" << endl;
    cout << "|*****欢迎进入外币兑换系统*****|" << endl;
    cout << "--------------------------------" << endl;
    while (1) {
        cout << "一、请选择兑换方式:" << endl;
        cout << "    1.外币兑换人民币(1)" << endl;
        cout << "    2.人民币兑换外币(2)" << endl;
        cout << "    3.退出系统(0)" << endl;
        cin >> sev_type;
        clearScreen(); // 清除之前的输出
        if (sev_type != '1' && sev_type != '2' && sev_type != '0') {
            cout << "无效选择，请重新输入..." << endl;
        } else if (sev_type == '1') {
            cout << "您的选择是：外币兑换人民币" << endl;
            currencies();
        } else if (sev_type == '2') {
            cout << "您的选择是：人民币兑换外币" << endl;
            currencies();
        } else if (sev_type == '0') {
            cout << "感谢您的使用" << endl;
            return 0;
        }
    }
}
void clearScreen() {
    cout << "\033[2J\033[1;1H"; // 使用 ANSI Escape Code 清屏
}

void currencies() {
    int kind;
    string fromCode, toCode = "CNY"; // 默认目标币种为人民币
    while (1) {
        cout << endl;
        cout << "二、请选择兑换币种：" << endl;
        cout << "    1.英镑(GBP)" << endl;
        cout << "    2.欧元(EUR)" << endl;
        cout << "    3.美元(USD)" << endl;
        cout << "    4.港币(HKD)" << endl;
        cout << "    5.澳元(AUD)" << endl;
        cout << "    6.日元(JPY)" << endl;
        cout << "    7.韩元(KRW)" << endl;
        cout << "    8.泰铢(THB)" << endl;
        cout << "    9.卢布(RUB)" << endl;
        cin >> kind;
        clearScreen(); // 清除之前的输出

        switch (kind) {
            case 1: fromCode = "GBP"; break;
            case 2: fromCode = "EUR"; break;
            case 3: fromCode = "USD"; break;
            case 4: fromCode = "HKD"; break;
            case 5: fromCode = "AUD"; break;
            case 6: fromCode = "JPY"; break;
            case 7: fromCode = "KRW"; break;
            case 8: fromCode = "THB"; break;
            case 9: fromCode = "RUB"; break;
            default:
                cout << "无效选择，请重新输入..." << endl;
                cin.clear();
                cin.sync();
                continue;
        }
        cout << "您的选择是：" << fromCode << endl;
        calculate(fromCode, toCode);
        break;
    }
}

void calculate(const string& fromCode, const string& toCode) {
    float num;
    while (1) {
        cout << endl;
        cout << "三、请输入兑换金额：";
        cin >> num;
        if (num <= 0 || cin.fail()) {
            cout << "无效输入，请输入一个正数！" << endl;
            cin.clear(); // 清除cin的错误状态
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // 忽略缓冲区中直到下一个换行符的所有字符
        } else {
            break;
        }
    }

    // 调用 API 获取汇率
    float exchange = fetch_exchange_rate(fromCode, toCode, num);
    if (exchange != -1) {
        cout << "兑换结果：" << num << " " << fromCode << " = " << exchange << " " << toCode << endl;
    } else {
        cout << "获取汇率失败，请稍后再试！" << endl;
    }
}

float fetch_exchange_rate(const string& fromCode, const string& toCode, float money) {
    CURL* curl;
    CURLcode res;
    string readBuffer;

    curl = curl_easy_init();
    if (curl) {
        // 构建完整 URL
        string querys = "?fromCode=" + fromCode + "&toCode=" + toCode + "&money=" + to_string(money);
        string url = host + path + querys;

        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());

        // 设置请求头
        struct curl_slist* headers = NULL;
        headers = curl_slist_append(headers, ("Authorization: APPCODE " + appcode).c_str());
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);

        // 设置回调函数，用于读取返回的数据
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);

        // 发送请求
        res = curl_easy_perform(curl);
        if (res != CURLE_OK) {
            cerr << "curl_easy_perform() failed: " << curl_easy_strerror(res) << endl;
            return -1;
        }

        curl_easy_cleanup(curl);
        curl_slist_free_all(headers);
    } else {
        cerr << "CURL 初始化失败！" << endl;
        return -1;
    }

    // 解析 JSON 响应
    Json::Reader reader;
    Json::Value root;
    if (reader.parse(readBuffer, root)) {
        if (root["code"].asInt() == 200 && root["success"].asBool()) {
            return root["data"]["money"].asFloat(); // 提取兑换结果
        } else {
            cerr << "API 返回错误：" << root["msg"].asString() << endl;
        }
    } else {
        cerr << "JSON 解析失败" << endl;
    }
    return -1; // 返回 -1 表示失败
}