#include "raylib.h"
#include <string>
#include <cstring>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <ctime>
#include <vector>
struct EMPLOYEE {
    int ID = 0;
    std::string name = "";
    std::string department = "";
    std::string designation = "";
    float salary = 0;
    std::string joining_date = "";
    std::string skills = "";
    bool availability = true;
    std::string availability_string = "Yes";
    int leaves = 0;
};
struct Financial_matters {
    std::string year = "";
    int expenses[12] = { 0,0,0,0,0,0,0,0,0,0,0,0 };
    int total_income[12] = { 0,0,0,0,0,0,0,0,0,0,0,0 };
    int net_income[12] = { 0,0,0,0,0,0,0,0,0,0,0,0 };
};
struct Project {
    int projectId = 0;
    std::string title = "";
    float budget = 0;
    std::string startDate = "";
    std::string endDate = "";
    std::string status = "";
    std::vector<int> assignedEmployeeIds;
};

std::vector<EMPLOYEE> employees;
std::vector<Project> projects;
std::vector<int> busy_employees;
std::vector<int> valid_employee_ids;
std::vector<Financial_matters> finances;

void display_manager_options(void);
void employee_management_module(void);
void project_management_module(void);
void save_employee_data(void);
void load_employee_data(void);
void add_employee(void);
void update_employee_checker(void);
void update_employee(int);
void delete_employee_id_input(void);
void delete_employee(int);
int binary_search(int);
void sort_employees(void);
void display_employee_checker();
int check_if_employee_already_exists(int, EMPLOYEE);
void availability_string_initializer(EMPLOYEE&);
void display_specific_employee_data(int);
void display_all_employees_data(void);
bool is_valid_date(const std::string&);

void add_project(void);
void load_project_data(void);
void sort_projects(void);
int binary_search_project(int);
void save_project_data(void);
void search_employee_and_assign_employee(int, int, Project, int);
void assign_project_to_employee_checker(int);
void project_id_checker(void);
void project_id_checker_for_display(void);
bool check_employee_id_existence(const std::string*, std::string*, int, const std::string&, int);
void display_specific_project_data(int);
int dateToNumber(const std::string&);
void busy_employees_text_generator(void);
void read_busy_employees_from_file(void);
std::string get_current_date(void);

void finance_management_module(void);
void add_income(std::string);
void add_expense(std::string, int[12]);
void generate_financial_report();
void input_financial_data();
int binary_search_finances(int);
void Add_financial_summary();
void sort_finances();
void financial_id_checker_for_display(void);
void display_finacial_summary(int);
int corporate_tax_calculator(int);
void draw_bar_chart(int, int, int, int, int);
void draw_monthly_bar_chart(int [], int [], int []);

int main(void) {
    InitWindow(2000, 900, "Company Management System");
    SetTargetFPS(10);

    input_financial_data();
    read_busy_employees_from_file();
    load_project_data();
    load_employee_data();
    display_manager_options();
}
void display_manager_options(void) {
  
    Rectangle button1 = { 100, 170, 400, 50 };
    Rectangle button2 = { 100, 230, 400, 50 };
    Rectangle button3 = { 100, 290, 400, 50 };

    bool shouldExit = false;

    while (!WindowShouldClose() && !shouldExit) {
        Vector2 mouse = GetMousePosition();
        bool button1Active = false;
        bool button2Active = false;
        bool button3Active = false;

        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            if (CheckCollisionPointRec(mouse, button1)) {
                button1Active = true;
                CloseWindow(); // Close current window
                employee_management_module(); // Open employee management window
                shouldExit = true; // Indicate exit

            }
            if (CheckCollisionPointRec(mouse, button2)) {
                button2Active = true;
                CloseWindow(); // Close current window
                project_management_module(); // Open project management window
                shouldExit = true; // Indicate exit
            }
            if (CheckCollisionPointRec(mouse, button3)) {
                button3Active = true;
                CloseWindow(); // Close current window
                finance_management_module(); // Open finance management window
                shouldExit = true; // Indicate exit
            }
        }

        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawText("Welcome Sir!", 120, 100, 50, BLACK);
        DrawRectangleRec(button1, button1Active ? DARKGRAY : LIGHTGRAY);
        DrawText("EMPLOYEE MANAGEMENT MODULE", button1.x + 10, button1.y + 15, 20, BLACK);
        DrawRectangleRec(button2, button2Active ? DARKGRAY : LIGHTGRAY);
        DrawText("PROJECT MANAGEMENT MODULE", button2.x + 10, button2.y + 15, 20, BLACK);
        DrawRectangleRec(button3, button3Active ? DARKGRAY : LIGHTGRAY);
        DrawText("FINANCE MANAGEMENT MODULE", button3.x + 10, button3.y + 15, 20, BLACK);
        EndDrawing();
    }
    if (shouldExit) {
        CloseWindow(); // Close the window and end the program
    }
}
void employee_management_module(void) {

    Rectangle button_1 = { 700, 170, 400, 50 };
    Rectangle button_2 = { 700, 230, 400, 50 };
    Rectangle button_3 = { 700, 290, 400, 50 };
    Rectangle button_4 = { 700, 350, 400, 50 };
    Rectangle button_5 = { 700, 410, 400, 50 };
    Rectangle button_7 = { 700, 470, 400, 50 };
 
    bool should_exit = false;
    while (!WindowShouldClose() && !should_exit) {
        Vector2 mouse_position = GetMousePosition();

        bool button_1_Active = false;
        bool button_2_Active = false;
        bool button_3_Active = false;
        bool button_4_Active = false;
        bool button_5_active = false;
        bool button_7_Active = false;
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            if (CheckCollisionPointRec(mouse_position, button_1)) {
                button_1_Active = true;
                CloseWindow();
                add_employee();
                should_exit = true;
                break;
            }
            if (CheckCollisionPointRec(mouse_position, button_2)) {
                button_2_Active = true;
                CloseWindow();
                update_employee_checker();
                should_exit = true;
                break;
            }
            if (CheckCollisionPointRec(mouse_position, button_3)) {
                button_3_Active = true;
                CloseWindow();
                delete_employee_id_input();
                should_exit = true;
                break;
            }
            if (CheckCollisionPointRec(mouse_position, button_4)) {
                button_4_Active = true;
                CloseWindow();
                display_all_employees_data();
                should_exit = true;
                break;
            }
            if (CheckCollisionPointRec(mouse_position, button_5)) {
                button_5_active = true;
                CloseWindow();
                display_employee_checker();
                should_exit = true;
                break;
            }
            if (CheckCollisionPointRec(mouse_position, button_7)) {
                button_7_Active = true;
                CloseWindow();
                display_manager_options();
                should_exit = true;
                break;
            }
        }
        BeginDrawing();
        DrawText("Welcome Sir!", 720, 100, 50, BLACK);
        ClearBackground(RAYWHITE);
        DrawRectangleRec(button_1, button_1_Active ? DARKGRAY : LIGHTGRAY);
        DrawText("Add new employee", button_1.x + 10, button_1.y + 15, 20, BLACK);
        DrawRectangleRec(button_2, button_2_Active ? DARKGRAY : LIGHTGRAY);
        DrawText("Update existing employee data", button_2.x + 10, button_2.y + 15, 20, BLACK);
        DrawRectangleRec(button_3, button_3_Active ? DARKGRAY : LIGHTGRAY);
        DrawText("Delete employee", button_3.x + 10, button_3.y + 15, 20, BLACK);
        DrawRectangleRec(button_4, button_4_Active ? DARKGRAY : LIGHTGRAY);
        DrawText("Show record of all employees", button_4.x + 10, button_4.y + 15, 20, BLACK);
        DrawRectangleRec(button_5, button_5_active ? DARKGRAY : LIGHTGRAY);
        DrawText("Display data of a employee", button_5.x + 10, button_5.y + 15, 20, BLACK);
        DrawRectangleRec(button_7, button_7_Active ? DARKGRAY : LIGHTGRAY);
        DrawText("BACK", button_7.x + 10, button_7.y + 15, 20, BLACK);
        EndDrawing();
    }
    if (should_exit) {
        CloseWindow();
    }
}
void project_management_module(void) {

    Rectangle button_1 = { 700, 170, 400, 50 };
    Rectangle button_2 = { 700, 230, 400, 50 };
    Rectangle button_3 = { 700, 290, 400, 50 };
    Rectangle button_7 = { 700, 350 ,400, 50 };

    bool should_exit = false;
    while (!WindowShouldClose() && !should_exit) {
        Vector2 mouse_position = GetMousePosition();

        bool button_1_Active = false;
        bool button_2_Active = false;
        bool button_3_Active = false;
        bool button_7_Active = false;

        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            if (CheckCollisionPointRec(mouse_position, button_1)) {
                button_1_Active = true;
                CloseWindow();
                add_project();
                should_exit = true;
                break;
            }
            if (CheckCollisionPointRec(mouse_position, button_2)) {
                button_2_Active = true;
                CloseWindow();
                project_id_checker();
                should_exit = true;
                break;
            }
            if (CheckCollisionPointRec(mouse_position, button_3)) {
                button_3_Active = true;
                CloseWindow();
                project_id_checker_for_display();
                should_exit = true;
                break;
            }
            if (CheckCollisionPointRec(mouse_position, button_7)) {
                button_7_Active = true;
                CloseWindow();
                display_manager_options();
                should_exit = true;
                break;
            }
        }
        BeginDrawing();
        DrawText("Welcome Sir!", 720, 100, 50, BLACK);
        ClearBackground(RAYWHITE);
        DrawRectangleRec(button_1, button_1_Active ? DARKGRAY : LIGHTGRAY);
        DrawText("Create new project", button_1.x + 10, button_1.y + 15, 20, BLACK);
        DrawRectangleRec(button_2, button_2_Active ? DARKGRAY : LIGHTGRAY);
        DrawText("Assign project to employees", button_2.x + 10, button_2.y + 15, 20, BLACK);
        DrawRectangleRec(button_3, button_3_Active ? DARKGRAY : LIGHTGRAY);
        DrawText("View Project details", button_3.x + 10, button_3.y + 15, 20, BLACK);
        DrawRectangleRec(button_7, button_7_Active ? DARKGRAY : LIGHTGRAY);
        DrawText("BACK", button_7.x + 10, button_7.y + 15, 20, BLACK);
        EndDrawing();
    }
    if (should_exit) {
        CloseWindow();
    }
}

void add_employee(void) {
   
    std::string employee_id_string, employee_name, employee_salary, employee_department,
        employee_designation, employee_joining_date, employee_skills;

    Rectangle button_7 = { 0, 0, 400, 50 };

    bool employee_id_string_Active = false, employee_name_Active = false, employee_department_Active = false,
        employee_designation_Active = false, employee_joining_date_Active = false, employee_skills_Active = false,
        employee_salary_Active = false, button_7_active = false;

    EMPLOYEE temp;

    bool all_inputs_valid = false;
    bool should_exit = false;
    while (!WindowShouldClose() && !should_exit) {
        Vector2 mouse = GetMousePosition();
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            employee_id_string_Active = (mouse.x > 600 && mouse.x < 1000 && mouse.y > 150 && mouse.y < 200);
            employee_name_Active = (mouse.x > 600 && mouse.x < 1000 && mouse.y > 250 && mouse.y < 300);
            employee_department_Active = (mouse.x > 600 && mouse.x < 1000 && mouse.y > 350 && mouse.y < 400);
            employee_designation_Active = (mouse.x > 600 && mouse.x < 1000 && mouse.y > 450 && mouse.y < 500);
            employee_joining_date_Active = (mouse.x > 600 && mouse.x < 1000 && mouse.y > 550 && mouse.y < 600);
            employee_skills_Active = (mouse.x > 600 && mouse.x < 1000 && mouse.y > 650 && mouse.y < 700);
            employee_salary_Active = (mouse.x > 600 && mouse.x < 1000 && mouse.y > 750 && mouse.y < 800);
            button_7_active = CheckCollisionPointRec(mouse, button_7);
        }
        if (button_7_active) {
            CloseWindow();
            employee_management_module();
            should_exit = true;
            break;
        }

        // Handle text input
        if (employee_id_string_Active || employee_name_Active || employee_department_Active || employee_designation_Active ||
            employee_joining_date_Active || employee_skills_Active || employee_salary_Active) {
            int key = GetCharPressed();
            while (key > 0) {
                if (key >= 32 && key <= 125) {
                    if (employee_id_string_Active && employee_id_string.length() < 63) {
                        employee_id_string += static_cast<char>(key);
                    }
                    if (employee_name_Active && employee_name.length() < 63) {
                        employee_name += static_cast<char>(key);
                    }
                    if (employee_department_Active && employee_department.length() < 63) {
                        employee_department += static_cast<char>(key);
                    }
                    if (employee_designation_Active && employee_designation.length() < 63) {
                        employee_designation += static_cast<char>(key);
                    }
                    if (employee_joining_date_Active && employee_joining_date.length() < 63) {
                        employee_joining_date += static_cast<char>(key);
                    }
                    if (employee_skills_Active && employee_skills.length() < 63) {
                        employee_skills += static_cast<char>(key);
                    }
                    if (employee_salary_Active && employee_salary.length() < 63) {
                        employee_salary += static_cast<char>(key);
                    }
                }
                key = GetCharPressed();
            }
            // Handle backspace key
            if (IsKeyPressed(KEY_BACKSPACE)) {
                if (employee_id_string_Active && !employee_id_string.empty()) {
                    employee_id_string.pop_back();
                }
                if (employee_name_Active && !employee_name.empty()) {
                    employee_name.pop_back();
                }
                if (employee_department_Active && !employee_department.empty()) {
                    employee_department.pop_back();
                }
                if (employee_designation_Active && !employee_designation.empty()) {
                    employee_designation.pop_back();
                }
                if (employee_joining_date_Active && !employee_joining_date.empty()) {
                    employee_joining_date.pop_back();
                }
                if (employee_skills_Active && !employee_skills.empty()) {
                    employee_skills.pop_back();
                }
                if (employee_salary_Active && !employee_salary.empty()) {
                    employee_salary.pop_back();
                }
            }
        }

        // Check for save button click
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && (mouse.x > 600 && mouse.x < 1000 && mouse.y > 850 && mouse.y < 900)) {
            // Validate inputs before proceeding
            all_inputs_valid = true;

            try {
                temp.ID = std::stoi(employee_id_string); // Try to convert the ID to an integer
            }
            catch (const std::invalid_argument& e) {
                temp.ID = 0;
                all_inputs_valid = false;
                DrawText("Invalid ID entered. Please enter a valid ID.", 1500, 300, 20, RED);
            }

            temp.name = employee_name;
            temp.department = employee_department;
            temp.designation = employee_designation;
            try {
                temp.salary = std::stod(employee_salary);  // Try to convert salary to a double
            }
            catch (const std::invalid_argument& e) {
                all_inputs_valid = false;
                DrawText("Invalid Salary entered. Please enter a valid salary.", 1500, 350, 20, RED);
            }

            // Validate the joining date
            if (!is_valid_date(employee_joining_date)) {
                all_inputs_valid = false;
                DrawText("Invalid date format. Use DD/MM/YYYY.", 1500, 400, 20, RED);
            }
            else {
                temp.joining_date = employee_joining_date;
            }

            temp.skills = employee_skills;

            // Check if employee with this ID already exists in the vector
            bool employee_exists = false;
            for (const auto& emp : employees) {
                if (emp.ID == temp.ID) {
                    employee_exists = true;
                    break;
                }
            }

            // Only add the employee if all inputs are valid
            if (!employee_exists && all_inputs_valid) {
                employees.push_back(temp); // Add employee to the vector
                DrawText("Employee added successfully!", 1500, 400, 20, DARKGREEN);
                // Clear input fields after successful addition
                employee_id_string = "";
                employee_name = "";
                employee_salary = "";
                employee_department = "";
                employee_designation = "";
                employee_joining_date = "";
                employee_skills = "";
            }
            else if (employee_exists) {
                DrawText("Employee corresponding to this ID already exists", 1500, 400, 20, RED);
            }
            else {
                DrawText("Please correct the invalid entries.", 1500, 400, 20, RED);
            }
        }

        BeginDrawing();
        ClearBackground(RAYWHITE);

        DrawText("ADD EMPLOYEE", 650, 50, 20, DARKGRAY);

        // Draw input fields
        DrawRectangle(600, 150, 400, 50, LIGHTGRAY);
        DrawText(employee_id_string.c_str(), 610, 160, 20, BLACK);
        DrawText("ID", 300, 160, 20, DARKGRAY);

        DrawRectangle(600, 250, 400, 50, LIGHTGRAY);
        DrawText(employee_name.c_str(), 610, 260, 20, BLACK);
        DrawText("Name", 300, 260, 20, DARKGRAY);

        DrawRectangle(600, 350, 400, 50, LIGHTGRAY);
        DrawText(employee_department.c_str(), 610, 360, 20, BLACK);
        DrawText("Department", 300, 360, 20, DARKGRAY);

        DrawRectangle(600, 450, 400, 50, LIGHTGRAY);
        DrawText(employee_designation.c_str(), 610, 460, 20, BLACK);
        DrawText("Designation", 300, 460, 20, DARKGRAY);

        DrawRectangle(600, 550, 400, 50, LIGHTGRAY);
        DrawText(employee_joining_date.c_str(), 610, 560, 20, BLACK);
        DrawText("Joining Date (DD/MM/YYYY)", 300, 560, 20, DARKGRAY);

        DrawRectangle(600, 650, 400, 50, LIGHTGRAY);
        DrawText(employee_skills.c_str(), 610, 660, 20, BLACK);
        DrawText("Skills", 300, 660, 20, DARKGRAY);

        DrawRectangle(600, 750, 400, 50, LIGHTGRAY);
        DrawText(employee_salary.c_str(), 610, 760, 20, BLACK);
        DrawText("Salary (PKR)", 300, 760, 20, DARKGRAY);

        DrawRectangle(600, 850, 400, 50, DARKGRAY);
        DrawText("Save", 800, 860, 20, WHITE);

        DrawRectangleRec(button_7, button_7_active ? DARKGRAY : LIGHTGRAY);
        DrawText("BACK", button_7.x + 10, button_7.y + 15, 20, BLACK);

        EndDrawing();
    }
    if (should_exit) {
        save_employee_data();
        CloseWindow();
    }
}
bool is_valid_date(const std::string& date) {
    if (date.length() != 10) return false;

    // Check if the date format is DD/MM/YYYY
    if (date[2] != '/' || date[5] != '/') return false;

    int day, month, year;
    std::stringstream ss(date);
    char slash;

    ss >> day >> slash >> month >> slash >> year;

    // Check if the day, month, and year are valid numbers
    if (ss.fail()) return false;

    // Check month range
    if (month < 1 || month > 12) return false;

    // Check if the day is valid for the given month and year
    int days_in_month = 31;

    if (month == 4 || month == 6 || month == 9 || month == 11) {
        days_in_month = 30;
    }
    else if (month == 2) {
        // Check for leap year for February
        if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0)) {
            days_in_month = 29;
        }
        else {
            days_in_month = 28;
        }
    }

    if (day < 1 || day > days_in_month)
        return false;

    return true;
}

void availability_string_initializer(EMPLOYEE& temp) {
    if (temp.availability) {
        temp.availability_string = "Yes";
    }
    else {
        temp.availability_string = "No";
    }
    return;
}
int check_if_employee_already_exists(int id, EMPLOYEE temp) {
    int employee_index = binary_search(id);
    if (employee_index == -1) {
        availability_string_initializer(temp);
        employees.push_back(temp);
    }
    return employee_index;
}
void load_employee_data(void) {
    std::ifstream FILE("EMPLOYEE DETAILS.txt");
    if (!FILE) {
        std::cerr << "Error opening file" << std::endl;
        return;
    }
    std::string line;
    while (std::getline(FILE, line)) {
        std::istringstream ss(line);
        EMPLOYEE temp;
        std::string id;
        std::string salary_string;
        std::string availability;
        std::getline(ss, id, '|');
        std::getline(ss, temp.name, '|');
        std::getline(ss, temp.department, '|');
        std::getline(ss, temp.designation, '|');
        std::getline(ss, salary_string, '|');
        temp.salary = std::stod(salary_string);
        std::getline(ss, temp.joining_date, '|');
        std::getline(ss, temp.skills, '|');
        std::getline(ss, availability, '|');
        temp.ID = std::stoi(id);
        employees.push_back(temp);
    }
    FILE.close();
}

void save_employee_data(void) {
    std::ofstream FILE;
    FILE.open("EMPLOYEE DETAILS.txt");
    if (!FILE) {
        std::cerr << "Error opening file" << std::endl;
        return;
    }
    for (int i = 0; i < employees.size(); ++i) {
        EMPLOYEE employee = employees[i];
        FILE << employee.ID << "|"
            << employee.name << "|"
            << employee.department << "|"
            << employee.designation << "|"
            << employee.salary << "|"
            << employee.joining_date << "|"
            << employee.skills << "|"
            << employee.availability << "|"
            << std::endl;
    }
    load_employee_data();
    FILE.close();
}
void update_employee_checker(void) {
    Rectangle button_back = { 0, 0, 400, 50 };
    Rectangle button_user_input = { 100, 100, 400, 50 };
    std::string employee_id = "";
    bool employee_id_input_active = false;
    bool should_exit = false;
    bool is_data_valid = true;
    while (!WindowShouldClose() && !should_exit) {
        bool button_back_active = false;
        Vector2 mouse = GetMousePosition();
        // Handle button clicks
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            employee_id_input_active = (mouse.x > button_user_input.x && mouse.x < button_user_input.x + button_user_input.width) &&
                (mouse.y > button_user_input.y && mouse.y < button_user_input.y + button_user_input.height);
            button_back_active = (mouse.x > button_back.x && mouse.x < button_back.x + button_back.width) &&
                (mouse.y > button_back.y && mouse.y < button_back.y + button_back.height);
        }
        // Handle text input
        if (employee_id_input_active) {
            int key = GetCharPressed();
            while (key > 0) {
                if (key >= 32 && key <= 125) {
                    if (employee_id_input_active && employee_id.length() < 63) {
                        employee_id += static_cast<char>(key);
                    }
                }
                key = GetCharPressed();
            }
            if (IsKeyPressed(KEY_BACKSPACE) && !employee_id.empty()) {
                employee_id.pop_back();
            }
        }
        // Handle Enter key to validate the input
        if (employee_id_input_active && IsKeyPressed(KEY_ENTER)) {
            try {
                // Try to convert the employee_id to an integer
                int employee_id_int = std::stoi(employee_id);

                // Perform binary search to find the employee index
                int index_of_employee = binary_search(employee_id_int);
                if (index_of_employee == -1) {
                    DrawText("Employee does not exist in our database", 100, 200, 20, BLACK);
                }
                else {
                    update_employee(index_of_employee);
                }
            }
            catch (const std::invalid_argument& e) {
                // If conversion fails, show an error message and ask the user to try again
                DrawText("Invalid input. Please enter a valid Employee ID (numeric only).", 100, 200, 20, RED);
                employee_id = "";  // Reset input for the user to try again
            }
            catch (const std::out_of_range& e) {
                // If the input number is too large, handle it gracefully
                DrawText("Employee ID too large. Please enter a smaller number.", 100, 200, 20, RED);
                employee_id = "";  // Reset input for the user to try again
            }
        }

        // Drawing section
        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawText("Enter Employee ID:", 100, 70, 20, DARKGRAY);

        // Draw the input button and the entered text
        DrawRectangleRec(button_user_input, employee_id_input_active ? DARKGRAY : LIGHTGRAY);
        DrawText(employee_id.c_str(), button_user_input.x + 10, button_user_input.y + 10, 20, BLACK);

        // Draw the back button
        DrawRectangleRec(button_back, button_back_active ? DARKGRAY : LIGHTGRAY);
        DrawText("BACK", button_back.x + 10, button_back.y + 15, 20, BLACK);

        // Handle BACK button click
        if (CheckCollisionPointRec(mouse, button_back) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            CloseWindow();
            employee_management_module();
            should_exit = true;
            break;
        }
        EndDrawing();
    }
    if (should_exit) {
        CloseWindow();
    }
}
void update_employee(int index) {
    Rectangle button_7 = { 0, 0, 400, 50 };

    bool employee_id_string_Active = false, employee_name_Active = false, employee_department_Active = false,
        employee_designation_Active = false, employee_joining_date_Active = false, employee_skills_Active = false,
        employee_salary_Active = false, button_7_active = false;

    EMPLOYEE temp = employees[index]; // Load the existing employee data into temp
    std::string employee_id_string = std::to_string(temp.ID), employee_name = temp.name , employee_salary = std::to_string(temp.salary), employee_department = temp.department,
        employee_designation = temp.designation, employee_joining_date = temp.joining_date, employee_skills = temp.skills;

    bool is_data_valid = true; // To track if all inputs are valid
    bool should_exit = false;
    while (!WindowShouldClose() && !should_exit) {
        Vector2 mouse = GetMousePosition();
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            employee_id_string_Active = (mouse.x > 600 && mouse.x < 1000 && mouse.y > 150 && mouse.y < 200);
            employee_name_Active = (mouse.x > 600 && mouse.x < 1000 && mouse.y > 250 && mouse.y < 300);
            employee_department_Active = (mouse.x > 600 && mouse.x < 1000 && mouse.y > 350 && mouse.y < 400);
            employee_designation_Active = (mouse.x > 600 && mouse.x < 1000 && mouse.y > 450 && mouse.y < 500);
            employee_joining_date_Active = (mouse.x > 600 && mouse.x < 1000 && mouse.y > 550 && mouse.y < 600);
            employee_skills_Active = (mouse.x > 600 && mouse.x < 1000 && mouse.y > 650 && mouse.y < 700);
            employee_salary_Active = (mouse.x > 600 && mouse.x < 1000 && mouse.y > 750 && mouse.y < 800);
            button_7_active = CheckCollisionPointRec(mouse, button_7);
        }

        if (button_7_active) {
            employee_management_module();
            CloseWindow();
            should_exit = true;
            break;
        }

        // Handle text input
        if (employee_id_string_Active || employee_name_Active || employee_department_Active ||
            employee_designation_Active || employee_joining_date_Active || employee_skills_Active ||
            employee_salary_Active) {

            int key = GetCharPressed();
            while (key > 0) {
                if (key >= 32 && key <= 125) {
                    if (employee_id_string_Active && employee_id_string.length() < 63) {
                        employee_id_string += static_cast<char>(key);
                    }
                    if (employee_name_Active && employee_name.length() < 63) {
                        employee_name += static_cast<char>(key);
                    }
                    if (employee_department_Active && employee_department.length() < 63) {
                        employee_department += static_cast<char>(key);
                    }
                    if (employee_designation_Active && employee_designation.length() < 63) {
                        employee_designation += static_cast<char>(key);
                    }
                    if (employee_joining_date_Active && employee_joining_date.length() < 63) {
                        employee_joining_date += static_cast<char>(key);
                    }
                    if (employee_skills_Active && employee_skills.length() < 63) {
                        employee_skills += static_cast<char>(key);
                    }
                    if (employee_salary_Active && employee_salary.length() < 63) {
                        employee_salary += static_cast<char>(key);
                    }
                }
                key = GetCharPressed();
            }

            // Handle backspace key
            if (IsKeyPressed(KEY_BACKSPACE)) {
                if (employee_id_string_Active && !employee_id_string.empty()) {
                    employee_id_string.pop_back();
                }
                if (employee_name_Active && !employee_name.empty()) {
                    employee_name.pop_back();
                }
                if (employee_department_Active && !employee_department.empty()) {
                    employee_department.pop_back();
                }
                if (employee_designation_Active && !employee_designation.empty()) {
                    employee_designation.pop_back();
                }
                if (employee_joining_date_Active && !employee_joining_date.empty()) {
                    employee_joining_date.pop_back();
                }
                if (employee_skills_Active && !employee_skills.empty()) {
                    employee_skills.pop_back();
                }
                if (employee_salary_Active && !employee_salary.empty()) {
                    employee_salary.pop_back();
                }
            }
        }

        // When Save button is pressed, validate and update the employee
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && (mouse.x > 600 && mouse.x < 1000 && mouse.y > 850 && mouse.y < 900)) {
            // Validate inputs
            is_data_valid = true; // Assume valid unless proven otherwise

            // Validate employee ID (should be a number)
            try {
                std::stoi(employee_id_string);
            }
            catch (...) {
                is_data_valid = false;
                DrawText("Invalid Employee ID. Must be a number.", 1500, 300, 20, RED);
            }

            // Validate salary (should be a number)
            try {
                std::stod(employee_salary);
            }
            catch (...) {
                is_data_valid = false;
                DrawText("Invalid Salary. Must be a number.", 1500, 350, 20, RED);
            }

            // Validate joining date (should match format DD/MM/YYYY)
            if (!is_valid_date(employee_joining_date)) {
                is_data_valid = false;
                DrawText("Invalid date format. Use DD/MM/YYYY.", 1500, 400, 20, RED);
            }

            // If valid, update the employee data
            if (is_data_valid) {
                temp.ID = std::stoi(employee_id_string);
                temp.name = employee_name;
                temp.department = employee_department;
                temp.designation = employee_designation;
                temp.salary = std::stod(employee_salary);
                temp.joining_date = employee_joining_date;
                temp.skills = employee_skills;
                employees[index] = temp;
                DrawText("Employee added successfully!", 1500, 400, 20, DARKGREEN);
            }
        }

        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawText("UPDATE EMPLOYEE DATA", 650, 50, 20, DARKGRAY);

        // Draw the input fields and labels for the user to update data
        DrawRectangle(600, 150, 400, 50, LIGHTGRAY);
        DrawText(employee_id_string.c_str(), 610, 160, 20, BLACK);
        DrawText("UPDATE ID", 250, 160, 20, DARKGRAY);
        DrawRectangle(600, 250, 400, 50, LIGHTGRAY);
        DrawText(employee_name.c_str(), 610, 260, 20, BLACK);
        DrawText("UPDATE Name", 250, 260, 20, DARKGRAY);
        DrawRectangle(600, 350, 400, 50, LIGHTGRAY);
        DrawText(employee_department.c_str(), 610, 360, 20, BLACK);
        DrawText("UPDATE Department", 250, 360, 20, DARKGRAY);
        DrawRectangle(600, 450, 400, 50, LIGHTGRAY);
        DrawText(employee_designation.c_str(), 610, 460, 20, BLACK);
        DrawText("UPDATE Designation", 250, 460, 20, DARKGRAY);
        DrawRectangle(600, 550, 400, 50, LIGHTGRAY);
        DrawText(employee_joining_date.c_str(), 610, 560, 20, BLACK);
        DrawText("UPDATE Joining Date", 250, 560, 20, DARKGRAY);
        DrawRectangle(600, 650, 400, 50, LIGHTGRAY);
        DrawText(employee_skills.c_str(), 610, 660, 20, BLACK);
        DrawText("UPDATE Skills", 250, 660, 20, DARKGRAY);
        DrawRectangle(600, 750, 400, 50, LIGHTGRAY);
        DrawText(employee_salary.c_str(), 610, 760, 20, BLACK);
        DrawText("UPDATE Salary", 250, 760, 20, DARKGRAY);

        // Save button
        DrawRectangle(600, 850, 400, 50, DARKGRAY);
        DrawText("Save", 800, 860, 20, WHITE);

        // Back button
        DrawRectangleRec(button_7, button_7_active ? DARKGRAY : LIGHTGRAY);
        DrawText("BACK", button_7.x + 10, button_7.y + 15, 20, BLACK);
        if (CheckCollisionPointRec(mouse, button_7) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            CloseWindow();
            update_employee_checker();
            should_exit = true;
            break;
        }
        EndDrawing();
    }
    // Update the employee data in the vector if date is valid
    if (should_exit) {
        CloseWindow();
    }
}
void delete_employee_id_input() {
    Rectangle button_back = { 0, 0, 400, 50 };
    Rectangle button_user_input = { 100, 100, 400, 50 };
    std::string employee_id = "";
    bool employee_id_input_active = false;
    bool shouldexit = false;

    while (!WindowShouldClose() && !shouldexit) {
        bool button_back_active = false;
        Vector2 mouse = GetMousePosition();

        // Handle button clicks
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            employee_id_input_active = (mouse.x > button_user_input.x && mouse.x < button_user_input.x + button_user_input.width) &&
                (mouse.y > button_user_input.y && mouse.y < button_user_input.y + button_user_input.height);
            button_back_active = (mouse.x > button_back.x && mouse.x < button_back.x + button_back.width) &&
                (mouse.y > button_back.y && mouse.y < button_back.y + button_back.height);
        }

        // Handle text input
        if (employee_id_input_active) {
            int key = GetCharPressed();
            while (key > 0) {
                if (key >= 32 && key <= 125) {
                    if (employee_id_input_active && employee_id.length() < 63) {
                        employee_id += static_cast<char>(key);
                    }
                }
                key = GetCharPressed();
            }
            if (IsKeyPressed(KEY_BACKSPACE) && !employee_id.empty()) {
                employee_id.pop_back();
            }
        }

        // Handle Enter key to validate the input
        if (employee_id_input_active && IsKeyPressed(KEY_ENTER)) {
            try {
                // Try to convert the employee_id to an integer
                int employee_id_int = std::stoi(employee_id);

                // Perform binary search to find the employee index
                int index_of_employee = binary_search(employee_id_int);
                if (index_of_employee == -1) {
                    DrawText("Employee does not exist in our database.", 100, 200, 20, BLACK);
                }
                else {
                    DrawText("Employee successfully deleted from database.", 100, 200, 20, BLACK);
                    delete_employee(employee_id_int);
                }
            }
            catch (const std::invalid_argument& e) {
                // If conversion fails (non-numeric input), show error and reset input
                DrawText("Invalid input. Please enter a valid Employee ID (numeric only).", 100, 200, 20, RED);
                employee_id = "";  // Reset the input field
            }
            catch (const std::out_of_range& e) {
                // If the input number is too large
                DrawText("Employee ID too large. Please enter a smaller number.", 100, 200, 20, RED);
                employee_id = "";  // Reset the input field
            }
        }

        // Drawing section
        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawText("Enter Employee ID:", 100, 70, 20, DARKGRAY);

        // Draw the input button and the entered text
        DrawRectangleRec(button_user_input, employee_id_input_active ? DARKGRAY : LIGHTGRAY);
        DrawText(employee_id.c_str(), button_user_input.x + 10, button_user_input.y + 10, 20, BLACK);

        // Draw the back button
        DrawRectangleRec(button_back, button_back_active ? DARKGRAY : LIGHTGRAY);
        DrawText("BACK", button_back.x + 10, button_back.y + 15, 20, BLACK);

        // Handle BACK button click
        if (CheckCollisionPointRec(mouse, button_back) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            CloseWindow();
            employee_management_module();
            shouldexit = true;
            break;
        }
        EndDrawing();
    }
    if (shouldexit) {
        CloseWindow();
    }
}
void delete_employee(int id_to_be_removed) {
    EMPLOYEE temp;
    std::vector<EMPLOYEE> updated_employees;
    for (int i = 0; i < employees.size(); ++i) {
        if (employees[i].ID != id_to_be_removed) {
            updated_employees.push_back(employees[i]);
        }
    }
    employees = updated_employees;
    save_employee_data();
}
void sort_employees(void) {
    int size = employees.size();
    for (int i = 1; i < size; ++i) {
        EMPLOYEE temp = employees[i];
        int key = employees[i].ID;
        int j = i - 1;
        while (j >= 0 && employees[j].ID > key) {
            employees[j + 1] = employees[j];
            j--;
        }
        employees[j + 1] = temp;
    }
}
void display_employee_checker(void) {
    Rectangle button_back = { 0, 0, 400, 50 };
    Rectangle button_user_input = { 100, 100, 400, 50 };
    std::string employee_id = "";
    bool employee_id_input_active = false;
    bool shouldexit = false;

    while (!WindowShouldClose() && !shouldexit) {
        bool button_back_active = false;
        Vector2 mouse = GetMousePosition();

        // Handle mouse input
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            employee_id_input_active = (mouse.x > button_user_input.x && mouse.x < button_user_input.x + button_user_input.width) &&
                (mouse.y > button_user_input.y && mouse.y < button_user_input.y + button_user_input.height);
            button_back_active = (mouse.x > button_back.x && mouse.x < button_back.x + button_back.width) &&
                (mouse.y > button_back.y && mouse.y < button_back.y + button_back.height);
        }

        // Handle text input
        if (employee_id_input_active) {
            int key = GetCharPressed();
            while (key > 0) {
                if (key >= 32 && key <= 125) {
                    if (employee_id_input_active && employee_id.length() < 63) {
                        employee_id += static_cast<char>(key);
                    }
                }
                key = GetCharPressed();
            }
            if (IsKeyPressed(KEY_BACKSPACE) && !employee_id.empty()) {
                employee_id.pop_back();
            }
        }

        // Handle Enter key to validate input and perform action
        if (employee_id_input_active && IsKeyPressed(KEY_ENTER)) {
            try {
                // Try to convert the employee_id to an integer
                int employee_id_int = std::stoi(employee_id);

                // Perform binary search to find the employee index
                int index_of_employee = binary_search(employee_id_int);
                if (index_of_employee == -1) {
                    DrawText("Employee does not exist in our database", 100, 200, 20, BLACK);
                }
                else {
                    display_specific_employee_data(index_of_employee);
                }
            }
            catch (const std::invalid_argument& e) {
                // If conversion fails (non-numeric input), show error and reset input
                DrawText("Invalid input. Please enter a valid Employee ID (numeric only).", 100, 200, 20, RED);
                employee_id = "";  // Reset the input field
            }
            catch (const std::out_of_range& e) {
                // If the input number is too large
                DrawText("Employee ID too large. Please enter a smaller number.", 100, 200, 20, RED);
                employee_id = "";  // Reset the input field
            }
        }
        // Drawing section
        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawText("Enter Employee ID:", 100, 70, 20, DARKGRAY);
        // Draw the input button and the entered text
        DrawRectangleRec(button_user_input, employee_id_input_active ? DARKGRAY : LIGHTGRAY);
        DrawText(employee_id.c_str(), button_user_input.x + 10, button_user_input.y + 10, 20, BLACK);
        // Draw the back button
        DrawRectangleRec(button_back, button_back_active ? DARKGRAY : LIGHTGRAY);
        DrawText("BACK", button_back.x + 10, button_back.y + 15, 20, BLACK);
        // Handle BACK button click
        if (CheckCollisionPointRec(mouse, button_back) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            CloseWindow();
            employee_management_module();
            shouldexit = true;
            break;
        }
        EndDrawing();
    }
    if (shouldexit) {
        CloseWindow();
    }
}
void display_specific_employee_data(int index) {
    std::string employee_id = std::to_string(employees[index].ID);
    std::string employee_name = employees[index].name;
    std::string employee_department = employees[index].department;
    std::string employee_designation = employees[index].designation;
    std::string employee_salary = std::to_string(employees[index].salary);
    std::string employee_joining_date = employees[index].joining_date;
    std::string employee_skills = employees[index].skills;
    std::string employee_leaves = std::to_string(employees[index].leaves);
    std::string employee_availability = employees[index].availability_string;

    Rectangle button_7 = { 0,0,400,50 };
    bool button_7_active = false;
    bool shouldexit = false;
    while (!WindowShouldClose()&& !shouldexit) {
        Vector2 mouse = GetMousePosition();
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            button_7_active = CheckCollisionPointRec(mouse, button_7);
        }
        if (button_7_active) {
            CloseWindow();
            employee_management_module();
            shouldexit = true;
            break;
        }
        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawText("Display employee data", 650, 50, 20, DARKGRAY);
        DrawRectangle(600, 150, 400, 50, LIGHTGRAY);
        DrawText(employee_id.c_str(), 610, 160, 20, BLACK);
        DrawText("ID", 300, 160, 20, DARKGRAY);
        DrawRectangle(600, 250, 400, 50, LIGHTGRAY);
        DrawText(employee_name.c_str(), 610, 260, 20, BLACK);
        DrawText("Name", 300, 260, 20, DARKGRAY);
        DrawRectangle(600, 350, 400, 50, LIGHTGRAY);
        DrawText(employee_department.c_str(), 610, 360, 20, BLACK);
        DrawText("Department", 300, 360, 20, DARKGRAY);
        DrawRectangle(600, 450, 400, 50, LIGHTGRAY);
        DrawText(employee_designation.c_str(), 610, 460, 20, BLACK);
        DrawText("Designation", 300, 460, 20, DARKGRAY);
        DrawRectangle(600, 550, 400, 50, LIGHTGRAY);
        DrawText(employee_joining_date.c_str(), 610, 560, 20, BLACK);
        DrawText("Joining Date", 300, 560, 20, DARKGRAY);
        DrawRectangle(600, 650, 400, 50, LIGHTGRAY);
        DrawText(employee_skills.c_str(), 610, 660, 20, BLACK);
        DrawText("Skills", 300, 660, 20, DARKGRAY);
        DrawRectangle(600, 750, 400, 50, LIGHTGRAY);
        DrawText(employee_availability.c_str(), 610, 760, 20, BLACK);
        DrawText("Availability (Y/N)", 300, 760, 20, DARKGRAY);
        DrawText("Salary(PKR)", 300, 860, 20, DARKGRAY);
        DrawRectangle(600, 850, 400, 50, LIGHTGRAY);
        DrawText(employee_salary.c_str(), 610, 860, 20, BLACK);
        DrawRectangleRec(button_7, button_7_active ? DARKGRAY : LIGHTGRAY);
        DrawText("BACK", button_7.x + 10, button_7.y + 15, 20, BLACK);
        EndDrawing();
    }
    if (shouldexit) {
        CloseWindow();
    }
}

void display_all_employees_data() {
    Rectangle button_back = { 0, 0, 400, 50 };
    bool button_back_active = false;
    bool shouldexit = false;
    // Scrollbar parameters
    int scroll_offset = 0;
    int item_height = 60;
    int visible_items = 13;  // Number of items visible on screen at once
    int max_scroll_offset = employees.size() * item_height - 800;
    if (max_scroll_offset < 0) max_scroll_offset = 0; // Ensure non-negative max offset

    int size, last_id;
    // Scrollbar dragging state
    bool is_dragging_scrollbar = false;
    float scrollbar_height = static_cast<float>(visible_items) / static_cast<float>(employees.size()) * 800;
    Rectangle scrollbar_handle = { 1900, 50, 20, scrollbar_height };
    if (employees.size() > 0) {
        size = employees.size() - 1;
        last_id = employees[size].ID;
    }
    else {
        size = 0;
        last_id = 0;
    }
    while (!WindowShouldClose()) {
        Vector2 mouse = GetMousePosition();

        // Handle mouse button for "BACK" button
        if (IsMouseButtonDown(MOUSE_LEFT_BUTTON)) {
            button_back_active = CheckCollisionPointRec(mouse, button_back);
            if (button_back_active) {
                CloseWindow();
                employee_management_module();
                shouldexit = true;
                break;
            }

            // Handle scrollbar dragging
            if (CheckCollisionPointRec(mouse, scrollbar_handle)) {
                is_dragging_scrollbar = true;
            }
        }

        if (IsMouseButtonUp(MOUSE_LEFT_BUTTON)) {
            is_dragging_scrollbar = false;
        }

        if (is_dragging_scrollbar) {
            // Adjust scroll_offset based on the mouse movement when dragging the scrollbar
            float drag_delta = mouse.y - (scrollbar_handle.y + scrollbar_handle.height / 2);
            float drag_ratio = drag_delta / (800 - scrollbar_height); // Convert pixel movement to ratio of total scroll area

            // Update the scroll_offset based on dragging
            scroll_offset = static_cast<int>(drag_ratio * max_scroll_offset);

            // Clamp scroll_offset within valid bounds
            if (scroll_offset < 0) scroll_offset = 0;
            if (scroll_offset > max_scroll_offset) scroll_offset = max_scroll_offset;

            // Update the scrollbar handle position
            scrollbar_handle.y = 50 + static_cast<float>(scroll_offset) / max_scroll_offset * (800 - scrollbar_height);
        }

        // Adjust scroll offset with mouse wheel
        scroll_offset -= GetMouseWheelMove() * 20;
        if (scroll_offset < 0)
            scroll_offset = 0;
        if (scroll_offset > max_scroll_offset)
            scroll_offset = max_scroll_offset;

        BeginDrawing();
        ClearBackground(RAYWHITE);

        // Draw column headers only once
        DrawText("ID", 100, 50, 20, DARKGRAY);
        DrawText("Name", 200, 50, 20, DARKGRAY);
        DrawText("Department", 400, 50, 20, DARKGRAY);
        DrawText("Designation", 600, 50, 20, DARKGRAY);
        DrawText("Joining Date", 800, 50, 20, DARKGRAY);
        DrawText("Skills", 1000, 50, 20, DARKGRAY);
        DrawText("Availability", 1200, 50, 20, DARKGRAY);
        DrawText("Salary (PKR)", 1400, 50, 20, DARKGRAY);

        // Draw employee data, but ensure it only draws the visible portion
        for (int i = 0; i < employees.size(); ++i) {
            int y_offset = 100 + (i * item_height) - scroll_offset; // Adjust y-coordinate for scrolling

            // Stop drawing if the y_offset is out of the visible range or if the last employee has been drawn
            if (y_offset > 850) break;  // Stop if we're past the visible area

            // Only draw the visible rows
            if (y_offset > 50 && y_offset < 850) {
                std::string employee_id = std::to_string(employees[i].ID);
                std::string employee_name = employees[i].name;
                std::string employee_department = employees[i].department;
                std::string employee_designation = employees[i].designation;
                std::string employee_joining_date = employees[i].joining_date;
                std::string employee_skills = employees[i].skills;
                std::string employee_availability = employees[i].availability_string;
                std::string employee_salary = std::to_string(employees[i].salary);

                // Draw employee information
                DrawText(employee_id.c_str(), 100, y_offset, 20, BLACK);
                DrawText(employee_name.c_str(), 200, y_offset, 20, BLACK);
                DrawText(employee_department.c_str(), 400, y_offset, 20, BLACK);
                DrawText(employee_designation.c_str(), 600, y_offset, 20, BLACK);
                DrawText(employee_joining_date.c_str(), 800, y_offset, 20, BLACK);
                DrawText(employee_skills.c_str(), 1000, y_offset, 20, BLACK);
                DrawText(employee_availability.c_str(), 1200, y_offset, 20, BLACK);
                DrawText(employee_salary.c_str(), 1400, y_offset, 20, BLACK);
            }
            if (employees[i].ID == last_id) {
                break;
            }
        }
        // Draw "BACK" button
        DrawRectangleRec(button_back, button_back_active ? DARKGRAY : LIGHTGRAY);
        DrawText("BACK", button_back.x + 10, button_back.y + 15, 20, BLACK);
        // Draw the scrollbar only if needed
        if (employees.size() > visible_items) {
            // Draw scrollbar background
            Rectangle scrollbar = { 1900, 50, 20, 800 };
            DrawRectangleRec(scrollbar, LIGHTGRAY);
            // Draw scrollbar handle
            DrawRectangleRec(scrollbar_handle, DARKGRAY);
        }
        EndDrawing();
    }
    if (shouldexit) {
        CloseWindow();
    }
}
int binary_search(int employee_id) {
    sort_employees();
    int low = 0;
    int high = employees.size() - 1;
    int index = -1;
    while (low <= high) {
        int mid = (low + high) / 2;
        if (employees[mid].ID == employee_id) {
            index = mid;
            break;
        }
        else if (employees[mid].ID > employee_id) {
            high = mid - 1;
        }
        else if (employees[mid].ID < employee_id) {
            low = mid + 1;
        }
    }
    return index;
}
void add_project(void) {

    std::string project_id_string, project_title, project_budget, project_start_date, project_end_date;
    std::vector<int> assigned_employees;
    Rectangle button_7 = { 0, 0, 400, 50 };

    bool project_id_string_Active = false, project_name_string_active = false, project_budget_string_active = false,
        project_start_date_string_active = false, project_end_date_string_active = false;
    bool assign_employees_active = false, button_7_active = false;
    Project temp;
    bool project_saved = false; // Flag to check if the project is saved
    bool shouldexit = false;
    while (!WindowShouldClose()&& !shouldexit) {
        Vector2 mouse = GetMousePosition();

        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            project_id_string_Active = (mouse.x > 600 && mouse.x < 1000 && mouse.y > 150 && mouse.y < 200);
            project_name_string_active = (mouse.x > 600 && mouse.x < 1000 && mouse.y > 250 && mouse.y < 300);
            project_budget_string_active = (mouse.x > 600 && mouse.x < 1000 && mouse.y > 350 && mouse.y < 400);
            project_start_date_string_active = (mouse.x > 600 && mouse.x < 1000 && mouse.y > 450 && mouse.y < 500);
            project_end_date_string_active = (mouse.x > 600 && mouse.x < 1000 && mouse.y > 550 && mouse.y < 600);
            assign_employees_active = (mouse.x > 600 && mouse.x < 1000 && mouse.y > 650 && mouse.y < 700);
            button_7_active = CheckCollisionPointRec(mouse, button_7);
        }

        // Handle "BACK" button action
        if (button_7_active && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            CloseWindow();
            project_management_module();
            shouldexit = true;
            break;
        }

        // Handle text input
        if (project_id_string_Active || project_name_string_active || project_budget_string_active ||
            project_start_date_string_active || project_end_date_string_active || assign_employees_active) {
            int key = GetCharPressed();
            while (key > 0) {
                if (key >= 32 && key <= 125) {
                    if (project_id_string_Active && project_id_string.length() < 63) {
                        project_id_string += static_cast<char>(key);
                    }
                    if (project_name_string_active && project_title.length() < 63) {
                        project_title += static_cast<char>(key);
                    }
                    if (project_budget_string_active && project_budget.length() < 63) {
                        project_budget += static_cast<char>(key);
                    }
                    if (project_start_date_string_active && project_start_date.length() < 63) {
                        project_start_date += static_cast<char>(key);
                    }
                    if (project_end_date_string_active && project_end_date.length() < 63) {
                        project_end_date += static_cast<char>(key);
                    }
                }
                key = GetCharPressed();
            }

            if (IsKeyPressed(KEY_BACKSPACE)) {
                if (project_id_string_Active && !project_id_string.empty()) {
                    project_id_string.pop_back();
                }
                if (project_name_string_active && !project_title.empty()) {
                    project_title.pop_back();
                }
                if (project_budget_string_active && !project_budget.empty()) {
                    project_budget.pop_back();
                }
                if (project_start_date_string_active && !project_start_date.empty()) {
                    project_start_date.pop_back();
                }
                if (project_end_date_string_active && !project_end_date.empty()) {
                    project_end_date.pop_back();
                }
            }
        }

        // Handle "Save" button click and validate inputs
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && (mouse.x > 600 && mouse.x < 1000 && mouse.y > 850 && mouse.y < 900)) {
            // Ensure valid Project ID
            if (project_id_string.empty()) {
                DrawText("Error: Project ID cannot be empty.", 100, 700, 20, RED);
                continue; // Skip saving if the Project ID is empty
            }

            try {
                temp.projectId = std::stoi(project_id_string); // Attempt to convert to integer
            }
            catch (const std::invalid_argument& e) {
                DrawText("Error: Invalid Project ID. Please enter a valid integer.", 100, 700, 20, RED);
                continue; // Skip saving if the Project ID is not a valid integer
            }
            catch (const std::out_of_range& e) {
                DrawText("Error: Project ID is out of range. Please enter a smaller value.", 100, 700, 20, RED);
                continue; // Skip saving if the integer is out of range
            }
            temp.projectId = std::stoi(project_id_string);

            // Ensure valid Project Title
            if (project_title.empty()) {
                DrawText("Error: Project Title cannot be empty.", 100, 730, 20, RED);
                continue; // Skip saving if the title is empty
            }
            temp.title = project_title;

            // Ensure valid Project Budget
            if (project_budget.empty()) {
                DrawText("Error: Budget cannot be empty.", 100, 700, 20, RED);
                continue; // Skip saving if the Budget is empty
            }
            try {
                temp.budget = std::stod(project_budget); // Attempt to convert to double (for floating-point values)
            }
            catch (const std::invalid_argument& e) {
                DrawText("Error: Invalid Budget. Please enter a valid number.", 100, 700, 20, RED);
                continue; // Skip saving if the Budget is not a valid number
            }
            catch (const std::out_of_range& e) {
                DrawText("Error: Budget is out of range. Please enter a smaller value.", 100, 700, 20, RED);
                continue; // Skip saving if the number is out of range
            }

            // Check if the Budget is positive
            if (temp.budget <= 0) {
                DrawText("Error: Budget must be a positive value.", 100, 730, 20, RED);
                continue; // Skip saving if the Budget is not positive
            }
            temp.budget = std::stoi(project_budget);

            // Ensure valid Start Date and End Date
            if (project_start_date.empty() || project_end_date.empty() || !is_valid_date(project_start_date) || !is_valid_date(project_end_date)) {
                DrawText("Error: Invalid date format. Please use dd/mm/yyyy.", 100, 790, 20, RED);
                continue; // Skip saving if the dates are invalid
            }

            // Check if start date is before end date
            int startNum = dateToNumber(project_start_date);
            int endNum = dateToNumber(project_end_date);
            if (startNum >= endNum) {
                DrawText("Error: Start Date must be before End Date.", 100, 820, 20, RED);
                continue; // Skip saving if the dates are incorrect
            }

            // Set project status based on the date comparison
            std::string currentDate = get_current_date();
            int currentDateNum = dateToNumber(currentDate);
            int projectEndDateNum = dateToNumber(project_end_date);
            temp.status = (projectEndDateNum > currentDateNum) ? "In Progress" : "Completed";

            // Check if the project ID already exists
            if (binary_search_project(temp.projectId) == -1) {
                projects.push_back(temp);  // Save the project
                project_saved = true; // Flag to prevent saving again
                DrawText("Project Saved Successfully", 100, 700, 20, DARKGREEN); // Confirmation message
            }
            else {
                DrawText("Error: Project corresponding to this ID already exists.", 100, 700, 20, DARKGRAY);
            }

            // Clear input fields after save attempt
            project_id_string = "";
            project_title = "";
            project_budget = "";
            project_start_date = "";
            project_end_date = "";
        }

        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawText("ADD PROJECT", 650, 50, 20, DARKGRAY);

        // Draw input fields for project details
        DrawRectangle(600, 150, 400, 50, LIGHTGRAY);
        DrawText(project_id_string.c_str(), 610, 160, 20, BLACK);
        DrawText("Project ID:", 300, 160, 20, DARKGRAY);

        DrawRectangle(600, 250, 400, 50, LIGHTGRAY);
        DrawText(project_title.c_str(), 610, 260, 20, BLACK);
        DrawText("Project Title:", 300, 260, 20, DARKGRAY);

        DrawRectangle(600, 350, 400, 50, LIGHTGRAY);
        DrawText(project_budget.c_str(), 610, 360, 20, BLACK);
        DrawText("Budget:", 300, 360, 20, DARKGRAY);

        DrawRectangle(600, 450, 400, 50, LIGHTGRAY);
        DrawText(project_start_date.c_str(), 610, 460, 20, BLACK);
        DrawText("Start Date:", 300, 460, 20, DARKGRAY);

        DrawRectangle(600, 550, 400, 50, LIGHTGRAY);
        DrawText(project_end_date.c_str(), 610, 560, 20, BLACK);
        DrawText("End Date:", 300, 560, 20, DARKGRAY);

        // Draw "Save" and "Back" buttons
        DrawRectangle(600, 850, 400, 50, DARKGRAY);
        DrawText("Save", 800, 860, 20, WHITE);
        DrawRectangleRec(button_7, button_7_active ? DARKGRAY : LIGHTGRAY);
        DrawText("BACK", button_7.x + 10, button_7.y + 15, 20, BLACK);

        EndDrawing();
    }
    if (shouldexit) {
        CloseWindow();
    }
    save_project_data();  // Save project data to file if needed
}

std::string get_current_date() {
    std::time_t t = std::time(nullptr); // Get current time
    std::tm now; // Use localtime_s for thread safety on Windows 
    if (localtime_s(&now, &t) != 0) {
        std::cerr << "Error in localtime_s" << std::endl;
        return ""; // Return empty string in case of error
    }
    // Format the current date as dd/mm/yyyy 
    std::stringstream ss;
    ss << std::setw(2) << std::setfill('0') << now.tm_mday << "/" << std::setw(2) << std::setfill('0') << (now.tm_mon + 1) << "/" << (now.tm_year + 1900);
    return ss.str();
}
int dateToNumber(const std::string& date) {
    if (date.length() != 10 || date[2] != '/' || date[5] != '/') {
        return -1;  // Invalid date format
    }

    int day, month, year;
    char slash;
    std::stringstream ss(date);
    ss >> day >> slash >> month >> slash >> year;

    // Check if the conversion was successful
    if (ss.fail()) return -1;

    // Return the date as an integer in YYYYMMDD format
    return year * 10000 + month * 100 + day;
}

void project_id_checker(void) {
    Rectangle button_back = { 0, 0, 400, 50 };
    Rectangle button_user_input = { 100, 100, 400, 50 };
    std::string project_id = "";
    bool project_id_input_active = false;
    bool should_exit = false;
    while (!WindowShouldClose() && !should_exit) {
        bool button_back_active = false;
        Vector2 mouse = GetMousePosition();

        // Handle mouse input
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            project_id_input_active = (mouse.x > button_user_input.x && mouse.x < button_user_input.x + button_user_input.width) &&
                (mouse.y > button_user_input.y && mouse.y < button_user_input.y + button_user_input.height);
            button_back_active = (mouse.x > button_back.x && mouse.x < button_back.x + button_back.width) &&
                (mouse.y > button_back.y && mouse.y < button_back.y + button_back.height);
        }

        // Handle text input
        if (project_id_input_active) {
            int key = GetCharPressed();
            while (key > 0) {
                if (key >= 32 && key <= 125) {
                    if (project_id_input_active && project_id.length() < 63) {
                        project_id += static_cast<char>(key);
                    }
                }
                key = GetCharPressed();
            }
            if (IsKeyPressed(KEY_BACKSPACE) && !project_id.empty()) {
                project_id.pop_back();
            }
        }
        // Handle Enter key to validate input and perform action
        if (project_id_input_active && IsKeyPressed(KEY_ENTER)) {
            try {
                // Try to convert the project_id to an integer
                int project_id_int = std::stoi(project_id);

                // Perform binary search to find the project index
                int index_of_project = binary_search_project(project_id_int);
                if (index_of_project == -1) {
                    DrawText("Project does not exist in our database", 100, 200, 20, BLACK);
                }
                else {
                    assign_project_to_employee_checker(index_of_project);
                }
            }
            catch (const std::invalid_argument& e) {
                // If conversion fails (non-numeric input), show error and reset input
                DrawText("Invalid input. Please enter a valid Project ID (numeric only).", 100, 200, 20, RED);
                project_id = "";  // Reset the input field
            }
            catch (const std::out_of_range& e) {
                // If the input number is too large
                DrawText("Project ID too large. Please enter a smaller number.", 100, 200, 20, RED);
                project_id = "";  // Reset the input field
            }
        }
        // Drawing section
        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawText("Enter Project ID:", 100, 70, 20, DARKGRAY);
        // Draw the input button and the entered text
        DrawRectangleRec(button_user_input, project_id_input_active ? DARKGRAY : LIGHTGRAY);
        DrawText(project_id.c_str(), button_user_input.x + 10, button_user_input.y + 10, 20, BLACK);
        // Draw the back button
        DrawRectangleRec(button_back, button_back_active ? DARKGRAY : LIGHTGRAY);
        DrawText("BACK", button_back.x + 10, button_back.y + 15, 20, BLACK);
        // Handle BACK button click
        if (CheckCollisionPointRec(mouse, button_back) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            CloseWindow();
            project_management_module();
            should_exit = true;
            break;
        }
        EndDrawing();
    }
    if (should_exit) {
        CloseWindow();
    }
}
void assign_project_to_employee_checker(int project_index) {
    int temp_project_index = project_index;
    Rectangle button_back = { 0, 0, 400, 50 };
    Rectangle button_user_input = { 100, 100, 400, 50 };
    std::string employee_id = "";
    bool employee_id_input_active = false;
    bool shouldexit = false;
    while (!WindowShouldClose() && !shouldexit) {
        bool button_back_active = false;
        Vector2 mouse = GetMousePosition();
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            employee_id_input_active = (mouse.x > button_user_input.x && mouse.x < button_user_input.x + button_user_input.width) && (mouse.y > button_user_input.y && mouse.y < button_user_input.y + button_user_input.height);
            button_back_active = (mouse.x > button_back.x && mouse.x < button_back.x + button_back.width) && (mouse.y > button_back.y && mouse.y < button_back.y + button_back.height);
        }
        if (employee_id_input_active) {
            int key = GetCharPressed();
            while (key > 0) {
                if (key >= 32 && key <= 125) {
                    if (employee_id_input_active && employee_id.length() < 63) {
                        employee_id += static_cast<char>(key);
                    }
                }
                key = GetCharPressed();
            }
            if (IsKeyPressed(KEY_BACKSPACE) && !employee_id.empty()) {
                employee_id.pop_back();
            }
        }
        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawText("Enter Employee ID:", 100, 70, 20, DARKGRAY);
        DrawRectangleRec(button_user_input, employee_id_input_active ? DARKGRAY : LIGHTGRAY);
        DrawText(employee_id.c_str(), button_user_input.x + 10, button_user_input.y + 10, 20, BLACK);
        if (employee_id_input_active && IsKeyPressed(KEY_ENTER)) {
            int employee_id_int = std::stoi(employee_id);
            int index_of_employee = binary_search(employee_id_int);
            if (index_of_employee == -1) {
                DrawText("Employee does not exist in our database", 100, 200, 20, BLACK);
            }
            else {
                search_employee_and_assign_employee(index_of_employee, employees[index_of_employee].ID, projects[temp_project_index], temp_project_index);
                DrawText("Employee succesfully assigned to project", 100, 200, 20, BLACK);
            }
        }
        DrawRectangleRec(button_back, button_back_active ? DARKGRAY : LIGHTGRAY);
        DrawText("BACK", button_back.x + 10, button_back.y + 15, 20, BLACK);
        if (CheckCollisionPointRec(mouse, button_back) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            CloseWindow();
            project_id_checker();
            shouldexit = true;
            break;
        }
        EndDrawing();
    }
    if (shouldexit) {
        CloseWindow();
    }
}
void search_employee_and_assign_employee(int employee_index, int employee_id, Project temp, int project_index) {
    for (int i = 0; i < busy_employees.size(); ++i) {
        if (employee_id == busy_employees[i])
            return;
    }
    busy_employees.push_back(employee_id);
    employees[employee_index].availability = false;
    availability_string_initializer(employees[employee_index]);
    availability_string_initializer(employees[employee_index]);
    temp.assignedEmployeeIds.push_back(employee_id);
    projects[project_index] = temp;
    busy_employees_text_generator();
}
void save_project_data(void) {
    std::ofstream FILE;
    FILE.open("PROJECT DETAILS.txt");
    if (!FILE) {
        std::cerr << "Error opening file" << std::endl;
        return;
    }
    for (const Project project : projects) {
        FILE << project.projectId << "|"
            << project.title << "|"
            << project.budget << "|"
            << project.startDate << "|"
            << project.endDate << "|";
        for (int i = 0; i < project.assignedEmployeeIds.size(); ++i) {
            FILE << project.assignedEmployeeIds[i] << "|";
        }
        FILE << std::endl;
    }
    load_project_data();
    FILE.close();
}
void load_project_data(void) {
    std::ifstream FILE("PROJECT DETAILS.txt");
    if (!FILE) {
        std::cerr << "Error opening file" << std::endl;
        return;
    }
    std::string line;
    while (std::getline(FILE, line)) {
        std::istringstream ss(line);
        Project temp;
        std::string item;
        std::getline(ss, item, '|');
        temp.projectId = std::stoi(item);
        std::getline(ss, temp.title, '|');
        std::getline(ss, item, '|');
        temp.budget = std::stod(item);
        std::getline(ss, temp.startDate, '|');
        std::getline(ss, temp.endDate, '|');
        temp.assignedEmployeeIds.clear();
        while (std::getline(ss, item, '|')) {
            if (!item.empty()) {
                temp.assignedEmployeeIds.push_back(std::stoi(item));
            }
        }
        projects.push_back(temp);
    }
    FILE.close();
}
void sort_projects(void) {
    int size = projects.size();
    for (int i = 1; i < size; ++i) {
        Project temp = projects[i];
        int key = projects[i].projectId;
        int j = i - 1;
        while (j >= 0 && projects[j].projectId > key) {
            projects[j + 1] = projects[j];
            j--;
        }
        projects[j + 1] = temp;
    }
}
int binary_search_project(int project_id) {
    sort_projects();
    int low = 0;
    int high = projects.size() - 1;
    int index = -1;
    while (low <= high) {
        int mid = (low + high) / 2;
        if (projects[mid].projectId == project_id) {
            index = mid;
            break;
        }
        else if (projects[mid].projectId > project_id) {
            high = mid - 1;
        }
        else if (projects[mid].projectId < project_id) {
            low = mid + 1;
        }
    }
    return index;
}
void busy_employees_text_generator(void) {
    std::ofstream outfile;
    outfile.open("Unavailable_employees.txt");
    for (int i = 0; i < busy_employees.size(); ++i) {
        outfile << busy_employees[i] << '|';
    }
    read_busy_employees_from_file();
}
void read_busy_employees_from_file(void) {
    std::ifstream infile("Unavailable_employees.txt"); if (infile.is_open()) {
        busy_employees.clear(); // Clear the existing data in the vector 
        std::string line;
        while (std::getline(infile, line, '|')) {
            if (!line.empty()) {
                int id = std::stoi(line);
                busy_employees.push_back(id);
            }
        }
        infile.close();
    }
    else {
        std::cerr << "Unable to open file Unavailable_employees.txt" << std::endl;
    }
}
void project_id_checker_for_display(void) {
    Rectangle button_back = { 0, 0, 400, 50 };
    Rectangle button_user_input = { 100, 100, 400, 50 };
    std::string project_id = "";
    bool project_id_input_active = false;
    bool shouldexit = false;
    while (!WindowShouldClose()&& !shouldexit) {
        bool button_back_active = false;
        Vector2 mouse = GetMousePosition();
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            project_id_input_active = (mouse.x > button_user_input.x && mouse.x < button_user_input.x + button_user_input.width) && (mouse.y > button_user_input.y && mouse.y < button_user_input.y + button_user_input.height);
            button_back_active = (mouse.x > button_back.x && mouse.x < button_back.x + button_back.width) && (mouse.y > button_back.y && mouse.y < button_back.y + button_back.height);
        }
        if (project_id_input_active) {
            int key = GetCharPressed();
            while (key > 0) {
                if (key >= 32 && key <= 125) {
                    if (project_id_input_active && project_id.length() < 63) {
                        project_id += static_cast<char>(key);
                    }
                }
                key = GetCharPressed();
            }
            if (IsKeyPressed(KEY_BACKSPACE) && !project_id.empty()) {
                project_id.pop_back();
            }
        }
        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawText("Enter Project ID:", 100, 70, 20, DARKGRAY);
        DrawRectangleRec(button_user_input, project_id_input_active ? DARKGRAY : LIGHTGRAY);
        DrawText(project_id.c_str(), button_user_input.x + 10, button_user_input.y + 10, 20, BLACK);
        if (project_id_input_active && IsKeyPressed(KEY_ENTER)) {
            int project_id_int = std::stoi(project_id);
            int index_of_project = binary_search_project(project_id_int);
            if (index_of_project == -1) {
                DrawText("Project does not exist in our database", 100, 200, 20, BLACK);
            }
            else {
                display_specific_project_data(index_of_project);
            }
        }
        DrawRectangleRec(button_back, button_back_active ? DARKGRAY : LIGHTGRAY);
        DrawText("BACK", button_back.x + 10, button_back.y + 15, 20, BLACK);
        if (CheckCollisionPointRec(mouse, button_back) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            CloseWindow();
            project_management_module();
            shouldexit = true;
            break;
        }
        EndDrawing();
    }
    if (shouldexit) {
        CloseWindow();
    }
}
bool check_employee_id_existence(const std::string* ID_POINTER_STRING, std::string* ID_POINTER_RETURN, int size, const std::string& id_to_check, int current_index) {
    for (int j = 0; j < current_index; ++j) {
        if (*(ID_POINTER_RETURN + j) == id_to_check) {
            return true;
        }
    }
    return false;
}

void display_specific_project_data(int index) {
    bool shouldexit = false;
    std::string project_id = std::to_string(projects[index].projectId);
    std::string project_name = projects[index].title;
    std::string project_budget = std::to_string(projects[index].budget);
    std::string project_start_date = projects[index].startDate;
    std::string project_end_date = projects[index].endDate;
    std::string project_status = projects[index].status;  // Add project status

    int size = projects[index].assignedEmployeeIds.size();
    std::string* ID_POINTER_STRING = new std::string[size];
    for (int i = 0; i < size; ++i) {
        *(ID_POINTER_STRING + i) = std::to_string(projects[index].assignedEmployeeIds[i]);
    }
    std::string* ID_POINTER_STRING_CHECKED = new std::string[size];
    int checked_size = 0;
    for (int i = 0; i < size; ++i) {
        bool is_duplicate = check_employee_id_existence(ID_POINTER_STRING, ID_POINTER_STRING_CHECKED, checked_size, ID_POINTER_STRING[i], checked_size);
        if (!is_duplicate) {
            *(ID_POINTER_STRING_CHECKED + checked_size) = ID_POINTER_STRING[i];
            ++checked_size;
        }
    }

    Rectangle button_7 = { 0, 0, 400, 50 };
    bool button_7_active = false;
    Rectangle employee_ids_box = { 600, 650, 400, 145 };  // Reduce the height of the employee IDs box
    bool employee_ids_box_active = false;
    Rectangle status_box = { 600, 600, 400, 50 };  // New box for displaying project status

    while (!WindowShouldClose() && !shouldexit) {
        Vector2 mouse = GetMousePosition();

        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            button_7_active = CheckCollisionPointRec(mouse, button_7);
        }
        if (button_7_active) {
            CloseWindow();
            project_management_module();
            shouldexit = true;
            break;
        }

        BeginDrawing();
        ClearBackground(RAYWHITE);

        DrawText("Project Details", 650, 50, 20, DARKGRAY);

        // Display Project ID
        DrawRectangle(600, 150, 400, 50, LIGHTGRAY);
        DrawText(project_id.c_str(), 610, 160, 20, BLACK);
        DrawText("ID", 300, 160, 20, DARKGRAY);

        // Display Project Title
        DrawRectangle(600, 250, 400, 50, LIGHTGRAY);
        DrawText(project_name.c_str(), 610, 260, 20, BLACK);
        DrawText("Title", 300, 260, 20, DARKGRAY);

        // Display Project Budget
        DrawRectangle(600, 350, 400, 50, LIGHTGRAY);
        DrawText(project_budget.c_str(), 610, 360, 20, BLACK);
        DrawText("Budget", 300, 360, 20, DARKGRAY);

        // Display Project Start Date
        DrawRectangle(600, 450, 400, 50, LIGHTGRAY);
        DrawText(project_start_date.c_str(), 610, 460, 20, BLACK);
        DrawText("Start Date", 300, 460, 20, DARKGRAY);

        // Display Project End Date
        DrawRectangle(600, 550, 400, 50, LIGHTGRAY);
        DrawText(project_end_date.c_str(), 610, 560, 20, BLACK);
        DrawText("End Date", 300, 560, 20, DARKGRAY);

        // Display Project Status
        DrawRectangleRec(status_box, LIGHTGRAY);
        DrawText(project_status.c_str(), 610, 610, 20, BLACK);  // Display the project status
        DrawText("Status", 300, 610, 20, DARKGRAY);  // Label for Status

        // Display Assigned Employees
        DrawRectangleRec(employee_ids_box, LIGHTGRAY);
        DrawText("Assigned Employees:", 610, 630, 20, DARKGRAY);
        int y_position = 670;
        int x_position = 610;
        for (int i = 0; i < checked_size; ++i) {
            std::string display_string = ID_POINTER_STRING_CHECKED[i] + ',';
            DrawText(display_string.c_str(), x_position, y_position, 20, BLACK);
            x_position += 30;
            if (x_position == 990)
                y_position += 30;
        }
        // Display "BACK" button
        DrawRectangleRec(button_7, button_7_active ? DARKGRAY : LIGHTGRAY);
        DrawText("BACK", button_7.x + 10, button_7.y + 15, 20, BLACK);

        EndDrawing();
    }

    delete[] ID_POINTER_STRING;
    delete[] ID_POINTER_STRING_CHECKED;
    if (shouldexit) {
        CloseWindow();
    }
}
void financial_id_checker_for_display(void) {
    Rectangle button_back = { 0, 0, 400, 50 };
    Rectangle button_user_input = { 100, 100, 400, 50 };
    std::string finance_year = "";
    bool finance_year_active = false;
    bool shouldexit = false;
    while (!WindowShouldClose() && !shouldexit) {
        bool button_back_active = false;
        Vector2 mouse = GetMousePosition();

        // Handle mouse input
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            finance_year_active = (mouse.x > button_user_input.x && mouse.x < button_user_input.x + button_user_input.width) &&
                (mouse.y > button_user_input.y && mouse.y < button_user_input.y + button_user_input.height);
            button_back_active = (mouse.x > button_back.x && mouse.x < button_back.x + button_back.width) &&
                (mouse.y > button_back.y && mouse.y < button_back.y + button_back.height);
        }

        // Handle text input
        if (finance_year_active) {
            int key = GetCharPressed();
            while (key > 0) {
                if (key >= 32 && key <= 125) {
                    if (finance_year_active && finance_year.length() < 63) {
                        finance_year += static_cast<char>(key);
                    }
                }
                key = GetCharPressed();
            }
            if (IsKeyPressed(KEY_BACKSPACE) && !finance_year.empty()) {
                finance_year.pop_back();
            }
        }

        // Handle Enter key to validate input and perform action
        if (finance_year_active && IsKeyPressed(KEY_ENTER)) {
            try {
                // Try to convert the finance_year to an integer
                int year_int = std::stoi(finance_year);

                // Perform binary search to find the financial summary
                int index_of_summary = binary_search_finances(year_int);
                if (index_of_summary == -1) {
                    DrawText("Summary of this year does not exist in our database", 100, 200, 20, BLACK);
                }
                else {
                    display_finacial_summary(index_of_summary);
                    CloseWindow();
                    shouldexit = true;
                    break;
                }
            }
            catch (const std::invalid_argument& e) {
                // If conversion fails (non-numeric input), show error and reset input
                DrawText("Invalid input. Please enter a valid Year (numeric only).", 100, 200, 20, RED);
                finance_year = "";  // Reset the input field
            }
            catch (const std::out_of_range& e) {
                // If the input number is too large
                DrawText("Year is too large. Please enter a smaller number.", 100, 200, 20, RED);
                finance_year = "";  // Reset the input field
            }
        }
        // Drawing section
        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawText("Enter Year:", 100, 70, 20, DARKGRAY);
        // Draw the input button and the entered text
        DrawRectangleRec(button_user_input, finance_year_active ? DARKGRAY : LIGHTGRAY);
        DrawText(finance_year.c_str(), button_user_input.x + 10, button_user_input.y + 10, 20, BLACK);
        // Draw the back button
        DrawRectangleRec(button_back, button_back_active ? DARKGRAY : LIGHTGRAY);
        DrawText("BACK", button_back.x + 10, button_back.y + 15, 20, BLACK);
        // Handle BACK button click
        if (CheckCollisionPointRec(mouse, button_back) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            CloseWindow();
            finance_management_module();
            shouldexit = true;
            break;
        }
        EndDrawing();
    }
    if (shouldexit) {
        CloseWindow();
    }
}
// Function to determine the maximum value and scale other values accordingly
void draw_bar_chart(int income, int expense, int net_income, int tax, int max_value) {
    // Define some spacing for the chart
    const int chart_x = 1200;
    const int chart_width = 100; // Width of each bar
    const int bar_gap = 30; // Gap between bars
    const int max_height = 200; // Maximum height of the bars (adjust as needed)

    // Scaling factor based on the largest value
    float scale_factor = static_cast<float>(max_height) / max_value;

    // Draw bars for each financial value
    // Income bar
    int income_height = static_cast<int>(income * scale_factor);
    DrawRectangle(chart_x, 450 - income_height, chart_width, income_height, GREEN);

    // Expense bar
    int expense_height = static_cast<int>(expense * scale_factor);
    DrawRectangle(chart_x + chart_width + bar_gap, 450 - expense_height, chart_width, expense_height, RED);

    // Net income bar
    int net_income_height = static_cast<int>(net_income * scale_factor);
    DrawRectangle(chart_x + 2 * (chart_width + bar_gap), 450 - net_income_height, chart_width, net_income_height, BLUE);

    // Tax bar
    int tax_height = static_cast<int>(tax * scale_factor);
    DrawRectangle(chart_x + 3 * (chart_width + bar_gap), 450 - tax_height, chart_width, tax_height, DARKGRAY);

    // Labels for each bar
    DrawText("Income", chart_x, 470, 20, GREEN);
    DrawText("Expense", chart_x + chart_width + bar_gap, 470, 20, RED);
    DrawText("Net Income", chart_x + 2 * (chart_width + bar_gap), 470, 20, BLUE);
    DrawText("Tax", chart_x + 3 * (chart_width + bar_gap) + 10, 470, 20, DARKGRAY);
}
// Function to draw bar chart for each month based on income, net income, and expenses
void draw_monthly_bar_chart(int total_income[], int expenses[], int net_income[]) {
    const int chart_x = 100;   // X position for the chart
    const int chart_width = 70;  // Width of each bar
    const int bar_gap = 20;      // Gap between bars
    const int max_height = 100;  // Maximum height for the bars (adjust as needed)

    // Maximum value to scale the bars
    int max_value = 0;
    for (int i = 0; i < 12; ++i) {
        max_value = std::max({ max_value, total_income[i], expenses[i], net_income[i] });
    }

    // Scaling factor to fit bars within the available space
    float scale_factor = static_cast<float>(max_height) / max_value;

    // Loop through each month to draw the bars
    for (int i = 0; i < 12; ++i) {
        int income_height = static_cast<int>(total_income[i] * scale_factor);
        int expense_height = static_cast<int>(expenses[i] * scale_factor);
        int net_income_height = static_cast<int>(net_income[i] * scale_factor);

        // Draw income bar for the current month
        DrawRectangle(chart_x + i * (chart_width + bar_gap), 650 - income_height, chart_width, income_height, GREEN);

        // Draw expense bar for the current month
        DrawRectangle(chart_x + i * (chart_width + bar_gap), 750 - expense_height, chart_width, expense_height, RED);
    }

    // Add labels for each month
    const char* months[12] = { "Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec" };
    for (int i = 0; i < 12; ++i) {
        DrawText(months[i], chart_x + i * (chart_width + bar_gap) + 10, 750, 15, DARKGRAY);
    }
    DrawText("Monthly Expenses and Incomes", 150 , 850, 30, DARKGRAY);
}
// Modified display_financial_summary function with bar chart
void display_finacial_summary(int index) {
    Financial_matters temp = finances[index];
    std::string year = temp.year;
    int Yearly_income = 0;
    int Yearly_expense = 0;
    int net_income = 0;
    bool shouldexit = false;
    for (int i = 0; i < 12; ++i) {
        Yearly_income += temp.total_income[i];
    }
    for (int i = 0; i < 12; ++i) {
        Yearly_expense += temp.expenses[i];
    }
    for (int i = 0; i < 12; ++i) {
        net_income += temp.net_income[i];
    }
    int tax = corporate_tax_calculator(Yearly_income);
    std::string income_str = std::to_string(Yearly_income);
    std::string expense_str = std::to_string(Yearly_expense);
    std::string net_income_str = std::to_string(net_income);
    std::string tax_str = std::to_string(tax);
    Rectangle button_7 = { 0,0,400,50 };
    bool button_7_active = false;

    // Find the maximum value to scale the bar chart
    int max_value = std::max({ Yearly_income, Yearly_expense, net_income, tax });

    while (!WindowShouldClose() && !shouldexit) {
        Vector2 mouse = GetMousePosition();
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            button_7_active = CheckCollisionPointRec(mouse, button_7);
        }
        if (button_7_active) {
            CloseWindow();
            finance_management_module();
            shouldexit = true;
            break;
        }

        BeginDrawing();
        ClearBackground(RAYWHITE);
        std::string display_string = "Financial Summary for " + year;
        DrawText(display_string.c_str(), 650, 50, 20, DARKGRAY);

        // Display financial information
        DrawRectangle(600, 150, 400, 50, LIGHTGRAY);
        DrawText(income_str.c_str(), 610, 160, 20, BLACK);
        DrawText("Total yearly income(PKR)", 150, 160, 20, DARKGRAY);

        DrawRectangle(600, 250, 400, 50, LIGHTGRAY);
        DrawText(expense_str.c_str(), 610, 260, 20, BLACK);
        DrawText("Total yearly expense(PKR)", 150, 260, 20, DARKGRAY);

        DrawRectangle(600, 350, 400, 50, LIGHTGRAY);
        DrawText(net_income_str.c_str(), 610, 360, 20, BLACK);
        DrawText("Net income(PKR)", 150, 360, 20, DARKGRAY);

        DrawRectangle(600, 450, 400, 50, LIGHTGRAY);
        DrawText(tax_str.c_str(), 610, 460, 20, BLACK);
        DrawText("Tax(PKR)", 150, 460, 20, DARKGRAY);

        // Draw the bar chart
        draw_bar_chart(Yearly_income, Yearly_expense, net_income, tax, max_value);
        draw_monthly_bar_chart(temp.total_income, temp.expenses, temp.net_income);
        // Draw BACK button
        DrawRectangleRec(button_7, button_7_active ? DARKGRAY : LIGHTGRAY);
        DrawText("BACK", button_7.x + 10, button_7.y + 15, 20, BLACK);

        EndDrawing();
    }
    if (shouldexit) {
        CloseWindow();
    }
}
void Add_financial_summary(void) {
    Rectangle button_back = { 0, 0, 400, 50 };
    Rectangle button_user_input = { 100, 100, 400, 50 };
    std::string year = "";
    bool year_active = false;
    bool shouldexit = false;

    while (!WindowShouldClose() && !shouldexit) {
        bool button_back_active = false;
        Vector2 mouse = GetMousePosition();
        // Handle mouse input
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            year_active = (mouse.x > button_user_input.x && mouse.x < button_user_input.x + button_user_input.width) &&
                (mouse.y > button_user_input.y && mouse.y < button_user_input.y + button_user_input.height);
            button_back_active = (mouse.x > button_back.x && mouse.x < button_back.x + button_back.width) &&
                (mouse.y > button_back.y && mouse.y < button_back.y + button_back.height);
        }
        // Handle text input
        if (year_active) {
            int key = GetCharPressed();
            while (key > 0) {
                if (key >= 32 && key <= 125) {
                    if (year_active && year.length() < 63) {
                        year += static_cast<char>(key);
                    }
                }
                key = GetCharPressed();
            }
            if (IsKeyPressed(KEY_BACKSPACE) && !year.empty()) {
                year.pop_back();
            }
        }
        // Handle Enter key to validate input and perform action
        if (year_active && IsKeyPressed(KEY_ENTER)) {
            try {
                // Try to convert the year to an integer
                int year_int = std::stoi(year);

                // Check if the financial report for the year already exists
                int index = binary_search_finances(year_int);
                if (index == -1) {
                    // If the report doesn't exist, add the income for that year
                    add_income(year);
                    CloseWindow();
                    break;
                }
                else {
                    // If the report exists, display an error message
                    DrawText("Financial report of this year already exists", 500, 500, 20, RED);
                }
            }
            catch (const std::invalid_argument& e) {
                // If conversion fails (non-numeric input), show error and reset input
                DrawText("Invalid input. Please enter a valid Year (numeric only).", 100, 200, 20, RED);
                year = "";  // Reset the input field
            }
            catch (const std::out_of_range& e) {
                // If the input number is too large
                DrawText("Year is too large. Please enter a smaller number.", 100, 200, 20, RED);
                year = "";  // Reset the input field
            }
        }
        // Drawing section
        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawText("Enter Year:", 100, 70, 20, DARKGRAY);
        // Draw the input button and the entered text
        DrawRectangleRec(button_user_input, year_active ? DARKGRAY : LIGHTGRAY);
        DrawText(year.c_str(), button_user_input.x + 10, button_user_input.y + 10, 20, BLACK);
        // Draw the back button
        DrawRectangleRec(button_back, button_back_active ? DARKGRAY : LIGHTGRAY);
        DrawText("BACK", button_back.x + 10, button_back.y + 15, 20, BLACK);
        // Handle BACK button click
        if (CheckCollisionPointRec(mouse, button_back) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            CloseWindow();
            finance_management_module();
            shouldexit = true;
            break;
        }
        EndDrawing();
    }
    if (shouldexit) {
        CloseWindow();
    }
}
void finance_management_module(void) {

    Rectangle button_1 = { 700, 170, 400, 50 };
    Rectangle button_2 = { 700, 230, 400, 50 };
    Rectangle button_7 = { 700, 290 ,400, 50 };
    bool shouldexit = false;

    while (!WindowShouldClose() && !shouldexit) {
        Vector2 mouse_position = GetMousePosition();

        bool button_1_Active = false;
        bool button_2_Active = false;
        bool button_7_Active = false;

        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            if (CheckCollisionPointRec(mouse_position, button_1)) {
                button_1_Active = true;
                CloseWindow();
                Add_financial_summary();
                shouldexit = true;
                break;
            }
            if (CheckCollisionPointRec(mouse_position, button_2)) {
                button_2_Active = true;
                CloseWindow();
                financial_id_checker_for_display();
                shouldexit = true;
                break;
            }
            if (CheckCollisionPointRec(mouse_position, button_7)) {
                button_7_Active = true;
                CloseWindow();
                display_manager_options();
                shouldexit = true;
                break;
            }
        }
        BeginDrawing();
        DrawText("Welcome Sir!", 750, 100, 50, BLACK);
        ClearBackground(RAYWHITE);
        DrawRectangleRec(button_1, button_1_Active ? DARKGRAY : LIGHTGRAY);
        DrawText("Create new financial summary", button_1.x + 10, button_1.y + 15, 20, BLACK);
        DrawRectangleRec(button_2, button_2_Active ? DARKGRAY : LIGHTGRAY);
        DrawText("View yearly finances", button_2.x + 10, button_2.y + 15, 20, BLACK);
        DrawRectangleRec(button_7, button_7_Active ? DARKGRAY : LIGHTGRAY);
        DrawText("BACK", button_7.x + 10, button_7.y + 15, 20, BLACK);
        EndDrawing();
    }
    if (shouldexit) {
        CloseWindow();
    }
}
void add_income(std::string year) {
    // Input fields as strings for each month's income
    std::string jan_income_string, feb_income_string, march_income_string;
    std::string april_income_string, may_income_string, june_income_string;
    std::string july_income_string, august_income_string, sep_income_string;
    std::string oct_income_string, nov_income_string, dec_income_string;

    Rectangle button_7 = { 0, 0, 400, 50 };
    int total_income[12];
    bool jan_income_active = false, feb_income_active = false, march_income_active = false;
    bool april_income_active = false, may_income_active = false, june_income_active = false;
    bool july_income_active = false, august_income_active = false, sep_income_active = false;
    bool oct_income_active = false, nov_income_active = false, dec_income_active = false;
    bool button_7_active = false;
    bool should_exit = false;
    while (!WindowShouldClose() && !should_exit) {
        Vector2 mouse = GetMousePosition();

        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            jan_income_active = (mouse.x > 600 && mouse.x < 1000 && mouse.y > 145 && mouse.y < 185);
            feb_income_active = (mouse.x > 600 && mouse.x < 1000 && mouse.y > 195 && mouse.y < 235);
            march_income_active = (mouse.x > 600 && mouse.x < 1000 && mouse.y > 245 && mouse.y < 285);
            april_income_active = (mouse.x > 600 && mouse.x < 1000 && mouse.y > 295 && mouse.y < 335);
            may_income_active = (mouse.x > 600 && mouse.x < 1000 && mouse.y > 345 && mouse.y < 385);
            june_income_active = (mouse.x > 600 && mouse.x < 1000 && mouse.y > 395 && mouse.y < 435);
            july_income_active = (mouse.x > 600 && mouse.x < 1000 && mouse.y > 445 && mouse.y < 485);
            august_income_active = (mouse.x > 600 && mouse.x < 1000 && mouse.y > 495 && mouse.y < 535);
            sep_income_active = (mouse.x > 600 && mouse.x < 1000 && mouse.y > 545 && mouse.y < 585);
            oct_income_active = (mouse.x > 600 && mouse.x < 1000 && mouse.y > 595 && mouse.y < 635);
            nov_income_active = (mouse.x > 600 && mouse.x < 1000 && mouse.y > 645 && mouse.y < 685);
            dec_income_active = (mouse.x > 600 && mouse.x < 1000 && mouse.y > 695 && mouse.y < 735);
            button_7_active = CheckCollisionPointRec(mouse, button_7);
        }

        if (button_7_active) {
            CloseWindow();
            finance_management_module();
            should_exit = true;
            break;
        }

        // Handle text input for each month
        if (jan_income_active || feb_income_active || march_income_active || april_income_active ||
            may_income_active || june_income_active || july_income_active || august_income_active ||
            sep_income_active || oct_income_active || nov_income_active || dec_income_active) {
            int key = GetCharPressed();
            while (key > 0) {
                if (key >= 32 && key <= 125) {
                    if (jan_income_active && jan_income_string.length() < 63) {
                        jan_income_string += static_cast<char>(key);
                    }
                    if (feb_income_active && feb_income_string.length() < 63) {
                        feb_income_string += static_cast<char>(key);
                    }
                    if (march_income_active && march_income_string.length() < 63) {
                        march_income_string += static_cast<char>(key);
                    }
                    if (april_income_active && april_income_string.length() < 63) {
                        april_income_string += static_cast<char>(key);
                    }
                    if (may_income_active && may_income_string.length() < 63) {
                        may_income_string += static_cast<char>(key);
                    }
                    if (june_income_active && june_income_string.length() < 63) {
                        june_income_string += static_cast<char>(key);
                    }
                    if (july_income_active && july_income_string.length() < 63) {
                        july_income_string += static_cast<char>(key);
                    }
                    if (august_income_active && august_income_string.length() < 63) {
                        august_income_string += static_cast<char>(key);
                    }
                    if (sep_income_active && sep_income_string.length() < 63) {
                        sep_income_string += static_cast<char>(key);
                    }
                    if (oct_income_active && oct_income_string.length() < 63) {
                        oct_income_string += static_cast<char>(key);
                    }
                    if (nov_income_active && nov_income_string.length() < 63) {
                        nov_income_string += static_cast<char>(key);
                    }
                    if (dec_income_active && dec_income_string.length() < 63) {
                        dec_income_string += static_cast<char>(key);
                    }
                }
                key = GetCharPressed();
            }
            // Handle backspace key
            if (IsKeyPressed(KEY_BACKSPACE)) {
                if (jan_income_active && !jan_income_string.empty()) {
                    jan_income_string.pop_back();
                }
                if (feb_income_active && !feb_income_string.empty()) {
                    feb_income_string.pop_back();
                }
                if (march_income_active && !march_income_string.empty()) {
                    march_income_string.pop_back();
                }
                if (april_income_active && !april_income_string.empty()) {
                    april_income_string.pop_back();
                }
                if (may_income_active && !may_income_string.empty()) {
                    may_income_string.pop_back();
                }
                if (june_income_active && !june_income_string.empty()) {
                    june_income_string.pop_back();
                }
                if (july_income_active && !july_income_string.empty()) {
                    july_income_string.pop_back();
                }
                if (august_income_active && !august_income_string.empty()) {
                    august_income_string.pop_back();
                }
                if (sep_income_active && !sep_income_string.empty()) {
                    sep_income_string.pop_back();
                }
                if (oct_income_active && !oct_income_string.empty()) {
                    oct_income_string.pop_back();
                }
                if (nov_income_active && !nov_income_string.empty()) {
                    nov_income_string.pop_back();
                }
                if (dec_income_active && !dec_income_string.empty()) {
                    dec_income_string.pop_back();
                }
            }
        }

        // Validate input and only proceed if all are valid
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && (mouse.x > 600 && mouse.x < 1000 && mouse.y > 755 && mouse.y < 805)) {
            bool all_inputs_valid = true;
            std::vector<std::string> all_inputs = { jan_income_string, feb_income_string, march_income_string, april_income_string,
                may_income_string, june_income_string, july_income_string, august_income_string,
                sep_income_string, oct_income_string, nov_income_string, dec_income_string };

            for (int i = 0; i < 12; ++i) {
                try {
                    total_income[i] = std::stoi(all_inputs[i]);
                }
                catch (const std::invalid_argument& e) {
                    all_inputs_valid = false;
                    break;
                }
            }

            if (all_inputs_valid) {
                CloseWindow();
                add_expense(year, total_income);
                should_exit = true;
                break;
            }
            else {
                DrawText("Invalid Input! Enter valid integers for all months.", 1300, 300, 20, RED);
            }
        }

        BeginDrawing();
        ClearBackground(RAYWHITE);

        DrawText("ADD INCOME(PKR)", 650, 50, 20, DARKGRAY);

        // Drawing input fields for each month
        DrawRectangle(600, 145, 400, 40, LIGHTGRAY);
        DrawText(jan_income_string.c_str(), 610, 155, 20, BLACK);
        DrawText("January", 300, 155, 20, DARKGRAY);

        DrawRectangle(600, 195, 400, 40, LIGHTGRAY);
        DrawText(feb_income_string.c_str(), 610, 205, 20, BLACK);
        DrawText("February", 300, 205, 20, DARKGRAY);

        DrawRectangle(600, 245, 400, 40, LIGHTGRAY);
        DrawText(march_income_string.c_str(), 610, 255, 20, BLACK);
        DrawText("March", 300, 255, 20, DARKGRAY);

        DrawRectangle(600, 295, 400, 40, LIGHTGRAY);
        DrawText(april_income_string.c_str(), 610, 305, 20, BLACK);
        DrawText("April", 300, 305, 20, DARKGRAY);

        DrawRectangle(600, 345, 400, 40, LIGHTGRAY);
        DrawText(may_income_string.c_str(), 610, 355, 20, BLACK);
        DrawText("May", 300, 355, 20, DARKGRAY);

        DrawRectangle(600, 395, 400, 40, LIGHTGRAY);
        DrawText(june_income_string.c_str(), 610, 405, 20, BLACK);
        DrawText("June", 300, 405, 20, DARKGRAY);

        DrawRectangle(600, 445, 400, 40, LIGHTGRAY);
        DrawText(july_income_string.c_str(), 610, 455, 20, BLACK);
        DrawText("July", 300, 455, 20, DARKGRAY);

        DrawRectangle(600, 495, 400, 40, LIGHTGRAY);
        DrawText(august_income_string.c_str(), 610, 505, 20, BLACK);
        DrawText("August", 300, 505, 20, DARKGRAY);

        DrawRectangle(600, 545, 400, 40, LIGHTGRAY);
        DrawText(sep_income_string.c_str(), 610, 555, 20, BLACK);
        DrawText("September", 300, 555, 20, DARKGRAY);

        DrawRectangle(600, 595, 400, 40, LIGHTGRAY);
        DrawText(oct_income_string.c_str(), 610, 605, 20, BLACK);
        DrawText("October", 300, 605, 20, DARKGRAY);

        DrawRectangle(600, 645, 400, 40, LIGHTGRAY);
        DrawText(nov_income_string.c_str(), 610, 655, 20, BLACK);
        DrawText("November", 300, 655, 20, DARKGRAY);

        DrawRectangle(600, 695, 400, 40, LIGHTGRAY);
        DrawText(dec_income_string.c_str(), 610, 705, 20, BLACK);
        DrawText("December", 300, 705, 20, DARKGRAY);

        // Draw the save button
        DrawRectangle(600, 755, 400, 50, DARKGRAY);
        DrawText("Proceed to add expenses", 700, 765, 20, WHITE);

        // Draw BACK button
        DrawRectangleRec(button_7, button_7_active ? DARKGRAY : LIGHTGRAY);
        DrawText("BACK", button_7.x + 10, button_7.y + 15, 20, BLACK);

        EndDrawing();
    }
    if (should_exit) {
        CloseWindow();
    }
}

void add_expense(std::string year, int income_array[12]) {

    // Input fields as strings for each month's expense
    std::string jan_expense_string, feb_expense_string, march_expense_string;
    std::string april_expense_string, may_expense_string, june_expense_string;
    std::string july_expense_string, august_expense_string, sep_expense_string;
    std::string oct_expense_string, nov_expense_string, dec_expense_string;

    Rectangle button_7 = { 0, 0, 400, 50 };  // Back button rectangle
    Financial_matters temp;

    temp.year = year;

    bool jan_expense_active = false, feb_expense_active = false, march_expense_active = false;
    bool april_expense_active = false, may_expense_active = false, june_expense_active = false;
    bool july_expense_active = false, august_expense_active = false, sep_expense_active = false;
    bool oct_expense_active = false, nov_expense_active = false, dec_expense_active = false;
    bool button_7_active = false;
    bool should_exit = false;
    while (!WindowShouldClose()&& !should_exit) {
        Vector2 mouse = GetMousePosition();

        // Mouse click detection
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            jan_expense_active = (mouse.x > 600 && mouse.x < 1000 && mouse.y > 145 && mouse.y < 185);
            feb_expense_active = (mouse.x > 600 && mouse.x < 1000 && mouse.y > 195 && mouse.y < 235);
            march_expense_active = (mouse.x > 600 && mouse.x < 1000 && mouse.y > 245 && mouse.y < 285);
            april_expense_active = (mouse.x > 600 && mouse.x < 1000 && mouse.y > 295 && mouse.y < 335);
            may_expense_active = (mouse.x > 600 && mouse.x < 1000 && mouse.y > 345 && mouse.y < 385);
            june_expense_active = (mouse.x > 600 && mouse.x < 1000 && mouse.y > 395 && mouse.y < 435);
            july_expense_active = (mouse.x > 600 && mouse.x < 1000 && mouse.y > 445 && mouse.y < 485);
            august_expense_active = (mouse.x > 600 && mouse.x < 1000 && mouse.y > 495 && mouse.y < 535);
            sep_expense_active = (mouse.x > 600 && mouse.x < 1000 && mouse.y > 545 && mouse.y < 585);
            oct_expense_active = (mouse.x > 600 && mouse.x < 1000 && mouse.y > 595 && mouse.y < 635);
            nov_expense_active = (mouse.x > 600 && mouse.x < 1000 && mouse.y > 645 && mouse.y < 685);
            dec_expense_active = (mouse.x > 600 && mouse.x < 1000 && mouse.y > 695 && mouse.y < 735);
            button_7_active = CheckCollisionPointRec(mouse, button_7);
        }

        // If BACK button is pressed, return to finance management
        if (button_7_active) {
            CloseWindow();
            finance_management_module();
            should_exit = true;
            break;
        }

        // Handle text input for each month
        if (jan_expense_active || feb_expense_active || march_expense_active || april_expense_active ||
            may_expense_active || june_expense_active || july_expense_active || august_expense_active ||
            sep_expense_active || oct_expense_active || nov_expense_active || dec_expense_active) {

            int key = GetCharPressed();
            while (key > 0) {
                if (key >= 32 && key <= 125) {
                    if (jan_expense_active && jan_expense_string.length() < 63) {
                        jan_expense_string += static_cast<char>(key);
                    }
                    if (feb_expense_active && feb_expense_string.length() < 63) {
                        feb_expense_string += static_cast<char>(key);
                    }
                    if (march_expense_active && march_expense_string.length() < 63) {
                        march_expense_string += static_cast<char>(key);
                    }
                    if (april_expense_active && april_expense_string.length() < 63) {
                        april_expense_string += static_cast<char>(key);
                    }
                    if (may_expense_active && may_expense_string.length() < 63) {
                        may_expense_string += static_cast<char>(key);
                    }
                    if (june_expense_active && june_expense_string.length() < 63) {
                        june_expense_string += static_cast<char>(key);
                    }
                    if (july_expense_active && july_expense_string.length() < 63) {
                        july_expense_string += static_cast<char>(key);
                    }
                    if (august_expense_active && august_expense_string.length() < 63) {
                        august_expense_string += static_cast<char>(key);
                    }
                    if (sep_expense_active && sep_expense_string.length() < 63) {
                        sep_expense_string += static_cast<char>(key);
                    }
                    if (oct_expense_active && oct_expense_string.length() < 63) {
                        oct_expense_string += static_cast<char>(key);
                    }
                    if (nov_expense_active && nov_expense_string.length() < 63) {
                        nov_expense_string += static_cast<char>(key);
                    }
                    if (dec_expense_active && dec_expense_string.length() < 63) {
                        dec_expense_string += static_cast<char>(key);
                    }
                }
                key = GetCharPressed();
            }

            // Handle backspace key
            if (IsKeyPressed(KEY_BACKSPACE)) {
                if (jan_expense_active && !jan_expense_string.empty()) {
                    jan_expense_string.pop_back();
                }
                if (feb_expense_active && !feb_expense_string.empty()) {
                    feb_expense_string.pop_back();
                }
                if (march_expense_active && !march_expense_string.empty()) {
                    march_expense_string.pop_back();
                }
                if (april_expense_active && !april_expense_string.empty()) {
                    april_expense_string.pop_back();
                }
                if (may_expense_active && !may_expense_string.empty()) {
                    may_expense_string.pop_back();
                }
                if (june_expense_active && !june_expense_string.empty()) {
                    june_expense_string.pop_back();
                }
                if (july_expense_active && !july_expense_string.empty()) {
                    july_expense_string.pop_back();
                }
                if (august_expense_active && !august_expense_string.empty()) {
                    august_expense_string.pop_back();
                }
                if (sep_expense_active && !sep_expense_string.empty()) {
                    sep_expense_string.pop_back();
                }
                if (oct_expense_active && !oct_expense_string.empty()) {
                    oct_expense_string.pop_back();
                }
                if (nov_expense_active && !nov_expense_string.empty()) {
                    nov_expense_string.pop_back();
                }
                if (dec_expense_active && !dec_expense_string.empty()) {
                    dec_expense_string.pop_back();
                }
            }
        }
        // Save button functionality
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && (mouse.x > 600 && mouse.x < 1000 && mouse.y > 755 && mouse.y < 805)) {
            bool all_inputs_valid = true;
            std::vector<std::string> all_inputs = { jan_expense_string, feb_expense_string, march_expense_string, april_expense_string,
                may_expense_string, june_expense_string, july_expense_string, august_expense_string,
                sep_expense_string, oct_expense_string, nov_expense_string, dec_expense_string };

            for (int i = 0; i < 12; ++i) {
                try {
                    temp.expenses[i] = std::stoi(all_inputs[i]);
                }
                catch (const std::invalid_argument& e) {
                    all_inputs_valid = false;
                    break;
                }
            }
            if (all_inputs_valid) {
                for (int i = 0; i < 12; ++i) {
                    temp.total_income[i] = income_array[i];
                }
                for (int i = 0; i < 12; ++i) {
                    temp.net_income[i] = temp.total_income[i] - temp.expenses[i];
                }
                finances.push_back(temp);
                DrawText("Data saved successfully!", 1300, 300, 20, DARKGREEN);
                CloseWindow();
                finance_management_module();
                should_exit = true;
                break;
            }
            else {
                DrawText("Invalid Input! Enter valid integers for all months.", 1300, 300, 20, RED);
            }
        }
        BeginDrawing();
        ClearBackground(RAYWHITE);

        DrawText("ADD EXPENSE(PKR)", 650, 50, 20, DARKGRAY);

        // Drawing input fields for each month
        DrawRectangle(600, 145, 400, 40, LIGHTGRAY);
        DrawText(jan_expense_string.c_str(), 610, 155, 20, BLACK);
        DrawText("January", 300, 155, 20, DARKGRAY);

        DrawRectangle(600, 195, 400, 40, LIGHTGRAY);
        DrawText(feb_expense_string.c_str(), 610, 205, 20, BLACK);
        DrawText("February", 300, 205, 20, DARKGRAY);

        DrawRectangle(600, 245, 400, 40, LIGHTGRAY);
        DrawText(march_expense_string.c_str(), 610, 255, 20, BLACK);
        DrawText("March", 300, 255, 20, DARKGRAY);

        DrawRectangle(600, 295, 400, 40, LIGHTGRAY);
        DrawText(april_expense_string.c_str(), 610, 305, 20, BLACK);
        DrawText("April", 300, 305, 20, DARKGRAY);

        DrawRectangle(600, 345, 400, 40, LIGHTGRAY);
        DrawText(may_expense_string.c_str(), 610, 355, 20, BLACK);
        DrawText("May", 300, 355, 20, DARKGRAY);

        DrawRectangle(600, 395, 400, 40, LIGHTGRAY);
        DrawText(june_expense_string.c_str(), 610, 405, 20, BLACK);
        DrawText("June", 300, 405, 20, DARKGRAY);

        DrawRectangle(600, 445, 400, 40, LIGHTGRAY);
        DrawText(july_expense_string.c_str(), 610, 455, 20, BLACK);
        DrawText("July", 300, 455, 20, DARKGRAY);

        DrawRectangle(600, 495, 400, 40, LIGHTGRAY);
        DrawText(august_expense_string.c_str(), 610, 505, 20, BLACK);
        DrawText("August", 300, 505, 20, DARKGRAY);

        DrawRectangle(600, 545, 400, 40, LIGHTGRAY);
        DrawText(sep_expense_string.c_str(), 610, 555, 20, BLACK);
        DrawText("September", 300, 555, 20, DARKGRAY);

        DrawRectangle(600, 595, 400, 40, LIGHTGRAY);
        DrawText(oct_expense_string.c_str(), 610, 605, 20, BLACK);
        DrawText("October", 300, 605, 20, DARKGRAY);

        DrawRectangle(600, 645, 400, 40, LIGHTGRAY);
        DrawText(nov_expense_string.c_str(), 610, 655, 20, BLACK);
        DrawText("November", 300, 655, 20, DARKGRAY);

        DrawRectangle(600, 695, 400, 40, LIGHTGRAY);
        DrawText(dec_expense_string.c_str(), 610, 705, 20, BLACK);
        DrawText("December", 300, 705, 20, DARKGRAY);

        // Draw the save button
        DrawRectangle(600, 755, 400, 50, DARKGRAY);
        DrawText("Save", 800, 765, 20, WHITE);

        // Draw BACK button
        DrawRectangleRec(button_7, button_7_active ? DARKGRAY : LIGHTGRAY);
        DrawText("BACK", button_7.x + 10, button_7.y + 15, 20, BLACK);
        EndDrawing();
    }
    generate_financial_report();
    if (should_exit) {
        CloseWindow();
    }
}
void generate_financial_report() {
    std::ofstream outfile;
    outfile.open("Finances.txt");
    for (int i = 0; i < finances.size(); ++i) {
        outfile << finances[i].year << '|';
        for (int j = 0; j < 12; ++j) {
            outfile << finances[i].total_income[j] << '|';
        }
        for (int j = 0; j < 12; ++j) {
            outfile << finances[i].expenses[j] << '|';
        }
        for (int j = 0; j < 12; ++j) {
            outfile << finances[i].net_income[j] << '|';
        }
        outfile << std::endl;
    }
}
void input_financial_data() {
    std::ifstream infile("Finances.txt");  // Open the file for reading
    if (!infile) {
        std::cerr << "Unable to open the file!" << std::endl;
        return;
    }
    std::string line;
    while (std::getline(infile, line)) {
        Financial_matters data;
        std::stringstream ss(line);
        std::string token;
        // Read the year (it's a string now)
        std::getline(ss, token, '|');
        data.year = token;  // Directly assign the string
        // Read the total income values (12 months)
        for (int i = 0; i < 12; ++i) {
            std::getline(ss, token, '|');
            data.total_income[i] = std::stoi(token);  // Convert to int
        }
        // Read the expenses values (12 months)
        for (int i = 0; i < 12; ++i) {
            std::getline(ss, token, '|');
            data.expenses[i] = std::stoi(token);  // Convert to int
        }
        // Read the net income values (12 months)
        for (int i = 0; i < 12; ++i) {
            std::getline(ss, token, '|');
            data.net_income[i] = std::stoi(token);  // Convert to int
        }
        // Add the parsed data to the finances vector
        finances.push_back(data);
    }
    infile.close();
    std::cout << "Financial data loaded from 'Finances.txt'." << std::endl;
}
void sort_finances(void) {
    int size = finances.size();
    for (int i = 1; i < size; ++i) {
        Financial_matters temp = finances[i];
        int key = std::stoi(finances[i].year);
        int j = i - 1;
        while (j >= 0 && std::stoi(finances[j].year) > key) {
            finances[j + 1] = finances[j];
            j--;
        }
        finances[j + 1] = temp;
    }
}
int binary_search_finances(int year) {
    sort_finances();
    int low = 0;
    int high = finances.size() - 1;
    int index = -1;
    while (low <= high) {
        int mid = (low + high) / 2;
        if (std::stoi(finances[mid].year) == year) {
            index = mid;
            break;
        }
        else if (std::stoi(finances[mid].year) > year) {
            high = mid - 1;
        }
        else if (std::stoi(finances[mid].year) < year) {
            low = mid + 1;
        }
    }
    return index;
}
int corporate_tax_calculator(int income) {
    if ((income > 15000000) && (income <= 20000000))
        return income * 0.20;
    else if ((income > 20000000) && (income <= 25000000))
        return income * 0.21;
    else if ((income > 25000000) && (income <= 30000000))
        return income * 0.22;
    else if ((income > 30000000) && (income <= 35000000))
        return income * 0.23;
    else if ((income > 35000000) && (income <= 40000000))
        return income * 0.25;
    else if ((income > 40000000) && (income <= 50000000))
        return income * 0.27;
    else if (income > 50000000)
        return income * 0.29;
    else
        return income * 0.20;
    return 0;
}
