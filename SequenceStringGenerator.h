#pragma once

#include <string>
#include <vector>
#include <type_traits>
#include <unordered_map>

/// <summary>
/// If you wanna use string as key of key sorted container like map, unordered_map,
/// You should use std::string.
/// Why :	if you use string literal ( const char* ) as key, it can't works well
///			Because when compare key, it compare with address of literal string not checking if string is same
///			Luckly Some compilers allocate just one literal string on multiple same literal string
///			
///			But If you want to use literal string having sequence string like Entity1, Entity2, Entity3, Entity4
///			How to do this???.
/// 
///			You can't do this. 
/// 
///			std::unordered_map<const char*, int> uMap;
///			for(int i = 0 ; i < 10 ; i++)
///			{
///				uMap["Entity" + itoa(i)] // <--- this doesn't work, You can't merge two literal string
///			}
///			
///			So you should use std::string as key. but comparing std::string is 2x slower than comparing address.
///			So if you don't want to make std::string everytime, you should cache with std::string and pass iteral string data of std::string.
///			std::string::data() will return literal string data in std::string.
///			
///			This library will help this cumbersome works
///			
/// 
///			
///	Example : 
/// std::unordered_map<const char*, int> uMap;
/// for(int i = 0 ; i < 10 ; i++)
///	{
///		uMap[SequenceStringGenerator::GetLiteralString("Test String Index : ", i)];  // GetLiteralString return literal string "Test String Index : i"
///	}
/// </summary>

#define DIGIT_NUM 3
#define RESERVER_COUNT 100

class SequenceStringGenerator
{
	static_assert(std::is_same_v<std::conditional_t<"TEST LITEAL STRING" == "TEST LITEAL STRING", const char*, std::string>, const char*>);

private:

	static inline bool bmInit{ false };

	/// <summary>
	/// In C++20, You can initialize std::string at compile time ( constexpr )
	/// </summary>
	static inline std::unordered_map<const char*, std::vector<std::string>> StringList{};

public:

	static inline const char* GetLiteralString(const char* key, size_t index)
	{
		auto& strList = StringList[key];

		if (bmInit == false)
		{
			strList.resize(RESERVER_COUNT);
			bmInit = true;
		}
	
		if (strList.size() < index + 1)
		{
			strList.resize((index + 1) * 2);
		}
		
		if (strList[index].empty() == true)
		{
			char c[DIGIT_NUM + 1];
			_itoa_s(static_cast<int>(index), c, DIGIT_NUM + 1, 10);

			std::string str{ key };
			str += c;
			strList[index] = std::move(str);
		}
		return strList[index].data();
	}
};