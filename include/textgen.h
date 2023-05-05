// Copyright 2021 GHA Test Team
#pragma once
#include <vector>
#include <map>
#include <deque>
#include <string>
#include <iostream>
#include <random>
#include <fstream>
#include <sstream>

using std::vector;
using std::map;
using std::deque;
using std::string;
using std::cout;
using std::cerr;
using std::endl;
using std::random_device;
using std::mt19937;
using std::uniform_int_distribution;
using std::istringstream;
using std::ifstream;
using std::invalid_argument;

typedef deque<string> prefix;
typedef vector<string> suffix;

class MarkovChains {
 public:
    explicit MarkovChains(map<prefix, suffix> statetab);
    explicit MarkovChains(int prefixSize, vector<string> words);
    explicit MarkovChains(int prefixSIze, const string filePath);
    string GenerateText(int textLength);
    map<prefix, suffix> GetStatetab();
    void PrintStatetab(const map<prefix, suffix> table);

 private:
    int wordsInPrefix;
    map<prefix, suffix> statetab;
    void InitStatetab(const vector<string> words);
    vector<string> GetWords(const string filePath);
    bool IsCorrect(const map<prefix, suffix> table);
};
