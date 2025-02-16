#ifndef WORDTREE_H
#define WORDTREE_H

#include <string>
#include <vector>
#include "WordNode.h"

using namespace std;

class WordTree
{
    public:
        WordTree();
        void insert(const string& word, int lineNumber);
        void printTreeInOrder();
        int countUniqueWords();
        int countWords();
        string lastWord();
        string firstWord();
        vector<int> wordLines(const string& word);
        vector<string> mostFrequent();

    protected:
        WordNode* insert(WordNode* node, const string& word, int lineNumber);
        void printTreeInOrder(WordNode* node);
        int countUniqueWords(WordNode* node);
        void countWords(WordNode* node);
        string lastWord(WordNode* node);
        string firstWord(WordNode* node);
        vector<int> wordLines(WordNode* node, const string& word);
        void findMostFrequent(WordNode* node, vector<string>& mostFrequentWords, int& maxFrequency);

    private:
        WordNode* m_root;
        int m_numberWords;
};

#endif
