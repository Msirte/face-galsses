#include "read_files.h"
#include "face.h"


int main(int argc, char* argv[])
{
    // ensure argc == 1
    if (argc != 1)
	{
		cout << "Parameter should be 1." << endl;
		cout << "False!" << endl;
		return 3;
	}

	char* basePath = argv[1];

	vector<string> fileNames;
	readFileList(basePath, fileNames);

	vector<string> names;
	vector<vector<float> > features(fileNames.size(), vector<float>(128));

	for (vector<string>::iterator it = fileNames.begin(); it != fileNames.end(); it++)
	{
		string fileName = *it;
		int index = distance(fileNames.begin(),it);

		// save name vector
		string name = removeSuffix(fileName);
		names.push_back(name);

		// save feature vector
		Mat img = imread(fileName);
		Mat face = mt(img);
		vector<float> feature = extract_feature(face);
		features[index] = feature;
	}

	ofstream outFeature("../data/feature.dat", ios::out | ios::app | ios::binary);
	ofstream outName("../data/name.dat", ios::out | ios::app);

	if (!outFeature.is_open())
	{
		cout << "Cannot open feature file."<< endl;
		return 2;
	}
	if (!outName.is_open())
	{
		cout << "Cannot open name file."<< endl;
		return 2;
	}

	for (auto feature : features)
	{
		outFeature.write((char*)&feature[0], sizeof(float)*128)
	}
	
	for (auto name : names)
	{
		outName << name << endl;
	}

	outFeature.close();
	outName.close();
	
    return 0;
}

