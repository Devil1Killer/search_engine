#include "inverted_index.h"

std::mutex mtx;

void index(std::vector<std::string> input_docs, size_t i, std::map<std::string, std::vector<Entry>>& freq_dictionary, std::vector<int>& wordCount) {

    std::string word;
    int beginningWord = 0;

    for (int j = 0; j <= input_docs[i].size(); ++j) {

        if (input_docs[i][j] == ' ' || input_docs[i][j] == '\0') {

            mtx.lock();

            word = input_docs[i].substr(beginningWord, j - beginningWord);
            beginningWord = j + 1;

            wordCount[i]++;

            auto it = freq_dictionary.find(word);

            if (it!=freq_dictionary.end()) {

                bool key = true;
                std::vector<Entry> &entries = it->second;

                for (auto& qqq : entries) {

                    if (qqq.doc_id == i) {

                        qqq.count++;
                        key = false;

                    }

                }

                if (key) {

                    Entry entry{i, 1};
                    freq_dictionary[word].push_back(entry);

                }

            }
            else {

                Entry entry{ i, 1 };
                freq_dictionary[word].push_back(entry);

            }

            mtx.unlock();

        }

    }

}

void InvertedIndex::UpdateDocumentBase(std::vector<std::string> input_docs) {

    freq_dictionary.clear();

    std::ifstream checkFile("resources/frequency dictionary file.txt");

    if (!checkFile.is_open()) std::cout << " File with frequency words was not found." << std::endl;
    else {

        std::string size;

        checkFile >> size;

        if (size == std::to_string(input_docs.size())) {

            int i = 0;

            while (!checkFile.eof()) {

                checkFile >> size;

                if (size == "Start") {

                    std::string name;

                    while (!checkFile.eof()) {

                        name = "";

                        checkFile >> name;
                        checkFile >> size;

                        for (int j = 0; j < atoi(size.c_str()); ++j) {

                            size_t id;
                            size_t count;

                            checkFile >> id;
                            checkFile >> count;

                            Entry entry{id, count};
                            freq_dictionary[name].push_back(entry);

                        }

                    }

                    checkFile.close();

                    return;

                } else if (atoi(size.c_str()) == input_docs[i].size()) {

                    i++;

                    std::string wordCountSize;

                    checkFile >> wordCountSize;

                    wordCount.push_back(atoi(wordCountSize.c_str()));

                } else break;

            }

        }

    }

    checkFile.close();

    std::vector<std::thread> indexing;

    for (size_t i = 0; i < input_docs.size(); ++i) {

        wordCount.push_back(0);

    }

    for (size_t i = 0; i < input_docs.size(); ++i) {

        indexing.push_back(std::thread(index, input_docs, i, std::ref(freq_dictionary), std::ref(wordCount)));

    }

    for (size_t i = 0; i < input_docs.size(); ++i) {

        indexing[i].join();

    }

    std::fstream fillingFile("resources/frequency dictionary file.txt", std::ios::out);

    fillingFile << input_docs.size() << std::endl;

    for (int i = 0; i < input_docs.size(); ++i) {

        fillingFile << input_docs[i].size() << std::endl;
        fillingFile << wordCount[i] << std::endl;

    }

    fillingFile << "Start" << std::endl;

    for (auto &pair: freq_dictionary) {

        const std::string &key = pair.first;
        std::vector<Entry> &entries = pair.second;

        fillingFile << key << std::endl;
        fillingFile << freq_dictionary[key].size() << std::endl;

        for (auto &element: entries) {

            fillingFile << element.doc_id << std::endl;
            fillingFile << element.count << std::endl;

        }

    }

    fillingFile.close();

}

std::vector<Entry> InvertedIndex::GetWordCount(const std::string &word) {

    std::vector<Entry> entrys;

    for (auto &pair: freq_dictionary) {

        const std::string &key = pair.first;
        std::vector <Entry> &entries = pair.second;

        for (auto &element: entries) {

            if (key == word) {

                entrys.push_back(element);

            }

        }

    }

    return entrys;

}