#ifndef LSYSTEM_H
#define LSYSTEM_H

#include "Turtle.h"
#include <string>
#include <map>
#include <memory>

class LSystem
{
public:
    LSystem();
    LSystem(std::map<std::string, std::string> & mappings, std::string start, float angle);
    std::string generate(int replacements);
private:
    std::string m_current;
    std::map<std::string, std::string> m_mappings;
    float m_length;
    float m_angle;
    void replace(void);
    void draw(void);
    // need something to get cylinders from turtle
    std::unique_ptr<Turtle> m_turtle;


};

#endif // LSYSTEM_H
