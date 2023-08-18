#include <iostream>
#include <string>
using namespace std;

class Course {
private:
    string courseName;
    string assessmentItem[10];
    int weightPercentage[10];
    int totalGrade[10];
    int yourGrade[10];
    int itemCount;

public:
    Course() {
        itemCount = 0;
    }

    void addAssessmentItem(const string& item, int weight, int total, int your) {
        assessmentItem[itemCount]= item;
        weightPercentage[itemCount]= weight;
        totalGrade[itemCount]= total;
        yourGrade[itemCount]= your;
        itemCount++;
    }

    double calculateWeightedAverage() {
        double weightedAverage = 0.0;
        for (int i = 0; i < itemCount; i++) {
            weightedAverage += static_cast<double>(weightPercentage[i]) * yourGrade[i] / totalGrade[i];
        }
        return weightedAverage;
    }

    string getPassingMessage() {
        double weightedAverage = calculateWeightedAverage();
        if (weightedAverage > 50) {
            return "Congratulations! You have passed the course with " + to_string(static_cast<int>(weightedAverage)) + " points but you can do even better!";
        } else {
            return "Your average grade is now " + to_string(static_cast<int>(weightedAverage)) + ". Keep up! You still need " + to_string(static_cast<int>(50 - weightedAverage)) + " to pass the course.";
        }
    }
};

int main() {
    Course course;
    string courseName;
    string itemName;
    int weight, total, your;
    char choice;

    cout << "What's your course? ";
    getline(cin, courseName);
    courseName[0] = toupper(courseName[0]); // Capitalize the first letter
    
    int totalWeight = 0;
    while (totalWeight < 100) {
        cout << "Enter your assessment item (item name, weight %(1-100), total grade, your grade) (Note: separated by space): ";
        cin >> itemName >> weight >> total >> your;
        cin.ignore(); // Clear newline from buffer

        if ( your <= total && weight > 0 && weight <= 100 && totalWeight + weight <= 100) {
            course.addAssessmentItem(itemName, weight, total, your);
            totalWeight += weight;

            if (totalWeight == 100) {
                cout << course.getPassingMessage() << endl;
                return 0;
            }

        } else {
            cout << "Invalid inputs, please try again." << endl;
            continue;
        }

        cout << "Add another assessment item ('y') or get the average grade now ('g'): ";
        cin >> choice;
        cin.ignore(); // Clear newline from buffer

        if (choice == 'g' || choice == 'G') {
            cout << course.getPassingMessage() << endl;
            return 0;
        }
    }

    return 0;
}
