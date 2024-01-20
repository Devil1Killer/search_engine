#include "../headerFiles/converter_JSON.h"

std::vector<std::string> ConverterJSON::GetTextDocuments() {

    std::vector<std::string> pathToFile;
    std::vector<std::string> readingFile;

    std::ifstream file("../json/config.json");
    nlohmann::json dict;
    file >> dict;
    pathToFile = dict["files"];
    file.close();

    std::string textDocuments;

    for (int i = 0; i < pathToFile.size(); ++i) {

        std::ifstream fileJson(pathToFile[i]);

        if (!fileJson.is_open()) {

            std::cout << pathToFile[i] << " The file did not open." << std::endl;

        }
        else {

            while (!fileJson.eof()) {

                std::getline(fileJson, textDocuments);

            }

            readingFile.push_back(textDocuments);

        }

        fileJson.close();

    }

    return readingFile;

}

int ConverterJSON::GetResponsesLimit() {

    nlohmann::json dict;

    std::ifstream file("../json/config.json");

    file >> dict;

    file.close();

    return dict["config"]["max_responses"];

}

std::vector<std::string> ConverterJSON::GetRequests() {

    nlohmann::json dict;

    std::ifstream file("../json/requests.json");

    file >> dict;

    file.close();

    return dict["requests"];

}

void ConverterJSON::putAnswers(std::vector<std::vector<std::pair<int, float>>> answers) {

    nlohmann::json dict;

    std::fstream fileAnswers("../json/answers.json",  std::ios::out);

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

            dict["answers"][request]["result"] = false;

        }

    }

    fileAnswers << std::setw(4) << dict;

    fileAnswers.close();

/* // Для разработчика получить результат

    int i = 0;

    std::vector<std::string> searchWord = GetRequests();

    for (const auto& innerVec : answers) {

        std::cout << searchWord[i] << " ";

        for (const auto& pair : innerVec) {

            std::cout << "(" << pair.first << ", " << pair.second << ") ";

        }

        std::cout << std::endl;
        i++;

    }

*/

}

