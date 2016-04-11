#include<iostream>
#include<stdexcept>
#include<cmath>
#include<string>

unsigned int GetBitsNum(unsigned int x)
{
	unsigned int result=0;
	while(result++,x>>=1);
	return result;
}

unsigned int GetMask(std::size_t len)
{
	unsigned int mask=0x00;
	while(len!=0)
	{
		mask=(mask<<1)+1;
		len--;
	}
	return mask;
}

unsigned int BtoD(const std::string &src)
{
	unsigned int result=0;
	auto count=src.size()-1;
	for(auto &c:src)
	{
		if(c!='0'&&c!='1')
			throw std::runtime_error("the data is not binary");
		result=result+std::pow(2,count)*(c-48);
		count--;
	}
	return result;
}

bool CRCcheck(const std::string &Checksum,const std::string &Src)
{
	if(Checksum.size()>Src.size())
		throw std::runtime_error("Checksum's length is short than srouce data");
	
	unsigned int check=BtoD(Checksum);
	unsigned int src=BtoD(Src);
	
	auto checkSize=Checksum.size();
	auto srcSize=Src.size();
	auto mask=GetMask(checkSize);
	
	while(srcSize>=checkSize)
	{
		auto sizeDiff=srcSize-checkSize;
		auto temp=check^(src>>sizeDiff);
		src=temp<<sizeDiff|(src&~(mask<<sizeDiff));
		srcSize=GetBitsNum(src);
	}
	
	if(src!=0)
		return false;
	else
		return true;
}

int main()
{
	std::string Checksum;
	std::cout<<"please enter the checksum"<<std::endl;
	std::cin>>Checksum;
	
	std::string Src;
	std::cout<<"please enter the data you received"<<std::endl;
	std::cin>>Src;
	
	try
	{
		if(CRCcheck(Checksum,Src))
		{
			std::cout<<"data is right"<<std::endl;
		}
		else
		{
			std::cout<<"data error"<<std::endl;
		}
	}
	catch(std::runtime_error err)
	{
		std::cerr<<err.what()<<std::endl;
	}
	
	return 0;
}