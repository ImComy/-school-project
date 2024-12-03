#include<iostream>
#include<string>
using namespace std;

const int MAX_STUDENTS = 50;
const int MAX_COURSES = 50;
const int MAX_SCORES = 50;

class Student {
    private:
        int Num;
        string Name;
        char Gender;
        int Age;
        string Institution;
        string Major;

    public:
        void set_Num(int value) { Num = value; }
        void set_Gender(char value) { Gender = value; }
        void set_Name(string value) { Name = value; }
        void set_Age(int value) { Age = value; }
        void set_Institution(string value) { Institution = value; }
        void set_Major(string value) { Major = value; }

        int get_Num() { return Num; }
        string get_Name() { return Name; }
        char get_Gender() { return Gender; }
        int get_Age() { return Age; }
        string get_Institution() { return Institution; }
        string get_Major() { return Major; }

        void displayStudent() {
            cout << "Student No: " << Num << "\n"
                << "Name: " << Name << "\n"
                << "Gender: " << Gender << "\n"
                << "Age: " << Age << "\n"
                << "Institution: " << Institution << "\n"
                << "Major: " << Major << "\n";
        }
};

class Course {
    private:
        string Name;
        int Num;
        int credit;
        bool property;

    public:
        void set_Name(string value) { Name = value; }
        void set_Num(int value) { Num = value; }
        void set_Credit(int value) { credit = value; }
        void set_Property(bool value) { property = value; }

        string get_Name() { return Name; }
        int get_Num() { return Num; }
        int get_Credit() { return credit; }
        bool get_Property() { return property; }

        void displayCourse() {
            cout << "Course Name: " << Name << "\n"
                << "Course No: " << Num << "\n"
                << "Credits: " << credit << "\n"
                << "Compulsory: " << (property ? "Yes" : "No") << "\n";
        }
};

class Student_Score {
    private:
        int studentNum;
        int courseNum;
        float score;

    public:
        void set_StudentNum(int value) { studentNum = value; }
        void set_CourseNum(int value) { courseNum = value; }
        void set_Score(float value) { score = value; }

        int get_StudentNum() { return studentNum; }
        int get_CourseNum() { return courseNum; }
        float get_Score() { return score; }

        void displayStudentScore(Student students[], int studentCount, Course courses[], int courseCount) {
            string studentName = "Unknown";
            string courseName = "Unknown";

            for (int i = 0; i < studentCount; i++) {
                if (students[i].get_Num() == studentNum) {
                    studentName = students[i].get_Name();
                    break;
                }
            }

            for (int i = 0; i < courseCount; i++) {
                if (courses[i].get_Num() == courseNum) {
                    courseName = courses[i].get_Name();
                    break;
                }
            }

            cout << "Student: " << studentName << " (" << studentNum << ")\n"
                << "Course: " << courseName << " (" << courseNum << ")\n"
                << "Score: " << score << "\n";
        }
};

void displayMenu() {
    cout << "\n\t\t\t\t" << "***** Welcome to the Student Information System *****\n";
    cout << "\nSelect an option:\n";
    cout << "---------------------------------------------\n";
    cout << "1. Add Student\n";
    cout << "2. Display Students\n";
    cout << "3. Add Course\n";
    cout << "4. Display Courses\n";
    cout << "5. Add Student Score\n";
    cout << "6. Display Student Scores\n";
    cout << "0. Exit\n";
    cout << "---------------------------------------------\n";
    cout << "Enter your choice (0-6): ";
}

void addStudent(Student students[], int& studentCount) {
    if (studentCount >= MAX_STUDENTS) {
        cout << "Maximum number of students reached. Cannot add more students.\n";
        return;
    }

    Student student;
    int num, age;
    char gender;
    string name, institution, major;

    cout << "Enter Student No: ";
    cin >> num;
    cin.ignore();
    cout << "Enter Name: ";
    getline(cin, name);
    cout << "Enter Gender (M/F): ";
    cin >> gender;
    cout << "Enter Age: ";
    cin >> age;
    cin.ignore();
    cout << "Enter Institution: ";
    getline(cin, institution);
    cout << "Enter Major: ";
    getline(cin, major);

    student.set_Num(num);
    student.set_Name(name);
    student.set_Gender(gender);
    student.set_Age(age);
    student.set_Institution(institution);
    student.set_Major(major);

    students[studentCount++] = student;
    cout << "Student added successfully!\n";
}

void displayStudents(Student students[], int studentCount) {
    if (studentCount == 0) {
        cout << "No students to display.\n";
        return;
    }

    cout << "\n***** Student List *****\n";
    for (int i = 0; i < studentCount; i++) {
        students[i].displayStudent();
        cout << "------------------------\n";
    }
}

void addCourse(Course courses[], int& courseCount) {
    if (courseCount >= MAX_COURSES) {
        cout << "Maximum number of courses reached. Cannot add more courses.\n";
        return;
    }

    Course course;
    int num, credit;
    bool property;
    string name;

    cout << "Enter Course No: ";
    cin >> num;
    cin.ignore();
    cout << "Enter Course Name: ";
    getline(cin, name);
    cout << "Enter Course Credits: ";
    cin >> credit;
    cout << "Is the course compulsory? (1 for Yes, 0 for No): ";
    cin >> property;

    course.set_Num(num);
    course.set_Name(name);
    course.set_Credit(credit);
    course.set_Property(property);

    courses[courseCount++] = course;
    cout << "Course added successfully!\n";
}

void displayCourses(Course courses[], int courseCount) {
    if (courseCount == 0) {
        cout << "No courses to display.\n";
        return;
    }

    cout << "\n***** Course List *****\n";
    for (int i = 0; i < courseCount; i++) {
        courses[i].displayCourse();
        cout << "------------------------\n";
    }
}

void addStudentScore(Student_Score scores[], int& scoreCount, Student students[], int studentCount, Course courses[], int courseCount) {
    if (scoreCount >= MAX_SCORES) {
        cout << "Maximum number of scores reached. Cannot add more scores.\n";
        return;
    }

    int studentNum, courseNum;
    float score;
    cout << "Enter Student No: ";
    cin >> studentNum;
    cout << "Enter Course No: ";
    cin >> courseNum;
    cout << "Enter Score: ";
    cin >> score;

    bool studentExists = false, courseExists = false;

    for (int i = 0; i < studentCount; i++) {
        if (students[i].get_Num() == studentNum) {
            studentExists = true;
            break;
        }
    }

    for (int i = 0; i < courseCount; i++) {
        if (courses[i].get_Num() == courseNum) {
            courseExists = true;
            break;
        }
    }

    if (!studentExists) {
        cout << "Student does not exist! (Student No: " << studentNum << ")\n";
        return;
    }

    if (!courseExists) {
        cout << "Course does not exist! (Course No: " << courseNum << ")\n";
        return;
    }

    Student_Score studentScore;
    studentScore.set_StudentNum(studentNum);
    studentScore.set_CourseNum(courseNum);
    studentScore.set_Score(score);

    scores[scoreCount++] = studentScore;
    cout << "Score added successfully!\n";
}

void displayStudentScores(Student_Score scores[], int scoreCount, Student students[], int studentCount, Course courses[], int courseCount) {
    if (scoreCount == 0) {
        cout << "No student scores to display.\n";
        return;
    }

    cout << "\n***** Student Scores *****\n";
    for (int i = 0; i < scoreCount; i++) {
        scores[i].displayStudentScore(students, studentCount, courses, courseCount);
        cout << "------------------------\n";
    }
}

int main() {
    Student students[MAX_STUDENTS];
    Course courses[MAX_COURSES];
    Student_Score scores[MAX_SCORES];

    int studentCount = 0, courseCount = 0, scoreCount = 0;
    int choice;

    do {
        displayMenu();
        cin >> choice;

        switch (choice) {
            case 1:
                addStudent(students, studentCount);
                break;
            case 2:
                displayStudents(students, studentCount);
                break;
            case 3:
                addCourse(courses, courseCount);
                break;
            case 4:
                displayCourses(courses, courseCount);
                break;
            case 5:
                addStudentScore(scores, scoreCount, students, studentCount, courses, courseCount);
                break;
            case 6:
                displayStudentScores(scores, scoreCount, students, studentCount, courses, courseCount);
                break;
            case 0:
                cout << "Exiting the system...\n";
                break;
            default:
                cout << "Invalid choice, please try again.\n";
        }
    } while (choice != 0);

    return 0;
}
