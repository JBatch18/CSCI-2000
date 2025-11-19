#include <iostream>
#include <string>
#include <ctime>

using namespace std;        

int count_correct_characters(string sentence_to_type, string user_input_sentence, int sentence_length);
float calculate_accuracy_percent(int correct_characters, int total_characters);
void show_typing_results(string user_input_sentence, int correct_characters, int total_characters, float accuracy_percent, float typing_time_seconds);
void show_debug_info(const float* time_ptr, const float* accuracy_ptr);
void start_typing_test();
const float* time_ptr = nullptr;
const float* accuracy_ptr = nullptr;
int main()
{
    bool exit = false;
    char choice;
    do
    {
        cout << "Do you want to take the typing test? (Y/N): ";
        cin >> choice;
        cout << endl;
        if (choice != 'Y' && choice != 'y' && choice != 'N' && choice != 'n')
        {
            cout << "Invalid Input! Please try again!\n";
        }

    } while ((choice != 'Y' && choice != 'y' && choice != 'N' && choice != 'n'));

    if (choice == 'N' || choice == 'n')
    {
        return 0;
    }

    start_typing_test();
    
    do
    {
        cout << "Do you want to continue? (Y/N): ";
        cin >> choice;
        cout << endl;

        if ((choice != 'Y' && choice != 'y' && choice != 'N' && choice != 'n'))
        {
            cout << "Invalid Input! Please try again!\n";
        }
        else if (choice == 'N' || choice == 'n')
        {
            exit = true;
        }
        else
        {
            start_typing_test();
        }

    } while (!exit);

}

int count_correct_characters(string sentence_to_type, string user_input_sentence, int sentence_length)
{
    int correct_characters = 0;
    int cur_index = 0;
    for (cur_index; cur_index < sentence_length; cur_index++)
    {
        if (user_input_sentence[cur_index] == sentence_to_type[cur_index])
        {
           correct_characters++;
        }
        else if (user_input_sentence[cur_index] == '\0')
        {
            break;
        }
    }

    return correct_characters;
}
float calculate_accuracy_percent(int correct_characters, int total_characters)
{
    if (total_characters == 0)
    {
        return 0;
    }
    else
    {
        return (float)correct_characters / total_characters* 100;
    }
    
}
void show_typing_results(string user_input_sentence, int correct_characters, int total_characters, float accuracy_percent, float typing_time_seconds)
{
    cout << endl;
    cout << "--------------------------------\n";
    cout << "Your typed sentence:\n";
    cout << user_input_sentence << endl;
    cout << "--------------------------------\n";
    cout << "Total characters: " << total_characters << endl;
    cout << "Correct characters: " << correct_characters << endl;
    cout << "Accuracy: " << accuracy_percent << "%"   << endl;
    cout << "Time taken: " << typing_time_seconds << " seconds" << endl;
    if (typing_time_seconds == 0)
    {
        cout << "Typing Speed: 0 character per second\n";
    }
    else
    {
        cout << "Typing Speed: " << (total_characters / typing_time_seconds) << endl;
    }
    if (accuracy_percent == 100)
    {
        cout << "Feedback: Perfect!\n";
    }
    else if (accuracy_percent >= 90)
    {
        cout << "Feedback: Excellent speed and precision!\n";
    }
    else if (accuracy_percent >= 75)
    {
        cout << "Feedback: Good! Just needs more accuracy.\n";
    }
    else
    {
        cout << "Feedback: Keep practicing!\n";
    }
}
void show_debug_info(const float* time_ptr, const float* accuracy_ptr) 
{
    cout << "[DEBUG INFO - Read Only]\n";
    cout << "typing_time_seconds @ " << time_ptr << " = " << *time_ptr << endl;
    cout << "accuracy_percent @ " << accuracy_ptr << " = " << *accuracy_ptr << endl;
    cout << endl;
}
void start_typing_test()
{
    string sentence_to_type = "The quick brown fox jumps over the lazy dog.";
    string user_input_sentence;
    string clear_input;
    time_t end_time, start_time;
    char debug;

    cout << "Rule 1:Type as fast as you can!\n";
    cout << "The target sentence is: " << sentence_to_type << endl;
    cout << "Press enter to begin the test!\n";

    getline(cin, clear_input);
    getline(cin, clear_input);
    start_time = time(0);
    getline(cin, user_input_sentence);
    end_time = time(0);

    float typing_time_seconds = end_time - start_time;

    int sentence_length = 0;

    while (sentence_to_type[sentence_length] != '\0')
    {
       sentence_length++;   
    }

    int correct_characters = count_correct_characters(sentence_to_type, user_input_sentence, sentence_length);
    float accuracy = calculate_accuracy_percent(correct_characters, sentence_length);
    accuracy_ptr = &accuracy;
    time_ptr = &typing_time_seconds;
    show_typing_results(user_input_sentence, correct_characters, sentence_length, accuracy, typing_time_seconds);

    do
    {
        cout << endl;
        cout << "Do you want to show debug info? (Y/N): ";
        cin >> debug;
    } while ((debug != 'Y' && debug != 'y' && debug != 'N' && debug != 'n'));

    if (debug == 'Y' || debug == 'y')
    {
        show_debug_info(time_ptr, accuracy_ptr);
    }
    else
    {
        return;
    }

}