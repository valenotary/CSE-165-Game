#pragma once
#ifndef DATALOADER_H
#define DATALOADER_H

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>

//I wanted to be able to load character features
//from text files and automatically have them 
//loaded in for me rather than me manually
//typing in every single state animation

struct cData {
	std::string imgName;
	int row, col;

	cData();
	cData(std::string, int, int);
};

std::vector<cData> loadData(std::string);
#endif /*DATALOADER_H*/