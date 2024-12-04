/*
C++ Programming Project
3.  Student Score and Information Management System

Made by: Ahmed El-Shazly
*/

#include<iostream>
#include<string>
using namespace std;

const int MAX_STUDENTS = 50;
const int MAX_COURSES = 150;
const int MAX_SCORES = 150;

class Student {
    private:
        int Num;
        string Name;
        char Gender;
        int Age;
        string Institution;
        string Major;
        int selectedCourses[MAX_COURSES]; 
        int courseCredits[MAX_COURSES];   
        int totalCredits;

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
                 << "Major: " << Major << "\n"
                 << "Selected Courses: \n";

            /*checking if there any course to be displayed*/
            bool foundCourse = false;
            for (int i = 0; i < MAX_COURSES; i++) {
                if (selectedCourses[i] != -1) {
                    cout << "Course No: " << selectedCourses[i]
                         << ", Credits: " << courseCredits[i] << "\n";
                    foundCourse = true;
                }
            }
            if (!foundCourse) {
                cout << "No courses selected.\n";
            }

            cout << "Total Credits: " << totalCredits << "\n";
        }

        /*replacing the first uninitialized element in the selectedCourses array to the new course*/
        void addCourse(int courseNum, int credits) {
            if (totalCredits + credits <= 32) {
                for (int i = 0; i < MAX_COURSES; i++) {
                    if (selectedCourses[i] == -1) {
                        selectedCourses[i] = courseNum;
                        courseCredits[i] = credits; 
                        totalCredits += credits;
                        cout << "Course added successfully! Total credits: " << totalCredits << "\n";
                        break;
                    }
                }
            } else {
                cout << "Cannot add course. Total credits would exceed 32.\n";
            }
        }

        int getTotalCredits() {
            return totalCredits;
        }
};

class Course {
    private:
        string Name;
        int Num;
        int credit;
        bool property;
        int studentNums[MAX_STUDENTS]; 
        int studentCount;

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
            cout << "Students who selected this course: ";

            /*checking if there any students that have selected this course*/
            bool found = false;
            for (int i = 0; i < studentCount; i++) {
                if (studentNums[i] != -1) {
                    cout << studentNums[i] << " ";
                    found = true;
                }
            }
            if (!found) {
                cout << "No students selected this course yet.";
            }
            cout << "\n";
        }
        
        /*add a new student no to the list of students who have selected this course
        if the number of students who have selected this course hasnt reached its max yet*/
        void addStudent(int studentNum) {
            if (studentCount < MAX_STUDENTS) {
                studentNums[studentCount++] = studentNum;
            }
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
            /*initial value of the name of the student and the course*/
            string studentName = "Unknown";
            string courseName = "Unknown";

            /*searches for a Student name in the students array thats a student object 
            based on the student's number*/
            for (int i = 0; i < studentCount; i++) {
                if (students[i].get_Num() == studentNum) {
                    studentName = students[i].get_Name();
                    break;
                }
            }

            /*searches for a Course name in the courses array thats a Course object 
            based on the course's number*/
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
    cout << "7. Select Courses for a Student\n";  
    cout << "8. Delete Student\n"; 
    cout << "9. Delete Course\n"; 
    cout << "10. Display Failed Students\n";
    cout << "11. Modify Student Information\n";  
    cout << "12. Modify Course Information\n"; 
    cout << "0. Exit\n";
    cout << "---------------------------------------------\n";
    cout << "Enter your choice (0-12): ";
}

/*Student Functions*/
void addStudent(Student students[], int& studentCount) {
    if (studentCount >= MAX_STUDENTS) {
        cout << "Maximum number of students has been reached.\n";
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

void modifyStudent(Student students[], int studentCount) {
    int studentNum;
    cout << "Enter Student No to modify: ";
    cin >> studentNum;

    bool found = false;
    for (int i = 0; i < studentCount; i++) {
        if (students[i].get_Num() == studentNum) {
            found = true;
            int option;
            cout << "1. Modify Name\n";
            cout << "2. Modify Gender\n";
            cout << "3. Modify Age\n";
            cout << "4. Modify Institution\n";
            cout << "5. Modify Major\n";
            cout << "Enter your choice: ";
            cin >> option;
            cin.ignore(); 

            switch (option) {
                case 1: {
                    string name;
                    cout << "Enter new name: ";
                    getline(cin, name);
                    students[i].set_Name(name);
                    break;
                }
                case 2: {
                    char gender;
                    cout << "Enter new gender (M/F): ";
                    cin >> gender;
                    students[i].set_Gender(gender);
                    break;
                }
                case 3: {
                    int age;
                    cout << "Enter new age: ";
                    cin >> age;
                    students[i].set_Age(age);
                    break;
                }
                case 4: {
                    string institution;
                    cout << "Enter new institution: ";
                    cin.ignore();
                    getline(cin, institution);
                    students[i].set_Institution(institution);
                    break;
                }
                case 5: {
                    string major;
                    cout << "Enter new major: ";
                    getline(cin, major);
                    students[i].set_Major(major);
                    break;
                }
                default:
                    cout << "Invalid choice.\n";
            }
            cout << "Student information updated successfully.\n";
            break;
        }
    }
    if (!found) {
        cout << "Student not found.\n";
    }
}

void addCourse(Course courses[], int& courseCount) {
    if (courseCount >= MAX_COURSES) {
        cout << "Maximum number of courses reached.\n";
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

void modifyCourse(Course courses[], int courseCount) {
    int courseNum;
    cout << "Enter Course No to modify: ";
    cin >> courseNum;

    bool found = false;
    for (int i = 0; i < courseCount; i++) {
        if (courses[i].get_Num() == courseNum) {
            found = true;
            int option;
            cout << "1. Modify Course Name\n";
            cout << "2. Modify Course Credits\n";
            cout << "3. Modify Compulsory Status\n";
            cout << "Enter your choice: ";
            cin >> option;
            cin.ignore();

            switch (option) {
                case 1: {
                    string name;
                    cout << "Enter new course name: ";
                    getline(cin, name);
                    courses[i].set_Name(name);
                    break;
                }
                case 2: {
                    int credit;
                    cout << "Enter new course credits: ";
                    cin >> credit;
                    courses[i].set_Credit(credit);
                    break;
                }
                case 3: {
                    bool property;
                    cout << "Is the course compulsory? (1 for Yes, 0 for No): ";
                    cin >> property;
                    courses[i].set_Property(property);
                    break;
                }
                default:
                    cout << "Invalid choice.\n";
            }
            cout << "Course information updated successfully.\n";
            break;
        }
    }
    if (!found) {
        cout << "Course not found.\n";
    }
}

void deleteStudent(Student students[], int& studentCount) {
    int studentNum;
    cout << "Enter Student No to delete: ";
    cin >> studentNum;

    bool found = false;
    for (int i = 0; i < studentCount; i++) {
        if (students[i].get_Num() == studentNum) {
            found = true;
            for (int j = i; j < studentCount - 1; j++) {
                students[j] = students[j + 1];
            }
            studentCount--;
            cout << "Student with Student No " << studentNum << " deleted successfully.\n";
            break;
        }
    }

    if (!found) {
        cout << "Student not found!\n";
    }
}

void deleteCourse(Course courses[], int& courseCount) {
    int courseNum;
    cout << "Enter Course No to delete: ";
    cin >> courseNum;

    bool found = false;
    for (int i = 0; i < courseCount; i++) {
        if (courses[i].get_Num() == courseNum) {
            found = true;
            for (int j = i; j < courseCount - 1; j++) {
                courses[j] = courses[j + 1];
            }
            courseCount--;
            cout << "Course with Course No " << courseNum << " deleted successfully.\n";
            break;
        }
    }

    if (!found) {
        cout << "Course not found!\n";
    }
}

void selectCoursesForStudent(Student students[], int studentCount, Course courses[], int courseCount) {
    int studentNum, courseNum;
    cout << "Enter Student No: ";
    cin >> studentNum;

    bool studentFound = false;
    for (int i = 0; i < studentCount; i++) {
        if (students[i].get_Num() == studentNum) {
            studentFound = true;
            cout << "Enter course numbers (Enter -1 to stop):\n";
            while (true) {
                cout << "Enter Course No: ";
                cin >> courseNum;

                if (courseNum == -1) {
                    break;
                }

                bool courseFound = false;
                for (int j = 0; j < courseCount; j++) {
                    if (courses[j].get_Num() == courseNum) {
                        courses[j].addStudent(studentNum); 
                        students[i].addCourse(courseNum, courses[j].get_Credit());
                        courseFound = true;
                        break;
                    }
                }

                if (!courseFound) {
                    cout << "Course not found. Try again.\n";
                }
            }
            break;
        }
    }

    if (!studentFound) {
        cout << "Student not found.\n";
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
    cout << "Enter Score (Minimum 100): ";
    cin >> score;

    if (score < 100) {
        cout << "Score is below minimum. Setting score to 100.\n";
        score = 100;
    }

    scores[scoreCount].set_StudentNum(studentNum);
    scores[scoreCount].set_CourseNum(courseNum);
    scores[scoreCount].set_Score(score);
    scoreCount++;
    cout << "Score added successfully!\n";
}

void displayFailedStudents(Student_Score scores[], int scoreCount, Student students[], int studentCount) {
    bool found = false;
    cout << "\n***** Students Who Failed Courses *****\n";
    for (int i = 0; i < scoreCount; i++) {
        if (scores[i].get_Score() < 100) {
            int studentNum = scores[i].get_StudentNum();
            for (int j = 0; j < studentCount; j++) {
                if (students[j].get_Num() == studentNum) {
                    students[j].displayStudent();
                    cout << "Failed Course No: " << scores[i].get_CourseNum() << ", Score: " << scores[i].get_Score() << "\n";
                    found = true;
                    break;
                }
            }
        }
    }

    if (!found) {
        cout << "No students failed any courses.\n";
    }
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
            case 1: addStudent(students, studentCount); break;
            case 2: displayStudents(students, studentCount); break;
            case 3: addCourse(courses, courseCount); break;
            case 4: displayCourses(courses, courseCount); break;
            case 5: addStudentScore(scores, scoreCount, students, studentCount, courses, courseCount); break;
            case 6: displayStudentScores(scores, scoreCount, students, studentCount, courses, courseCount); break;
            case 7: selectCoursesForStudent(students, studentCount, courses, courseCount); break;
            case 8: deleteStudent(students, studentCount); break;
            case 9: deleteCourse(courses, courseCount); break;
            case 10: displayFailedStudents(scores, scoreCount, students, studentCount); break;
            case 11: modifyStudent(students, studentCount); break;
            case 12: modifyCourse(courses, courseCount); break;
            case 0: cout << "Exiting the system...\n"; break;
            default:cout << "Invalid choice. Try again.\n";
        }
    } while (choice != 0);

    return 0;
}
