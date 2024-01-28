#include "../headerFiles/search_server.h"

std::vector<std::vector<RelativeIndex>> SearchServer::search(const std::vector<std::string>& queries_input) {

    std::vector<std::vector<RelativeIndex>> result;

    std::vector <Entry> list;
    std::vector <Entry> newList;

/* // Для разработчика получить результат


    for (int i = 0; i < queries_input.size(); ++i) {

        std::cout << queries_input[i] << std::endl;

    }
    std::cout << std::endl << std::endl;

*/


    std::vector <int> numberSearchWords;

    for (int i = 0; i < queries_input.size(); ++i) {

        int count = 1;

        for (int j = 0; j < queries_input[i].size(); ++j) {

            if (queries_input[i][j] == ' ') {

                count++;

            }

        }

        numberSearchWords.push_back(count);

    }

    //---------------------------------------------------------------

    std::vector<std::string> separateWords;

    int start = 0;

    for (int i = 0; i < queries_input.size(); ++i) {

        for (int j = 0; j < queries_input[i].size(); ++j) {

            if (queries_input[i][j] == ' ') {

                separateWords.push_back(queries_input[i].substr(start, j - start));

                start = j + 1;

            }

        }

        if (start != 0) {

            separateWords.push_back(queries_input[i].substr(start, queries_input[i].size() - start));

        }
        else {

            separateWords.push_back(queries_input[i]);

        }

        start = 0;

    }


    // Для разработчика получить результат

/*    for (int i = 0, q = 0; i < numberSearchWords.size(); ++i) {

        for (int j = 0; j < numberSearchWords[i]; ++j) {

            std::cout << numberSearchWords[i] << " " << separateWords[j + q] << std::endl;
        }

        q += numberSearchWords[i];

    }*/


    for (int i = 0, q = 0; i < numberSearchWords.size(); ++i) {

        std::vector<RelativeIndex> interval;

        std::vector<Entry> list;

        for (int j = 0; j < numberSearchWords[i]; ++j) {

            std::vector<Entry> newList = _index.GetWordCount(separateWords[q + j]);

            if (j == 0) list = newList;
            else {

                for (int k = 0; k < list.size() && k < newList.size(); ++k) {

                    for (auto& qqq : list) {

                        if (qqq.doc_id == newList[k].doc_id) qqq.count += newList[k].count;

                    }

                }

            }

        }

        q += numberSearchWords[i];

        for (int j = 0; j < list.size(); ++j) {

            RelativeIndex rank {list[j].doc_id,list[j].count / 10.0f};

            interval.push_back(rank);

        }

        std::sort(interval.begin(),interval.end(), [](const RelativeIndex& p1, const RelativeIndex& p2){

            return p1.rank > p2.rank;

        });

        result.push_back(interval);

    }

    // Для разработчика получить результат

/*    for (int i = 0; i < result.size(); ++i) {

        std::cout << queries_input[i] << std::endl;

        for (int j = 0; j < result[i].size(); ++j) {

            std::cout << result[i][j].doc_id << " " << result[i][j].rank << std::endl;

        }

    }*/


    return result;

}

