#include "converter_JSON.h"

std::vector<std::string> ConverterJSON::GetTextDocuments() {

    std::vector<std::string> pathToFile;
    std::vector<std::string> readingFile;

    std::ifstream file("json/config.json");

    if (!file.is_open()) {

        std::cout << "Configuration file not found, please create it." << std::endl;

        std::system("pause");

        std::exit(0);

    }
    else {

        nlohmann::json dict;
        file >> dict;
        pathToFile = dict["files"];
        file.close();

        std::string textDocuments;

        for (int i = 0; i < pathToFile.size(); ++i) {

            std::ifstream fileJson(pathToFile[i]);

            if (!fileJson.is_open()) {

                std::cout << pathToFile[i] << " The file did not open." << std::endl;

            } else {

                while (!fileJson.eof()) {

                    std::getline(fileJson, textDocuments);

                }

                readingFile.push_back(textDocuments);

            }

            fileJson.close();

        }

        return readingFile;

    }

}

int ConverterJSON::GetResponsesLimit() {

    nlohmann::json dict;

    std::ifstream file("json/config.json");

    file >> dict;

    file.close();

    return dict["config"]["max_responses"];

}

std::vector<std::string> ConverterJSON::GetRequests() {

    nlohmann::json dict;

    std::ifstream file("json/requests.json");

    if (!file.is_open()) {

        std::cout << "The request file was not found, please create it." << std::endl;

        std::system("pause");

        std::exit(0);

    }
    else {

        file >> dict;

        file.close();

        return dict["requests"];

    }

}

void ConverterJSON::putAnswers(std::vector<std::vector<std::pair<int, float>>> answers) {

    nlohmann::json dict;

    std::vector<std::string> qwe {"json/answers.json", "answer/answers.txt"};

    for (int i = 0; i < qwe.size(); ++i) {


        std::fstream fileAnswers(qwe[i], std::ios::out);

        std::vector<std::string> searchWord = GetRequests();

        dict["answers"];

        for (int i = 0; i < answers.size(); ++i) {

            std::string request = "request_" + std::to_string(i + 1);

            if (answers[i].size() != 0) {

                dict["answers"][request]["result"] = true;
                dict["answers"][request]["relevance"];

                for (int j = 0; j < answers[i].size() && j < GetResponsesLimit(); ++j) {

                    dict["answers"][request]["relevance"][j]["search word"] = searchWord[i];
                    dict["answers"][request]["relevance"][j]["docid"] = std::to_string(answers[i][j].first);
                    dict["answers"][request]["relevance"][j]["rank"] = std::to_string(answers[i][j].second);

                }

            } else {

                dict["answers"][request]["search word"] = searchWord[i];
                dict["answers"][request]["result"] = false;

            }

        }

        fileAnswers << std::setw(4) << dict;

        fileAnswers.close();
    }

}

void ConverterJSON::createRequest(){

    std::vector<std::string> words;

    int count = 0;
    std::string word;

    std::cout << "Введите количество запроссов: ";

    std::cin >> count;

    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    for (int i = 0; i < count; ++i) {

        std::cout << "Введите слова(слово) которое ищите: ";

        std::getline(std::cin, word);

        words.push_back(word);

    }

    nlohmann::json dict;

    std::fstream file("json/requests.json", std::ios::out);

    for (int i = 0; i < words.size(); ++i) {

        dict["requests"].push_back(words[i]);

    }

    file << std::setw(4) << dict;

    file.close();

}