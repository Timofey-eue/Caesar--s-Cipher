#include <cstdlib>
#include <iostream>
#include <string>
#include <locale>
#include <fstream>
#include <conio.h>
#include <vector>
#include <iomanip>
#include <algorithm>
const std::string alphabet_eng = "abcdefghijklmnopqrstuvwxyz";
const size_t n_eng = alphabet_eng.size();
std::vector<std::string> read_file(std::string file_name)
{
    std::vector<std::string> text;
    std::string temp;
    std::ifstream ist(file_name, std::ios::in | std::ios::binary);
    if (!ist) {
        std::cout << "cant open the file with this name! return to menu..." << std::endl;
    }
    else {
        while (!ist.eof()) {
            std::getline(ist, temp);
            text.push_back(temp);
        }
        std::cout << "file has been successfully read" << std::endl;
    }
    ist.close(); //Закрываем файл
    return text;
}

void write_file(std::string file_name, std::vector<std::string> text)
{
    std::string temp;
    std::ofstream ost(file_name, std::ios::in | std::ios::binary);
    if (!ost) {
        std::cout << "cant open the file with this name" << std::endl;
    }
    else {
        for (size_t i = 0; i < text.size(); i++) {
            ost << text[i] << std::endl;
        }
        std::cout << "file has been successfully writed" << std::endl;
    }
    ost.close(); //Закрываем файл
}

void print_text(std::vector<std::string> text)
{
    for (size_t i = 0; i < text.size(); i++) {
        std::cout << text[i] << std::endl;
    }
}

std::vector<std::string> encrypt(std::vector<std::string> text, size_t k)
{
    k %= n_eng;
    std::string txt;
    for (size_t i = 0; i < text.size(); ++i) {
        txt = text[i];
        for (size_t j = 0; j < txt.length(); ++j) {
            if (isprint((unsigned char)txt[j])) {
                txt[j] = alphabet_eng[(alphabet_eng.find(txt[j]) + k) % n_eng];
            }
        }
        text[i] = txt;
    }
    return text;
}

std::vector<std::string> decrypt(std::vector<std::string> text, size_t k)
{
    k %= n_eng;
    std::string txt;
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

std::vector<double> frequency_analysis(std::vector<std::string> text)
{
    std::vector<double> counters(26);
    int count = 0;
    std::string txt;
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
    std::cout << "frequency analyse complete" << std::endl;
    std::ofstream ost("graph.txt");
    std::locale mylocale("");
    ost.imbue(mylocale);
    if (!ost) {
        std::cout << "cant open the file with this name" << std::endl;
    }
    else {
        for (size_t i = 0; i < counters.size(); i++) {
            counters[i] = counters[i] / count * 100;
            ost << std::setprecision(2) << std::fixed << counters[i] << std::endl;
        }
        std::cout << "file has been successfully writed" << std::endl;
    }
    ost.close();
    return counters;
}
void showmenu()
{
    std::cout << "Menu : " << std::endl;
    std::cout << "1 - Open file\n";
    std::cout << "2 - Write text from file\n";
    std::cout << "3 - Crypt file\n";
    std::cout << "4 - Decrypt file\n";
    std::cout << "5 - Frequency analysis\n";
    std::cout << "0 - Exit\n";
    std::cout << std::endl;
}

int main()
{
    setlocale(LC_ALL, "");
    size_t k = 0;
    std::vector<std::string> text;  //текст считанный из файла
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
            std::cout << "write a file name" << std::endl;
            std::string file_name;
            std::cin >> file_name;
            text = read_file(file_name);
            break;
        };
        case '2':   //crypted string
        {
            if (text.size() == 0) { std::cout << "text is empty! return to menu..." << std::endl; }
            else {
                print_text(text);
            }
            break;
        };
        case '3':   //crypted string
        {
            if (text.size() == 0) { std::cout << "text is empty! return to menu..." << std::endl; }
            else {
                std::cout << "write key:" << std::endl;
                std::cin >> k;
                std::string file_name = "crypt.txt";
                write_file(file_name, encrypt(text, k));
                std::cout << "text crypted" << std::endl;
            }
            break;
        };
        case '4':   //decrypted string
        {
            if (text.size() == 0) { std::cout << "text is empty! return to menu..." << std::endl; }
            else {
                std::cout << "write key:" << std::endl;
                std::cin >> k;
                std::string file_name = "decrypt.txt";
                write_file(file_name, decrypt(text, k));
                std::cout << "text decrypted" << std::endl;
            }
            break;
        };
        case '5':   //frequency analysis
        {
            if (text.size() == 0) { std::cout << "text is empty! return to menu..." << std::endl; }
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
            std::cout << "Wrong input!" << std::endl;
            break;
        }
        }
        std::cout << std::endl << std::endl;
        system("pause");
    } while (prisn);
    return 0;
}