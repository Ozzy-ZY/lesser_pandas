#include "lesser_pandas.h"

int main() {
    string file_dir = "test.csv";
    DataFrame df(file_dir);

    //cout << df << endl;
    //cout << df["pickup_datetime"] << endl;
    df.head();

    return 0;
}
