#include "lesser_pandas.h"

int main() {
    try {
        DataFrame df("titanic.csv");

        // cout << "Full DataFrame:\n";
        // cout << df << endl;

        // cout << "First 3 rows:\n";
        // df.head(3);

        // cout << "Last 2 rows:\n";
        // df.tail(2);

        // // Access a single column
        // Column& age_col = df["Age"];
        // cout << "Age column:\n" << age_col << endl;

        // // Compute mean of Age column (ignoring missing values)
        // cout << "Mean age: " << age_col.mean() << endl;

        // age_col.fillna(age_col.mean());
        // cout << "Age column after filling missing values with the average:\n" << age_col << endl;

        // // Save the DataFrame to a file named "output.csv"
        // df.save_to_csv("output.csv", true, "|", true, "N/A", {"Age", "Salary"});

        // df.fillna(5);
        // cout << "DataFrame after filling missing values:\n";
        // cout << df << endl;

        // // Rename columns
        // df.rename({{"Age", "Years"}, {"Salary", "Income"}});
        // cout << "DataFrame after renaming columns:\n";
        // cout << df << endl;
        // cout << df["Income"];

        // cout << "Min Salary: " << df["Income"].min() << endl;
        // cout << "Max Salary: " << df["Income"].max() << endl;

        //cout << df["Age"] << endl; // print Sex column as (',') comma spilt
        /*
            so if we print any col before Name col , it works well 
            but if we print any col after Name col , it will not work well as there are (,) in name
        */

        auto newData = df[df["Survived"] < 1];
        cout << newData << endl;
        /*
            will works noramally as we are using col prev Name 
        */

        // DataSet name is titanic.csv

    } catch (const exception& e) {
        cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
    return 0;
}
