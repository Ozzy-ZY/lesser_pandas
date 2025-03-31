#include "lesser_pandas.h"

int main() {
    string file_dir = "test.csv";
    DataFrame df(file_dir);

    //cout << df << endl;
    df.head();
    //cout << df["trip_duration"] << endl;

    return 0;
}
