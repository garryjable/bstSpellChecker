#include <algorithm>
#include <ctime>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "BinaryTree.hpp"
int main()
{
	std::ifstream dictionaryInput;
	dictionaryInput.open("Dictionary.txt");
	std::vector<std::string> dictionary;
	while (dictionaryInput)
	{
		std::string temp;
		dictionaryInput >> temp;
		dictionary.push_back(temp);
	}
	std::random_shuffle(dictionary.begin(), dictionary.end());
	for (unsigned int i = 0; i < dictionary.size(); i++)
	{
		for (unsigned int j = 0; j < dictionary[i].length(); j++)
		{
			if (dictionary[i][j] == '\'')
			{
				dictionary[i][j] = dictionary[i][j + 1];
				dictionary[i][j + 1] = 0;
			}
		}
	}
	BinaryTree<std::string> tree;
	std::cout << dictionary.size();
	for (unsigned int i = 0; i < dictionary.size(); i++)
	{
		tree.insert(dictionary[i]);
	}
	tree.statInfo();
	std::ifstream letterInput;
	letterInput.open("Letter.txt");
	std::vector<std::string> letter;
	while (letterInput)
	{
		std::string temp;
		letterInput >> temp;
		letter.push_back(temp);
	}
	for (unsigned int i = 0; i < letter.size(); i++)
	{
		for (unsigned int j = 0; j < letter[i].length(); j++)
			{
			switch (letter[i][j]) 
			{
			case'"':
			case',':
			case':':
			case'.':
			case'!':
			case'?':
			case'(':
			case')':
				letter[i].erase(j);
				break;
			}
			if (isupper(letter[i][j]))
			{
				letter[i][j] = tolower(letter[i][j]);
			}
			}
	}
	std::cout << std::endl
		<< std::endl
		<< "list of misspelled words"
		<< std::endl
		<< std::endl;

	for (unsigned int i = 0; i < letter.size(); i++)
	{ 
		if (!tree.search(letter[i]))
		{
			std::cout
				<< letter[i]
				<< std::endl;
		}
	}
	return 0;
}