#define NOMINMAX // ��ֹ Windows.h �궨�� max �� min ���³�ͻ
#include <iostream>
#include <string>
#include <curl/curl.h>
#include <json/json.h>

using namespace std;

// ������Ҫ���õĺ���
void clearScreen();
void currencies();
void displayHeader();
void calculate(const string& fromCode, const string& toCode);
float fetch_exchange_rate(const string& fromCode, const string& toCode, float money);

// API ������Ϣ
const string appcode = "19015e4d20284658a3b7a4feac8e1a07";
const string host = "https://tysjhlcx.market.alicloudapi.com";
const string path = "/exchange_rate/convert";

// CURL �ص�����
size_t WriteCallback(void* contents, size_t size, size_t nmemb, string* userp) {
    userp->append((char*)contents, size * nmemb);
    return size * nmemb;
}

int main() {
    char sev_type;
    while (1) {
        displayHeader(); // ��ʾϵͳ����
        cout << endl;
        cout << "һ����ѡ��һ���ʽ:" << endl;
        cout << "    1.��Ҷһ������(1)" << endl;
        cout << "    2.����Ҷһ����(2)" << endl;
        cout << "    3.�˳�ϵͳ(0)" << endl;
        cin >> sev_type;
        clearScreen(); // ���֮ǰ�����

        if (sev_type != '1' && sev_type != '2' && sev_type != '0') {
            cout << "��Чѡ������������..." << endl;
            cin.clear();
            cin.sync();
            _sleep(800); // �ȴ� 1 ��
            displayHeader(); // ��ʾϵͳ����
            continue; // ��Чѡ��ʱ��������������������
        }

        displayHeader(); // ��ʾϵͳ���⣨������Чѡ��ʱ���ã�
        
        if (sev_type == '1') {
            cout << "����ѡ���ǣ���Ҷһ������" << endl;
            currencies();
        } else if (sev_type == '2') {
            cout << "����ѡ���ǣ�����Ҷһ����" << endl;
            currencies();
        } else if (sev_type == '0') {
            cout << "��л����ʹ��" << endl;
            _sleep(1000); // �ȴ� 1 ��
            return 0; // �˳�����
        }
    }
}

// ��ʾϵͳ����ĺ���
void displayHeader() {
    cout << "--------------------------------" << endl;
    cout << "|*********��Ҷһ�ϵͳ*********|" << endl;
    cout << "--------------------------------" << endl;
}

void clearScreen() {
    cout << "\033[2J\033[1;1H"; // ʹ�� ANSI Escape Code ����
}

void currencies() {
    int kind;
    string fromCode, toCode = "CNY"; // Ĭ��Ŀ�����Ϊ�����
    while (1) {
        cout << endl;
        cout << "������ѡ��һ����֣�" << endl;
        cout << "    1.Ӣ��(GBP)" << endl;
        cout << "    2.ŷԪ(EUR)" << endl;
        cout << "    3.��Ԫ(USD)" << endl;
        cout << "    4.�۱�(HKD)" << endl;
        cout << "    5.��Ԫ(AUD)" << endl;
        cout << "    6.��Ԫ(JPY)" << endl;
        cout << "    7.��Ԫ(KRW)" << endl;
        cout << "    8.̩��(THB)" << endl;
        cout << "    9.¬��(RUB)" << endl;
        cout << "    10.����" << endl;
        cin >> kind;
        clearScreen(); // ���֮ǰ�����

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
            case 10:
                return; // ֱ�ӷ��غ������ص���ѭ��
            default:
                cout << "��Чѡ������������..." << endl;
                cin.clear();
                cin.sync();
                _sleep(800); // �ȴ� 1 ��
                clearScreen(); // ���֮ǰ�����
                displayHeader(); // ��ʾϵͳ����
                continue;
        }
        displayHeader(); // ��ʾϵͳ����
        cout << "����ѡ���ǣ�" << fromCode << endl;
        calculate(fromCode, toCode);
        break;
    }
}

void calculate(const string& fromCode, const string& toCode) {
    float num;
    while (1) {
        cout << endl;
        cout << "����������һ���";
        cin >> num;
        if (num <= 0 || cin.fail()) {
            cout << "��Ч���룬������һ��������" << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        } else {
            break;
        }
    }

    // ���� API ��ȡ����
    float exchange = fetch_exchange_rate(fromCode, toCode, num);
    if (exchange != -1) {
        cout << "�һ������" << num << " " << fromCode << " = " << exchange << " " << toCode << endl;
        cout << "��л����ʹ�ã��ټ���" << endl; // ���������ʾ
        cout << endl;
        cout << "3��󽫻ص���ҳ��" << endl;
        _sleep(3000); // �ȴ� 3 ��
        clearScreen(); // ���֮ǰ�����
    } else {
        cout << "��ȡ����ʧ�ܣ����Ժ����ԣ�" << endl;
    }
}

float fetch_exchange_rate(const string& fromCode, const string& toCode, float money) {
    CURL* curl;
    CURLcode res;
    string readBuffer;

    curl = curl_easy_init();
    if (curl) {
        // �������� URL
        string querys = "?fromCode=" + fromCode + "&toCode=" + toCode + "&money=" + to_string(money);
        string url = host + path + querys;

        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());

        // ��������ͷ
        struct curl_slist* headers = NULL;
        headers = curl_slist_append(headers, ("Authorization: APPCODE " + appcode).c_str());
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);

        // ���ûص����������ڶ�ȡ���ص�����
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);

        // ��������
        res = curl_easy_perform(curl);
        if (res != CURLE_OK) {
            displayHeader();
            cerr << "curl_easy_perform() failed: " << curl_easy_strerror(res) << endl;
            return -1;
        }

        curl_easy_cleanup(curl);
        curl_slist_free_all(headers);
    } else {
        cerr << "CURL ��ʼ��ʧ�ܣ�" << endl;
        return -1;
    }

    // ���� JSON ��Ӧ
    Json::Reader reader;
    Json::Value root;
    if (reader.parse(readBuffer, root)) {
        if (root["code"].asInt() == 200 && root["success"].asBool()) {
            return root["data"]["money"].asFloat(); // ��ȡ�һ����
        } else {
            cerr << "API ���ش���" << root["msg"].asString() << endl;
        }
    } else {
        cerr << "JSON ����ʧ��" << endl;
    }
    return -1; // ���� -1 ��ʾʧ��
}