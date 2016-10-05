#pragma once
#include "stdafx.h"

const std::string CRIPT_PREFIX = "crypt";
const std::string DECRIPT_PREFIX = "decrypt";

bool CheckArgumentCount(int argumentCount);
bool CheckSettings(const std::string & settings);
bool CheckKey(const std::string & key);
bool OpenFile(std::ofstream & file, std::string fileName);
bool OpenFile(std::ifstream & file, std::string fileName);
void Encode(std::ifstream & input, std::ofstream & output, uint8_t key, const std::function<uint8_t(uint8_t byte, uint8_t key)> & EncodingFunction);
uint8_t Cript(uint8_t byte, uint8_t key);
uint8_t Decript(uint8_t byte, uint8_t key);
