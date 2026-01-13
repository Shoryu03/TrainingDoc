#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "Exercise.hpp"
#include "json.hpp"
#include <sstream>
/**
 * @brief Workout class definition
 */
namespace gm{

    /**
    * @brief Workout class contains all exercises and represents a single workout session
    * Manage json file 
    */
    class Workout {
    private:
        std::string m_date;
        std::vector<Exercise*> m_exercises;
        std::string m_training_name;
        bool flaga = false;
        
    public:
    /**
    * @brief parametrized constructor
    */
        Workout(std::string date, std::string m_training_name) : m_date(date), m_training_name(m_training_name){

        }
    /**
    * @brief destructor, iterates through vector of exercises and deletes all pointers
    */
        ~Workout(){
            for(auto* e : m_exercises) delete e;
            m_exercises.clear();
        }
        /**
        * @brief getter for flag
        */
        bool getFlag() const{
            return flaga;
        }

        /**
        * @brief method for sum all volume in one training session 
        */
        double total_volume() const {
            double sum = 0.0;
            for (auto* exe : m_exercises) {
                sum += exe->calc_volume();
            }
            return sum;
        }

        /**
        * @brief method for adding exercise to workout, checking error flag
        */
        void addExercise(Exercise* exe) {
            m_exercises.push_back(exe);
            if (exe->getError() == true){
                flaga = true;
            }
        }
        /**
        * @brief method to delete last training session
        */
        static void delete_last(){
            json data;
            std::ifstream input("training_doc.json");
            if(input.good()) {
                input >> data;
            }
            input.close();
            if(!data.empty()) {
            data.erase(data.end()-1); 
            }
            std::ofstream output("training_doc.json");
            output << data.dump(4);
            output.close();
        }

        /**
        * @brief method to 
        * -save data from one workout to json
        * -calculate volume progress 
        * -validate with error flag
        */
        void saveToFile(){
            if (flaga == false){
            json data_base;

            std::ifstream input("training_doc.json");
            if (input.good()) {
                    input >> data_base;
            } else {
                data_base = json::array();
            }
            input.close();
            
            double suma = total_volume();
            double last_vol;

            if(!data_base.empty()) {
                json last_train = data_base.back();
                last_vol = last_train.value("total_volume",0.0);
            }
            double diff = suma - last_vol;
            
            json training;
            training["training_name"] = m_training_name;
            training["date"] = m_date;
            training["exercises"] = json::array();
            training["total_volume"] = suma;
            training["volume_progress"] = diff;

            for (auto* e : m_exercises) {
                training["exercises"].push_back(e->toJson());
            }
            data_base.push_back(training);
            std::ofstream output("training_doc.json");
            output << data_base.dump(4);
            output.close();
            }
        }

        /**
        * @brief overloaded operator += for adding exercise
        */
        Workout& operator+=(Exercise* exe) {
            this->addExercise(exe); 
            return *this;      
        }
        
        /**
        * @brief static method to show whole trainings doc
        */

        static std::string training_history() {
            std::ifstream input("training_doc.json");
            std::stringstream ss;

            if (!input.good()) {
                return "ERROR! No training file! \n";
            }

            json data = json::parse(input, nullptr, false);

            if (data.empty() || data.is_discarded()) {
                return "ERROR! You have no trainings in your .json file or file corupted \n";
            }

            ss << "          HISTORIA TRENINGOW            " << "\n";
            ss << "----------------------------------------" << "\n";

            for (const auto& training : data) {
                ss << "DATE:   " << training.value("date", "null") << "\n";
                ss << "NAME:  " << training.value("training_name", "null") << "\n";
                

                ss << "----------------------------------------" << "\n";
                ss << " EXERCISES:" << "\n";

                for (const auto& exe : training["exercises"]) {
                    ss << "  --" << exe.value("name", "null");
                    ss << " | SETS: " << exe.value("sets", 0);
                    if (exe.contains("reps")) {
                        ss << " | REPS: " << exe["reps"];
                    }
                    if (exe.contains("time")) {
                        ss << " | TIME: " << exe["time"] << "s";
                    }
                    
                    ss << " | WEIGHT: " << exe.value("weight", 0.0) << "kg" << "\n";
                    
                    ss << "Komentarz: " << exe.value("comment", "null") << "\n";
                    ss << "VOLUME: " << exe.value("volume", 0.0) << "\n";
                }
                    
                    ss << "TOTAL VOLUME: " << training.value("total_volume", 0.0) << "\n";
                    ss << "PROGRESS: " << training.value("volume_progress", 0.0) << "\n";
                    ss << "------------------------------------------\n";
            }
            input.close();
            return ss.str();
        }
    };
}