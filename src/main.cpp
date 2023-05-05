// Copyright 2021 GHA Test Team
#include "textgen.h"

int main() {
    setlocale(LC_ALL, "Russian");
    MarkovChains mch = MarkovChains(2, "input.txt");
    cout << mch.GenerateText(200) << endl;;
}
