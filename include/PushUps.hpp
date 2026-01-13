#include "Exercise.hpp"
#pragma once

/**
 * @brief  definition of derived PushUps class, one of the exercise
 */

namespace gm{
    class PushUps : public Exercise {
    private:
        int m_reps; 

    public:
        /**
        * @brief parametrized constuctor
        */
        PushUps(int sets, int reps, double weight, std::string comment) : Exercise("Push ups", "Chest, tricpes, biceps", sets, weight, comment, false), m_reps(reps){
            if (m_reps <= 0){ 
                m_error = true;

            }
        }
        /**
        * @brief default constructor
        */
        PushUps():
            Exercise(),
            m_reps(0)
        {

        }
        /**
        * override method from base class with own values
        */
        double calc_volume() const override {
            if (m_weight > 0) {
            return m_sets * m_reps * m_weight * 0.7;
            }
            else {
            return m_sets * m_reps * 0.7;
            } 
        }
        
        /**
        * @brief add "reps" field to json file
        */
        json toJson() const override {
            json data = Exercise::toJson();
            data["reps"] = m_reps;
            return data;

        }
    };
}