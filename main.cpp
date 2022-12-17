#include <iostream>
#include <vector>
#include <string>
#include <set>
#include <cmath>
#include <fstream>
#include <iomanip>

int ScalarProduct(const std::vector<size_t> &v1, const std::vector<size_t> &v2) {
    int res = 0;
    for (size_t i = 0; i < v1.size(); ++i) {
        res += v1[i] * v2[i];
    }
    return res;
}

double Distance(const std::vector<size_t> &v) {
    int res = 0;
    for (size_t i = 0; i < v.size(); ++i) {
        res += v[i] * v[i];
    }
    return pow(res, 0.5);
}

void ScanFile(std::ifstream &file, std::vector<std::string>& output_text) {
    std::string word;

    while (file >> word) {
        output_text.emplace_back(word);
    }
}

void FillSet(std::set<std::string>& patt, std::vector<std::string>& text) {
    for (auto &word: text) {
        patt.insert(word);
    }
}

void CalculateEntries(std::set<std::string>& patt, std::vector<std::string>& text, std::vector<size_t>& v) {
    size_t j = 0;
    for (auto &word: patt) {
        for (size_t i = 0; i < text.size(); ++i) {
            if (text[i] == word) {
                ++v[j];
                break;
            }
        }
        ++j;
    }
}

double Cos(const std::vector<size_t> &v1, const std::vector<size_t> &v2) {
    return ScalarProduct(v1, v2) / (Distance(v1) * Distance(v2));
}

int main() {

    std::vector<std::string> text1, text2;
    std::set<std::string> patt;

    std::ifstream file1;
    std::ifstream file2;

    file1.open("/home/budddma/CLionProjects/untitled/text1.txt");
    file2.open("/home/budddma/CLionProjects/untitled/text2.txt");

    ScanFile(file1, text1);
    ScanFile(file2, text2);

    file1.close();
    file2.close();

    FillSet(patt, text1);
    FillSet(patt, text2);
    
    std::vector<size_t> v1(patt.size()), v2(patt.size());

    CalculateEntries(patt, text1, v1);
    CalculateEntries(patt, text2, v2);

    std::cout << std::fixed << std::setprecision(3) << 100 * Cos(v1, v2);

    return 0;
}