#include <iostream>
#include <string>
#include <vector>
#include "value_checker.hpp"
#include "Workout.hpp"
#include "PushUps.hpp"
#include "PullUps.hpp"
#include "Dips.hpp"
#include "Plank.hpp"
#include "Custom.hpp"
#include "get_date.hpp"


void check() {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }


int main() {
    std::string name;
    std::string info;
    std::string comment;
    double custom_vol_coef;
    double weight;
    double volume_coef;
    int sub_options;
    int sets, reps, exe_time;
    int main_options;
    bool adding = true;
    bool save = true;
    bool running = true;
    std::string date;
    
    while(running) {
        std::cout << "--------MENU--------" << std::endl;
        std::cout << "Hello!, choose option" << std::endl;
        std::cout << "1. Add training" << std::endl;
        std::cout << "2. Delete last training" << std::endl;
        std::cout << "3. Show history" << std::endl;
        std::cout << "4. Exit" << std::endl;
        if (!(std::cin >> main_options)){
            check();
            continue;
        }
        
        switch (main_options) {
            case 1: {
                date = gm::get_date();
                std::cout << date << std::endl;
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Enter the training name: " << std::endl;
                getline(std::cin, name);
                adding = true;
                save = true;
            
                gm::Workout training(date, name);

                while (adding) {
                    std::cout << "1. Add PushUps" << std::endl;
                    std::cout << "2. Add PullUps" << std::endl;
                    std::cout << "3. Add Dips" << std::endl;
                    std::cout << "4. Add Plank" << std::endl;
                    std::cout << "5. Add Custom Exercise" << std::endl;
                    std::cout << "6. Save and exit" << std::endl;
                    std::cout << "7. Exit without saving" << std::endl;

                    if (!(std::cin >> sub_options)){
                        check();
                        continue;
                    
                    }
                    switch(sub_options) {
                        case 1:
                            std::cout << "How much reps: " << std::endl;
                            reps = gm::good_input<int>();
                            std::cout << "How much sets: " << std::endl;
                            sets = gm::good_input<int>();
                            std::cout << "How much weight (kg ): " << std::endl;
                            weight = gm::good_input<double>();
                            std::cout << "Comment: " << std::endl;
                            
                            getline(std::cin, comment);
                            training += new gm::PushUps(sets, reps, weight, comment);
                            break;
            
                        case 2:
                            std::cout << "How much reps: " << std::endl;
                            reps = gm::good_input<int>();
                            std::cout << "How much sets: " << std::endl;
                            sets = gm::good_input<int>();
                            std::cout << "How much weight (kg): " << std::endl;
                            weight = gm::good_input<double>();
                            
                            std::cout << "Comment: " << std::endl;
                            getline(std::cin, comment);
                            training += (new gm::PullUps(sets, reps, weight, comment));
                            break;

                        case 3:
                            std::cout << "How much reps: " << std::endl;
                            reps = gm::good_input<int>();
                            std::cout << "How much sets: " << std::endl;
                            sets = gm::good_input<int>();
                            std::cout << "How much weight (kg): " << std::endl;
                            weight = gm::good_input<double>();
                            
                            std::cout << "Comment: " << std::endl;
                            getline(std::cin, comment);
                            training += (new gm::Dips(sets, reps, weight, comment));
                            break;

                        case 4:
                            std::cout << "How much sets: " << std::endl;
                            sets = gm::good_input<int>();
                            std::cout << "How much time (s): " << std::endl;
                            exe_time = gm::good_input<int>();
                            std::cout << "How much weight (kg): " << std::endl;
                            weight = gm::good_input<double>();
                            
                            std::cout << "Comment: " << std::endl;
                            getline(std::cin, comment);
                            training += (new gm::Plank(sets, exe_time, weight, comment));
                            break;

                        case 5:
                            
                            std::cout << "Enter name of your exercise: " << std::endl;
                            getline(std::cin, name);
                            std::cout << "How much reps (0 if exercise is for time): " << std::endl;
                            reps = gm::good_input<int>();
                            std::cout << "How much sets: " << std::endl;
                            sets = gm::good_input<int>();
                            std::cout << "How much weight (kg): " << std::endl;
                            weight = gm::good_input<double>();
                            std::cout << "How much time (0 if exercise is for sets): " << std::endl;
                            exe_time = gm::good_input<int>();
                            std::cout << "What volume coefficient you want to add: " << std::endl;
                            volume_coef = gm::good_input<double>();
                            
                            std::cout << "For what muscles is this exercise: " << std::endl;
                            getline(std::cin, info);
                            std::cout << "Comment: " << std::endl;
                            getline(std::cin, comment);
                            training += (new gm::Custom(name, info, sets, reps, weight, exe_time, volume_coef, comment));
                            break;

                        case 6:
                            if (training.getFlag()) {
                                std::cout << "ERROR!: Training won't save, wrong values!" << std::endl;
                            } else {
                                std::cout << "Training saved, returning to menu" << std::endl;
                                adding = false;
                                }
                            break;

                        case 7:
                            std::cout << "Training discarded. Returning to menu" << std::endl;
                            save = false;
                            adding = false;
                            break;

                            default:
                            std::cout << "Wrong option! Try again" << std::endl;
                            break;
                    }
                }       
                if (save) {
                training.saveToFile();
                }
                break;
            }  
            case 2:
                gm::Workout::delete_last();
                std::cout << "Last training deleted" << std::endl;
                break;

            case 3: 
                {
                std::string report = gm::Workout::training_history();
                std::cout << report << std::endl;
                
                 
                break;
                }
            case 4:
                std::cout << "Leaving aplication..." << std::endl;
                running = false;
                break; 

            default:
                std::cout << "Wrong option! Try again" << std::endl;
        }
    
    }
    return 0;
}