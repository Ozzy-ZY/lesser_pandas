#include "lesser_pandas.h"

int main() {
    string file_dir = "test.csv";
    DataFrame df(file_dir);

    cout << df << endl;
    df.head();
    cout << df["id"].dtype << endl;
    cout << df["id"].mean() << endl;

    return 0;
}
