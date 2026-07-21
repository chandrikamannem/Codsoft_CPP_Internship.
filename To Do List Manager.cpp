#include <iostream>
#include <vector>
#include <string>

using namespace std;

struct Task
{
    string name;
    bool completed;
};

int main()
{
    vector<Task> tasks;
    int choice;

    do
    {
        cout << "\n===== TO-DO LIST MANAGER =====\n";
        cout << "1. Add Task\n";
        cout << "2. View Tasks\n";
        cout << "3. Mark Task as Completed\n";
        cout << "4. Remove Task\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore();

        switch(choice)
        {
            case 1:
            {
                Task t;
                cout << "Enter task: ";
                getline(cin, t.name);
                t.completed = false;
                tasks.push_back(t);
                cout << "Task added successfully!\n";
                break;
            }

            case 2:
            {
                if(tasks.empty())
                {
                    cout << "No tasks available.\n";
                }
                else
                {
                    cout << "\n----- Task List -----\n";
                    for(int i = 0; i < tasks.size(); i++)
                    {
                        cout << i + 1 << ". " << tasks[i].name
                             << " [" << (tasks[i].completed ? "Completed" : "Pending") << "]\n";
                    }
                }
                break;
            }

            case 3:
            {
                int taskNo;
                if(tasks.empty())
                {
                    cout << "No tasks available.\n";
                }
                else
                {
                    cout << "Enter task number to mark as completed: ";
                    cin >> taskNo;

                    if(taskNo >= 1 && taskNo <= tasks.size())
                    {
                        tasks[taskNo - 1].completed = true;
                        cout << "Task marked as completed.\n";
                    }
                    else
                    {
                        cout << "Invalid task number.\n";
                    }
                }
                break;
            }

            case 4:
            {
                int taskNo;
                if(tasks.empty())
                {
                    cout << "No tasks available.\n";
                }
                else
                {
                    cout << "Enter task number to remove: ";
                    cin >> taskNo;

                    if(taskNo >= 1 && taskNo <= tasks.size())
                    {
                        tasks.erase(tasks.begin() + taskNo - 1);
                        cout << "Task removed successfully.\n";
                    }
                    else
                    {
                        cout << "Invalid task number.\n";
                    }
                }
                break;
            }

            case 5:
                cout << "Thank you for using To-Do List Manager!\n";
                break;

            default:
                cout << "Invalid choice! Please try again.\n";
        }

    } while(choice != 5);

    return 0;
}
