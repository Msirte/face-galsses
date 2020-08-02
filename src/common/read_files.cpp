#include "read_files.h"


string removeSuffix(string fileName)
{
	const char* full_name = fileName.c_str();
	const char*  mn_first = full_name;
	int tmp = strlen(full_name);//长度不包含'/0'
	const char*  mn_last = full_name /*+ strlen(full_name)*/;
	if (strrchr(full_name, '\\') != NULL)//去除路径，只留文件名
		mn_first = strrchr(full_name, '\\') + 1;
	else if (strrchr(full_name, '/') != NULL)//去除linux下的文件路径
		mn_first = strrchr(full_name, '/') + 1;
	if (strrchr(full_name, '.') != NULL)
		mn_last = strrchr(full_name, '.');//获取.*后缀
	if (mn_last < mn_first)//地址比较
		mn_last = full_name + strlen(full_name);
	fileName.assign(mn_first, mn_last);//参数10001.jpg和.jpg
	return fileName;
}


int readFileList(char *basePath, vector<string>& fileNames)
{
    DIR *dir;
    struct dirent *ptr;
    char base[1000];
	string fileName;
	string str_basePath;
	str_basePath.assign(basePath);

    if ((dir=opendir(basePath)) == NULL)
    {
        perror("Open dir error...");
        exit(1);
    }

    while ((ptr=readdir(dir)) != NULL)
    {
        if(strcmp(ptr->d_name,".")==0 || strcmp(ptr->d_name,"..")==0)    ///current dir OR parrent dir
            continue;
        else if(ptr->d_type == 8)    ///file
		{
			fileName = str_basePath;
			fileName.append(ptr->d_name);
			fileNames.push_back(fileName);
		}
        else if(ptr->d_type == 10)    ///link file
		{
			fileName = str_basePath;
			fileName.append(ptr->d_name);
			fileNames.push_back(fileName);
		}
        else if(ptr->d_type == 4)    ///dir
        {
            memset(base,'\0',sizeof(base));
            strcpy(base,basePath);
            strcat(base,"/");
            strcat(base,ptr->d_name);
            readFileList(base, fileNames);
        }
    }
    closedir(dir);
    return 1;
}