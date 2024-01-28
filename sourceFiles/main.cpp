#include <iostream>
#include "gtest/gtest.h"
#include "../headerFiles/inverted_index.h"
#include "../headerFiles/converter_JSON.h"
#include "../headerFiles/search_server.h"

using namespace std;

TEST(sample_test_case, sample_test)
{
EXPECT_EQ(1, 1);
}

void TestInvertedIndexFunctionality(
        const vector<string>& docs,
        const vector<string>& requests,
        const std::vector<vector<Entry>>& expected
) {
    std::vector<std::vector<Entry>> result;
    InvertedIndex idx;
    idx.UpdateDocumentBase(docs);
    for(auto& request : requests) {

        std::vector<Entry> word_count = idx.GetWordCount(request);

        result.push_back(word_count);

    }

    ASSERT_EQ(result, expected);
}

TEST(TestCaseInvertedIndex, TestBasic) {
    const vector<string> docs = {
            "london is the capital of great britain",
            "big ben is the nickname for the Great bell of the striking clock"
    };
    const vector<string> requests = {"london", "the"};
    const vector<vector<Entry>> expected = {
            {
                    {0, 1}
            }, {{
                     0, 1}, {1, 3}
            }};
    TestInvertedIndexFunctionality(docs, requests, expected);
}
TEST(TestCaseInvertedIndex, TestBasic2) {
    const vector<string> docs = {
            "milk milk milk milk water water water",
            "milk water water",
            "milk milk milk milk milk water water water water water",
            "americano cappuccino"
    };
    const vector<string> requests = {"milk", "water", "cappuccino"};
    const vector<vector<Entry>> expected = {
            {
                    {0, 4}, {1, 1}, {2, 5}
            }, {
                    {0, 3}, {1, 2}, {2, 5}
            }, {
                    {3, 1}
            }
    };
    TestInvertedIndexFunctionality(docs, requests, expected);
}

TEST(TestCaseInvertedIndex, TestInvertedIndexMissingWord) {
    const vector<string> docs = {
            "a b c d e f g h i j k l",
            "statement"
    };
    const vector<string> requests = {"m", "statement"};
    const vector<vector<Entry>> expected = {
            {
            }, {
                    {1, 1}
            }
    };
    TestInvertedIndexFunctionality(docs, requests, expected);
}

TEST(TestCaseSearchServer, TestSimple) {
    const vector<string> docs = {
            "milk milk milk milk water water water",
            "milk water water",
            "milk milk milk milk milk water water water water water",
            "americano cappuccino"
    };
    const vector<string> request = {"milk water", "sugar"};
    const std::vector<vector<RelativeIndex>> expected = {
            {
                    {2, 1},
                    {0, 0.7},
                    {1, 0.3}
            },
            {
            }
    };
    InvertedIndex idx;
    idx.UpdateDocumentBase(docs);
    SearchServer srv(idx);
    std::vector<vector<RelativeIndex>> result = srv.search(request);
    ASSERT_EQ(result, expected);
}

TEST(TestCaseSearchServer, TestTop5) {
    const vector<string> docs = {
            "london is the capital of great britain",
            "paris is the capital of france",
            "berlin is the capital of germany",
            "rome is the capital of italy",
            "madrid is the capital of spain",
            "lisboa is the capital of portugal",
            "bern is the capital of switzerland",
            "moscow is the capital of russia",
            "kiev is the capital of ukraine",
            "minsk is the capital of belarus",
            "astana is the capital of kazakhstan",
            "beijing is the capital of china",
            "tokyo is the capital of japan",
            "bangkok is the capital of thailand",
            "welcome to moscow the capital of russia the third rome",
            "amsterdam is the capital of netherlands",
            "helsinki is the capital of finland",
            "oslo is the capital of norway",
            "stockholm is the capital of sweden",
            "riga is the capital of latvia",
            "tallinn is the capital of estonia",
            "warsaw is the capital of poland",
    };
    const vector<string> request = {"moscow is the capital of russia"};
    const std::vector<vector<RelativeIndex>> expected = {
            {
                    {7, 0.2},
                    {14, 0.2}
            }
    };
    InvertedIndex idx;
    idx.UpdateDocumentBase(docs);
    SearchServer srv(idx);
    std::vector<vector<RelativeIndex>> result = srv.search(request);

    for (int i = 0; i < result.size(); ++i) {

        std::cout << request[0] << std::endl;

        for (int j = 0; j < result[i].size(); ++j) {

            std::cout << result[i][j].doc_id << " " << result[i][j].rank << std::endl;

        }

    }

    ASSERT_EQ(result, expected);
}

//---------------------------------------------------------------------------------------------------------------

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
        cout << "start (S) - Получить результат." << endl;
        cout << "update (U) - Принудительно обновить базу данных." << endl;
        cout << "exit (E) - выйти из программы." << endl;
        cout << "Введите команду: ";

        std::getline(std::cin, command);

        if (command == "start" || command == "S") {

            invertedIndex.UpdateDocumentBase(converterJSON.GetTextDocuments());

            SearchServer searchServer(invertedIndex);

            converterJSON.putAnswers(convert(searchServer.search(converterJSON.GetRequests())));

        } else if (command == "update" || command == "U") {

            invertedIndex.UpdateDocumentBase(converterJSON.GetTextDocuments());

        } else if (command == "create a request" || command == "C") {

            converterJSON.createRequest();

        } else if (command == "exit" || command == "E") {

            break;

        } else {

            cout << "Вы ввели неизвестную команду!" << endl;

        }

        i++;

    }

}
