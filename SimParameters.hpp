#ifndef SIM_PARAMETERS_HPP
#define SIM_PARAMETERS_HPP

#include <string>

struct Parameter {
	int id;
	bool isInt;
	std::string name;
	int valueInt;
	double valueDouble;
	double maxValue;
	double minValue;
};

class ParameterManager {
private:
	std::Vector<Parameter> parameterList;
	int paramCnt;
public:
	ParameterManager();
	void addIntParam(std::string name, int initalValue, int max, int min);
	void addDoubleParam(std::string name, double initalValue, double max, double min);
	int getIntParam(int id);
	double getDoubleParam(int id);
	int getIntParam(std::string name);
	double getDoubleParam(std::string name);
	bool setParam(int id, double value);
	
};

#endif