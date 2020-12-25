#pragma once

#include <iostream>
#include "unordered_map"
#include <vector>

class LogManager {
public:
    void add_log_note(std::string, std::string);
    std::vector<std::string> find_log_notes_by_time(std::string);
    std::unordered_map<std::string, std::vector<std::string>> get_all_notes();
private:
    std::unordered_map<std::string, std::vector<std::string>> _log; // �࠭���� ����� �� �६���
};