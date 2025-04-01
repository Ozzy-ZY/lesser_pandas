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
using namespace std;

class Column {
public:
    string name; // column's name
    vector<string> data; // column's data
    string dtype = "string"; // data type
    friend std::ostream& operator<<(std::ostream& os, const Column& col);

    void print() const {
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
        vector<string> result = data;

        if (result.size() <= 1) {
            return result;
        }
        
        auto compare = [this](const string& a, const string& b) -> bool {
            if (dtype == "int" || dtype == "float") {
                return stod(a) < stod(b);
            }
            throw invalid_argument("Invalid type: Column::Sorted() expects `dtype` to be int or float");

        };
        
        vector<string> temp(result.size());
        
        for (size_t width = 1; width < result.size(); width *= 2) {
            for (size_t i = 0; i < result.size(); i += 2 * width) {
                size_t left = i;
                size_t mid = min(i + width, result.size());
                size_t right = min(i + 2 * width, result.size());
                
                size_t l = left;
                size_t r = mid;
                size_t k = left;
                
                while (l < mid && r < right) {
                    if (compare(result[l], result[r])) {
                        temp[k++] = result[l++];
                    } else {
                        temp[k++] = result[r++];
                    }
                }
        
                while (l < mid) {
                    temp[k++] = result[l++];
                }
                
                while (r < right) {
                    temp[k++] = result[r++];
                }
                
                for (size_t j = left; j < right; j++) {
                    result[j] = temp[j];
                }
            }
        }
        
        return result;
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

    void print(int rows_cnt = 0, int is_tail = 0) const {
        if (rows_cnt == 0) {
            rows_cnt = row_data.size();
        }

        size_t idx = 0;
        for(auto& row : row_data) {
            if (is_tail && idx < static_cast<size_t>(row_data.size()-rows_cnt)) {
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
            if (idx == static_cast<size_t>(rows_cnt + 1) && !is_tail) {
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
