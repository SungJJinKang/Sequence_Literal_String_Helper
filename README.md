# Sequence_Literal_String_Helper

If you wanna use string as key of key sorted container like map, unordered_map      
You should use std::string.      
But with this library you can make literal string easily

## Why need this 

if you use string literal ( const char* ) as key, it can't works well     
Because when compare key, it compare with address of literal string not checking if string is same     
Luckly Some compilers allocate just one literal string on multiple same literal string     
			
But If you want to use literal string having sequence string like Entity1, Entity2, Entity3, Entity4    
How to do this???.     

You can't do this.      
```c++
std::unordered_map<const c`har*, int> uMap;     
for(int i = 0 ; i < 10 ; i++)     
{
  uMap["Entity" + itoa(i)] // <--- this doesn't work, You can't merge two literal string     
}      
```

So you should use std::string as key. but comparing std::string is 2x slower than comparing address.        
So if you don't want to make std::string everytime, you should cache with std::string and pass iteral string data of std::string.       
std::string::data() will return literal string data in std::string.            
		
This library will help this cumbersome works          
		
 
		
## Example 
```c++
std::unordered_map<const char*, int> uMap;     
for(int i = 0 ; i < 10 ; i++)
{
  uMap[SequenceStringGenerator::GetLiteralString("Test String Index : ", i)];  // GetLiteralString return literal string "Test String Index : i"
}
```
