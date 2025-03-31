#include "lesser_pandas.h"

int main() {
    string file_dir = "data.csv";
    DataFrame df(file_dir);

    cout << df << endl;
    cout << df["c2"] << endl;
    df.head();
    cout << endl;
    df.tail();

    return 0;
}
