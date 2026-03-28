#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Define category enum */
typedef enum Category {
    it_department = 1,
    accounting_department,
    marketing_department,
    hr_department,
    sales_department
} Category;

/* Define priority enum */
typedef enum Priority {
    HIGH = 1,
    MEDIUM,
    LOW
} Priority;

/* Define task using struct */
typedef struct Task {
    char name[50];
    Category category;
    Priority priority;
    char deadline[50];
    int status;  // 1: Complete, 2: Not Complete
} Task;

typedef struct Users{
    char usersID[50];
}Users;

/* Function prototypes*/
void saveFile(Task *tasks, Users *user);
int checkUserExist(Users user[], int numUsers, const char *tempUsers);
int UserRegister(Users **user, int *numUsers);
int UsersLogin(Users user[], int numUsers);

int addTask(Task *tasks, int numUsers);
int editTask(Task *tasks, int numUsers);
int deleteTask(Task *task, int numUsers);
void viewTasks(Task *tasks);

/*Function to return string representation of category*/
const char* returnCategory(enum Category category){
    switch (category){
    case it_department:
        return "IT";
        break;
    case accounting_department:
        return "Accounting";
        break;
    case marketing_department:
        return "Marketing";
        break;
    case hr_department:
        return "HR";
        break;
    case sales_department:
        return "Sales";
        break;
    default:
        return "Invalid Input";
        break;
    }
}

/*Function to return string representation of priority*/
const char* returnPriority(enum Priority priority){
    switch(priority){
    case HIGH:
        return "High";
        break;
    case MEDIUM:
        return "Medium";
        break;
    case LOW:
        return "Low";
        break;
    }
}

/* Main function*/
int main() {
    int taskCount = 0;
    Task* tasks;
    tasks = malloc (taskCount * sizeof(int));

    int numUsers = 0;
    Users * user;
    user = malloc(numUsers * sizeof(int));

    printf("\n");
    printf("*******************************************\n");
    printf("Welcome to CFIM's Task Management System!\n");
    printf("*******************************************\n");
    printf("\n");

    char select = 'Y';

   while (1)
    {
        printf("Are you a new users?(Y/N): ");
        scanf(" %c", &select);

        if (select == 'Y' || select == 'y')
        {
            UserRegister(&user, &numUsers);
            saveFile(tasks, user);
            break;
        }else if(select == 'N' || select == 'n'){
            int loginSuccess = UsersLogin(user, numUsers);
            if (loginSuccess){
                break;
            }
        }else {
            printf("Invalid input. Plaese enter Y and N.\n");
        }
    }

    int choice;

    while (1) {
        printf("\n--- Task Management System (CFIM) ---\n");
        printf("1. Add Task\n");
        printf("2. Edit Task\n");
        printf("3. Delete Task\n");
        printf("4. Display Tasks\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
        case 1:
            addTask(tasks, numUsers);
            break;;
        case 2:
            editTask(tasks, numUsers);
            break;
        case 3:
            deleteTask(tasks, numUsers);
            break;
        case 4:
            viewTasks(tasks);
            break;
        case 5:
            printf("Have a good Day! Remember do your own task ~\n");
            saveFile(tasks, user);
            free(tasks);    
            free(user);
            return 0;
        default:
            printf("Invalid choice! Please try again.\n");
        }
    }

    
}

int taskCount;
int userCount;
Users *user;

// Function to save tasks to a file
void saveFile(Task *tasks, Users *user) {
    FILE *file = fopen("task.txt", "w");
    if(file == NULL){
        printf("Error opening file !\n");
        return;
    }

    for(int i = 0; i < taskCount; i++) {
        fprintf(file, "Users ID: %s\n",user[i].usersID);
        fprintf(file, "\n");
        fprintf(file, "Name: %s\n", tasks[i].name);
        fprintf(file, "Category: %s\n", returnCategory(tasks[i].category));
        fprintf(file, "Priority: %s\n", returnPriority(tasks[i].priority));
        fprintf(file, "Deadline: %s\n", tasks[i].deadline);
        fprintf(file, "Status: %s\n\n", tasks[i].status == 1 ? "Complete" : "Not Complete");
    }

    fclose(file);
    printf("Tasks saved to file successfully!\n");
}

/*Check to see if you have the same Users ID*/
int checkUserExist(Users user[], int numUsers, const char *tempUsers){
    for (int i = 0; i < numUsers; i++)
    {
        if (strcmp(tempUsers, user[i].usersID) == 0)
        {
            return 1;//error
        }
    }
    return 0;
}

/*Getting new users to sign up for an account*/
int UserRegister(Users **user, int *numUsers){
    char tempUsers[50];

    printf("Create new account\n");
    
    while(1){
        printf("Enter User ID: ");
        scanf("%s", tempUsers);
        int UserExist = checkUserExist(*user, *numUsers, tempUsers);

        if (UserExist == 1)
        {
            printf("Error: Users ID already exists.\n");
            continue;
        }

        strcpy((*user)[*numUsers].usersID, tempUsers);
        (*numUsers)++;
        printf("Register Successfully.\n");
        break;
    }
    return 1;
}

/*Let users with accounts log in to program*/
int UsersLogin(Users *user, int numUsers){
    char tempUsers[50];

    while (1)
    {
        printf("Enter Users ID: ");
        scanf("%s",tempUsers);
        int usersExist = checkUserExist(user, numUsers, tempUsers);
        if(!usersExist){
            printf("Error: Users ID does not exist. Please Register\n");
            break;
        }
        printf("Login Successfully. Welcome back, %s", tempUsers);
        while (getchar() != '\n');
        return 1;
    }
}

/*Function to add a task*/
int addTask(Task *tasks, int numUsers) {
    Task *newTask = &tasks[taskCount];
    int input;

    printf("Enter your task name: ");
    scanf("%s", newTask->name);

    // Input and validate category
    while (1) {
        printf("Enter category of department (1 for IT, 2 for Accounting, 3 for Marketing, 4 for HR, 5 for Sales): ");
        if (scanf("%d", &input) == 1 && input >= 1 && input <= 5) {
            newTask->category = (Category)input;
            break;
        }
        printf("Invalid input! Please enter a number between 1 and 5.\n");
        while (getchar() != '\n');
    }

    // Input and validate priority
    while (1) {
        printf("Enter priority (1: High, 2: Medium, 3: Low): ");
        if (scanf("%d", &input) == 1 && input >= 1 && input <= 3) {
            newTask->priority = (Priority)input;
            break;
        }
        printf("Invalid input! Please enter a number between 1 and 3.\n");
        while (getchar() != '\n'); 
    }

    // Input deadline
    printf("Enter deadline (YYYY-MM-DD): ");
    scanf("%s", newTask->deadline);

    // Default status is incomplete"
    newTask->status = 2;
    taskCount++;

    printf("Task added successfully!\n");

    saveFile(tasks, user);
}

/* Function to edit a task*/
int editTask(Task *tasks, int numUsers) {
    char taskName[50];
    int input;

    printf("Enter the name of the task to edit: ");
    scanf("%s", taskName);

    for (int i = 0; i < taskCount; i++) {
        if (strcmp(tasks[i].name, taskName) == 0) {
            printf("Enter new status (1: Complete, 2: Incomplete): ");
            scanf("%d", &tasks[i].status);

            // Input and validate category
            while (1) {
                printf("Enter new category (1 for IT, 2 for Accounting, 3 for Marketing, 4 for HR, 5 for Sales): ");
                if (scanf("%d", &input) == 1 && input >= 1 && input <= 5) {
                    tasks[i].category = (Category)input;
                    break;
                }
                printf("Invalid input! Please enter a number between 1 and 5.\n");
                while (getchar() != '\n'); // Clear buffer
            }

            // Input and validate priority
            while (1) {
                printf("Enter new priority (1: High, 2: Medium, 3: Low): ");
                if (scanf("%d", &input) == 1 && input >= 1 && input <= 3) {
                    tasks[i].priority = (Priority)input;
                    break;
                }
                printf("Invalid input! Please enter a number between 1 and 3.\n");
                while (getchar() != '\n'); // Clear buffer
            }

            // Input new deadline
            printf("Enter new deadline (YYYY-MM-DD): ");
            scanf("%s", tasks[i].deadline);
            
            printf("Task updated successfully!\n");

            // Save tasks to file
            saveFile(tasks, user);

            return 1;
        }
    }

    printf("Task not found.\n");
    return 0;
}

/*Using this function allows them to delete the desired task.*/
int deleteTask(Task *tasks, int numUsers){
    char taskName[50];
    int found = 0; //doesnt find the task

    printf("Enter the Task to Delete: ");
    scanf("%s", taskName);
    for (int i = 0; i < taskCount; i++)
    {
        if(strcmp(tasks[i].name, taskName) == 0){
            found = 1;

            tasks[i] = tasks[taskCount - 1]; //when we delete the task, Tasks after this one are shifted forward.
            taskCount --;

            printf("Task deleted successfully.\n", taskName);
            return 1;
        }

        if (!found){
            printf("Error: %s not found.\n", taskName);
        }
        
    }
    saveFile(tasks, user);

    return 0;
}

/* Function to display tasks */
void viewTasks(Task *tasks) {
    if (taskCount == 0) {
        printf("No tasks available.\n");
        return;
    }

    printf("\n--- Task List ---\n");
    for (int i = 0; i < taskCount; i++) {
        printf("Task %d:\n", i + 1);
        printf("Name: %s\n", tasks[i].name);
        printf("Category: %s\n", returnCategory(tasks[i].category));
        printf("Priority: %s\n", returnPriority(tasks[i].priority));
        printf("Deadline: %s\n", tasks[i].deadline);
        printf("Status: %s\n", tasks[i].status == 1 ? "Complete" : "Not Complete");
        printf("\n");
    }

    saveFile(tasks, user);

}


