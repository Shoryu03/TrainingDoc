#pragma once
#include <string>
#include <iostream>
#include "json.hpp"
/**
 * @brief Base class for all exercises
 */
namespace gm{
    using json = nlohmann::ordered_json;

    /**
    * @brief Abstract class representing every exercise
    */
    class Exercise {
    protected:
        std::string m_name;
        std::string m_info;
        int m_sets;
        double m_weight;
        bool m_error;
        std::string m_comment;
        

    public:
    /**
    * @brief Parametrized constructor with value validations
    * 
    */
        Exercise(std::string name, std::string info, int sets, double weight, std::string comment, bool error) : m_name(name), m_info(info), m_sets(sets), m_weight(weight),m_comment(comment),  m_error(error) {
            if (m_sets <= 0 || m_weight < 0){ 
                m_error = true;
            }
        }
    /**
    * @brief default constructor
    */
        Exercise():
            m_name("unknown"),
            m_info("unknown"),
            m_sets(0),
            m_weight(0.0),
            m_error(false),
            m_comment("unknown"){
                
            }
        
            /**
            * @brief virtual destructor
            */
        virtual ~Exercise(){

        }

        /**
        * @brief getter for error flag
        */
        bool getError() const {
            return m_error;
        }
        /**
        * @brief pure virtual method
        * calculate training volume for each exercise
        */
        virtual double calc_volume() const = 0;
        
        /**
        * virtual method
        * creates json object containing all class fields
        */
        virtual json toJson() const {
            json data;
            data["name"] = m_name;
            data["info"] = m_info;
            data["sets"] = m_sets;
            data["weight"] = m_weight;
            data["volume"] = calc_volume();
            data["comment"] = m_comment;
            return data;
        }
    };
}