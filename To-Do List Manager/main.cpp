#include<iostream>
#include<fstream>
#include<string>
using namespace std;

const int MAX_TASKS = 100;

struct Task
{
    string description;
    bool isDone;
};

Task tasks[MAX_TASKS];
int taskCount = 0;

void loadTasks();
void saveTasks();
void showMenu();
void addTask();
void viewTasks();
void markDone();
void deleteTask();

int main()
{
    loadTasks();
    int choice;

    cout << "=====================================\n";
    cout << "          TO-DO LIST MANAGER         \n";
    cout << "=====================================\n";

    while(true)
    {
        showMenu();
        cout << "Enter your choice (1-5): ";
        if(!(cin >> choice))
        {
            cout << "Invalid input! Enter a number.\n";
            cin.clear();
            cin.ignore(1000, '\n');
            continue;
        }

        switch(choice)
        {
            case 1: addTask(); break;
            case 2: viewTasks(); break;
            case 3: markDone(); break;
            case 4: deleteTask(); break;
            case 5:
                saveTasks();
                cout << "All tasks saved. Exiting...\n";
                return 0;
            default:
                cout << "Invalid choice! Try again.\n";
        }
        cout << "\n";
    }
}


void showMenu() 
{
    cout << "-------------------------------------\n";
    cout << "1. Add Task\n";
    cout << "2. View Tasks\n";
    cout << "3. Mark Task as Done\n";
    cout << "4. Delete Task\n";
    cout << "5. Exit & Save\n";
    cout << "-------------------------------------\n";
}


void addTask()
{
    if(taskCount >= MAX_TASKS)
    {
        cout << "Task list full! Cannot add more.\n";
        return;
    }

    cin.ignore();
    cout << "Enter task description: ";
    getline(cin, tasks[taskCount].description);
    tasks[taskCount].isDone = false;
    taskCount++;
    cout << "Task added successfully!\n";
    saveTasks();
}

void viewTasks()
{
    if(taskCount == 0)
    {
        cout << "No tasks available.\n";
        return;
    }

    cout << "\n---------------------- To-Do Tasks ---------------------\n";
    for(int i=0; i<taskCount; i++)
    {
        cout << i+1 << ". " << tasks[i].description
             << " [" << (tasks[i].isDone ? "Done" : "Pending") << "]\n";
    }
    cout << "\n---------------------- To-Do Tasks ---------------------\n";
}


void markDone()
{
    if(taskCount ==0 )
    {
        cout << "No tasks to mark!\n";
        return;
    }

    int index;
    cout << "Enter task number to mark as done: ";
    cin >> index;

    if (index < 1 || index > taskCount) 
    {
        cout << "Invalid task number!\n";
        return;
    }

    tasks[index -1].isDone = true;
    cout << "Tasks marked as done!\n";
    saveTasks();
}


void deleteTask()
{
    if (taskCount == 0) 
    {
        cout << "No tasks to delete!\n";
        return;
    }

    int index;
    cout << "Enter task number to delete: ";
    cin >> index;

    if (index < 1 || index > taskCount) 
    {
        cout << "Invalid task number!\n";
        return;
    }

    for(int i=index-1; i<taskCount-1; i++)
    {
        tasks[i] = tasks[i+1];
    }
    taskCount--;
    cout << "Task deleted successfully!\n";
    saveTasks();
}

void saveTasks()
{
    ofstream out("tasks.txt");

    if (!out) 
    {
        cout << "Error saving tasks!\n";
        return;
    }

    for(int i=0; i<taskCount; i++)
    {
        out << tasks[i].description << "\n";
        out << tasks[i].isDone << "\n";
    }
    out.close();
}


void loadTasks()
{
    ifstream in("tasks.txt");
    if(!in)
    {
        cout << "No previous tasks found.\n";
        return;
    }

    string desc;
    bool done;
    taskCount = 0;

    while(getline(in, desc))
    {
        if (!(in >> done)) 
        {
            break;
        }
        in.ignore(1, '\n');
        tasks[taskCount].description = desc;
        tasks[taskCount].isDone = done;
        taskCount++;
        if(taskCount >= MAX_TASKS)
        {
            break;
        }
    }
    in.close();
    cout << "Loaded " << taskCount << " task(s) from file.\n";
}
