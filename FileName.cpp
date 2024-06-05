#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

class Entity {
protected:
    string name;

public:
    Entity(const string& name) : name(name) {}

    string getName() const {
        return name;
    }
};

class Task : public Entity {
private:
    string deadline;
    bool isCompleted;

public:
    Task(const string& name, const string& dl) : Entity(name), deadline(dl), isCompleted(false) {}

    void markCompleted() {
        isCompleted = true;
    }

    bool getStatus() const {
        return isCompleted;
    }

    string getDeadline() const {
        return deadline;
    }

    void setDeadline(const string& dl) {
        deadline = dl;
    }

    void displayTask() const {
        cout << "Task: " << name << ", Deadline: " << deadline << ", Completed: " << (isCompleted ? "Yes" : "No") << endl;
    }
};

class User : public Entity {
private:
    vector<Task> tasks;

public:
    User(const string& uname) : Entity(uname) {}

    void assignTask(const Task& task) {
        tasks.push_back(task);
    }

    void displayTasks() const {
        cout << "Tasks for user: " << name << endl;
        for (const auto& task : tasks) {
            task.displayTask();
        }
    }

    void completeTask(const string& taskName) {
        for (auto& task : tasks) {
            if (task.getName() == taskName) {
                task.markCompleted();
                break;
            }
        }
    }

    void updateTaskDeadline(const string& taskName, const string& newDeadline) {
        for (auto& task : tasks) {
            if (task.getName() == taskName) {
                task.setDeadline(newDeadline);
                break;
            }
        }
    }
};

class Project {
private:
    string projectName;
    vector<User> users;

public:
    Project(const string& name) : projectName(name) {}

    void addUser(const User& user) {
        users.push_back(user);
    }

    User* findUser(const string& username) {
        auto it = find_if(users.begin(), users.end(), [&](const User& user) {
            return user.getName() == username;
            });
        return it != users.end() ? &(*it) : nullptr;
    }

    void displayProjectDetails() const {
        cout << "Project: " << projectName << endl;
        for (const auto& user : users) {
            user.displayTasks();
        }
    }

    bool userExists(const string& username) const {
        return find_if(users.begin(), users.end(), [&](const User& user) {
            return user.getName() == username;
            }) != users.end();
    }
};

void showMenu() {
    cout << "\nTask Management System Menu:\n";
    cout << "1. Add User\n";
    cout << "2. Add Task\n";
    cout << "3. Update Task Deadline\n";
    cout << "4. Mark Task as Completed\n";
    cout << "5. Display Project Details\n";
    cout << "6. Exit\n";
    cout << "Enter your choice: ";
}

int main() {
    Project project("Website Development");

    int choice;
    do {
        showMenu();
        cin >> choice;

        switch (choice) {
        case 1: {
            string username;
            cout << "Enter username: ";
            cin >> username;

            if (!project.userExists(username)) {
                project.addUser(User(username));
                cout << "User added successfully.\n";
            }
            else {
                cout << "User already exists.\n";
            }
            break;
        }
        case 2: {
            string username, taskName, deadline;
            cout << "Enter username: ";
            cin >> username;
            cout << "Enter task name: ";
            cin.ignore();
            getline(cin, taskName);
            cout << "Enter deadline: ";
            getline(cin, deadline);

            User* user = project.findUser(username);
            if (user) {
                user->assignTask(Task(taskName, deadline));
            }
            else {
                cout << "User not found.\n";
            }
            break;
        }
        case 3: {
            string username, taskName, newDeadline;
            cout << "Enter username: ";
            cin >> username;
            cout << "Enter task name: ";
            cin.ignore();
            getline(cin, taskName);
            cout << "Enter new deadline: ";
            getline(cin, newDeadline);

            User* user = project.findUser(username);
            if (user)
            {
                user->updateTaskDeadline(taskName, newDeadline);
            }
            else {
                cout << "User not found.\n";
            }
            break;
        }
        case 4: {
            string username, taskName;
            cout << "Enter username: ";
            cin >> username;
            cout << "Enter task name: ";
            cin.ignore();
            getline(cin, taskName);

            User* user = project.findUser(username);
            if (user) {
                user->completeTask(taskName);
            }
            else {
                cout << "User not found.\n";
            }
            break;
        }
        case 5: {
            project.displayProjectDetails();
            break;
        }
        case 6: {
            cout << "Exiting...\n";
            break;
        }
        default: {
            cout << "Invalid choice. Please try again.\n";
            break;
        }
        }
    } while (choice != 6);

    return 0;
}
