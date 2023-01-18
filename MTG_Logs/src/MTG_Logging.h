#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <chrono>


using namespace std::chrono_literals;
typedef std::chrono::steady_clock  MTG_CLOCK;
typedef std::chrono::time_point<MTG_CLOCK>  MTG_TIME_POINT;
typedef std::chrono::duration<long long, std::nano> MTG_DURATION;
class LogFile
{
public:

	bool LOG(std::string message) {
		std::string prefix = log_prefix();
		std::cout << prefix << message << std::endl;
		m_file << prefix << message << std::endl;
	}

	LogFile(std::string filename, std::string severity) {
		m_startTime = MTG_CLOCK::now();
		m_severity = severity;
		m_file.open(filename, std::ios::trunc | std::ios::out);
		std::cout << "NEW LOGGER WITH SEVERITY: [" << severity << "] CREATED AT " << std::chrono::system_clock::now() << std::endl;
		m_file << "NEW LOGGER WITH SEVERITY: [" << severity << "] CREATED AT " << std::chrono::system_clock::now() << std::endl;
	}

	~LogFile() {
		std::cout << "LOGGER WITH SEVERITY : [" << m_severity << "] DELETED AT " << std::chrono::system_clock::now() << std::endl;
		m_file << "LOGGER WITH SEVERITY : [" << m_severity << "] DELETED AT " << std::chrono::system_clock::now() << std::endl;
		m_file.close();
	}


private:
	std::ofstream m_file;
	MTG_TIME_POINT m_startTime;
	std::string m_severity;

	std::string log_prefix() {
		MTG_DURATION log_time = MTG_CLOCK::now() - m_startTime;
		return "[" + std::to_string(log_time.count()) + "]\t" + m_severity + '\t';
	}
};
