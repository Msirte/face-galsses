#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <unistd.h>

using namespace std;

string removeSuffix(string fileName);
int readFileList(char *basePath, vector<string>& fileNames);

