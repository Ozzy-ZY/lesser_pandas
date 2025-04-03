/*
 * Copyright (c) 2025 Ahmed Hossam <https://github.com/ahmedhosssam>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

#ifndef LESSER_PANDAS
#define LESSER_PANDAS

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <stdexcept>
#include <map>
#include <iomanip>
#include <algorithm>
#include <type_traits>
using namespace std;

class Column {
public:
    string name; // column's name
    vector<string> data; // column's data
    string dtype = "string"; // data type
    friend std::ostream& operator<<(std::ostream& os, const Column& col);

    void print() const {
        if (data.size() == 0) {
            return;
        }

        cout << name << endl;
        for(size_t i = 0; i < name.length(); i++) {
            cout << '-';
        }
        cout << endl;
        for(const string &str : data) {
            cout << str << endl;
        }
    }

    double mean() const {
        if (dtype == "int" || dtype == "float") {
            double sum = 0;
            double col_size = static_cast<double> (data.size());
            for(const string& element : data) {
                double num = stod(element);
                sum += num;
            }
            return sum / col_size;
        }

        throw invalid_argument("Invalid type: Column::mean() expects `dtype` to be int or float");
    }
    
    vector<string> sorted() const {
        if (dtype == "string") {
            throw invalid_argument("Invalid type: Column::Sorted() expects `dtype` to be int or float");
        }
        vector<string> result = data;

        std::sort(result.begin(), result.end(), [](string &s1, string &s2) {
            return stod(s1) < stod(s2);
        });
        
        return result;
    }

    double min() {
        if (dtype == "string") {
            throw invalid_argument("Invalid type: Column::min() expects `dtype` to be int or float");
        }
        vector<string> sorted_col = sorted();
        double mn = stod(sorted_col[0]);

        return mn;
    }

    double max() {
        if (dtype == "string") {
            throw invalid_argument("Invalid type: Column::max() expects `dtype` to be int or float");
        }
        vector<string> sorted_col = sorted();
        double mx = stod(sorted_col[sorted_col.size()-1]);

        return mx;
    }
};

bool is_integer(const string& s) {
    try {
        size_t pos;
        stoi(s, &pos);
        return pos == s.length();
    } catch (...) {
        return false;
    }
}

bool is_float(const string& s) {
    try {
        size_t pos;
        stod(s, &pos);
        return pos == s.length();
    } catch (...) {
        return false;
    }
}

class DataFrame {
private:
    map<string, Column> col_data;
    vector<vector<string>> row_data; // used for printing
    string file_dir;
public:
    vector<string> columns;
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
            vector<string> temp_row;

            if (idx == 0) {
                idx = 1;
                while(getline(ss, element, delim)) {
                    Column col;
                    col.name = element;
                    columns.push_back(element);

                    temp_data.push_back(col);
                    temp_row.push_back(element);
                }
                row_data.push_back(temp_row);
                continue;
            }

            size_t jdx = 0;
            while(getline(ss, element, delim)) {
                temp_data[jdx].data.push_back(element);
                temp_row.push_back(element);
                jdx++;
            }
            if (temp_row.size() < row_data[0].size()) {
                // there is a missing element in that row (in the last column)
                temp_row.push_back("");
                temp_data[jdx-1].data.push_back("");
            }
            row_data.push_back(temp_row);
        }
        for (auto& col : temp_data) {
            bool all_int = true;
            bool all_float = true;
            for (const string& element : col.data) {
                if (!is_integer(element)) {
                    all_int = false;
                }
                if (!is_float(element)) {
                    all_float = false;
                }
                if (!all_int && !all_float) {
                    break;
                }
            }
            if (all_int) {
                col.dtype = "int";
            } else if (all_float) {
                col.dtype = "float";
            } else {
                col.dtype = "string";
            }
        }
        for(Column col : temp_data) {
            col_data[col.name] = col;
        }
    }

    void print(int rows_cnt = 0, int is_tail = 0, vector<string> cols = {}) const {
        if (rows_cnt == 0) {
            rows_cnt = row_data.size();
        }

        if (cols.size() == 0) {
            cols = columns;
        }

        vector<vector<string>> print_row_data;

        for(size_t i = 0; i < row_data.size(); i++) {
            size_t col_idx = 0;
            vector<string> new_row;
            for(string col : cols) {
                for(size_t j = 0; j < row_data[0].size(); j++) {
                    if (row_data[0][j] == col) {
                        new_row.push_back(row_data[i][j]);
                        col_idx++;
                    }
                }
            }
            print_row_data.push_back(new_row);
        }

        size_t idx = 0;
        for(auto& row : print_row_data) {
            cout << std::left;
            if (is_tail && idx < static_cast<size_t>(row_data.size()-rows_cnt)) {
                if (idx == 0) {
                    for(auto& element : row) {
                        cout << setw(20) << element;
                    }
                    cout << endl;
                }
                idx++;
                continue;
            }
            for(auto& element : row) {
                cout << setw(20) << element;
            }
            cout << endl;
            idx++;
            if (idx == static_cast<size_t>(rows_cnt + 1) && !is_tail) {
                break;
            }

            if (idx == row_data.size() && is_tail) {
                break;
            }
        }
        cout << "\nPrinted: " << print_row_data.size() << " rows\n";
    }

    void head(int rows_cnt = 5) const {
        print(rows_cnt);
    };

    void tail(int rows_cnt = 5) const {
        print(rows_cnt, 1);
    };

    void rename(vector<pair<string, string>> vec) {
        for(pair<string, string> col_pair : vec) {
            string old_col_name = col_pair.first;
            string new_col_name = col_pair.second;

            auto it = col_data.find(old_col_name);
            if (it != col_data.end()) {
                col_data[new_col_name] = it->second;
                col_data[new_col_name].name = new_col_name;
                col_data.erase(old_col_name);
                for(size_t idx = 0; idx < row_data[0].size(); idx++) {
                    if (row_data[0][idx] == old_col_name) {
                        row_data[0][idx] = new_col_name;
                        break;
                    }
                }
                continue;
            }

            throw std::out_of_range("Column not found!");
        }
    }

    template <typename T>
    void fillna(T x) {
        for(size_t i = 0; i < row_data.size(); i++) {
            for(size_t j = 0; j < row_data[0].size(); j++) {
                if (row_data[i][j].length() == 0) {
                    if (is_same<T, int>::value || is_same<T, double>::value) {
                        col_data[row_data[0][j]].data[i] = to_string(x);
                        row_data[i][j] = to_string(x);
                    } else {
                        row_data[i][j] = x;
                    }
                }
            }
        }
    }

    friend std::ostream& operator<<(std::ostream& os, const DataFrame& df);

    Column& operator[](const string& key) {
        auto it = col_data.find(key);
        if (it != col_data.end()) {
            return it->second;
        }
        throw std::out_of_range("Column not found!");
    }

    Column operator[](const vector<string>& keys) {
        print(0, 0, keys);

        Column dummy;
        return dummy;
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
