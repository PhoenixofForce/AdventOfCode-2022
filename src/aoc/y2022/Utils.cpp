#include "Utils.h"

using clock_type = std::chrono::steady_clock;
using second_type = std::chrono::duration<double, std::ratio<1> >;

static std::chrono::time_point<clock_type> start{};

std::string getFileName(int year, int day) {
    std::string out{ "../../../" + std::to_string(year) + "inputs/Day" + (day > 9? std::to_string(day): "0" + std::to_string(day)) + "_Input" };
    return { out };
}

std::ifstream getReader(int year, int day) {
  std::ifstream f;
  std::cout << getFileName(year, day) << std::endl;
  f.open(getFileName(year, day));

  //execute jar that fetches the input from the website
  if(f.fail()) {
    std::string command{ "cd .. & cd .. & cd .. & InputGrabber.bat " + std::to_string(year) + " " + std::to_string(day) };
    system(command.c_str());
    std::cout << std::endl;

    f.close();
    f.open(getFileName(year, day));
  }

  return f;
}

std::string getFile(int year, int day){
  std::string out;
  std::ifstream f{getReader(year, day)};

  std::string line;
  while(std::getline(f, line)) {
    out += line;
  }
  f.close();

  start = clock_type::now();
  return out;
}

void getLines(std::vector<std::string>& list, int year, int day) {
  std::ifstream f = getReader(year, day);

  std::string line;
  while(std::getline(f, line)) {
    list.push_back(line);
  }
  f.close();
  start = clock_type::now();
}

void getParagraphs(std::vector<std::string>& list, int year, int day){
  std::ifstream f = getReader(year, day);

  std::string line;
  std::string current;
  while(std::getline(f, line)) {
    if(line.length() == 0) {
      list.push_back(strings::trim(current));
      current = "";

      continue;
    }

    current += line + " ";
  }

  if(current.length() > 0) list.push_back(strings::trim(current));
  start = clock_type::now();
}

std::ostream& print(int part) {
  static std::chrono::time_point<clock_type> lastSolution{};
  static int solution{0};
  double timeFromStart{ std::chrono::duration_cast<second_type>(clock_type::now() - start).count() };

  std::cout << std::endl <<  "------------------" << std::endl;
  std::cout << "Solution for part " << (std::max(solution, part) + 1);
  if(part > 0 || solution > 0) {
    double timeFromLast{std::chrono::duration_cast<second_type>(clock_type::now() - lastSolution).count()};
    std::cout << " in " << timeFromLast << "s";
  } else {
    std::cout << " in " << timeFromStart << "s";
  }
  std::cout << " (" << timeFromStart << "s total)" << std::endl;

  solution += 1;
  lastSolution = clock_type::now();
  return std::cout;
}