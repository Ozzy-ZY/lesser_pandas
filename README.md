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
    df.tail();
    cout << df["col_name"].mean() << endl;

    return 0;
}
```

## TODO
### Contributions are welcomed

- [x] Rename a column
- [ ] `fillna`: Fill missing values
- [ ] `dropna(col_name)`: Drop rows where `col_name` is missing
- [ ] `df.describe()`: Descriptive statistics
- [ ] `df.corr()`: Correlation matrix
- [ ] `df[df['Amount'] > 1000]`: Filter rows based on a condition
- [ ] `df.sum()`: Returns the sum of all rows
- [ ] `df["col"].sum()`
  - If the column contains non-numeric data (e.g., strings), `sum()` will concatenate them.
  - If the column has missing values (NaN), they will be ignored by default unless you specify `skipna=False`.
