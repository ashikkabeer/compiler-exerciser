#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_EXPRS 100
#define MAX_EXPR_LEN 100
#define MAX_VARS 50

// Structure to store the variable name and its constant value (if any)
typedef struct {
    char name[10];
    int value;
    int is_constant;  // Flag to check if the variable is constant
} Variable;

Variable vars[MAX_VARS];
int var_count = 0;

// Function to find if a variable is already assigned a constant value
int find_variable(const char *name) {
    for (int i = 0; i < var_count; i++) {
        if (strcmp(vars[i].name, name) == 0) {
            return i;
        }
    }
    return -1;  // Variable not found
}

// Function to add a new constant value for a variable
void set_variable(const char *name, int value) {
    int idx = find_variable(name);
    if (idx == -1) {
        // Variable not found, add new one
        strcpy(vars[var_count].name, name);
        vars[var_count].value = value;
        vars[var_count].is_constant = 1;
        var_count++;
    } else {
        // Variable found, update the value
        vars[idx].value = value;
        vars[idx].is_constant = 1;
    }
}

// Function to replace variables in expressions with their constant values (if available)
void optimize_expression(char *expr) {
    char result[MAX_EXPR_LEN];
    int j = 0;  // Index for result

    for (int i = 0; expr[i] != '\0'; i++) {
        // If the current character is a variable, check if it is constant
        if (expr[i] >= 'a' && expr[i] <= 'z') {
            char var_name[10];
            int k = 0;
            // Extract the variable name
            while (expr[i] >= 'a' && expr[i] <= 'z') {
                var_name[k++] = expr[i++];
            }
            var_name[k] = '\0'; // Null-terminate the variable name

            // Check if the variable has a constant value
            int idx = find_variable(var_name);
            if (idx != -1 && vars[idx].is_constant) {
                // If variable is constant, replace it with its value
                int value = vars[idx].value;
                j += sprintf(&result[j], "%d", value);
            } else {
                // Otherwise, just append the variable name as is
                j += sprintf(&result[j], "%s", var_name);
            }

            // Adjust the loop counter to skip over the variable characters
            i--;
        } else {
            // Copy other characters (e.g., operators, numbers) directly
            result[j++] = expr[i];
        }
    }
    result[j] = '\0';  // Null-terminate the result

    // Print the optimized expression
    printf("%s\n", result);
}

// Main function
int main() {
    int n;
    char expr[MAX_EXPR_LEN];

    // Read the number of expressions
    printf("Enter number of expressions: ");
    scanf("%d", &n);
    getchar();  // Consume the newline character after the number input

    // Read each expression and process constant propagation
    for (int i = 0; i < n; i++) {
        printf("Enter expression %d: ", i + 1);
        fgets(expr, MAX_EXPR_LEN, stdin);
        expr[strcspn(expr, "\n")] = '\0';  // Remove the newline character

        // Process the assignment: "var = expression"
        char var_name[10];
        int j = 0;
        while (expr[j] != ' ' && expr[j] != '=' && expr[j] != '\0') {
            var_name[j++] = expr[j];
        }
        var_name[j] = '\0';  // Null-terminate the variable name
        j += 2;  // Skip the " = " part

        // Extract and evaluate the expression (we assume simple expressions)
        int value = 0;
        int sign = 1;  // For handling negative values
        for (int i = j; expr[i] != '\0'; i++) {
            if (expr[i] == '+') {
                sign = 1;
            } else if (expr[i] == '-') {
                sign = -1;
            } else if (expr[i] >= '0' && expr[i] <= '9') {
                value = value * 10 + (expr[i] - '0');
            }
        }
        value *= sign;  // Apply the sign

        // Set the constant value for the variable
        set_variable(var_name, value);
    }

    // After constant propagation, print the optimized code
    printf("\nOptimized Code:\n");
    for (int i = 0; i < n; i++) {
        printf("Optimized Expression %d: ", i + 1);
        fgets(expr, MAX_EXPR_LEN, stdin);
        expr[strcspn(expr, "\n")] = '\0';  // Remove the newline character
        optimize_expression(expr);
    }

    return 0;
}
