// Copyright 2021 GHA Test Team
#include <gtest/gtest.h>
#include "textgen.h"

TEST(markovTest, formationTextWithGivenPrefixCount) {
    int wordsInPrefix = 2;
    vector<string> words = { "Another", "One", "Bites", "the", "Dust" };

    auto gen = MarkovChains(wordsInPrefix, words);
    auto tab = gen.GetStatetab();

    for (auto element : tab) {
        EXPECT_EQ(element.first.size(), wordsInPrefix);
    }
}

TEST(markovTest, formationPairPrefixSuffix) {
    int wordsInPrefix = 2;
    vector<string> words = { "Another", "One", "Bites", "the", "Dust" };

    auto gen = MarkovChains(wordsInPrefix, words);
    auto tab = gen.GetStatetab();

    prefix prefix;
    prefix.push_back(words[0]);

    for (int i = 1; i < words.size() - 1; i++) {
        prefix.push_back(words[i]);

        EXPECT_EQ(tab[prefix].size(), 1);
        EXPECT_EQ(tab[prefix][0], words[i + 1]);

        prefix.pop_front();
    }
}

TEST(markovTest, checkOneSuffix) {
    int wordsInPrefix = 1;
    vector<string> words = { "Another", "One", "Bites", "the", "Dust" };

    auto gen = MarkovChains(wordsInPrefix, words);
    auto tab = gen.GetStatetab();

    prefix prefix;
    prefix.push_back(words[0]);

    EXPECT_EQ(tab[prefix].size(), 1);
    EXPECT_EQ(tab[prefix][0], words[1]);
}

TEST(markovTest, checkDifferentSuffixes) {
    int wordsInPrefix = 1;
    vector<string> words = { "Another", "Another", "Bites", "the", "Dust" };

    auto gen = MarkovChains(wordsInPrefix, words);
    auto tab = gen.GetStatetab();

    prefix prefix;
    prefix.push_back(words[0]);

    EXPECT_EQ(tab[prefix].size(), 2);
    EXPECT_EQ(tab[prefix][0], words[1]);
    EXPECT_EQ(tab[prefix][1], words[2]);

    prefix.pop_front();
    prefix.push_back(words[2]);

    EXPECT_EQ(tab[prefix].size(), 1);
    EXPECT_EQ(tab[prefix][0], words[3]);
}

TEST(markovTest, formationTextWithGivenTable) {
    vector<string> words = { "Another", "One", "Bites", "the", "Dust" };
    map<prefix, suffix> tab;

    prefix prefix;
    suffix suffix;
    prefix.push_back(words[0]);


    for (int i = 1; i < words.size() - 1; i++) {
        prefix.push_back(words[i]);
        suffix.push_back(words[i + 1]);

        tab.insert({ prefix, suffix });

        prefix.pop_front();
        suffix.pop_back();
    }

    auto gen = MarkovChains(tab);

    auto text = gen.GenerateText(5);
    EXPECT_EQ(text, "Another One Bites the Dust");

    text = gen.GenerateText(10);
    EXPECT_EQ(text, "Another One Bites the Dust");

    text = gen.GenerateText(3);
    EXPECT_EQ(text, "Another One Bites");
}
