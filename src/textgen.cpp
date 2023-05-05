// Copyright 2021 GHA Test Team
#include "textgen.h"

MarkovChains::MarkovChains(map<prefix, suffix> statetab) {
    if (IsCorrect(statetab)) {
        wordsInPrefix = statetab.begin()->first.size();
        this->statetab = statetab;
    } else {
        throw invalid_argument("Incorrect table");
    }
}

MarkovChains::MarkovChains(int prefixSize, vector<string> words) {
    this->wordsInPrefix = prefixSize;
    InitStatetab(words);
}

MarkovChains::MarkovChains(int prefixSize, string filePath) {
    this->wordsInPrefix = prefixSize;
    InitStatetab(GetWords(filePath));
}

string MarkovChains::GenerateText(int maxWords) {
    if (maxWords < 0)
        throw invalid_argument("Text length should be >= 0");

    if (maxWords < wordsInPrefix)
        throw invalid_argument("Text length should be >= prefix length");

    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dist(0, statetab.size() - 1);

    prefix currentPrefix = statetab.begin()->first;

    string text;
    for (int i = 0; i < currentPrefix.size(); i++)
        text += currentPrefix[i] + " ";

    for (int i = 0; i < maxWords - wordsInPrefix; i++) {
        suffix currentSuffix;

        auto it = statetab.find(currentPrefix);
        if (it != statetab.end())
            currentSuffix = it->second;

        if (currentSuffix.size() == 0)
            break;

        int index = dist(gen) % currentSuffix.size();
        text += currentSuffix[index] + " ";

        currentPrefix.pop_front();
        currentPrefix.push_back(currentSuffix[index]);
    }

    if (!text.empty())
        text.erase(text.size() - 1);

    return text;
}

map<prefix, suffix> MarkovChains::GetStatetab() {
    return statetab;
}

void MarkovChains::PrintStatetab(const map<prefix, suffix> statetab) {
    for (auto& pair : statetab) {
        for (auto& prefix : pair.first) {
            cout << "Prefix: " << prefix << endl;
        }
        for (auto& suffix : pair.second) {
            cout << "Suffix: " << suffix << endl;
        }
    }
}

void MarkovChains::InitStatetab(const vector<string> words) {
    prefix currentPrefix;

    for (string word : words) {
        if (currentPrefix.size() == wordsInPrefix) {
            statetab[currentPrefix].push_back(word);
            currentPrefix.pop_front();
        }
        currentPrefix.push_back(word);
    }
}

vector<string> MarkovChains::GetWords(const string filePath) {
    ifstream file(filePath);
    if (!file.is_open()) {
        cerr << "Error : Cannot open file " << filePath << endl;
        exit(EXIT_FAILURE);
    }

    vector<string> words;
    string line;

    while (getline(file, line)) {
        istringstream iss(line);
        string word;

        while (iss >> word)
            words.push_back(word);
    }
    file.close();
    return words;
}

bool MarkovChains::IsCorrect(const map<prefix, suffix> statetab) {
    if (statetab.empty())
        return true;

    int wordsInPrefix = statetab.begin()->first.size();
    for (auto element : statetab) {
        if (element.first.size() != wordsInPrefix)
            return false;
    }
    return true;
}
