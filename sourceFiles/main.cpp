#include <iostream>
#include "inverted_index.h"
#include "converter_JSON.h"
#include "search_server.h"

using namespace std;

std::vector<std::vector<std::pair<int, float>>> convert(const std::vector<std::vector<RelativeIndex>>& matrix) {
    std::vector<std::vector<std::pair<int, float>>> answers;

    for (const auto& outerVec : matrix) {
        std::vector<std::pair<int, float>> innerVector;

        for (const auto& relativeIndex : outerVec) {
            innerVector.emplace_back(static_cast<int>(relativeIndex.doc_id), relativeIndex.rank);
        }

        answers.push_back(innerVector);
    }

    return answers;
}

int main() {

    ConverterJSON converterJSON;
    InvertedIndex invertedIndex;

    string command;

    int i = 0;

while (i != 1000) {

        cout << "Добро пожаловать в программу по поиску релевантности." << endl;
        cout << "Есть следующие команды:" << endl;
        cout << "create a request (С) - Создать лист слов запросов для поисковой программы." << endl;
        cout << "start (S) - Запустить расчёт." << endl;
        cout << "exit (E) - выйти из программы." << endl;
        cout << "Введите команду: ";

        std::getline(std::cin, command);

        if (command == "start" || command == "S") {

            invertedIndex.UpdateDocumentBase(converterJSON.GetTextDocuments());

            SearchServer searchServer(invertedIndex);

            converterJSON.putAnswers(convert(searchServer.search(converterJSON.GetRequests())));

        }else if (command == "create a request" || command == "C") {

            converterJSON.createRequest();

        }else if (command == "exit" || command == "E") {

            break;

        } else {

            cout << "Вы ввели неизвестную команду!" << endl;

        }

        i++;

    }


}
