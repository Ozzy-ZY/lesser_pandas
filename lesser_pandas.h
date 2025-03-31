#ifndef LESSER_PANDAS
#define LESSER_PANDAS

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <map>
using namespace std;

class Column {
public:
    string name; // column's name
    vector<string> data; // column's data
    friend std::ostream& operator<<(std::ostream& os, const Column& col);

    void print() const {
        cout << name << endl;
        for(const char& c : name) {
            cout << '-';
        }
        cout << endl;
        for(const string &str : data) {
            cout << str << endl;
        }
    }
};

class DataFrame {
private:
    map<string, Column> col_data;
    vector<vector<string>> row_data;
    string file_dir;
public:
    DataFrame(string new_file_dir) {
        file_dir = new_file_dir;
        ifstream file(file_dir);
        string line;

        vector<Column> temp_data;

        int idx = 0;
        while(getline(file, line)) {
            char delim = ',';
            stringstream ss(line);
            string element;
            vector<string> tmp_row;

            if (idx == 0) {
                idx = 1;
                while(getline(ss, element, delim)) {
                    Column col;
                    col.name = element;
                    temp_data.push_back(col);
                    tmp_row.push_back(element);
                }
                row_data.push_back(tmp_row);
                continue;
            }

            int jdx = 0;
            while(getline(ss, element, delim)) {
                temp_data[jdx].data.push_back(element);
                tmp_row.push_back(element);
                jdx++;
            }
            row_data.push_back(tmp_row);
        }

        for(Column col : temp_data) {
            col_data[col.name] = col;
        }
    }

    void print(int rows_cnt = 0, int is_tail = 0) const {
        if (rows_cnt == 0) {
            rows_cnt = row_data.size();
        }

        int idx = 0;
        int cols_names_printed = 0;
        for(auto& row : row_data) {
            if (is_tail && idx < (row_data.size()-rows_cnt)) {
                if (idx == 0) {
                    for(auto& element : row) {
                        cout << element << "\t";
                    }
                    cout << endl;
                }
                idx++;
                continue;
            }
            for(auto& element : row) {
                cout << element << "\t";
            }
            cout << endl;
            idx++;
            if (idx == rows_cnt + 1 && !is_tail) {
                break;
            }

            if (idx == row_data.size() && is_tail) {
                break;
            }
        }
    }

    void head(int rows_cnt = 5) const {
        print(rows_cnt);
    };

    void tail(int rows_cnt = 5) const {
        print(rows_cnt, 1);
    };

    friend std::ostream& operator<<(std::ostream& os, const DataFrame& df);

    Column& operator[](const string& key) {
        auto it = col_data.find(key);
        if (it != col_data.end()) {
            return it->second;
        }
        throw std::out_of_range("Column not found!");
    }
};

ostream& operator<<(std::ostream& os, const DataFrame& df) {
    df.print();
    return os;
}

ostream& operator<<(std::ostream& os, const Column& col) {
    col.print();
    return os;
}

#endif
