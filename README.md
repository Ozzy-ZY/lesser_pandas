# Lesser Pandas
![Logo](assets/lesser_pandas_logo.png)

## Pandas-like Data Analysis Library in C++

### Examples:

```cpp
#include "lesser_pandas.h"

int main() {
    DataFrame df("data.csv");

    cout << "Full DataFrame:\n";
    cout << df << endl;

    cout << "First 3 rows:\n";
    df.head(3);

    cout << "Last 2 rows:\n";
    df.tail(2);

    // Access a single column
    Column& age_col = df["Age"];
    cout << "Age column:\n" << age_col << endl;

    // Compute mean of Age column (ignoring missing values)
    cout << "Mean age: " << age_col.mean() << endl;

    age_col.fillna(age_col.mean());
    cout << "Age column after filling missing values with the average:\n" << age_col << endl;

    df.fillna(5);
    cout << "DataFrame after filling missing values:\n";
    cout << df << endl;

    // Rename columns
    df.rename({{"Age", "Years"}, {"Salary", "Income"}});
    cout << "DataFrame after renaming columns:\n";
    cout << df << endl;
    cout << df["Income"];

    cout << "Min Salary: " << df["Income"].min() << endl;
    cout << "Max Salary: " << df["Income"].max() << endl;

    return 0;
}
```

## TODO
### Contributions are welcomed

- [x] Rename a column
- [x] `fillna`: Fill missing values
- [x] `dropna(col_name)`: Drop rows where `col_name` is missing
- [ ] `df.describe()`: Descriptive statistics
- [ ] `df.corr()`: Correlation matrix
- [ ] `df[df['Amount'] > 1000]`: Filter rows based on a condition
- [ ] `df.sum()`: Returns the sum of all rows
- [ ] `df["col"].sum()`
  - If the column contains non-numeric data (e.g., strings), `sum()` will concatenate them.
  - If the column has missing values (NaN), they will be ignored by default unless you specify `skipna=False`.
- [ ] `df.to_csv('cleaned_data.csv')` save a modified dataframe to a new csv file.
- [ ] Implement A Test Suit for Lesser Pandas.
