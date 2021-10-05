#include <cstdlib>
#include <iostream>
#include <string>
#include <locale>
#include <fstream>
#include <conio.h>
#include <vector>
#include <iomanip>
#include <algorithm>

using namespace std;

const string alphabet_eng = "abcdefghijklmnopqrstuvwxyz";
const size_t n_eng = alphabet_eng.size();
vector<string> read_file(string file_name)
{
    vector<string> text;
    string temp;
    ifstream ist(file_name, ios::in | ios::binary);
    if (!ist) {
        cout << "cant open the file with this name! return to menu..." << endl;
    }
    else {
        while (!ist.eof()) {
            getline(ist, temp);
            text.push_back(temp);
        }
        cout << "file has been successfully read" << endl;
    }
    ist.close();
    return text;
}

void write_file(string file_name, vector<string> text)
{
    string temp;
    ofstream ost(file_name, ios::in | ios::binary);
    if (!ost) {
        cout << "cant open the file with this name" << endl;
    }
    else {
        for (size_t i = 0; i < text.size(); i++) {
            ost << text[i] << endl;
        }
        cout << "file has been successfully writed" << endl;
    }
    ost.close(); //Закрываем файл
}

void print_text(vector<string> text)
{
    for (size_t i = 0; i < text.size(); i++) {
        cout << text[i] << endl;
    }
}

vector<string> encrypt(vector<string> word, size_t k)
{
    k %= n_eng;
    string wrd;
    for (size_t i = 0; i < word.size(); ++i) {
        wrd = word[i];
        for (size_t j = 0; j < wrd.length(); ++j) {
            if (isprint((unsigned char)wrd[j])) {
                wrd[j] = alphabet_eng[(alphabet_eng.find(wrd[j]) + k) % n_eng];
            }
        }
        word[i] = wrd;
    }
    return word;
}

vector<string> decrypt(vector<string> text, size_t k)
{
    k %= n_eng;
    string txt;
    for (size_t i = 0; i < text.size(); ++i) {
        txt = text[i];
        for (size_t j = 0; j < txt.length(); ++j) {
            if (isprint((unsigned char)txt[j])) {
                txt[j] = alphabet_eng[(alphabet_eng.find(txt[j]) - k + n_eng) % n_eng];
            }
        }
        text[i] = txt;
    }
    return text;
}

vector<double> frequency_analysis(vector<string> text)
{
    vector<double> counters(26);
    int count = 0;
    string txt;
    for (size_t i = 0; i < text.size(); i++) {
        txt = text[i];
        for (size_t j = 0; j < txt.length(); ++j) {
            for (size_t m = 0; m < 26; ++m) {
                if (txt[j] == alphabet_eng[m]) {
                    counters[m]++;
                }
            }
            count++;
        }

    }
    cout << "frequency analyse complete" << endl;
    ofstream ost("frequency.txt");
    locale mylocale("");
    ost.imbue(mylocale);
    if (!ost) {
        cout << "cant open the file with this name" << endl;
    }
    else {
        for (size_t i = 0; i < counters.size(); i++) {
            counters[i] = counters[i] / count * 100;
            ost << setprecision(2) << fixed << counters[i] << endl;
        }
        cout << "file has been successfully writed" << endl;
    }
    ost.close();
    return counters;
}
void showmenu()
{
    cout << "Menu : " << endl;
    cout << "1 - Open file\n";
    cout << "2 - Write text from file\n";
    cout << "3 - Crypt file\n";
    cout << "4 - Decrypt file\n";
    cout << "5 - Frequency analysis\n";
    cout << "0 - Exit\n";
    cout << endl;
}

int main()
{
    setlocale(LC_ALL, "");
    size_t k = 0;
    vector<string> text;  //текст считанный из файла
    bool prisn;
    prisn = true;
    do
    {
        system("cls");
        showmenu();
        switch (_getch())
        {
        case '1':   //open file to string
        {
            cout << "write a file name" << endl;
            string file_name;
            cin >> file_name;
            text = read_file(file_name);
            break;
        };
        case '2':   //crypted string
        {
            if (text.size() == 0) { cout << "text is empty! return to menu..." << endl; }
            else {
                print_text(text);
            }
            break;
        };
        case '3':   //crypted string
        {
            if (text.size() == 0) { cout << "text is empty! return to menu..." << endl; }
            else {
                cout << "write key:" << endl;
                cin >> k;
                string file_name = "crypt.txt";
                write_file(file_name, encrypt(text, k));
                cout << "text crypted" << endl;
            }
            break;
        };
        case '4':   //decrypted string
        {
            if (text.size() == 0) { cout << "text is empty! return to menu..." << endl; }
            else {
                cout << "write key:" << endl;
                cin >> k;
                string file_name = "decrypt.txt";
                write_file(file_name, decrypt(text, k));
                cout << "text decrypted" << endl;
            }
            break;
        };
        case '5':   //frequency analysis
        {
            if (text.size() == 0) {cout << "text is empty! return to menu..." << endl; }
            else {
                frequency_analysis(text);
            }
            break;
        };
        case '0':   //exit
        {
            prisn = false;
            exit(0);
        }
        default:
        {
          cout << "Wrong input!" <<endl;
            break;
        }
        }
       cout << endl << endl;
        system("pause");
    } while (prisn);
    return 0;
}
