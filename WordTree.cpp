#include "WordTree.h"
#include <iostream>
#include <algorithm>
using namespace std;

WordTree::WordTree() : m_root(nullptr), m_numberWords(0) {}

WordNode* WordTree::insert(WordNode* node, const string& word, int lineNumber) {
    if (node == nullptr) {
        WordNode* newNode = new WordNode();
        newNode->m_key = word;
        newNode->m_count = 1;
        newNode->m_lineNumbers.push_back(lineNumber);
        newNode->m_left = nullptr;
        newNode->m_right = nullptr;
        newNode->m_parent = nullptr;
        return newNode;
    }

    if (word < node->m_key) {
        WordNode* leftChild = insert(node->m_left, word, lineNumber);
        node->m_left = leftChild;
        leftChild->m_parent = node;
    } else if (word > node->m_key) {
        WordNode* rightChild = insert(node->m_right, word, lineNumber);
        node->m_right = rightChild;
        rightChild->m_parent = node;
    } else {
        node->m_count++;
        if (find(node->m_lineNumbers.begin(), node->m_lineNumbers.end(), lineNumber) == node->m_lineNumbers.end()) {
            node->m_lineNumbers.push_back(lineNumber);
        }
    }
    return node;
}

void WordTree::insert(const string& word, int lineNumber) {
    m_root = insert(m_root, word, lineNumber);
    m_numberWords++;
}

void WordTree::printTreeInOrder() {
    printTreeInOrder(m_root);
}

void WordTree::printTreeInOrder(WordNode* node) {
    if (node == nullptr) return;
    printTreeInOrder(node->m_left);
    cout << node->m_key << " ";
    printTreeInOrder(node->m_right);
}

int WordTree::countUniqueWords(WordNode* node) {
    if (node == nullptr) return 0;
    return 1 + countUniqueWords(node->m_left) + countUniqueWords(node->m_right);
}

int WordTree::countUniqueWords() {
    return countUniqueWords(m_root);
}

int WordTree::countWords() {
    return m_numberWords;
}

string WordTree::firstWord() {
    WordNode* current = m_root;
    while (current && current->m_left) {
        current = current->m_left;
    }
    return current ? current->m_key : "";
}

string WordTree::lastWord() {
    WordNode* current = m_root;
    while (current && current->m_right) {
        current = current->m_right;
    }
    return current ? current->m_key : "";
}

vector<int> WordTree::wordLines(const string& word) {
    WordNode* current = m_root;
    while (current) {
        if (word == current->m_key) return current->m_lineNumbers;
        current = (word < current->m_key) ? current->m_left : current->m_right;
    }
    return {};
}

vector<string> WordTree::mostFrequent() {
    vector<string> mostFrequentWords;
    int maxFrequency = 0;
    findMostFrequent(m_root, mostFrequentWords, maxFrequency);
    return mostFrequentWords;
}

void WordTree::findMostFrequent(WordNode* node, vector<string>& mostFrequentWords, int& maxFrequency) {
    if (node == nullptr) return;
    findMostFrequent(node->m_left, mostFrequentWords, maxFrequency);
    if (node->m_count > maxFrequency) {
        mostFrequentWords.clear();
        mostFrequentWords.push_back(node->m_key);
        maxFrequency = node->m_count;
    } else if (node->m_count == maxFrequency) {
        mostFrequentWords.push_back(node->m_key);
    }
    findMostFrequent(node->m_right, mostFrequentWords, maxFrequency);
}
