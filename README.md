# Lesser Pandas
![Logo](assets/lesser_pandas_logo.png)

## Pandas-like Data Analysis Library in C++

### Examples:

```cpp
#include "lesser_pandas.h"

int main() {
    string file_dir = "data.csv";
    DataFrame df(file_dir);

    cout << df << endl;
    cout << df["col_name"] << endl;
    df.head();
    cout << endl;
    df.tail();

    return 0;
}
```
