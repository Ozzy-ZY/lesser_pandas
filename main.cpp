#include "lesser_pandas.h"

int main() {
    string file_dir = "test.csv";
    DataFrame df(file_dir);

    //cout << df << endl;
    df.head();
    //df.rename({{"id", "new_id"}, {"trip_duration", "nigaaaaaaa"}});
    cout << df["pickup_longitude"].dtype << endl;
    cout << df["pickup_longitude"].mean() << endl;
    cout << df["id"] << endl;
    df.head();

    return 0;
}
