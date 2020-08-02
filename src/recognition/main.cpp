#include "face.h"
#include <ctime>


clock_t start,stop;

int main()
{
    float simThreshold = 0.7f;
    ifstream inFeature("../data/feature.dat", ios::in | ios::binary);
    ifstream inName("../data/name.dat", ios::in);

    if (!inFeature.is_open())
	{
		cout << "Cannot open feature file."<< endl;
		return 2;
	}
	if (!inName.is_open())
	{
		cout << "Cannot open name file."<< endl;
		return 2;
	}

    vector<string> names;
    while(!inName.eof())
    {
        string name;
        getline(inName, name, '\n');
        names.push_back(name);
    }

    vector<vector<float> > features(names.size(), vector<float>(128));

    for (auto feature: features)
    {
        inFeature.read((char*)&feature[0], sizeof(float)*128);
    }
    

    VideoCapture capture(0);
    if (!capture.isOpened())
    {
        cout << "Camera not found." << endl;
        return 1;
    }

    while (1)
    {
        start=clock();
        Mat frame;
        capture >> frame;
        if (frame.empty())
		{
            cout<<"Cannot capture frames." << endl;
			break;
		}
        else
        {
            Mat face = mt(frame);
            
            if (face.empty())
                continue;

            vector<float> feature = extract_feature(face);

            vector<float> similarity;
            for (auto dbFeature : features)
            {
                similarity.push_back(calculSimilar(feature, dbFeature));
            }

            float maxValue = *max_element(similarity.begin(),similarity.end());
            if (maxValue > simThreshold)
            {
                int maxPosition = max_element(similarity.begin(),similarity.end()) - similarity.begin(); 
                cout << names[maxPosition] << endl;
            }
            else
            {
                cout << "Not Found!" << endl;
            }
            stop=clock();
            double endtime=(double)(stop-start)/CLOCKS_PER_SEC;
            cout<<"Total time:"<<endtime*1000<<"ms"<<endl;
        }
    }
    
    return 0;
}
