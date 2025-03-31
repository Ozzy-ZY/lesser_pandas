#include "lesser_pandas.h"

int main() {
    string file_dir = "test.csv";
    DataFrame df(file_dir);

    cout << df << endl;
    df.head();
    cout << df["pickup_latitude"].dtype << endl;
    cout << df["pickup_latitude"].mean() << endl;

    return 0;
}
