#include <iostream>
#include <fstream>
#include <string>
#include <map>

using namespace std;

bool is_aspek(char ch) {
    return (ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z');
}

char toflop(char ch) {
    if (ch >= 'A' && ch <= 'Z') {
        return ch + ('a' - 'A');
    }
    return ch;
}

string toflop(const string& str) {
    string result;
    for (char ch : str) {
        result += toflop(ch);
    }
    return result;
}

void poprc(const string& line, map<string, int>& wordfail) {
    string word;
    for (char ch : line) {
        if (is_aspek(ch)) {
            word += ch;
        }
        else if (!word.empty()) {
            word = toflop(word);
            wordfail[word]++;
            word.clear();
        }
    }
    if (!word.empty()) {
        word = toflop(word);
        wordfail[word]++;
    }
}

void persontext(const string& inputform, const string& outpufail) {
    ifstream infail(inputform);
    ofstream outfail(outpufail);

    if (!infail) {
        cerr << "Помилка відкриття вхідного файлу!" << endl;
        return;
    }

    if (!outfail) {
        cerr << "Помилка відкриття вихідного файлу!" << endl;
        return;
    }

    map<string, int> wordfail;
    string line;

    while (getline(infail, line)) {
        poprc(line, wordfail);
    }

    outfail << "Частотний словник:" << endl;

    for (map<string, int>::const_iterator it = wordfail.begin(); it != wordfail.end(); ++it) {
        outfail << it->first << ": " << it->second << endl;
    }


    map<string, int>::iterator mostfind = wordfail.begin();
    for (map<string, int>::iterator it = wordfail.begin(); it != wordfail.end(); ++it) {
        if (it->second > mostfind->second) {
            mostfind = it;
        }
    }

    if (mostfind != wordfail.end()) {
        outfail << "\nНайбільш часте слово: \"" << mostfind->first
            << "\" зустрічається " << mostfind->second << " раз(ів)." << endl;
    }

    infail.close();
    outfail.close();
}

int main() {
    string inputform = "input.txt";
    string outpufail = "output.txt";

    persontext(inputform, outpufail);

    cout << "Обробка завершена. Результат збережено у файлі \"" << outpufail << "\"." << endl;

    return 0;
