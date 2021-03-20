#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <chrono>
#include <utility>

#include "../SequenceStringGenerator.h"

int main()
{
	
	

	{
		std::chrono::high_resolution_clock::time_point now = std::chrono::high_resolution_clock::now();

		std::map<std::string, int> STD_STRING_MAP{};
		for (int i = 0; i < 100; i++)
		{
			char c[DIGIT_NUM + 1];
			_itoa_s(i, c, DIGIT_NUM + 1, 10);

			std::string str{ "Test String Index : " };
			str += c;

			STD_STRING_MAP[str] = i;
		}

		for (int i = 0; i < 100; i++)
		{
			char c[DIGIT_NUM + 1];
			_itoa_s(i, c, DIGIT_NUM + 1, 10);

			std::string str{ "Test String Index : " };
			str += c;
			int a = STD_STRING_MAP[str];
		}

		std::chrono::high_resolution_clock::time_point end = std::chrono::high_resolution_clock::now();
		std::cout << std::chrono::duration_cast<std::chrono::microseconds>(end - now).count() << std::endl;
	}

	{
		std::chrono::high_resolution_clock::time_point now = std::chrono::high_resolution_clock::now();

		std::map<std::string, int> STD_STRING_MAP{};
		std::vector<std::string> KeyList{};
		for (int i = 0; i < 100; i++)
		{
			char c[DIGIT_NUM + 1];
			_itoa_s(i, c, DIGIT_NUM + 1, 10);

			std::string str{ "Test String Index : " };
			str += c;

			STD_STRING_MAP[str] = i;

			KeyList.push_back(std::move(str));
		}

		for (int i = 0; i < 100; i++)
		{
			int a = STD_STRING_MAP[KeyList[i]];
		}


		std::chrono::high_resolution_clock::time_point end = std::chrono::high_resolution_clock::now();
		std::cout << std::chrono::duration_cast<std::chrono::microseconds>(end - now).count() << std::endl;
	}
	
	{
		std::chrono::high_resolution_clock::time_point now = std::chrono::high_resolution_clock::now();

		std::map<const char*, int> LITERAL_STRING_MAP{};
		for (int i = 0; i < 100; i++)
		{
			LITERAL_STRING_MAP[SequenceStringGenerator::GetLiteralString("Test String Index : ", i)] = i;
		}

		for (int i = 0; i < 100; i++)
		{
			int a = LITERAL_STRING_MAP[SequenceStringGenerator::GetLiteralString("Test String Index : ", i)];
		}


		std::chrono::high_resolution_clock::time_point end = std::chrono::high_resolution_clock::now();
		std::cout << std::chrono::duration_cast<std::chrono::microseconds > (end - now).count() << std::endl;
	}
}