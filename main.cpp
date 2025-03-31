#include "lesser_pandas.h"

int main() {
    string file_dir = "test.csv";
    DataFrame df(file_dir);

    //cout << df << endl;
    df.head();
    cout << df["trip_duration"].dtype << endl;
    cout << df["trip_duration"].mean() << endl;

    return 0;
}
