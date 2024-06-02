//设计一个程序，读取一个叫做generated_predictions.jsonl的文件，其每行内容格式为
//{"label": "I,N,F", "predict": "I,N,F,P"}
//其中label是真实标签，predict是预测标签。
//程序需要读取predict的前四个大写字符，然后将其按照cvs格式输出到一个叫做transformed_predictions.csv的文件中。
//例如，如果predict是"I,N,F,P,J"，那么输出应该是"I,N,F,P"
//例如，如果predict是"I,N,F,P,I,N,P"，那么输出应该是"I,N,F,P"
//例如，如果predict是"I,N,F,P"，那么输出应该是"I,N,F,P"
//C语言实现
#include <stdio.h>
#include <string.h>

int main() {
    FILE *fp_input, *fp_output;
    char buffer[1024]; // Buffer to hold each line from the JSONL file

    // Open the input JSONL file and output CSV file
    fp_input = fopen("generated_predictions_test.jsonl", "r");
    if (fp_input == NULL) {
        perror("Error opening input file");
        return -1;
    }
    
    fp_output = fopen("transformed_predictions_test.csv", "w");
    if (fp_output == NULL) {
        perror("Error opening output file");
        fclose(fp_input);
        return -1;
    }

    // Process each line in the input file
    while (fgets(buffer, 1024, fp_input) != NULL) {
        char *start = strstr(buffer, "\"predict\": \""); // Find the predict field
        if (start != NULL) {
            start += 12; // Move pointer to the start of the prediction string
            char output[5]; // Buffer to hold the extracted characters
            int i = 0, count = 0;

            // Extract the first four uppercase characters
            while (start[i] != '\0' && count < 4) {
                if (start[i] >= 'A' && start[i] <= 'Z') {
                    output[count++] = start[i];
                    if (count == 4) break;
                }
                i++;
            }
            output[count] = '\0'; // Null terminate the string

            // Check if less than 4 characters were found and fill remaining columns with empty
            char output1 = (count > 0) ? output[0] : ' ';
            char output2 = (count > 1) ? output[1] : ' ';
            char output3 = (count > 2) ? output[2] : ' ';
            char output4 = (count > 3) ? output[3] : ' ';

            // Write to the output file in CSV format
            fprintf(fp_output, "%s,%c,%c,%c,%c\n", output, output1, output2, output3, output4);
        }
    }

    // Close files
    fclose(fp_input);
    fclose(fp_output);

    return 0;
}

